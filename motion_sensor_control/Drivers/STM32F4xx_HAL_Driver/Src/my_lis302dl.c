/*
 * my_lis302dl.c
 *
 *  Created on: Feb 14, 2024
 *      Author: turkm
 */

#include "my_lis302dl.h"
#include "main.h"
extern SPI_HandleTypeDef hspi1;
extern LIS302DL_DataRaw data;

/**
 * @brief LIS302DL LIS302DL_Init also starts according to the specified parameters.
 *
 * @param Configuration information for *pBuffer pointer of type Lis302dl_InitTypeDef, LIS302DL
 *
 * @retval none
 *
 * */


void Lis302dl_Init(Lis302dl_InitTypeDef*pBuffer){
	uint8_t reg;
	reg = (uint8_t)0x00;

	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET);
	reg |= (uint8_t)(pBuffer->Axis_Mode|pBuffer->Data_Rate|pBuffer->Full_Scale_Mode|pBuffer->Power_Mode|pBuffer->Self_Test_Mode);

	Lis302dl_Write(&reg,CTRL_REG1,1);
}


/*
 * @Brief LIS302DL used to write data and send configuration information
 *
 * @param The *pBuffer pointer of type uint8_t retrieves the configuration information it receives from the LIS302DL_Init
 *
 * @param Register address for data_addr LIS302DL
 *
 * @param It gets you the size information from the uint16_t type
 *
 * @retval none
 * */


void Lis302dl_Write(uint8_t*pBuffer,uint8_t data_Addr, uint16_t size){

     uint8_t data= data_Addr;

	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET);


	HAL_SPI_Transmit(&hspi1,&data,1,100);

	HAL_SPI_Transmit(&hspi1,pBuffer,size,100);

	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET);

}


/*
 * @Brief Reads from LIS302DL and retrieves data
 *
 * @param uint8_t type *pbuffer pointer stores the read data
 *
 * @param The data_Addr is specifies the register address to be read from lis302dl
 *
 * @param It gets you the size information from the uint16_t type
 *
 * @retval none
 * */

void Lis302dl_Read(uint8_t*pbuffer,uint8_t data_Addr, uint16_t size){

	uint8_t spiBuf[3];
	spiBuf[0] = data_Addr | 0x80;


	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET);

	HAL_SPI_Transmit(&hspi1, spiBuf, 1,100);

	HAL_SPI_Receive(&hspi1, spiBuf,size, 100);

	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET);

	for( uint8_t i = 0; i < ( size & 0x3 ); i++ ){
		pbuffer[i] = spiBuf[i];

	}

}


/*
 *@Brief Gets the values of the x, y, and z axes
 *
 *@param none
 *
 *@retval The return type is LIS302DL_DataRaw. The return value is tempDataRaw
 *
 * */


LIS302DL_DataRaw LIS302DL_GetDataRaw(void)
{
	uint8_t spiBuf[2];
	LIS302DL_DataRaw tempDataRaw;
	//Read X data
	Lis302dl_Read(spiBuf,OUT_X, 1);
	tempDataRaw.x = (spiBuf[0]);

	//Read Y data
	Lis302dl_Read(spiBuf,OUT_Y, 1);
	tempDataRaw.y =  spiBuf[0];



	return tempDataRaw;

}

/*
 * @Brief   LIS302DL_X_calibrate converts the value between 255 and 190 for the x-axis to a range of values
 * 						         between -1 and -65. otherwise, it reads a value in the range of 0 to 65
 *
 *@retval The return type is uint8_t. The return value is x
 *
 * */

uint8_t  LIS302DL_X_calibrate(void)
{

uint8_t x = data.x;

	if( (x  >= 0xBE) && (x <= 0xFF) )
	{
		data.x = ~(data.x) + 0x01;
		data.x |=0x80;

	}
return x ;

}

/*
 * @Brief LIS302DL_Y_calibrate converts the value between 255 and 190 for the x-axis to a range of values
 * 						         between -1 and -65. otherwise, it reads a value in the range of 0 to 65
 *
 * @retval The return type is uint8_t. The return value is y
 *
 * */

uint8_t  LIS302DL_Y_calibrate(void)
{

uint8_t y = data.y;

	if( (y  >= 0xBE) && (y <= 0xFF) )
	{
		data.y = ~(data.y) + 0x01;
		data.y |=0x80;

	}
return y ;

}





