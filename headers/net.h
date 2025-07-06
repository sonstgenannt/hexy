#ifndef NETFUNK 
#define NETFUNK

#include <enet/enet.h>
#include <cstddef>

class server {
   private:
      size_t m_maxClients;
      size_t m_channels;
      
      enet_uint16 m_port;

      enet_uint32 m_inBandwidth;
      enet_uint32 m_outBandwidth;

      ENetHost* m_host;
   public:
      server();
      int initialize();
      int stop();
      int listen(int);
};

#endif
