/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
 #define Width_raw	40
 #define Height_raw	40

#define nWidth_raw	300
#define nHeight_raw	300
 
#define DEF_DcmiDmaRxBuff_Size nWidth_raw*nHeight_raw/2
#define SRAM_ADDR 0x684FC000


extern SRAM_HandleTypeDef hsram1;
extern DCMI_HandleTypeDef hdcmi;
extern DMA_HandleTypeDef hdma_dcmi;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart3;
extern TIM_HandleTypeDef htim6;



/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define KEY_0_Pin GPIO_PIN_4
#define KEY_0_GPIO_Port GPIOE
#define LED0_Pin GPIO_PIN_9
#define LED0_GPIO_Port GPIOF
#define LED1_Pin GPIO_PIN_10
#define LED1_GPIO_Port GPIOF
#define Bee_Pin GPIO_PIN_0
#define Bee_GPIO_Port GPIOC
#define KEY_UP_Pin GPIO_PIN_0
#define KEY_UP_GPIO_Port GPIOA
#define SPI_F_CS_Pin GPIO_PIN_14
#define SPI_F_CS_GPIO_Port GPIOB
#define Flash_Pin GPIO_PIN_8
#define Flash_GPIO_Port GPIOA
#define SCL_Pin GPIO_PIN_6
#define SCL_GPIO_Port GPIOD
#define SDA_Pin GPIO_PIN_7
#define SDA_GPIO_Port GPIOD
#define OV2640_PWDN_Pin GPIO_PIN_9
#define OV2640_PWDN_GPIO_Port GPIOG
#define OV2640_RST_Pin GPIO_PIN_15
#define OV2640_RST_GPIO_Port GPIOG

/* USER CODE BEGIN Private defines */
void delay_us(uint16_t us);
void delay_ms(uint16_t ms);

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
