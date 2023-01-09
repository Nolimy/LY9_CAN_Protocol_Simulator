#include "Bsp_CAN.h"

#define Transmitter 1
#define Receiver    0

void CANFilter_Config(void)//���۷�ɶ�Ҷ��յ�ȫ�ա�
{
    CAN_FilterTypeDef  sFilterConfig;
    
    sFilterConfig.FilterBank = 0;                       //CAN��������ţ���Χ0-27
    sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;   //CAN������ģʽ������ģʽ���б�ģʽ
    sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;  //CAN�������߶ȣ�16λ��32λ
    sFilterConfig.FilterIdHigh = 0x000 << 5;			//32λ�£��洢Ҫ����ID�ĸ�16λ
    sFilterConfig.FilterIdLow = 0x0000;					//32λ�£��洢Ҫ����ID�ĵ�16λ
    sFilterConfig.FilterMaskIdHigh = 0x0000;			//����ģʽ�£��洢��������
    sFilterConfig.FilterMaskIdLow = 0x0000;
    sFilterConfig.FilterFIFOAssignment = 0;				//����ͨ����������ƥ��󣬴洢���ĸ�FIFO
    sFilterConfig.FilterActivation = ENABLE;    		//���������
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
    
  TxMessage.IDE = CAN_ID_STD;     //����ID����
	TxMessage.StdId = 0x222;        //����ID��
  TxMessage.RTR = CAN_RTR_DATA;   //���ô�������֡
	TxMessage.DLC = 4;              //�������ݳ���
    
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
	uint8_t FrontSpeed;          //ǰ�ֳ��� ��������Ϊ�ο�����
	uint8_t PedalTravel;         //����̤�忪�� ��Χ0~1000% �ֱ���1%
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
*/


#ifdef Transmitter
struct RacingCarData racingCarData;
void carDataUpdate()//ģ�������ܶ�����
{
	racingCarData.FrontSpeed = ((racingCarData.lmotorSpeed + racingCarData.rmotorSpeed)/2)/
}

#endif

#ifdef Receiver


#endif
