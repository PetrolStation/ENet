#include "Server.h"
#include "enet/enet.h"
#include <cstring>
#include <iostream>

static void sendString(ENetPeer* peer, const char* str) {
	ENetPacket* packet = enet_packet_create(str, strlen(str) + 1, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
}

namespace PetrolEngine {
    Server::Server(int port){
        this->address.host = ENET_HOST_ANY;
        this->address.port = port;
    }

    int Server::init(){
        if(enet_initialize() != 0) return 1;

        server = enet_host_create(&address, 32, 2, 0, 0);
        
        if(server == nullptr) return 2;

        return 0;
    }

    void Server::broadcast(String msg){
        for(auto& client : clients) client.send(msg);

        enet_host_flush(server);
    }

    void Server::run(){
        ENetEvent event;

        bool done = false;
        while(!done){
            while(enet_host_service(server, &event, 1) > 0){
                switch (event.type) {
                    case ENET_EVENT_TYPE_CONNECT: {
                        Peer peer(event.peer);
                        onConnect(peer);
                        clients.emplace_back(event.peer);
                        break;
                    }
                    case ENET_EVENT_TYPE_RECEIVE: {
                        //fn(event.peer->address.host, event.peer->address.port, event.packet->data, event.packet->dataLength);
                        String s((char*)event.packet->data, event.packet->dataLength);
                        Peer peer(event.peer);

                        onRecive(peer, s);
                        //std::cout<<s<<std::endl;

                        enet_packet_destroy(event.packet);
                        
                        enet_host_flush(server);
                        //std::cout<<"yes?\n";
                        //enet_peer_disconnect(clients[0], 0);
                        break;
                    }
                    case ENET_EVENT_TYPE_DISCONNECT: {
                        Peer peer(event.peer);
                        onDisconnect(peer);
                        clients.erase(std::remove(clients.begin(), clients.end(), peer), clients.end());
                        std::cout<<"Client disconnected"<<std::endl;
                        done = true;
                        break;
                    }
                }
            }
        }
    }

    Server::~Server(){
        enet_host_destroy(server);
        enet_deinitialize();
    }
}
