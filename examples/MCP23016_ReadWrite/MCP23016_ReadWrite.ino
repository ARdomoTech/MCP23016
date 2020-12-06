/***********************************************************
 * ESP32 library for Microchip MCP23016 16-channel IO expander
 * Adapted from Rob Tillaart MCP23017 Arduino library
 * Developed by: ARdomoTech Enterprises
 * 
 * 
 * Sample sketch for testing MCP23016 library                          
 *  
*/

#include <MCP23016.h>


MCP23016 MCP;

#define GPA 0x00 //port A data register address
#define GPB 0x01 //port B data register address
#define I_mcpInterrupt 15 //GPIO15 of ESP32 - LOW means one or more inputs change value. after a read it will go back to HIGH
#define O_A0 a0 //MCP GPIO A0 declared as OUTPUT
#define I_B0 b0 //MCP GPIO B0 declared as INPUT

uint8_t mcpA; //internal variable of the library - required to be declared as is
uint8_t mcpB; //internal variable of the library - required to be declared as is


void setup(void)
{ 
  Serial.begin(115200);  
  Wire.begin();    
  Wire.setClock(200000); 
  pinMode(I_mcpInterrupt, INPUT_PULLUP);
  
  MCP.init(0x20); //initialization with I2C address 20Hex
   
  MCP.pinMode(O_A0, OUTPUT); //A0 as OUTPUT
  MCP.pinMode(I_B0, INPUT); //B0 as OUTPUT

  MCP.digitalWrite(O_A0, HIGH); //set A0
  Serial.print("A0 state: ");
  Serial.println(MCP.digitalRead(O_A0));
  Serial.print("B0 state: ");
  Serial.println(MCP.digitalRead(I_B0));  
  MCP.digitalWrite(O_A0, LOW); //reset A0
}

void loop(void)
{ 
  readMCP(!digitalRead(I_mcpInterrupt)); //monitor if there are changes on pins of port B declared as input
}

void readMCP(bool enable)
{
  if(enable)  
  {
    String statusGP = String(MCP.readByte(GPB),BIN); 
    Serial.print("Port B state: ");
    Serial.println(statusGP);
  }       
}
