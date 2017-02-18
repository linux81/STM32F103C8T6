#include "stm32f10x.h" 
#include "system.h"
#include "delay.h"
void I2C3_init(void);
void I2C3_WriteChar (char Adr, char Dat);


int main (void){

SystemInit();
	

GPIOC->CRH=0x00;
GPIOC->CRH|=1<<20;
	I2C1_init();

	
	uint16_t i;
I2C3_WriteChar(0x00,0x00);
I2C3_WriteChar(0x01,0x00);

while(1){
	for(i=1;i<200;i++){
	
I2C3_WriteChar(0x12,i);
sprintf(buffer, "%u \n",i);
		LCD_string(0,0,buffer);
		USART_send(buffer);
Delay(500);
	}	


}


}


void I2C3_WriteChar (char Adr, char Dat)    { 
  I2C2->CR1         |= 0x0100;       // send START bit 
  while (!(I2C3->SR1 & 0x0001)) {};  // wait for START condition (SB=1)  
  I2C3->DR           = 0x40;         // slave address   -> DR & write 
  while (!(I2C3->SR1 & 0x0002)) {};  // wait for ADDRESS sent (ADDR=1)  
  int Status2        = I2C3->SR2;    // read status to clear flag 
  I2C3->DR           = Adr;          // Address in chip -> DR & write 
  while (!(I2C3->SR1 & 0x0080)) {};  // wait for DR empty (TxE) 
  I2C3->DR           = Dat;          // Dat -> DR & write 
  while (!(I2C3->SR1 & 0x0080)) {};  // wait for DR empty (TxE)  
  while (!(I2C3->SR1 & 0x0004)) {};  // wait for Byte sent (BTF) 
  I2C3->CR1         |= 0x0200;       // send STOP bit 
} 

void I2C3_init(void) {
	
	  ///* Initialize I2C1, SDA: PB7, SCL: PB6 */
RCC->APB2ENR |= RCC_APB2ENR_IOPBEN|RCC_APB2ENR_AFIOEN;
GPIOB->CRL=0x00;

	
  // initialize I2C block 
  RCC->APB1ENR  |= 1<<23;       // Enable clock for I2C3 
  I2C3->CR2     |= 0x0008;           // clock == 8MHz!    
  I2C3->CCR     |= 0x0040;           // clock control register (270kHz) 
  I2C3->TRISE   |= 0x0009;           // rise time register 
  I2C3->CR1     |= 0x0001;           // I2C3 enable 
	
};



