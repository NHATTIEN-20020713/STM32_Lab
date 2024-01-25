/*
 * command_parser_fsm.c
 *
 *  Created on: Dec 4, 2023
 *      Author: Administrator
 */

#include "command_parser_fsm.h"

uint8_t temp = 0;
uint8_t index_buffer = 0;
uint8_t buffer_flag = 0;
uint32_t ADC_value = 0;
uint8_t buffer[MAX_BUFFER_SIZE];
uint8_t indexBuffer = 0;
uint8_t receiving = 0;
uint8_t waiting = 0;
char command[10];
char str[30];

void clearBuffer()
{
	memset(command, 0, sizeof(command));
	indexBuffer = 0;
}

void command_parser_fsm()
{
	switch(status)
	{
		case INIT:
			clearBuffer();
			status = RECEIVE_COMMAND;
			break;
		case RECEIVE_COMMAND:
			if(indexBuffer >= 4)
			{
				clearBuffer();
			}
			else if(temp == '!')
			{
				receiving = 1;
				clearBuffer();
			}
			else if(receiving == 1)
				command[indexBuffer++] = temp;
			break;
		default:
			break;
	}
}

void uart_communication_fsm()
{
	switch(status1)
	{
		case RESPONSE_DATA:

			if(commandCheck(command) == 1)
			{
				HAL_ADC_Start(&hadc1);
				ADC_value = HAL_ADC_GetValue(&hadc1);
				HAL_ADC_Stop(&hadc1);
				sprintf((char *)str, "%s%u%s", "!ADC=", (long)ADC_value, "#\r\n");
				HAL_UART_Transmit(&huart2, (void*)str, sizeof(str), 50);
				clearBuffer();
				setTimer(0, 100);
				waiting = 1;
			}
			else if(commandCheck(command) == 2) status1 = END;
			else if(waiting == 1)
			{
				if(timerFlag[0] == 1)
				{
					HAL_UART_Transmit(&huart2, (void*)str, sizeof(str), 50);
					setTimer(0, 100);
				}
			}
			break;
		case END:
			memset(str, 0, sizeof(str));
			sprintf((char*)str, "%s", "END\r\n");
			HAL_UART_Transmit(&huart2, (void*)str, sizeof(str), 50);
			status1 = END + 1;
			break;
		default:
			break;
	}
}
