/* USER CODE BEGIN Header */
//... (Header comments)
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h" // Adjust include path based on your HAL

/* USER CODE BEGIN Includes */
#include "lcd_i2c.h" // Replace with your actual LCD library header
/* USER CODE END Includes */

/* USER CODE BEGIN PV */
// Define GPIO pins for the buzzer and button
#define BUZZER_PIN GPIO_PIN_5
#define BUZZER_GPIO_PORT GPIOA
#define BUTTON_PIN GPIO_PIN_13
#define BUTTON_GPIO_PORT GPIOC
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
    // (Add any additional initialization code here if needed)
    /* USER CODE END 1 */

    /* MCU Configuration--------------------------------------------------------*/
    HAL_Init();

    /* Configure the system clock */
    SystemClock_Config();

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_USART2_UART_Init();
    MX_RTC_Init(); // Initialize RTC

    /* USER CODE BEGIN 2 */
    // Initialize LCD
    LCD_Init(); // Replace with your actual initialization function

    // Display a welcome message on LCD
    LCD_Clear(); // Clear the LCD screen
    LCD_SetCursor(0, 0); // Set cursor to the first line
    LCD_Print("Medication"); // Print a message
    LCD_SetCursor(1, 0); // Set cursor to the second line
    LCD_Print("Reminder"); // Print a message

    // ... (rest of your initialization code)
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1) {
        /* USER CODE BEGIN 3 */
        // Check button state
        if (HAL_GPIO_ReadPin(BUTTON_GPIO_PORT, BUTTON_PIN) == GPIO_PIN_SET) {
            // If button is pressed, turn on the buzzer
            HAL_GPIO_WritePin(BUZZER_GPIO_PORT, BUZZER_PIN, GPIO_PIN_SET);
        } else {
            // If button is not pressed, turn off the buzzer
            HAL_GPIO_WritePin(BUZZER_GPIO_PORT, BUZZER_PIN, GPIO_PIN_RESET);
        }

        // Additional application code as needed

        HAL_Delay(10); // Delay for debouncing and to prevent CPU hogging
    }
    /* USER CODE END 3 */
}

void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
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
    //... (RTC initialization code - you need to implement this based on your RTC setup)
}

void Error_Handler(void) {
    //... (Error Handler code)
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line) {
    //... (Assert Failed code)
}
#endif /* USE_FULL_ASSERT */
