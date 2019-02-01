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
    m_network.send(AuthenticationMessage(m_token).to_string());//TODO about the authentication process

    // Now wait for init message
    Logger::Get(LogLevel_TRACE) << "Waiting for init message" << std::endl;

//    InitMessage init_message(m_network.receive());



    // Start the event handling thread
    //TODO maybe this should be called after the InitMessage
    m_event_handling_thread = std::thread(&Controller::event_handling_loop, this);

    while (m_network.is_connected()) {
        Logger::Get(LogLevel_TRACE) << "Waiting for turn/shutdown message" << std::endl;

        auto message = Message::CreateFromJsonString(m_network.receive());

        if (InitMessage* init_message = dynamic_cast<InitMessage*>(message.get())) {
            Logger::Get(LogLevel_TRACE) << "Parsing init message" << std::endl;
            m_world.importInitData(*init_message);
        }
        else if (PickMessage* pick_message = dynamic_cast<PickMessage*>(message.get())) {
            Logger::Get(LogLevel_INFO) << "Received Pick message from server" << std::endl;
            World* _world = new World(m_world);//copying a from the initial world
            pick_message->update_game(_world);

            std::unique_ptr<std::thread> pickThread =
                    std::unique_ptr<std::thread>(
                            new std::thread(Controller::pick_event,&m_client,_world));
            m_thread_list.push_back(std::move(pickThread));
        }
        else if (TurnMessage* turn_message = dynamic_cast<TurnMessage*>(message.get())) {
            World* _world = new World(m_world);//copying a from the initial world
            turn_message->update_game(_world);//updating the new world
            if(_world->currentPhase() == Phase::MOVE){
                Logger::Get(LogLevel_INFO) << "Received Move message from server" << std::endl;

                std::unique_ptr<std::thread> moveThread =
                        std::unique_ptr<std::thread>(
                                new std::thread(Controller::move_event,&m_client,_world));
                m_thread_list.push_back(std::move(moveThread));
            } else if (_world->currentPhase() == Phase::ACTION){
                Logger::Get(LogLevel_INFO) << "Received Action message from server" << std::endl;

                std::unique_ptr<std::thread> actionThread =
                        std::unique_ptr<std::thread>(
                                new std::thread(Controller::action_event,&m_client,_world));
                m_thread_list.push_back(std::move(actionThread));
            } else
                throw std::string("Can't determine phase of turn message");

            Logger::Get(LogLevel_DEBUG) << "Current turn is " << m_world.currentTurn();
        }
        else if (dynamic_cast<ShutdownMessage*>(message.get())) {
            Logger::Get(LogLevel_INFO) << "Received shutdown message from server" << std::endl;
            break;
        }


        Logger::Get(LogLevel_TRACE) << "Sending end message with turn = " << m_world.currentTurn() << std::endl;
        m_event_queue.push(EndTurnMessage(m_world.currentTurn()));//TODO should we have this?
    }
    //TODO join the threads here
    Logger::Get(LogLevel_INFO) << "Closing the connection" << std::endl;
    m_event_queue.terminate();
    m_network.disconnect();

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

void Controller::pick_event(AI* client,World* tmp_world) {
    client->pick(tmp_world);
    delete tmp_world;
}

void Controller::move_event(AI* client,World* tmp_world) {
    client->move(tmp_world);
    delete tmp_world;
}

void Controller::action_event(AI* client,World* tmp_world) {
    client->action(tmp_world);
    delete tmp_world;
}

