#include <Core/Aliases.h>
#include <enet/enet.h>

namespace PetrolEngine {
    class Peer {
    public:
        ENetPeer* peer = nullptr;
        Peer() = default;
        Peer(ENetPeer* peer): peer(peer) {}
        void send(String& msg);
        bool operator==(Peer a){ return this->peer == a.peer; }
    };
}
