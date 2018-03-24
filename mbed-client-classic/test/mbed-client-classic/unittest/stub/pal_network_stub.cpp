/*
 * Copyright (c) 2016 ARM Limited. All rights reserved.
 * SPDX-License-Identifier: Apache-2.0
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <string.h>
#include "pal_network_stub.h"

palStatus_t pal_network_stub::status;
palStatus_t pal_network_stub::new_status;
uint32_t pal_network_stub::change_status_count;

palSocket_t pal_network_stub::socket;
palSocketAddress_t pal_network_stub::socket_address;
palIpV4Addr_t pal_network_stub::ipv4_address;
palIpV6Addr_t pal_network_stub::ipv6_address;
size_t pal_network_stub::size;
uint32_t pal_network_stub::uint32_value;
void *pal_network_stub::void_value;

static palStatus_t get_pal_status(void)
{
    palStatus_t status_to_return;

    status_to_return = pal_network_stub::status;

    if(pal_network_stub::change_status_count){

        pal_network_stub::change_status_count--;

        if(!pal_network_stub::change_status_count){
            pal_network_stub::status = pal_network_stub::new_status;
        }
    }

    return status_to_return;

}

palStatus_t pal_registerNetworkInterface(void* networkInterfaceContext, uint32_t* interfaceIndex)
{
    *interfaceIndex = pal_network_stub::uint32_value;
    return get_pal_status();
}

palStatus_t pal_setSockAddrPort(palSocketAddress_t* address, uint16_t port)
{
    return get_pal_status();
}

palStatus_t pal_setSockAddrIPV4Addr(palSocketAddress_t* address, palIpV4Addr_t ipV4Addr)
{
    return get_pal_status();
}

palStatus_t pal_setSockAddrIPV6Addr(palSocketAddress_t* address, palIpV6Addr_t ipV6Addr)
{
    return get_pal_status();
}

palStatus_t pal_getSockAddrIPV4Addr(const palSocketAddress_t* address, palIpV4Addr_t ipV4Addr)
{
    memcpy(ipV4Addr, pal_network_stub::ipv4_address, sizeof(pal_network_stub::ipv4_address));
    return get_pal_status();
}

palStatus_t pal_getSockAddrIPV6Addr(const palSocketAddress_t* address, palIpV6Addr_t ipV6Addr)
{
    memcpy(ipV6Addr, pal_network_stub::ipv6_address, sizeof(pal_network_stub::ipv6_address));
    return get_pal_status();
}

palStatus_t pal_getSockAddrPort(const palSocketAddress_t* address, uint16_t* port)
{
    return get_pal_status();
}

palStatus_t pal_socket(palSocketDomain_t domain, palSocketType_t type, bool nonBlockingSocket, uint32_t interfaceNum, palSocket_t* socket)
{
    memcpy(socket, pal_network_stub::socket, sizeof(pal_network_stub::socket));
    return get_pal_status();
}

palStatus_t pal_getSocketOptions(palSocket_t socket, palSocketOptionName_t optionName, void* optionValue, palSocketLength_t* optionLength)
{
    return get_pal_status();
}

palStatus_t pal_setSocketOptions(palSocket_t socket, int optionName, const void* optionValue, palSocketLength_t optionLength)
{
    return get_pal_status();
}

palStatus_t pal_bind(palSocket_t socket, palSocketAddress_t* myAddress, palSocketLength_t addressLength)
{
    return get_pal_status();
}

palStatus_t pal_receiveFrom(palSocket_t socket, void* buffer, size_t length, palSocketAddress_t* from, palSocketLength_t* fromLength, size_t* bytesReceived)
{
    if(pal_network_stub::void_value){
    	memcpy(buffer, pal_network_stub::void_value, pal_network_stub::size);
    }
    *bytesReceived = pal_network_stub::size;
    return get_pal_status();
}

palStatus_t pal_sendTo(palSocket_t socket, const void* buffer, size_t length, const palSocketAddress_t* to, palSocketLength_t toLength, size_t* bytesSent)
{
    *bytesSent = pal_network_stub::size;
    return get_pal_status();
}

palStatus_t pal_close(palSocket_t* socket)
{
    return get_pal_status();
}

palStatus_t pal_getNumberOfNetInterfaces(uint32_t* numInterfaces)
{
    *numInterfaces = pal_network_stub::uint32_value;
    return get_pal_status();
}

palStatus_t pal_getNetInterfaceInfo(uint32_t interfaceNum, palNetInterfaceInfo_t* interfaceInfo)
{
    return get_pal_status();
}

palStatus_t pal_socketMiniSelect(const palSocket_t socketsToCheck[PAL_NET_SOCKET_SELECT_MAX_SOCKETS], uint32_t numberOfSockets, pal_timeVal_t* timeout,
								uint8_t palSocketStatus[PAL_NET_SOCKET_SELECT_MAX_SOCKETS], uint32_t* numberOfSocketsSet)
{
    return get_pal_status();
}

palStatus_t pal_listen(palSocket_t socket, int backlog)
{
    return get_pal_status();
}

palStatus_t pal_accept(palSocket_t socket, palSocketAddress_t* address, palSocketLength_t* addressLen, palSocket_t* acceptedSocket)
{
    return get_pal_status();
}

palStatus_t pal_connect(palSocket_t socket, const palSocketAddress_t* address, palSocketLength_t addressLen)
{
    return get_pal_status();
}

palStatus_t pal_recv(palSocket_t socket, void* buf, size_t len, size_t* recievedDataSize)
{
    if(pal_network_stub::void_value){
    	memcpy(buf, pal_network_stub::void_value, pal_network_stub::size);
    }
    *recievedDataSize = pal_network_stub::size;
    return get_pal_status();
}

palStatus_t pal_send(palSocket_t socket, const void* buf, size_t len, size_t* sentDataSize)
{
    *sentDataSize = pal_network_stub::size;
    return get_pal_status();
}

palStatus_t pal_asynchronousSocket(palSocketDomain_t domain, palSocketType_t type, bool nonBlockingSocket, uint32_t interfaceNum, palAsyncSocketCallback_t callback, palSocket_t* socket)
{
    //memcpy(socket, pal_network_stub::socket, sizeof(pal_network_stub::socket));
    callback();
    return get_pal_status();
}

palStatus_t pal_getAddressInfo(const char* url, palSocketAddress_t* address, palSocketLength_t* addressLength)
{
    memcpy(address, &pal_network_stub::socket_address, sizeof(pal_network_stub::socket_address));
    *addressLength = sizeof(pal_network_stub::socket_address);
    return get_pal_status();
}
