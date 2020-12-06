# MCP23016

ESP32 Arduino library for Microchip MCP23016 16-channel IO expander

## Description

Short discription of the interface

* **MCP23016**         constructor
* **init(I2CAddress)**

* **pinMode(pin, value)**       pin = a0..a7, b0..b7 | value = INPUT,OUTPUT
* **digitalWrite(pin, value)**  pin = a0..a7, b0..b7 | value = LOW(0) HIGH (1)
* **digitalRead(pin)**          pin = a0..a7, b0..b7
* **writeByte(port, value)**    port = 0, 1 | value = 0..255
* **readByte(port)**            port = 0, 1

## Operation

See example
