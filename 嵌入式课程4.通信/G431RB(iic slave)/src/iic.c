#include "iic.h"
#include "tim.h"

void I2C_W_SCL(uint8_t BitValue)
{
	HAL_GPIO_WritePin(SCL_GPIO_Port, SCL_Pin,BitValue);  // ����BitValue������SCL���ŵĵ�ƽ
    delay_us(10);                                                     // ��ʱ10us����ֹʱ��Ƶ�ʳ���Ҫ��
}


void I2C_W_SDA(uint8_t BitValue)
{
    HAL_GPIO_WritePin(SDA_GPIO_Port, SDA_Pin, BitValue);  // ����BitValue������SDA���ŵĵ�ƽ��BitValueҪʵ�ַ�0��1������
    delay_us(10);                                                                            // ��ʱ10us����ֹʱ��Ƶ�ʳ���Ҫ��
}

uint8_t I2C_R_SDA(void)
{
    uint8_t BitValue;
    BitValue = HAL_GPIO_ReadPin(SDA_GPIO_Port, SDA_Pin);  // ��ȡSDA��ƽ
    delay_us(10);                                     // ��ʱ10us����ֹʱ��Ƶ�ʳ���Ҫ��
    return BitValue;                                  // ����SDA��ƽ
}


void I2C_Init(void)
{
		HAL_GPIO_WritePin(SDA_GPIO_Port, SDA_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(SCL_GPIO_Port, SCL_Pin, GPIO_PIN_SET);
}

/*Э���*/


void I2C_Start(void)
{
    I2C_W_SDA(1);  // �ͷ�SDA��ȷ��SDAΪ�ߵ�ƽ
    I2C_W_SCL(1);  // �ͷ�SCL��ȷ��SCLΪ�ߵ�ƽ
    I2C_W_SDA(0);  // ��SCL�ߵ�ƽ�ڼ䣬����SDA��������ʼ�ź�
    I2C_W_SCL(0);  // ��ʼ���SCLҲ���ͣ���Ϊ��ռ�����ߣ�ҲΪ�˷�������ʱ���ƴ��
}


void I2C_Stop(void)
{
    I2C_W_SDA(0);  // ����SDA��ȷ��SDAΪ�͵�ƽ
    I2C_W_SCL(1);  // �ͷ�SCL��ʹSCL���ָߵ�ƽ
    I2C_W_SDA(1);  // ��SCL�ߵ�ƽ�ڼ䣬�ͷ�SDA��������ֹ�ź�
}


void I2C_SendByte(uint8_t Byte)
{
    uint8_t i;
    for (i = 0; i < 8; i++)  // ѭ��8�Σ��������η������ݵ�ÿһλ
    {
        I2C_W_SDA(Byte & (0x80 >> i));  // ʹ������ķ�ʽȡ��Byte��ָ��һλ���ݲ�д�뵽SDA��
        I2C_W_SCL(1);                   // �ͷ�SCL���ӻ���SCL�ߵ�ƽ�ڼ��ȡSDA
        I2C_W_SCL(0);                   // ����SCL��������ʼ������һλ����
    }
}


uint8_t I2C_ReceiveByte(void)
{
    uint8_t i, Byte = 0x00;  // ������յ����ݣ�������ֵ0x00���˴����븳��ֵ0x00��������õ�
    I2C_W_SDA(1);          // ����ǰ��������ȷ���ͷ�SDA��������Ŵӻ������ݷ���
    for (i = 0; i < 8; i++)  // ѭ��8�Σ��������ν������ݵ�ÿһλ
    {
        I2C_W_SCL(1);  // �ͷ�SCL����������SCL�ߵ�ƽ�ڼ��ȡSDA
        if (I2C_R_SDA() == 1) { Byte |= (0x80 >> i); }  // ��ȡSDA���ݣ����洢��Byte����
                                                          // ��SDAΪ1ʱ���ñ���ָ��λΪ1����SDAΪ0ʱ����������ָ��λΪĬ�ϵĳ�ֵ0
        I2C_W_SCL(0);  // ����SCL���ӻ���SCL�͵�ƽ�ڼ�д��SDA
    }
    return Byte;  // ���ؽ��յ���һ���ֽ�����
}

void I2C_SendAck(uint8_t AckBit)
{
    I2C_W_SDA(AckBit);  // ������Ӧ��λ���ݷŵ�SDA��
    I2C_W_SCL(1);       // �ͷ�SCL���ӻ���SCL�ߵ�ƽ�ڼ䣬��ȡӦ��λ
    I2C_W_SCL(0);       // ����SCL����ʼ��һ��ʱ��ģ��
}

uint8_t I2C_ReceiveAck(void)
{
    uint8_t AckBit;  // ����Ӧ��λ����
    I2C_W_SDA(1);  // ����ǰ��������ȷ���ͷ�SDA��������Ŵӻ������ݷ���
    I2C_W_SCL(1);  // �ͷ�SCL����������SCL�ߵ�ƽ�ڼ��ȡSDA
    AckBit = I2C_R_SDA();  // ��Ӧ��λ�洢��������
    I2C_W_SCL(0);  // ����SCL����ʼ��һ��ʱ��ģ��
    return AckBit;  // ���ض���Ӧ��λ����
}

void I2C_WriteData(uint8_t Data)
{
    I2C_Start();                      // I2C��ʼ
    I2C_SendByte(0x30);    // ���ʹӻ���ַ����дλΪ0����ʾ����д��
    I2C_ReceiveAck();                 // ����Ӧ��
    I2C_SendByte(Data);               // ����Ҫд�������
    I2C_ReceiveAck();                 // ����Ӧ��
    I2C_Stop();                       // I2C��ֹ
}

uint8_t I2C_ReadData(void)
{
	uint8_t Data;
	
	I2C_Start();						//I2C��ʼ
	I2C_SendByte(0x30);	//���ʹӻ���ַ����дλΪ0����ʾ����д��
	I2C_ReceiveAck();					//����Ӧ��

	I2C_Start();						//I2C�ظ���ʼ
	I2C_SendByte(0x30 | 0x01);	//���ʹӻ���ַ����дλΪ1����ʾ������ȡ
	I2C_ReceiveAck();					//����Ӧ��
	Data = I2C_ReceiveByte();			//����ָ���Ĵ���������
	I2C_SendAck(1);					//����Ӧ�𣬸��ӻ���Ӧ����ֹ�ӻ����������
	I2C_Stop();						//I2C��ֹ
	
	return Data;
}
