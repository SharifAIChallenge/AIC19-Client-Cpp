#include "Controller.h"

#include <iostream>
#include <thread>
#include <chrono>

#include <Utility/Utility.h>
#include <Utility/Logger.h>

#include <Network/NetworkError.h>
#include <Core/Message/PickMessage.h>

#include "Message/ParseError.h"

#include "Message/InitMessage.h"
#include "Message/TurnMessage.h"
#include "Message/ShutdownMessage.h"
#include "Message/AuthenticationMessage.h"
#include "Message/EndTurnMessage.h"

int Controller::thread_count = 0;

Controller::Controller(const std::string& host, uint16_t port, const std::string& token, unsigned retry_delay)
        : m_token(token)
        , m_retry_delay(retry_delay)
        , m_network(host, port)
        , m_world(m_event_queue)
{
    Logger::Get(LogLevel_DEBUG) << "Server is " << host << ":" << port << std::endl;
    Logger::Get(LogLevel_DEBUG) << "Authentication token is " << token << std::endl;
    Logger::Get(LogLevel_DEBUG) << "Retry delay is " << retry_delay << std::endl;
}

Controller::~Controller() {
    if (m_event_handling_thread.joinable())
        m_event_handling_thread.join();
    if (m_network.is_connected())
        m_network.disconnect();
}

void Controller::run() try {
    Logger::Get(LogLevel_TRACE) << "Enter Controller::run" << std::endl;

    // Connect to the server

    constexpr size_t MAX_RETRY_COUNT = 3;
    for (size_t i = 1; i <= MAX_RETRY_COUNT && !m_network.is_connected(); ++i)
        try {
            Logger::Get(LogLevel_INFO) << "Trying to connect #" << i << std::endl;
            m_network.connect();
        }
        catch (NetworkError &e) {
            if (i == MAX_RETRY_COUNT)
                throw;
            else
                std::this_thread::sleep_for(std::chrono::milliseconds(m_retry_delay));
        }

    Logger::Get(LogLevel_INFO) << "Connected" << std::endl;

    Logger::Get(LogLevel_TRACE) << "Sending authentication message" << std::endl;
    m_network.send(AuthenticationMessage(m_token).to_string());// about the authentication process

    // Now wait for init message
    Logger::Get(LogLevel_TRACE) << "Waiting for init message" << std::endl;

    // Start the event handling thread
    m_event_handling_thread = std::thread(&Controller::event_handling_loop, this);

    while (m_network.is_connected()) {
        Logger::Get(LogLevel_TRACE) << "Waiting for init/pick/turn/shutdown message" << std::endl;

        auto message = Message::CreateFromJsonString(m_network.receive());

        if (InitMessage* init_message = dynamic_cast<InitMessage*>(message.get())) {
            Logger::Get(LogLevel_TRACE) << "Parsing init message" << std::endl;

            m_world.initData();
            init_message->update_world(&m_world);

            World* _world = new World(m_world);

            std::thread * preProcThread =
                    new std::thread(Controller::preProcess_event,&m_client,_world,&(this->m_event_queue));
            m_thread_list.push_back(preProcThread);
        }
        else if (PickMessage* pick_message = dynamic_cast<PickMessage*>(message.get())) {
            Logger::Get(LogLevel_INFO) << "Received Pick message from server" << std::endl;
            World* _world = new World(m_world);//copying a from the initial world
            Logger::Get(LogLevel_INFO) << "Received update_game server" << std::endl;

            pick_message->update_game(_world);

            std::thread * pickThread =
                    new std::thread(Controller::pick_event,&m_client,_world,&(this->m_event_queue));
            m_thread_list.push_back(pickThread);
        }
        else if (TurnMessage* turn_message = dynamic_cast<TurnMessage*>(message.get())) {
//            Logger::Get(LogLevel_INFO) << "Received Turn message from server" << std::endl;
            World* _world = new World(m_world);//copying a from the initial world
            turn_message->update_game(_world);//updating the new world
            Logger::Get(LogLevel_DEBUG) << "Current turn is " << _world->currentTurn() << std::endl;
            if(_world->currentPhase() == Phase::MOVE){
                Logger::Get(LogLevel_INFO) << "Received Move message from server" << std::endl;

                std::thread * moveThread =
                        new std::thread(Controller::move_event,&m_client,_world,&(this->m_event_queue));
                m_thread_list.push_back(moveThread);
            } else if (_world->currentPhase() == Phase::ACTION){
                Logger::Get(LogLevel_INFO) << "Received Action message from server" << std::endl;

                std::thread* actionThread =
                        new std::thread(Controller::action_event,&m_client,_world,&(this->m_event_queue));
                m_thread_list.push_back(actionThread);
            } else
                throw std::string("Can't determine phase of turn message");

        }
        else if (dynamic_cast<ShutdownMessage*>(message.get())) {
            Logger::Get(LogLevel_INFO) << "Received shutdown message from server" << std::endl;
            break;
        }



    }
    Logger::Get(LogLevel_INFO) << "Closing the connection" << std::endl;
    m_event_queue.terminate();
    m_network.disconnect();

    Logger::Get(LogLevel_INFO) << "Joining all threads" << std::endl;
    for (std::thread * _thread : m_thread_list){
        _thread->join();
        delete _thread;
    }

    Logger::Get(LogLevel_TRACE) << "Exit Controller::run" << std::endl;


}
catch (Json::Exception&) {
    throw ParseError("Malformed json string");
}

void Controller::event_handling_loop() noexcept {
    while (m_network.is_connected()) {
        auto message = m_event_queue.pop();
        if (!message)
            break;
        m_network.send(message->to_string());
    }
}

void Controller::preProcess_event(AI *client, World *tmp_world, EventQueue *m_event_queue) {
    int THREAD_NUM = Controller::thread_count++;
    try{
        Logger::Get(LogLevel_DEBUG) << "Launched preProcess Thread #" << THREAD_NUM << std::endl;
        client->preProcess(tmp_world);
    }catch(const char* err_msg){
        Logger::Get(LogLevel_ERROR) << "Error in preProcess Thread #" << THREAD_NUM << std::endl <<
                                    err_msg << std::endl;
    }

    Logger::Get(LogLevel_TRACE) << "preProcess:Sending end message with turn = " << tmp_world->currentTurn() << std::endl;
    m_event_queue->push(EndTurnMessage("init-end",{}));

    delete tmp_world;
    Logger::Get(LogLevel_DEBUG) << "End of preProcess Thread #" << THREAD_NUM << std::endl;
}

void Controller::pick_event(AI* client,World* tmp_world, EventQueue *m_event_queue) {
    int THREAD_NUM = Controller::thread_count++;
    try {
        Logger::Get(LogLevel_DEBUG) << "Launched pick Thread #" << THREAD_NUM << std::endl;
        client->pick(tmp_world);
    }catch(const char* err_msg){
        Logger::Get(LogLevel_ERROR) << "Error in pick Thread #" << THREAD_NUM << std::endl <<
                                    err_msg << std::endl;
    }

    Logger::Get(LogLevel_TRACE) << "pick:Sending end message with turn = " << tmp_world->currentTurn() << std::endl;
    m_event_queue->push(EndTurnMessage("pick-end",{tmp_world->currentTurn()}));

    delete tmp_world;
    Logger::Get(LogLevel_DEBUG) << "End of pick Thread #" << THREAD_NUM << std::endl;
}

void Controller::move_event(AI* client,World* tmp_world, EventQueue *m_event_queue) {
    int THREAD_NUM = Controller::thread_count++;
    try {
        Logger::Get(LogLevel_DEBUG) << "Launched move Thread #" << THREAD_NUM << std::endl;
        client->move(tmp_world);
    }catch(const char* err_msg){
        Logger::Get(LogLevel_ERROR) << "Error in move Thread #" << THREAD_NUM << std::endl <<
                                    err_msg << std::endl;
    }


    Logger::Get(LogLevel_TRACE) << "move:Sending end message with turn = " << tmp_world->currentTurn() << std::endl;
    m_event_queue->push(EndTurnMessage("move-end",{tmp_world->currentTurn(),tmp_world->movePhaaseNum()}));

    delete tmp_world;
    Logger::Get(LogLevel_DEBUG) << "End of move Thread #" << THREAD_NUM << std::endl;
}

void Controller::action_event(AI* client,World* tmp_world, EventQueue *m_event_queue) {
    int THREAD_NUM = Controller::thread_count++;
    try {
        Logger::Get(LogLevel_DEBUG) << "Launched action Thread #" << THREAD_NUM << std::endl;
        client->action(tmp_world);
    }catch(const char* err_msg){
        Logger::Get(LogLevel_ERROR) << "Error in action Thread #" << THREAD_NUM << std::endl<<
                                    err_msg << std::endl;
    }

    Logger::Get(LogLevel_TRACE) << "action:Sending end message with turn = " << tmp_world->currentTurn() << std::endl;
    m_event_queue->push(EndTurnMessage("action-end",{tmp_world->currentTurn()}));

    delete tmp_world;
    Logger::Get(LogLevel_DEBUG) << "End of action Thread #" << THREAD_NUM << std::endl;
}

