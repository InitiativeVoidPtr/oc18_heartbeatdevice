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
#include "CppUTest/TestHarness.h"
#include "test_m2mconnectionhandlerimpl_classic.h"
#include "m2mconnectionhandlerpimpl_stub.h"
#include "m2mconnectionobserver.h"

class M2MConnection_TestObserver : public M2MConnectionObserver {

public:
    M2MConnection_TestObserver(){}

    virtual ~M2MConnection_TestObserver(){}

    void set_class_object(M2MConnectionHandler *impl) {}
    void data_available(uint8_t*,
                        uint16_t,
                        const M2MConnectionObserver::SocketAddress &){
        dataAvailable = true;
    }

    void socket_error(uint8_t error_code, bool retry){error = true;}

    void address_ready(const M2MConnectionObserver::SocketAddress &,
                       M2MConnectionObserver::ServerType,
                       const uint16_t){addressReady = true;}

    void data_sent(){dataSent = true;}

    bool dataAvailable;
    bool error;
    bool addressReady;
    bool dataSent;
};

Test_M2MConnectionHandler_classic::Test_M2MConnectionHandler_classic()
{
    observer = new M2MConnection_TestObserver();
    handler = new M2MConnectionHandler(*observer, NULL ,M2MInterface::NOT_SET,M2MInterface::Uninitialized);
}

Test_M2MConnectionHandler_classic::~Test_M2MConnectionHandler_classic()
{
    delete handler;
    delete observer;
}

void Test_M2MConnectionHandler_classic::test_bind_connection()
{
    m2mconnectionhandlerpimpl_stub::bool_value = true;
    CHECK( handler->bind_connection(7) == true);
}

void Test_M2MConnectionHandler_classic::test_resolve_server_address()
{
    m2mconnectionhandlerpimpl_stub::bool_value = true;
    CHECK(handler->resolve_server_address("10", 7, M2MConnectionObserver::LWM2MServer, NULL) == true);

    CHECK(handler->resolve_server_address("10", 7, M2MConnectionObserver::LWM2MServer, NULL) == true);

    m2mconnectionhandlerpimpl_stub::bool_value = false;
    CHECK(handler->resolve_server_address("10", 7, M2MConnectionObserver::LWM2MServer, NULL) == false);
}

void Test_M2MConnectionHandler_classic::test_send_data()
{
    sn_nsdl_addr_s* addr = (sn_nsdl_addr_s*)malloc(sizeof(sn_nsdl_addr_s));

    memset(addr, 0, sizeof(sn_nsdl_addr_s));
    m2mconnectionhandlerpimpl_stub::bool_value = false;
    CHECK(false == handler->send_data(NULL, 0 , NULL));

    m2mconnectionhandlerpimpl_stub::bool_value = true;
    CHECK(true == handler->send_data(NULL, 0 , addr));

    m2mconnectionhandlerpimpl_stub::bool_value = false;
    CHECK(false == handler->send_data(NULL, 0 , addr));

    free(addr);
}

void Test_M2MConnectionHandler_classic::test_start_listening_for_data()
{
    handler->start_listening_for_data();
}



void Test_M2MConnectionHandler_classic::test_stop_listening()
{

    handler->stop_listening();

}

void Test_M2MConnectionHandler_classic::test_send_to_socket()
{
    const char buf[] = "hello";
    handler->send_to_socket((unsigned char *)&buf, 5);
}

void Test_M2MConnectionHandler_classic::test_receive_from_socket()
{
    unsigned char *buf = (unsigned char *)malloc(6);
    handler->receive_from_socket(buf, 5);
    free(buf);
}

void Test_M2MConnectionHandler_classic::test_handle_connection_error()
{
    // To manage code coverage
    handler->handle_connection_error(5);
}

void Test_M2MConnectionHandler_classic::test_set_platform_network_handler()
{
    // To manage code coverage
    handler->set_platform_network_handler(NULL);
}

void Test_M2MConnectionHandler_classic::test_claim_mutex()
{
    // To manage code coverage
    handler->claim_mutex();
}

void Test_M2MConnectionHandler_classic::test_release_mutex()
{
    // To manage code coverage
    handler->release_mutex();
}
