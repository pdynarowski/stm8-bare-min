#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stm8s.h>
#include <delay.h>
#include <uart.h>
#include <i2c.h>
#include "PCF8563.h"

int putchar(int c) {
    uart_write(c);
    return 0;
}

void main() {
    uart_init();
    i2c_init();

    Time time;
    time.Second = bin2bcd(10);
    time.Minute = bin2bcd(50);
    time.Hour = bin2bcd(21);

    PCF8563_SetTime(&time);

    while(1) {
        delay_ms(1000);
        PCF8563_GetTime(&time);
        uint8_t hours = bcd2bin(time.Hour & 0b111111);
        uint8_t minutes = bcd2bin(time.Minute & 0b1111111);
        uint8_t seconds = bcd2bin(time.Second & 0b1111111);
        printf("%0.2i:%0.2i:%0.2i\n\r", hours, minutes, seconds);
    }
}
