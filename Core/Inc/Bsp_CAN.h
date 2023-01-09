#ifndef __BSP_CAN_H__
#define __BSP_CAN_H__

#include "can.h"
#include "main.h"
#include "stdio.h"
#include "usart.h"


static CAN_TxHeaderTypeDef        TxMessage;    //CAN发送的消息的消息头
static CAN_RxHeaderTypeDef        RxMessage;    //CAN接收的消息的消息头

void CAN1_Send_Test();

void CANFilter_Config(void);
void CanFilterInit(void);

struct RacingCarData
{
	uint8_t FrontSpeed;          //前轮车速 在这里作为参考车速
	uint8_t PedalTravel;         //油门踏板开度
	uint8_t brakeTravel;         //刹车踏板开度
	uint8_t batAlarm;            //电池告警
	uint8_t batTemp;             //电池温度
	uint8_t batLevel;            //电池电量
	uint8_t batVol;              //电池电压
	uint8_t gearMode;            //挡位信息
	uint8_t carMode;             //车辆运行模式
	uint8_t timeCount;           //运行时间
	uint8_t carTravel;           //车辆跑动距离
	uint8_t mcu1Temp;            //电机控制器1温度
	uint8_t mcu2Temp;            //电机控制器2温度
	uint8_t lmotorTemp;          //左电机温度
	uint8_t rmotorTemp;          //右电机温度
	uint8_t lmotorSpeed;         //左电机转速
	uint8_t rmotorSpeed;         //右电机转速
	
};
extern struct RacingCarData racingCarData;
#endif //__BSP_CAN_H__
