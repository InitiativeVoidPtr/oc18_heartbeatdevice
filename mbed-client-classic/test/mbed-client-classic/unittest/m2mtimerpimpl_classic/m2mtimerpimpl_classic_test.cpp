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
#include "test_m2mtimerpimpl_classic.h"

TEST_GROUP(M2MTimerPimpl_classic)
{
  Test_M2MTimerPimpl_classic* m2m_timer;

  void setup()
  {
      m2m_timer = new Test_M2MTimerPimpl_classic();
  }
  void teardown()
  {
      delete m2m_timer;
  }
};

TEST(M2MTimerPimpl_classic, Create)
{
    CHECK(m2m_timer != NULL);
}

TEST(M2MTimerPimpl_classic, start_timer)
{
    m2m_timer->test_start_timer();
}

TEST(M2MTimerPimpl_classic, stop_timer)
{
    m2m_timer->test_stop_timer();
}

TEST(M2MTimerPimpl_classic, timer_expired)
{
    m2m_timer->test_timer_expired();
}

TEST(M2MTimerPimpl_classic, test_start_dtls_timer)
{
    m2m_timer->test_start_dtls_timer();
}

TEST(M2MTimerPimpl_classic, test_is_intermediate_interval_passed)
{
    m2m_timer->test_is_intermediate_interval_passed();
}

TEST(M2MTimerPimpl_classic, test_is_total_interval_passed)
{
    m2m_timer->test_is_total_interval_passed();
}

TEST(M2MTimerPimpl_classic, tasklet_func)
{
    m2m_timer->test_tasklet_func();
}

TEST(M2MTimerPimpl_classic, start_still_left_timer)
{
    m2m_timer->test_start_still_left_timer();
}


