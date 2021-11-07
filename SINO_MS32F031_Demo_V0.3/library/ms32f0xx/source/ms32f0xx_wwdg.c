/* Includes ------------------------------------------------------------------*/
#include "ms32f0xx_bus.h"
#include "ms32f0xx_wwdg.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define WWDG_CNT_MAX    0x7F


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @addtogroup WWDG_EF_Init
  * @{
  */

/**
  * @brief  De-initialize the WWDG registers to their default reset values.
  * @param  None
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: WWDG registers are de-initialized
  *          - ERROR: not applicable
  */
ErrorStatus MS32_WWDG_DeInit(void) {
  /* Force and Release reset on clock of WWDG */
  MS32_APB1_GRP1_EnableClock(MS32_APB1_GRP1_PERIPH_WWDG);
  MS32_APB1_GRP1_ForceReset(MS32_APB1_GRP1_PERIPH_WWDG);
  MS32_APB1_GRP1_ReleaseReset(MS32_APB1_GRP1_PERIPH_WWDG);

  return SUCCESS;
}

/**
  * @brief Set each @ref MS32_WWDG_InitTypeDef field to default value.
  * @param WwdgInitStr  pointer to a @ref MS32_WWDG_InitTypeDef structure
  *                          whose fields will be set to default values.
  * @retval None
  */
void MS32_WWDG_StructInit(MS32_WWDG_InitTypeDef *WwdgInitStr) {
  /* Reset WWDG init structure parameters values */
  WwdgInitStr->Prescaler = MS32_WWDG_PRESCALER_1;
  WwdgInitStr->Window    = WWDG_CNT_MAX;
  WwdgInitStr->Counter   = WWDG_CNT_MAX;
}

/**
  * @brief  Initialize the WWDG according to the specified.
  *         parameters in the MS32_WWDG_InitTypeDef of associated handle.
  * @param  WwdgInitStr  pointer to a MS32_WWDG_InitTypeDef structure that contains
  *                the configuration information for the specified WWDG module.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: WWDG registers are initialized
  *          - ERROR: not applicable
  */
ErrorStatus MS32_WWDG_Init(MS32_WWDG_InitTypeDef *WwdgInitStr) {
  /* Enable WWDG clock */
  MS32_APB1_GRP1_EnableClock(MS32_APB1_GRP1_PERIPH_WWDG);

  /* WWDG config */
  MODIFY_REG(WWDG->CFR, (WWDG_CFR_WDGTB | WWDG_CFR_W), (WwdgInitStr->Prescaler | WwdgInitStr->Window));
  MODIFY_REG(WWDG->CR, (WWDG_CR_WDGA | WWDG_CR_T), (WWDG_CR_WDGA | WwdgInitStr->Counter));

  return SUCCESS;
}

/**
  * @brief  Initializes the WWDG interrupt according to the specified parameters.
  * @param  InterruptFunc  contains the configuration information for the WWDG interrupt.
  *         This parameter can be one or more of the following values:
  *         @arg @ref MS32_WWDG_EWI_DISABLE  the WWDG Early Wakeup Interupt interrupt disable
  *         @arg @ref MS32_WWDG_EWI_ENABLE   the WWDG Early Wakeup Interupt interrupt enable
  * @param  Priority  the interrupt priority 
  *         This parameter can be a value of 0x0~0x3
  * @retval None
  */
void MS32_WWDG_ITConfig(uint32_t InterruptFunc, uint32_t Priority) {
  /* Enable WWDG clock */
  MS32_APB1_GRP1_EnableClock(MS32_APB1_GRP1_PERIPH_WWDG);

  /* Enable/disable WWDG interrupt and clear flag */
  MS32_WWDG_ClearFlag_EWKUP(WWDG);
  MODIFY_REG(WWDG->CFR, WWDG_CFR_EWI, InterruptFunc);
    
  /*----------------------------- NVIC configuration -------------------------*/
  if (MS32_WWDG_IsEnabledIT_EWKUP(WWDG)) {
    NVIC_EnableIRQ(WWDG_IRQn);
    NVIC_SetPriority(WWDG_IRQn, Priority);
  } else {
    NVIC_DisableIRQ(WWDG_IRQn);
  }
}

/**
  * @brief  Refresh the WWDG.
  * @param  Counter  the refresh value between 0x40 and 0x7F.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: WWDG registers are refreshed
  *          - ERROR: not applicable
  */
ErrorStatus MS32_WWDG_Refresh(uint8_t Counter) {
  ErrorStatus status;

  /* Write to WWDG CR the WWDG Counter value to refresh with */
  if (Counter <= WWDG_CNT_MAX) {
    MS32_WWDG_SetCounter(WWDG, Counter);
    status = SUCCESS;
  } else {
    status = ERROR;
  }

  return status;
}

/**
  * @brief  Get the WWDG interrupt and error flags according to the internal 
  *         WWDG SR registers.
  * @param  None
  * @note   Clear flags After getting the interrupt flags equal to set. 
  * @retval A FlagStatus enumeration value:
  *          - SET:   flag set(equal to "1")
  *          - RESET: flag no set(equal to "0")
  */
FlagStatus MS32_WWDG_GetStatusFlag(void) {
  FlagStatus flags;

  if (MS32_WWDG_IsActiveFlag_EWKUP(WWDG)) {
    flags = SET;
    MS32_WWDG_ClearFlag_EWKUP(WWDG);
  } else {
    flags = RESET;
  }

  return flags;
}


/******************************** END OF FILE *********************************/
