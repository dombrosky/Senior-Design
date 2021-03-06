/* 
 * File:   comm_uart.h
 * Author: Chris
 *
 * Contains user made functions used to send information over the MCU UART Module.
 */

#include "comm_uart.h"

void uart_send_string(char* msg) {
    for (int i = 0; i < strlen(msg); i++){
        while(U1FIFObits.TXBF == 1); //Wait until there is room in the buffer
        UART1_Write(msg[i]);
    }
    while(UART1_is_tx_done() == 0); //Wait until this transmission is finished
}