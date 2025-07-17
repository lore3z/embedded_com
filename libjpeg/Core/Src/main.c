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
#include "dcmi.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "fsmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "string.h"
#include "ov2640.h"
#include "math.h"
#include "jpeg.h"
#include "stm32f4xx_it.h"
#include <setjmp.h>
#include "network.h"
#include "network_data.h"
#include "w25flash.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

//uint32_t a_DcmiDmaRxBuff[DEF_DcmiDmaRxBuff_Size] __attribute__((at(0x684FC000)));
extern uint8_t rgb888[3][Width_raw*Height_raw] __attribute__((at(0x68531800)));
extern uint8_t ov2640_mode;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */


/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

uint8_t trans_uart2[100];
uint8_t trans_uart3[100];
int cnt[100];
uint8_t frame = 0;
uint8_t RxBuf[4]; // ���ջ���??
uint8_t dataReceived = 0; // �洢���յ�������
uint8_t variable = 0; // ����
//char buffer[10][100];


/* Global handle to reference the instantiated C-model */
ai_handle network = AI_HANDLE_NULL;

/* Global c-array to handle the activations buffer */
AI_ALIGNED(32)
ai_u8 activations[AI_NETWORK_DATA_ACTIVATIONS_SIZE];

/* Array to store the data of the input tensor */
AI_ALIGNED(32)
ai_float in_data[AI_NETWORK_IN_1_SIZE] ;

	//static uint16_t in_data[2700];
/* or static ai_float in_data[AI_NETWORK_IN_1_SIZE_BYTES]; */

/* c-array to store the data of the output tensor */
AI_ALIGNED(32)
ai_float out_data[AI_NETWORK_OUT_1_SIZE];
/* static ai_u8 out_data[AI_NETWORK_OUT_1_SIZE_BYTES]; */

/* Array of pointer to manage the model's input/output tensors */
ai_buffer *ai_input;
ai_buffer *ai_output;


/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
void ImgShow(uint8_t flag)
{
	if(flag==0){
			memset(trans_uart3,0,sizeof(trans_uart3));
			int len=sprintf((char *)trans_uart3,"p0.pic=0\xff\xff\xff");
			HAL_UART_Transmit_IT(&huart3,trans_uart3,len);
	}else if(flag==1){
			memset(trans_uart3,0,sizeof(trans_uart3));
			int len=sprintf((char *)trans_uart3,"p0.pic=1\xff\xff\xff");
			HAL_UART_Transmit_IT(&huart3,trans_uart3,len);
	}else if(flag==2){
			memset(trans_uart3,0,sizeof(trans_uart3));
			int len=sprintf((char *)trans_uart3,"p0.pic=2\xff\xff\xff");
			HAL_UART_Transmit_IT(&huart3,trans_uart3,len);
	}else if(flag==3){
			memset(trans_uart3,0,sizeof(trans_uart3));
			int len=sprintf((char *)trans_uart3,"p0.pic=3\xff\xff\xff");
			HAL_UART_Transmit_IT(&huart3,trans_uart3,len);
	}
}
int aiInit(void) {
  ai_error err;
  
  /* Create and initialize the c-model */
  const ai_handle acts[] = { activations };
  err = ai_network_create_and_init(&network, acts, NULL);
  if (err.type != AI_ERROR_NONE) { return -1;};

  /* Reteive pointers to the model's input/output tensors */
  ai_input = ai_network_inputs_get(network, NULL);
  ai_output = ai_network_outputs_get(network, NULL);

  return 0;
}

/* 
 * Run inference
 */
int aiRun(const void *in_data, void *out_data) {
  ai_i32 n_batch;
  
  /* 1 - Update IO handlers with the data payload *//* 1 -?????????IO????*/
  ai_input[0].data = AI_HANDLE_PTR(in_data);
  ai_output[0].data = AI_HANDLE_PTR(out_data);

  /* 2 - Perform the inference *//* 2 -????*/
  n_batch = ai_network_run(network, &ai_input[0], &ai_output[0]);
  if (n_batch != 1) {
      ai_network_get_error(network);
  };
  
  return 0;
}

void initialize_rgb888() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < Width_raw * Height_raw; j++) {
            rgb888[i][j] = 0;
        }
    }
}
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
  MX_DMA_Init();
  MX_USART1_UART_Init();
  MX_USART3_UART_Init();
  MX_DCMI_Init();
  MX_FSMC_Init();
  MX_SPI1_Init();
  MX_TIM6_Init();
  MX_TIM7_Init();
  MX_TIM10_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
	while(norflash_init());
	initialize_rgb888();
  HAL_TIM_Base_Start_IT(&htim7);
	HAL_TIM_Base_Start_IT(&htim10);
  DCMI->IER = 0x0;
  __HAL_DCMI_ENABLE(&hdcmi);
  __HAL_DCMI_ENABLE_IT(&hdcmi,DCMI_IT_FRAME);
	rgb_init();
  HAL_UART_Receive_IT(&huart2, RxBuf, 1);
  aiInit();
	ImgShow(3);
//	for(int i=0;i < 4096;i++)
//	{
//		in_data[i]=1;
//	}
//	aiRun(in_data,out_data);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		if((double)out_data[2]<0.1&&out_data[2]!=0&&dataReceived)
		{
					if((double)(out_data[1]-out_data[0])>0)
						HAL_GPIO_WritePin(Bee_GPIO_Port, Bee_Pin, (GPIO_PinState)0);
					else
						HAL_GPIO_WritePin(Bee_GPIO_Port, Bee_Pin, (GPIO_PinState)1);
		}
		else
		{
				HAL_GPIO_WritePin(Bee_GPIO_Port, Bee_Pin, (GPIO_PinState)1);	
		}
		if(out_data[0]!=0){
			if((double)out_data[2]<0.1&&out_data[2]!=0)
			{
						if((double)(out_data[1]-out_data[0])>0)
							ImgShow(2);
						else
							ImgShow(1);
			}
			else
			{
					ImgShow(0);	
			}
		}else{
				ImgShow(3);
		}
		rgb_test();
		
		aiRun(in_data,out_data);
//		fsmc_sram_test();
    /* USER CODE END WHILE */

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
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */


void HAL_DCMI_FrameEventCallback(DCMI_HandleTypeDef *hdcmi)
{
	frame=1;
	if(ov2640_mode){
    __HAL_DCMI_CLEAR_FLAG(hdcmi, DCMI_FLAG_FRAMERI);    /* ���֡�ж�????? */
	    __HAL_DCMI_ENABLE_IT(hdcmi, DCMI_IT_FRAME);
	    jpeg_data_process();    /* jpeg���ݴ��� */
	}

//	     uint8_t *p = (uint8_t *)SRAM_ADDR;

//        for (int i = 0; i < DEF_DcmiDmaRxBuff_Size*4; i++) {
////					printf("[%d]",i);
//					printf(",%d",(uint8_t)*p);
//					p++;
//           while ((USART1->SR & 0X40) == 0);

//       }

	HAL_GPIO_TogglePin(LED0_GPIO_Port,LED0_Pin);

    /* ����ʹ��֡�ж�,��ΪHAL_DCMI_IRQHandler()������ر�֡�ж�????? */

}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    static uint8_t index = 0;
    static uint8_t buffer[4];

    if (huart->Instance == USART2)
    {
				if(index == 0 && RxBuf[0]!=0xA5){
					HAL_UART_Receive_IT(&huart2, RxBuf, 1);
					return;
				}
        buffer[index++] = RxBuf[0];

        if (index == 4)
        {
            index = 0;
            if (buffer[0] == 0xA5 && buffer[3] == 0x5A) // �?查头和尾
            {
                uint8_t checksum = buffer[1];
                if ((checksum & 0xFF) == buffer[2]) // �?查校验码
                {
                    dataReceived = buffer[1];

                }
            }
        }

        // 继续接收下一个字�?
        HAL_UART_Receive_IT(&huart2, RxBuf, 1);
    }
}
/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */
  if (htim == &htim10)
  {
		

		cnt[0]++;
		if(cnt[0]==1000)
		{
			memset(trans_uart2,0,sizeof(trans_uart2));
			int len=sprintf((char *)trans_uart2,"[0]%f,[1]%f,[2]%f\r\n",out_data[0],out_data[1],out_data[2]);
			HAL_UART_Transmit_IT(&huart2,trans_uart2,len);
//			frame=0;
			cnt[0]=0;
			HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
//			OV2640_FLASH(1);
//    ov2640_write_reg(0xFF, 0x01);
//    ov2640_write_reg(0x4B, 0x81);
//    ov2640_write_reg(0x4B, 0x01);
		}

  }

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1)
  {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

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
#ifdef USE_FULL_ASSERT
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
