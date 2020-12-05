/*
 * Application.cpp
 *
 *  Created on: 2019/05/04
 *      Author: �T��
 */

#include "Application.hpp"
#include "DefineOrder.h"
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
	case 5:
			plow->BL1.setDuty(duty);
			break;
	case 6:
			plow->BL2.setDuty(duty);
			break;

	}
}

void App::TaskShift()
{
	if(CanRxFlag)
	{
		if(RXmsg.ExtId>>ORDER_BIT_Pos==SET_DUTY)//����ID��SET_DUTY�Ɉ�v������
		{
			this->node_id=RXmsg.ExtId&0xF;//�m�[�hID����
			SetDuty(RestoreData(4));//4�o�C�g�ɕ����Ă����f�[�^�𕜌����ăf���[�e�B�Ƃ��ăZ�b�g
		}


		CanRxFlag=false;
	}

}


