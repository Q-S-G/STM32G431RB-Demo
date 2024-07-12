#ifndef _IIC_H
#define _IIC_H
#define SDA_Pin GPIO_PIN_14
#define SDA_GPIO_Port GPIOB
#define SCL_Pin GPIO_PIN_15
#define SCL_GPIO_Port GPIOB
#include "stm32g4xx_hal.h"

#include <stdbool.h>
void I2C_Delay(void);

bool I2C_CheckStop(void);
void I2C_SendAck(void);
uint8_t I2C_ReadByte(void);
bool I2C_CheckStart(void);
void I2C_SlaveReceive(uint8_t* data, uint8_t length);
#endif
