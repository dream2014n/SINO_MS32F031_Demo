/* Includes ------------------------------------------------------------------*/
#include "ms32f0xx_adc.h"
#include "ms32f0xx_bus.h"


/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @addtogroup ADC_MS32_Private_Constants
  * @{
  */

/* Definitions of ADC hardware constraints delays */
/* Note: Only ADC IP HW delays are defined in ADC MS32 driver driver,         */
/*       not timeout values:                                                  */
/*       Timeout values for ADC operations are dependent to device clock      */
/*       configuration (system clock versus ADC clock),                       */
/*       and therefore must be defined in user application.                   */
/*       Refer to @ref ADC_EC_HW_DELAYS for description of ADC timeout        */
/*       values definition.                                                   */
/* Note: ADC timeout values are defined here in CPU cycles to be independent  */
/*       of device clock setting.                                             */
/*       In user application, ADC timeout values should be defined with       */
/*       temporal values, in function of device clock settings.               */
/*       Highest ratio CPU clock frequency vs ADC clock frequency:            */
/*        - ADC clock from synchronous clock with AHB prescaler 512,          */
/*          APB prescaler 16, ADC prescaler 4.                                */
/*        - ADC clock from asynchronous clock (HSI) with prescaler 1,         */
/*          with highest ratio CPU clock frequency vs HSI clock frequency:    */
/*          HSI frequency 16MHz: ratio 4.                                     */
/* Unit: CPU cycles.                                                          */
#define ADC_CLOCK_RATIO_VS_CPU_HIGHEST          ((uint32_t) 512U * 16U * 4U)
#define ADC_TIMEOUT_DISABLE_CPU_CYCLES          (ADC_CLOCK_RATIO_VS_CPU_HIGHEST * 1U)
#define ADC_TIMEOUT_STOP_CONVERSION_CPU_CYCLES  (ADC_CLOCK_RATIO_VS_CPU_HIGHEST * 1U)


/* Private macros ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @addtogroup ADC_EF_Init
  * @{
  */

/**
  * @brief  De-initialize registers of all ADC instances belonging to
  *         the same ADC common instance to their default reset values.
  * @note   This function is performing a hard reset, using high level
  *         clock source RCC ADC reset.
  * @param  AdcCommon ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __MS32_ADC_COMMON_INSTANCE() )
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: ADC common registers are de-initialized
  *          - ERROR: not applicable
  */
ErrorStatus MS32_ADC_CommonDeInit(ADC_Common_TypeDef *AdcCommon) {
  /* Enable clock */
  MS32_APB1_GRP2_EnableClock(MS32_APB1_GRP2_PERIPH_ADC1);
  /* Force reset of ADC clock (core clock) */
  MS32_APB1_GRP2_ForceReset(MS32_APB1_GRP2_PERIPH_ADC1);
  /* Release reset of ADC clock (core clock) */
  MS32_APB1_GRP2_ReleaseReset(MS32_APB1_GRP2_PERIPH_ADC1);
	/* ADC analog channel disable */
	MS32_ADC_SetCommonPathInternalCh(AdcCommon, MS32_ADC_PATH_INTERNAL_NONE);

  return SUCCESS;
}


/**
  * @brief  De-initialize registers of the selected ADC instance
  *         to their default reset values.
  * @note   To reset all ADC instances quickly (perform a hard reset),
  *         use function @ref MS32_ADC_CommonDeInit().
  * @note   If this functions returns error status, it means that ADC instance
  *         is in an unknown state.
  *         In this case, perform a hard reset using high level
  *         clock source RCC ADC reset.
  *         Refer to function @ref MS32_ADC_CommonDeInit().
  * @param  ADCx ADC instance
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: ADC registers are de-initialized
  *          - ERROR: ADC registers are not de-initialized
  */
ErrorStatus MS32_ADC_DeInit(ADC_TypeDef *ADCx) {
  ErrorStatus status = SUCCESS;

  __IO uint32_t timeout_cpu_cycles = 0U;

  /* Enable clock */
  MS32_APB1_GRP2_EnableClock(MS32_APB1_GRP2_PERIPH_ADC1);

  /* Disable ADC instance if not already disabled.                            */
  if (MS32_ADC_IsEnabled(ADCx) == 1U) {
    /* Set ADC group regular trigger source to SW start to ensure to not      */
    /* have an external trigger event occurring during the conversion stop    */
    /* ADC disable process.                                                   */
    MS32_ADC_REG_SetTriggerSource(ADCx, MS32_ADC_REG_TRIG_SOFTWARE);

    /* Stop potential ADC conversion on going on ADC group regular.           */
    if(MS32_ADC_REG_IsConversionOngoing(ADCx) != 0U) {
      if(MS32_ADC_REG_IsStopConversionOngoing(ADCx) == 0U) {
        MS32_ADC_REG_StopConversion(ADCx);
      }
    }

    /* Wait for ADC conversions are effectively stopped                       */
    timeout_cpu_cycles = ADC_TIMEOUT_STOP_CONVERSION_CPU_CYCLES;
    while (MS32_ADC_REG_IsStopConversionOngoing(ADCx) == 1U) {
      if (timeout_cpu_cycles-- == 0U) {
        /* Time-out error */
        status = ERROR;
      }
    }

    /* Disable the ADC instance */
    MS32_ADC_Disable(ADCx);

    /* Wait for ADC instance is effectively disabled */
    timeout_cpu_cycles = ADC_TIMEOUT_DISABLE_CPU_CYCLES;
    while (MS32_ADC_IsDisableOngoing(ADCx) == 1U) {
      if (timeout_cpu_cycles-- == 0U) {
        /* Time-out error */
        status = ERROR;
      }
    }
  }

  /* Check whether ADC state is compliant with expected state */
  if (READ_BIT(ADCx->CR,
               (  ADC_CR_ADSTP | ADC_CR_ADSTART
                | ADC_CR_ADDIS | ADC_CR_ADEN   )
              )
     == 0U) {
    /* ========== Reset ADC registers ========== */
    /* Reset register IER */
    CLEAR_BIT(ADCx->IER,
              (  MS32_ADC_IT_ADRDY
               | MS32_ADC_IT_EOC
               | MS32_ADC_IT_EOS
               | MS32_ADC_IT_OVR
               | MS32_ADC_IT_EOSMP
               | MS32_ADC_IT_AWD1 )
             );

    /* Reset register ISR */
    SET_BIT(ADCx->ISR,
            (  MS32_ADC_FLAG_ADRDY
             | MS32_ADC_FLAG_EOC
             | MS32_ADC_FLAG_EOS
             | MS32_ADC_FLAG_OVR
             | MS32_ADC_FLAG_EOSMP
             | MS32_ADC_FLAG_AWD1 )
           );

    /* Reset register CR */
    /* Bits ADC_CR_ADCAL, ADC_CR_ADSTP, ADC_CR_ADSTART are in access mode     */
    /* "read-set": no direct reset applicable.                                */
    /* No action on register CR */

    /* Reset register CFGR1 */
    CLEAR_BIT(ADCx->CFGR1,
              (  ADC_CFGR1_AWDCH   | ADC_CFGR1_AWDEN  | ADC_CFGR1_AWDSGL  | ADC_CFGR1_DISCEN
               | ADC_CFGR1_AUTOFF  | ADC_CFGR1_WAIT   | ADC_CFGR1_CONT    | ADC_CFGR1_OVRMOD
               | ADC_CFGR1_EXTEN   | ADC_CFGR1_EXTSEL | ADC_CFGR1_ALIGN   | ADC_CFGR1_RES
               | ADC_CFGR1_SCANDIR | ADC_CFGR1_DMACFG | ADC_CFGR1_DMAEN                     )
             );

    /* Reset register CFGR2 */
    /* Note: Update of ADC clock mode is conditioned to ADC state disabled:   */
    /*       already done above.                                              */
    CLEAR_BIT(ADCx->CFGR2, ADC_CFGR2_CKMODE);

    /* Reset register SMPR */
    CLEAR_BIT(ADCx->SMPR, ADC_SMPR_SMP);

    /* Reset register TR */
    MODIFY_REG(ADCx->TR, ADC_TR_HT | ADC_TR_LT, ADC_TR_HT);

    /* Reset register CHSELR */
    CLEAR_BIT(ADCx->CHSELR,
              (  ADC_CHSELR_CHSEL18 | ADC_CHSELR_CHSEL17 | ADC_CHSELR_CHSEL16
               | ADC_CHSELR_CHSEL15 | ADC_CHSELR_CHSEL14 | ADC_CHSELR_CHSEL13 | ADC_CHSELR_CHSEL12
               | ADC_CHSELR_CHSEL11 | ADC_CHSELR_CHSEL10 | ADC_CHSELR_CHSEL9  | ADC_CHSELR_CHSEL8
               | ADC_CHSELR_CHSEL7  | ADC_CHSELR_CHSEL6  | ADC_CHSELR_CHSEL5  | ADC_CHSELR_CHSEL4
               | ADC_CHSELR_CHSEL3  | ADC_CHSELR_CHSEL2  | ADC_CHSELR_CHSEL1  | ADC_CHSELR_CHSEL0 )
             );

    /* Reset register DR */
    /* bits in access mode read only, no direct reset applicable */
  } else {
    /* ADC instance is in an unknown state */
    /* Need to performing a hard reset of ADC instance, using high level      */
    /* clock source RCC ADC reset.                                            */
    /* Caution: On this MS32 serie, if several ADC instances are available    */
    /*          on the selected device, RCC ADC reset will reset              */
    /*          all ADC instances belonging to the common ADC instance.       */
    status = ERROR;
  }

  return status;
}

/**
  * @brief  Initialize some features of ADC instance.
  * @note   These parameters have an impact on ADC scope: ADC instance.
  *         Refer to corresponding unitary functions into
  *         @ref ADC_MS32_EF_Configuration_ADC_Instance .
  * @note   The setting of these parameters by function @ref MS32_ADC_Init()
  *         is conditioned to ADC state:
  *         ADC instance must be disabled.
  *         This condition is applied to all ADC features, for efficiency
  *         and compatibility over all MS32 families. However, the different
  *         features can be set under different ADC state conditions
  *         (setting possible with ADC enabled without conversion on going,
  *         ADC enabled with conversion on going, ...)
  *         Each feature can be updated afterwards with a unitary function
  *         and potentially with ADC in a different state than disabled,
  *         refer to description of each function for setting
  *         conditioned to ADC state.
  * @note   After using this function, some other features must be configured
  *         using LL unitary functions.
  *         The minimum configuration remaining to be done is:
  *          - Set ADC group regular sequencer:
  *            map channel on rank corresponding to channel number.
  *            Refer to function @ref MS32_ADC_REG_SetSequencerChannels();
  *          - Set ADC channel sampling time
  *            Refer to function MS32_ADC_SetChannelSamplingTime();
  * @param  ADCx ADC instance
  * @param  AdcInitStr Pointer to a @ref MS32_ADC_REG_InitTypeDef structure
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: ADC registers are initialized
  *          - ERROR: ADC registers are not initialized
  */
ErrorStatus MS32_ADC_Init(ADC_TypeDef *ADCx, MS32_ADC_InitTypeDef *AdcInitStr) {
  ErrorStatus status = SUCCESS;

  /* Enable clock */
  MS32_APB1_GRP2_EnableClock(MS32_APB1_GRP2_PERIPH_ADC1);

  /* Note: Hardware constraint (refer to description of this function):       */
  /*       ADC instance must be disabled.                                     */
  if (MS32_ADC_IsEnabled(ADCx) == 0U) {
    /* Configuration of ADC hierarchical scope:                               */
    /*  - ADC instance                                                        */
    /*    - Set ADC data resolution                                           */
    /*    - Set ADC conversion data alignment                                 */
    /*    - Set ADC low power mode                                            */
    MODIFY_REG(ADCx->CFGR1,
                 ADC_CFGR1_RES
               | ADC_CFGR1_ALIGN
               | ADC_CFGR1_WAIT
               | ADC_CFGR1_AUTOFF
              ,
                 AdcInitStr->Resolution
               | AdcInitStr->DataAlignment
               | AdcInitStr->LowPowerMode
              );

    MODIFY_REG(ADCx->CFGR2,
               ADC_CFGR2_CKMODE
              ,
               AdcInitStr->Clock
              );
  } else {
    /* Initialization error: ADC instance is not disabled. */
    status = ERROR;
  }

  return status;
}

/**
  * @brief  Set each @ref MS32_ADC_InitTypeDef field to default value.
  * @param  AdcInitStr Pointer to a @ref MS32_ADC_InitTypeDef structure
  *                        whose fields will be set to default values.
  * @retval None
  */
void MS32_ADC_StructInit(MS32_ADC_InitTypeDef *AdcInitStr) {
  /* Set AdcInitStr fields to default values */
  /* Set fields of ADC instance */
  AdcInitStr->Clock         = MS32_ADC_CLOCK_SYNC_PCLK_DIV2;
  AdcInitStr->Resolution    = MS32_ADC_RESOLUTION_12B;
  AdcInitStr->DataAlignment = MS32_ADC_DATA_ALIGN_RIGHT;
  AdcInitStr->LowPowerMode  = MS32_ADC_LP_MODE_NONE;

}

/**
  * @brief  Initialize some features of ADC group regular.
  * @note   These parameters have an impact on ADC scope: ADC group regular.
  *         Refer to corresponding unitary functions into
  *         @ref ADC_MS32_EF_Configuration_ADC_Group_Regular
  *         (functions with prefix "REG").
  * @note   The setting of these parameters by function @ref MS32_ADC_Init()
  *         is conditioned to ADC state:
  *         ADC instance must be disabled.
  *         This condition is applied to all ADC features, for efficiency
  *         and compatibility over all MS32 families. However, the different
  *         features can be set under different ADC state conditions
  *         (setting possible with ADC enabled without conversion on going,
  *         ADC enabled with conversion on going, ...)
  *         Each feature can be updated afterwards with a unitary function
  *         and potentially with ADC in a different state than disabled,
  *         refer to description of each function for setting
  *         conditioned to ADC state.
  * @note   After using this function, other features must be configured
  *         using LL unitary functions.
  *         The minimum configuration remaining to be done is:
  *          - Set ADC group regular sequencer:
  *            map channel on rank corresponding to channel number.
  *            Refer to function @ref MS32_ADC_REG_SetSequencerChannels();
  *          - Set ADC channel sampling time
  *            Refer to function MS32_ADC_SetChannelSamplingTime();
  * @param  ADCx ADC instance
  * @param  AdcRegInitStr Pointer to a @ref MS32_ADC_REG_InitTypeDef structure
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: ADC registers are initialized
  *          - ERROR: ADC registers are not initialized
  */
ErrorStatus MS32_ADC_REG_Init(ADC_TypeDef *ADCx, MS32_ADC_REG_InitTypeDef *AdcRegInitStr) {
  ErrorStatus status = SUCCESS;

  /* Enable clock */
  MS32_APB1_GRP2_EnableClock(MS32_APB1_GRP2_PERIPH_ADC1);

  /* Note: Hardware constraint (refer to description of this function):       */
  /*       ADC instance must be disabled.                                     */
  if (MS32_ADC_IsEnabled(ADCx) == 0U) {
    /* Configuration of ADC hierarchical scope:                               */
    /*  - ADC group regular                                                   */
    /*    - Set ADC group regular trigger source                              */
    /*    - Set ADC group regular sequencer discontinuous mode                */
    /*    - Set ADC group regular continuous mode                             */
    /*    - Set ADC group regular conversion data transfer: no transfer or    */
    /*      transfer by DMA, and DMA requests mode                            */
    /*    - Set ADC group regular overrun behavior                            */
    /*  Note: On this MS32 serie, ADC trigger edge is set to value 0x0 by     */
    /*       setting of trigger source to SW start.                           */
    MODIFY_REG(ADCx->CFGR1,
                 ADC_CFGR1_EXTSEL
               | ADC_CFGR1_EXTEN
               | ADC_CFGR1_DISCEN
               | ADC_CFGR1_CONT
               | ADC_CFGR1_DMAEN
               | ADC_CFGR1_DMACFG
               | ADC_CFGR1_OVRMOD
              ,
                 AdcRegInitStr->TriggerSource
               | AdcRegInitStr->SequencerDiscont
               | AdcRegInitStr->ContinuousMode
               | AdcRegInitStr->DMATransfer
               | AdcRegInitStr->Overrun
              );

  } else {
    /* Initialization error: ADC instance is not disabled. */
    status = ERROR;
  }

  return status;
}

/**
  * @brief  Set each @ref MS32_ADC_REG_InitTypeDef field to default value.
  * @param  AdcRegInitStr Pointer to a @ref MS32_ADC_REG_InitTypeDef structure
  *                            whose fields will be set to default values.
  * @retval None
  */
void MS32_ADC_REG_StructInit(MS32_ADC_REG_InitTypeDef *AdcRegInitStr) {
  /* Set AdcRegInitStr fields to default values */
  /* Set fields of ADC group regular */
  /* Note: On this MS32 serie, ADC trigger edge is set to value 0x0 by        */
  /*       setting of trigger source to SW start.                             */
  AdcRegInitStr->TriggerSource    = MS32_ADC_REG_TRIG_SOFTWARE;
  AdcRegInitStr->SequencerDiscont = MS32_ADC_REG_SEQ_DISCONT_DISABLE;
  AdcRegInitStr->ContinuousMode   = MS32_ADC_REG_CONV_SINGLE;
  AdcRegInitStr->DMATransfer      = MS32_ADC_REG_DMA_TRANSFER_NONE;
  AdcRegInitStr->Overrun          = MS32_ADC_REG_OVR_DATA_OVERWRITTEN;
}

/**
  * @brief  Initializes the ADC interrupt according to the specified parameters.
  * @param  ADCx ADC Instance
  * @param  InterruptFunc  contains the configuration information for the ADC interrupt.
  *         This parameter can be one or more of the following values:
  *         @arg @ref MS32_ADC_IT_ADRDY
  *         @arg @ref MS32_ADC_IT_EOC  
  *         @arg @ref MS32_ADC_IT_EOS  
  *         @arg @ref MS32_ADC_IT_OVR  
  *         @arg @ref MS32_ADC_IT_EOSMP
  *         @arg @ref MS32_ADC_IT_AWD1  
  * @param  Priority  the interrupt priority 
  *         This parameter can be a value of 0x0~0x3
  * @retval None
  */
void MS32_ADC_ITConfig(ADC_TypeDef *ADCx, uint32_t InterruptFunc, uint32_t Priority) {
  /* Enable clock */
  MS32_APB1_GRP2_EnableClock(MS32_APB1_GRP2_PERIPH_ADC1);

  /*-------------------------------- ALL Interrrupt --------------------------*/
  WRITE_REG(ADCx->ISR, MS32_ADC_FLAG_ALL);
  SET_BIT(ADCx->IER, InterruptFunc);

  /*----------------------------- NVIC configuration -------------------------*/
  if (READ_BIT(ADCx->IER, MS32_ADC_IT_ALL)) {
    NVIC_EnableIRQ(ADC1_COMP_IRQn);
    NVIC_SetPriority(ADC1_COMP_IRQn, Priority);
  } else {
    NVIC_DisableIRQ(ADC1_COMP_IRQn);
  }
}

/**
  * @brief  Get the ADC flags according to the internal ADC ISR registers.
  * @param  ADCx ADC Instance
  * @param  Flags specifies the function flags.
  *          This parameter can be one or more of the following values:
  *            @arg @ref MS32_ADC_FLAG_ADRDY
  *            @arg @ref MS32_ADC_FLAG_EOC  
  *            @arg @ref MS32_ADC_FLAG_EOS  
  *            @arg @ref MS32_ADC_FLAG_OVR  
  *            @arg @ref MS32_ADC_FLAG_EOSMP
  *            @arg @ref MS32_ADC_FLAG_AWD1 
  * @note   Clear flags After getting the interrupt flags equal to set. 
  * @retval A FlagStatus enumeration value:
  *          - SET:   flag set(equal to "1")
  *          - RESET: flag no set(equal to "0")
  */
FlagStatus MS32_ADC_GetStatusFlag(ADC_TypeDef *ADCx, uint32_t Flags) {
  FlagStatus flags;

  if (READ_BIT(ADCx->ISR, Flags)) {
    flags = SET;
    WRITE_REG(ADCx->ISR, Flags);
  } else {
    flags = RESET;
  }

  return flags;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
