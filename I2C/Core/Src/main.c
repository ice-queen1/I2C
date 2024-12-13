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
#include "dma.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include<stdio.h>
#include "MYI2C.h" 
#include "stm32_u8g2.h"
#include "test.h"
#include "string.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

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
uint32_t CT_data[2] = {0, 0};
void transmit(char *data) 
{
    HAL_UART_Transmit(&huart1, (uint8_t *)data, strlen(data), HAL_MAX_DELAY);
}

void oled_write(int temperature,int humidity)
{

	char t[5]; // 创建一个足够大的字符数组来存储转换后的数字
	char h[5];
	double t1=( double)temperature;
	double h1=(double)humidity;
	sprintf(t, "%.2f",t1/10 ); // 使用sprintf将int变量转换为字符串
	sprintf(h, "%.2f",h1/10);
	
	u8g2_t u8g2;
	u8g2Init(&u8g2);	
	u8g2_ClearBuffer(&u8g2); 
	u8g2_SetFont(&u8g2,u8g2_font_ncenB12_tf);//设置字体格式
	u8g2_DrawXBMP(&u8g2,16,0,16,16,wen);//（参数顺序依次是，结构体、x、y、字宽、字高、储存要显示的字点阵的数组）
	u8g2_DrawXBMP(&u8g2,32,0,16,16,du);
	u8g2_DrawStr(&u8g2,48,16,":");
	u8g2_DrawXBMP(&u8g2,16,32,16,16,shi);
	u8g2_DrawXBMP(&u8g2,32,32,16,16,du);
	u8g2_DrawStr(&u8g2,48,48,":");
	u8g2_DrawUTF8(&u8g2,55,16,t);
	u8g2_DrawUTF8(&u8g2,55,48,h);
	
	u8g2_SendBuffer(&u8g2);
}
	
void Oled_write_init()
 {
	u8g2_t u8g2;
    u8g2Init(&u8g2);	
	u8g2_ClearBuffer(&u8g2); 
	u8g2_SetFont(&u8g2,u8g2_font_ncenB12_tf);//设置字体格式
	u8g2_DrawXBMP(&u8g2,16,0,16,16,wen);//（参数顺序依次是，结构体、x、y、字宽、字高、储存要显示的字点阵的数组）
	u8g2_DrawXBMP(&u8g2,32,0,16,16,du);
	u8g2_DrawStr(&u8g2,48,16,":");
	u8g2_DrawXBMP(&u8g2,16,32,16,16,shi);
	u8g2_DrawXBMP(&u8g2,32,32,16,16,du);
	u8g2_DrawStr(&u8g2,48,48,":");
	u8g2_DrawXBMP(&u8g2,58,0,16,16,dai);
	u8g2_DrawXBMP(&u8g2,74,0,16,16,jian);
	u8g2_DrawXBMP(&u8g2,90,0,16,16,ce);
	u8g2_DrawXBMP(&u8g2,58,32,16,16,dai);
	u8g2_DrawXBMP(&u8g2,74,32,16,16,jian);
	u8g2_DrawXBMP(&u8g2,90,32,16,16,ce);
	u8g2_SendBuffer(&u8g2);
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
//  unsigned int x=16;
  uint32_t CT_data[2]={0,0};
  volatile int  c1,t1;
  Delay_1ms(500);
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
  MX_DMA_Init();
  MX_I2C1_Init();
  MX_I2C2_Init();
  MX_USART1_UART_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
    AHT20_Init();
	Delay_1ms(500);
    u8g2_t u8g2;
    u8g2Init(&u8g2);	
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  Oled_write_init();
  while (1)
  {
	  //程序烧录成功stm32内置LED灯亮
	    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
//	  
//	   OLED显示AHT20的温度和湿度
	  //crc校验后，读取AHT20的温度和湿度数据
		AHT20_Read_CTdata(CT_data);  
		c1 = CT_data[0]*1000/1024/1024;  //计算得到湿度值c1（放大了10倍）
		t1 = CT_data[1]*2000/1024/1024-500;//计算得到温度值t1（放大了10倍）
		oled_write(t1,c1);
	  
	  //每隔2s串口发送AHT20的温度和湿度
		transmit("正在检测");
		for(int i=0; i<10; i++) 
	  {
			HAL_Delay(100);
			transmit(".");
		}
		transmit("\r\n");
		HAL_Delay(1000);
		char buffer[16]; // 确保缓冲区足够大以存储要发送的字符串
		sprintf(buffer, "温度:%d%d.%d", t1/100, (t1/10)%10, t1%10);
		transmit(buffer);
		sprintf(buffer, "湿度:%d%d.%d", c1/100, (c1/10)%10, c1%10);
		transmit(buffer);
		transmit("\r\n");
		transmit("等待");
		for(int i=0; i<10; i++) 
		{
			HAL_Delay(100);
			transmit(".");
		}
		transmit("\r\n");
		HAL_Delay(1000);
		transmit("\r\n");
	  
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	//学号加名字
//	u8g2_SetFont(&u8g2,u8g2_font_ncenB12_tf);//设置字体格式
//	//（参数顺序依次是，结构体、x、y、字宽、字高、储存要显示的字点阵的数组）
//	u8g2_DrawXBMP(&u8g2,40,8,16,16,zuo);
//	u8g2_DrawXBMP(&u8g2,56,8,16,16,zuo);
//	u8g2_DrawXBMP(&u8g2,72,8,16,16,zai);
//	u8g2_SetFont(&u8g2,u8g2_font_ncenB10_tf);
//	u8g2_DrawStr(&u8g2,16,50,"632207060723");
//	u8g2_SendBuffer(&u8g2);

	//显示AHT20的温度和湿度




	//左右滑动长字符
//	if(x<=128)
//	{
//		x+=3;//向右滑动，可以提高每次x的增加量来控制滑动速度
//	}
//	else if(x>128)//置零
//	{
//		x=0;
//	}
//	u8g2_SetFont(&u8g2,u8g2_font_ncenB12_tf);//设置字体格式
//	u8g2_DrawXBMP(&u8g2,x,25,16,16,shen);//（参数顺序依次是，结构体、x、y、字宽、字高、储存要显示的字点阵的数组）
//	u8g2_DrawXBMP(&u8g2,x+16,25,16,16,wu);
//	u8g2_DrawXBMP(&u8g2,x+32,25,16,16,cai);
//	u8g2_DrawXBMP(&u8g2,x+48,25,16,16,feng);
//	u8g2_DrawXBMP(&u8g2,x+64,25,16,16,shaung);
//	u8g2_DrawXBMP(&u8g2,x+80,25,16,16,fei);	
//	u8g2_DrawXBMP(&u8g2,x+96,25,16,16,yi);
//	u8g2_SetFont(&u8g2,u8g2_font_ncenB10_tf);
//	u8g2_SendBuffer(&u8g2);

	
	//OLED_TEST
//	u8g2_FirstPage(&u8g2);
//       do
//       {
//				 draw(&u8g2);
//				 u8g2DrawTest(&u8g2);
//       } while (u8g2_NextPage(&u8g2));
	
	
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
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
}

/* USER CODE BEGIN 4 */


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
