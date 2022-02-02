/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC18F16Q41
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include "comm_uart.h"
#include "sleep.h"
/*
                         Main application
 */
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    sleep_setup();
    IOCCF0_SetInterruptHandler(uart_btn_msg);
    INTERRUPT_GlobalInterruptEnable();
    
    //Startup procedure
    led_SetLow();
    __delay_ms(1500);
    uart_send_string("Device powered on");
    
    
    bool btn_pressed = false; //For button debounce
    while (1)
    {
        //Code for testing microcontroller
        if (sleep_sw_GetValue() == LOW) {
            //If sleep switch is on, flash led 5 times then enter sleep
            for (int i = 0; i < 5; i++){
                led_SetLow();
                __delay_ms(250);
                led_SetHigh();
                __delay_ms(250);
            }
            
            //Send dummy battery status
            uart_send_string("BAT??");
            
            sleep_enter();
        }
        else {
            //If sleep switch is off, turn on LED and send message when
            //the push button is pressed.
            if (btn_GetValue() == LOW && btn_pressed == false){
                //Only execute following code once per button press
                btn_pressed = true;
                uart_send_string("PSH");
                led_SetLow();
            }
            else if (btn_GetValue() == HIGH && btn_pressed == true){
                btn_pressed = false;
            }

            if (btn_pressed == false) led_SetHigh();
        }
    }
}
/**
 End of File
*/