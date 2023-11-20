/* USER CODE BEGIN Header */
//... (Header comments)
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h" // Adjust include path based on your HAL

/* USER CODE BEGIN Includes */
#include "lcd_i2c.h" // Include your LCD library here
/* USER CODE END Includes */

/* USER CODE BEGIN PV */
#define BUZZER_PIN GPIO_PIN_5
#define BUZZER_GPIO_PORT GPIOA
#define BUTTON_PIN GPIO_PIN_13
#define BUTTON_GPIO_PORT GPIOC
uint32_t buzzerStartTime = 0;
uint32_t buttonPressTime = 0;
uint32_t totalTime = 0;
uint32_t pressCount = 0;
float averageTime = 0.0;
bool buzzerActive = false;
/* USER CODE END PV */

/* USER CODE BEGIN PFP */
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_RTC_Init(void); // Placeholder for RTC initialization function
/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
// (Add any custom user code here if needed)
/* USER CODE END 0 */

int main(void) {
    /* USER CODE BEGIN 1 */
    // (Additional initialization code here if needed)
    /* USER CODE END 1 */

    /* MCU Configuration--------------------------------------------------------*/
    HAL_Init();
    SystemClock_Config();

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_USART2_UART_Init();
    MX_RTC_Init(); // Initialize RTC

    /* USER CODE BEGIN 2 */
  HD44780_Init(2);
  HD44780_Clear();
  HD44780_SetCursor(0,0);
  HD44780_PrintStr("HELLO");
  HD44780_SetCursor(10,1);
  HD44780_PrintStr("WORLD");
  HAL_Delay(2000);

  HD44780_Clear();
  HD44780_SetCursor(0,0);
  HD44780_PrintStr("HELLO");
  HAL_Delay(2000);
  HD44780_NoBacklight();
  HAL_Delay(2000);
  HD44780_Backlight();

  HAL_Delay(2000);
  HD44780_Cursor();
  HAL_Delay(2000);
  HD44780_Blink();
  HAL_Delay(5000);
  HD44780_NoBlink();
  HAL_Delay(2000);
  HD44780_NoCursor();
  HAL_Delay(2000);

  HD44780_NoDisplay();
  HAL_Delay(2000);
  HD44780_Display();

  HD44780_Clear();
  HD44780_SetCursor(0,0);
  HD44780_PrintStr("Learning STM32 with LCD is fun :-)");
  int x;
  for(int x=0; x<40; x=x+1)
  {
    HD44780_ScrollDisplayLeft();  //HD44780_ScrollDisplayRight();
    HAL_Delay(500);
  }

  char snum[5];
  for ( int x = 1; x <= 200 ; x++ )
  {
    itoa(x, snum, 10);
    HD44780_Clear();
    HD44780_SetCursor(0,0);
    HD44780_PrintStr(snum);
    HAL_Delay (1000);
  }
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1) {
        /* USER CODE BEGIN 3 */
        // Example buzzer activation condition (modify as per your application logic)
        if (/* condition to start buzzer */) {
            HAL_GPIO_WritePin(BUZZER_GPIO_PORT, BUZZER_PIN, GPIO_PIN_SET);
            buzzerStartTime = HAL_GetTick();
            buzzerActive = true;
        }

        // Check button state
        if (HAL_GPIO_ReadPin(BUTTON_GPIO_PORT, BUTTON_PIN) == GPIO_PIN_SET && buzzerActive) {
            HAL_GPIO_WritePin(BUZZER_GPIO_PORT, BUZZER_PIN, GPIO_PIN_RESET);
            buzzerActive = false;

            // Calculate time taken and update average
            buttonPressTime = HAL_GetTick();
            uint32_t timeTaken = buttonPressTime - buzzerStartTime;
            totalTime += timeTaken;
            pressCount++;
            averageTime = (float)totalTime / pressCount;

            // Display the average time on the LCD or send it over UART
            // LCD_Print("Avg Time: %f", averageTime); // Placeholder
        }

        HAL_Delay(10);
    }
    /* USER CODE END 3 */
}

void SystemClock_Config(void) {
    //... (System clock configuration code)
}

static void MX_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    //... (GPIO initialization code)

    /* USER CODE BEGIN 2 */
    // Buzzer GPIO Initialization
    GPIO_InitStruct.Pin = BUZZER_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(BUZZER_GPIO_PORT, &GPIO_InitStruct);

    // Button GPIO Initialization
    GPIO_InitStruct.Pin = BUTTON_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(BUTTON_GPIO_PORT, &GPIO_InitStruct);
    /* USER CODE END 2 */
}

static void MX_USART2_UART_Init(void) {
    //... (USART2 initialization code)
}

static void MX_RTC_Init(void) {
    //... (RTC initialization code)
}

void Error_Handler(void) {
    //... (Error Handler code)
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line) {
    //... (Assert Failed code)
}
#endif /* USE_FULL_ASSERT */
