/******************************************************************//**
* @file max7300.cpp
*
* @author Justin Jordan
*
* @version 0.0
*
* Started: 14JUL15
*
* Updated: 
* 
* 22JAN16 - ported to Arduino
*
* @brief Source file for Max7300 class
***********************************************************************
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


#include "max7300.h"


//configuration register bits
#define MAX7300_S_BIT                   (0x01)
#define MAX7300_M_BIT                   (0x80)

//registers
#define MAX7300_CONFIGURATION           (0x04)
#define MAX7300_TRANSITION_DETECT_MASK  (0x06)
#define MAX7300_PORT_CONFIGURATION      (0x09)
#define MAX7300_PORT_ONLY_BASE_ADRS     (0x20)

//helper for calclating register addresses in 8 port wide fxs
#define MAX7300_8_PORTS_OFFSET          (0x40)


//*********************************************************************
Max7300::Max7300()
{
  
}


//*********************************************************************
void Max7300::begin(max7300_i2c_adrs_t i2c_adrs)
{
    _i2c_adrs = i2c_adrs;
    Wire.begin();
}


//*********************************************************************
void Max7300::end()
{
    Wire.end();
}


//*********************************************************************
uint8_t Max7300::enable_ports(void)
{
    uint8_t result = 4;
    
    result = write_config_register(true, MAX7300_S_BIT);

    return result;
}


//*********************************************************************
uint8_t Max7300::disable_ports(void)
{
    uint8_t result = 4;
    
    result = write_config_register(false, MAX7300_S_BIT);

    return result;
}


//*********************************************************************
uint8_t Max7300::enable_transition_detection(void)
{
    uint8_t result = 4;
    
    result = write_config_register(true, MAX7300_M_BIT);

    return result;
}


//*********************************************************************
uint8_t Max7300::disable_transition_detection(void)
{
    uint8_t result = 4;
    
    result = write_config_register(false, MAX7300_M_BIT);

    return result;
}


//*********************************************************************
uint8_t Max7300::config_port(max7300_port_number_t port_num, max7300_port_type_t port_type)
{
    uint8_t result = 4;
    char data[2];
    uint8_t cnt = 0;
    
    //get address of port configuration register 
    data[cnt++]  = ((port_num/4) + 8);
    
    //get port config bits offset in that register
    uint8_t offset = (port_num % 4);
    
    //set internal register pointer to port configuration register
    result = i2c_write(_i2c_adrs, data, 1);
    if(!result)
    {
        //get current port configuration register
        result = i2c_read(_i2c_adrs, (data + 1), 1);
        
        if(!result)
        {
            //clear old port configuration, do not increment count
            data[cnt] &= ~(0x03 << (offset*2));
            //set port configuration bits
            data[cnt++] |= ((port_type & 0x03) << (offset*2));
            
            //write back to device
            result = i2c_write(_i2c_adrs, data, cnt);
        } 
    }
    
    return result;
}


//*********************************************************************
uint8_t Max7300::config_4_ports(max7300_port_number_t low_port, uint8_t data)
{
    uint8_t result = 4;
    char local_data[2];
    uint8_t cnt = 0;
    
    if(low_port <= MAX7300_PORT_28)
    {
        if((low_port % 4) == 0)
        {
            local_data[cnt++] = ((low_port/4) + 8);
            local_data[cnt++] = data;
            
            //no need for read, modify, write.  
            //Fx is intended to write whole register
            result = i2c_write(_i2c_adrs, local_data, cnt);
        }
    }
    
    return result;
}

//*********************************************************************
uint8_t Max7300::config_all_ports(max7300_port_type_t port_type)
{
    uint8_t result = 4;
    char data[8];
    char local_type = 0;
    uint8_t cnt = 0;
    
    //build byte for each port configuration register
    local_type = ((port_type << 6) | (port_type << 4) | (port_type << 2) | port_type);
    
    //stuff packet
    data[cnt++] = MAX7300_PORT_CONFIGURATION;
    for(/**/;cnt < 8; cnt++)
    {
        data[cnt] = local_type;
    }
    
    result = i2c_write(_i2c_adrs, data, cnt);
 
    return result;
}


//*********************************************************************
uint8_t Max7300::read_port(max7300_port_number_t port_num)
{
    uint8_t result = 4;
    char data[2];
    
    data[0] = (port_num + MAX7300_PORT_ONLY_BASE_ADRS);
    
    //set internal register pointer to port data register
    result = i2c_write(_i2c_adrs, data, 1);
    if(!result)
    {
        //get port data
        result = i2c_read(_i2c_adrs, (data + 1), 1);
        if(!result)
        {
            result = data[1];
        }
        else
        {
            result = -1;
        }
    }
     
    return result;
}


//*********************************************************************
uint8_t Max7300::write_port(max7300_port_number_t port_num, uint8_t data)
{
    uint8_t result = 4;
    char local_data[2];
    uint8_t cnt = 0;
    
    local_data[cnt++] = (port_num + MAX7300_PORT_ONLY_BASE_ADRS);
    local_data[cnt++] = data;
    
    //no need for read, modify, write.  
    //Fx is intended to write whole register
    result = i2c_write(_i2c_adrs, local_data, cnt);
    
    return result;
}


//*********************************************************************
uint8_t Max7300::read_8_ports(max7300_port_number_t low_port)
{
    uint8_t result = 4;
    char data[2];
    
    if((low_port >= MAX7300_PORT_04) && (low_port <= MAX7300_PORT_24))
    {
        data[0] = low_port + MAX7300_8_PORTS_OFFSET;
        
        //set internal register pointer to port data register
        result = i2c_write(_i2c_adrs, data, 1);
        if(!result)
        {
            //get port data
            result = i2c_read(_i2c_adrs, (data + 1), 1);
            if(!result)
            {
                result = data[1];
            }
            else
            {
                result = -1;
            }
        }
    } 
     
    return result;
}


//*********************************************************************
uint8_t Max7300::write_8_ports(max7300_port_number_t low_port, uint8_t data)
{
    uint8_t result = 4;
    char local_data[2];
    uint8_t cnt = 0;
    
    if(low_port <= MAX7300_PORT_24)
    {
        local_data[cnt++] = low_port + MAX7300_8_PORTS_OFFSET;
        local_data[cnt++] = data;
    
        //no need for read, modify, write.  
        //Fx is intended to write whole register
        result = i2c_write(_i2c_adrs, local_data, cnt);
    }
    
    return result;
}


//*********************************************************************
uint8_t Max7300::read_mask_register(bool enable_snapshot)
{
    uint8_t result = 4;
    char data[2];
    
    data[0] = MAX7300_TRANSITION_DETECT_MASK;
    
    //set internal register pointer to mask register
    result = i2c_write(_i2c_adrs, data, 1);
    if(!result)
    {
        //get mask data
        result = i2c_read(_i2c_adrs, (data + 1), 1);
        if(!result)
        {
            if(enable_snapshot)
            {
                result = enable_transition_detection();
                if(!result)
                {
                    result = data[1];
                }
                else
                {
                    result = -1;
                }
            }
            else
            {
                result = data[1];
            }
        }
        else
        {
            result = -1;
        }
    }
    
    return result;
}


//*********************************************************************
uint8_t Max7300::write_mask_register(uint8_t data)
{
    uint8_t result = 4;
    char local_data[2];
    uint8_t cnt = 0;
    
    local_data[cnt++] = MAX7300_TRANSITION_DETECT_MASK;
    local_data[cnt++] = data;

    //no need for read, modify, write.  
    //Fx is intended to write whole register
    result = i2c_write(_i2c_adrs, local_data, cnt);
    
    return result;
}


//*********************************************************************
uint8_t Max7300::write_config_register(bool set_clear, uint8_t data)
{
    uint8_t result = 4;
    char local_data[2];
    uint8_t cnt = 0;
    
    local_data[cnt++] = MAX7300_CONFIGURATION;
    
    //set internal register pointer to configuration register
    result = i2c_write(_i2c_adrs, local_data, 1);
    if(!result)
    {
        //get current configuration register
        result = i2c_read(_i2c_adrs, (local_data + 1), 1);
        
        if(!result)
        {
            if(set_clear)
            {
                local_data[cnt++] |= data;
            }
            else
            {
                local_data[cnt++] &= ~data;
            }
        
            //write back to device
            result = i2c_write(_i2c_adrs, local_data, cnt);
        } 
    }

    return result;
}


//*********************************************************************
uint8_t Max7300::i2c_write(uint8_t adrs, const char *p_data_buff, uint8_t num_bytes)
{
  
    Wire.beginTransmission(adrs);
    Wire.write(p_data_buff, num_bytes);
    return(Wire.endTransmission());
}


//*********************************************************************
uint8_t Max7300::i2c_read(uint8_t adrs, char *p_data_buff, uint8_t num_bytes)
{
    uint8_t rtn_val =0xFF;
    uint8_t num_bytes_returned = 0;
    uint8_t idx = 0;

    num_bytes_returned = Wire.requestFrom(adrs, num_bytes);

    if(num_bytes_returned == num_bytes)
    {
        rtn_val = 0;

        while(Wire.available())
        {
          *(p_data_buff + idx++) = Wire.read();
        }
    }

    return(rtn_val);
}

