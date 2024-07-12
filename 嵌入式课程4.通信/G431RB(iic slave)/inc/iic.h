#ifndef _IIC_H
#define _IIC_H
#define SDA_Pin GPIO_PIN_14
#define SDA_GPIO_Port GPIOB
#define SCL_Pin GPIO_PIN_15
#define SCL_GPIO_Port GPIOB
#include "stm32g4xx_hal.h"
#define SCL_L      (HAL_GPIO_WritePin(SCL_GPIO_Port, SCL_Pin, GPIO_PIN_RESET))
#define SCL_H      (HAL_GPIO_WritePin(SCL_GPIO_Port, SCL_Pin, GPIO_PIN_SET))
#define SDA_L      (HAL_GPIO_WritePin(SDA_GPIO_Port, SDA_Pin, GPIO_PIN_RESET))
#define SDA_H      (HAL_GPIO_WritePin(SDA_GPIO_Port, SDA_Pin, GPIO_PIN_SET))
#define SDA_READ   (HAL_GPIO_ReadPin(SDA_GPIO_Port, SDA_Pin))
void I2C_W_SCL(uint8_t BitValue);
void I2C_W_SDA(uint8_t BitValue);
uint8_t I2C_R_SDA(void);
void I2C_Init(void);
void I2C_Start(void);

void I2C_Stop(void);
void I2C_SendByte(uint8_t Byte);
uint8_t I2C_ReceiveByte(void);
void     I2C_init(void);
void I2C_SendAck(uint8_t AckBit);
uint8_t I2C_ReceiveAck(void);
void I2C_WriteData(uint8_t Data);
uint8_t I2C_ReadData(void);
#endif
