/**
 * @file       steval_board_1.h
 * @brief      
 * @date       2026/05/23
 * @author     [Gentantun] (nguyenthanhtung8196@gmail.com)
 * @details    
 * @ref        
 * @copyright  Copyright (c) 2026 RoboTun
*/
#ifndef _STEVAL_BOARD_1_H_
#define _STEVAL_BOARD_1_H_
#ifdef __cplusplus
extern "C"
{
#endif

/* CODE */

/************************/
/* STEVAL Memory Map    */
/************************/                            

/* Memory of STEVAL V1 */
#define STEVAL_BOARD_MM_START_ADDRESS       0x00000000
#define STEVAL_BOARD_MM_END_ADDRESS         0xFFFFFFFF

/* BOOTLOADER */

/* APPLICATION */
#define STEVAL_BOARD_APP_START_ADDRESS   0x08040000
#define STEVAL_BOARD_APP_SIZE            0x3FFFF      

/***********************/
/* Setup Board         */
/***********************/
#define STEVAL_BOARD_DEBUG_BAUD_RATE    115200

#ifdef __cplusplus
}
#endif
#endif