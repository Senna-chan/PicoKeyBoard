// CommonSetup.h

#ifndef _COMMONSETUP_h
#define _COMMONSETUP_h

#include <Arduino.h>

/**
 * Setup SPI1(OLEDS)
 */
void setupSPI1(void);
/**
 * Setup SPI2(KEYMATRIX)
 */
void setupSPI2(void);

/**
 * Setup Wire1 with specific pins.
 */
void setupWire1(void);

/**
 * Setup UART1 for debugging.
 */
void setupUART1(void);

/**
 * Setup UART2 for BluetoothModule.
 */
void setupUART2(void);


#endif


