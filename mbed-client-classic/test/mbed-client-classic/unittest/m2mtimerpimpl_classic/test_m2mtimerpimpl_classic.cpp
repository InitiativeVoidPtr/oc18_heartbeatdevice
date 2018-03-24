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
#include "test_m2mtimerpimpl_classic.h"
#include "eventOS_event.h"
#include <unistd.h>

extern void expired(union sigval sigval);
class TestObserver : public M2MTimerObserver {

public:
    TestObserver(){}
    virtual ~TestObserver(){}
    void timer_expired(M2MTimerObserver::Type){
        visited = true;
    }
    bool visited;

};

Test_M2MTimerPimpl_classic::Test_M2MTimerPimpl_classic()
{
    observer = new TestObserver();
    timer = new M2MTimerPimpl(*observer);
}

Test_M2MTimerPimpl_classic::~Test_M2MTimerPimpl_classic()
{
    delete observer;
    delete timer;
}

void Test_M2MTimerPimpl_classic::test_start_timer()
{
    timer->start_timer(100,M2MTimerObserver::Notdefined,true);
    CHECK(!timer->_still_left);
    timer->start_timer(10000000000,M2MTimerObserver::Notdefined,true);
    CHECK(timer->_still_left);
}

void Test_M2MTimerPimpl_classic::test_stop_timer()
{
    //common_stub::int_value = 0;
    timer->start_timer(100,M2MTimerObserver::Notdefined,true);
    timer->stop_timer();
    timer->start_timer(100,M2MTimerObserver::Notdefined,false);
    timer->stop_timer();
    //CHECK(timer->_timer_specs.it_value.tv_sec == 0);
    //CHECK(timer->_timer_specs.it_value.tv_nsec == 0);
}

void Test_M2MTimerPimpl_classic::test_timer_expired()
{
    observer->visited = false;
    timer->timer_expired();
    CHECK(observer->visited == true);

    timer->_single_shot = false;
    timer->timer_expired();
    CHECK(observer->visited == true);
}

void Test_M2MTimerPimpl_classic::test_start_dtls_timer()
{
    timer->start_dtls_timer(10, 100, M2MTimerObserver::Dtls);
}

void Test_M2MTimerPimpl_classic::test_is_intermediate_interval_passed()
{
    timer->start_dtls_timer(2500, 10000, M2MTimerObserver::Dtls);
    CHECK(false == timer->is_intermediate_interval_passed());
    timer->timer_expired();
    CHECK(true == timer->is_intermediate_interval_passed());
}

void Test_M2MTimerPimpl_classic::test_is_total_interval_passed()
{
    timer->start_dtls_timer(250, 2000, M2MTimerObserver::Dtls);
    timer->timer_expired();
    CHECK(false == timer->is_total_interval_passed());
    timer->timer_expired();
    CHECK(true == timer->is_total_interval_passed());
}

extern "C" void tasklet_func(arm_event_s *event);

void Test_M2MTimerPimpl_classic::test_tasklet_func()
{
    arm_event_s event;

    event.event_type = 10;
    event.event_id = (-1);

    observer->visited = false;
    tasklet_func(&event);
    CHECK(!observer->visited);

    event.event_id = timer->get_timer_id();

    tasklet_func(&event);
    CHECK(observer->visited);

    observer->visited = false;
    timer->_still_left = 1;
    tasklet_func(&event);
    CHECK(!observer->visited);
}

void Test_M2MTimerPimpl_classic::test_start_still_left_timer()
{
    observer->visited = false;
    timer->_still_left = (uint64_t)INT32_MAX + 1;
    timer->start_still_left_timer();
    CHECK(!observer->visited);
    CHECK(timer->_still_left);

    timer->start_still_left_timer();
    CHECK(!observer->visited);
    CHECK(!timer->_still_left);

    timer->_still_left = 0;
    timer->_single_shot = false;
    timer->start_still_left_timer();
    CHECK(observer->visited);

}

