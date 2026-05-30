/**
 * @file       app_main.h
 * @brief      
 * @date       2026/05/24
 * @author     [Gentantun] (nguyenthanhtung8196@gmail.com)
 * @details    
 * @ref        
 * @copyright  Copyright (c) 2026 RoboTun
*/
#ifndef _APP_MAIN_H_
#define _APP_MAIN_H_
#ifdef __cplusplus
extern "C"
{
#endif

/* CODE */
#include <stdio.h>
#include <stdint.h>
#include "mcu.h"
#include "debug_1.h"
#include "ble_status.h"
#include "ble.h"
#include "component.h"

#define STM32_UUID ((uint32_t *)0x1FFF7A10)
#define NAME_BLUEMS 'D','R','N','1','1','2','0'
extern int32_t BytesToWrite;
extern uint8_t BufferToWrite[256];


#ifdef __cplusplus
}
#endif
#endif