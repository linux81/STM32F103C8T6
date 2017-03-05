#include "system.h"
uint32_t SystemCoreClock;   

//const uint8_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};

//#define HSI_VALUE    ((uint32_t)16000000)
//#define HSE_VALUE    ((uint32_t)8000000)



void SystemInit(void) {
RCC->CR |= RCC_CR_HSEON;
RCC->CFGR = RCC_CFGR_PLLMULL9 | RCC_CFGR_PLLSRC | RCC_CFGR_ADCPRE_DIV6 |
RCC_CFGR_PPRE1_DIV2 | RCC_CFGR_USBPRE;
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






