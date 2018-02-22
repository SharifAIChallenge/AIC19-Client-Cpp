#include "Controller.h"

#include <iostream>
#include <thread>
#include <chrono>

#include <Utility/Utility.h>
#include <Utility/Logger.h>

#include <Network/NetworkError.h>

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
    m_network.send(AuthenticationMessage(m_token).to_string());

    // Parse init message
    Logger::Get(LogLevel_TRACE) << "Waiting for init message" << std::endl;
    InitMessage init_message(m_network.receive());

    Logger::Get(LogLevel_TRACE) << "Parsing init message" << std::endl;

    init_message.parse_world_constants();
    init_message.parse_unit_constants();
    init_message.parse_tower_constants();

    m_world.set_my_information(Player(World::INITIAL_HEALTH, World::INITIAL_MONEY, 0, World::INITIAL_BEANS_COUNT,
                                      World::INITIAL_STORMS_COUNT));
    m_world.set_enemy_information(Player(World::INITIAL_HEALTH, 0, 0, World::INITIAL_BEANS_COUNT,
                                         World::INITIAL_STORMS_COUNT));

    const Map& map = init_message.parse_map();
    m_world.set_defence_map(map);
    m_world.set_attack_map(map);

    m_world.set_attack_map_paths(init_message.parse_paths(m_world.get_attack_map()));
    m_world.set_defence_map_paths(init_message.parse_paths(m_world.get_defence_map()));

    m_world.set_current_turn(0);

    // Start the event handling thread
    m_event_handling_thread = std::thread(&Controller::event_handling_loop, this);

    while (m_network.is_connected()) {
        Logger::Get(LogLevel_TRACE) << "Waiting for turn/shutdown message" << std::endl;

        auto message = Message::CreateFromJsonString(m_network.receive());
        if (dynamic_cast<ShutdownMessage*>(message.get())) {
            Logger::Get(LogLevel_INFO) << "Received shutdown message from server" << std::endl;
            break;
        }

        auto turn_message = std::unique_ptr<TurnMessage>(static_cast<TurnMessage*>(message.release()));

        Logger::Get(LogLevel_TRACE) << "Parsing turn message" << std::endl;

        m_world.set_dead_units_in_this_turn(turn_message->parse_dead_units(m_world));
        m_world.set_passed_units_in_this_turn(turn_message->parse_passed_units(m_world));
        m_world.set_destroyed_towers_in_this_turn(turn_message->parse_destroyed_towers(m_world));

        m_world.set_beans_in_this_turn(turn_message->parse_bean_events());
        m_world.set_storms_in_this_turn(turn_message->parse_storm_events());

        // Apply beans
        for (BeanEvent* bean : m_world.get_beans_in_this_turn()) {
            Map& map = (bean->get_owner() == Owner::ME ? m_world.get_attack_map() : m_world.get_defence_map());

            int x = bean->get_location().x();
            int y = bean->get_location().y();

            delete map.get_cells_grid()[x][y];
            map.get_cells_grid()[x][y] = new BlockCell(Point(x, y));
        }

        turn_message->parse_my_units(m_world.get_attack_map(), m_world.get_attack_map_paths());
        turn_message->parse_enemy_units(m_world.get_defence_map(), m_world.get_defence_map_paths());

        turn_message->parse_my_towers(m_world.get_defence_map());
        turn_message->parse_enemy_towers(m_world.get_attack_map());

        m_world.set_my_information(turn_message->parse_my_information());
        m_world.set_enemy_information(turn_message->parse_enemy_information());

        m_world.set_current_turn(m_world.get_current_turn() + 1);

        // Run the client AI

        Logger::Get(LogLevel_DEBUG) << "Current turn is " << m_world.get_current_turn() << std::endl;

        constexpr size_t COMPLEX_TURN_INTERVAL = 10;

        if (m_world.get_current_turn() % COMPLEX_TURN_INTERVAL == 0) {
            Logger::Get(LogLevel_DEBUG) << "Running complex turn" << std::endl;
            m_client.complex_turn(&m_world);
        } else {
            Logger::Get(LogLevel_DEBUG) << "Running simple turn" << std::endl;
            m_client.simple_turn(&m_world);
        }

        Logger::Get(LogLevel_TRACE) << "Sending end message with turn = " << m_world.get_current_turn() << std::endl;
        m_event_queue.push(EndTurnMessage(m_world.get_current_turn()));
    }

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