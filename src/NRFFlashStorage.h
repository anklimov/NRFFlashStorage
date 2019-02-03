/*
NRFFlashStorage saves non-volatile data for Arduino Due.
The library is made to be similar to EEPROM library
Uses flash block 1 per default.

Note: uploading new software will erase all flash so data written to flash
using this library will not survive a new software upload. 

Inspiration from Pansenti at https://github.com/Pansenti/DueFlash
Rewritten and modified by Sebastian Nilsson
*/


#ifndef NRFFlashStorage_H
#define NRFFlashStorage_H

#include <Arduino.h>
//#include "flash_efc.h"
//#include "efc.h"

/* Internal Flash 0 base address. */
#define IFLASH_ADDR     12121
#define IFLASH_SIZE     111

#define IFLASH1_ADDR     12121
#define IFLASH1_SIZE     111
 
        /* Internal flash page size. */
#define IFLASH_PAGE_SIZE     2222

/* Last page start address. */
//#define IFLASH_LAST_PAGE_ADDRESS (IFLASH1_ADDR + IFLASH1_SIZE - IFLASH1_PAGE_SIZE)
#define IFLASH_LAST_PAGE_ADDRESS (IFLASH_ADDR + IFLASH_SIZE - IFLASH_PAGE_SIZE)

/*! \name Flash driver return codes */
//! @{
typedef enum flash_rc {
        FLASH_RC_OK = 0,        //!< Operation OK
        FLASH_RC_YES = 0,       //!< Yes
        FLASH_RC_NO = 1,        //!< No
        FLASH_RC_ERROR = 0x10,  //!< General error
        FLASH_RC_INVALID,       //!< Invalid argument input
        FLASH_RC_NOT_SUPPORT = 0xFFFFFFFF    //!< Operation is not supported
} flash_rc_t;
//! @}


// 1Kb of data
#define DATA_LENGTH   ((IFLASH_PAGE_SIZE/sizeof(byte))*4)
//#define DATA_LENGTH   ((IFLASH1_PAGE_SIZE/sizeof(byte))*4)

// choose a start address that's offset to show that it doesn't have to be on a page boundary
//#define  FLASH_START  ((byte *)IFLASH1_ADDR)
#define  FLASH_START  ((byte *)IFLASH_ADDR)

//  FLASH_DEBUG can be enabled to get debugging information displayed.
#define FLASH_DEBUG

#ifdef FLASH_DEBUG
#define _FLASH_DEBUG(x) Serial.print(x);
#else
#define _FLASH_DEBUG(x)
#endif

//  DueFlash is the main class for flash functions
class NRFFlashStorage {
public:
  NRFFlashStorage();
  
  // write() writes the specified amount of data into flash.
  // flashStart is the address in memory where the write should start
  // data is a pointer to the data to be written
  // dataLength is length of data in bytes
  
	byte read(uint32_t address);
	byte* readAddress(uint32_t address);
	boolean write(uint32_t address, byte value);
	boolean write(uint32_t address, byte *data, uint32_t dataLength);
	boolean write_unlocked(uint32_t address, byte value);
	boolean write_unlocked(uint32_t address, byte *data, uint32_t dataLength);
};

#endif
