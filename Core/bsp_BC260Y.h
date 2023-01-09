#ifndef __BSP_BC260Y_H__
#define __BSP_BC260Y_H__

#include "stdio.h"
#include "string.h"
#include "usart.h"
#include "gpio.h"

#define RXBUFFERSIZE  256     //最大接收字节数

extern char RxBuffer1[RXBUFFERSIZE];   //接收数据
extern char RxBuffer3[RXBUFFERSIZE];   //接收数据
extern char Buffer[RXBUFFERSIZE];   //接收数据
extern uint8_t aRxBuffer1;   //接收中断缓冲
extern uint8_t aRxBuffer3;   //接收中断缓冲
extern uint8_t Uart1_Rx_Cnt;  //接收缓冲计数
extern uint8_t Uart3_Rx_Cnt;  //接收缓冲计数
extern uint8_t okFlag;

//FrontSpeed,PedalTravel,batAlarm,MotorSpeed,batTemp,batLevel,gearMode,carMode,timeCount,batVol,carTravel,mcu1Temp,mcu2Temp,breakTravel,lmotorTemp,rmotorTemp,lmotorSpeed,rmotorSpeed,motorTemp
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

uint8_t BC260Y_init();
uint8_t MQTT_Init();
void mqttServiceStartup();
void jsonPack();

#endif //__BSP_BC260Y_H__

