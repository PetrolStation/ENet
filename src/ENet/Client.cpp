#include "Client.h"
#include "enet/enet.h"
#include <iostream>
#include <cstring>
#include <chrono>
#include <thread>
#include <PCH.h>

namespace PetrolEngine {
    Client::Client(const char* ip, int port){
        this->ip = ip;
        this->port = port;

        //init();
    }

    int Client::init(){
        if(enet_initialize() != 0) return 1;

        client = enet_host_create(nullptr, 1, 2, 0, 0);
        
        if(client == nullptr){
            LOG("could not create client!", 3);
            return 2;
        }

        enet_address_set_host(&address, ip);
        address.port = port;

        LOG("Client connecting to server...", 3);
        server = enet_host_connect(client, &address, 2, 0);

        if(server == nullptr){
            LOG("could not connect to server!", 3);
            return 3;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(2000));

        update();
        update();
        update();

        return 0;
    }

    void Client::update(){
        ENetEvent event;
        
        while (enet_host_service(client, &event, 1) > 0) {
            switch (event.type) {
                case ENET_EVENT_TYPE_CONNECT: { onConnect(); break; }
                case ENET_EVENT_TYPE_RECEIVE: {
                    String s((char*)event.packet->data, event.packet->dataLength);
                    onRecive(s);
                    enet_packet_destroy(event.packet);
                    break;
                }
                case ENET_EVENT_TYPE_DISCONNECT: { onDisconnect(); return; }
                default: break;
            }
        }
    }

    void Client::send(String& msg){
        const char* str = msg.c_str();

        ENetPacket* packet = enet_packet_create(str, strlen(str) + 1, ENET_PACKET_FLAG_RELIABLE);
        enet_peer_send(server, 0, packet);
    }

    void Client::flush(){
        enet_host_flush(client);
    }

    Client::~Client(){
        enet_peer_reset(server);
        enet_host_destroy(client);
        enet_deinitialize();
    }
}
