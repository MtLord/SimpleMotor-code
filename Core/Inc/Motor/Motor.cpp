/*
 * Motor.cpp
 *
 *  Created on: 2019/05/01
 *      Author: �T��
 */

#include "Motor.hpp"




void Motor::setDuty(float d)
{
		if(d>=0)
		{
			HAL_GPIO_WritePin(GPIOx,pin,GPIO_PIN_RESET);
			HAL_TIM_SetCompare(Mhandler,channel,map(d,0,100,0,Mhandler->Instance->ARR));

		}

		else if(d<0)
		{
			HAL_GPIO_WritePin(GPIOx,pin,GPIO_PIN_SET);
			HAL_TIM_SetCompare(Mhandler,channel,map(-d,0,100,0,Mhandler->Instance->ARR));
		}
}

void BLMotor::SetFree()
{
	HAL_GPIO_WritePin(coast,pin,GPIO_PIN_SET);
}



void Motor::Begin()
{
	HAL_TIM_PWM_Start(Mhandler,channel) ;       //HAL�̎d�l
	HAL_GPIO_WritePin(GPIOx,pin,GPIO_PIN_RESET);
}

void Motor::SetFrequency(long freq)
{
		float freqency=freq;
		unsigned short counterperiod=0;
		unsigned short Prescaler=0;
		float ajustfreq=0;
		long sysclock=0;
			sysclock=HAL_RCC_GetPCLK1Freq();

		while(ajustfreq!=freqency)
				{
					Prescaler++;
				for(counterperiod=0;counterperiod<65535;counterperiod++)
				{
					ajustfreq=(float)sysclock/((float)Prescaler*((float)counterperiod+1));
					if(ajustfreq==freqency)
					{
						break;
					}
				}

				}
		Mhandler->Instance->PSC=(unsigned short)Prescaler-1;
		Mhandler->Instance->ARR=(unsigned short)counterperiod;
}

void Motor::HAL_TIM_SetCompare(TIM_HandleTypeDef *htim,int channel, int compre)
{
	switch(channel)
	{
	case TIM_CHANNEL_1:
		htim->Instance->CCR1=compre;
		break;
	case TIM_CHANNEL_2:
			htim->Instance->CCR2=compre;
			break;
	case TIM_CHANNEL_3:
			htim->Instance->CCR3=compre;
			break;
	case TIM_CHANNEL_4:
			htim->Instance->CCR4=compre;
			break;
	case TIM_CHANNEL_5:
			htim->Instance->CCR5=compre;
			break;
	case TIM_CHANNEL_6:
			htim->Instance->CCR6=compre;
			break;

	}

}
