/**
 * @file       app_it.h
 * @brief      
 * @date       2026/05/24
 * @author     [Gentantun] (nguyenthanhtung8196@gmail.com)
 * @details    
 * @ref        
 * @copyright  Copyright (c) 2026 RoboTun
*/
#ifndef _APP_IT_H_
#define _APP_IT_H_
#ifdef __cplusplus
extern "C"
{
#endif

/* CODE */
void NMI_IRQHandler(void);
void HardFault_IRQHandler(void);
void MemManage_IRQHandler(void);
void BusFault_IRQHandler(void);
void UsageFault_IRQHandler(void);
void SVC_IRQHandler(void);
void DebugMonitor_IRQHandler(void);
void PendSV_IRQHandler(void);
void SysTick_IRQHandler(void);

#ifdef __cplusplus
}
#endif
#endif