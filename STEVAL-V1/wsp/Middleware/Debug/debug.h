/**
 * @file       debug.h
 * @brief      
 * @date       2026/05/24
 * @author     [Gentantun] (nguyenthanhtung8196@gmail.com)
 * @details    
 * @ref        
 * @copyright  Copyright (c) 2026 RoboTun
*/
#ifndef _DEBUG_H_
#define _DEBUG_H_
#ifdef __cplusplus
extern "C"
{
#endif

/* CODE */
#include <stdint.h>
#include <stdio.h>


void debug_uart_init(uint32_t baudrate);
void debug_uart_putchar(char ch);

#define DEBUG
#if defined(DEBUG)
/* TRACE info : normal log */
#define TRACE_INFO(format, ... )                                                        \
    printf("%s (%d) : " format, __FUNCTION__, __LINE__, ##__VA_ARGS__)                  \
/* TRACE info : normal log */
#define ERROR(format, ... )                                                              \
    printf("%s (%d) : " format, __FUNCTION__, __LINE__, ##__VA_ARGS__)                  \
    
#else
#define TRACE_INFO(__format__, ...)
#define ERROR(__format__, ...)
#endif //  DEBUG


#ifdef __cplusplus
}
#endif
#endif