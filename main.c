/* USER CODE BEGIN Includes */
#include "rtc.h"
#include "scheduler.h"
#include "alerts.h"
#include "user_data.h"
#include "user_confirmation.h"
/* USER CODE END Includes */

// ... (rest of your existing code remains unchanged)

/* USER CODE BEGIN PV */
// (Add any global variables here if needed)
/* USER CODE END PV */

/* USER CODE BEGIN PFP */
// (Add any private function prototypes here if needed)
/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
// (Add any custom user code here if needed)
/* USER CODE END 0 */

int main(void) {
  /* USER CODE BEGIN 1 */
  // (Add any additional initialization code here if needed)
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  // ... (existing initialization code)

  /* USER CODE BEGIN 2 */
  // Initialize additional components
  RTC_Init();
  UserData_Init();
  Scheduler_Init();
  Alerts_Init();
  UserConfirmation_Init();

  // (Add any additional user setup code here if needed)
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1) {
    /* USER CODE BEGIN 3 */
    // Update scheduler to check for any reminders
    Scheduler_Update();

    // Update user confirmation to check for button presses
    UserConfirmation_Update();

    // Additional application code as needed

    // Small delay to prevent CPU hogging, adjust as per requirement
    HAL_Delay(10);
  }
  /* USER CODE END 3 */
}



/* USER CODE BEGIN PV */
// Define GPIO pins for the buzzer and button
#define BUZZER_PIN GPIO_PIN_5
#define BUZZER_GPIO_PORT GPIOA
#define BUTTON_PIN GPIO_PIN_13
#define BUTTON_GPIO_PORT GPIOC
/* USER CODE END PV */

// ... (previous code)

static void MX_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // ... (existing GPIO initialization code)

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

int main(void) {
    // ... (previous initialization code)

    /* USER CODE BEGIN 2 */
    // Additional initialization if needed
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



