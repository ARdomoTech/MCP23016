/***************************************************************
 * ESP32 Arduino library for Microchip MCP23016 16-channel IO expander
 * Adapted from Rob Tillaart MCP23017 Arduino library
 * Developed by: ARdomoTech Enterprises
 * https://github.com/ARdomoTech/MCP23016
 * 
 * Revision History: MCP23016.h
 * Version     Date          Author      Commemts 
 * 1.0.0       2020.12.03    acruzado    create                                
 *
*****************************************************************/


#include "Wire.h"


#define a0 0 //port A bit 1
#define a1 1 //port A bit 2
#define a2 2 //port A bit 3
#define a3 3 //port A bit 4
#define a4 4 //port A bit 5
#define a5 5 //port A bit 6
#define a6 6 //port A bit 7
#define a7 7 //port A bit 8
#define b0 8 //port B bit 1
#define b1 9 //port B bit 2
#define b2 10 //port B bit 3
#define b3 11 //port B bit 4
#define b4 12 //port B bit 5
#define b5 13 //port B bit 6
#define b6 14 //port B bit 7
#define b7 15 //port B bit 8

extern uint8_t mcpA; //port A data register
extern uint8_t mcpB; //port B data register

class MCP23016
{
  public:
    void init(uint8_t address);
    void pinMode(uint8_t pin, uint8_t value);
    void digitalWrite(uint8_t pin, uint8_t value);
    bool digitalRead(uint8_t pin);
    void writeByte(uint8_t port, uint8_t value);
    uint8_t readByte(uint8_t port);
  
  private:
    void writeReg(uint8_t reg, uint8_t value);
    uint8_t readReg(uint8_t reg);
    uint8_t mcpAddress;  
};
