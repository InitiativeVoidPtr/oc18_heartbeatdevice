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

#include "eventOS_scheduler.h"
#include "eventOS_event.h"
#include "eventOS_stub.h"

int8_t eventOS_stub::int8_value;

void eventOS_scheduler_mutex_wait(void){}

void eventOS_scheduler_mutex_release(void){}

int8_t eventOS_event_handler_create(void (*handler_func_ptr)(arm_event_s *), uint8_t init_event_type)
{
    return eventOS_stub::int8_value;
}

int8_t eventOS_event_send(arm_event_s *event)
{
    if(event->data_ptr && !eventOS_stub::int8_value)
    {
        free(event->data_ptr);
    }
    return eventOS_stub::int8_value;
}

extern "C" int8_t eventOS_event_timer_request(uint8_t snmessage, uint8_t event_type, int8_t tasklet_id, uint32_t time)
{
    return eventOS_stub::int8_value;
}

extern "C" int8_t eventOS_event_timer_cancel(uint8_t snmessage, int8_t tasklet_id)
{
    return eventOS_stub::int8_value;
}