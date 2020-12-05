/*
 * Motor.hpp
 *
 *  Created on: 2019/05/01
 *      Author: �T��
 */

#ifndef INC_MOTOR_MOTOR_HPP_
#define INC_MOTOR_MOTOR_HPP_
#include "stm32f3xx.h"
#include "tim.h"
class Motor
{
protected:

	TIM_HandleTypeDef *Mhandler;
	GPIO_TypeDef *GPIOx;
	unsigned short pin;
	unsigned int channel;
	void HAL_TIM_SetCompare(TIM_HandleTypeDef *htim,int channel, int compre);
	long map(float x, long in_min, long in_max, long out_min, long out_max)
		{
			return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
		}
public:
	Motor(TIM_HandleTypeDef *Mhand,GPIO_TypeDef *_GPIOx,unsigned short _pin,unsigned int _channel):
		Mhandler(Mhand),GPIOx(_GPIOx),pin(_pin),channel(_channel)
	{

	}
	virtual ~Motor(){
	}
	void setDuty(float d);
	void SetFrequency(long freq);
	void Begin();

};

class BLMotor:public Motor
{
private:
	GPIO_TypeDef *coast;
	unsigned short coastpin;
public:
	BLMotor(TIM_HandleTypeDef *Mhand,GPIO_TypeDef *_GPIOx,GPIO_TypeDef *_coast,unsigned short _pin,unsigned short _coastpin,unsigned int _channel):
		Motor(Mhand,_GPIOx,_pin,_channel),coast(_coast),coastpin(_coastpin)
	{

	}

	void SetFree();
};

#endif /* INC_MOTOR_MOTOR_HPP_ */
