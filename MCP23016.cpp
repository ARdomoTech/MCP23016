/***************************************************************
 * ESP32 Arduino library for Microchip MCP23016 16-channel IO expander
 * Adapted from Rob Tillaart MCP23017 Arduino library
 * Developed by: ARdomoTech Enterprises
 * https://github.com/ARdomoTech/MCP23016
 * 
 * Revision History: MCP23016.cpp
 * Version     Date          Author      Commemts 
 * 1.0.0       2020.12.03    acruzado    create                                
 *
*****************************************************************/

#include "MCP23016.h"

#define GPA  0x00   // data register port  A 
#define GPB  0x01   // data register port B 
#define OLATA  0x02   // output latch register port A 
#define OLATB  0x03   // output latch register port B 
#define IPOLA   0x04  // input polarity register port A 
#define IPOLB   0x05  // input polarity register port B 
#define IODIRA  0x06  // I/O direction register port A 
#define IODIRB  0x07  // I/O direction register port B 
#define INTCAPA 0x08  // interrupt capture register port A 
#define INTCAPB 0x09  // interrupt capture register port B 
#define IOCONA  0x0A  // I/O expander control register port A 
#define IOCONB  0x0B  // I/O expander control register port B



void MCP23016::init(uint8_t address)
{
  mcpAddress = address;
  writeReg(IODIRA, 0x00);
  writeReg(IODIRB, 0x00); 
  writeReg(GPA, 0x00);
  writeReg(GPB, 0x00);   
}



void MCP23016::pinMode(uint8_t pin, uint8_t value)
{
  if (value != INPUT and value != OUTPUT) return;  
  uint8_t IOdir = IODIRA;   
  if (pin > 7)
  {
    IOdir = IODIRB;
    pin -= 8;
  }
  uint8_t val = readReg(IOdir);
  uint8_t mask = 1 << pin;
  if (value == INPUT) val |= mask;
  else if (value == OUTPUT) val &= ~mask;
  writeReg(IOdir, val);
}

void MCP23016::digitalWrite(uint8_t pin, uint8_t value)   
{
  uint8_t IOreg, val;   
  if (pin > 7)
  {
    IOreg = GPB;
    pin -= 8;	
	  val = mcpB;
  }  
  else
  {
	  IOreg = GPA;
   	val = mcpA;
  }
  uint8_t mask = 1 << pin; 
  if (value) val |= mask;  
  else val &= ~mask;
  writeReg(IOreg, val);
  if(IOreg==1) mcpB = val;
  else mcpA = val;
}

bool MCP23016::digitalRead(uint8_t pin)
{
  uint8_t IOreg = GPA;		
  if (pin > 7)
  {
    IOreg = GPB;
    pin -= 8;	
  }   
  uint8_t val = readReg(IOreg);
  uint8_t mask = 1 << pin;
  if(IOreg==1) mcpB = val;
  else mcpA = val;
  if (val & mask) return 1;
  else return 0;
}

void MCP23016::writeByte(uint8_t port, uint8_t value) 
{
  if (port == 0) 
  {
  	writeReg(GPA, value);
  	mcpA = value;
  }	
  if (port == 1) 
  {
    writeReg(GPB, value);
    mcpB = value;
  }
}

uint8_t MCP23016::readByte(uint8_t port)
{
  if(port<0 and port>1) return 255;	
  if (port == 0) 
  {
  	mcpA = readReg(GPA); 
  	return mcpA; 
  }
  if (port == 1)
  {
  	mcpB = readReg(GPB); 
  	return mcpB; 
  }  
}

void MCP23016::writeReg(uint8_t reg, uint8_t value)
{
  Wire.beginTransmission(mcpAddress);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

uint8_t MCP23016::readReg(uint8_t reg)
{
  Wire.beginTransmission(mcpAddress);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(mcpAddress, (uint8_t)1);
  return Wire.read();
}
