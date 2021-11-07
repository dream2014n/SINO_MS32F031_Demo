/* Includes ------------------------------------------------------------------*/
#include "ms32f0xx_bus.h"
#include "ms32f0xx_cortex.h"
#include "ms32f0xx_pwr.h"


/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @defgroup FUNC_FLAG Defines
  * @{
  */
#define CLEAR_FLAG_OFFSET     (PWR_CR_CWUF_Pos - PWR_CSR_WUF_Pos)


/* Private macros ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @addtogroup PWR_EF_Init
  * @{
  */

/**
  * @brief  De-initialize the PWR registers to their default reset values.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: PWR registers are de-initialized
  *          - ERROR: not applicable
  */
ErrorStatus MS32_PWR_DeInit(void) {
  /* Force and Release reset on clock of PWR */
  MS32_APB1_GRP1_EnableClock(MS32_APB1_GRP1_PERIPH_PWR);
  MS32_APB1_GRP1_ForceReset(MS32_APB1_GRP1_PERIPH_PWR);
  MS32_APB1_GRP1_ReleaseReset(MS32_APB1_GRP1_PERIPH_PWR);

  return SUCCESS;
}

/**
  * @brief Set each @ref MS32_PWR_InitTypeDef field to default value.
  * @param PwrInitStr  pointer to a @ref MS32_PWR_InitTypeDef structure
  *                          whose fields will be set to default values.
  * @retval None
  */
void MS32_PWR_StructInit(MS32_PWR_InitTypeDef *PwrInitStr) {
  /* Reset PWR init structure parameters values */
  PwrInitStr->BackupAccessStatus  = MS32_PWR_BKUPACC_DIS;
  PwrInitStr->WakeupPin           = MS32_PWR_WAKEUP_NONE;
  PwrInitStr->PowerVoltDetectSel  = MS32_PWR_PVDOFF;
  PwrInitStr->PowerVoltDetectLock = MS32_SYSCFG_PVD_UNLOCK;
}

/**
  * @brief  Initialize the PWR according to the specified.
  *         parameters in the MS32_PWR_InitTypeDef of associated handle.
  * @param  PwrInitStr  pointer to a MS32_PWR_InitTypeDef structure that contains
  *                the configuration information for the specified PWR module.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: PWR registers are initialized
  *          - ERROR: not applicable
  */
ErrorStatus MS32_PWR_Init(MS32_PWR_InitTypeDef *PwrInitStr) {
  __IO uint8_t syscfg_clk_en_bk;

  /* Enable PWR clock */
  MS32_APB1_GRP1_EnableClock(MS32_APB1_GRP1_PERIPH_PWR);
  /* PWR config */
  MODIFY_REG(PWR->CR, (PWR_CR_DBP | PWR_CR_PLS | PWR_CR_PVDE), (PwrInitStr->BackupAccessStatus | PwrInitStr->PowerVoltDetectSel));
  MODIFY_REG(PWR->CSR, (PWR_CSR_EWUP1 | PWR_CSR_EWUP2), PwrInitStr->WakeupPin);

  /* SYSCFG config */
  if (READ_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_PVD_LOCK) != PwrInitStr->PowerVoltDetectLock) {
    /* Backup SYSCFG clock and enalbe SYSCFG clock */
    syscfg_clk_en_bk = MS32_APB1_GRP2_IsEnabledClock(MS32_APB1_GRP2_PERIPH_SYSCFG);
    MS32_APB1_GRP2_EnableClock(MS32_APB1_GRP2_PERIPH_SYSCFG);
    /* Set PVD lock */
    MODIFY_REG(SYSCFG->CFGR2, SYSCFG_CFGR2_PVD_LOCK, PwrInitStr->PowerVoltDetectLock);
    /* Recover SYSCFG clock */
    if (!syscfg_clk_en_bk) {
      MS32_APB1_GRP2_DisableClock(MS32_APB1_GRP2_PERIPH_SYSCFG);
    }
  }

  return SUCCESS;
}

/**
  * @brief  Initializes the PWR interrupt according to the specified parameters.
  * @param  InterruptFunc  contains the configuration information for the PWR interrupt.
  *         This parameter can be one or more of the following values:
  *         @arg @ref MS32_PWR_PVDIT_DISABLE  PVD interrupt disable
  *         @arg @ref MS32_PWR_PVDIT_ENABLE   PVD interrupt enable
  * @param  Priority  the interrupt priority 
  *         This parameter can be a value of 0x0~0x3
  * @retval None
  */
void MS32_PWR_ITConfig(uint32_t InterruptFunc, uint32_t Priority) {
  /*----------------------------- NVIC configuration -------------------------*/
  if (InterruptFunc == MS32_PWR_PVDIT_ENABLE) {
    NVIC_EnableIRQ(PVD_IRQn);
    NVIC_SetPriority(PVD_IRQn, Priority);
  } else {
    NVIC_DisableIRQ(PVD_IRQn);
  }
}

/**
  * @brief  Get the PWR flags according to the internal PWR SR registers.
  * @param  Flags specifies the function flags.
  *          This parameter can be one or more of the following values:
  *            @arg @ref MS32_PWR_CSR_WUF   the PWR programme error flag
  *            @arg @ref MS32_PWR_CSR_SBF   the PWR write error flag
  *            @arg @ref MS32_PWR_CSR_PVDO  the PWR end of operartion flag
  * @note   Clear flags After getting the interrupt flags equal to set. 
  * @retval A FlagStatus enumeration value:
  *          - SET:   flag set(equal to "1")
  *          - RESET: flag no set(equal to "0")
  */
FlagStatus MS32_PWR_GetStatusFlag(uint32_t Flags) {
  FlagStatus flags;

  if (READ_BIT(PWR->CSR, Flags)) {
    flags = SET;
    SET_BIT(PWR->CR, CLEAR_BIT(Flags, PWR_CSR_PVDO) << CLEAR_FLAG_OFFSET);
  } else {
    flags = RESET;
  }

  return flags;
}

/**
  * @brief Enters Sleep mode.
  * @note  In Sleep mode, all I/O pins keep the same state as in Run mode.
  * @param SLEEPEntry Specifies if SLEEP mode is entered with WFI or WFE instruction.
  *           When WFI entry is used, tick interrupt have to be disabled if not desired as 
  *           the interrupt wake up source.
  *           This parameter can be one of the following values:
  *            @arg PWR_SLEEPENTRY_WFI: enter SLEEP mode with WFI instruction
  *            @arg PWR_SLEEPENTRY_WFE: enter SLEEP mode with WFE instruction
  * @retval None
  */
void MS32_PWR_EnterSLEEPMode(uint32_t SLEEPEntry) {
  /* Enable PWR clock */
  MS32_APB1_GRP1_EnableClock(MS32_APB1_GRP1_PERIPH_PWR);

  /* Clear SLEEPDEEP bit of Cortex System Control Register */
  MS32_LPM_EnableSleep();

  /* Select SLEEP mode entry -------------------------------------------------*/
  if(SLEEPEntry == PWR_SLEEPENTRY_WFI) {
    /* Request Wait For Interrupt */
    __WFI();
  } else {
    /* Request Wait For Event */
    __SEV();
    __WFE();
    __WFE();
  }
}

/**
  * @brief Enters STOP mode.
  * @note  In Stop mode, all I/O pins keep the same state as in Run mode.
  * @note  When exiting Stop mode by issuing an interrupt or a wakeup event,
  *         the HSI RC oscillator is selected as system clock.
  * @note  When the voltage regulator operates in low power mode, an additional
  *         startup delay is incurred when waking up from Stop mode.
  *         By keeping the internal regulator ON during Stop mode, the consumption
  *         is higher although the startup time is reduced.
  * @param Regulator Specifies the regulator state in STOP mode.
  *          This parameter can be one of the following values:
  *            @arg PWR_MAINREGULATOR_ON: STOP mode with regulator ON
  *            @arg PWR_LOWPOWERREGULATOR_ON: STOP mode with low power regulator ON
  * @param STOPEntry specifies if STOP mode in entered with WFI or WFE instruction.
  *          This parameter can be one of the following values:
  *            @arg PWR_STOPENTRY_WFI:Enter STOP mode with WFI instruction
  *            @arg PWR_STOPENTRY_WFE: Enter STOP mode with WFE instruction
  * @retval None
  */
void MS32_PWR_EnterSTOPMode(uint32_t Regulator, uint8_t STOPEntry) {
  /* Enable PWR clock */
  MS32_APB1_GRP1_EnableClock(MS32_APB1_GRP1_PERIPH_PWR);

  /* Select the regulator state in STOP mode ---------------------------------*/
  MS32_PWR_SetPowerMode(Regulator);
  /* Set SLEEPDEEP bit of Cortex System Control Register */
  MS32_LPM_EnableDeepSleep();

  /* Select STOP mode entry --------------------------------------------------*/
  if (STOPEntry == PWR_STOPENTRY_WFI) {
    /* Request Wait For Interrupt */
    __WFI();
  } else {
    /* Request Wait For Event */
    __SEV();
    __WFE();
    __WFE();
  }

  /* Reset SLEEPDEEP bit of Cortex System Control Register */
  MS32_LPM_EnableSleep();
}

/**
  * @brief Enters STANDBY mode.
  * @note  In Standby mode, all I/O pins are high impedance except for:
  *          - Reset pad (still available)
  *          - RTC alternate function pins if configured for tamper, time-stamp, RTC
  *            Alarm out, or RTC clock calibration out.
  *          - WKUP pins if enabled.
  *            MS32F0 devices, the Stop mode is available, but it is 
  *            aningless to distinguish between voltage regulator in Low power 
  *            mode and voltage regulator in Run mode because the regulator 
  *            not used and the core is supplied directly from an external source.
  *            Consequently, the Standby mode is not available on those devices.
  * @retval None
  */
void MS32_PWR_EnterSTANDBYMode(void) {
  /* Enable PWR clock */
  MS32_APB1_GRP1_EnableClock(MS32_APB1_GRP1_PERIPH_PWR);

  /* Select STANDBY mode */
  SET_BIT(PWR->CR, PWR_CR_PDDS);
  /* Set SLEEPDEEP bit of Cortex System Control Register */
  MS32_LPM_EnableDeepSleep();

  /* Request Wait For Interrupt */
  __WFI();
}


/******************************** END OF FILE *********************************/
