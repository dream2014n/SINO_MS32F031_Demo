/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MS32F0XX_CORTEX_H
#define __MS32F0XX_CORTEX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ms32f0xx.h"


/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup CORTEX_EC_CLKSOURCE_HCLK SYSTICK Clock Source
  * @{
  */
#define MS32_SYSTICK_CLKSOURCE_HCLK_DIV8     0x00000000U                 /*!< AHB clock divided by 8 selected as SysTick clock source.*/
#define MS32_SYSTICK_CLKSOURCE_HCLK          SysTick_CTRL_CLKSOURCE_Msk  /*!< AHB clock selected as SysTick clock source. */


/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @defgroup CORTEX_EF_SYSTICK SYSTICK
  * @{
  */

/**
  * @brief  Enable SysTick
  * @rmtoll STK_CTRL     ENABLE       MS32_SYSTICK_Enable
  * @retval None
  */
__STATIC_INLINE void MS32_SYSTICK_Enable(void) {
  SET_BIT(SysTick->CTRL, SysTick_CTRL_ENABLE_Msk);
}

/**
  * @brief  Disable SysTick
  * @rmtoll STK_CTRL     ENABLE       MS32_SYSTICK_Disable
  * @retval None
  */
__STATIC_INLINE void MS32_SYSTICK_Disable(void) {
  CLEAR_BIT(SysTick->CTRL, SysTick_CTRL_ENABLE_Msk);
}

/**
  * @brief  Checks if the SYSTICK is enabled or disabled.
  * @rmtoll STK_CTRL     ENABLE       MS32_SYSTICK_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_SYSTICK_IsEnabled(void) {
  return (READ_BIT(SysTick->CTRL, SysTick_CTRL_ENABLE_Msk) == (SysTick_CTRL_ENABLE_Msk));
}

/**
  * @brief  This function checks if the Systick counter flag is active or not.
  * @note   It can be used in timeout function on application side.
  * @rmtoll STK_CTRL     COUNTFLAG     MS32_SYSTICK_IsActiveCounterFlag
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_SYSTICK_IsActiveCounterFlag(void) {
  return ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == (SysTick_CTRL_COUNTFLAG_Msk));
}

/**
  * @brief  Configures the SysTick clock source
  * @rmtoll STK_CTRL     CLKSOURCE     MS32_SYSTICK_SetClkSource
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref MS32_SYSTICK_CLKSOURCE_HCLK_DIV8
  *         @arg @ref MS32_SYSTICK_CLKSOURCE_HCLK
  * @retval None
  */
__STATIC_INLINE void MS32_SYSTICK_SetClkSource(uint32_t Source) {
  if (Source == MS32_SYSTICK_CLKSOURCE_HCLK) {
    SET_BIT(SysTick->CTRL, MS32_SYSTICK_CLKSOURCE_HCLK);
  } else {
    CLEAR_BIT(SysTick->CTRL, MS32_SYSTICK_CLKSOURCE_HCLK);
  }
}

/**
  * @brief  Get the SysTick clock source
  * @rmtoll STK_CTRL     CLKSOURCE     MS32_SYSTICK_GetClkSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_SYSTICK_CLKSOURCE_HCLK_DIV8
  *         @arg @ref MS32_SYSTICK_CLKSOURCE_HCLK
  */
__STATIC_INLINE uint32_t MS32_SYSTICK_GetClkSource(void) {
  return READ_BIT(SysTick->CTRL, MS32_SYSTICK_CLKSOURCE_HCLK);
}

/**
  * @brief  Set the SysTick reload-value
  * @rmtoll STK_LOAD     LOAD     MS32_SYSTICK_SetReLoadVal
  * @param  AutoReload between Min_Data=0 and Max_Data=0xFFFFFFUL
  * @retval None
  */
__STATIC_INLINE void MS32_SYSTICK_SetReloadVal(uint32_t AutoReload) {
  if (AutoReload <= SysTick_LOAD_RELOAD_Msk) {
    WRITE_REG(SysTick->LOAD, AutoReload);
  }
}

/**
  * @brief  Get the SysTick reload-value
  * @rmtoll STK_LOAD     LOAD     MS32_SYSTICK_GetReLoadVal
  * @retval Auto-reload value
  */
__STATIC_INLINE uint32_t MS32_SYSTICK_GetReLoadVal(void) {
  return READ_REG(SysTick->LOAD);
}

/**
  * @brief  Set the SysTick value
  * @rmtoll STK_VAL     VAL     MS32_SYSTICK_SetVal
  * @param  Value between Min_Data=0 and Max_Data=0xFFFFFFUL
  * @retval None
  */
__STATIC_INLINE void MS32_SYSTICK_SetVal(uint32_t Value) {
  if (Value <= SysTick_VAL_CURRENT_Msk) {
    WRITE_REG(SysTick->VAL, Value);
  }
}

/**
  * @brief  Get the SysTick value
  * @rmtoll STK_VAL     VAL     MS32_SYSTICK_GetVal
  * @retval Value
  */
__STATIC_INLINE uint32_t MS32_SYSTICK_GetVal(void) {
  return READ_REG(SysTick->VAL);
}

/**
  * @brief  Enable SysTick exception request
  * @rmtoll STK_CTRL     TICKINT       MS32_SYSTICK_EnableIT
  * @retval None
  */
__STATIC_INLINE void MS32_SYSTICK_EnableIT(void) {
  SET_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk);
}

/**
  * @brief  Disable SysTick exception request
  * @rmtoll STK_CTRL     TICKINT       MS32_SYSTICK_DisableIT
  * @retval None
  */
__STATIC_INLINE void MS32_SYSTICK_DisableIT(void) {
  CLEAR_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk);
}

/**
  * @brief  Checks if the SYSTICK interrupt is enabled or disabled.
  * @rmtoll STK_CTRL     TICKINT       MS32_SYSTICK_IsEnabledIT
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_SYSTICK_IsEnabledIT(void) {
  return (READ_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk) == (SysTick_CTRL_TICKINT_Msk));
}


/** @defgroup CORTEX_EF_LOW_POWER_MODE LOW POWER MODE
  * @{
  */

/**
  * @brief  Processor uses sleep as its low power mode
  * @rmtoll SCB_SCR      SLEEPDEEP     MS32_LPM_EnableSleep
  * @retval None
  */
__STATIC_INLINE void MS32_LPM_EnableSleep(void) {
  /* Clear SLEEPDEEP bit of Cortex System Control Register */
  CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));
}

/**
  * @brief  Processor uses deep sleep as its low power mode
  * @rmtoll SCB_SCR      SLEEPDEEP     MS32_LPM_EnableDeepSleep
  * @retval None
  */
__STATIC_INLINE void MS32_LPM_EnableDeepSleep(void) {
  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));
}

/**
  * @brief  Configures sleep-on-exit when returning from Handler mode to Thread mode.
  * @note   Setting this bit to 1 enables an interrupt-driven application to avoid returning to an
  *         empty main application.
  * @rmtoll SCB_SCR      SLEEPONEXIT   MS32_LPM_EnableSleepOnExit
  * @retval None
  */
__STATIC_INLINE void MS32_LPM_EnableSleepOnExit(void) {
  /* Set SLEEPONEXIT bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPONEXIT_Msk));
}

/**
  * @brief  Do not sleep when returning to Thread mode.
  * @rmtoll SCB_SCR      SLEEPONEXIT   MS32_LPM_DisableSleepOnExit
  * @retval None
  */
__STATIC_INLINE void MS32_LPM_DisableSleepOnExit(void) {
  /* Clear SLEEPONEXIT bit of Cortex System Control Register */
  CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPONEXIT_Msk));
}

/**
  * @brief  Enabled events and all interrupts, including disabled interrupts, can wakeup the
  *         processor.
  * @rmtoll SCB_SCR      SEVEONPEND    MS32_LPM_EnableEventOnPend
  * @retval None
  */
__STATIC_INLINE void MS32_LPM_EnableEventOnPend(void) {
  /* Set SEVEONPEND bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SEVONPEND_Msk));
}

/**
  * @brief  Only enabled interrupts or events can wakeup the processor, disabled interrupts are
  *         excluded
  * @rmtoll SCB_SCR      SEVEONPEND    MS32_LPM_DisableEventOnPend
  * @retval None
  */
__STATIC_INLINE void MS32_LPM_DisableEventOnPend(void) {
  /* Clear SEVEONPEND bit of Cortex System Control Register */
  CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SEVONPEND_Msk));
}


/** @defgroup CORTEX_EF_MCU_INFO MCU INFO
  * @{
  */

/**
  * @brief  Get Implementer code
  * @rmtoll SCB_CPUID    IMPLEMENTER   MS32_CPUID_GetImplementer
  * @retval Value should be equal to 0x41 for ARM
  */
__STATIC_INLINE uint32_t MS32_CPUID_GetImplementer(void) {
  return (uint32_t)(READ_BIT(SCB->CPUID, SCB_CPUID_IMPLEMENTER_Msk) >> SCB_CPUID_IMPLEMENTER_Pos);
}

/**
  * @brief  Get Variant number (The r value in the rnpn product revision identifier)
  * @rmtoll SCB_CPUID    VARIANT       MS32_CPUID_GetVariant
  * @retval Value between 0 and 255 (0x0: revision 0)
  */
__STATIC_INLINE uint32_t MS32_CPUID_GetVariant(void) {
  return (uint32_t)(READ_BIT(SCB->CPUID, SCB_CPUID_VARIANT_Msk) >> SCB_CPUID_VARIANT_Pos);
}

/**
  * @brief  Get Architecture number
  * @rmtoll SCB_CPUID    ARCHITECTURE  MS32_CPUID_GetArchitecture
  * @retval Value should be equal to 0xC for Cortex-M0 devices
  */
__STATIC_INLINE uint32_t MS32_CPUID_GetArchitecture(void) {
  return (uint32_t)(READ_BIT(SCB->CPUID, SCB_CPUID_ARCHITECTURE_Msk) >> SCB_CPUID_ARCHITECTURE_Pos);
}

/**
  * @brief  Get Part number
  * @rmtoll SCB_CPUID    PARTNO        MS32_CPUID_GetParNo
  * @retval Value should be equal to 0xC20 for Cortex-M0
  */
__STATIC_INLINE uint32_t MS32_CPUID_GetParNo(void) {
  return (uint32_t)(READ_BIT(SCB->CPUID, SCB_CPUID_PARTNO_Msk) >> SCB_CPUID_PARTNO_Pos);
}

/**
  * @brief  Get Revision number (The p value in the rnpn product revision identifier, indicates patch release)
  * @rmtoll SCB_CPUID    REVISION      MS32_CPUID_GetRevision
  * @retval Value between 0 and 255 (0x1: patch 1)
  */
__STATIC_INLINE uint32_t MS32_CPUID_GetRevision(void) {
  return (uint32_t)(READ_BIT(SCB->CPUID, SCB_CPUID_REVISION_Msk) >> SCB_CPUID_REVISION_Pos);
}


#ifdef __cplusplus
}
#endif

#endif /* __MS32F0XX_CORTEX_H */

/******************************** END OF FILE *********************************/
