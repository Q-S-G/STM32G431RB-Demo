#include "iic.h"
#include "tim.h"

void I2C_W_SCL(uint8_t BitValue)
{
	HAL_GPIO_WritePin(SCL_GPIO_Port, SCL_Pin,BitValue);  // 根据BitValue，设置SCL引脚的电平
    delay_us(10);                                                     // 延时10us，防止时序频率超过要求
}


void I2C_W_SDA(uint8_t BitValue)
{
    HAL_GPIO_WritePin(SDA_GPIO_Port, SDA_Pin, BitValue);  // 根据BitValue，设置SDA引脚的电平，BitValue要实现非0即1的特性
    delay_us(10);                                                                            // 延时10us，防止时序频率超过要求
}

uint8_t I2C_R_SDA(void)
{
    uint8_t BitValue;
    BitValue = HAL_GPIO_ReadPin(SDA_GPIO_Port, SDA_Pin);  // 读取SDA电平
    delay_us(10);                                     // 延时10us，防止时序频率超过要求
    return BitValue;                                  // 返回SDA电平
}


void I2C_Init(void)
{
		HAL_GPIO_WritePin(SDA_GPIO_Port, SDA_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(SCL_GPIO_Port, SCL_Pin, GPIO_PIN_SET);
}

/*协议层*/


void I2C_Start(void)
{
    I2C_W_SDA(1);  // 释放SDA，确保SDA为高电平
    I2C_W_SCL(1);  // 释放SCL，确保SCL为高电平
    I2C_W_SDA(0);  // 在SCL高电平期间，拉低SDA，产生起始信号
    I2C_W_SCL(0);  // 起始后把SCL也拉低，即为了占用总线，也为了方便总线时序的拼接
}


void I2C_Stop(void)
{
    I2C_W_SDA(0);  // 拉低SDA，确保SDA为低电平
    I2C_W_SCL(1);  // 释放SCL，使SCL呈现高电平
    I2C_W_SDA(1);  // 在SCL高电平期间，释放SDA，产生终止信号
}


void I2C_SendByte(uint8_t Byte)
{
    uint8_t i;
    for (i = 0; i < 8; i++)  // 循环8次，主机依次发送数据的每一位
    {
        I2C_W_SDA(Byte & (0x80 >> i));  // 使用掩码的方式取出Byte的指定一位数据并写入到SDA线
        I2C_W_SCL(1);                   // 释放SCL，从机在SCL高电平期间读取SDA
        I2C_W_SCL(0);                   // 拉低SCL，主机开始发送下一位数据
    }
}


uint8_t I2C_ReceiveByte(void)
{
    uint8_t i, Byte = 0x00;  // 定义接收的数据，并赋初值0x00，此处必须赋初值0x00，后面会用到
    I2C_W_SDA(1);          // 接收前，主机先确保释放SDA，避免干扰从机的数据发送
    for (i = 0; i < 8; i++)  // 循环8次，主机依次接收数据的每一位
    {
        I2C_W_SCL(1);  // 释放SCL，主机机在SCL高电平期间读取SDA
        if (I2C_R_SDA() == 1) { Byte |= (0x80 >> i); }  // 读取SDA数据，并存储到Byte变量
                                                          // 当SDA为1时，置变量指定位为1，当SDA为0时，不做处理，指定位为默认的初值0
        I2C_W_SCL(0);  // 拉低SCL，从机在SCL低电平期间写入SDA
    }
    return Byte;  // 返回接收到的一个字节数据
}

void I2C_SendAck(uint8_t AckBit)
{
    I2C_W_SDA(AckBit);  // 主机把应答位数据放到SDA线
    I2C_W_SCL(1);       // 释放SCL，从机在SCL高电平期间，读取应答位
    I2C_W_SCL(0);       // 拉低SCL，开始下一个时序模块
}

uint8_t I2C_ReceiveAck(void)
{
    uint8_t AckBit;  // 定义应答位变量
    I2C_W_SDA(1);  // 接收前，主机先确保释放SDA，避免干扰从机的数据发送
    I2C_W_SCL(1);  // 释放SCL，主机机在SCL高电平期间读取SDA
    AckBit = I2C_R_SDA();  // 将应答位存储到变量里
    I2C_W_SCL(0);  // 拉低SCL，开始下一个时序模块
    return AckBit;  // 返回定义应答位变量
}

void I2C_WriteData(uint8_t Data)
{
    I2C_Start();                      // I2C起始
    I2C_SendByte(0x30);    // 发送从机地址，读写位为0，表示即将写入
    I2C_ReceiveAck();                 // 接收应答
    I2C_SendByte(Data);               // 发送要写入的数据
    I2C_ReceiveAck();                 // 接收应答
    I2C_Stop();                       // I2C终止
}

uint8_t I2C_ReadData(void)
{
	uint8_t Data;
	
	I2C_Start();						//I2C起始
	I2C_SendByte(0x30);	//发送从机地址，读写位为0，表示即将写入
	I2C_ReceiveAck();					//接收应答

	I2C_Start();						//I2C重复起始
	I2C_SendByte(0x30 | 0x01);	//发送从机地址，读写位为1，表示即将读取
	I2C_ReceiveAck();					//接收应答
	Data = I2C_ReceiveByte();			//接收指定寄存器的数据
	I2C_SendAck(1);					//发送应答，给从机非应答，终止从机的数据输出
	I2C_Stop();						//I2C终止
	
	return Data;
}
