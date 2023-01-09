#ifndef __BSP_CAN_H__
#define __BSP_CAN_H__

#include "can.h"
#include "main.h"
#include "stdio.h"
#include "usart.h"


static CAN_TxHeaderTypeDef        TxMessage;    //CAN���͵���Ϣ����Ϣͷ
static CAN_RxHeaderTypeDef        RxMessage;    //CAN���յ���Ϣ����Ϣͷ

void CAN1_Send_Test();

void CANFilter_Config(void);
void CanFilterInit(void);

struct RacingCarData
{
	uint8_t FrontSpeed;          //ǰ�ֳ��� ��������Ϊ�ο�����
	uint8_t PedalTravel;         //����̤�忪��
	uint8_t brakeTravel;         //ɲ��̤�忪��
	uint8_t batAlarm;            //��ظ澯
	uint8_t batTemp;             //����¶�
	uint8_t batLevel;            //��ص���
	uint8_t batVol;              //��ص�ѹ
	uint8_t gearMode;            //��λ��Ϣ
	uint8_t carMode;             //��������ģʽ
	uint8_t timeCount;           //����ʱ��
	uint8_t carTravel;           //�����ܶ�����
	uint8_t mcu1Temp;            //���������1�¶�
	uint8_t mcu2Temp;            //���������2�¶�
	uint8_t lmotorTemp;          //�����¶�
	uint8_t rmotorTemp;          //�ҵ���¶�
	uint8_t lmotorSpeed;         //����ת��
	uint8_t rmotorSpeed;         //�ҵ��ת��
	
};
extern struct RacingCarData racingCarData;
#endif //__BSP_CAN_H__
