/*
 * my_lis302dl.h
 *
 *  Created on: Feb 14, 2024
 *      Author: turkm
 */

#ifndef STM32F4XX_HAL_DRIVER_INC_MY_LIS302DL_H_
#define STM32F4XX_HAL_DRIVER_INC_MY_LIS302DL_H_

#include "stm32f4xx_hal.h"

/*LIS302DL register addresses*/

#define CTRL_REG1 					0x20  					//control register1 address
#define CTRL_REG2					0x21					//control register2 address
#define STATUS_REG					0x27					//status register address
#define OUT_X						0x29					//Address of the x-axis
#define OUT_Y						0x2B                    //Address of the x-axis
#define OUT_Z						0x2D                    //Address of the x-axis

/*
 * @defgroup Data_rate_define
 *
 * */

#define DATA_RATE_100HZ				((uint8_t)0x00)			// 100 Hz data rate
#define DATA_RATE_400HZ				((uint8_t)0x80)			// 400 Hz data rate


/*
 * @defgroup power_mode_define
 *
 * */


#define POWER_DOWN_MODE				((uint8_t)0x00)			// power down mode
#define POWER_ACTIVE_MODE			((uint8_t)0x40)			// power active mode


/*
 * @defgroup Full_scale_define
 *
 * */


#define FUL_SCALE_2G				((uint8_t)0x00)			// full scale 2g
#define FUL_SCALE_8G				((uint8_t)0x20)			// full scale 4g


/*
 * @defgroup self_test_define
 *
 * */


#define SELF_TEST_NORMAL			((uint8_t)0x00)			// self test mode disable (normal mode )

/*
 * @defgroup xyz_axis_define
 *
 * */

#define XYZ_ENABLE					((uint8_t)0x07)			// x,y,z axis enable

/*
 * @defgroup sensitivity_define
 *
 * */

#define LIS302DL_SENSITIVITY		64.8f          			//64.8 mg/digit


/*
 * @brief LIS302DL Init structure definition
 *
 * */


typedef struct{

	uint8_t Data_Rate;										//data rate selection @ref Data_rate_define
	uint8_t Power_Mode;										//data rate selection @ref power_mode_define
	uint8_t Full_Scale_Mode;								//data rate selection @ref Full_scale_define
	uint8_t Self_Test_Mode;									//data rate selection @ref self_test_define
	uint8_t Axis_Mode;										//data rate selection @ref xyz_axis_define

}Lis302dl_InitTypeDef;


/*
 * @brief Data structure for recording x, y, and z axes
 *
 * */

typedef struct{
	uint16_t x;
	uint16_t y;
	uint16_t z;
}LIS302DL_DataRaw;


/* Function Statements  */

void Lis302dl_Init(Lis302dl_InitTypeDef*pBuffer);
void Lis302dl_Write(uint8_t*pBuffer,uint8_t data_Addr, uint16_t size);
void Lis302dl_Read(uint8_t*pbuffer,uint8_t data_Addr, uint16_t size);
uint8_t   LIS302DL_X_calibrate(void);
uint8_t  LIS302DL_Y_calibrate(void);
LIS302DL_DataRaw LIS302DL_GetDataRaw(void);



#endif /* STM32F4XX_HAL_DRIVER_INC_MY_LIS302DL_H_ */
