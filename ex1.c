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
		SPIEepromEnable(); //1 us
		eeprom_command = SPIRead(); //5 us
		SPIEepromDisable(); //1 us

		/* Execution of the task*/
		RobotTask (eeprom_command); //100 ms

		/*
		 * The main problem I see here is how can I interrupt the
		 * RobotTask in case the sensor detect an object, as it is
		 * the slowest function
		 */

		/* Condition to stop the main */
		if (sensor_value == SENSOR_LIMIT)
		{
			RobotStop(); //15us
			stop_program = 1;
		}

	}while (!stop_program);

	return 0;
}

void TimerISR (void){
	/* Read sensor value */
	SPISensorEnable(); //1 us
	sensor_value = SPIRead(); //5 us
	SPISensorDisable(); // 1 us

	TimerInit();
}
