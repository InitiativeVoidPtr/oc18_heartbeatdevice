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
#include "test_m2mconnectionhandlerpimpl_classic.h"
#include "mbed-client-classic/m2mconnectionhandlerpimpl.h"
#include "mbed-client/m2mconnectionhandler.h"
#include "m2mconnectionobserver.h"
#include "m2msecurity.h"
#include "m2mconnectionsecurity_stub.h"
#include "m2msecurity_stub.h"
#include "eventOS_stub.h"
#include "pal_network_stub.h"
#include "eventOS_event.h"
#include "nsdlaccesshelper_stub.h"
#include "m2mstringbufferbase_stub.h"
#include <limits.h>

class M2MConnection_TestObserver : public M2MConnectionObserver {

public:
    M2MConnection_TestObserver():
    obj(NULL){}

    virtual ~M2MConnection_TestObserver(){}

    void set_class_object(M2MConnectionHandlerPimpl *impl) {obj = impl;}
    void data_available(uint8_t*,
                        uint16_t,
                        const M2MConnectionObserver::SocketAddress &){
        dataAvailable = true;
        if(obj) {
            //obj->_receive_data = false;
        }

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
    M2MSecurity* sec;

    M2MConnectionHandlerPimpl *obj;

};

Test_M2MConnectionHandlerPimpl_classic::Test_M2MConnectionHandlerPimpl_classic()
{
    observer = new M2MConnection_TestObserver();
    m2mconnectionsecurityimpl_stub::clear();
    pal_network_stub::void_value = NULL;
    pal_network_stub::change_status_count = 0;

    handler = new M2MConnectionHandlerPimpl(NULL, *observer, NULL , M2MInterface::NOT_SET, M2MInterface::Uninitialized);

    sec = new M2MSecurity(M2MSecurity::M2MServer);
    M2MConnectionSecurity* sec1 = new M2MConnectionSecurity(M2MConnectionSecurity::TLS);
    M2MConnectionSecurity* sec2 = new M2MConnectionSecurity(M2MConnectionSecurity::TLS);
    M2MConnectionSecurity* sec3 = new M2MConnectionSecurity(M2MConnectionSecurity::TLS);
    M2MConnectionSecurity* sec4 = new M2MConnectionSecurity(M2MConnectionSecurity::TLS);

    udp4_unsec = new M2MConnectionHandlerPimpl(NULL, *observer, NULL , M2MInterface::UDP, M2MInterface::LwIP_IPv4);
    udp4_sec = new M2MConnectionHandlerPimpl(NULL, *observer, sec1 , M2MInterface::UDP, M2MInterface::LwIP_IPv4);
    tcp4_unsec = new M2MConnectionHandlerPimpl(NULL, *observer, NULL , M2MInterface::TCP, M2MInterface::LwIP_IPv4);
    tcp4_sec = new M2MConnectionHandlerPimpl(NULL, *observer, sec2 , M2MInterface::TCP, M2MInterface::LwIP_IPv4);
    udp6_unsec = new M2MConnectionHandlerPimpl(NULL, *observer, NULL , M2MInterface::UDP, M2MInterface::LwIP_IPv6);
    udp6_sec = new M2MConnectionHandlerPimpl(NULL, *observer, sec3 , M2MInterface::UDP, M2MInterface::LwIP_IPv6);
    tcp6_unsec = new M2MConnectionHandlerPimpl(NULL, *observer, NULL , M2MInterface::TCP, M2MInterface::LwIP_IPv6);
    tcp6_sec = new M2MConnectionHandlerPimpl(NULL, *observer, sec4 , M2MInterface::TCP, M2MInterface::LwIP_IPv6);

}

Test_M2MConnectionHandlerPimpl_classic::~Test_M2MConnectionHandlerPimpl_classic()
{
    delete handler;
    delete observer;
    delete udp4_unsec;
    delete tcp4_unsec;
    delete udp6_unsec;
    delete tcp6_unsec;
    delete udp4_sec;
    delete tcp4_sec;
    delete udp6_sec;
    delete tcp6_sec;
    delete sec;
}

void Test_M2MConnectionHandlerPimpl_classic::test_bind_connection()
{
    CHECK( handler->bind_connection(7) == true);
}

void Test_M2MConnectionHandlerPimpl_classic::test_resolve_server_address()
{

    eventOS_stub::int8_value = 1;
    CHECK(handler->resolve_server_address("1", 12345, M2MConnectionObserver::LWM2MServer, NULL) == false);
    eventOS_stub::int8_value = 0;
    CHECK(handler->resolve_server_address("1", 12345, M2MConnectionObserver::LWM2MServer, NULL) == true);

}

void Test_M2MConnectionHandlerPimpl_classic::test_dns_handler()
{

    pal_network_stub::status = PAL_SUCCESS;
    observer->addressReady = false;
    pal_network_stub::uint32_value = 1;

    udp4_unsec->resolve_server_address("1", 12345, M2MConnectionObserver::LWM2MServer, NULL);
    udp4_unsec->dns_handler();
    CHECK(observer->addressReady == true);

    observer->addressReady = false;
    udp6_unsec->resolve_server_address("1", 12345, M2MConnectionObserver::LWM2MServer, NULL);
    udp6_unsec->dns_handler();
    CHECK(observer->addressReady == true);

    observer->addressReady = false;
    tcp4_unsec->resolve_server_address("1", 12345, M2MConnectionObserver::LWM2MServer, NULL);
    tcp4_unsec->dns_handler();
    CHECK(observer->addressReady == true);

    observer->addressReady = false;
    tcp6_unsec->resolve_server_address("1", 12345, M2MConnectionObserver::LWM2MServer, NULL);
    tcp6_unsec->dns_handler();
    CHECK(observer->addressReady == true);

    observer->addressReady = false;
    m2msecurity_stub::int_value = M2MSecurity::Psk;
    m2mconnectionsecurityimpl_stub::use_inc_int = true;
    m2mconnectionsecurityimpl_stub::inc_int_value = 0;
    udp4_sec->resolve_server_address("1", 12345, M2MConnectionObserver::LWM2MServer, sec);
    udp4_sec->dns_handler();
    CHECK(observer->addressReady == false);
    CHECK(udp4_sec->is_handshake_ongoing());

    /* error cases */

    observer->addressReady = false;
    observer->error = false;
    m2msecurity_stub::int_value = M2MSecurity::Psk;
    m2mconnectionsecurityimpl_stub::use_inc_int = false;
    m2mconnectionsecurityimpl_stub::int_value = 0;
    m2mconnectionsecurityimpl_stub::int_value2 = -123;
    udp4_sec->resolve_server_address("1", 12345, M2MConnectionObserver::LWM2MServer, sec);
    udp4_sec->dns_handler();
    CHECK(observer->error);
    CHECK(observer->addressReady == false);
    CHECK(!udp4_sec->is_handshake_ongoing());

    M2MConnectionSecurity *connection_security;

    observer->error = false;
    observer->addressReady = false;
    m2msecurity_stub::int_value = M2MSecurity::Psk;
    connection_security = udp4_sec->_security_impl;
    udp4_sec->_security_impl = NULL;
    udp4_sec->resolve_server_address("1", 12345, M2MConnectionObserver::LWM2MServer, sec);
    udp4_sec->dns_handler();
    CHECK(observer->addressReady == false);
    CHECK(observer->error);
    udp4_sec->_security_impl = connection_security;

    observer->error = false;
    observer->addressReady = false;
    m2msecurity_stub::int_value = M2MSecurity::Psk;
    m2mconnectionsecurityimpl_stub::use_inc_int = false;
    m2mconnectionsecurityimpl_stub::int_value = 1;
    udp4_sec->resolve_server_address("1", 12345, M2MConnectionObserver::LWM2MServer, sec);
    udp4_sec->dns_handler();
    CHECK(observer->addressReady == false);
    CHECK(observer->error);

    pal_network_stub::uint32_value = 1;

    udp4_unsec->_network_stack = (M2MInterface::NetworkStack)123;
    udp4_unsec->resolve_server_address("1", 12345, M2MConnectionObserver::LWM2MServer, NULL);
    udp4_unsec->dns_handler();
    CHECK(observer->addressReady == false);
    udp4_unsec->_network_stack = M2MInterface::LwIP_IPv4;

    observer->error = false;
    pal_network_stub::status = PAL_SUCCESS;
    pal_network_stub::new_status = PAL_ERR_GENERIC_FAILURE;
    pal_network_stub::change_status_count = 1;
    udp4_unsec->resolve_server_address("1", 12345, M2MConnectionObserver::LWM2MServer, NULL);
    udp4_unsec->dns_handler();
    CHECK(observer->addressReady == false);
    CHECK(observer->error);

    observer->error = false;
    pal_network_stub::status = PAL_SUCCESS;
    pal_network_stub::new_status = PAL_ERR_GENERIC_FAILURE;
    pal_network_stub::change_status_count = 2;
    udp4_unsec->resolve_server_address("1", 12345, M2MConnectionObserver::LWM2MServer, NULL);
    udp4_unsec->dns_handler();
    CHECK(observer->addressReady == false);
    CHECK(observer->error);

    observer->error = false;
    pal_network_stub::status = PAL_SUCCESS;
    pal_network_stub::new_status = PAL_ERR_GENERIC_FAILURE;
    pal_network_stub::change_status_count = 3;
    udp4_unsec->resolve_server_address("1", 12345, M2MConnectionObserver::LWM2MServer, NULL);
    udp4_unsec->dns_handler();
    CHECK(observer->addressReady == false);
    CHECK(observer->error);

    observer->error = false;
    pal_network_stub::status = PAL_SUCCESS;
    pal_network_stub::new_status = PAL_ERR_GENERIC_FAILURE;
    pal_network_stub::change_status_count = 4;
    udp4_unsec->resolve_server_address("1", 12345, M2MConnectionObserver::LWM2MServer, NULL);
    udp4_unsec->dns_handler();
    CHECK(observer->addressReady == false);
    CHECK(observer->error);

    observer->error = false;
    pal_network_stub::status = PAL_SUCCESS;
    pal_network_stub::new_status = PAL_ERR_GENERIC_FAILURE;
    pal_network_stub::change_status_count = 3;
    tcp6_unsec->resolve_server_address("1", 12345, M2MConnectionObserver::LWM2MServer, NULL);
    tcp6_unsec->dns_handler();
    CHECK(observer->addressReady == false);
    CHECK(observer->error);

    observer->error = false;
    pal_network_stub::status = PAL_SUCCESS;
    pal_network_stub::new_status = PAL_ERR_GENERIC_FAILURE;
    pal_network_stub::change_status_count = 8;
    tcp6_unsec->resolve_server_address("1", 12345, M2MConnectionObserver::LWM2MServer, NULL);
    tcp6_unsec->dns_handler();
    CHECK(observer->addressReady == false);
    CHECK(observer->error);

    pal_network_stub::change_status_count = 0;

}

void Test_M2MConnectionHandlerPimpl_classic::test_send_data()
{
    sn_nsdl_addr_s* addr = (sn_nsdl_addr_s*)malloc(sizeof(sn_nsdl_addr_s));
    memset(addr, 0, sizeof(sn_nsdl_addr_s));
    uint8_t* data = (uint8_t*)malloc(5);

    eventOS_stub::int8_value = 0;
    CHECK(false == handler->send_data(data, 5 , NULL));

    CHECK(false == handler->send_data(data, 0 , addr));

    CHECK(false == handler->send_data(NULL, 5 , addr));

    handler->_running = false;
    CHECK(false == handler->send_data(data, 5 , addr));
    handler->_running = true;

    CHECK(true == handler->send_data(data, 5 , addr));

    eventOS_stub::int8_value = 1;
    CHECK(false == handler->send_data(data, 5 , addr));

    free(data);
    free(addr);
}

void Test_M2MConnectionHandlerPimpl_classic::test_send_socket_data()
{

    uint8_t data[5] = {1};

    pal_network_stub::status = PAL_SUCCESS;

    udp4_unsec->_running = true;
    tcp4_unsec->_running = true;
    udp4_sec->_running = true;
    tcp4_sec->_running = true;

    observer->dataSent = false;
    udp4_unsec->send_socket_data(data, sizeof(data));
    CHECK(observer->dataSent);

    observer->dataSent = false;
    tcp4_unsec->send_socket_data(data, sizeof(data));
    CHECK(observer->dataSent);


    m2mconnectionsecurityimpl_stub::use_inc_int = false;
    m2mconnectionsecurityimpl_stub::int_value = 5;

    observer->dataSent = false;
    tcp4_sec->_use_secure_connection = true;
    tcp4_sec->send_socket_data(data, sizeof(data));
    CHECK(observer->dataSent);

    pal_network_stub::status = PAL_ERR_GENERIC_FAILURE;

    observer->dataSent = false;
    udp4_unsec->send_socket_data(data, sizeof(data));
    CHECK(!observer->dataSent);

    observer->dataSent = false;
    tcp4_unsec->send_socket_data(data, sizeof(data));
    CHECK(!observer->dataSent);

    pal_network_stub::status = PAL_SUCCESS;

    observer->dataSent = false;
    tcp4_unsec->send_socket_data(NULL, sizeof(data));
    CHECK(!observer->dataSent);

    observer->dataSent = false;
    tcp4_unsec->send_socket_data(data, 0);
    CHECK(!observer->dataSent);

    udp4_unsec->_running = false;
    observer->dataSent = false;
    udp4_unsec->send_socket_data(data, sizeof(data));
    CHECK(!observer->dataSent);
    udp4_unsec->_running = true;

}

void Test_M2MConnectionHandlerPimpl_classic::test_start_listening_for_data()
{
    handler->start_listening_for_data();
}

void Test_M2MConnectionHandlerPimpl_classic::test_receive_handler()
{

    uint8_t data[5] = {0,0,0,1,123};
    pal_network_stub::size = 5;

    udp4_unsec->_running = true;
    tcp4_unsec->_running = true;
    udp4_sec->_running = true;
    tcp4_sec->_running = true;

    udp4_unsec->start_listening_for_data();
    tcp4_unsec->start_listening_for_data();

    pal_network_stub::status = PAL_SUCCESS;
    pal_network_stub::new_status = PAL_ERR_SOCKET_WOULD_BLOCK;
    pal_network_stub::change_status_count = 1;
    observer->dataAvailable = false;
    udp4_unsec->receive_handler();
    CHECK(observer->dataAvailable);

    pal_network_stub::status = PAL_SUCCESS;
    pal_network_stub::new_status = PAL_ERR_SOCKET_WOULD_BLOCK;
    pal_network_stub::change_status_count = 1;
    observer->dataAvailable = false;
    pal_network_stub::void_value = data;
    tcp4_unsec->receive_handler();
    CHECK(observer->dataAvailable);

    pal_network_stub::status = PAL_ERR_GENERIC_FAILURE;
    observer->dataAvailable = false;
    observer->error = 0;
    udp4_unsec->receive_handler();
    CHECK(!observer->dataAvailable);
    CHECK(observer->error);

    pal_network_stub::status = PAL_ERR_SOCKET_WOULD_BLOCK;
    observer->dataAvailable = false;
    observer->error = 0;
    udp4_unsec->receive_handler();
    CHECK(!observer->dataAvailable);
    CHECK(!observer->error);

    pal_network_stub::status = PAL_SUCCESS;
    pal_network_stub::new_status = PAL_ERR_SOCKET_WOULD_BLOCK;
    pal_network_stub::change_status_count = 1;
    observer->error = 0;
    pal_network_stub::size = 3;
    observer->dataAvailable = false;
    pal_network_stub::void_value = data;
    tcp4_unsec->receive_handler();
    CHECK(!observer->dataAvailable);
    CHECK(observer->error);

    pal_network_stub::status = PAL_SUCCESS;
    pal_network_stub::new_status = PAL_ERR_SOCKET_WOULD_BLOCK;
    pal_network_stub::change_status_count = 1;
    observer->dataAvailable = false;
    data[3] = 2;
    tcp4_unsec->receive_handler();
    CHECK(!observer->dataAvailable);

    udp4_sec->_use_secure_connection = true;
    observer->error = 0;
    observer->dataAvailable = false;
    m2mconnectionsecurityimpl_stub::use_inc_int = false;
    m2mconnectionsecurityimpl_stub::int_value = M2MConnectionHandler::CONNECTION_ERROR_WANTS_READ;
    udp4_sec->receive_handler();
    CHECK(!observer->dataAvailable);
    CHECK(!observer->error);

    udp4_sec->_use_secure_connection = true;
    observer->error = 0;
    observer->dataAvailable = false;
    m2mconnectionsecurityimpl_stub::use_inc_int = false;
    m2mconnectionsecurityimpl_stub::int_value = (-123);
    udp4_sec->receive_handler();
    CHECK(!observer->dataAvailable);
    CHECK(observer->error);

    udp4_sec->_is_handshaking = true;
    observer->error = 0;
    observer->dataAvailable = false;
    m2mconnectionsecurityimpl_stub::use_inc_int = false;
    m2mconnectionsecurityimpl_stub::int_value = M2MConnectionHandler::CONNECTION_ERROR_WANTS_READ;
    udp4_sec->receive_handler();
    CHECK(!observer->dataAvailable);
    CHECK(!observer->error);

    udp4_sec->_is_handshaking = false;
    udp4_sec->_running = true;
    observer->error = 0;
    observer->dataAvailable = false;
    m2mconnectionsecurityimpl_stub::use_inc_int = true;
    m2mconnectionsecurityimpl_stub::inc_int_value = INT_MAX;
    udp4_sec->receive_handler();
    CHECK(observer->dataAvailable);
    CHECK(observer->error);

    udp4_sec->_is_handshaking = false;
    udp4_sec->_listening = false;
    observer->error = 0;
    observer->dataAvailable = false;
    m2mconnectionsecurityimpl_stub::use_inc_int = false;
    m2mconnectionsecurityimpl_stub::int_value = M2MConnectionHandler::CONNECTION_ERROR_WANTS_READ;
    udp4_sec->receive_handler();
    CHECK(!observer->dataAvailable);
    CHECK(!observer->error);
    udp4_sec->_listening = true;

    udp4_sec->_is_handshaking = false;
    udp4_sec->_running = false;
    observer->error = 0;
    observer->dataAvailable = false;
    m2mconnectionsecurityimpl_stub::use_inc_int = false;
    m2mconnectionsecurityimpl_stub::int_value = M2MConnectionHandler::CONNECTION_ERROR_WANTS_READ;
    udp4_sec->receive_handler();
    CHECK(!observer->dataAvailable);
    CHECK(!observer->error);
    udp4_sec->_running = true;

}


void Test_M2MConnectionHandlerPimpl_classic::test_stop_listening()
{
    handler->stop_listening();
}

void Test_M2MConnectionHandlerPimpl_classic::test_send_to_socket()
{
    const char buf[] = "hello";
    handler->send_to_socket((unsigned char *)&buf, 5);

    pal_network_stub::status = PAL_SUCCESS;
    pal_network_stub::size = 5;

    udp4_unsec->_running = true;
    tcp4_unsec->_running = true;

    CHECK(udp4_unsec->send_to_socket((unsigned char *)&buf, 5) == 5);

    CHECK(tcp4_unsec->send_to_socket((unsigned char *)&buf, 5) == 5);

    udp4_unsec->_running = false;
    CHECK(udp4_unsec->send_to_socket((unsigned char *)&buf, 5) < 0);
    udp4_unsec->_running = true;

    pal_network_stub::status = PAL_ERR_GENERIC_FAILURE;

    CHECK(udp4_unsec->send_to_socket((unsigned char *)&buf, 5) < 0);

    CHECK(tcp4_unsec->send_to_socket((unsigned char *)&buf, 5) < 0);

}

void Test_M2MConnectionHandlerPimpl_classic::test_receive_from_socket()
{
    unsigned char *buf = (unsigned char *)malloc(6);

    pal_network_stub::status = PAL_SUCCESS;
    pal_network_stub::size = 5;

    udp4_unsec->_running = true;
    tcp4_unsec->_running = true;

    CHECK(udp4_unsec->receive_from_socket(buf, 5) == 5);

    CHECK(tcp4_unsec->receive_from_socket(buf, 5) == 5);

    udp4_unsec->_running = false;
    CHECK(udp4_unsec->receive_from_socket(buf, 5) < 0);
    udp4_unsec->_running = true;

    pal_network_stub::status = PAL_ERR_GENERIC_FAILURE;

    CHECK(udp4_unsec->receive_from_socket(buf, 5) < 0);

    CHECK(tcp4_unsec->receive_from_socket(buf, 5) < 0);

    pal_network_stub::status = PAL_ERR_SOCKET_WOULD_BLOCK;

    CHECK(udp4_unsec->receive_from_socket(buf, 5) == M2MConnectionHandler::CONNECTION_ERROR_WANTS_READ);

    CHECK(tcp4_unsec->receive_from_socket(buf, 5) == M2MConnectionHandler::CONNECTION_ERROR_WANTS_READ);

    free(buf);
}

void Test_M2MConnectionHandlerPimpl_classic::test_handle_connection_error()
{
    handler->handle_connection_error(4);
    CHECK(observer->error == true);
}

extern "C" void connection_event_handler(arm_event_s *event);

void Test_M2MConnectionHandlerPimpl_classic::test_connection_event_handler()
{
    arm_event_s event;

    event.data_ptr = malloc(1);
    event.event_data = 1;

    event.event_type = M2MConnectionHandlerPimpl::ESocketReadytoRead;
    connection_event_handler(&event);

    event.event_type = M2MConnectionHandlerPimpl::ESocketDnsHandler;
    connection_event_handler(&event);

    event.event_type = M2MConnectionHandlerPimpl::ESocketSend;
    connection_event_handler(&event);

    event.event_type = 1234;
    connection_event_handler(&event);

}

void Test_M2MConnectionHandlerPimpl_classic::test_set_platform_network_handler()
{
    pal_network_stub::status = PAL_SUCCESS;
    handler->set_platform_network_handler((void*)1);

    pal_network_stub::status = PAL_ERR_GENERIC_FAILURE;
    handler->set_platform_network_handler((void*)1);
}

void Test_M2MConnectionHandlerPimpl_classic::test_receive_handshake_handler()
{

    udp4_sec->_is_handshaking = true;
    observer->error = 0;
    observer->addressReady = 0;
    m2mconnectionsecurityimpl_stub::use_inc_int = false;
    m2mconnectionsecurityimpl_stub::int_value = M2MConnectionHandler::CONNECTION_ERROR_WANTS_READ;
    udp4_sec->receive_handshake_handler();
    CHECK(!observer->error);
    CHECK(!observer->addressReady);

    udp4_sec->_is_handshaking = true;
    observer->error = 0;
    observer->addressReady = 0;
    m2mconnectionsecurityimpl_stub::use_inc_int = false;
    m2mconnectionsecurityimpl_stub::int_value = 0;
    udp4_sec->receive_handshake_handler();
    CHECK(!observer->error);
    CHECK(observer->addressReady);

    udp4_sec->_is_handshaking = true;
    observer->error = 0;
    observer->addressReady = 0;
    m2mconnectionsecurityimpl_stub::use_inc_int = false;
    m2mconnectionsecurityimpl_stub::int_value = (-123);
    udp4_sec->receive_handshake_handler();
    CHECK(observer->error);
    CHECK(!observer->addressReady);

}

void Test_M2MConnectionHandlerPimpl_classic::test_claim_mutex()
{

    handler->claim_mutex();

}

void Test_M2MConnectionHandlerPimpl_classic::test_release_mutex()
{

    handler->release_mutex();

}


