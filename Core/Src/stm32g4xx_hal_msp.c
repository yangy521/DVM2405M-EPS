/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file         stm32g4xx_hal_msp.c
  * @brief        This file provides code for the MSP Initialization
  *               and de-Initialization codes.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "Device.h"
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;
ADC_HandleTypeDef hadc2;
DMA_HandleTypeDef hdma_adc2;
ADC_HandleTypeDef hadc3;
DMA_HandleTypeDef hdma_adc3;
ADC_HandleTypeDef hadc4;
DMA_HandleTypeDef hdma_adc4;
ADC_HandleTypeDef hadc5;
DMA_HandleTypeDef hdma_adc5;

static uint32_t HAL_RCC_ADC12_CLK_ENABLED=0;
static uint32_t HAL_RCC_ADC345_CLK_ENABLED=0;
/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN Define */

/* USER CODE END Define */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN Macro */

/* USER CODE END Macro */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* External functions --------------------------------------------------------*/
/* USER CODE BEGIN ExternalFunctions */
void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);
/* USER CODE END ExternalFunctions */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */
/**
  * Initializes the Global MSP.
  */
void HAL_MspInit(void)
{
  /* USER CODE BEGIN MspInit 0 */

  /* USER CODE END MspInit 0 */
  //PWR_PVDTypeDef sConfigPVD = {0};

  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_RCC_PWR_CLK_ENABLE();

  /* System interrupt init*/

  /** PVD Configuration
  */
//  sConfigPVD.PVDLevel = PWR_PVDLEVEL_3;
//  sConfigPVD.Mode = PWR_PVD_MODE_NORMAL;
//  HAL_PWR_ConfigPVD(&sConfigPVD);
//  /** Enable the PVD Output
//  */
//  HAL_PWR_EnablePVD();
  /** Disable the internal Pull-Up in Dead Battery pins of UCPD peripheral
  */
  HAL_PWREx_DisableUCPDDeadBattery();

  /* USER CODE BEGIN MspInit 1 */

  /* USER CODE END MspInit 1 */
}

/**
* @brief ADC MSP Initialization
* This function configures the hardware resources used in this example
* @param hadc: ADC handle pointer
* @retval None
*/
void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(hadc->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspInit 0 */

  /* USER CODE END ADC1_MspInit 0 */
    /* Peripheral clock enable */
    HAL_RCC_ADC12_CLK_ENABLED++;
    if(HAL_RCC_ADC12_CLK_ENABLED==1){
      __HAL_RCC_ADC12_CLK_ENABLE();
    }

    /**ADC1 GPIO Configuration
    */
		#ifdef ADC1_PINS_GPIOA
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitStruct.Pin = ADC1_PINS_GPIOA;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
		#endif

		#ifdef ADC1_PINS_GPIOB
    __HAL_RCC_GPIOB_CLK_ENABLE();
    GPIO_InitStruct.Pin = ADC1_PINS_GPIOB;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
		#endif

		#ifdef ADC1_PINS_GPIOC
    __HAL_RCC_GPIOC_CLK_ENABLE();
    GPIO_InitStruct.Pin = ADC1_PINS_GPIOC;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
		#endif

		#ifdef ADC1_PINS_GPIOD
    __HAL_RCC_GPIOD_CLK_ENABLE();
    GPIO_InitStruct.Pin = ADC1_PINS_GPIOD;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
		#endif

		#ifdef ADC1_PINS_GPIOE
    __HAL_RCC_GPIOE_CLK_ENABLE();
    GPIO_InitStruct.Pin = ADC1_PINS_GPIOE;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
		#endif

		#ifdef ADC1_PINS_GPIOF
    __HAL_RCC_GPIOF_CLK_ENABLE();
    GPIO_InitStruct.Pin = ADC1_PINS_GPIOF;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
		#endif

    /* ADC1 DMA Init */
    /* ADC1 Init */
		#if (ADC1_NUM != 0)
    hdma_adc1.Instance = DMA1_Channel1;
    hdma_adc1.Init.Request = DMA_REQUEST_ADC1;
    hdma_adc1.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_adc1.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_adc1.Init.MemInc = DMA_MINC_ENABLE;
    hdma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_adc1.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma_adc1.Init.Mode = DMA_CIRCULAR;
    hdma_adc1.Init.Priority = DMA_PRIORITY_HIGH;
    if (HAL_DMA_Init(&hdma_adc1) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(hadc,DMA_Handle,hdma_adc1);
		#endif //#if (ADC1_NUM != 0)
  /* USER CODE BEGIN ADC1_MspInit 1 */

  /* USER CODE END ADC1_MspInit 1 */
  }
  else if(hadc->Instance==ADC2)
  {
  /* USER CODE BEGIN ADC2_MspInit 0 */

  /* USER CODE END ADC2_MspInit 0 */
    /* Peripheral clock enable */
    HAL_RCC_ADC12_CLK_ENABLED++;
    if(HAL_RCC_ADC12_CLK_ENABLED==1){
      __HAL_RCC_ADC12_CLK_ENABLE();
    }

    /**ADC2 GPIO Configuration
    */
		#ifdef ADC2_PINS_GPIOA
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitStruct.Pin = ADC2_PINS_GPIOA;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
		#endif

		#ifdef ADC2_PINS_GPIOB
    __HAL_RCC_GPIOB_CLK_ENABLE();
    GPIO_InitStruct.Pin = ADC2_PINS_GPIOB;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
		#endif

		#ifdef ADC2_PINS_GPIOC
    __HAL_RCC_GPIOC_CLK_ENABLE();
    GPIO_InitStruct.Pin = ADC2_PINS_GPIOC;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
		#endif

		#ifdef ADC2_PINS_GPIOD
    __HAL_RCC_GPIOD_CLK_ENABLE();
    GPIO_InitStruct.Pin = ADC2_PINS_GPIOD;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
		#endif

		#ifdef ADC2_PINS_GPIOE
    __HAL_RCC_GPIOE_CLK_ENABLE();
    GPIO_InitStruct.Pin = ADC2_PINS_GPIOE;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
		#endif

		#ifdef ADC2_PINS_GPIOF
    __HAL_RCC_GPIOF_CLK_ENABLE();
    GPIO_InitStruct.Pin = ADC2_PINS_GPIOF;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
		#endif

		/* ADC2 DMA Init */
    /* ADC2 Init */
		#if (ADC2_NUM != 0)
    hdma_adc2.Instance = DMA1_Channel2;
    hdma_adc2.Init.Request = DMA_REQUEST_ADC2;
    hdma_adc2.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_adc2.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_adc2.Init.MemInc = DMA_MINC_ENABLE;
    hdma_adc2.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_adc2.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma_adc2.Init.Mode = DMA_CIRCULAR;
    hdma_adc2.Init.Priority = DMA_PRIORITY_HIGH;
    if (HAL_DMA_Init(&hdma_adc2) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(hadc,DMA_Handle,hdma_adc2);
		#endif //		#if (ADC2_NUM != 0)
  /* USER CODE BEGIN ADC2_MspInit 1 */

  /* USER CODE END ADC2_MspInit 1 */
  }
  else if(hadc->Instance==ADC3)
  {
  /* USER CODE BEGIN ADC3_MspInit 0 */

  /* USER CODE END ADC3_MspInit 0 */
    /* Peripheral clock enable */
    HAL_RCC_ADC345_CLK_ENABLED++;
    if(HAL_RCC_ADC345_CLK_ENABLED==1){
			__HAL_RCC_ADC345_CLK_ENABLE();
    }

    /**ADC3 GPIO Configuration
    */
		#ifdef ADC3_PINS_GPIOA
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitStruct.Pin = ADC3_PINS_GPIOA;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
		#endif

		#ifdef ADC3_PINS_GPIOB
    __HAL_RCC_GPIOB_CLK_ENABLE();
    GPIO_InitStruct.Pin = ADC3_PINS_GPIOB;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
		#endif

		#ifdef ADC3_PINS_GPIOC
    __HAL_RCC_GPIOC_CLK_ENABLE();
    GPIO_InitStruct.Pin = ADC3_PINS_GPIOC;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
		#endif

		#ifdef ADC3_PINS_GPIOD
    __HAL_RCC_GPIOD_CLK_ENABLE();
    GPIO_InitStruct.Pin = ADC3_PINS_GPIOD;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
		#endif

		#ifdef ADC3_PINS_GPIOE
    __HAL_RCC_GPIOE_CLK_ENABLE();
    GPIO_InitStruct.Pin = ADC3_PINS_GPIOE;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
		#endif

		#ifdef ADC3_PINS_GPIOF
    __HAL_RCC_GPIOF_CLK_ENABLE();
    GPIO_InitStruct.Pin = ADC3_PINS_GPIOF;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
		#endif
		
    /* ADC3 DMA Init */
    /* ADC3 Init */
		#if (ADC3_NUM != 0)
    hdma_adc3.Instance = DMA1_Channel3;
    hdma_adc3.Init.Request = DMA_REQUEST_ADC3;
    hdma_adc3.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_adc3.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_adc3.Init.MemInc = DMA_MINC_ENABLE;
    hdma_adc3.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_adc3.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma_adc3.Init.Mode = DMA_CIRCULAR;
    hdma_adc3.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_adc3) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(hadc,DMA_Handle,hdma_adc3);
		#endif //		#if (ADC3_NUM != 0)

  /* USER CODE BEGIN ADC3_MspInit 1 */

  /* USER CODE END ADC3_MspInit 1 */
  }
else if(hadc->Instance==ADC4)
  {
  /* USER CODE BEGIN ADC4_MspInit 0 */

  /* USER CODE END ADC4_MspInit 0 */
    /* Peripheral clock enable */
    HAL_RCC_ADC345_CLK_ENABLED++;
    if(HAL_RCC_ADC345_CLK_ENABLED==1){
      __HAL_RCC_ADC345_CLK_ENABLE();
    }

    /**ADC4 GPIO Configuration
    */
	#ifdef ADC4_PINS_GPIOA
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitStruct.Pin = ADC4_PINS_GPIOA;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	#endif

	#ifdef ADC4_PINS_GPIOB
    __HAL_RCC_GPIOB_CLK_ENABLE();
    GPIO_InitStruct.Pin = ADC4_PINS_GPIOB;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	#endif

	#ifdef ADC4_PINS_GPIOC
    __HAL_RCC_GPIOC_CLK_ENABLE();
    GPIO_InitStruct.Pin = ADC4_PINS_GPIOC;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	#endif

	#ifdef ADC4_PINS_GPIOD
    __HAL_RCC_GPIOD_CLK_ENABLE();
    GPIO_InitStruct.Pin = ADC4_PINS_GPIOD;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	#endif

	#ifdef ADC4_PINS_GPIOE
    __HAL_RCC_GPIOE_CLK_ENABLE();
    GPIO_InitStruct.Pin = ADC4_PINS_GPIOE;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
	#endif

	#ifdef ADC4_PINS_GPIOF
    __HAL_RCC_GPIOF_CLK_ENABLE();
    GPIO_InitStruct.Pin = ADC4_PINS_GPIOF;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
	#endif

    /* ADC4 DMA Init */
    /* ADC4 Init */
	#if (ADC4_NUM != 0)
    hdma_adc4.Instance = DMA1_Channel4;
    hdma_adc4.Init.Request = DMA_REQUEST_ADC4;
    hdma_adc4.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_adc4.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_adc4.Init.MemInc = DMA_MINC_ENABLE;
    hdma_adc4.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_adc4.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma_adc4.Init.Mode = DMA_CIRCULAR;
    hdma_adc4.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_adc4) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(hadc,DMA_Handle,hdma_adc4);
	#endif //		#if (ADC4_NUM != 0)
  /* USER CODE BEGIN ADC4_MspInit 1 */

  /* USER CODE END ADC4_MspInit 1 */
  }
  else if(hadc->Instance==ADC5)
  {
  /* USER CODE BEGIN ADC5_MspInit 0 */

  /* USER CODE END ADC5_MspInit 0 */
    /* Peripheral clock enable */
    HAL_RCC_ADC345_CLK_ENABLED++;
    if(HAL_RCC_ADC345_CLK_ENABLED==1){
      __HAL_RCC_ADC345_CLK_ENABLE();
    }

     /**ADC5 GPIO Configuration
    */
	#ifdef ADC5_PINS_GPIOA
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitStruct.Pin = ADC5_PINS_GPIOA;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	#endif

	#ifdef ADC5_PINS_GPIOB
    __HAL_RCC_GPIOB_CLK_ENABLE();
    GPIO_InitStruct.Pin = ADC5_PINS_GPIOB;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	#endif

	#ifdef ADC5_PINS_GPIOC
    __HAL_RCC_GPIOC_CLK_ENABLE();
    GPIO_InitStruct.Pin = ADC5_PINS_GPIOC;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	#endif

	#ifdef ADC5_PINS_GPIOD
    __HAL_RCC_GPIOD_CLK_ENABLE();
    GPIO_InitStruct.Pin = ADC5_PINS_GPIOD;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	#endif

	#ifdef ADC5_PINS_GPIOE
    __HAL_RCC_GPIOE_CLK_ENABLE();
    GPIO_InitStruct.Pin = ADC5_PINS_GPIOE;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
	#endif

	#ifdef ADC5_PINS_GPIOF
    __HAL_RCC_GPIOF_CLK_ENABLE();
    GPIO_InitStruct.Pin = ADC5_PINS_GPIOF;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
	#endif

    /* ADC5 DMA Init */
    /* ADC5 Init */
	#if (ADC5_NUM != 0)
    hdma_adc5.Instance = DMA1_Channel5;
    hdma_adc5.Init.Request = DMA_REQUEST_ADC5;
    hdma_adc5.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_adc5.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_adc5.Init.MemInc = DMA_MINC_ENABLE;
    hdma_adc5.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_adc5.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma_adc5.Init.Mode = DMA_CIRCULAR;
    hdma_adc5.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_adc5) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(hadc,DMA_Handle,hdma_adc5);
	#endif //		#if (ADC5_NUM != 0)
  /* USER CODE BEGIN ADC5_MspInit 1 */

  /* USER CODE END ADC5_MspInit 1 */
  }
}

/**
* @brief ADC MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hadc: ADC handle pointer
* @retval None
*/
void HAL_ADC_MspDeInit(ADC_HandleTypeDef* hadc)
{
  if(hadc->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspDeInit 0 */

  /* USER CODE END ADC1_MspDeInit 0 */
    /* Peripheral clock disable */
    HAL_RCC_ADC12_CLK_ENABLED--;
    if(HAL_RCC_ADC12_CLK_ENABLED==0){
      __HAL_RCC_ADC12_CLK_DISABLE();
    }

		#ifdef ADC1_PINS_GPIOA
		HAL_GPIO_DeInit(GPIOA, ADC1_PINS_GPIOA);
		#endif
		#ifdef ADC1_PINS_GPIOB
		HAL_GPIO_DeInit(GPIOB, ADC1_PINS_GPIOB);
		#endif
		#ifdef ADC1_PINS_GPIOC
		HAL_GPIO_DeInit(GPIOC, ADC1_PINS_GPIOC);
		#endif
		#ifdef ADC1_PINS_GPIOD
		HAL_GPIO_DeInit(GPIOD, ADC1_PINS_GPIOD);
		#endif
		#ifdef ADC1_PINS_GPIOE
		HAL_GPIO_DeInit(GPIOE, ADC1_PINS_GPIOE);
		#endif
		#ifdef ADC1_PINS_GPIOF
		HAL_GPIO_DeInit(GPIOF, ADC1_PINS_GPIOF);
		#endif

    /* ADC1 DMA DeInit */
		#if (ADC1_NUM != 0)
    HAL_DMA_DeInit(hadc->DMA_Handle);
		#endif
  /* USER CODE BEGIN ADC1_MspDeInit 1 */

  /* USER CODE END ADC1_MspDeInit 1 */
  }
  else if(hadc->Instance==ADC2)
  {
  /* USER CODE BEGIN ADC2_MspDeInit 0 */

  /* USER CODE END ADC2_MspDeInit 0 */
    /* Peripheral clock disable */
    HAL_RCC_ADC12_CLK_ENABLED--;
    if(HAL_RCC_ADC12_CLK_ENABLED==0){
      __HAL_RCC_ADC12_CLK_DISABLE();
    }

		#ifdef ADC2_PINS_GPIOA
		HAL_GPIO_DeInit(GPIOA, ADC2_PINS_GPIOA);
		#endif
		#ifdef ADC2_PINS_GPIOB
		HAL_GPIO_DeInit(GPIOB, ADC2_PINS_GPIOB);
		#endif
		#ifdef ADC2_PINS_GPIOC
		HAL_GPIO_DeInit(GPIOC, ADC2_PINS_GPIOC);
		#endif
		#ifdef ADC2_PINS_GPIOD
		HAL_GPIO_DeInit(GPIOD, ADC2_PINS_GPIOD);
		#endif
		#ifdef ADC2_PINS_GPIOE
		HAL_GPIO_DeInit(GPIOE, ADC2_PINS_GPIOE);
		#endif
		#ifdef ADC2_PINS_GPIOF
		HAL_GPIO_DeInit(GPIOF, ADC2_PINS_GPIOF);
		#endif

    /* ADC2 DMA DeInit */
		#if (ADC2_NUM != 0)
    HAL_DMA_DeInit(hadc->DMA_Handle);
		#endif
  /* USER CODE BEGIN ADC2_MspDeInit 1 */

  /* USER CODE END ADC2_MspDeInit 1 */
  }
  else if(hadc->Instance==ADC3)
  {
  /* USER CODE BEGIN ADC3_MspDeInit 0 */

  /* USER CODE END ADC3_MspDeInit 0 */
    /* Peripheral clock disable */
    HAL_RCC_ADC345_CLK_ENABLED--;
    if(HAL_RCC_ADC345_CLK_ENABLED==0){
      __HAL_RCC_ADC345_CLK_DISABLE();
    }

		#ifdef ADC3_PINS_GPIOA
		HAL_GPIO_DeInit(GPIOA, ADC3_PINS_GPIOA);
		#endif
		#ifdef ADC3_PINS_GPIOB
		HAL_GPIO_DeInit(GPIOB, ADC3_PINS_GPIOB);
		#endif
		#ifdef ADC3_PINS_GPIOC
		HAL_GPIO_DeInit(GPIOC, ADC3_PINS_GPIOC);
		#endif
		#ifdef ADC3_PINS_GPIOD
		HAL_GPIO_DeInit(GPIOD, ADC3_PINS_GPIOD);
		#endif
		#ifdef ADC3_PINS_GPIOE
		HAL_GPIO_DeInit(GPIOE, ADC3_PINS_GPIOE);
		#endif
		#ifdef ADC3_PINS_GPIOF
		HAL_GPIO_DeInit(GPIOF, ADC3_PINS_GPIOF);
		#endif

    /* ADC3 DMA DeInit */
		#if (ADC3_NUM != 0)
    HAL_DMA_DeInit(hadc->DMA_Handle);
		#endif
  /* USER CODE BEGIN ADC3_MspDeInit 1 */

  /* USER CODE END ADC3_MspDeInit 1 */
  }
  else if(hadc->Instance==ADC4)
  {
  /* USER CODE BEGIN ADC4_MspDeInit 0 */

  /* USER CODE END ADC4_MspDeInit 0 */
    /* Peripheral clock disable */
    HAL_RCC_ADC345_CLK_ENABLED--;
    if(HAL_RCC_ADC345_CLK_ENABLED==0){
      __HAL_RCC_ADC345_CLK_DISABLE();
    }

	#ifdef ADC4_PINS_GPIOA
	HAL_GPIO_DeInit(GPIOA, ADC4_PINS_GPIOA);
	#endif
	#ifdef ADC4_PINS_GPIOB
	HAL_GPIO_DeInit(GPIOB, ADC4_PINS_GPIOB);
	#endif
	#ifdef ADC4_PINS_GPIOC
	HAL_GPIO_DeInit(GPIOC, ADC4_PINS_GPIOC);
	#endif
	#ifdef ADC4_PINS_GPIOD
	HAL_GPIO_DeInit(GPIOD, ADC4_PINS_GPIOD);
	#endif
	#ifdef ADC4_PINS_GPIOE
	HAL_GPIO_DeInit(GPIOE, ADC4_PINS_GPIOE);
	#endif
	#ifdef ADC4_PINS_GPIOF
	HAL_GPIO_DeInit(GPIOF, ADC4_PINS_GPIOF);
	#endif

    /* ADC4 DMA DeInit */
	#if (ADC4_NUM != 0)
    HAL_DMA_DeInit(hadc->DMA_Handle);
	#endif
  /* USER CODE BEGIN ADC4_MspDeInit 1 */

  /* USER CODE END ADC4_MspDeInit 1 */
  }
  else if(hadc->Instance==ADC5)
  {
  /* USER CODE BEGIN ADC5_MspDeInit 0 */

  /* USER CODE END ADC5_MspDeInit 0 */
    /* Peripheral clock disable */
    HAL_RCC_ADC345_CLK_ENABLED--;
    if(HAL_RCC_ADC345_CLK_ENABLED==0){
      __HAL_RCC_ADC345_CLK_DISABLE();
    }

	#ifdef ADC5_PINS_GPIOA
	HAL_GPIO_DeInit(GPIOA, ADC5_PINS_GPIOA);
	#endif
	#ifdef ADC5_PINS_GPIOB
	HAL_GPIO_DeInit(GPIOB, ADC5_PINS_GPIOB);
	#endif
	#ifdef ADC5_PINS_GPIOC
	HAL_GPIO_DeInit(GPIOC, ADC5_PINS_GPIOC);
	#endif
	#ifdef ADC5_PINS_GPIOD
	HAL_GPIO_DeInit(GPIOD, ADC5_PINS_GPIOD);
	#endif
	#ifdef ADC5_PINS_GPIOE
	HAL_GPIO_DeInit(GPIOE, ADC5_PINS_GPIOE);
	#endif
	#ifdef ADC5_PINS_GPIOF
	HAL_GPIO_DeInit(GPIOF, ADC5_PINS_GPIOF);
	#endif

    /* ADC5 DMA DeInit */
	#if (ADC5_NUM != 0)
    HAL_DMA_DeInit(hadc->DMA_Handle);
	#endif
  /* USER CODE BEGIN ADC5_MspDeInit 1 */

  /* USER CODE END ADC5_MspDeInit 1 */
  }

}
/**
* @brief FDCAN MSP Initialization
* This function configures the hardware resources used in this example
* @param hfdcan: FDCAN handle pointer
* @retval None
*/
void HAL_FDCAN_MspInit(FDCAN_HandleTypeDef* fdcanHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(fdcanHandle->Instance==FDCAN1)
  {
  /* USER CODE BEGIN FDCAN1_MspInit 0 */

  /* USER CODE END FDCAN1_MspInit 0 */
    /* FDCAN1 clock enable */
    __HAL_RCC_FDCAN_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**FDCAN1 GPIO Configuration
    PA11     ------> FDCAN1_RX
    PA12     ------> FDCAN1_TX
    */
    GPIO_InitStruct.Pin = CAN_RX_Pin|CAN_TX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_FDCAN1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* FDCAN1 interrupt Init */
    HAL_NVIC_SetPriority(FDCAN1_IT0_IRQn, 2, 1);
    HAL_NVIC_EnableIRQ(FDCAN1_IT0_IRQn);
  /* USER CODE BEGIN FDCAN1_MspInit 1 */
		//Rx INT
		fdcanHandle->Instance->IE |= FDCAN_IE_RF0NE;	// Rx FIFO 0 new message interrupt enable
//		fdcanHandle->Instance->IE |= FDCAN_IE_TFEE;	//  Tx FIFO empty interrupt enable
//		fdcanHandle->Instance->ILS |= FDCAN_ILS_RXFIFO0;	//Rx FIFO 0 new message interrupt line
		fdcanHandle->Instance->ILE |= FDCAN_ILE_EINT0;	//Enable interrupt line 0
		
		//Tx INT
		fdcanHandle->Instance->IE |= FDCAN_IT_TX_FIFO_EMPTY;	//Transmission Cancellation Finished
		fdcanHandle->Instance->TXBTIE |= 0x01;	//Transmission interrupt enable
  /* USER CODE END FDCAN1_MspInit 1 */
  }
}

/**
* @brief FDCAN MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hfdcan: FDCAN handle pointer
* @retval None
*/
void HAL_FDCAN_MspDeInit(FDCAN_HandleTypeDef* hfdcan)
{
	if(hfdcan->Instance==FDCAN1)
	{
		/* USER CODE BEGIN FDCAN1_MspDeInit 0 */

		/* USER CODE END FDCAN1_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_FDCAN_CLK_DISABLE();

		/**FDCAN1 GPIO Configuration
    PA11     ------> FDCAN1_RX
    PA12     ------> FDCAN1_TX
		*/
		HAL_GPIO_DeInit(GPIOA, CAN_TX_Pin|CAN_RX_Pin);

		/* FDCAN1 interrupt DeInit */
		HAL_NVIC_DisableIRQ(FDCAN1_IT0_IRQn);
		/* USER CODE BEGIN FDCAN1_MspDeInit 1 */

		/* USER CODE END FDCAN1_MspDeInit 1 */
	}
}

void HAL_SPI_MspInit(SPI_HandleTypeDef* spiHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(spiHandle->Instance == SPI3)
	{
  /* USER CODE BEGIN SPI1_MspInit 0 */

  /* USER CODE END SPI1_MspInit 0 */
    /* SPI3 clock enable */		
		__HAL_RCC_SPI3_CLK_ENABLE();
		__HAL_RCC_GPIOC_CLK_ENABLE();
    /**SPI1 GPIO Configuration
    PC10     ------> SPI3_SCK
    PC11     ------> SPI3_MISO
    PC12     ------> SPI3_MOSI
    */		
		GPIO_InitStruct.Pin = SPI_CLK_Pin|SPI_MISO_Pin|SPI_MOSI_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
		GPIO_InitStruct.Alternate = GPIO_AF_SPIX;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	}
}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef* spiHandle)
{

  if(spiHandle->Instance==SPI1)
  {
  /* USER CODE BEGIN SPI1_MspDeInit 0 */

  /* USER CODE END SPI1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SPI1_CLK_DISABLE();

    /**SPI1 GPIO Configuration
    PB3     ------> SPI1_SCK
    PB4     ------> SPI1_MISO
    PB5     ------> SPI1_MOSI
    */
    HAL_GPIO_DeInit(GPIOB, SPI_CLK_Pin|SPI_MISO_Pin|SPI_MOSI_Pin);

  /* USER CODE BEGIN SPI1_MspDeInit 1 */

  /* USER CODE END SPI1_MspDeInit 1 */
  }
	else if(spiHandle ->Instance == SPI3)
	{
		  /* USER CODE END SPI1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SPI3_CLK_DISABLE();

    /**SPI1 GPIO Configuration
    PC10     ------> SPI1_SCK
    PC11     ------> SPI1_MISO
    PC12     ------> SPI1_MOSI
    */
    HAL_GPIO_DeInit(GPIOC, SPI_CLK_Pin|SPI_MISO_Pin|SPI_MOSI_Pin);		
	}
}

/**
* @brief TIM_Base MSP Initialization
* This function configures the hardware resources used in this example
* @param htim_base: TIM_Base handle pointer
* @retval None
*/
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{

 // GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(tim_baseHandle->Instance==TIM1)
  {
  /* USER CODE BEGIN TIM1_MspInit 0 */

  /* USER CODE END TIM1_MspInit 0 */
    /* TIM1 clock enable */
    __HAL_RCC_TIM1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**TIM1 GPIO Configuration
    PA6     ------> TIM1_BKIN
    */
//    GPIO_InitStruct.Pin = GPIO_PIN_6;
//    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//    GPIO_InitStruct.Alternate = GPIO_AF6_TIM1;
//    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* TIM1 interrupt Init */
//    HAL_NVIC_SetPriority(TIM1_BRK_TIM15_IRQn, 0, 0);
//    HAL_NVIC_EnableIRQ(TIM1_BRK_TIM15_IRQn);
    HAL_NVIC_SetPriority(TIM1_UP_TIM16_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM1_UP_TIM16_IRQn);
  /* USER CODE BEGIN TIM1_MspInit 1 */
//		HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
//		HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
//		htim1.Instance->DIER |= TIM_IT_UPDATE;	//enable update interrupt 
  /* USER CODE END TIM1_MspInit 1 */
  }
	else if(tim_baseHandle->Instance == TIM2)
	{
  /* USER CODE BEGIN TIM1_MspInit 0 */

  /* USER CODE END TIM1_MspInit 0 */
    /* TIM2 clock enable */
    __HAL_RCC_TIM2_CLK_ENABLE();
	}
}

void HAL_TIM_Encoder_MspInit(TIM_HandleTypeDef* tim_encoderHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(tim_encoderHandle->Instance==TIM4)
  {
  /* USER CODE BEGIN TIM4_MspInit 0 */

  /* USER CODE END TIM4_MspInit 0 */
    /* TIM4 clock enable */
    __HAL_RCC_TIM4_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**TIM4 GPIO Configuration
    PB6     ------> TIM4_CH1
    PB7     ------> TIM4_CH2
    */
    GPIO_InitStruct.Pin = CMD_ENCA_Pin|CMD_ENCB_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM4;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN TIM4_MspInit 1 */

  /* USER CODE END TIM4_MspInit 1 */
  }
	else if(tim_encoderHandle->Instance==TIM8)
  {
  /* USER CODE BEGIN TIM8_MspInit 0 */

  /* USER CODE END TIM8_MspInit 0 */
    /* TIM8 clock enable */
    __HAL_RCC_TIM8_CLK_ENABLE();

    __HAL_RCC_GPIOC_CLK_ENABLE();
    /**TIM8 GPIO Configuration
    PC6     ------> TIM8_CH1
    PC7     ------> TIM8_CH2
    */
    GPIO_InitStruct.Pin = M_ENCODE_A_Pin|M_ENCODE_B_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_TIM8;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* USER CODE BEGIN TIM4_MspInit 1 */
//  HAL_NVIC_SetPriority(TIM8_CC_IRQn, 1, 2);
//  HAL_NVIC_EnableIRQ(TIM8_CC_IRQn);
  /* USER CODE END TIM4_MspInit 1 */
  }
}
void HAL_TIM_MspPostInit(TIM_HandleTypeDef* timHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(timHandle->Instance==TIM1)
  {
  /* USER CODE BEGIN TIM1_MspPostInit 0 */

  /* USER CODE END TIM1_MspPostInit 0 */

    __HAL_RCC_GPIOB_CLK_ENABLE();	
		/**TIM1 GPIO Configuration   _1220_G4
    PB13     ------> TIM1_CH1N
    PB14     ------> TIM1_CH2N
    PA8     ------> TIM1_CH1
    PA9     ------> TIM1_CH2
    */
    GPIO_InitStruct.Pin = MOTOR_H1_Pin|MOTOR_H2_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF6_TIM1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = MOTOR_N1_Pin|MOTOR_N2_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF6_TIM1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);	


  /* USER CODE BEGIN TIM1_MspPostInit 1 */

  /* USER CODE END TIM1_MspPostInit 1 */
  }
	else if(timHandle->Instance == TIM2)
	{
  /* USER CODE BEGIN TIM2_MspPostInit 0 */
    __HAL_RCC_TIM2_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
  /* USER CODE END TIM2_MspPostInit 0 */
    /**TIM2 GPIO Configuration**
    PA15     ------> TIM2_CH1*/
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
	#ifdef TIM2_CHANNEL1_DO_Pin
	GPIO_InitStruct.Pin = TIM2_CHANNEL1_DO_Pin;
	HAL_GPIO_Init(TIM2_CHANNEL1_DO_GPIO_Port, &GPIO_InitStruct);		
	#endif	
	}

}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM1)
  {
  /* USER CODE BEGIN TIM1_MspDeInit 0 */

  /* USER CODE END TIM1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM1_CLK_DISABLE();

    /**TIM1 GPIO Configuration
    PB13    ------> TIM1_CH1N
    PB14    ------> TIM1_CH2N
    PA8     ------> TIM1_CH1
    PA9     ------> TIM1_CH2
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_8|GPIO_PIN_9);

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_13|GPIO_PIN_14);

    /* TIM1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM1_BRK_TIM15_IRQn);
    HAL_NVIC_DisableIRQ(TIM1_UP_TIM16_IRQn);
  /* USER CODE BEGIN TIM1_MspDeInit 1 */

  /* USER CODE END TIM1_MspDeInit 1 */
  }
	else if(tim_baseHandle->Instance==TIM2)
  {
  /* USER CODE BEGIN TIM2_MspDeInit 0 */

  /* USER CODE END TIM2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM2_CLK_DISABLE();
  /* USER CODE BEGIN TIM2_MspDeInit 1 */

  /* USER CODE END TIM2_MspDeInit 1 */
  }

}

void HAL_TIM_Encoder_MspDeInit(TIM_HandleTypeDef* tim_encoderHandle)
{

  if(tim_encoderHandle->Instance==TIM4)
  {
  /* USER CODE BEGIN TIM4_MspDeInit 0 */

  /* USER CODE END TIM4_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM4_CLK_DISABLE();

    /**TIM4 GPIO Configuration
    PB6     ------> TIM4_CH1
    PB7     ------> TIM4_CH2
    */
    HAL_GPIO_DeInit(GPIOB, CMD_ENCA_Pin|CMD_ENCB_Pin);

  /* USER CODE BEGIN TIM4_MspDeInit 1 */

  /* USER CODE END TIM4_MspDeInit 1 */
  }
  else if(tim_encoderHandle->Instance==TIM8)
  {
  /* USER CODE BEGIN TIM8_MspDeInit 0 */

  /* USER CODE END TIM8_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM8_CLK_DISABLE();

    /**TIM4 GPIO Configuration
    PC6     ------> TIM8_CH1
    PC7     ------> TIM8_CH2
    */
    HAL_GPIO_DeInit(GPIOB, M_ENCODE_A_Pin|M_ENCODE_B_Pin);

  /* USER CODE BEGIN TIM8_MspDeInit 1 */

  /* USER CODE END TIM8_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
/**
* @brief UART MSP Initialization
* This function configures the hardware resources used in this example
* @param huart: UART handle pointer
* @retval None
*/
void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  if(huart->Instance==USART2)
  {
	#if (UART2_DRIVER_EN == 1)
  /* USER CODE BEGIN USART2_MspInit 0 */

  /* USER CODE END USART2_MspInit 0 */

  /** Initializes the peripherals clocks
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2;
    PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

    /* Peripheral clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();

		GPIO_InitStruct.Pin = UART2_RX_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
		HAL_GPIO_Init(UART2_RX_GPIO_Port, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = UART2_TX_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
		HAL_GPIO_Init(UART2_TX_GPIO_Port, &GPIO_InitStruct);


    /* USART2 interrupt Init */
    HAL_NVIC_SetPriority(USART2_IRQn, UART2_PreemptionPriority, UART2RX_SubPriority);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspInit 1 */

  /* USER CODE END USART2_MspInit 1 */
	#endif //#if (UART2_DRIVER_EN == 1)
  }
  else if(huart->Instance==USART3)
  {
	#if (UART3_DRIVER_EN == 1)
  /* USER CODE BEGIN USART3_MspInit 0 */

  /* USER CODE END USART3_MspInit 0 */

  /** Initializes the peripherals clocks
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART3;
    PeriphClkInit.Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

    /* Peripheral clock enable */
    __HAL_RCC_USART3_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();
		
		GPIO_InitStruct.Pin = UART3_RX_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
		HAL_GPIO_Init(UART3_RX_GPIO_Port, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = UART3_TX_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
		HAL_GPIO_Init(UART3_TX_GPIO_Port, &GPIO_InitStruct);

    /* USART3 interrupt Init */
    HAL_NVIC_SetPriority(USART3_IRQn, UART3_PreemptionPriority, UART3RX_SubPriority);
    HAL_NVIC_EnableIRQ(USART3_IRQn);

	/* USER CODE BEGIN USART3_MspInit 1 */

  /* USER CODE END USART3_MspInit 1 */
	#endif //	#if (UART3_DRIVER_EN == 1)
  }

}

/**
* @brief UART MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param huart: UART handle pointer
* @retval None
*/
void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{
  if(huart->Instance==USART2)
  {
	#if (UART2_DRIVER_EN == 1)
  /* USER CODE BEGIN USART2_MspDeInit 0 */

  /* USER CODE END USART2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();

    HAL_GPIO_DeInit(UART2_RX_GPIO_Port, UART2_RX_Pin);

    HAL_GPIO_DeInit(UART2_TX_GPIO_Port, UART2_TX_Pin);

    /* USART2 interrupt DeInit */
    HAL_NVIC_DisableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspDeInit 1 */

  /* USER CODE END USART2_MspDeInit 1 */
	#endif //	#if (UART2_DRIVER_EN == 1)
  }
  else if(huart->Instance==USART3)
  {
	#if (UART3_DRIVER_EN == 1)
  /* USER CODE BEGIN USART3_MspDeInit 0 */

  /* USER CODE END USART3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART3_CLK_DISABLE();

    HAL_GPIO_DeInit(UART3_RX_GPIO_Port, UART3_RX_Pin);

    HAL_GPIO_DeInit(UART3_TX_GPIO_Port, UART3_TX_Pin);

    /* USART3 interrupt DeInit */
    HAL_NVIC_DisableIRQ(USART3_IRQn);
	/* USER CODE BEGIN USART3_MspDeInit 1 */

  /* USER CODE END USART3_MspDeInit 1 */
	#endif //	#if (UART3_DRIVER_EN == 1)
  }

}



/* USER CODE BEGIN 1 */
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
