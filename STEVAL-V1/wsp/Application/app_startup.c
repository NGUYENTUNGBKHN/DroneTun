/**
 * @file       app_startup.c
 * @brief      
 * @date       2026/05/24
 * @author     [Gentantun] (nguyenthanhtung8196@gmail.com)
 * @details    
 * @ref        
 * @copyright  Copyright (c) 2026 RoboTun
*/
/*******************************************************************************
**                                INCLUDES
*******************************************************************************/
#include <stdint.h>
#include "system_stm32f4xx.h"
#include "stm32f4xx.h"
/*******************************************************************************
**                       INTERNAL MACRO DEFINITIONS
*******************************************************************************/


/*******************************************************************************
**                      COMMON VARIABLE DEFINITIONS
*******************************************************************************/


/*******************************************************************************
**                      INTERNAL VARIABLE DEFINITIONS
*******************************************************************************/


/*******************************************************************************
**                      INTERNAL FUNCTION PROTOTYPES
*******************************************************************************/

extern uint32_t _estack;
extern uint32_t _sidata;

extern uint32_t _sdata;
extern uint32_t _edata;

extern uint32_t _sbss;
extern uint32_t _ebss;
/*******************************************************************************
**                          FUNCTION DEFINITIONS
*******************************************************************************/
extern int app_main();

void Reset_Handler()
{
    volatile uint32_t *start = &_sdata;
    volatile uint32_t *end = &_edata;
    volatile uint32_t *data = &_sidata;
    volatile uint32_t *bss_start = &_sbss;
    volatile uint32_t *bss_end = &_ebss;
    SystemInit();

    while (start < end)
    {
        /* code */
        *start++ = *data++;
    }
   
    /* setup bss data = 0 */
    while (bss_start < bss_end)
    {
        /* code */
        *bss_start++ = 0;
    }

    app_main();
}

void default_handler(void)
{
    while (1)
    {
        /* code */
    }
    
}

void NMI_IRQHandler(void) __attribute((weak, alias("default_handler")));
void HardFault_IRQHandler(void) __attribute((weak, alias("default_handler")));
void MemManage_IRQHandler(void) __attribute((weak, alias("default_handler")));
void BusFault_IRQHandler(void) __attribute((weak, alias("default_handler")));
void UsageFault_IRQHandler(void) __attribute((weak, alias("default_handler")));
void SVC_IRQHandler(void) __attribute((weak, alias("default_handler")));
void DebugMonitor_IRQHandler(void) __attribute((weak, alias("default_handler")));
void PendSV_IRQHandler(void) __attribute((weak, alias("default_handler")));
void SysTick_IRQHandler(void) __attribute((weak, alias("default_handler")));
void WWDG_IRQHandler(void) __attribute((weak, alias("default_handler")));
void PVD_IRQHandler(void) __attribute((weak, alias("default_handler")));
void TAMP_STTAMP_IRQHandler(void) __attribute((weak, alias("default_handler")));
void RTC_WKUP_IRQHandler(void) __attribute((weak, alias("default_handler")));
void FLASH_IRQHandler(void) __attribute((weak, alias("default_handler")));
void RCC_IRQHandler(void) __attribute((weak, alias("default_handler")));
void EXTI0_IRQHandler(void) __attribute((weak, alias("default_handler")));
void EXTI1_IRQHandler(void) __attribute((weak, alias("default_handler")));
void EXTI2_IRQHandler(void) __attribute((weak, alias("default_handler")));
void EXTI3_IRQHandler(void) __attribute((weak, alias("default_handler")));
void EXTI4_IRQHandler(void) __attribute((weak, alias("default_handler")));
void DMA1_Stream0_IRQHandler(void) __attribute((weak, alias("default_handler")));
void DMA1_Stream1_IRQHandler(void) __attribute((weak, alias("default_handler")));
void DMA1_Stream2_IRQHandler(void) __attribute((weak, alias("default_handler")));
void DMA1_Stream3_IRQHandler(void) __attribute((weak, alias("default_handler")));
void DMA1_Stream4_IRQHandler(void) __attribute((weak, alias("default_handler")));
void DMA1_Stream5_IRQHandler(void) __attribute((weak, alias("default_handler")));
void DMA1_Stream6_IRQHandler(void) __attribute((weak, alias("default_handler")));
void ADC_IRQHandler(void) __attribute((weak, alias("default_handler")));

void EXTI9_5_IRQHandler(void) __attribute((weak, alias("default_handler")));
void TIM1_BRK_TIM9_IRQHandler(void) __attribute((weak, alias("default_handler")));
void TIM1_UP_TIM10_IRQHandler(void) __attribute((weak, alias("default_handler")));
void TIM1_TRG_COM_TIM11_IRQHandler(void) __attribute((weak, alias("default_handler")));
void TIM1_CC_IRQHandler(void) __attribute((weak, alias("default_handler")));
void TIM2_IRQHandler(void) __attribute((weak, alias("default_handler")));
void TIM3_IRQHandler(void) __attribute((weak, alias("default_handler")));
void TIM4_IRQHandler(void) __attribute((weak, alias("default_handler")));
void I2C1_EV_IRQHandler(void) __attribute((weak, alias("default_handler")));
void I2C1_ER_IRQHandler(void) __attribute((weak, alias("default_handler")));
void I2C2_EV_IRQHandler(void) __attribute((weak, alias("default_handler")));
void I2C2_ER_IRQHandler(void) __attribute((weak, alias("default_handler")));
void SPI1_IRQHandler(void) __attribute((weak, alias("default_handler")));
void SPI2_IRQHandler(void) __attribute((weak, alias("default_handler")));
void USART1_IRQHandler(void) __attribute((weak, alias("default_handler")));
void USART2_IRQHandler(void) __attribute((weak, alias("default_handler")));

void EXTI15_10_IRQHandler(void) __attribute((weak, alias("default_handler")));
void RTC_ALARM_IRQHandler(void) __attribute((weak, alias("default_handler")));
void OTG_FS_WKUP_IRQHandler(void) __attribute((weak, alias("default_handler")));

void DMA1_Stream7_IRQHandler(void) __attribute((weak, alias("default_handler")));

void SDIO_IRQHandler(void) __attribute((weak, alias("default_handler")));
void TIM5_IRQHandler(void) __attribute((weak, alias("default_handler")));
void SPI3_IRQHandler(void) __attribute((weak, alias("default_handler")));
void DMA2_Stream0_IRQHandler(void) __attribute((weak, alias("default_handler")));
void DMA2_Stream1_IRQHandler(void) __attribute((weak, alias("default_handler")));
void DMA2_Stream2_IRQHandler(void) __attribute((weak, alias("default_handler")));
void DMA2_Stream3_IRQHandler(void) __attribute((weak, alias("default_handler")));
void DMA2_Stream4_IRQHandler(void) __attribute((weak, alias("default_handler")));
void OTG_FS_IRQHandler(void) __attribute((weak, alias("default_handler")));
void DMA2_Stream5_IRQHandler(void) __attribute((weak, alias("default_handler")));
void DMA2_Stream6_IRQHandler(void) __attribute((weak, alias("default_handler")));
void DMA2_Stream7_IRQHandler(void) __attribute((weak, alias("default_handler")));
void USART6_IRQHandler(void) __attribute((weak, alias("default_handler")));
void I2C3_EV_IRQHandler(void) __attribute((weak, alias("default_handler")));
void I2C3_ER_IRQHandler(void) __attribute((weak, alias("default_handler")));
void FPU_IRQHandler(void) __attribute((weak, alias("default_handler")));
void SPI4_IRQHandler(void) __attribute((weak, alias("default_handler")));


__attribute__((section(".isr_vector")))
uint32_t *_isr_vector[] = {
    (uint32_t*) &_estack,                               /* top stack pointer */
    (uint32_t*) Reset_Handler,                          /* Reset handler  */
    (uint32_t*) NMI_IRQHandler,                         /* NHI handler */
    (uint32_t*) HardFault_IRQHandler,                   /* HardFault Handler */
    (uint32_t*) MemManage_IRQHandler,                   /* Memory Manager Handler */
    (uint32_t*) BusFault_IRQHandler,                    /* Bus Fault Handler */
    (uint32_t*) UsageFault_IRQHandler,                  /* Usage Fault Handler */
    0,
    0,
    0,
    0,
    (uint32_t*) SVC_IRQHandler,                         /* SVC Handler */
    (uint32_t*) DebugMonitor_IRQHandler,                /* Debug Monitor Handler */
    (uint32_t*) 0,                                      
    (uint32_t*) PendSV_IRQHandler,                      /* PendSV Handler */
    (uint32_t*) SysTick_IRQHandler,                     /* Systick Handler */
    (uint32_t*) WWDG_IRQHandler,
    (uint32_t*) PVD_IRQHandler,
    (uint32_t*) TAMP_STTAMP_IRQHandler,
    (uint32_t*) RTC_WKUP_IRQHandler,
    (uint32_t*) FLASH_IRQHandler,
    (uint32_t*) RCC_IRQHandler,
    (uint32_t*) EXTI0_IRQHandler,
    (uint32_t*) EXTI1_IRQHandler,
    (uint32_t*) EXTI2_IRQHandler,
    (uint32_t*) EXTI3_IRQHandler,
    (uint32_t*) EXTI4_IRQHandler,
    (uint32_t*) DMA1_Stream0_IRQHandler,
    (uint32_t*) DMA1_Stream1_IRQHandler,
    (uint32_t*) DMA1_Stream2_IRQHandler,
    (uint32_t*) DMA1_Stream3_IRQHandler,
    (uint32_t*) DMA1_Stream4_IRQHandler,
    (uint32_t*) DMA1_Stream5_IRQHandler,
    (uint32_t*) DMA1_Stream6_IRQHandler,
    (uint32_t*) ADC_IRQHandler,
    (uint32_t*) 0,
    (uint32_t*) 0,
    (uint32_t*) 0,
    (uint32_t*) 0,
    (uint32_t*) EXTI9_5_IRQHandler,
    (uint32_t*) TIM1_BRK_TIM9_IRQHandler,
    (uint32_t*) TIM1_UP_TIM10_IRQHandler,
    (uint32_t*) TIM1_TRG_COM_TIM11_IRQHandler,
    (uint32_t*) TIM1_CC_IRQHandler,
    (uint32_t*) TIM2_IRQHandler,
    (uint32_t*) TIM3_IRQHandler,
    (uint32_t*) TIM4_IRQHandler,
    (uint32_t*) I2C1_EV_IRQHandler,
    (uint32_t*) I2C1_ER_IRQHandler,
    (uint32_t*) I2C2_EV_IRQHandler,
    (uint32_t*) I2C2_ER_IRQHandler,
    (uint32_t*) SPI1_IRQHandler,
    (uint32_t*) SPI2_IRQHandler,
    (uint32_t*) USART1_IRQHandler,
    (uint32_t*) USART2_IRQHandler,
    (uint32_t*) 0,
    (uint32_t*) EXTI15_10_IRQHandler,
    (uint32_t*) RTC_ALARM_IRQHandler,
    (uint32_t*) OTG_FS_WKUP_IRQHandler,
    (uint32_t*) 0,
    (uint32_t*) 0,
    (uint32_t*) 0,
    (uint32_t*) 0,
    (uint32_t*) DMA1_Stream7_IRQHandler,
    (uint32_t*) 0,
    (uint32_t*) SDIO_IRQHandler,
    (uint32_t*) TIM5_IRQHandler,
    (uint32_t*) SPI3_IRQHandler,
    (uint32_t*) 0,
    (uint32_t*) 0,
    (uint32_t*) 0,
    (uint32_t*) 0,
    (uint32_t*) DMA2_Stream0_IRQHandler,
    (uint32_t*) DMA2_Stream1_IRQHandler,
    (uint32_t*) DMA2_Stream2_IRQHandler,
    (uint32_t*) DMA2_Stream3_IRQHandler,
    (uint32_t*) DMA2_Stream4_IRQHandler,
    (uint32_t*) 0,
    (uint32_t*) 0,
    (uint32_t*) 0,
    (uint32_t*) 0,
    (uint32_t*) 0,
    (uint32_t*) 0,
    (uint32_t*) OTG_FS_IRQHandler,
    (uint32_t*) DMA2_Stream5_IRQHandler,
    (uint32_t*) DMA2_Stream6_IRQHandler,
    (uint32_t*) DMA2_Stream7_IRQHandler,
    (uint32_t*) USART6_IRQHandler,
    (uint32_t*) I2C3_EV_IRQHandler,
    (uint32_t*) I2C3_ER_IRQHandler,
    (uint32_t*) 0,
    (uint32_t*) 0,
    (uint32_t*) 0,
    (uint32_t*) 0,
    (uint32_t*) 0,
    (uint32_t*) 0,
    (uint32_t*) 0,
    (uint32_t*) FPU_IRQHandler,
    (uint32_t*) 0,
    (uint32_t*) 0,
    (uint32_t*) SPI4_IRQHandler,
};

/******************************** End of file *********************************/
