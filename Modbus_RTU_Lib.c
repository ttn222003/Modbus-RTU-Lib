#include "Modbus_RTU_Lib.h"

uint16_t CRC16_Check_A(uint8_t Num, uint8_t buffer[]) //CRC 16 Modbus
{
	uint8_t x, y, i; 
	uint16_t Crc = 0xFFFF;
	
	for(x = 0; x < Num; ++x)
	{        
		 y = buffer[x];
		 Crc=Crc^y; //Calculate the CRC 
		 
		 for(i=8;i!=0;--i) //Shift Right
		 {
				if((Crc&0x0001)!=0) //If the LSB is set
				{ 
					 Crc>>=1; //Shift right and XOR 0xA001
					 Crc^=0xA001;
				}
				else //Else LSB is not set  
				{
					 Crc>>=1; //Just shift right
				}   
		 } 
	}
			 
	//Swapping of the high and low CRC bytes      
	return Crc;
}

// For peripheral use Modbus, register is 2 bytes data
void ModbusMasterTransmitt(uint8_t slaveAddress, uint8_t funcCode, uint8_t addressRegister[], uint8_t numberOfReg[], uint8_t* data)
{
	uint8_t frame_buffer[6];
	uint16_t crc = 0x00;
	
	// Add slave address to data frame
	*(data + 0) = slaveAddress;
	
	// Add function code to data frame
	*(data + 1) = funcCode;
	
	// Add address of register to data frame
	*(data + 2) = addressRegister[0];
	*(data + 3) = addressRegister[1];
	
	// Add number of register to data frame
	*(data + 4) = numberOfReg[0];
	*(data + 5) = numberOfReg[1];
	
	frame_buffer[0] = slaveAddress;
	frame_buffer[1] = funcCode;
	frame_buffer[2] = addressRegister[0];
	frame_buffer[3] = addressRegister[1];
	frame_buffer[4] = numberOfReg[0];
	frame_buffer[5] = numberOfReg[1];
	
	crc = CRC16_Check_A(6, frame_buffer);
	
	*(data + 6) = (uint8_t)(crc & 0xFF);
	*(data + 7) = (uint8_t)((crc >> 8) & 0xFF);
}

uint8_t ModbusMasterReceive(uint8_t data[], uint16_t* real_data)
{
	uint8_t len = data[2] / 2;
	uint8_t i = 3;
	uint8_t n = i;
	uint8_t len_frame_without_crc = 3 + len * 2;
	uint8_t receive_frame_without_crc[len_frame_without_crc];
	uint16_t crc_check;
	uint16_t crc_data;
	
	
	while(i < (len + 3))
	{
		*(real_data + i - 3) = (uint16_t)((data[n] << 8) | data[n + 1]);
		n = n + 2;
		i++;
	}
	
	for(uint8_t j = 0; j < len_frame_without_crc; j++)
	{
		receive_frame_without_crc[j] = data[j];
	}
	crc_check = CRC16_Check_A(len_frame_without_crc, receive_frame_without_crc);
	crc_check = ((crc_check << 8) & 0xFF00) | ((crc_check >> 8) & 0xFF);
	
	crc_data = (uint16_t)((data[3 + len * 2] << 8) | data[3 + len * 2 + 1]);
	
	if(crc_check == crc_data)	return 1;
	else											return 0;
}
