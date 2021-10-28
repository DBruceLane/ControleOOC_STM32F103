/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ssd1306.h"
#include "fonts.h"
#include "test.h"
#include "stdbool.h"
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
I2C_HandleTypeDef hi2c1;

TIM_HandleTypeDef htim4;

/* USER CODE BEGIN PV */
uint32_t MenuAtual = 0;
uint32_t counterOpcao = 0;
uint32_t counterPrev = 0;
char txtCounter[10];
_Bool ligarMotor = false;
_Bool StepAlta = true;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_TIM4_Init(void);
/* USER CODE BEGIN PFP */
void HAL_TIM_PeriodElapsedCallback (TIM_HandleTypeDef * htim) // Interrupt do passo do motor
{
  if(StepAlta)
  {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 1); // Pino Step
    StepAlta = false;
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 1);
  }
  else
  {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 0); // Pino Step
    StepAlta = true;
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 0);
  }

/*
  static uint32_t millis = 0;
  millis++;
  if (millis % 1000 == 0) {
    HAL_GPIO_WritePin(GPIOB, MotorSTEP_Pin, 0);
  }
  */
  
}

void MenuHandler(void)
{
  if(MenuAtual==0)
    {
      
      itoa(counterOpcao, txtCounter, 10); // Coloca valor do counter na txtCounter
      if (counterPrev != counterOpcao) // Atualiza tela so se mudar contador
      {
        SSD1306_Clear();
        counterPrev = counterOpcao;
        SSD1306_GotoXY(2, 2);
        SSD1306_Puts(txtCounter, &Font_7x10, 1);
        SSD1306_GotoXY(2, 12);
        SSD1306_Puts("1 Outro Menu", &Font_7x10, 1);
        
        SSD1306_UpdateScreen();
      }
    }
    else if (MenuAtual==1)
    {
      
      itoa(counterOpcao, txtCounter, 10); // Coloca valor do counter na txtCounter
      if (counterPrev != counterOpcao) // Atualiza tela so se mudar contador
      {
        SSD1306_Clear();
        counterPrev = counterOpcao;
        SSD1306_GotoXY(2, 2);
        SSD1306_Puts(txtCounter, &Font_7x10, 1);
        SSD1306_GotoXY(2, 12);
        SSD1306_Puts("0 Voltar", &Font_7x10, 1);
        SSD1306_GotoXY(2, 22);
        SSD1306_Puts("1 Ligar Motor", &Font_7x10, 1);
        SSD1306_GotoXY(2, 32);
        SSD1306_Puts("2 Desligar Motor", &Font_7x10, 1);
        
        SSD1306_UpdateScreen();
      }
    }
    
}

void ClickHandler(void)
{
  //SSD1306_Clear();
  if(MenuAtual == 0)
  {
    if(counterOpcao == 1)
    {
      MenuAtual = 1;
    }
  }
  if(MenuAtual == 1)
  {
    if(counterOpcao == 1) //Ligar Interrupt
    {
      HAL_TIM_Base_Start_IT(&htim4);
    }
    else if (counterOpcao == 2) // Desligar Interrupt
    {
      HAL_TIM_Base_Stop_IT(&htim4);
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 0);
    }
    else if(counterOpcao == 0)
    {
      MenuAtual = 0;
    }
  }
  
  
  counterPrev = 99; // Forca a atualizar a tela
  
  
}
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
  /*uint32_t i;
  float Temp;
  uint32_t counter = 0;*/
  GPIO_PinState aState;
  GPIO_PinState aLastState = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6);
  uint32_t counter = 0;
  
  

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
  MX_I2C1_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  /*SSD1306_Init(); // initialize the display

    SSD1306_GotoXY(10, 10);                // goto 10, 10
    SSD1306_Puts("HELLO", &Font_11x18, 1); // print Hello
    SSD1306_GotoXY(10, 30);
    SSD1306_Puts("WORLD !!", &Font_11x18, 1);
    SSD1306_UpdateScreen();*/
  SSD1306_Init();

  while (1)
  {
    
    /*if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10) == GPIO_PIN_RESET)
    {
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 1);
    }
    else
    {
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 0);
    }*/

    // Contador Rot Button
    aState = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6);
    if (aState != aLastState)
    {
      if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7) != aState)
      {
        counter--; // Sentido Horario
      }
      else
      {
        counter++; // Sentido Anti Horario
      }
      if (counter % 2 == 0)
      {
        counterOpcao = counter/2;
      }
      if(counter>100)
      {
        counter = 0;
      }
    }

    aLastState = aState;


    // OLED
    /*
    MenuHandler();
    if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10))
    {
      ClickHandler();
    }
    */
    MenuHandler();
    
  
    if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10))
    {
      //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 1);
      ClickHandler();
    }
    else
    {
      //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 0);
    }
    
    
    
    // update screen
    /*for (i = 0; i < 8; i++)
    {
      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 0);
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 0);
      //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 1);
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 1);
      HAL_Delay(2500);
      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 1);
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 1);
      //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 0);
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 0);
      HAL_Delay(2500);
    }*/
    //HAL_Delay(800);

    /*Temp = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5);
    Temp = ((Temp * 1.1 / (1023)) / 0.01);

    if (Temp < 25)
    {
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 1);
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 0);
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 0);
    }
    else if (Temp >= 25 && Temp < 30)
    {
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 1);
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 0);
    }
    else if (Temp >= 30 && Temp < 35)
    {
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 0);
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 0);
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 1);
    }
    else if (Temp >= 35 && Temp < 40)
    {
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 0);
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 1);
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 1);
    }
    else
    {
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 0);
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 0);
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 0);
    }*/

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

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 400000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 7200-1;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 10000;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1|GPIO_PIN_8|GPIO_PIN_10, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA1 PA8 PA10 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_8|GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PA6 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PB10 */
  GPIO_InitStruct.Pin = GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
