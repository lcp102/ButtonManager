#ifndef TRACE_CONFIG_H
#define TRACE_CONFIG_H

/**
 * Trace config example. Copy this file into the 'config' folder 
 * of your project and do your configuration there. 
 * Be sure to set up your include path such that the config file in
 * your project is seen first.
 * 
 * Do not perform changes in this file at this location. It may
 * cause other projects to no more build!
 */
#include "stm32f7xx_hal.h"                      // Do not use "mcu/mcu.h" here!
#ifdef __cplusplus
extern "C" UART_HandleTypeDef huart1;           // Defined in main.c

#define USE_PLATFORM_F7_DISCO_GCC_TRACE         1

#define TRACE_UART_NUMBER                       0
#define TRACE_UART_HANDLE                       huart1
#define TRACE_UART_BAUD_RATE                    /* 115200, but given by STM32CubeMX tool configuration */
#define TRACE_UART_USE_TX_DMA                   false
#define TRACE_UART_CONSTRUCTOR_PARAMETERS       TRACE_UART_NUMBER, &TRACE_UART_HANDLE, TRACE_UART_USE_TX_DMA

#define TRACE_ADD_CRLF_SEQU                     0

#define USE_TRACE_EXAMPLE		0
#define TRACE_ADD_CRLF_SEQU		0
#endif
#endif // TRACE_CONFIG_H
