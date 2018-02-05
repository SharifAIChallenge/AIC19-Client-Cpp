#include "Controller.h"

#include <iostream>
#include <thread>
#include <chrono>

#include "../Network/NetworkError.h"
#include "Message/AuthenticationMessage.h"
#include "Message/InitMessage.h"
#include "Message/TurnMessage.h"
#include "ParseError.h"
#include "../Utility.h"

Controller::Controller(const std::string& host, uint16_t port, const std::string& token, unsigned retry_delay)
        : m_token(token)
        , m_retry_delay(retry_delay)
        , m_network(host, port)
        , m_world(m_event_queue)
{
    DEBUG("Server is " << host << ":" << port);
    DEBUG("Token is " << token);
    DEBUG("Retry delay is " << retry_delay);
}

Controller::~Controller() {
    if (m_event_handling_thread.joinable())
        m_event_handling_thread.join();
    if (m_network.is_connected())
        m_network.disconnect();
}

void Controller::run() {
    // Connect to the server

    constexpr size_t MAX_RETRY_COUNT = 3;
    for (size_t i = 1; i <= MAX_RETRY_COUNT && !m_network.is_connected(); ++i)
        try {
            std::cerr << "Trying to connect #" << i << std::endl;
            m_network.connect();
        }
        catch (NetworkError &e) {
            if (i == MAX_RETRY_COUNT)
                throw;
            else
                std::this_thread::sleep_for(std::chrono::milliseconds(m_retry_delay));
        }
    std::cerr << "Connected" << std::endl;

    DEBUG("Sending authentication message");
    m_network.send(AuthenticationMessage(m_token, "token").to_string());

    // Parse init message
    try {
        InitMessage init_message(m_network.receive());

        DEBUG("Parsing init message");

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
    }
    catch (Json::Exception& e) {
        std::cerr << "Parsing init message failed" << std::endl;
        throw;
    }

    // Start the event handling thread
    m_event_handling_thread = std::thread(&Controller::event_handling_loop, this);

    while (m_network.is_connected()) {
        try {
            DEBUG("Waiting for turn message");
            TurnMessage turn_message(m_network.receive());

            DEBUG("Parsing turn message");

            m_world.set_dead_units_in_this_turn(turn_message.parse_dead_units(m_world));
            m_world.set_passed_units_in_this_turn(turn_message.parse_passed_units(m_world));
            m_world.set_destroyed_towers_in_this_turn(turn_message.parse_destroyed_towers(m_world));

            m_world.set_beans_in_this_turn(turn_message.parse_bean_events());
            m_world.set_storms_in_this_turn(turn_message.parse_storm_events());

            turn_message.parse_my_units(m_world.get_attack_map(), m_world.get_attack_map_paths());
            turn_message.parse_enemy_units(m_world.get_defence_map(), m_world.get_defence_map_paths());

            turn_message.parse_my_towers(m_world.get_defence_map());
            turn_message.parse_enemy_towers(m_world.get_attack_map());

            m_world.set_my_information(turn_message.parse_my_information());
            m_world.set_enemy_information(turn_message.parse_enemy_information());

            m_world.set_current_turn(m_world.get_current_turn() + 1);

            // Run the client AI

            DEBUG("Current turn is " << m_world.get_current_turn());
            DEBUG("Running client ai");

            constexpr size_t COMPLEX_TURN_INTERVAL = 10;
            std::thread ai_thread(
                    m_world.get_current_turn() % COMPLEX_TURN_INTERVAL == 0 ? &AI::complex_turn : &AI::simple_turn,
                    m_client, &m_world);
            ai_thread.detach();
        }
        catch (Json::Exception& e) {
            std::cerr << "Warning: Received malformed json string" << std::endl;
        }
        catch (NetworkEOFError& e) {
            std::cerr << "Received EOF from server" << std::endl;
            break;
        }
        catch (ParseError& e) {
            std::cerr << "Received shutdown message from server" << std::endl;
            break;
        }
    }

    std::cerr << "Closing the connection" << std::endl;
    m_event_queue.terminate();
    m_network.disconnect();
}

void Controller::event_handling_loop() noexcept {
    while (m_network.is_connected()) {
        auto message = m_event_queue.pop();
        if (!message)
            break;
        m_network.send(message->to_string());
    }
}