/*
  EEPROM.cpp - EEPROM library
  Copyright (c) 2006 David A. Mellis.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

/******************************************************************************
 * Includes
 ******************************************************************************/

#include "Energia.h"
#include "MspFlash.h"
#include "EEPROM.h"

/******************************************************************************
 * Definitions
 ******************************************************************************/

/******************************************************************************
 * Constructors
 ******************************************************************************/

/******************************************************************************
 * User API
 ******************************************************************************/
#if (defined __MSP430_HAS_FLASH__) || (defined __MSP430_HAS_FLASH2__)

#define BYTES_PER_BLOCK INFO_SIZE
#define NUM_BLOCKS		4

#define PLACE_IN_INFOMEM __attribute__((section(".infomem")))
uint8_t EEPROM_buffer[BYTES_PER_BLOCK] PLACE_IN_INFOMEM;


uint8_t EEPROMClass::read(int address)
{
	return (uint8_t) EEPROM_buffer[address];
}

void EEPROMClass::write(int address, uint8_t value)
{

	//if (EEPROM_buffer[address] == 0xFF){
	    // still erased - just write the data
        //Flash.write((unsigned char *)&EEPROM_buffer[i],  (unsigned char *)&value,1);
	//}else{
	    uint16_t i;
	    uint8_t buffer[BYTES_PER_BLOCK];
        for (i =0;i<BYTES_PER_BLOCK;i++){
            buffer[i]=EEPROM_buffer[i];
        }
        buffer[address]=value;

        Flash.erase((unsigned char *)EEPROM_buffer);
        Flash.write((unsigned char *)EEPROM_buffer,  (unsigned char *)buffer,BYTES_PER_BLOCK);
	//}
}

void EEPROMClass::update(int address, uint8_t value)
{
  	uint8_t old_value = read(address);
  
	if(value != old_value)
		write(address, value);
}

EEPROMClass EEPROM;
#endif // #ifdef __MSP430_HAS_FLASH__
