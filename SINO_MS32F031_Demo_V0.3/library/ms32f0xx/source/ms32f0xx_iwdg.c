/* Includes ------------------------------------------------------------------*/
#include "ms32f0xx_iwdg.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define IWDG_CNT_MAX          (0xFFF)


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @addtogroup IWDG_EF_Init
  * @{
  */

/**
  * @brief Set each @ref MS32_IWDG_InitTypeDef field to default value.
  * @param IwdgInitStr  pointer to a @ref MS32_IWDG_InitTypeDef structure
  *                          whose fields will be set to default values.
  * @retval None
  */
void MS32_IWDG_StructInit(MS32_IWDG_InitTypeDef *IwdgInitStr) {
  /* Reset IWDG init structure parameters values */
  IwdgInitStr->Prescaler = MS32_IWDG_PRESCALER_4;
  IwdgInitStr->Reload    = IWDG_CNT_MAX;
  IwdgInitStr->Window    = IWDG_CNT_MAX;
}

/**
  * @brief  Initialize the IWDG according to the specified.
  *         parameters in the MS32_IWDG_InitTypeDef of associated handle.
  * @param  IwdgInitStr  pointer to a MS32_IWDG_InitTypeDef structure that contains
  *                the configuration information for the specified IWDG module.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: IWDG registers are initialized
  *          - ERROR: not applicable
  */
ErrorStatus MS32_IWDG_Init(MS32_IWDG_InitTypeDef *IwdgInitStr) {
  /* Enable LSI clock */
  if (!MS32_RCC_LSI_IsReady()) {
    MS32_RCC_LSI_Enable();
    while (!MS32_RCC_LSI_IsReady());
  }

  /* IWDG unlock */
  MS32_IWDG_EnableWriteAccess(IWDG);
  /* IWDG config */
  MS32_IWDG_SetPrescaler(IWDG, IwdgInitStr->Prescaler);
  MS32_IWDG_SetReloadCounter(IWDG, IwdgInitStr->Reload);
  while (!MS32_IWDG_IsReady(IWDG));
  MS32_IWDG_SetWindow(IWDG, IwdgInitStr->Window);
  /* IWDG run */
  MS32_IWDG_Enable(IWDG);

  return SUCCESS;
}

/**
  * @brief  Refresh the IWDG.
  * @param  None
  * @retval None
  */
void MS32_IWDG_Refresh(void) {
  /* Reload IWDG counter with value defined in the reload register */
  MS32_IWDG_ReloadCounter(IWDG);
}

/**
  * @brief  Get the IWDG interrupt and error flags according to the internal 
  *         WWDG SR registers.
  * @param  Flags specifies the function flags.
  *          This parameter can be one of the following values:
  *            @arg @ref MS32_IWDG_FLAG_PVU  the IWDG counter prescaler value update
  *            @arg @ref MS32_IWDG_FLAG_RVU  the IWDG counter reload value update
  *            @arg @ref MS32_IWDG_FLAG_WVU  the IWDG counter window value update
  * @retval A FlagStatus enumeration value:
  *          - SET:   flag set(equal to "1")
  *          - RESET: flag no set(equal to "0")
  */
FlagStatus MS32_IWDG_GetStatusFlag(uint32_t Flags) {
  FlagStatus flags;

  if (READ_BIT(IWDG->SR, Flags)) {
    flags = SET;
  } else {
    flags = RESET;
  }

  return flags;
}


/******************************** END OF FILE *********************************/
