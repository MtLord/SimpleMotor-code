/*
 * LowlayerHandel.hpp
 *
 *  Created on: 2019/05/01
 *      Author: �T��
 */

#ifndef INC_LOWLAYERHANDEL_HPP_
#define INC_LOWLAYERHANDEL_HPP_
#include "Motor/Motor.hpp"
#include "CAN/CAN.hpp"
#include "stm32f3xx_hal.h"
#include "tim.h"
#include "main.h"
#include "stm32f3xx_hal_can.h"
class LowlayerHandelTypedef
{
public:

	Motor M1,M2,M3,M4;
	BLMotor BL1,BL2;
	CanBus extcan;
	CanBus stdcan;
	LowlayerHandelTypedef():
	M1(&htim2,GPIOA,GPIO_PIN_5,TIM_CHANNEL_1),
	M2(&htim2,GPIOA,GPIO_PIN_7,TIM_CHANNEL_2),
	M3(&htim2,GPIOB,GPIO_PIN_0,TIM_CHANNEL_3),
	M4(&htim2,GPIOB,GPIO_PIN_1,TIM_CHANNEL_4),
	BL1(&htim3,GPIOA,GPIOA,GPIO_PIN_8,GPIO_PIN_9,TIM_CHANNEL_1),
	BL2(&htim3,GPIOA,GPIOB,GPIO_PIN_10,GPIO_PIN_4,TIM_CHANNEL_2),
	extcan(CAN_ID_EXT,CAN_RTR_DATA),stdcan(CAN_ID_STD,CAN_RTR_DATA)
	{

	}
	void LedCheck()
	{
		HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_7);
		HAL_Delay(500);
	}
	void DebugMotor(int num,float duty)
	{
		switch(num)
		{
		case 1:
			M1.setDuty(duty);
			break;
		case 2:
			M2.setDuty(duty);
			break;
		case 3:
			M3.setDuty(duty);
			break;
		case 4:
			M4.setDuty(duty);
			break;
		case 5:

			break;
		case 6:

			break;
		case 7:

			break;
		case 8:

			break;
		}
	}
};
//CAN_ID_EXT


#endif /* INC_LOWLAYERHANDEL_HPP_ */
