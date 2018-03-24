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

#ifndef PAL_NETWORK_STUB_H
#define PAL_NETWORK_STUB_H

#include "pal.h"
#include "pal_network.h"

namespace pal_network_stub
{
    extern palStatus_t status;
    extern palStatus_t new_status;
    extern uint32_t change_status_count; //status changed to new_status after this turns to 0

    extern palSocket_t socket;
    extern palSocketAddress_t socket_address;
    extern palIpV4Addr_t ipv4_address;
    extern palIpV6Addr_t ipv6_address;
    extern size_t size;
    extern uint32_t uint32_value;
    extern void *void_value;

}

#endif // PAL_NETWORK_STUB_H

