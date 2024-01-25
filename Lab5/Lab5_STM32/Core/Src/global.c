/*
 * global.c
 *
 *  Created on: Dec 4, 2023
 *      Author: Administrator
 */

#include"global.h"

int status = 2;
int status1 = RESPONSE_DATA;
int commandCheck(char *str)
{
	if (str[0] == 'R' && str[1] == 'S' && str[2] == 'T' && str[3] == '#') return 1;
	else if (str[0] == 'O' && str[1] == 'K' && str[2] == '#') return 2;
	else return 0;

}
