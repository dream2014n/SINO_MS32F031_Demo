/* Includes ------------------------------------------------------------------*/
#include "ms32f0xx_bus.h"
#include "ms32f0xx_exti.h"


/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @addtogroup EXTI_EF_Init
  * @{
  */

/**
  * @brief  De-initialize the EXTI registers to their default reset values.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: EXTI registers are de-initialized
  *          - ERROR: not applicable
  */
ErrorStatus MS32_EXTI_DeInit(void) {
  /* Interrupt mask register set to default reset values */
  MS32_EXTI_WriteReg(IMR,   0x0FF40000U);
  /* Event mask register set to default reset values */
  MS32_EXTI_WriteReg(EMR,   0x00000000U);
  /* Rising Trigger selection register set to default reset values */
  MS32_EXTI_WriteReg(RTSR,  0x00000000U);
  /* Falling Trigger selection register set to default reset values */
  MS32_EXTI_WriteReg(FTSR,  0x00000000U);
  /* Software interrupt event register set to default reset values */
  MS32_EXTI_WriteReg(SWIER, 0x00000000U);
  /* Pending register clear */
  MS32_EXTI_WriteReg(PR,    0x007BFFFFU);

  return SUCCESS;
}

/**
  * @brief  Set each @ref MS32_EXTI_InitTypeDef field to default value.
  * @param  ExtiInitStr Pointer to a @ref MS32_EXTI_InitTypeDef structure.
  * @retval None
  */
void MS32_EXTI_StructInit(MS32_EXTI_InitTypeDef *ExtiInitStr) {
  ExtiInitStr->Line_0_31   = MS32_EXTI_LINE_NONE;
  ExtiInitStr->LineCommand = DISABLE;
  ExtiInitStr->Mode        = MS32_EXTI_MODE_IT;
  ExtiInitStr->Trigger     = MS32_EXTI_TRIGGER_FALLING;
}

/**
  * @brief  Initialize the EXTI registers according to the specified parameters in ExtiInitStr.
  * @param  ExtiInitStr pointer to a @ref MS32_EXTI_InitTypeDef structure.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: EXTI registers are initialized
  *          - ERROR: not applicable
  */
ErrorStatus MS32_EXTI_Init(MS32_EXTI_InitTypeDef *ExtiInitStr) {
  ErrorStatus status = SUCCESS;

  /* ENABLE LineCommand */
  if (ExtiInitStr->LineCommand == ENABLE) {
    /* Configure EXTI Lines in range from 0 to 31 */
    if (ExtiInitStr->Line_0_31 != MS32_EXTI_LINE_NONE) {
      switch (ExtiInitStr->Mode) {
        case MS32_EXTI_MODE_IT:
          /* First Disable Event on provided Lines */
          MS32_EXTI_DisableEvent_0_31(ExtiInitStr->Line_0_31);
          /* Then Enable IT on provided Lines */
          MS32_EXTI_EnableIT_0_31(ExtiInitStr->Line_0_31);
          break;
        case MS32_EXTI_MODE_EVENT:
          /* First Disable IT on provided Lines */
          MS32_EXTI_DisableIT_0_31(ExtiInitStr->Line_0_31);
          /* Then Enable Event on provided Lines */
          MS32_EXTI_EnableEvent_0_31(ExtiInitStr->Line_0_31);
          break;
        case MS32_EXTI_MODE_IT_EVENT:
          /* Directly Enable IT & Event on provided Lines */
          MS32_EXTI_EnableIT_0_31(ExtiInitStr->Line_0_31);
          MS32_EXTI_EnableEvent_0_31(ExtiInitStr->Line_0_31);
          break;
        default:
          status = ERROR;
          break;
      }

      if (ExtiInitStr->Trigger != MS32_EXTI_TRIGGER_NONE) {
        switch (ExtiInitStr->Trigger) {
          case MS32_EXTI_TRIGGER_RISING:
            /* First Disable Falling Trigger on provided Lines */
            MS32_EXTI_DisableFallingTrig_0_31(ExtiInitStr->Line_0_31);
            /* Then Enable Rising Trigger on provided Lines */
            MS32_EXTI_EnableRisingTrig_0_31(ExtiInitStr->Line_0_31);
            break;
          case MS32_EXTI_TRIGGER_FALLING:
            /* First Disable Rising Trigger on provided Lines */
            MS32_EXTI_DisableRisingTrig_0_31(ExtiInitStr->Line_0_31);
            /* Then Enable Falling Trigger on provided Lines */
            MS32_EXTI_EnableFallingTrig_0_31(ExtiInitStr->Line_0_31);
            break;
          case MS32_EXTI_TRIGGER_RISING_FALLING:
            /* Directly Enable Rising and Falling Trigger on provided Lines */
            MS32_EXTI_EnableRisingTrig_0_31(ExtiInitStr->Line_0_31);
            MS32_EXTI_EnableFallingTrig_0_31(ExtiInitStr->Line_0_31);
            break;
          default:
            status = ERROR;
            break;
        }
      }
    }
  } else {
    /* DISABLE LineCommand */
    /* De-configure EXTI Lines in range from 0 to 31 */
    MS32_EXTI_DisableIT_0_31(ExtiInitStr->Line_0_31);
    MS32_EXTI_DisableEvent_0_31(ExtiInitStr->Line_0_31);
  }

  return status;
}

/**
  * @brief  Initializes the EXTI pin according to the specified parameters.
  * @param  ExtiLine  This parameter can be a combination of the following values:
  *         @arg @ref MS32_EXTI_LINE_0
  *         @arg @ref MS32_EXTI_LINE_1
  *         @arg @ref MS32_EXTI_LINE_2
  *         @arg @ref MS32_EXTI_LINE_3
  *         @arg @ref MS32_EXTI_LINE_4
  *         @arg @ref MS32_EXTI_LINE_5
  *         @arg @ref MS32_EXTI_LINE_6
  *         @arg @ref MS32_EXTI_LINE_7
  *         @arg @ref MS32_EXTI_LINE_8
  *         @arg @ref MS32_EXTI_LINE_9
  *         @arg @ref MS32_EXTI_LINE_10
  *         @arg @ref MS32_EXTI_LINE_11
  *         @arg @ref MS32_EXTI_LINE_12
  *         @arg @ref MS32_EXTI_LINE_13
  *         @arg @ref MS32_EXTI_LINE_14
  *         @arg @ref MS32_EXTI_LINE_15
  * @param  ExtiPort  This parameter can be one of the following values: 
  *         @arg @ref MS32_EXTI_PORTA
  *         @arg @ref MS32_EXTI_PORTB
  *         @arg @ref MS32_EXTI_PORTC
  *         @arg @ref MS32_EXTI_PORTF
  * @param  Priority  the interrupt priority 
  *         This parameter can be a value of 0x0~0x3
  * @param  State  EXTI enable/disable state
  *         This parameter can be one of the following values:
  *         @arg @ref ENABLE
  *         @arg @ref DISABLE
  * @retval None
  */
void MS32_EXTI_PinITConfig(uint32_t ExtiLine, uint32_t ExtiPort, uint32_t Priority, FunctionalState State) {
  uint8_t   temp, index;

  /* Enable SYSCFG clock */
  MS32_APB1_GRP2_EnableClock(MS32_APB1_GRP2_PERIPH_SYSCFG);

  /* Config EXTI port-pin */
  for (temp = 0; temp < 16; temp++) {
    if (ExtiLine & ((uint32_t)1 << temp)) {
      index = (temp & 0x3) << 2;
      MODIFY_REG(SYSCFG->EXTICR[temp >> 2],  (SYSCFG_EXTICR1_EXTI0 << index), (ExtiPort << index));
    }
  }

  /* Clear flags */
  MS32_EXTI_ClearFlag_0_31(MS32_EXTI_LINE_ALL_0_31);
    
  /*----------------------------- NVIC configuration -------------------------*/
  /*  */
  if (ExtiLine & (MS32_EXTI_LINE_0 | MS32_EXTI_LINE_1)) {
    if (State == ENABLE) {
      NVIC_EnableIRQ(EXTI0_1_IRQn);
      NVIC_SetPriority(EXTI0_1_IRQn, Priority);
    } else {
      NVIC_DisableIRQ(EXTI0_1_IRQn);
    }
  }

  if (ExtiLine & (MS32_EXTI_LINE_2 | MS32_EXTI_LINE_3)) {
    if (State == ENABLE) {
      NVIC_EnableIRQ(EXTI2_3_IRQn);
      NVIC_SetPriority(EXTI2_3_IRQn, Priority);
    } else {
      NVIC_DisableIRQ(EXTI2_3_IRQn);
    }
  }

  if (ExtiLine & (MS32_EXTI_LINE_4  | MS32_EXTI_LINE_5  | MS32_EXTI_LINE_6  | MS32_EXTI_LINE_7  |\
                  MS32_EXTI_LINE_8  | MS32_EXTI_LINE_9  | MS32_EXTI_LINE_10 | MS32_EXTI_LINE_11 |\
                  MS32_EXTI_LINE_12 | MS32_EXTI_LINE_13 | MS32_EXTI_LINE_14 | MS32_EXTI_LINE_15)) {
    if (State == ENABLE) {
      NVIC_EnableIRQ(EXTI4_15_IRQn);
      NVIC_SetPriority(EXTI4_15_IRQn, Priority);
    } else {
      NVIC_DisableIRQ(EXTI4_15_IRQn);
    }
  }
}

/**
  * @brief  Generate a software interrupt for a dedicated line.
  * @param  ExtiLine This parameter can be a combination of the following values:
  *         @arg @ref MS32_EXTI_LINE_0
  *         @arg @ref MS32_EXTI_LINE_1
  *         @arg @ref MS32_EXTI_LINE_2
  *         @arg @ref MS32_EXTI_LINE_3
  *         @arg @ref MS32_EXTI_LINE_4
  *         @arg @ref MS32_EXTI_LINE_5
  *         @arg @ref MS32_EXTI_LINE_6
  *         @arg @ref MS32_EXTI_LINE_7
  *         @arg @ref MS32_EXTI_LINE_8
  *         @arg @ref MS32_EXTI_LINE_9
  *         @arg @ref MS32_EXTI_LINE_10
  *         @arg @ref MS32_EXTI_LINE_11
  *         @arg @ref MS32_EXTI_LINE_12
  *         @arg @ref MS32_EXTI_LINE_13
  *         @arg @ref MS32_EXTI_LINE_14
  *         @arg @ref MS32_EXTI_LINE_15
  *         @arg @ref MS32_EXTI_LINE_16
  *         @arg @ref MS32_EXTI_LINE_17
  *         @arg @ref MS32_EXTI_LINE_19
  *         @arg @ref MS32_EXTI_LINE_20
  *         @arg @ref MS32_EXTI_LINE_21
  *         @arg @ref MS32_EXTI_LINE_22
  * @note   Please check each device line mapping for EXTI Line availability
  * @retval None.
  */
void MS32_EXTI_GenerateSWI(uint32_t ExtiLine) {
  MS32_EXTI_GenerateSWI_0_31(ExtiLine);
}

/**
  * @brief  Get the EXTI interrupt flags according to the internal 
  *         EXTI SR registers.
  * @param  ExtiLine This parameter can be a combination of the following values:
  *         @arg @ref MS32_EXTI_LINE_0
  *         @arg @ref MS32_EXTI_LINE_1
  *         @arg @ref MS32_EXTI_LINE_2
  *         @arg @ref MS32_EXTI_LINE_3
  *         @arg @ref MS32_EXTI_LINE_4
  *         @arg @ref MS32_EXTI_LINE_5
  *         @arg @ref MS32_EXTI_LINE_6
  *         @arg @ref MS32_EXTI_LINE_7
  *         @arg @ref MS32_EXTI_LINE_8
  *         @arg @ref MS32_EXTI_LINE_9
  *         @arg @ref MS32_EXTI_LINE_10
  *         @arg @ref MS32_EXTI_LINE_11
  *         @arg @ref MS32_EXTI_LINE_12
  *         @arg @ref MS32_EXTI_LINE_13
  *         @arg @ref MS32_EXTI_LINE_14
  *         @arg @ref MS32_EXTI_LINE_15
  *         @arg @ref MS32_EXTI_LINE_16
  *         @arg @ref MS32_EXTI_LINE_17
  *         @arg @ref MS32_EXTI_LINE_19
  *         @arg @ref MS32_EXTI_LINE_20
  *         @arg @ref MS32_EXTI_LINE_21
  *         @arg @ref MS32_EXTI_LINE_22
  * @note   Please check each device line mapping for EXTI Line availability 
  * @note   Clear flags After getting the interrupt or error flags equal to set. 
  * @retval A FlagStatus enumeration value:
  *          - SET:   flag set(equal to "1")
  *          - RESET: flag no set(equal to "0")
  */
FlagStatus MS32_EXTI_GetStatusFlag(uint32_t ExtiLine) {
  FlagStatus flags;

  if (MS32_EXTI_ReadFlag_0_31(ExtiLine)) {
    flags = SET;
    MS32_EXTI_ClearFlag_0_31(ExtiLine);
  } else {
    flags = RESET;
  }

  return flags;
}


/******************************** END OF FILE *********************************/
