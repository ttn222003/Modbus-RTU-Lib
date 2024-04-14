#ifndef __MODBUS_RTU_LIB__
#define	__MODBUS_RTU_LIB__

#include "main.h"

uint16_t CRC16_Check_A(uint8_t Num, uint8_t buffer[]);
void ModbusMasterTransmitt(uint8_t slaveAddress, uint8_t funcCode, uint8_t addressRegister[], uint8_t numberOfReg[], uint8_t* data);
uint8_t ModbusMasterReceive(uint8_t data[], uint16_t* real_data);

#endif
