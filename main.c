#include "main.h"
#include "Modbus_RTU_Lib.h"

uint8_t dataSend[8];
uint8_t dataReceive[256];
uint16_t realData[256];

// Config the UART first
int main(void)
{
    uint8_t startReg[2] = {0x00, 0x00};
	uint8_t numReg[2] = {0x00, 0x05};
	ModbusMasterTransmitt(5, 3, startReg, numReg, dataSend);

    while(1)
    {
        HAL_UART_Transmit(&huart1, dataSend, sizeof(dataSend), 100);
		HAL_UART_Receive(&huart1, dataReceive, sizeof(dataReceive), 100);
		correct = ModbusMasterReceive(dataReceive, realData);
		
		if(correct != 1)	break;
		HAL_Delay(2);
    }
    return 0;
}