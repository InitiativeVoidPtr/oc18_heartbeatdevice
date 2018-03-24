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
//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"
#include "test_m2mconnectionhandlerpimpl_classic.h"

TEST_GROUP(M2MConnectionHandlerPimpl_classic)
{
  Test_M2MConnectionHandlerPimpl_classic* handler;

  void setup()
  {
    handler = new Test_M2MConnectionHandlerPimpl_classic();
  }
  void teardown()
  {
    delete handler;
  }
};


TEST(M2MConnectionHandlerPimpl_classic, create)
{
    CHECK(handler != NULL);
}

TEST(M2MConnectionHandlerPimpl_classic, test_bind_connection)
{
    handler->test_bind_connection();
}

TEST(M2MConnectionHandlerPimpl_classic, test_resolve_server_address)
{
    handler->test_resolve_server_address();
}

TEST(M2MConnectionHandlerPimpl_classic, test_dns_handler)
{
    handler->test_dns_handler();
}

TEST(M2MConnectionHandlerPimpl_classic, test_start_listening_for_data)
{
    handler->test_start_listening_for_data();
}

TEST(M2MConnectionHandlerPimpl_classic, test_receive_handler)
{
    handler->test_receive_handler();
}

TEST(M2MConnectionHandlerPimpl_classic, test_send_data)
{
    handler->test_send_data();
}

TEST(M2MConnectionHandlerPimpl_classic, test_send_socket_data)
{
    handler->test_send_socket_data();
}

TEST(M2MConnectionHandlerPimpl_classic, test_stop_listening)
{
    handler->test_stop_listening();
}

TEST(M2MConnectionHandlerPimpl_classic, test_send_to_socket)
{
    handler->test_send_to_socket();
}

TEST(M2MConnectionHandlerPimpl_classic, test_receive_from_socket)
{
    handler->test_receive_from_socket();
}

TEST(M2MConnectionHandlerPimpl_classic, test_handle_connection_error)
{
    handler->test_handle_connection_error();
}

TEST(M2MConnectionHandlerPimpl_classic, test_connection_event_handler)
{
    handler->test_connection_event_handler();
}

TEST(M2MConnectionHandlerPimpl_classic, test_set_platform_network_handler)
{
    handler->test_set_platform_network_handler();
}

TEST(M2MConnectionHandlerPimpl_classic, test_receive_handshake_handler)
{
    handler->test_receive_handshake_handler();
}

TEST(M2MConnectionHandlerPimpl_classic, test_claim_mutex)
{
    handler->test_claim_mutex();
}

TEST(M2MConnectionHandlerPimpl_classic, test_release_mutex)
{
    handler->test_release_mutex();
}
