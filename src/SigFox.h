/*****************************************************************************/
/*
  Arduino library for Atmel SIGFOX module ATA8520.
  This library uses Arduino SPI library.
*/
/*****************************************************************************/

/*
 Copyright (c) 2016 Arduino LLC

 This software is open source software and is not owned by Atmel;
 you can redistribute it and/or modify it under the terms of the GNU 
 Lesser General Public License as published by the Free Software Foundation; 
 either version 2.1 of the License, or (at your option) any later version.

 You acknowledge that the ArduinoUNO software is distributed to you free of 
 charge on an "as is" basis and that it has not been developed to meet your 
 specific requirements. It is supplied in the hope that it will be useful but 
 WITHOUT ANY WARRANTY that its use will be uninterrupted or error-free.
 All other conditions, warranties or other terms which might have effect 
 between the parties or be implied or incorporated into this licence or any 
 collateral contract whether by statute or otherwise are hereby excluded, 
 including the implied conditions, warranties or other terms as to 
 satisfactory quality, fitness for purpose, non-infringement or the use of 
 reasonable skill and care.
 See the GNU Lesser General Public License for more details.
*/

#ifndef SIGFOX_h
#define SIGFOX_h

#include <Arduino.h>
#include <SPI.h>

#define BLEN  64            // Communication buffer length

typedef enum country {
  US = 0 ,
  EU
} Country;

typedef enum communication {
  TX = 0 ,
  TXRX
} TxRxMode;

class SIGFOXClass
{
  public:

  /*
  * Enables debug LED and prints
  */
  void debug(bool on);
  /*
  * Initialize module (ready to transmit)
  */
  int begin(bool configured = false);
    /*
  * Initialize module specifying SPI port and pins (ready to transmit)
  */
  int begin(SPIClass& spi, int reset, int poweron, int interrupt, int chip_select, int led);
  /*
  * Send null terminated string as message to SIGFOX network
  * Max 12 characters long  
  * Return SIGFOX status code
  */
  int send(char mess[]);
  /*
  * Send an array of bytes (max 12 bytes long) as message to SIGFOX network
  * Return SIGFOX status code
  */
  int send(unsigned char mess[],int len);
  /*
  * Read status (fill ssm,atm,sig status variables)
  */
  void getStatus();
  /*
  * Return status code.
  * Type: 0 -> ssm status ; 1 -> atm status ; 2 -> sigfox status    
  */
  int getStatusCode(byte type);
  /*
  * Return atm status message 
  */
  char* getStatusAtm();
  /*
  * Return SIGFOX status message
  */
  char* getStatusSig();
  /*
  * Return ATM version (major ver,minor ver)(two bytes)
  */
  unsigned char* getAtmVersion();
  /*
  * Return SIGFOX version (major ver, minor ver) (two bytes)
  */
  unsigned char* getSigVersion();
  /*
  * Return ID (4 bytes)
  */
  unsigned char* getID();
  /*
  * Return PAC (16 bytes)
  */
  unsigned char* getPAC();
  /*
  * Reset module
  */
  void reset();

  void getTemperatureInternal();

  void setMode(Country EUMode, TxRxMode tx_rx);

  int calibrateCrystal();
  /*
  * Test mode
  */
  void testMode(byte frameL,byte frameH, byte chanL,byte chanH);
  /*
  *  Disable module
  */
  void end();

  char* readConfig(int* len);

  private:

  byte ssm;
  byte atm;
  byte sig;
  byte sig2;
  byte vhidle;
  byte vlidle;
  byte vhactive;
  byte vlactive;
  byte temperatureL;
  byte temperatureH;
  uint32_t tx_freq, rx_freq;
  uint8_t configuration;
  uint8_t repeat;
  unsigned char buffer[BLEN];  // module communication buffer
  SPIClass& spi_port = SPI;
  int reset_pin;
  int poweron_pin;
  int interrupt_pin;
  int chip_select_pin;
  int led_pin;
  bool debugging = false;
};

extern SIGFOXClass SigFox;

#endif
