#include "Bsp_CAN.h"


void CANFilter_Config(void)
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