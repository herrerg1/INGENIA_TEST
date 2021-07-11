/*
 * ex1.c
 *
 *  Created on: 10 jul 2021
 *      Author: Guillem
 */
#include <stdint.h>
#include <stdio.h>


static uint8_t eeprom_command, sensor_value;

int main (){

	/* Initialization */
	TimerInit();
	SPInit();


	while (1){

	/* Read EEPROM task command */
	SPIEepromEnable();
	eeprom_command = SPIRead();
	SPIEepromDisable();

	}

	return 0;
}

void TimerISR (void){
	/* Read sensor value */
	SPISensorEnable();
	sensor_value = SPIRead();
	SPISensorDisable();
}
