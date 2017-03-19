/*
 *	Default pinout
 *	
 *	LCD		STM32F446/74HC595		DESCRIPTION
 *	
 *	GND		GND				Ground
 *	VCC		+5V				Power supply for LCD
 *	V0		Potentiometer	Contrast voltage. Connect to potentiometer
 *	RS		Q0				Register select, can be overwritten in your project’s defines.h file
 *	RW		GND				Read/write
 *	E		PB7				Enable pin, can be overwritten in your project’s defines.h file
 *	D0		-				Data 0 – doesn’t care
 *	D1		-				Data 1 - doesn’t care
 *	D2		-				Data 2 - doesn’t care
 *	D3		-				Data 3 - doesn’t  care
 *	D4		Q1			Data 4, can be overwritten in your project’s defines.h file
 *	D5		Q2			Data 5, can be overwritten in your project’s defines.h file
 *	D6		Q3			Data 6, can be overwritten in your project’s defines.h file
 *	D7		Q4			Data 7, can be overwritten in your project’s defines.h file
 *	A		+3V3			Backlight positive power
 *	K		GND				Ground for backlight

*/

#include "stm32f10x.h" 
#define HD44780_E_HIGH  GPIOB->BSRR |= 1<<7 //PB7
#define HD44780_E_LOW   GPIOB->BSRR |= 1<<23
#define HD44780_E_BLINK				HD44780_E_HIGH; Delay(1); HD44780_E_LOW; Delay(1); //bylo 2ms
#define clk GPIOB->BSRR |= 1<<22;Delay(1);GPIOB->BSRR |= 1<<6; //PB6
#include "LCD2x16_piotrek.h" 
#include "delay.h"


void send_data_4bit(uint8_t data, uint8_t RS){
	// DS PB5
	uint8_t i,a;
data=data<<1;

if(RS==1) data=data+1;



for(i=0;i<5;i++){

a=(data&0x10)>>4;
	
		if (a!= 0) {

		GPIOB->BSRR |= 1<<5;
}
else
{

GPIOB->BSRR |= 1<<21;
}
data=data<<1;
clk;
	
}
clk;
	
HD44780_E_BLINK;
	
};


void HD44780_Cmd(uint8_t cmd) {
	//HD44780_RS_LOW;
	
	send_data_4bit((cmd >> 4),0);			//High nibble
	send_data_4bit((cmd & 0x0F),0);			//Low nibble
};

void HD44780_Data(uint8_t data) {
	//HD44780_RS_HIGH;
	
	send_data_4bit((data >> 4),1);			//High nibble
	send_data_4bit((data & 0x0F),1);			//Low nibble
};

//--------------------------------------------------------------
// Ausgabe von einem String auf dem Display an x,y Position
// x : 0 bis 15
// y : 0 bis 1
//--------------------------------------------------------------
void HD44780_Cursor(uint8_t x, uint8_t y)
{
  uint8_t wert;

  if(x>=16) x=0;
  if(y>=2) y=0;

  wert=(y<<6);
  wert|=x;
  wert|=0x80;
  HD44780_Cmd(wert);
};

void LCD_string(uint8_t x, uint8_t y,char *str) {

    HD44780_Cursor(x,y); 
	
	while (*str != '\0') {                // send all characters in a string
    HD44780_Data (*str++);
  }
};







void LCD_init (void) {
RCC->APB2ENR = RCC_APB2ENR_IOPBEN;  // Enable clock for GPIOB
GPIOB->CRL=0x11144444;
	
	// PB5 DS, PB6 CLK, PB7 E
  
  
  HD44780_Cmd(0x03);        Delay(5);
  HD44780_Cmd(0x03);        Delay(5);
  HD44780_Cmd(0x03);        Delay(5);
  HD44780_Cmd(0x02);        Delay(5);
  HD44780_Cmd(0x28);
  HD44780_Cmd(0x0c);
  HD44780_Cmd(0x01);
  HD44780_Cmd(0x06);
  Delay(5);       
};


void LCD_clear (void){

HD44780_Cmd(0x01);
Delay(5);
};


void HD44780_ScrollLeft(void) {
	HD44780_Cmd(HD44780_CURSORSHIFT | HD44780_DISPLAYMOVE | HD44780_MOVELEFT);
};

void HD44780_ScrollRight(void) {
	HD44780_Cmd(HD44780_CURSORSHIFT | HD44780_DISPLAYMOVE | HD44780_MOVERIGHT);
};


