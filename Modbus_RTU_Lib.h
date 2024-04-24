#ifndef __MODBUS_RTU_LIB__
#define	__MODBUS_RTU_LIB__

#include "main.h"

extern UART_HandleTypeDef huart1;

#define READ_HOLDING_REGISTER	0x03

//#define MASTER	1
#define	SLAVE		0

uint16_t CRC16_Check_A(uint8_t Num, uint8_t buffer[]);
#ifdef	MASTER
void ModbusMasterTransmitt(uint8_t slaveAddress, uint8_t funcCode, uint8_t addressRegister[], uint8_t numberOfReg[]);
uint8_t ModbusMasterReceive(uint8_t data[], uint16_t* real_data);
#endif

#ifdef SLAVE
uint8_t ModbusSlaveReceive(uint8_t data_receive[], uint8_t slaveID);
void ModbusSlaveTransmitt(uint8_t data_receive[], uint16_t data[]);
#endif

#endif
