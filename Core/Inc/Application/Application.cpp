/*
 * Application.cpp
 *
 *  Created on: 2019/05/04
 *      Author: �T��
 */

#include "Application.hpp"
#include "DefineOrder.h"

#define BOARDID 1
extern unsigned char RxFIFO_Data[6];
extern CAN_RxHeaderTypeDef RXmsg;
extern bool CanRxFlag;

long tempID[20]={0,};
long count=0;
float App::RestoreData(int until)
{
	float temp_data=0;
	for(int i=0;i<until;i++){
		((unsigned char*)&temp_data)[i]=RxFIFO_Data[i];
	}
	return temp_data;
}


void App::SetDuty(float duty)
{
	switch(node_id)
	{
	case 1:
		plow->M1.setDuty(duty);
		break;
	case 2:
			plow->M2.setDuty(duty);
			break;
	case 3:
			plow->M3.setDuty(duty);
			break;
	case 4:
			plow->M4.setDuty(duty);
			break;
	case 17:
			plow->BL1.setDuty(duty);
			break;
	case 18:
			plow->BL2.setDuty(duty);
			break;

	}
}

void App::TaskShift()
{
	if(CanRxFlag)
	{
		if(RXmsg.ExtId>>ORDER_BIT_Pos==SET_DUTY)
		{
			this->node_id=(RXmsg.ExtId>>NODE_ID_Pos)&0xF;
			if((RXmsg.ExtId&0xF)==BOARDID)//ボード番号が自分のと一致したら
			{
				SetDuty(RestoreData(4));
			}
		}


		CanRxFlag=false;
	}

}


