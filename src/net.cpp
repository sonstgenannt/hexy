#define ENET_IMPLEMENTATION
#include <../headers/net.h>
#include <enet/enet.h>
#include <cstdio>
#include <iostream>

server::server():
   m_maxClients(1),
   m_channels(2),
   m_port(7777),
   m_inBandwidth(0),
   m_outBandwidth(0)
{
}
int server::initialize()
{
    if (enet_initialize() != 0)
    {
        fprintf(stderr, "ENet failed to initialize.\n");
        return 1; // Return false on failure
    }

    ENetAddress address = {0};
    address.host = ENET_HOST_ANY;
    address.port = m_port;

    m_host = enet_host_create(
        &address,
        m_maxClients,
        m_channels,
        m_inBandwidth,
        m_outBandwidth
    );

    if (m_host == nullptr)
    {
        printf("Failed to create server host.\n");
        enet_deinitialize();
        return 1; // Return false on failure
    }

    char ip[64];
    enet_address_get_host_ip(&address, ip, sizeof(ip));
    printf("STARTED SERVER ON %s : %u\n", ip, address.port);
    return 0; // Return true on success
}
int server::stop()
{
    enet_host_destroy(m_host);
    enet_deinitialize();
    return 0;
}
int server::listen(int duration)
{
   ENetEvent event;
   while (enet_host_service(m_host, &event, duration) > 0) {
      switch (event.type) {
         case ENET_EVENT_TYPE_CONNECT:
            printf("A new client connected from %x:%u.\n",  event.peer->address.host, event.peer->address.port);
            // Store any relevant client information here. //
            //event.peer->data = "Client information";
            printf("%s disconnected.\n", static_cast<const char*>(event.peer->data));

            break;

         case ENET_EVENT_TYPE_RECEIVE:
            printf("A packet of length %lu containing %s was received from %s on channel %u.\n",
                  event.packet->dataLength,
                  event.packet->data,
                  event.peer->data,
                  event.channelID);
            // Clean up the packet now that we're done using it. //
            enet_packet_destroy (event.packet);
            break;

         case ENET_EVENT_TYPE_DISCONNECT:
            printf("%s disconnected.\n", event.peer->data);
            // Reset the peer's client information. //
            event.peer->data = NULL;
            break;

         case ENET_EVENT_TYPE_DISCONNECT_TIMEOUT:
            printf("%s disconnected due to timeout.\n", event.peer->data);
            // Reset the peer's client information. //
            event.peer->data = NULL;
            break;

         case ENET_EVENT_TYPE_NONE:
            break;
      }
   }

   return 0;
}
