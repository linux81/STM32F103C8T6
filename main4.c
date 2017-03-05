// I2C1 with expander MCP23017

#include "stm32f10x.h" 
#include "system.h"
#include "delay.h"
void I2C1_init(void);
void I2C1_WriteChar (char Adr, char Dat);
	uint16_t i;

int main (void){

SystemInit();
	

	I2C1_init();

	

I2C1_WriteChar(0x00,0x00);
I2C1_WriteChar(0x01,0x00);

while(1){
	for(i=1;i<200;i++){
	
I2C1_WriteChar(0x12,i);

Delay(500);
	}	


}


}


void I2C1_WriteChar (char Adr, char Dat)    {
  int Status2; 	
  I2C1->CR1         |= 0x0100;       // send START bit 
  while (!(I2C1->SR1 & 0x0001)) {};  // wait for START condition (SB=1)  
  I2C1->DR           = 0x40;         // slave address   -> DR & write 
  while (!(I2C1->SR1 & 0x0002)) {};  // wait for ADDRESS sent (ADDR=1)  
  Status2        = I2C1->SR2;    // read status to clear flag 
  I2C1->DR           = Adr;          // Address in chip -> DR & write 
  while (!(I2C1->SR1 & 0x0080)) {};  // wait for DR empty (TxE) 
  I2C1->DR           = Dat;          // Dat -> DR & write 
  while (!(I2C1->SR1 & 0x0080)) {};  // wait for DR empty (TxE)  
  while (!(I2C1->SR1 & 0x0004)) {};  // wait for Byte sent (BTF) 
  I2C1->CR1         |= 0x0200;       // send STOP bit 
} 

void I2C1_init(void) {
	
	  ///* Initialize I2C1, SDA: PB7, SCL: PB6 */
  
RCC->APB2ENR = RCC_APB2ENR_IOPBEN|RCC_APB2ENR_AFIOEN;  // Enable clock for GPIOB
GPIOB->CRL=0xDD444444;

	
  // initialize I2C block 
  RCC->APB1ENR  |= 1<<21;       // Enable clock for I2C3 
  I2C1->CR2     |= 0x0008;           // clock == 8MHz!    
  I2C1->CCR     |= 0x0040;           // clock control register (270kHz) 
  I2C1->TRISE   |= 0x0009;           // rise time register 
  I2C1->CR1     |= 0x0001;           // I2C1 enable 
	
};



