#include <STC15Fxx.h>

#include <pinout.h>

#include <uart.h>

#define CMD_LED_ON 0x31
#define CMD_LED_OFF 0x32

BYTE b;
void main()
{
    TR0 = 1; // timer0 start running
    ET0 = 1; // enable timer0 interrupt
    PT0 = 1; // improve timer0 interrupt priority
    EA = 1;  // open global interrupt switch

    LED_BUILDIN = LED_BUILDIN_OFF;
    
    uart_init(BAUD_9600_110592);
    uart_send_string("VK STC15W204S BLINK_PIO V2.0\n");
    uart_send_string("Send 1 for led on\n");
    uart_send_string("Send 2 for led off\n");
    
    while (1)
    { // user's function
        b = uart_get_byte();
        if (b == CMD_LED_ON)
        {
            LED_BUILDIN = LED_BUILDIN_ON;
            uart_send_string("led on\n");
        }
        if (b == CMD_LED_OFF)
        {
            P33 = LED_BUILDIN_OFF;
            uart_send_string("led off\n");
        }

        uart_send_byte(b);
    }
}

INTERRUPT(tm0, 1)
{
    uart_handle();
}