#include "Peer.h"

#include <enet/enet.h>
#include <cstring>

namespace PetrolEngine {
    void Peer::send(String& msg){
        const char* str = msg.c_str();

        ENetPacket* packet = enet_packet_create(str, strlen(str)+1, ENET_PACKET_FLAG_RELIABLE);
        enet_peer_send(this->peer, 0, packet);
    }
    
    
}
