#include <rex/net/socket.h>
#include <rex/platform.h>

#include "platform_win.h"

#include <WinSock2.h>

namespace rex::net {

int socket_close(SocketHandle handle) {
  return closesocket(static_cast<SOCKET>(handle));
}

int socket_ioctl(SocketHandle handle, uint32_t cmd, uint8_t* arg) {
  return ioctlsocket(static_cast<SOCKET>(handle), cmd, reinterpret_cast<u_long*>(arg));
}

}
