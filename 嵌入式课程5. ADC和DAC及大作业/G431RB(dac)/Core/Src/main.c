/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dac.h"
#include "usart.h"
#include "gpio.h"
#include "math.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
uint32_t SinData[256]={2048, 2098, 2149, 2199, 2250, 2300, 2350, 2399, 2449, 2498, 2548, 2596, 2645, 2693, 2741, 2788, 2835, 2881, 2927, 2972, 3017, 3061, 3105, 3148, 3190, 3231, 3272, 3312, 3351, 3390, 3428, 3465, 3501, 3536, 3570, 3603, 3636, 3667, 3697, 3727, 3755, 3783, 3809, 3834, 3858, 3881, 3903, 3924, 3944, 3962, 3980, 3996, 4011, 4025, 4037, 4049, 4059, 4068, 4075, 4082, 4087, 4091, 4094, 4095, 4095, 4095, 4093, 4089, 4085, 4079, 4072, 4063, 4054, 4043, 4031, 4018, 4003, 3988, 3971, 3953, 3934, 3914, 3892, 3870, 3846, 3822, 3796, 3769, 3741, 3712, 3682, 3651, 3620, 3587, 3553, 3518, 3483, 3446, 3409, 3371, 3332, 3292, 3252, 3211, 3169, 3126, 3083, 3039, 2995, 2950, 2904, 2858, 2811, 2764, 2717, 2669, 2621, 2572, 2523, 2474, 2424,2375, 2325, 2275, 2224, 2174, 2124, 2073, 2023, 1972, 1922, 1872, 1821, 1771, 1721, 1672, 1622, 1573, 1524, 1475, 1427, 1379, 1332, 1285, 1238, 1192, 1146, 1101, 1057, 1013, 970, 927, 885, 844, 804, 764, 725, 687, 650, 613, 578, 543, 509, 476, 445, 414, 384, 355, 327, 300, 274, 250, 226, 204, 182, 162, 143, 125, 108, 93, 78, 65, 53, 42, 33, 24, 17, 11, 7, 3, 1, 0, 0, 2, 5, 9, 14, 21, 28, 37, 47, 59, 71, 85, 100, 116, 134, 152, 172, 193, 215, 238, 262, 287, 313, 341, 369, 399, 429, 460, 493, 526, 560, 595, 631, 668, 706, 745, 784, 824, 865, 906, 948, 991, 1035, 1079, 1124, 1169, 1215, 1261, 1308, 1355, 1403, 1451, 1500, 1548, 1598, 1647, 1697, 1746, 1796, 1846, 1897, 1947, 1998, 2048};
uint32_t i[3]={1241,2482,3723};
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
	double DAC_Data=0.0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DAC1_Init();
  MX_LPUART1_UART_Init();
  /* USER CODE BEGIN 2 */
	HAL_DAC_Start(&hdac1 , DAC_CHANNEL_1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
//		for(int i=0;i<10;i++)
//      {
//				HAL_DAC_SetValue(&hdac1,DAC_CHANNEL_1,DAC_ALIGN_12B_R,i*4096/10);  //����DAC�����ѹ = 0.33*i
//				DAC_Data = HAL_DAC_GetValue(&hdac1,DAC_CHANNEL_1);             //��ȡDAC��������
//				HAL_Delay(1000);                                              //��ʱ1s
//      }
      SinWave();
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV4;
  RCC_OscInitStruct.PLL.PLLN = 85;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
float x=0;
	uint32_t y=0;
void SquareWave() 
	{
        HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 4095);  // ����DAC������ߵ�ѹ
        HAL_Delay(50);

        HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 1);   // ����DAC������͵�ѹ
        HAL_Delay(50); 
}
void SinWave()
{
		for(int x=0;x<sizeof(i)/sizeof(i[0]);x++){
			HAL_DAC_SetValue(&hdac1,DAC_CHANNEL_1,DAC_ALIGN_12B_R,i[x]);
			HAL_Delay(1000);
			HAL_Delay(1000);
			HAL_Delay(1000);
			HAL_Delay(1000);
			HAL_Delay(1000);
			HAL_Delay(1000);
			HAL_Delay(1000);
			HAL_Delay(1000);
			HAL_Delay(1000);
			HAL_Delay(1000);
		}
		
//		while(x<2*3.14159)
//		{
//			y=(int) 4096*sin((double)x);
//			HAL_DAC_SetValue(&hdac1,DAC_CHANNEL_1,DAC_ALIGN_12B_R,y);
//			x=x+0.01f;
//			for(int temp1;temp1<1000;temp1++)
//			{
//				for(int temp2;temp2<170;temp2++)
//				{
//					;
//				}
//			}
//		}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
