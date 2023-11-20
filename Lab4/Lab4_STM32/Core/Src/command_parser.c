/*
 * command_parser.c
 *
 *  Created on: Nov 20, 2023
 *      Author: Administrator
 */

#include "command_parser.h"

void command_parser_fsm()
{
	switch(command_status)
	{
		case START_COMMAND:
			if(buffer[index_buffer - 1] == '!')
			{
				command_status = END_COMMAND;
			}
			break;
		case END_COMMAND:
			if(buffer[index_buffer - 1] == '#')
			{
				str_cpy(command_data, buffer);
				command_flag = 1;
			}
			else if(buffer[index_buffer - 1] == '!')
			{
				str_cpy(buffer, empty_str);
				index_buffer = 0;
				buffer[index_buffer++] = '!';
				command_status = START_COMMAND;
				command_flag = 0;
			}
			break;
		default:
			break;
	}
}
