#include <p24FJ128GB206.h>
#include "config.h"
#include "common.h"
#include "timer.h"
#include "pin.h"
#include "oc.h"
#include "usb.h"
#include <stdio.h>

#define SET_VALS 0

void VendorRequests(void) {
    uint16_t pan = 0;
    uint16_t tilt = 0;

    switch (USB_setup.bRequest) {
        case SET_VALS:
            pan = USB_setup.wValue.w;
            tilt = USB_setup.wIndex.w;
            pin_write(&D[2], pan);
            pin_write(&D[3], tilt);
            BD[EP0IN].bytecount = 0;    // set EP0 IN byte count to 0
            BD[EP0IN].status = 0xC8;    // send packet as DATA1, set UOWN bit
            break;
        default:
            USB_error_flags |= 0x01;    // set Request Error Flag
    }
}

void VendorRequestsIn(void) {
    switch (USB_request.setup.bRequest) {
        default:
            USB_error_flags |= 0x01;                    // set Request Error Flag
    }
}

void VendorRequestsOut(void) {
    switch (USB_request.setup.bRequest) {
        default:
            USB_error_flags |= 0x01;                    // set Request Error Flag
    }
}

int16_t main(void) {
    init_clock();
    init_timer();
    init_pin();
    init_oc();

    oc_servo(&oc1, &D[2], &timer1, 20e-3, 7e-4, 2.3e-3, (uint16_t)(0.9*65536));
    oc_servo(&oc2, &D[3], &timer2, 20e-3, 7e-4, 2.3e-3, (uint16_t)(0.9*65536)); //try using the same timer

    InitUSB();                              // initialize the USB registers and serial interface engine
    while (USB_USWSTAT!=CONFIG_STATE) {     // while the peripheral is not configured...
        ServiceUSB();                       // ...service USB requests
    }
    while (1) {
        ServiceUSB();                       // service any pending USB requests
    }
}

