#include "stm32f4xx_hal.h"
#include "thunderpack.h"

#define SPEED_SLOW 800
#define SPEED_FAST 200

static void gpio_init(void);

int main(void) {
  // Init the system
  HAL_Init();
  thunderpack_clock_init();

  // Setup GPIO
  gpio_init();

  int blinkSpeed = SPEED_SLOW;
  while (1) {
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_0);

    // Blink faster while the button (PB4) has been pressed
    if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4)) {
      blinkSpeed = SPEED_FAST;
    } else {
      blinkSpeed = SPEED_SLOW;
    }
    HAL_Delay(blinkSpeed);
  }
}

/**
  * Setup GPIO pins
  */
static void gpio_init(void) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  // GPIO Ports Clock Enable
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  // Configure GPIO pin Output Level
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);

  // Configure LED 1: PA0
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  // Configure Button: PB4
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}
