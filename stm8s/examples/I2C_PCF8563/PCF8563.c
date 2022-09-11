/*
 * PCF8563.c
 *
 * Created: 2014-08-19 13:00:51
 *  Author: tmf
 */ 

#include <stdint.h>
#include "i2c.h"
#include "PCF8563.h"


void PCF8563_WriteRegister(uint8_t reg, uint8_t value)
{
    i2c_start();
    i2c_write_addr(PCF8563_ADDR | I2C_WRITE);
    i2c_write(reg);
    i2c_write(value);
    i2c_stop();
}

uint8_t PCF8563_ReadRegister(uint8_t reg)
{
    i2c_start();
    i2c_write_addr(PCF8563_ADDR | I2C_WRITE);
    i2c_write(reg);
    i2c_stop();

    i2c_start();
    i2c_write_addr(PCF8563_ADDR | I2C_READ);
    return i2c_read();
}

uint8_t PCF8563_IsDataValid()
{
	return ((PCF8563_ReadRegister(SecondsReg) & PCF_TimeValid)==0);
}

void PCF8563_SetTime(Time *time)
{
    i2c_start();
    i2c_write_addr(PCF8563_ADDR | I2C_WRITE);
    i2c_write(SecondsReg);
    i2c_write(time->Second);
    i2c_write(time->Minute);
    i2c_write(time->Hour);
    i2c_stop();
}

void PCF8563_GetTime(Time *time)
{
    i2c_start();
    i2c_write_addr(PCF8563_ADDR | I2C_WRITE);
    i2c_write(SecondsReg);
    i2c_stop();

    i2c_start();
    i2c_write_addr(PCF8563_ADDR | I2C_READ);

    uint8_t buf[3];
    i2c_read_arr(buf, 3);
    time->Second = buf[0];
	time->Minute = buf[1];
	time->Hour = buf[2] & 0b111111;
}

// void PCF8563_SetDate(Date *date)
// {
// 	I2C_SendStartAndSelect(PCF8563_Addr | TW_WRITE);
// 	I2C_SendByte(DaysReg);
// 	I2C_SendByte(date->Day);
// 	I2C_SendByte(date->WeekDay);
// 	I2C_SendByte(date->Month);
// 	I2C_SendByte(date->Year);
// 	I2C_Stop();
// }

// void PCF8563_GetDate(Date *date)
// {
// 	I2C_SendStartAndSelect(PCF8563_Addr | TW_WRITE);
// 	I2C_SendByte(DaysReg);
// 	I2C_SendStartAndSelect(PCF8563_Addr | TW_READ);
// 	date->Day=I2C_ReceiveData_ACK() & 0x3F;
// 	date->WeekDay=I2C_ReceiveData_ACK() & 0x07;
// 	date->Month=I2C_ReceiveData_ACK() & 0x1F;
// 	date->Year=I2C_ReceiveData_NACK();
// 	I2C_Stop();
// }