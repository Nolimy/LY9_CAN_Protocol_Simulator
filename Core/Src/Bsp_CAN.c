#include "Bsp_CAN.h"

#define Transmitter 1
#define Receiver    0

void CANFilter_Config(void)//无论发啥我都照单全收。
{
    CAN_FilterTypeDef  sFilterConfig;
    
    sFilterConfig.FilterBank = 0;                       //CAN过滤器编号，范围0-27
    sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;   //CAN过滤器模式，掩码模式或列表模式
    sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;  //CAN过滤器尺度，16位或32位
    sFilterConfig.FilterIdHigh = 0x000 << 5;			//32位下，存储要过滤ID的高16位
    sFilterConfig.FilterIdLow = 0x0000;					//32位下，存储要过滤ID的低16位
    sFilterConfig.FilterMaskIdHigh = 0x0000;			//掩码模式下，存储的是掩码
    sFilterConfig.FilterMaskIdLow = 0x0000;
    sFilterConfig.FilterFIFOAssignment = 0;				//报文通过过滤器的匹配后，存储到哪个FIFO
    sFilterConfig.FilterActivation = ENABLE;    		//激活过滤器
    sFilterConfig.SlaveStartFilterBank = 0;
    
    if (HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig) != HAL_OK) {
        printf("CAN Filter Config Fail!\r\n");
        Error_Handler();
    }
    printf("CAN Filter Config Success!\r\n");

}
void CAN1_Send_Test()
{
	uint8_t data[4] = {0x01, 0x02, 0x03, 0x04};
    
  TxMessage.IDE = CAN_ID_STD;     //设置ID类型
	TxMessage.StdId = 0x222;        //设置ID号
  TxMessage.RTR = CAN_RTR_DATA;   //设置传送数据帧
	TxMessage.DLC = 4;              //设置数据长度
    
	if (HAL_CAN_AddTxMessage(&hcan1, &TxMessage, data, (uint32_t*)CAN_TX_MAILBOX0) != HAL_OK) {
        printf("CAN send test data fail!\r\n");
        Error_Handler();
    }
    printf("CAN send test data success!\r\n");
		
}
void CanFilterInit()
{
	usartTxFlag = 1;
	printf("----- CAN Test Board #1 -----\r\n");
	CANFilter_Config();
    
    /* 2. CAN Start */
	if (HAL_CAN_Start(&hcan1) != HAL_OK) {
			printf("CAN Start Fail\r\n");
			Error_Handler();
	}
	printf("CAN Start Success\r\n");
	
	/* 3. Enable CAN RX Interrupt */
	if (HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK) {
			printf("CAN_IT_RX_FIFO0_MSG_PENDING Enable Fail\r\n");
			Error_Handler();
	}
	printf("CAN_IT_RX_FIFO0_MSG_PENDING Enable Success\r\n");
}

/*
struct RacingCarData
{
	uint8_t FrontSpeed;          //前轮车速 在这里作为参考车速
	uint8_t PedalTravel;         //油门踏板开度 范围0~1000% 分辨率1%
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
*/


#ifdef Transmitter
struct RacingCarData racingCarData;
void carDataUpdate()//模拟汽车跑动数据
{
	racingCarData.FrontSpeed = ((racingCarData.lmotorSpeed + racingCarData.rmotorSpeed)/2)/
}

#endif

#ifdef Receiver


#endif
