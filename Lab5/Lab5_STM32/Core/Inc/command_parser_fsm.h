/*
 * command_parser_fsm.h
 *
 *  Created on: Dec 4, 2023
 *      Author: Administrator
 */

#ifndef INC_COMMAND_PARSER_FSM_H_
#define INC_COMMAND_PARSER_FSM_H_

#include"global.h"

#define MAX_BUFFER_SIZE 30

extern uint8_t temp;
extern uint8_t buffer[MAX_BUFFER_SIZE];
extern uint8_t index_buffer;
extern uint8_t buffer_flag;

void clearBuffer();
void command_parser_fsm();
void uart_communication_fsm();

#endif /* INC_COMMAND_PARSER_FSM_H_ */
