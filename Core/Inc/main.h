/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "IgnitionCotrol_Main.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void ITM_SendChar2(uint8_t ch);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define PC14_OSC32_IN_Pin GPIO_PIN_14
#define PC14_OSC32_IN_GPIO_Port GPIOC
#define PC15_OSC32_OUT_Pin GPIO_PIN_15
#define PC15_OSC32_OUT_GPIO_Port GPIOC
#define PH0_OSC_IN_Pin GPIO_PIN_0
#define PH0_OSC_IN_GPIO_Port GPIOH
#define PH1_OSC_OUT_Pin GPIO_PIN_1
#define PH1_OSC_OUT_GPIO_Port GPIOH
#define ADC_VMCU_Pin GPIO_PIN_1
#define ADC_VMCU_GPIO_Port GPIOA
#define ADC_VSENS_Pin GPIO_PIN_2
#define ADC_VSENS_GPIO_Port GPIOA
#define ADC_VBAT_Pin GPIO_PIN_3
#define ADC_VBAT_GPIO_Port GPIOA
#define Signal1_IntPin_Pin GPIO_PIN_4
#define Signal1_IntPin_GPIO_Port GPIOA
#define Signal1_IntPin_EXTI_IRQn EXTI4_IRQn
#define ADC_IGNITION_Pin GPIO_PIN_0
#define ADC_IGNITION_GPIO_Port GPIOB
#define Signal2_IntPin_Pin GPIO_PIN_10
#define Signal2_IntPin_GPIO_Port GPIOE
#define Signal2_IntPin_EXTI_IRQn EXTI15_10_IRQn
#define Cylinder4Out_Pin_Pin GPIO_PIN_11
#define Cylinder4Out_Pin_GPIO_Port GPIOB
#define Cylinder3Out_Pin_Pin GPIO_PIN_12
#define Cylinder3Out_Pin_GPIO_Port GPIOB
#define TestLED2_Pin GPIO_PIN_13
#define TestLED2_GPIO_Port GPIOB
#define TestLED1_Pin GPIO_PIN_14
#define TestLED1_GPIO_Port GPIOB
#define SPI1_CS_Pin GPIO_PIN_8
#define SPI1_CS_GPIO_Port GPIOA
#define OE_PIN1_Pin GPIO_PIN_9
#define OE_PIN1_GPIO_Port GPIOA
#define OE_PIN2_Pin GPIO_PIN_10
#define OE_PIN2_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
