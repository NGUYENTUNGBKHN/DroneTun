/**
 * @file       boot_main.c
 * @brief      
 * @date       2026/05/23
 * @author     [Gentantun] (nguyenthanhtung8196@gmail.com)
 * @details    
 * @ref        
 * @copyright  Copyright (c) 2026 RoboTun
*/
/*******************************************************************************
**                                INCLUDES
*******************************************************************************/
#include "boot_main.h"
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
void jump_to_application();
void jump_to_bootloader();

/*******************************************************************************
**                          FUNCTION DEFINITIONS
*******************************************************************************/
int boot_main()
{
    uint32_t app_crc_check = 1; 

    /* Essential function initialize */
    mcu_init();

    /* Check CRC */ 

    TRACE_INFO("Bootloader --> Start\n");
    if(app_crc_check)   // jump to Application
    {
        jump_to_application();
    }
    else                // jump to Bootloader
    {
        jump_to_bootloader();
    }
    while (1)
    {
        /* code */
    }
}    

void jump_to_bootloader()
{
    boot_process();
}

void jump_to_application()
{
    void (*app_reset_handler)(void);

    uint32_t app_msp_addr = *(volatile uint32_t*)(STEVAL_BOARD_APP_START_ADDRESS);

    uint32_t app_reset_addr = *(volatile uint32_t*)(STEVAL_BOARD_APP_START_ADDRESS + 4);

    /* Reset all register */
    // __set_CONTROL(0x00000000);   // Set CONTROL to its reset value 0.
    // __set_PRIMASK(0x00000000);   // Set PRIMASK to its reset value 0.
    // __set_BASEPRI(0x00000000);   // Set BASEPRI to its reset value 0.
    // __set_FAULTMASK(0x00000000); // Set FAULTMASK to its reset value 0.

    app_reset_handler = (void*)app_reset_addr;

    /* Set MSP */
    __set_MSP(app_msp_addr);
    /* Change vtor table */
    SCB->VTOR = STEVAL_BOARD_APP_START_ADDRESS;
    /* Call reset handler */
    app_reset_handler();
}


/******************************** End of file *********************************/

 

