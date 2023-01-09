#include "bsp_BC260Y.h"

char *MQTT_IP="\"82.156.207.102\"";
#define MQTT_PORT      "1883"
#define MQTT_User      "lingyun"
#define MQTT_Passwd    "lingyun666"
#define MQTT_ClientID  "BC260Y"
#define MQTT_OPEN_CMD  "AT+QMTOPEN=0,"
#define MQTT_CONN_CMD  "AT+QMTCONN=0,"

char RxBuffer1[RXBUFFERSIZE];   //��������
char RxBuffer3[RXBUFFERSIZE];   //��������
uint8_t aRxBuffer1;   //�����жϻ���
uint8_t aRxBuffer3;   //�����жϻ���
char Buffer[RXBUFFERSIZE];
uint8_t Uart1_Rx_Cnt = 0;  //���ջ������
uint8_t Uart3_Rx_Cnt = 0;  //���ջ������
uint8_t okFlag = 0; //�Ƿ��ѯOK�ַ���־λ

struct RacingCarData racingCarData;
/*ʧ�ܣ� 0  �ɹ� �� 1  */
uint8_t cmdToBC26Y(char *strSource, char *strTarget, uint8_t okCheck)
{
	char *strBuffer;
	uint8_t i = 0;
	memset(Buffer,0x00,sizeof(Buffer)); //�������
	if(okCheck == 0)
	{
		strBuffer = NULL;
		printf("%s\r\n", strSource);
		HAL_Delay(500);
		while(strBuffer == NULL && i<5)
		{
			strBuffer = strstr((const char*)Buffer,(const char*)strTarget);
			usartTxFlag = 1;
			printf("Buffer is %s\r\n",Buffer);
			//printf("strBuffer %s\r\n",strBuffer);
			memset(Buffer,0x00,sizeof(Buffer)); //�������
			usartTxFlag = 2;
			printf("%s\r\n", strSource);
			HAL_Delay(600);
			i++;
			//printf("sending %s\r\n",strSource);		
		}
		if(i >= 5)
		{
			usartTxFlag = 1;
			printf("%s init ERROR \r\n",strSource);
			return 0;
		}
		else
		{
			usartTxFlag = 1;
			printf("%s init OK \r\n",strSource);
			return 1;
		}
	}
	else
	{
		while(okFlag != 1 && i<5)
		{
			usartTxFlag = 2;
			printf("%s\r\n", strSource);
			HAL_Delay(200);
			usartTxFlag = 1;
			printf("sending %s\r\n",strSource);	
			i++;
		}
		if(i >= 5)
		{
			usartTxFlag = 1;
			printf("%s init ERROR \r\n",strSource);
			okFlag = 0;
			return 0;
		}
		else
		{
			usartTxFlag = 1;
			okFlag = 0;
			printf("%s init OK \r\n",strSource);
			return 1;
		}				
	}
}

//��������AT�������η��ͳ�ȥ��Ȼ���ж�buffer��������Ҫ�Ĺؼ��֡�
//return 0:ʧ��  1���ɹ�
uint8_t BC260Y_init()
{
	//4Gģ�鿪��
	HAL_GPIO_WritePin(PWR_4G_GPIO_Port, PWR_4G_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RST_4G_GPIO_Port, RST_4G_Pin, GPIO_PIN_SET);
	HAL_Delay(500);
	HAL_GPIO_WritePin(RST_4G_GPIO_Port, RST_4G_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PWR_4G_GPIO_Port, PWR_4G_Pin, GPIO_PIN_RESET);
	HAL_Delay(5000);
  //���ݻ���  
	memset(Buffer,0x00,sizeof(Buffer)); //�������
//	cmdToBC26Y("AT+CIMI","460",0);
//	cmdToBC26Y("AT+QSCLK = 0",NULL, 1);
//	cmdToBC26Y("AT+CSQ","CSQ",0);
	return cmdToBC26Y("AT+CIMI","460",0) & cmdToBC26Y("AT+QSCLK = 0",NULL, 1) & cmdToBC26Y("AT+CSQ","CSQ",0); //��0�򷵻�ʧ�� ȫ1��ɹ�
}
//AT+QMTOPEN=0,"82.156.207.102",1883
//AT+QMTCONN=0,"BC260Y","lingyun","lingyun666"
uint8_t MQTT_Init()
{
//	cmdToBC26Y("AT+QMTOPEN=0,\"82.156.207.102\",1883", "N: 0,0", 0);
//	cmdToBC26Y("AT+QMTCONN=0,\"BC260Y\",\"lingyun\",\"lingyun666\"", "N: 0,0", 0);
	return cmdToBC26Y("AT+QMTOPEN=0,\"82.156.207.102\",1883", "N: 0,0", 0)\
					& cmdToBC26Y("AT+QMTCONN=0,\"BC260Y\",\"lingyun\",\"lingyun666\"", "N: 0,0", 0)\
					& cmdToBC26Y("AT+QMTPUB=0,0,0,1,\"hello\",11,\"hello world\"","0,0,0", 0);
}

void mqttServiceStartup()
{
	uint8_t initFlag;
	initFlag = BC260Y_init();
	if(initFlag == 1)
	{
		usartTxFlag = 1;
		printf("*********************BC260Y INIT OK*********************\r\n");
	}
	
	else
	{
		usartTxFlag = 1;
		printf("*********************BC260Y Init Failure!*********************\r\n");
	}	
	
	initFlag = MQTT_Init();
	if(initFlag == 1)
	{
		usartTxFlag = 1;
		printf("*********************MQTT INIT OK*********************\r\n");
	}
	
	else
	{
		usartTxFlag = 1;
		printf("*********************MQTT Init Failure!*********************\r\n");
	}	
}
void MQTT_Pubdata(char *json)
{
	usartTxFlag = 2;
	char overCh = 0x1a;
	printf("AT+QMTPUB=0,0,0,1,\"hello\"\r\n");//��������
	HAL_Delay(10);
	printf("%s\r\n",json);
	printf("%c", overCh);
}
//FrontSpeed,PedalTravel,batAlarm,MotorSpeed,batTemp,batLevel,gearMode,carMode,time_Count,batVol,carTravel,mcu1Temp,mcu2Temp,breakTravel,lmotorTemp,rmotorTemp,lmotorSpeed,rmotorSpeed,motorTemp
void jsonPack(void)//json��� �ֶ� heap̫Сһ���Դ������
{
	char json[] = "{\"cSpeed\": %d,\"Pos\": %d,\"bAlarm\": %d,\"lmSpeed\": %d,\"rmSpeed\": %d,\"bTemp\": %d,\"bLevel\": %d,\"gMode\": %d,\"cMode\": %d,\"timeCount\": %d,\"batVol\": %d,\"carDistce\": %d,\"mcu1Temp\": %d,\"mcu2Temp\": %d,\"brakeTravel\": %d,\"lmoTemp\": %d,\"rmoTemp\": %d}";
	char t_json[256];
	sprintf(t_json, json, racingCarData.FrontSpeed,\
	racingCarData.PedalTravel, \
	racingCarData.batAlarm, \
	racingCarData.lmotorSpeed, \
	racingCarData.rmotorSpeed, \
	racingCarData.batTemp, \
	racingCarData.batLevel, \
	racingCarData.gearMode, \
	racingCarData.carMode, \
	racingCarData.timeCount, \
	racingCarData.batVol, \
	racingCarData.carTravel, \
	racingCarData.mcu1Temp, \
	racingCarData.mcu2Temp, \
	racingCarData.brakeTravel, \
	racingCarData.lmotorTemp, \
	racingCarData.rmotorTemp);
	usartTxFlag = 1;
	printf("%s\r\n",t_json);
	MQTT_Pubdata(t_json);
	memset(t_json,0x00,sizeof(t_json)); //�������
}



