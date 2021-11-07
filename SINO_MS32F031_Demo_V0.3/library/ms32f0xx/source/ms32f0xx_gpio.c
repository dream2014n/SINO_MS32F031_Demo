/* Includes ------------------------------------------------------------------*/
#include "ms32f0xx_gpio.h"
#include "ms32f0xx_bus.h"


/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @addtogroup GPIO_EF_Init
  * @{
  */

/**
  * @brief  De-initialize GPIO registers (Registers restored to their default values).
  * @param  GPIOx GPIO Port
  *          This parameter can be one of the following values:
  *            @arg @ref GPIOA  GPIO A port
  *            @arg @ref GPIOB  GPIO B port
  *            @arg @ref GPIOC  GPIO C port
  *            @arg @ref GPIOF  GPIO F port
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: GPIO registers are de-initialized
  *          - ERROR:   Wrong GPIO Port
  */
ErrorStatus MS32_GPIO_DeInit(GPIO_TypeDef *GPIOx) {
  ErrorStatus status = SUCCESS;

  /* Force and Release reset on clock of GPIOx Port */
  if (GPIOx == GPIOA) {
    MS32_AHB1_GRP1_EnableClock(MS32_AHB1_GRP1_PERIPH_GPIOA);
    MS32_AHB1_GRP1_ForceReset(MS32_AHB1_GRP1_PERIPH_GPIOA);
    MS32_AHB1_GRP1_ReleaseReset(MS32_AHB1_GRP1_PERIPH_GPIOA);
  } else if (GPIOx == GPIOB) {
    MS32_AHB1_GRP1_EnableClock(MS32_AHB1_GRP1_PERIPH_GPIOB);
    MS32_AHB1_GRP1_ForceReset(MS32_AHB1_GRP1_PERIPH_GPIOB);
    MS32_AHB1_GRP1_ReleaseReset(MS32_AHB1_GRP1_PERIPH_GPIOB);
  } else if (GPIOx == GPIOC) {
    MS32_AHB1_GRP1_EnableClock(MS32_AHB1_GRP1_PERIPH_GPIOC);
    MS32_AHB1_GRP1_ForceReset(MS32_AHB1_GRP1_PERIPH_GPIOC);
    MS32_AHB1_GRP1_ReleaseReset(MS32_AHB1_GRP1_PERIPH_GPIOC);
  } else if (GPIOx == GPIOF) {
    MS32_AHB1_GRP1_EnableClock(MS32_AHB1_GRP1_PERIPH_GPIOF);
    MS32_AHB1_GRP1_ForceReset(MS32_AHB1_GRP1_PERIPH_GPIOF);
    MS32_AHB1_GRP1_ReleaseReset(MS32_AHB1_GRP1_PERIPH_GPIOF);
  } else {
    status = ERROR;
  }

  return status;
}

/**
  * @brief Set each @ref MS32_GPIO_InitTypeDef field to default value.
  * @param GpioInitStr pointer to a @ref MS32_GPIO_InitTypeDef structure
  *                          whose fields will be set to default values.
  * @retval None
  */

void MS32_GPIO_StructInit(MS32_GPIO_InitTypeDef *GpioInitStr) {
  /* Reset GPIO init structure parameters values */
  GpioInitStr->Pin        = MS32_GPIO_PIN_ALL;
  GpioInitStr->Mode       = MS32_GPIO_MODE_ANALOG;
  GpioInitStr->Speed      = MS32_GPIO_SPEED_FREQ_LOW;
  GpioInitStr->OutputType = MS32_GPIO_OUTPUT_PUSHPULL;
  GpioInitStr->Pull       = MS32_GPIO_PULL_NO;
  GpioInitStr->Alternate  = MS32_GPIO_AF_0;
}

/**
  * @brief  Initialize GPIO registers according to the specified parameters in GpioInitStr.
  * @param  GPIOx GPIO Port
  *          This parameter can be one of the following values:
  *            @arg @ref GPIOA  GPIO A port
  *            @arg @ref GPIOB  GPIO B port
  *            @arg @ref GPIOC  GPIO C port
  *            @arg @ref GPIOF  GPIO F port
  * @param  GpioInitStr pointer to a @ref MS32_GPIO_InitTypeDef structure
  *         that contains the configuration information for the specified GPIO peripheral.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: GPIO registers are initialized according to GpioInitStr content
  *          - ERROR:   Not applicable
  */
ErrorStatus MS32_GPIO_Init(GPIO_TypeDef *GPIOx, MS32_GPIO_InitTypeDef *GpioInitStr) {
  ErrorStatus status = SUCCESS;
  uint32_t pinpos;
  uint32_t currentpin;

  /* ------------------------- Initialize GPIO clock ------------------ */
  if (GPIOx == GPIOA) {
    MS32_AHB1_GRP1_EnableClock(MS32_AHB1_GRP1_PERIPH_GPIOA);
  } else if (GPIOx == GPIOB) {
    MS32_AHB1_GRP1_EnableClock(MS32_AHB1_GRP1_PERIPH_GPIOB);
  } else if (GPIOx == GPIOC) {
    MS32_AHB1_GRP1_EnableClock(MS32_AHB1_GRP1_PERIPH_GPIOC);
  } else if (GPIOx == GPIOF) {
    MS32_AHB1_GRP1_EnableClock(MS32_AHB1_GRP1_PERIPH_GPIOF);
  } else {
    status = ERROR;
  }

  /* ------------------------- Configure the port pins ---------------- */
  if (status == SUCCESS) {
    /* Initialize  pinpos on first pin set */
    pinpos = 0;

    /* Configure the port pins */
    while (((GpioInitStr->Pin) >> pinpos) != 0x00u) {
      /* Get current io position */
      currentpin = (GpioInitStr->Pin) & (0x00000001uL << pinpos);

      if (currentpin != 0x00u) {
        /* Alternate configuration */
        if (GpioInitStr->Mode == MS32_GPIO_MODE_ALTERNATE) {
          if (currentpin < MS32_GPIO_PIN_8) {
            MS32_GPIO_SetAFPin_0_7(GPIOx, currentpin, GpioInitStr->Alternate);
          } else {
            MS32_GPIO_SetAFPin_8_15(GPIOx, currentpin, GpioInitStr->Alternate);
          }
        }

        /* Speed mode configuration */
        MS32_GPIO_SetPinSpeed(GPIOx, currentpin, GpioInitStr->Speed);
        /* Pull-up Pull down resistor configuration*/
        MS32_GPIO_SetPinPull(GPIOx, currentpin, GpioInitStr->Pull);
        /* Pin Mode configuration */
        MS32_GPIO_SetPinMode(GPIOx, currentpin, GpioInitStr->Mode);
      }
      pinpos++;
    }

    /* Output mode configuration*/
    MS32_GPIO_SetPinOutputType(GPIOx, GpioInitStr->Pin, GpioInitStr->OutputType);
  }

  return status;
}

/**
  * @brief  Control GPIO output voltage level.
  * @param  GPIOx GPIO Port
  *          This parameter can be one of the following values:
  *            @arg @ref GPIOA  GPIO A port
  *            @arg @ref GPIOB  GPIO B port
  *            @arg @ref GPIOC  GPIO C port
  *            @arg @ref GPIOF  GPIO F port
  * @param  Pin GPIO Pin
  *          This parameter can be one of the following values:
  *            @arg @ref MS32_GPIO_PIN_0
  *            @arg @ref MS32_GPIO_PIN_1
  *            @arg @ref MS32_GPIO_PIN_2
  *            @arg @ref MS32_GPIO_PIN_3
  *            @arg @ref MS32_GPIO_PIN_4
  *            @arg @ref MS32_GPIO_PIN_5
  *            @arg @ref MS32_GPIO_PIN_6
  *            @arg @ref MS32_GPIO_PIN_7
  *            @arg @ref MS32_GPIO_PIN_8
  *            @arg @ref MS32_GPIO_PIN_9
  *            @arg @ref MS32_GPIO_PIN_10
  *            @arg @ref MS32_GPIO_PIN_11
  *            @arg @ref MS32_GPIO_PIN_12
  *            @arg @ref MS32_GPIO_PIN_13
  *            @arg @ref MS32_GPIO_PIN_14
  *            @arg @ref MS32_GPIO_PIN_15
  *            @arg @ref MS32_GPIO_PIN_ALL
  * @param  Output GPIO output method
  *         This parameter can be one of the following values:
  *            @arg @ref MS32_GPIO_OUTPUT_HIGH  the gpio output high
  *            @arg @ref MS32_GPIO_OUTPUT_LOW   the gpio output low
  *            @arg @ref MS32_GPIO_OUTPUT_REV   the gpio output reverse
  * @retval None
  */
void MS32_GPIO_Output(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Output) {
  switch (Output) {
    case MS32_GPIO_OUTPUT_HIGH:
      MS32_GPIO_SetOutputPin(GPIOx, Pin);
      break;
    case MS32_GPIO_OUTPUT_LOW:
      MS32_GPIO_ResetOutputPin(GPIOx, Pin);
      break;
    case MS32_GPIO_OUTPUT_REV:
      MS32_GPIO_TogglePin(GPIOx, Pin);
      break;
    default:
      break;
  }
}

/**
  * @brief  Get GPIO input voltage level.
  * @param  GPIOx GPIO Port
  *          This parameter can be one of the following values:
  *            @arg @ref GPIOA  GPIO A port
  *            @arg @ref GPIOB  GPIO B port
  *            @arg @ref GPIOC  GPIO C port
  *            @arg @ref GPIOF  GPIO F port
  * @param  Pin GPIO Pin
  *          This parameter can be one of the following values:
  *            @arg @ref MS32_GPIO_PIN_0
  *            @arg @ref MS32_GPIO_PIN_1
  *            @arg @ref MS32_GPIO_PIN_2
  *            @arg @ref MS32_GPIO_PIN_3
  *            @arg @ref MS32_GPIO_PIN_4
  *            @arg @ref MS32_GPIO_PIN_5
  *            @arg @ref MS32_GPIO_PIN_6
  *            @arg @ref MS32_GPIO_PIN_7
  *            @arg @ref MS32_GPIO_PIN_8
  *            @arg @ref MS32_GPIO_PIN_9
  *            @arg @ref MS32_GPIO_PIN_10
  *            @arg @ref MS32_GPIO_PIN_11
  *            @arg @ref MS32_GPIO_PIN_12
  *            @arg @ref MS32_GPIO_PIN_13
  *            @arg @ref MS32_GPIO_PIN_14
  *            @arg @ref MS32_GPIO_PIN_15
  *            @arg @ref MS32_GPIO_PIN_ALL
  * @retval An LevelStatus enumeration value:
  *          - SET:   GPIO input level is high.
  *          - RESET: GPIO input level is low.
  */
LevelStatus MS32_GPIO_Input(GPIO_TypeDef *GPIOx, uint32_t Pin) {
  LevelStatus status;

  if (MS32_GPIO_IsInputPinSet(GPIOx, Pin)) {
    status = SET;
  } else {
    status = RESET;
  }

  return status;
}

/**
  * @brief  Get GPIO input voltage level.
  * @param  GPIOx GPIO Port
  *          This parameter can be one of the following values:
  *            @arg @ref GPIOA  GPIO A port
  *            @arg @ref GPIOB  GPIO B port
  *            @arg @ref GPIOC  GPIO C port
  *            @arg @ref GPIOF  GPIO F port
  * @param  Pin GPIO Pin
  *          This parameter can be one of the following values:
  *            @arg @ref MS32_GPIO_PIN_0
  *            @arg @ref MS32_GPIO_PIN_1
  *            @arg @ref MS32_GPIO_PIN_2
  *            @arg @ref MS32_GPIO_PIN_3
  *            @arg @ref MS32_GPIO_PIN_4
  *            @arg @ref MS32_GPIO_PIN_5
  *            @arg @ref MS32_GPIO_PIN_6
  *            @arg @ref MS32_GPIO_PIN_7
  *            @arg @ref MS32_GPIO_PIN_8
  *            @arg @ref MS32_GPIO_PIN_9
  *            @arg @ref MS32_GPIO_PIN_10
  *            @arg @ref MS32_GPIO_PIN_11
  *            @arg @ref MS32_GPIO_PIN_12
  *            @arg @ref MS32_GPIO_PIN_13
  *            @arg @ref MS32_GPIO_PIN_14
  *            @arg @ref MS32_GPIO_PIN_15
  *            @arg @ref MS32_GPIO_PIN_ALL
  * @retval A ErrorStatus enumeration value:
  *          - SUCCESS: finish locking gpio
  *          - ERROR: not applicable
  */
ErrorStatus MS32_GPIO_Lock(GPIO_TypeDef *GPIOx, uint32_t Pin) {
  ErrorStatus status;

  MS32_GPIO_LockPin(GPIOx, Pin);
  if (READ_BIT(GPIOx->LCKR, (Pin | GPIO_LCKR_LCKK)) == (Pin | GPIO_LCKR_LCKK)) {
    status = SUCCESS;
  } else {
    status = ERROR;
  }

  return status;
}

/******************************** END OF FILE *********************************/
