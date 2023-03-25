/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "adc.h"
#include "iwdg.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
//���¿�ʼ�û�ͷ�ļ��������ͷ�ļ���MY�ļ�����
#include "stdio.h"
#include "User_Scheduler.h"
#include "User_Function.h"
#include "IIC_OLED.h"
#include "key.h"
#include "bmp.h"
#include "Motor.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define VERSION      "A01.0D"//���汾���Ӱ汾��.�����汾��

/*---->
�汾������ʷ
A01.0D: �����ٶȱ�����ʵ�ֱ��������� 2023/3/25 13:18
A01.0C: �༶�˵�������� 2023/3/24 20:36
A01.0B: ���������ܳ�������ͨ�� 2023/3/15 21:39
A01.0A: ������/OLED���������ͨ�� 2023/3/15 20:49
A01.09: ��������ɨ�躯��(����֤) 2023/3/14 14:08
A01.08: ����ADCУ׼���淶����(����֤) 2023/3/11 17:19
A01.07: �������Ź������ʱ��Լ6.5s(����֤) 2023/3/11 16:42
A01.06: �ɼ��ĸ�ͨ����ADC����(����֤) 2023/3/11 16:30
A01.05: OLED��ֲ�ɹ�(����֤) 2023/3/11 15:54
A01.04: �����û�������(δ��֤) 2023/3/11 15:36
A01.03: ��дprintf�������޸������ڶ� 2023/3/11 15:19
A01.02: �궨���LED,BEEP����ܽ� 2023/3/11 15:06
A01.01: �½����̣���ʼ������ 2023/3/11 14:55
*/

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
volatile uint8_t SYS_TIME1S_FLAG = 0;//����1s��־λ
int8_t led_status;
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/*-----------------------------------------*/
/*-----�ض���printf����--------------------*/
/*-----��������int fputc(int ch, FILE *f)--*/
/*-----------------------------------------*/
int fputc(int ch, FILE *f){
	uint8_t temp[1] = {ch};
	HAL_UART_Transmit(&huart2, temp, 1, 2);//huart2��Ҫ������������޸�
	return ch;
}

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
  MX_TIM3_Init();
  MX_ADC1_Init();
  MX_TIM1_Init();
  MX_USART2_UART_Init();
  MX_IWDG_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start_IT(&htim2);//������ʱ��
  __HAL_TIM_CLEAR_IT(&htim3,TIM_IT_UPDATE);

	HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);//��������
  __HAL_TIM_ENABLE_IT(&htim3,TIM_IT_UPDATE);

	HAL_ADCEx_Calibration_Start(&hadc1); //ADCУ׼

	BEEP_OFF;
	OLED_Init();			//OLED��ʼ��
	OLED_CLS();				//OLED����
	//OLED_ShowStr(16,4,(unsigned char*)"SYS init succeeded      ",1);
	OLED_DrawBMP(0,0,128,8,BMP0);
	user_main_info("System initialization succeeded��");
	//MX_IWDG_Init();
	
	//HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
  //HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_1);
  //HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
  //HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_2);

	
	

	//TIM1->CCR1 = 50;//50%��ռ�ձ�
	//HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);//V������
	/*
				HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_1);//U�಻����
			HAL_TIMEx_PWMN_Stop(&htim1,TIM_CHANNEL_1);
			
			TIM1->CCR2 = 50;//50%��ռ�ձ�
			HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);//V������
			
			TIM1->CCR3 = 50;//50%��ռ�ձ�
			HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_3);//V������
			*/
	
	//MX_IWDG_Init();
	//LED0_ON;
	
	
	/*��ʼ���Ƶ��*/
	//Motor_Stop();
	//ROTOR_Pre_positioning(1);
	//Motor_Start(1);
	
	
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		Schedule();						/*������*/
		FuncRun(&tSysScanFlag);/*��������*/
		//Motor_Run(1);
		
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
/*���濪ʼ�Ӻ���*/
/*�жϷ�����*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) 
	{
			if (htim->Instance == htim2.Instance) {//��ʱ��2�ж�,����1ms�ж�һ��
					SYS_TIME1S_FLAG=1;
	    }
      if (htim->Instance == htim3.Instance)//�ⲿ�ж�3��Դ�ڱ�����
      {
        
        if( ((int)(__HAL_TIM_IS_TIM_COUNTING_DOWN(&htim3)))== 0)//������ת
        {
          KEY_Value = 4;
        }else//������ת
        {
          KEY_Value = 3;
        }
        //user_main_info("������%d",KEY_Value);
      }

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
