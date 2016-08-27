/******************************************************************//**
* @file max7300.h
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
* @brief Header file for Max7300 class
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


#ifndef MAX7300_H
#define MAX7300_H

#include "Arduino.h"
#include "Wire.h"


class Max7300
{
    public:
    
    typedef enum
    {
        MAX7300_I2C_ADRS0 = 0x40,
        MAX7300_I2C_ADRS1,
        MAX7300_I2C_ADRS2,
        MAX7300_I2C_ADRS3,
        MAX7300_I2C_ADRS4,
        MAX7300_I2C_ADRS5,
        MAX7300_I2C_ADRS6,
        MAX7300_I2C_ADRS7,
        MAX7300_I2C_ADRS8,
        MAX7300_I2C_ADRS9,
        MAX7300_I2C_ADRS10,
        MAX7300_I2C_ADRS11,
        MAX7300_I2C_ADRS12,
        MAX7300_I2C_ADRS13,
        MAX7300_I2C_ADRS14,
        MAX7300_I2C_ADRS15
    }max7300_i2c_adrs_t;
    
    
    typedef enum
    {
        MAX7300_PORT_OUTPUT = 1,
        MAX7300_PORT_INPUT,
        MAX7300_PORT_INPUT_PULLUP
    }max7300_port_type_t;
        
    
    typedef enum
    {
        MAX7300_PORT_04 = 4,
        MAX7300_PORT_05,
        MAX7300_PORT_06,
        MAX7300_PORT_07,
        MAX7300_PORT_08,
        MAX7300_PORT_09,
        MAX7300_PORT_10,
        MAX7300_PORT_11,
        MAX7300_PORT_12,
        MAX7300_PORT_13,
        MAX7300_PORT_14,
        MAX7300_PORT_15,
        MAX7300_PORT_16,
        MAX7300_PORT_17,
        MAX7300_PORT_18,
        MAX7300_PORT_19,
        MAX7300_PORT_20,
        MAX7300_PORT_21,
        MAX7300_PORT_22,
        MAX7300_PORT_23,
        MAX7300_PORT_24,
        MAX7300_PORT_25,
        MAX7300_PORT_26,
        MAX7300_PORT_27,
        MAX7300_PORT_28,
        MAX7300_PORT_29,
        MAX7300_PORT_30,
        MAX7300_PORT_31
    }max7300_port_number_t;
    

    /**********************************************************//**
    * @brief Constructor for Max7300 Class.  
    * 
    * @details
    *
    * On Entry:
    *
    * On Exit:
    *    @return none
    **************************************************************/
    Max7300();

    
    /**********************************************************//**
    * @brief Use in setup
    * 
    * @details 
    *
    * On Entry:
    *     @param[in] i2c_adrs - 7-bit slave address of MAX7300
    *
    * On Exit:
    *    @return none
    **************************************************************/
    void begin(max7300_i2c_adrs_t i2c_adrs);
    
    
    /**********************************************************//**
    * @brief Calls Wire.end() 
    *
    * @details 
    *
    * On Entry:
    *
    * On Exit:
    *    @return none
    **************************************************************/
    void end();
    
    
    /**********************************************************//**
    * @brief Enables MAX7300 GPIO Ports  
    *
    * @details Sets 'S' bit of configuration register
    *
    * On Entry:
    *
    * On Exit:
    *    @return 0 on success, non-0 on failure
    **************************************************************/
    uint8_t enable_ports(void);
    
    
    /**********************************************************//**
    * @brief Disables MAX7300 GPIO Ports 
    *
    * @details Clears 'S' bit of configuration register
    *
    * On Entry:
    *
    * On Exit:
    *    @return 0 on success, non-0 on failure 
    **************************************************************/
    uint8_t disable_ports(void);
    
    
    /**********************************************************//**
    * @brief Enables Transition Detection
    *
    * @details Sets 'M' bit of configuration register
    *
    * On Entry:
    *
    * On Exit:
    *    @return 0 on success, non-0 on failure
    **************************************************************/
    uint8_t enable_transition_detection(void);
    
    
    /**********************************************************//**
    * @brief Disables Transition Detection
    *
    * @details Clears 'M' bit of configuration register
    *
    * On Entry:
    *
    * On Exit:
    *    @return 0 on success, non-0 on failure
    **************************************************************/
    uint8_t disable_transition_detection(void);
    
    
    /**********************************************************//**
    * @brief Configures a single MAX7300 GPIO port
    *
    * @details  Configures MAX7300 GPIO port as either an output,
    *           input, or input with pullup.
    *
    * On Entry:
    *     @param[in] port_num - GPIO port to configure
    *     @param[in] port_type - One of the following port types
    *                            MAX7300_PORT_OUTPUT
    *                            MAX7300_PORT_INPUT
    *                            MAX7300_PORT_INPUT_PULLUP
    *
    * On Exit:
    *    @return 0 on success, non-0 on failure
    **************************************************************/
    uint8_t config_port(max7300_port_number_t port_num, max7300_port_type_t port_type);
    
    
    /**********************************************************//**
    * @brief Configure 4 MAX7300 GPIO ports
    *
    * @details  Allows user to configure 4 ports at a time
    *
    * On Entry:
    *    @param[in] low_port - lowest of 4 ports to configure, 
    *                          on 4 port boundaries as in datasheet
    *
    *    @param[in] data - Byte with each ports desired type with 
    *                      the following format - xx|xx|xx|xx
    *
    * On Exit:
    *    @return 0 on success, non-0 on failure
    **************************************************************/
    uint8_t config_4_ports(max7300_port_number_t low_port, uint8_t data);
    
    
    /**********************************************************//**
    * @brief Configures all MAX7300 GPIO ports
    *
    * @details  Allows user to configure all ports to a single type
    *
    * On Entry:
    *    @param[in] port_type - One of the following port types
    *                            MAX7300_PORT_OUTPUT
    *                            MAX7300_PORT_INPUT
    *                            MAX7300_PORT_INPUT_PULLUP
    *
    * On Exit:
    *    @return 0 on success, non-0 on failure
    **************************************************************/
    uint8_t config_all_ports(max7300_port_type_t port_type);
    
    
    /**********************************************************//**
    * @brief Read a single MAX7300 GPIO port
    *
    * @details
    *
    * On Entry:
    *    @param[in] port_num - MAX7300 port number to read
    *
    * On Exit:
    *    @return state of port, or -1 on failure
    **************************************************************/
    uint8_t read_port(max7300_port_number_t port_num);
    
    
    /**********************************************************//**
    * @brief Write a single MAX7300 GPIO port
    *
    * @details
    *
    * On Entry:
    *    @param[in] port_num - MAX7300 port to write
    *    @param[in] data - lsb of byte is written to port
    *
    * On Exit:
    *    @return 0 on success, non-0 on failure
    **************************************************************/
    uint8_t write_port(max7300_port_number_t port_num, uint8_t data);
    
    
    /**********************************************************//**
    * @brief Read 8 MAX7300 GPIO ports
    *
    * @details
    *
    * On Entry:
    *    @param[in] low_port - lowest port of 8 ports to read, 
    *                          on 8 port boundaries as in datasheet.
    *                          Max is port 24
    *
    * On Exit:
    *    @return state of ports, or -1 on failure
    **************************************************************/
    uint8_t read_8_ports(max7300_port_number_t low_port);
    
    
    /**********************************************************//**
    * @brief Write 8 MAX7300 GPIO ports
    *
    * @details
    *
    * On Entry:
    *    @param[in] low_port - lowest port of 8 ports to write, 
    *                          on 8 port boundaries as in datasheet.
    *                          Max is port 24
    *
    *    @param[in] data - Data is written to ports
    *
    * On Exit:
    *    @return 0 on success, non-0 on failure
    **************************************************************/
    uint8_t write_8_ports(max7300_port_number_t low_port, uint8_t data);
    
    
     /**********************************************************//**
    * @brief Read transition detection mask register
    *
    * @details See page 11 of DS, right hand side column, paragraph 2
    *          for details on one-shot event.
    *          
    * On Entry:
    *    @param[in] enable_snapshot - true to re-enable transition
    *                                 detection
    *
    * On Exit:
    *    @return contents of mask register, or -1 on failure
    **************************************************************/
    uint8_t read_mask_register(bool enable_snapshot);
    
    
    /**********************************************************//**
    * @brief Write transition detection mask register
    *
    * @details Enables transition detection on Ports 30-24
    *          
    *
    * On Entry:
    *    @param[in] data - Bits to set
    *
    * On Exit:
    *    @return 0 on success, non-0 on failure
    **************************************************************/
    uint8_t write_mask_register(uint8_t data);
    
    
    private:
    
    max7300_i2c_adrs_t _i2c_adrs;
    
    uint8_t write_config_register(bool set_clear, uint8_t data);
    
    uint8_t i2c_write(uint8_t adrs, const char *p_data_buff, uint8_t num_bytes);
    uint8_t i2c_read(uint8_t adrs, char *p_data_buff, uint8_t num_bytes);
    
};
#endif /* MAX7300_H*/
