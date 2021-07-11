/*
 * ex1.c
 *
 *  Created on: 10 jul 2021
 *      Author: Guillem
 */
#include <stdint.h>
#include <stdio.h>
#define SENSOR_LIMIT 128

static uint8_t eeprom_command, sensor_value;
static _Bool stop_program = false;

int main (){

	/* Initialization */
	TimerInit();
	SPInit();


	do {
		/* Read EEPROM task command */
		SPIEepromEnable();
		eeprom_command = SPIRead();
		SPIEepromDisable();

		/* Execution of the task*/
		RobotTask (eeprom_command);

		/* Condition to stop the main */
		if (sensor_value == SENSOR_LIMIT)
		{
			RobotStop();
			stop_program = 1;
		}

	}while (!stop_program);

	return 0;
}

void TimerISR (void){
	/* Read sensor value */
	SPISensorEnable();
	sensor_value = SPIRead();
	SPISensorDisable();

	TimerInit();
}
