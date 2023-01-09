#ifndef __BSP_BC260Y_H__
#define __BSP_BC260Y_H__

#include "stdio.h"
#include "string.h"
#include "usart.h"
#include "gpio.h"

#define RXBUFFERSIZE  256     //�������ֽ���

extern char RxBuffer1[RXBUFFERSIZE];   //��������
extern char RxBuffer3[RXBUFFERSIZE];   //��������
extern char Buffer[RXBUFFERSIZE];   //��������
extern uint8_t aRxBuffer1;   //�����жϻ���
extern uint8_t aRxBuffer3;   //�����жϻ���
extern uint8_t Uart1_Rx_Cnt;  //���ջ������
extern uint8_t Uart3_Rx_Cnt;  //���ջ������
extern uint8_t okFlag;

//FrontSpeed,PedalTravel,batAlarm,MotorSpeed,batTemp,batLevel,gearMode,carMode,timeCount,batVol,carTravel,mcu1Temp,mcu2Temp,breakTravel,lmotorTemp,rmotorTemp,lmotorSpeed,rmotorSpeed,motorTemp
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

uint8_t BC260Y_init();
uint8_t MQTT_Init();
void mqttServiceStartup();
void jsonPack();

#endif //__BSP_BC260Y_H__

