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
#ifndef TEST_M2M_CONNECTION_HANDLER_PIMPL_CLASSIC_H
#define TEST_M2M_CONNECTION_HANDLER_PIMPL_CLASSIC_H

#include "mbed-client-classic/m2mconnectionhandlerpimpl.h"

class M2MConnection_TestObserver;

class Test_M2MConnectionHandlerPimpl_classic
{
public:
    Test_M2MConnectionHandlerPimpl_classic();

    virtual ~Test_M2MConnectionHandlerPimpl_classic();

    void test_bind_connection();

    void test_resolve_server_address();
  
    void test_dns_handler();

    void test_send_data();

    void test_send_socket_data();

    void test_start_listening_for_data();

    void test_data_receive();

    void test_receive_from_socket();

    void test_stop_listening();

    void test_send_to_socket();

    void test_receive_handler();

    void test_handle_connection_error();

    void test_connection_event_handler();

    void test_set_platform_network_handler();

    void test_receive_handshake_handler();

    void test_claim_mutex();

    void test_release_mutex();

    M2MConnectionHandlerPimpl* handler;
    M2MConnection_TestObserver *observer;

    M2MConnectionHandlerPimpl *udp4_unsec;
    M2MConnectionHandlerPimpl *udp4_sec;
    M2MConnectionHandlerPimpl *tcp4_unsec;
    M2MConnectionHandlerPimpl *tcp4_sec;
    M2MConnectionHandlerPimpl *udp6_unsec;
    M2MConnectionHandlerPimpl *udp6_sec;
    M2MConnectionHandlerPimpl *tcp6_unsec;
    M2MConnectionHandlerPimpl *tcp6_sec;
    M2MSecurity* sec;

};

#endif // TEST_M2M_CONNECTION_HANDLER_PIMPL_CLASSIC_H
