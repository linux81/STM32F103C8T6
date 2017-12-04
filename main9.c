#include "stm32f10x.h" 
#include "system.h"
#include "delay.h"


void PCF8574_write (char Dat);

int main (void){

SystemInit();

RCC->APB2ENR |= RCC_APB2ENR_IOPBEN|RCC_APB2ENR_AFIOEN;
RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;



	
// PB10 I2C2 SCL, PB11 I2C2 SDA 
GPIOB->CRH=GPIO_CRH_MODE10|GPIO_CRH_CNF10|GPIO_CRH_MODE11|GPIO_CRH_CNF11;

  I2C2->CR2     |= 0x0008;           // clock == 8MHz!    
  I2C2->CCR     |= 0x0040;           // clock control register (270kHz) 
  I2C2->TRISE   |= 0x0009;           // rise time register 
  I2C2->CR1     |= 0x0001;           // I2C3 enable
	

	


	
while(1){

	
	int i;
	
for (i=0;i<255;i++){
PCF8574_write (i);
Delay(1);}

}


}





void PCF8574_write(char Dat)    {
  int Status2;
  I2C2->CR1         |= I2C_CR1_START;       // send START bit 
  while (!(I2C2->SR1 & I2C_SR1_SB)) {};  // wait for START condition (SB=1)  
  I2C2->DR           = 0x4e;         // slave address 
  while (!(I2C2->SR1 & I2C_SR1_ADDR)) {};  // wait for ADDRESS sent (ADDR=1) 
	
  Status2        = I2C2->SR2;    // read status to clear flag 
  I2C2->DR           = Dat;          // Dat -> DR & write 
  while (!(I2C2->SR1 & I2C_SR1_TXE)) {};  // wait for DR empty (TxE)  
  while (!(I2C2->SR1 & I2C_SR1_BTF)) {};  // wait for Byte sent (BTF) 
  I2C2->CR1         |= I2C_CR1_STOP;       // send STOP bit 
} 
