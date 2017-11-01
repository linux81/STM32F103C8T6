#include "system.h"
uint32_t SystemCoreClock;   





void SystemInit(void) {
RCC->CR |= RCC_CR_HSEON;
RCC->CFGR = RCC_CFGR_PLLMULL9 | RCC_CFGR_PLLSRC;
while (!(RCC->CR & RCC_CR_HSERDY));
RCC->CR |= RCC_CR_PLLON;
FLASH->ACR |= FLASH_ACR_LATENCY_1;
while (!(RCC->CR & RCC_CR_PLLRDY));
RCC->CFGR |= RCC_CFGR_SW_PLL;
while ( (RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
RCC->CR &= ~RCC_CR_HSION;


SysTick_Config(72000000/1000/8);
SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk;
	
}






