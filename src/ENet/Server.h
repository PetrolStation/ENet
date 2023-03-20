#pragma once

#include "Peer.h"

#include <Core/Aliases.h>
#include <enet/enet.h>
#include <string>

namespace PetrolEngine {
    class Server{
    public:
        Vector<Peer> clients;
        ENetAddress address;
        ENetHost* server;

        virtual void onConnect   (Peer& client) { };
        virtual void onDisconnect(Peer& client) { };
        virtual void onRecive    (Peer& client, String& msg) = 0;
        void run();
        void broadcast(String msg);
        int init();

        Server(int port);
        ~Server();
    };
}
