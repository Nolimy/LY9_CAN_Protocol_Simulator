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

#endif //__BSP_CAN_H__
