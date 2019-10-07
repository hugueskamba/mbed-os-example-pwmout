/* mbed Microcontroller Library
 * Copyright (c) 2018-2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>

#include "mbed.h"
#include "mbed_stats.h"
#include "drivers/InterruptIn.h"
#include "drivers/PwmOut.h"

InterruptIn button(PTC6);
PwmOut led(PTC11);


void flip_pwm_state()
{
    static bool pwm_state = false;
    led.enable_pwm(pwm_state);
    pwm_state = !pwm_state;
}

int main(void)
{
    // attach a handler to be executed on the button rising edge
    button.rise(&flip_pwm_state);

    // 4 second period
    led.period(4.0f);

    // 50% duty cycle, relative to period
    led.write(0.50f);

    while (1) {
        ThisThread::sleep_for(1000);

        mbed_stats_cpu_t stats;
        mbed_stats_cpu_get(&stats);
        printf("Uptime: %llu ", stats.uptime / 1000);
        printf("Sleep time: %llu ", stats.sleep_time / 1000);
        printf("Deep Sleep: %llu\n\r", stats.deep_sleep_time / 1000);
    }
}
