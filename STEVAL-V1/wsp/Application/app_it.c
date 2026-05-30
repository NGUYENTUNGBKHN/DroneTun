/**
 * @file       app_it.c
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
#include "app_it.h"
#include "app_main.h"
#include "stm32f4xx_hal.h"
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
// extern PCD_HandleTypeDef hpcd_USB_OTG_FS;
extern SPI_HandleTypeDef SpiHandle;
// extern SPI_HandleTypeDef hspi2;
// extern TIM_HandleTypeDef htim2;
// extern TIM_HandleTypeDef htim9;
// extern UART_HandleTypeDef huart1;

/*******************************************************************************
**                          FUNCTION DEFINITIONS
*******************************************************************************/
/**
 * @brief   This function handles NMI exception.
 * @param  None
 * @retval None
 */
void NMI_IRQHandler(void)
{
}

/**
 * @brief  This function handles Hard Fault exception.
 * @param  None
 * @retval None
 */
void HardFault_IRQHandler(void)
{
    /* Go to infinite loop when Hard Fault exception occurs */
    while (1)
    {
    }
}

/**
 * @brief  This function handles Memory Manage exception.
 * @param  None
 * @retval None
 */
void MemManage_IRQHandler(void)
{
    /* Go to infinite loop when Memory Manage exception occurs */
    while (1)
    {
    }
}

/**
 * @brief  This function handles Bus Fault exception.
 * @param  None
 * @retval None
 */
void BusFault_IRQHandler(void)
{
    /* Go to infinite loop when Bus Fault exception occurs */
    while (1)
    {
    }
}

/**
 * @brief  This function handles Usage Fault exception.
 * @param  None
 * @retval None
 */
void UsageFault_IRQHandler(void)
{
    /* Go to infinite loop when Usage Fault exception occurs */
    while (1)
    {
    }
}

/**
 * @brief  This function handles SVCall exception.
 * @param  None
 * @retval None
 */
void SVC_IRQHandler(void)
{
}

/**
 * @brief  This function handles Debug Monitor exception.
 * @param  None
 * @retval None
 */
void DebugMonitor_IRQHandler(void)
{
}

/**
 * @brief  This function handles PendSVC exception.
 * @param  None
 * @retval None
 */
void PendSV_IRQHandler(void)
{
}
/**
 * @brief  This function handles SysTick Handler.
 * @param  None
 * @retval None
 */
void SysTick_IRQHandler(void)
{
    HAL_IncTick();
}

/**
 * @brief This function handles SPI1 global interrupt.
 */
void SPI1_IRQHandler(void)
{
    /* USER CODE BEGIN SPI1_IRQn 0 */

    /* USER CODE END SPI1_IRQn 0 */
    HAL_SPI_IRQHandler(&SpiHandle);
    /* USER CODE BEGIN SPI1_IRQn 1 */

    /* USER CODE END SPI1_IRQn 1 */
}

void EXTI4_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
}

void USART1_IRQHandler(void)
{
    /* USER CODE BEGIN USART1_IRQn 0 */

    /* USER CODE END USART1_IRQn 0 */
    //   HAL_UART_IRQHandler(&huart1);
    /* USER CODE BEGIN USART1_IRQn 1 */

    /* USER CODE END USART1_IRQn 1 */
}

/******************************** End of file *********************************/
