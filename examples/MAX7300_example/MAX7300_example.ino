/***********************************************************************
* Copyright (C) 2016 Maxim Integrated Products, Inc., All Rights Reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
* OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
* OTHER DEALINGS IN THE SOFTWARE.
*
* Except as contained in this notice, the name of Maxim Integrated
* Products, Inc. shall not be used except as stated in the Maxim Integrated
* Products, Inc. Branding Policy.
*
* The mere transfer of this software does not imply any licenses
* of trade secrets, proprietary technology, copyrights, patents,
* trademarks, maskwork rights, or any other form of intellectual
* property whatsoever. Maxim Integrated Products, Inc. retains all
* ownership rights.
**********************************************************************/


#include <Arduino.h>
#include <max7300.h>


Max7300 io;

uint8_t data = 0;

void setup() 
{
  Serial.begin(9600);

  io.begin(Max7300::MAX7300_I2C_ADRS0);
  
  for(uint8_t idx = 0; idx < 8; idx++)
  {
    //config ports 12-19 as outputs
    io.config_port((Max7300::max7300_port_number_t) (idx+12), Max7300::MAX7300_PORT_OUTPUT);
    
    //config ports 22-29 as inputs
    io.config_port((Max7300::max7300_port_number_t) (idx+22), Max7300::MAX7300_PORT_INPUT_PULLUP);
  }

  io.enable_ports();
}

void loop() 
{
  data = io.read_8_ports((Max7300::max7300_port_number_t) 22);
  io.write_8_ports((Max7300::max7300_port_number_t) 12, data);

  Serial.print("data = ");
  Serial.println(data, BIN);
  
  delay(100);
}
