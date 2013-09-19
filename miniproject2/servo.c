#include <p24FJ128GB206.h>
#include "config.h"
#include "common.h"
#include "ui.h"
#include "timer.h"
#include "pin.h"
#include "uart.h"
#include "oc.h"
#include <stdio.h>

uint8_t string[40];
int16_t val1;
int16_t val2; 

int16_t main(void) {
    init_clock();
    init_ui();
    init_timer();
	init_pin();
	init_uart();
	init_oc();

	oc_servo(&oc1, &D[2], &timer1, 20e-3, 7e-4, 2.3e-3, (uint16_t)(0.9*65536));
	oc_servo(&oc2, &D[3], &timer2, 20e-3, 7e-4, 2.3e-3, (uint16_t)(0.9*65536)); //try using the same timer

	printf("Hello World!\n");
	printf("Type something at the prompt.\n");

    while (1) {
    	uart_gets(&uart1, string, 40);
		printf("You wrote %s \n", string);
		sscanf(string, "%d %d", &val1, &val2);
		printf("val1 is %d\n", val1);
		printf("val2 is %d\n", val2);
		pin_write(&D[2], val1);
		pin_write(&D[3], val2);
    }
}

