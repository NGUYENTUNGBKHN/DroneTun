/**
 * @file       mcu.h
 * @brief      
 * @date       2026/05/23
 * @author     [Gentantun] (nguyenthanhtung8196@gmail.com)
 * @details    
 * @ref        
 * @copyright  Copyright (c) 2026 RoboTun
*/
#ifndef _MCU_H_
#define _MCU_H_
#ifdef __cplusplus
extern "C"
{
#endif

/* CODE */
#include "steval_board_1.h"
#include "stm32f4xx_hal_conf.h"
#include "stm32f4xx_hal.h"
#include "cachel1_armv7.h"
#include "debug_1.h"


void mcu_init();

#ifdef __cplusplus
}
#endif
#endif