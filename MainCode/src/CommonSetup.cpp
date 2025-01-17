// 
// 
// 

#include <SPI.h>
#include <Wire.h>

#include "CommonSetup.h"
#include "Config.h"

void setupSPI1(){
	SPI.setRX(SPI1_MISO);
	SPI.setTX(SPI1_MOSI);
	SPI.setSCK(SPI1_SCLK);
	SPI.begin();
}

void setupSPI2(){
	if (!SPI1.setRX(SPI2_MISO)) Serial.println("SPI2 MISO/RX BAD");
	if (!SPI1.setTX(SPI2_MOSI)) Serial.println("SPI2 MISO/TX BAD");
	if (!SPI1.setSCK(SPI2_SCLK)) Serial.println("SPI2 SCK BAD");
	SPI1.begin();
}

void setupWire1() {
	Wire.setSCL(WIRE1_SCL);
	Wire.setSDA(WIRE1_SDA);
	Wire.begin();
	Wire.setClock(400000); // 400 kHz
}

void setupUART1(void)
{
}

void setupUART2(void)
{
	if (!Serial2.setTX(UART2_TX)) 
	{
		Serial.printf("Failed to set UART2_TX to GP%d\r\n", UART2_TX);
	}
	if (!Serial2.setRX(UART2_RX)) 
	{
		Serial.printf("Failed to set UART2_RX to GP%d\r\n", UART2_RX);
	}
}
