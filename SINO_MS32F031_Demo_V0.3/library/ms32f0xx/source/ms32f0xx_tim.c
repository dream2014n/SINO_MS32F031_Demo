/* Includes ------------------------------------------------------------------*/
#include "ms32f0xx_tim.h"
#include "ms32f0xx_bus.h"


/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup TIM_MS32_Private_Functions TIM Private Functions
  * @{
  */
static ErrorStatus TimClockEn (TIM_TypeDef *TIMx);
static ErrorStatus OC1Config  (TIM_TypeDef *TIMx, MS32_TIM_OC_InitTypeDef *TimOcInitStr);
static ErrorStatus OC2Config  (TIM_TypeDef *TIMx, MS32_TIM_OC_InitTypeDef *TimOcInitStr);
static ErrorStatus OC3Config  (TIM_TypeDef *TIMx, MS32_TIM_OC_InitTypeDef *TimOcInitStr);
static ErrorStatus OC4Config  (TIM_TypeDef *TIMx, MS32_TIM_OC_InitTypeDef *TimOcInitStr);
static ErrorStatus IC1Config  (TIM_TypeDef *TIMx, MS32_TIM_IC_InitTypeDef *TimIcInitStr);
static ErrorStatus IC2Config  (TIM_TypeDef *TIMx, MS32_TIM_IC_InitTypeDef *TimIcInitStr);
static ErrorStatus IC3Config  (TIM_TypeDef *TIMx, MS32_TIM_IC_InitTypeDef *TimIcInitStr);
static ErrorStatus IC4Config  (TIM_TypeDef *TIMx, MS32_TIM_IC_InitTypeDef *TimIcInitStr);


/* Exported functions --------------------------------------------------------*/
/** @addtogroup TIM_MS32_EF_Init
  * @{
  */

/**
  * @brief  Set TIMx registers to their reset values.
  * @param  TIMx Timer instance
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: TIMx registers are de-initialized
  *          - ERROR: invalid TIMx instance
  */
ErrorStatus MS32_TIM_DeInit(TIM_TypeDef *TIMx) {
  ErrorStatus result = SUCCESS;

  if (TIMx == TIM1) {
    MS32_APB1_GRP2_EnableClock(MS32_APB1_GRP2_PERIPH_TIM1);
    MS32_APB1_GRP2_ForceReset(MS32_APB1_GRP2_PERIPH_TIM1);
    MS32_APB1_GRP2_ReleaseReset(MS32_APB1_GRP2_PERIPH_TIM1);
  } else if (TIMx == TIM2) {
    MS32_APB1_GRP1_EnableClock(MS32_APB1_GRP1_PERIPH_TIM2);
    MS32_APB1_GRP1_ForceReset(MS32_APB1_GRP1_PERIPH_TIM2);
    MS32_APB1_GRP1_ReleaseReset(MS32_APB1_GRP1_PERIPH_TIM2);
  } else if (TIMx == TIM3) {
    MS32_APB1_GRP1_EnableClock(MS32_APB1_GRP1_PERIPH_TIM3);
    MS32_APB1_GRP1_ForceReset(MS32_APB1_GRP1_PERIPH_TIM3);
    MS32_APB1_GRP1_ReleaseReset(MS32_APB1_GRP1_PERIPH_TIM3);
  } else if (TIMx == TIM14) {
    MS32_APB1_GRP1_EnableClock(MS32_APB1_GRP1_PERIPH_TIM14);
    MS32_APB1_GRP1_ForceReset(MS32_APB1_GRP1_PERIPH_TIM14);
    MS32_APB1_GRP1_ReleaseReset(MS32_APB1_GRP1_PERIPH_TIM14);
  } else if (TIMx == TIM16) {
    MS32_APB1_GRP2_EnableClock(MS32_APB1_GRP2_PERIPH_TIM16);
    MS32_APB1_GRP2_ForceReset(MS32_APB1_GRP2_PERIPH_TIM16);
    MS32_APB1_GRP2_ReleaseReset(MS32_APB1_GRP2_PERIPH_TIM16);
  } else if (TIMx == TIM17) {
    MS32_APB1_GRP2_EnableClock(MS32_APB1_GRP2_PERIPH_TIM17);
    MS32_APB1_GRP2_ForceReset(MS32_APB1_GRP2_PERIPH_TIM17);
    MS32_APB1_GRP2_ReleaseReset(MS32_APB1_GRP2_PERIPH_TIM17);
  } else {
    result = ERROR;
  }

  return result;
}

/**
  * @brief  Set the fields of the time base unit configuration data structure
  *         to their default values.
  * @param  TimInitStr pointer to a @ref MS32_TIM_InitTypeDef structure (time base unit configuration data structure)
  * @retval None
  */
void MS32_TIM_StructInit(MS32_TIM_InitTypeDef *TimInitStr) {
  /* Set the default configuration */
  TimInitStr->Prescaler         = (uint16_t)0x0000;
  TimInitStr->CounterMode       = MS32_TIM_COUNTERMODE_CENTER1;
  TimInitStr->Autoreload        = 0xFFFFFFFFU;
  TimInitStr->AutoreloadPreload = MS32_TIM_AUTORELOAD_PRE_DISABLE;
  TimInitStr->OnePulseMode      = MS32_TIM_ONEPULSEMODE_REPETITIVE;
  TimInitStr->UpdateSource      = MS32_TIM_UPDATESOURCE_REGULAR;
  TimInitStr->UpdateEvent       = MS32_TIM_UPDATE_EVENT_ENABLE;
  TimInitStr->ClockDivision     = MS32_TIM_CLOCKDIVISION_DIV1;
  TimInitStr->RepetitionCounter = (uint8_t)0x00;
}

/**
  * @brief  Configure the TIMx time base unit.
  * @param  TIMx Timer Instance
  * @param  TimInitStr pointer to a @ref MS32_TIM_InitTypeDef structure (TIMx time base unit configuration data structure)
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: TIMx registers are de-initialized
  *          - ERROR: not applicable
  */
ErrorStatus MS32_TIM_Init(TIM_TypeDef *TIMx, MS32_TIM_InitTypeDef *TimInitStr) {
  uint32_t tmpcr1;

  TimClockEn(TIMx);

  tmpcr1 = MS32_TIM_ReadReg(TIMx, CR1);

  /* Set the auto-reload preload enable */
  MODIFY_REG(tmpcr1, \
             (TIM_CR1_CKD | TIM_CR1_ARPE | TIM_CR1_CMS | TIM_CR1_DIR | TIM_CR1_OPM | TIM_CR1_URS | TIM_CR1_UDIS), \
             (TimInitStr->ClockDivision | TimInitStr->AutoreloadPreload | TimInitStr->CounterMode | \
              TimInitStr->OnePulseMode | TimInitStr->UpdateSource | TimInitStr->UpdateEvent));

  /* Write to TIMx CR1 */
  MS32_TIM_WriteReg(TIMx, CR1, tmpcr1);

  /* Set the Autoreload value */
  MS32_TIM_SetAutoReload(TIMx, TimInitStr->Autoreload);

  /* Set the Prescaler value */
  MS32_TIM_SetPrescaler(TIMx, TimInitStr->Prescaler);

  if (IS_TIM_REPETITION_COUNTER_INSTANCE(TIMx)) {
    /* Set the Repetition Counter value */
    MS32_TIM_SetRepetitionCounter(TIMx, TimInitStr->RepetitionCounter);
  }

  /* Generate an update event to reload the Prescaler
     and the repetition counter value (if applicable) immediately */
  MS32_TIM_GenerateEvent_UPDATE(TIMx);

  return SUCCESS;
}

/**
  * @brief  Initializes the TIM interrupt according to the specified parameters.
  * @param  TIMx TIM Instance
  * @param  InterruptFunc  contains the configuration information for the TIM interrupt.
  *         This parameter can be one or more of the following values:
  *         @arg @ref MS32_TIM_DIER_UIE  
  *         @arg @ref MS32_TIM_DIER_CC1IE
  *         @arg @ref MS32_TIM_DIER_CC2IE
  *         @arg @ref MS32_TIM_DIER_CC3IE
  *         @arg @ref MS32_TIM_DIER_CC4IE
  *         @arg @ref MS32_TIM_DIER_COMIE
  *         @arg @ref MS32_TIM_DIER_TIE  
  *         @arg @ref MS32_TIM_DIER_BIE  
  * @param  Priority  the interrupt priority 
  *         This parameter can be a value of 0x0~0x3
  * @retval None
  */
void MS32_TIM_ITConfig(TIM_TypeDef *TIMx, uint32_t InterruptFunc, uint32_t Priority) {
  static IRQn_Type irq_str = (IRQn_Type)0;
  static uint32_t  TIM_IE;
  
  TimClockEn(TIMx);

  /*-------------------------------- ALL Interrrupt --------------------------*/
  CLEAR_BIT(TIMx->SR, MS32_TIM_SR_ALLIF);
  SET_BIT(TIMx->DIER, InterruptFunc);

  /*----------------------------- NVIC configuration -------------------------*/
  if (TIMx == TIM1) {
    if (READ_BIT(TIMx->DIER, MS32_TIM_DIER_UIE | MS32_TIM_DIER_COMIE | MS32_TIM_DIER_TIE | MS32_TIM_DIER_BIE)) {
      NVIC_EnableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);
      NVIC_SetPriority(TIM1_BRK_UP_TRG_COM_IRQn, Priority);
    } else {
      NVIC_DisableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);
    }
    irq_str = TIM1_CC_IRQn;
    TIM_IE  = MS32_TIM_DIER_CC1IE | MS32_TIM_DIER_CC2IE | MS32_TIM_DIER_CC3IE | MS32_TIM_DIER_CC4IE;
  } else if (TIMx == TIM2) {
    irq_str = TIM2_IRQn;
    TIM_IE  = MS32_TIM_DIER_UIE | MS32_TIM_DIER_CC1IE | MS32_TIM_DIER_CC2IE | MS32_TIM_DIER_CC3IE | MS32_TIM_DIER_CC4IE | MS32_TIM_DIER_TIE;
  } else if (TIMx == TIM3) {
    irq_str = TIM3_IRQn;
    TIM_IE  = MS32_TIM_DIER_UIE | MS32_TIM_DIER_CC1IE | MS32_TIM_DIER_CC2IE | MS32_TIM_DIER_CC3IE | MS32_TIM_DIER_CC4IE | MS32_TIM_DIER_TIE;
  } else if (TIMx == TIM14) {
    irq_str = TIM14_IRQn;
    TIM_IE  = MS32_TIM_DIER_UIE | MS32_TIM_DIER_CC1IE;
  } else if (TIMx == TIM16) {
    irq_str = TIM16_IRQn;
    TIM_IE  = MS32_TIM_DIER_UIE | MS32_TIM_DIER_CC1IE | MS32_TIM_DIER_COMIE | MS32_TIM_DIER_BIE;
  } else if (TIMx == TIM17) {
    irq_str = TIM17_IRQn;
    TIM_IE  = MS32_TIM_DIER_UIE | MS32_TIM_DIER_CC1IE | MS32_TIM_DIER_COMIE | MS32_TIM_DIER_BIE;
  }

  if (irq_str != 0) {
    if (READ_BIT(TIMx->DIER, TIM_IE)) {
      NVIC_EnableIRQ(irq_str);
      NVIC_SetPriority(irq_str, Priority);
    } else {
      NVIC_DisableIRQ(irq_str);
    }
  }
}

/**
  * @brief  Set the fields of the TIMx output channel configuration data
  *         structure to their default values.
  * @param  TimOcInitStr pointer to a @ref MS32_TIM_OC_InitTypeDef structure (the output channel configuration data structure)
  * @retval None
  */
void MS32_TIM_OC_StructInit(MS32_TIM_OC_InitTypeDef *TimOcInitStr) {
  /* Set the default configuration */
  TimOcInitStr->OCMode       = MS32_TIM_OCMODE_FROZEN;
  TimOcInitStr->OCState      = MS32_TIM_OCSTATE_DISABLE;
  TimOcInitStr->OCNState     = MS32_TIM_OCSTATE_DISABLE;
  TimOcInitStr->CompareValue = 0x00000000U;
  TimOcInitStr->OCPolarity   = MS32_TIM_OCPOLARITY_HIGH;
  TimOcInitStr->OCNPolarity  = MS32_TIM_OCPOLARITY_HIGH;
  TimOcInitStr->OCIdleState  = MS32_TIM_OCIDLESTATE_LOW;
  TimOcInitStr->OCNIdleState = MS32_TIM_OCIDLESTATE_LOW;
}

/**
  * @brief  Configure the TIMx output channel.
  * @param  TIMx Timer Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref MS32_TIM_CHANNEL_CH1
  *         @arg @ref MS32_TIM_CHANNEL_CH2
  *         @arg @ref MS32_TIM_CHANNEL_CH3
  *         @arg @ref MS32_TIM_CHANNEL_CH4
  * @param  TimOcInitStr pointer to a @ref MS32_TIM_OC_InitTypeDef structure (TIMx output channel configuration data structure)
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: TIMx output channel is initialized
  *          - ERROR: TIMx output channel is not initialized
  */
ErrorStatus MS32_TIM_OC_Init(TIM_TypeDef *TIMx, uint32_t Channel, MS32_TIM_OC_InitTypeDef *TimOcInitStr) {
  ErrorStatus result = ERROR;

  TimClockEn(TIMx);

  switch (Channel) {
    case MS32_TIM_CHANNEL_CH1:
      result = OC1Config(TIMx, TimOcInitStr);
      break;

    case MS32_TIM_CHANNEL_CH2:
      result = OC2Config(TIMx, TimOcInitStr);
      break;

    case MS32_TIM_CHANNEL_CH3:
      result = OC3Config(TIMx, TimOcInitStr);
      break;

    case MS32_TIM_CHANNEL_CH4:
      result = OC4Config(TIMx, TimOcInitStr);
      break;

    default:
      break;
  }

  return result;
}

/**
  * @brief  Set the fields of the TIMx input channel configuration data
  *         structure to their default values.
  * @param  TimIcInitStr pointer to a @ref MS32_TIM_IC_InitTypeDef structure (the input channel configuration data structure)
  * @retval None
  */
void MS32_TIM_IC_StructInit(MS32_TIM_IC_InitTypeDef *TimIcInitStr) {
  /* Set the default configuration */
  TimIcInitStr->ICPolarity    = MS32_TIM_IC_POLARITY_RISING;
  TimIcInitStr->ICActiveInput = MS32_TIM_ACTIVEINPUT_DIRECTTI;
  TimIcInitStr->ICPrescaler   = MS32_TIM_ICPSC_DIV1;
  TimIcInitStr->ICFilter      = MS32_TIM_IC_FILTER_FDIV1;
}

/**
  * @brief  Configure the TIMx input channel.
  * @param  TIMx Timer Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref MS32_TIM_CHANNEL_CH1
  *         @arg @ref MS32_TIM_CHANNEL_CH2
  *         @arg @ref MS32_TIM_CHANNEL_CH3
  *         @arg @ref MS32_TIM_CHANNEL_CH4
  * @param  TIM_IC_InitStruct pointer to a @ref MS32_TIM_IC_InitTypeDef structure (TIMx input channel configuration data structure)
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: TIMx output channel is initialized
  *          - ERROR: TIMx output channel is not initialized
  */
ErrorStatus MS32_TIM_IC_Init(TIM_TypeDef *TIMx, uint32_t Channel, MS32_TIM_IC_InitTypeDef *TIM_IC_InitStruct) {
  ErrorStatus result = ERROR;

  TimClockEn(TIMx);

  switch (Channel) {
    case MS32_TIM_CHANNEL_CH1:
      result = IC1Config(TIMx, TIM_IC_InitStruct);
      break;

    case MS32_TIM_CHANNEL_CH2:
      result = IC2Config(TIMx, TIM_IC_InitStruct);
      break;

    case MS32_TIM_CHANNEL_CH3:
      result = IC3Config(TIMx, TIM_IC_InitStruct);
      break;

    case MS32_TIM_CHANNEL_CH4:
      result = IC4Config(TIMx, TIM_IC_InitStruct);
      break;

    default:
      break;
  }

  return result;
}

/**
  * @brief  Fills each TIM_EncoderInitStruct field with its default value
  * @param  TIM_EncoderInitStruct pointer to a @ref MS32_TIM_ENCODER_InitTypeDef structure (encoder interface configuration data structure)
  * @retval None
  */
void MS32_TIM_ENCODER_StructInit(MS32_TIM_ENCODER_InitTypeDef *TIM_EncoderInitStruct) {
  /* Set the default configuration */
  TIM_EncoderInitStruct->EncoderMode    = MS32_TIM_ENCODERMODE_X2_TI1;
  TIM_EncoderInitStruct->IC1Polarity    = MS32_TIM_IC_POLARITY_RISING;
  TIM_EncoderInitStruct->IC1ActiveInput = MS32_TIM_ACTIVEINPUT_DIRECTTI;
  TIM_EncoderInitStruct->IC1Prescaler   = MS32_TIM_ICPSC_DIV1;
  TIM_EncoderInitStruct->IC1Filter      = MS32_TIM_IC_FILTER_FDIV1;
  TIM_EncoderInitStruct->IC2Polarity    = MS32_TIM_IC_POLARITY_RISING;
  TIM_EncoderInitStruct->IC2ActiveInput = MS32_TIM_ACTIVEINPUT_DIRECTTI;
  TIM_EncoderInitStruct->IC2Prescaler   = MS32_TIM_ICPSC_DIV1;
  TIM_EncoderInitStruct->IC2Filter      = MS32_TIM_IC_FILTER_FDIV1;
}

/**
  * @brief  Configure the encoder interface of the timer instance.
  * @param  TIMx Timer Instance
  * @param  TIM_EncoderInitStruct pointer to a @ref MS32_TIM_ENCODER_InitTypeDef structure (TIMx encoder interface configuration data structure)
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: TIMx registers are de-initialized
  *          - ERROR: not applicable
  */
ErrorStatus MS32_TIM_ENCODER_Init(TIM_TypeDef *TIMx, MS32_TIM_ENCODER_InitTypeDef *TIM_EncoderInitStruct) {
  uint32_t tmpccmr1;
  uint32_t tmpccer;

  TimClockEn(TIMx);

  /* Disable the CC1 and CC2: Reset the CC1E and CC2E Bits */
  TIMx->CCER &= (uint32_t)~(TIM_CCER_CC1E | TIM_CCER_CC2E);

  /* Get the TIMx CCMR1 register value */
  tmpccmr1 = MS32_TIM_ReadReg(TIMx, CCMR1);

  /* Get the TIMx CCER register value */
  tmpccer = MS32_TIM_ReadReg(TIMx, CCER);

  /* Configure TI1 */
  tmpccmr1 &= (uint32_t)~(TIM_CCMR1_CC1S | TIM_CCMR1_IC1F  | TIM_CCMR1_IC1PSC);
  tmpccmr1 |= (uint32_t)(TIM_EncoderInitStruct->IC1ActiveInput >> 16U);
  tmpccmr1 |= (uint32_t)(TIM_EncoderInitStruct->IC1Filter >> 16U);
  tmpccmr1 |= (uint32_t)(TIM_EncoderInitStruct->IC1Prescaler >> 16U);

  /* Configure TI2 */
  tmpccmr1 &= (uint32_t)~(TIM_CCMR1_CC2S | TIM_CCMR1_IC2F  | TIM_CCMR1_IC2PSC);
  tmpccmr1 |= (uint32_t)(TIM_EncoderInitStruct->IC2ActiveInput >> 8U);
  tmpccmr1 |= (uint32_t)(TIM_EncoderInitStruct->IC2Filter >> 8U);
  tmpccmr1 |= (uint32_t)(TIM_EncoderInitStruct->IC2Prescaler >> 8U);

  /* Set TI1 and TI2 polarity and enable TI1 and TI2 */
  tmpccer &= (uint32_t)~(TIM_CCER_CC1P | TIM_CCER_CC1NP | TIM_CCER_CC2P | TIM_CCER_CC2NP);
  tmpccer |= (uint32_t)(TIM_EncoderInitStruct->IC1Polarity);
  tmpccer |= (uint32_t)(TIM_EncoderInitStruct->IC2Polarity << 4U);
  tmpccer |= (uint32_t)(TIM_CCER_CC1E | TIM_CCER_CC2E);

  /* Set encoder mode */
  MS32_TIM_SetEncoderMode(TIMx, TIM_EncoderInitStruct->EncoderMode);

  /* Write to TIMx CCMR1 */
  MS32_TIM_WriteReg(TIMx, CCMR1, tmpccmr1);

  /* Write to TIMx CCER */
  MS32_TIM_WriteReg(TIMx, CCER, tmpccer);

  return SUCCESS;
}

/**
  * @brief  Set the fields of the TIMx Hall sensor interface configuration data
  *         structure to their default values.
  * @param  TIM_HallSensorInitStruct pointer to a @ref MS32_TIM_HALLSENSOR_InitTypeDef structure (HALL sensor interface configuration data structure)
  * @retval None
  */
void MS32_TIM_HALLSENSOR_StructInit(MS32_TIM_HALLSENSOR_InitTypeDef *TIM_HallSensorInitStruct) {
  /* Set the default configuration */
  TIM_HallSensorInitStruct->IC1Polarity  = MS32_TIM_IC_POLARITY_RISING;
  TIM_HallSensorInitStruct->IC1Prescaler = MS32_TIM_ICPSC_DIV1;
  TIM_HallSensorInitStruct->IC1Filter    = MS32_TIM_IC_FILTER_FDIV1;
}

/**
  * @brief  Configure the Hall sensor interface of the timer instance.
  * @note TIMx CH1, CH2 and CH3 inputs connected through a XOR
  *       to the TI1 input channel
  * @note TIMx slave mode controller is configured in reset mode.
          Selected internal trigger is TI1F_ED.
  * @note Channel 1 is configured as input, IC1 is mapped on TRC.
  * @note Captured value stored in TIMx_CCR1 correspond to the time elapsed
  *       between 2 changes on the inputs. It gives information about motor speed.
  * @note MS32_TIM_IC_POLARITY_BOTHEDGE must not be used for TI1 when it is used
  *       when TIMx operates in Hall sensor interface mode.
  * @param  TIMx Timer Instance
  * @param  TIM_HallSensorInitStruct pointer to a @ref MS32_TIM_HALLSENSOR_InitTypeDef structure (TIMx HALL sensor interface configuration data structure)
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: TIMx registers are de-initialized
  *          - ERROR: not applicable
  */
ErrorStatus MS32_TIM_HALLSENSOR_Init(TIM_TypeDef *TIMx, MS32_TIM_HALLSENSOR_InitTypeDef *TIM_HallSensorInitStruct) {
  uint32_t tmpcr2;
  uint32_t tmpccmr1;
  uint32_t tmpccer;
  uint32_t tmpsmcr;

  TimClockEn(TIMx);

  /* Disable the CC1 and CC2: Reset the CC1E and CC2E Bits */
  TIMx->CCER &= (uint32_t)~(TIM_CCER_CC1E | TIM_CCER_CC2E);

  /* Get the TIMx CR2 register value */
  tmpcr2 = MS32_TIM_ReadReg(TIMx, CR2);

  /* Get the TIMx CCMR1 register value */
  tmpccmr1 = MS32_TIM_ReadReg(TIMx, CCMR1);

  /* Get the TIMx CCER register value */
  tmpccer = MS32_TIM_ReadReg(TIMx, CCER);

  /* Get the TIMx SMCR register value */
  tmpsmcr = MS32_TIM_ReadReg(TIMx, SMCR);

  /* Connect TIMx_CH1, CH2 and CH3 pins to the TI1 input */
  tmpcr2 |= TIM_CR2_TI1S;

  /* OC2REF signal is used as trigger output (TRGO) */
  tmpcr2 |= MS32_TIM_TRGO_OC2REF;

  /* Configure the slave mode controller */
  tmpsmcr &= (uint32_t)~(TIM_SMCR_TS | TIM_SMCR_SMS);
  tmpsmcr |= MS32_TIM_TS_TI1F_ED;
  tmpsmcr |= MS32_TIM_SLAVEMODE_RESET;

  /* Configure input channel 1 */
  tmpccmr1 &= (uint32_t)~(TIM_CCMR1_CC1S | TIM_CCMR1_IC1F  | TIM_CCMR1_IC1PSC);
  tmpccmr1 |= (uint32_t)(MS32_TIM_ACTIVEINPUT_TRC >> 16U);
  tmpccmr1 |= (uint32_t)(TIM_HallSensorInitStruct->IC1Filter >> 16U);
  tmpccmr1 |= (uint32_t)(TIM_HallSensorInitStruct->IC1Prescaler >> 16U);

  /* Set Channel 1 polarity and enable Channel 1 and Channel2 */
  tmpccer &= (uint32_t)~(TIM_CCER_CC1P | TIM_CCER_CC1NP);
  tmpccer |= (uint32_t)(TIM_HallSensorInitStruct->IC1Polarity);
  tmpccer |= (uint32_t)(TIM_CCER_CC1E);

  /* Write to TIMx CR2 */
  MS32_TIM_WriteReg(TIMx, CR2, tmpcr2);

  /* Write to TIMx SMCR */
  MS32_TIM_WriteReg(TIMx, SMCR, tmpsmcr);

  /* Write to TIMx CCMR1 */
  MS32_TIM_WriteReg(TIMx, CCMR1, tmpccmr1);

  /* Write to TIMx CCER */
  MS32_TIM_WriteReg(TIMx, CCER, tmpccer);

  return SUCCESS;
}

/**
  * @brief  Set the fields of the Break and Dead Time configuration data structure
  *         to their default values.
  * @param  TIM_BDTRInitStruct pointer to a @ref MS32_TIM_BDTR_InitTypeDef structure (Break and Dead Time configuration data structure)
  * @retval None
  */
void MS32_TIM_BDTR_StructInit(MS32_TIM_BDTR_InitTypeDef *TIM_BDTRInitStruct) {
  /* Set the default configuration */
  TIM_BDTRInitStruct->OSSRState       = MS32_TIM_OSSR_DISABLE;
  TIM_BDTRInitStruct->OSSIState       = MS32_TIM_OSSI_DISABLE;
  TIM_BDTRInitStruct->LockLevel       = MS32_TIM_LOCKLEVEL_OFF;
  TIM_BDTRInitStruct->DeadTime        = (uint8_t)0x00;
  TIM_BDTRInitStruct->BreakState      = MS32_TIM_BREAK_DISABLE;
  TIM_BDTRInitStruct->BreakPolarity   = MS32_TIM_BREAK_POLARITY_LOW;
  TIM_BDTRInitStruct->AutomaticOutput = MS32_TIM_AUTOMATICOUTPUT_DISABLE;
}

/**
  * @brief  Configure the Break and Dead Time feature of the timer instance.
  * @note As the bits AOE, BKP, BKE, OSSR, OSSI and DTG[7:0] can be write-locked
  *  depending on the LOCK configuration, it can be necessary to configure all of
  *  them during the first write access to the TIMx_BDTR register.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @param  TIMx Timer Instance
  * @param  TIM_BDTRInitStruct pointer to a @ref MS32_TIM_BDTR_InitTypeDef structure (Break and Dead Time configuration data structure)
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: Break and Dead Time is initialized
  *          - ERROR: not applicable
  */
ErrorStatus MS32_TIM_BDTR_Init(TIM_TypeDef *TIMx, MS32_TIM_BDTR_InitTypeDef *TIM_BDTRInitStruct) {
  uint32_t tmpbdtr = 0;

  TimClockEn(TIMx);

  /* Set the BDTR bits */
  MODIFY_REG(tmpbdtr, TIM_BDTR_DTG, TIM_BDTRInitStruct->DeadTime);
  MODIFY_REG(tmpbdtr, TIM_BDTR_LOCK, TIM_BDTRInitStruct->LockLevel);
  MODIFY_REG(tmpbdtr, TIM_BDTR_OSSI, TIM_BDTRInitStruct->OSSIState);
  MODIFY_REG(tmpbdtr, TIM_BDTR_OSSR, TIM_BDTRInitStruct->OSSRState);
  MODIFY_REG(tmpbdtr, TIM_BDTR_BKE, TIM_BDTRInitStruct->BreakState);
  MODIFY_REG(tmpbdtr, TIM_BDTR_BKP, TIM_BDTRInitStruct->BreakPolarity);
  MODIFY_REG(tmpbdtr, TIM_BDTR_AOE, TIM_BDTRInitStruct->AutomaticOutput);
  MODIFY_REG(tmpbdtr, TIM_BDTR_MOE, TIM_BDTRInitStruct->AutomaticOutput);

  /* Set TIMx_BDTR */
  MS32_TIM_WriteReg(TIMx, BDTR, tmpbdtr);

  return SUCCESS;
}

/**
  * @brief  Get the TIM flags according to the internal TIM SR registers.
  * @param  TIMx TIM Instance
  * @param  Flags specifies the function flags.
  *          This parameter can be one or more of the following values:
  *            @arg @ref MS32_TIM_SR_UIF  
  *            @arg @ref MS32_TIM_SR_CC1IF
  *            @arg @ref MS32_TIM_SR_CC2IF
  *            @arg @ref MS32_TIM_SR_CC3IF
  *            @arg @ref MS32_TIM_SR_CC4IF
  *            @arg @ref MS32_TIM_SR_COMIF
  *            @arg @ref MS32_TIM_SR_TIF  
  *            @arg @ref MS32_TIM_SR_BIF  
  *            @arg @ref MS32_TIM_SR_CC1OF
  *            @arg @ref MS32_TIM_SR_CC2OF
  *            @arg @ref MS32_TIM_SR_CC3OF
  *            @arg @ref MS32_TIM_SR_CC4OF
  * @note   Clear flags After getting the interrupt flags equal to set. 
  * @retval A FlagStatus enumeration value:
  *          - SET:   flag set(equal to "1")
  *          - RESET: flag no set(equal to "0")
  */
FlagStatus MS32_TIM_GetStatusFlag(TIM_TypeDef *TIMx, uint32_t Flags) {
  FlagStatus flags;

  if (READ_BIT(TIMx->SR, Flags)) {
    flags = SET;
    CLEAR_BIT(TIMx->SR, Flags);
  } else {
    flags = RESET;
  }

  return flags;
}


/** @addtogroup TIM_MS32_Private_Functions TIM Private Functions
  *  @brief   Private functions
  * @{
  */


/**
  * @brief  Enable TIMx clock.
  * @param  TIMx Timer Instance
  * @retval @retval An ErrorStatus enumeration value:
  *          - SUCCESS: TIMx registers are de-initialized
  *          - ERROR: invalid TIMx instance
  */
static ErrorStatus TimClockEn(TIM_TypeDef *TIMx) {
  ErrorStatus result = SUCCESS;

  if (TIMx == TIM1) {
    MS32_APB1_GRP2_EnableClock(MS32_APB1_GRP2_PERIPH_TIM1);
  } else if (TIMx == TIM2) {
    MS32_APB1_GRP1_EnableClock(MS32_APB1_GRP1_PERIPH_TIM2);
  } else if (TIMx == TIM3) {
    MS32_APB1_GRP1_EnableClock(MS32_APB1_GRP1_PERIPH_TIM3);
  } else if (TIMx == TIM14) {
    MS32_APB1_GRP1_EnableClock(MS32_APB1_GRP1_PERIPH_TIM14);
  } else if (TIMx == TIM16) {
    MS32_APB1_GRP2_EnableClock(MS32_APB1_GRP2_PERIPH_TIM16);
  } else if (TIMx == TIM17) {
    MS32_APB1_GRP2_EnableClock(MS32_APB1_GRP2_PERIPH_TIM17);
  } else {
    result = ERROR;
  }

  return result;
}

/**
  * @brief  Configure the TIMx output channel 1.
  * @param  TIMx Timer Instance
  * @param  TimOcInitStr pointer to the the TIMx output channel 1 configuration data structure
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: TIMx registers are de-initialized
  *          - ERROR: not applicable
  */
static ErrorStatus OC1Config(TIM_TypeDef *TIMx, MS32_TIM_OC_InitTypeDef *TimOcInitStr) {
  uint32_t tmpccmr1;
  uint32_t tmpccer;
  uint32_t tmpcr2;

  /* Disable the Channel 1: Reset the CC1E Bit */
  CLEAR_BIT(TIMx->CCER, TIM_CCER_CC1E);

  /* Get the TIMx CCER register value */
  tmpccer = MS32_TIM_ReadReg(TIMx, CCER);

  /* Get the TIMx CR2 register value */
  tmpcr2 = MS32_TIM_ReadReg(TIMx, CR2);

  /* Get the TIMx CCMR1 register value */
  tmpccmr1 = MS32_TIM_ReadReg(TIMx, CCMR1);

  /* Reset Capture/Compare selection Bits */
  CLEAR_BIT(tmpccmr1, TIM_CCMR1_CC1S);

  /* Set the Output Compare Mode */
  MODIFY_REG(tmpccmr1, TIM_CCMR1_OC1M, TimOcInitStr->OCMode);

  /* Set the Output Compare Polarity and Output State */
  MODIFY_REG(tmpccer, \
             (TIM_CCER_CC1P | TIM_CCER_CC1E | TIM_CCER_CC1NP | TIM_CCER_CC1NE), \
             (TimOcInitStr->OCPolarity | TimOcInitStr->OCState | \
              (TimOcInitStr->OCNPolarity << (TIM_CCER_CC1NE_Pos - TIM_CCER_CC1E_Pos)) | \
              (TimOcInitStr->OCNState << (TIM_CCER_CC1NP_Pos - TIM_CCER_CC1P_Pos))));

  /* Set the Output Idle state and the complementary output Idle state */
  MODIFY_REG(tmpcr2, \
             (TIM_CR2_OIS1 | TIM_CR2_OIS1N), \
             (TimOcInitStr->OCIdleState | (TimOcInitStr->OCNIdleState << (TIM_CR2_OIS1N_Pos - TIM_CR2_OIS1_Pos))));

  /* Write to TIMx CR2 */
  MS32_TIM_WriteReg(TIMx, CR2, tmpcr2);

  /* Write to TIMx CCMR1 */
  MS32_TIM_WriteReg(TIMx, CCMR1, tmpccmr1);

  /* Set the Capture Compare Register value */
  MS32_TIM_OC_SetCompareCH1(TIMx, TimOcInitStr->CompareValue);

  /* Write to TIMx CCER */
  MS32_TIM_WriteReg(TIMx, CCER, tmpccer);

  return SUCCESS;
}

/**
  * @brief  Configure the TIMx output channel 2.
  * @param  TIMx Timer Instance
  * @param  TimOcInitStr pointer to the the TIMx output channel 2 configuration data structure
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: TIMx registers are de-initialized
  *          - ERROR: not applicable
  */
static ErrorStatus OC2Config(TIM_TypeDef *TIMx, MS32_TIM_OC_InitTypeDef *TimOcInitStr) {
  uint32_t tmpccmr1;
  uint32_t tmpccer;
  uint32_t tmpcr2;

  /* Disable the Channel 2: Reset the CC2E Bit */
  CLEAR_BIT(TIMx->CCER, TIM_CCER_CC2E);

  /* Get the TIMx CCER register value */
  tmpccer =  MS32_TIM_ReadReg(TIMx, CCER);

  /* Get the TIMx CR2 register value */
  tmpcr2 = MS32_TIM_ReadReg(TIMx, CR2);

  /* Get the TIMx CCMR1 register value */
  tmpccmr1 = MS32_TIM_ReadReg(TIMx, CCMR1);

  /* Reset Capture/Compare selection Bits */
  CLEAR_BIT(tmpccmr1, TIM_CCMR1_CC2S);

  /* Select the Output Compare Mode */
  MODIFY_REG(tmpccmr1, TIM_CCMR1_OC2M, TimOcInitStr->OCMode << (TIM_CCMR1_OC2M_Pos - TIM_CCMR1_OC1M_Pos));

  /* Set the Output Compare Polarity */
  MODIFY_REG(tmpccer, 
             (TIM_CCER_CC2P | TIM_CCER_CC2E | TIM_CCER_CC2NP | TIM_CCER_CC2NE), \
             ((TimOcInitStr->OCPolarity << (TIM_CCER_CC2P_Pos - TIM_CCER_CC1P_Pos)) | \
              (TimOcInitStr->OCState << (TIM_CCER_CC2E_Pos - TIM_CCER_CC1E_Pos)) | \
              (TimOcInitStr->OCNPolarity << (TIM_CCER_CC2NP_Pos - TIM_CCER_CC1P_Pos)) | \
              (TimOcInitStr->OCNState << (TIM_CCER_CC2NE_Pos - TIM_CCER_CC1E_Pos))));

  /* Set the Output Idle state and the complementary output Idle state */
  MODIFY_REG(tmpcr2, \
             (TIM_CR2_OIS2 | TIM_CR2_OIS2N), \
             ((TimOcInitStr->OCIdleState << (TIM_CR2_OIS2_Pos - TIM_CR2_OIS1_Pos)) | \
              (TimOcInitStr->OCNIdleState << (TIM_CR2_OIS2N_Pos - TIM_CR2_OIS1_Pos))));

  /* Write to TIMx CR2 */
  MS32_TIM_WriteReg(TIMx, CR2, tmpcr2);

  /* Write to TIMx CCMR1 */
  MS32_TIM_WriteReg(TIMx, CCMR1, tmpccmr1);

  /* Set the Capture Compare Register value */
  MS32_TIM_OC_SetCompareCH2(TIMx, TimOcInitStr->CompareValue);

  /* Write to TIMx CCER */
  MS32_TIM_WriteReg(TIMx, CCER, tmpccer);

  return SUCCESS;
}

/**
  * @brief  Configure the TIMx output channel 3.
  * @param  TIMx Timer Instance
  * @param  TimOcInitStr pointer to the the TIMx output channel 3 configuration data structure
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: TIMx registers are de-initialized
  *          - ERROR: not applicable
  */
static ErrorStatus OC3Config(TIM_TypeDef *TIMx, MS32_TIM_OC_InitTypeDef *TimOcInitStr) {
  uint32_t tmpccmr2;
  uint32_t tmpccer;
  uint32_t tmpcr2;

  /* Disable the Channel 3: Reset the CC3E Bit */
  CLEAR_BIT(TIMx->CCER, TIM_CCER_CC3E);

  /* Get the TIMx CCER register value */
  tmpccer =  MS32_TIM_ReadReg(TIMx, CCER);

  /* Get the TIMx CR2 register value */
  tmpcr2 = MS32_TIM_ReadReg(TIMx, CR2);

  /* Get the TIMx CCMR2 register value */
  tmpccmr2 = MS32_TIM_ReadReg(TIMx, CCMR2);

  /* Reset Capture/Compare selection Bits */
  CLEAR_BIT(tmpccmr2, TIM_CCMR2_CC3S);

  /* Select the Output Compare Mode */
  MODIFY_REG(tmpccmr2, TIM_CCMR2_OC3M, TimOcInitStr->OCMode);

  /* Set the Output Compare Polarity */
  MODIFY_REG(tmpccer, 
             (TIM_CCER_CC3P | TIM_CCER_CC3E | TIM_CCER_CC3NP | TIM_CCER_CC3NE), \
             ((TimOcInitStr->OCPolarity << (TIM_CCER_CC3P_Pos - TIM_CCER_CC1P_Pos)) | \
              (TimOcInitStr->OCState << (TIM_CCER_CC3E_Pos - TIM_CCER_CC1E_Pos)) | \
              (TimOcInitStr->OCNPolarity << (TIM_CCER_CC3NP_Pos - TIM_CCER_CC1P_Pos)) | \
              (TimOcInitStr->OCNState << (TIM_CCER_CC3NE_Pos - TIM_CCER_CC1E_Pos))));

  /* Set the Output Idle state and the complementary output Idle state */
  MODIFY_REG(tmpcr2, \
             (TIM_CR2_OIS3 | TIM_CR2_OIS3N), \
             ((TimOcInitStr->OCIdleState << (TIM_CR2_OIS3_Pos - TIM_CR2_OIS1_Pos)) | \
              (TimOcInitStr->OCNIdleState << (TIM_CR2_OIS3N_Pos - TIM_CR2_OIS1_Pos))));

  /* Write to TIMx CR2 */
  MS32_TIM_WriteReg(TIMx, CR2, tmpcr2);

  /* Write to TIMx CCMR2 */
  MS32_TIM_WriteReg(TIMx, CCMR2, tmpccmr2);

  /* Set the Capture Compare Register value */
  MS32_TIM_OC_SetCompareCH3(TIMx, TimOcInitStr->CompareValue);

  /* Write to TIMx CCER */
  MS32_TIM_WriteReg(TIMx, CCER, tmpccer);

  return SUCCESS;
}

/**
  * @brief  Configure the TIMx output channel 4.
  * @param  TIMx Timer Instance
  * @param  TimOcInitStr pointer to the the TIMx output channel 4 configuration data structure
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: TIMx registers are de-initialized
  *          - ERROR: not applicable
  */
static ErrorStatus OC4Config(TIM_TypeDef *TIMx, MS32_TIM_OC_InitTypeDef *TimOcInitStr) {
  uint32_t tmpccmr2;
  uint32_t tmpccer;
  uint32_t tmpcr2;

  /* Disable the Channel 4: Reset the CC4E Bit */
  CLEAR_BIT(TIMx->CCER, TIM_CCER_CC4E);

  /* Get the TIMx CCER register value */
  tmpccer = MS32_TIM_ReadReg(TIMx, CCER);

  /* Get the TIMx CR2 register value */
  tmpcr2 =  MS32_TIM_ReadReg(TIMx, CR2);

  /* Get the TIMx CCMR2 register value */
  tmpccmr2 = MS32_TIM_ReadReg(TIMx, CCMR2);

  /* Reset Capture/Compare selection Bits */
  CLEAR_BIT(tmpccmr2, TIM_CCMR2_CC4S);

  /* Select the Output Compare Mode */
  MODIFY_REG(tmpccmr2, TIM_CCMR2_OC4M, TimOcInitStr->OCMode << (TIM_CCMR2_OC4M_Pos - TIM_CCMR2_OC3M_Pos));

  /* Set the Output Compare Polarity */
  MODIFY_REG(tmpccer, 
             (TIM_CCER_CC4P | TIM_CCER_CC4E | TIM_CCER_CC4NP), \
             ((TimOcInitStr->OCPolarity << (TIM_CCER_CC4P_Pos - TIM_CCER_CC1P_Pos)) | \
              (TimOcInitStr->OCState << (TIM_CCER_CC4E_Pos - TIM_CCER_CC1E_Pos)) | \
              (TimOcInitStr->OCNPolarity << (TIM_CCER_CC4NP_Pos - TIM_CCER_CC1P_Pos))));

  /* Set the Output Idle state and the complementary output Idle state */
  MODIFY_REG(tmpcr2, \
             TIM_CR2_OIS4, \
             (TimOcInitStr->OCIdleState << (TIM_CR2_OIS4_Pos - TIM_CR2_OIS1_Pos)));

  /* Write to TIMx CR2 */
  MS32_TIM_WriteReg(TIMx, CR2, tmpcr2);

  /* Write to TIMx CCMR2 */
  MS32_TIM_WriteReg(TIMx, CCMR2, tmpccmr2);

  /* Set the Capture Compare Register value */
  MS32_TIM_OC_SetCompareCH4(TIMx, TimOcInitStr->CompareValue);

  /* Write to TIMx CCER */
  MS32_TIM_WriteReg(TIMx, CCER, tmpccer);

  return SUCCESS;
}


/**
  * @brief  Configure the TIMx input channel 1.
  * @param  TIMx Timer Instance
  * @param  TimIcInitStr pointer to the the TIMx input channel 1 configuration data structure
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: TIMx registers are de-initialized
  *          - ERROR: not applicable
  */
static ErrorStatus IC1Config(TIM_TypeDef *TIMx, MS32_TIM_IC_InitTypeDef *TimIcInitStr) {
  /* Disable the Channel 1: Reset the CC1E Bit */
  TIMx->CCER &= (uint32_t)~TIM_CCER_CC1E;

  /* Select the Input and set the filter and the prescaler value */
  MODIFY_REG(TIMx->CCMR1,
             (TIM_CCMR1_CC1S | TIM_CCMR1_IC1F | TIM_CCMR1_IC1PSC),
             (TimIcInitStr->ICActiveInput | TimIcInitStr->ICFilter | TimIcInitStr->ICPrescaler) >> 16U);

  /* Select the Polarity and set the CC1E Bit */
  MODIFY_REG(TIMx->CCER,
             (TIM_CCER_CC1P | TIM_CCER_CC1NP),
             (TimIcInitStr->ICPolarity | TIM_CCER_CC1E));

  return SUCCESS;
}

/**
  * @brief  Configure the TIMx input channel 2.
  * @param  TIMx Timer Instance
  * @param  TimIcInitStr pointer to the the TIMx input channel 2 configuration data structure
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: TIMx registers are de-initialized
  *          - ERROR: not applicable
  */
static ErrorStatus IC2Config(TIM_TypeDef *TIMx, MS32_TIM_IC_InitTypeDef *TimIcInitStr) {
  /* Disable the Channel 2: Reset the CC2E Bit */
  TIMx->CCER &= (uint32_t)~TIM_CCER_CC2E;

  /* Select the Input and set the filter and the prescaler value */
  MODIFY_REG(TIMx->CCMR1,
             (TIM_CCMR1_CC2S | TIM_CCMR1_IC2F | TIM_CCMR1_IC2PSC),
             (TimIcInitStr->ICActiveInput | TimIcInitStr->ICFilter | TimIcInitStr->ICPrescaler) >> 8U);

  /* Select the Polarity and set the CC2E Bit */
  MODIFY_REG(TIMx->CCER,
             (TIM_CCER_CC2P | TIM_CCER_CC2NP),
             ((TimIcInitStr->ICPolarity << 4U) | TIM_CCER_CC2E));

  return SUCCESS;
}

/**
  * @brief  Configure the TIMx input channel 3.
  * @param  TIMx Timer Instance
  * @param  TimIcInitStr pointer to the the TIMx input channel 3 configuration data structure
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: TIMx registers are de-initialized
  *          - ERROR: not applicable
  */
static ErrorStatus IC3Config(TIM_TypeDef *TIMx, MS32_TIM_IC_InitTypeDef *TimIcInitStr) {
  /* Disable the Channel 3: Reset the CC3E Bit */
  TIMx->CCER &= (uint32_t)~TIM_CCER_CC3E;

  /* Select the Input and set the filter and the prescaler value */
  MODIFY_REG(TIMx->CCMR2,
             (TIM_CCMR2_CC3S | TIM_CCMR2_IC3F | TIM_CCMR2_IC3PSC),
             (TimIcInitStr->ICActiveInput | TimIcInitStr->ICFilter | TimIcInitStr->ICPrescaler) >> 16U);

  /* Select the Polarity and set the CC3E Bit */
  MODIFY_REG(TIMx->CCER,
             (TIM_CCER_CC3P | TIM_CCER_CC3NP),
             ((TimIcInitStr->ICPolarity << 8U) | TIM_CCER_CC3E));

  return SUCCESS;
}

/**
  * @brief  Configure the TIMx input channel 4.
  * @param  TIMx Timer Instance
  * @param  TimIcInitStr pointer to the the TIMx input channel 4 configuration data structure
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: TIMx registers are de-initialized
  *          - ERROR: not applicable
  */
static ErrorStatus IC4Config(TIM_TypeDef *TIMx, MS32_TIM_IC_InitTypeDef *TimIcInitStr) {
  /* Disable the Channel 4: Reset the CC4E Bit */
  TIMx->CCER &= (uint32_t)~TIM_CCER_CC4E;

  /* Select the Input and set the filter and the prescaler value */
  MODIFY_REG(TIMx->CCMR2,
             (TIM_CCMR2_CC4S | TIM_CCMR2_IC4F | TIM_CCMR2_IC4PSC),
             (TimIcInitStr->ICActiveInput | TimIcInitStr->ICFilter | TimIcInitStr->ICPrescaler) >> 8U);

  /* Select the Polarity and set the CC2E Bit */
  MODIFY_REG(TIMx->CCER,
             (TIM_CCER_CC4P | TIM_CCER_CC4NP),
             ((TimIcInitStr->ICPolarity << 12U) | TIM_CCER_CC4E));

  return SUCCESS;
}

/******************************** END OF FILE *********************************/
