#pragma once

#include <Core/Aliases.h>
#include <enet/enet.h>
#include <Core/EventStack.h>

namespace PetrolEngine{
    class Client {
    public:
        const char* ip;
        int port;

        Client(const char* ip, int port);
        int init();
        virtual void onConnect() {};
        virtual void onDisconnect() {};
        virtual void onRecive(String& msg) = 0;
        void updateNetwork();
        void send(String& msg);
        void flush();
        
        ~Client();
    private:
        ENetAddress address;
        ENetHost* client;
        ENetPeer* server;
        bool active = true;
    };
}
