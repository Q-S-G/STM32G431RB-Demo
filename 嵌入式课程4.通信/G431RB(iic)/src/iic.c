#include "iic.h"

#define I2C_ADDRESS 0x18
#define I2C_DELAY 100
extern uint8_t adrr;
extern uint8_t adrr1;
void I2C_Delay(void) {
    for (uint32_t i = 0; i < I2C_DELAY; i++);
}


bool I2C_CheckStart() {
    while (HAL_GPIO_ReadPin(SCL_GPIO_Port, SCL_Pin) == GPIO_PIN_SET) {
        if (HAL_GPIO_ReadPin(SDA_GPIO_Port, SDA_Pin) == GPIO_PIN_RESET) {
            return true;
        }
    }
    return false;
}

uint8_t I2C_ReadByte() {
    uint8_t data = 0;
    for (int i = 0; i < 8; i++) {
        while (HAL_GPIO_ReadPin(SCL_GPIO_Port, SCL_Pin) == GPIO_PIN_RESET);
        data <<= 1;
        data |= HAL_GPIO_ReadPin(SDA_GPIO_Port, SDA_Pin);
        while (HAL_GPIO_ReadPin(SCL_GPIO_Port, SCL_Pin) == GPIO_PIN_SET);
    }
    return data;
}

void I2C_SendAck() {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = SDA_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(SDA_GPIO_Port, &GPIO_InitStruct);

    HAL_GPIO_WritePin(SDA_GPIO_Port, SDA_Pin, GPIO_PIN_RESET);
    while (HAL_GPIO_ReadPin(SCL_GPIO_Port, SCL_Pin) == GPIO_PIN_RESET);
    while (HAL_GPIO_ReadPin(SCL_GPIO_Port, SCL_Pin) == GPIO_PIN_SET);
    HAL_GPIO_WritePin(SDA_GPIO_Port, SDA_Pin, GPIO_PIN_SET);
}

bool I2C_CheckStop() {
    while (HAL_GPIO_ReadPin(SCL_GPIO_Port, SCL_Pin) == GPIO_PIN_SET) {
        if (HAL_GPIO_ReadPin(SDA_GPIO_Port, SDA_Pin) == GPIO_PIN_SET) {
            return true;
        }
    }
    return false;
}

void I2C_SlaveReceive(uint8_t* data, uint8_t length) {
    if (!I2C_CheckStart()) {
        return;
    }

    uint8_t address = I2C_ReadByte();
		adrr = address;
		adrr1 = address;
    if ((address >> 1) != I2C_ADDRESS) {
        
			return;
    }

    I2C_SendAck();

    for (uint8_t i = 0; i < length; i++) 
		{
        data[i] = I2C_ReadByte();
    }
		I2C_SendAck();
    while (!I2C_CheckStop());
}
