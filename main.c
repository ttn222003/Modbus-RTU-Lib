#include "main.h"
#include "Modbus_RTU_Lib.h"
#include "stdlib.h"

/********** Use as master ***********/
//uint8_t dataReceive[256];
//uint16_t realData[256];

/********** Use as slave ************/
uint8_t dataReceive[8];
uint8_t Data[256] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16};

// Config Interupt for UART first
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if(huart->Instance == USART1)
	{
		uint8_t correct;
		correct = ModbusSlaveReceive(dataReceive,5);
		
		ModbusSlaveTransmitt(dataReceive, Data);
	}
}

// Config the UART first
int main(void)
{
    /********** Use as master ***********/
//	uint8_t startReg[2] = {0x00, 0x00};
//	uint8_t numReg[2] = {0x00, 0x05};
//	uint8_t correct;

/********** Use as slave ************/
    while(1)
    {
        /********** Use as master ***********/
//		ModbusMasterTransmitt(5, 3, startReg, numReg);
//		HAL_UART_Receive(&huart1, dataReceive, sizeof(dataReceive), 100);
//		correct = ModbusMasterReceive(dataReceive, realData);
//		
//		if(correct != 1)	break;
//		HAL_Delay(2);
		
		/********** Use as slave ************/
		HAL_UART_Receive_IT(&huart1, dataReceive, sizeof(dataReceive));
		Data[1]++;
		Data[3]++;
		Data[5]++;
		Data[4]++;
		Data[9]++;
		Data[11]++;
		Data[13]++;
		Data[15]++;
    }
    return 0;
}