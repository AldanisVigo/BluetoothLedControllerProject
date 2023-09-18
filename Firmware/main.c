
#define __AVR_ATmega328__
#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdio.h>
#include <avr/delay.h>
#include "lib/st7735.h"
#include "lib/uart.h"
#define RESPONSEBUFFER 50
#define START 30
#define END MAX_X - START

/***
 * Define the LCD Screen Connections to ATMEGA328P
 * CS -> RB2
 * BL -> RB1
 * DC -> RB0
 * RS -> RD7
 * SDA -> RB3
 * SCL -> RB5
*/
struct signal cs = { .ddr = &DDRB, .port = &PORTB, .pin = 2 };
// Back Light
struct signal bl = { .ddr = &DDRB, .port = &PORTB, .pin = 1 };
// Data / Command
struct signal dc = { .ddr = &DDRB, .port = &PORTB, .pin = 0 };
// Reset
struct signal rs = { .ddr = &DDRD, .port = &PORTD, .pin = 7 };
// LCD struct
struct st7735 lcd1 = { .cs = &cs, .bl = &bl, .dc = &dc, .rs = &rs };

// Variable for storing incoming UART data.
char uart_response[RESPONSEBUFFER];

/***
 * Initializes the ST7735 tft screen based on the above config,
 * draws the title of the project and a loading bar and any other optional graphics.
*/
void initializeLcdScreen(){
    ST7735_Init (&lcd1);
    ST7735_ClearScreen (&lcd1, BLACK);
    ST7735_SetPosition (START + 5, 10);      
    ST7735_DrawString (&lcd1, "Industrial RCU v1.0", WHITE, X2);
    for (uint8_t i = START; i < END; i++) {
        ST7735_DrawRectangle (&lcd1, START, i, 30, 40, RED);
    }
    ST7735_DrawCircle(&lcd1, 64, 80, 20);
}

int main(void){
    // Initialize the TFT LCD screen
    initializeLcdScreen();
    
    // while(1){
    //     _delay_ms(1000);
    //     ST7735_ClearScreen (&lcd1, BLACK);
    //     ST7735_SetPosition (START + 0, 10);
    //     ST7735_DrawString (&lcd1,"Hey bros", WHITE, X2);
    //     ST7735_SetPosition(START + 0, 30);
    //     ST7735_DrawString (&lcd1, "put down the keyboards", WHITE, X2);
    //     _delay_ms(4000);
    //     ST7735_ClearScreen (&lcd1, BLACK);
    //     ST7735_SetPosition (START + 0, 10);
    //     ST7735_DrawString (&lcd1,"The weekend is here", WHITE, X2);
    //     ST7735_SetPosition(START + 0, 30);
    //     ST7735_DrawString (&lcd1, "Time for hookers", WHITE, X2);
    //     _delay_ms(4000);
    // }
    // Initalize the UART interface
    // ubrr = (fosc/16BAUD) - 1 = (16000000 / 16 * 9600) - 1 = 104 - 1 = 103
    uart_init(9600); 
    stdout = &uart_tx;
    stdin  = &uart_rx;

    // Setup led pins as outputs
    DDRD |= (1 << 2);
    DDRD |= (1 << 3);

    // int i = 0;
    while (1) {
        // printf("AT+VERSION?");
        receiveWord(RESPONSEBUFFER, &uart_response);
        if(strlen(uart_response) > 0){
            ST7735_ClearScreen (&lcd1, BLACK);
            // i++; // Increment the counter
            // char numStr[7]; // String to store number as characters
            // itoa(i,numStr,10); // Convert count to a string
            ST7735_SetPosition (START + 0, 10); 
            ST7735_DrawString (&lcd1,uart_response, WHITE, X2);
            if(strcmp(uart_response,"LED0")){
                PORTD ^= (1 << 2);
            }else if(strcmp(uart_response,"LED1")){
                PORTD ^= (1 << 3);
            }

            _delay_ms(100);
            memset(uart_response,0,RESPONSEBUFFER);
        }else{
            ST7735_ClearScreen (&lcd1, BLACK);
            ST7735_SetPosition (START + 0, 10); 
            ST7735_DrawString (&lcd1,"Listening...", WHITE, X2);
            _delay_ms(100);
        }
        // printf("AT");
        // _delay_ms(100);
        //To write to UART use printf
	    // uart_putchar('A',&uart_tx);
        // printf("Hello booger bug!\n");
        // printf("Please enter your last name:");
        // receiveWord(RESPONSEBUFFER,&uart_response);
        // printf("\n\n\nYou responded:\n %s\n\n\n",uart_response);
    }

    return 0;               
}


