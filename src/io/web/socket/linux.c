// Copyright (c) 2022 Levi Marvin
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "linux.h"

/**
 * Create and listen a socket.
 * @param address The IPv4 address of socket
 * @param port The port of socket
 * @result return socket descriptor if success
 *      return -1 if socket error
 *      return -2 if binding error
 */
int startup_socket(const char *address, int port)
{
    // Create a new tcp sock
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in socket_prop;
    memset(&socket_prop, 0, sizeof(socket_prop));
    socket_prop.sin_family = AF_INET;
    socket_prop.sin_addr.s_addr = inet_addr(address);
    socket_prop.sin_port = htons(port);
    // Binding properties to the sock
    if (!bind(sock, (struct sockaddr *) &socket_prop, sizeof(socket_prop)))
    {
        // Return -2 for binding error.
        return -2;
    }
    // Start listening of the sock
    listen(sock, 20);

    return sock;
}

/**
 * Send byte data to the socket.
 * @param sock The socket descriptor
 * @param data The byte data
 * @return return 0 if success
 *      return -1 if send error
 */
int send_socket(int sock, byte *data)
{
    byte buf[SOCKET_BUFFER_SIZE];
    for (int i = 0; i < sizeof buf; ++i) {
        buf[i] = 0x00;
    }
    memcpy(buf, data, sizeof buf);
    return send(sock, buf, sizeof buf, MSG_DONTWAIT);
}

/**
 * Recieve byte data from the socket.
 * @param sock The socket descriptor
 * @param data The byte data
 * @return return 0 if success
 *      return -1 if read error
 */
int receive_socket(int sock, byte *data)
{
    byte buf[SOCKET_BUFFER_SIZE];
    for (int i = 0; i < sizeof buf; ++i) {
        buf[i] = 0x00;
    }
    if (!read(sock, buf, sizeof buf)) {
        return -1;
    }
    memcpy(data, buf, sizeof buf);

    return 0;
}

int close_socket()
{}