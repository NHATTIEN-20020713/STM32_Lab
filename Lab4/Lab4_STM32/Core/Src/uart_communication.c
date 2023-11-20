/*
 * uart_communication.c
 *
 *  Created on: Nov 20, 2023
 *      Author: Administrator
 */

#include "uart_communication.h"

void uart_communication_fsm()
{
	char str[MAX_BUFFER_SIZE];
	switch(uart_status)
	{
		case START_UART:
			if(command_flag == 1)
			{
				if(compare(command_data, begin) == 1)
				{
					uart_status = TRANSMIT_DATA;
					setTimer(20);
				}
				else if(compare(command_data,finish) == 1)
				{
					uart_status = END_UART;
					setTimer(300);
				}
				command_flag = 0;
			}
			break;
		case TRANSMIT_DATA:
			if(timer_flag == 1)
			{
				ADC_Value = HAL_ADC_GetValue(&hadc1);
				HAL_UART_Transmit (&huart2 , (void*)str , sprintf (str , "\rADC_value: %ld \r\n", ADC_Value), 1000);
				if(buffer[index_buffer - 1] == '!')
				{
					uart_status = START_UART;
				}
				setTimer(20);
			}
			break;
		case END_UART:
			if(timer_flag == 1)
			{
				uart_status = START_UART;
			}
			break;
		default:
			break;

	}
}
