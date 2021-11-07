/* Includes ------------------------------------------------------------------*/
#include "ms32f0xx_bus.h"
#include "ms32f0xx_rcc.h"
#include "ms32f0xx_rtc.h"
#include "ms32f0xx_cortex.h"


/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @addtogroup RTC_Private_Constants
  * @{
  */
/* Default values used for prescaler */
#define RTC_ASYNCH_PRESC_DEFAULT     0x0000007FU
#define RTC_SYNCH_PRESC_DEFAULT      0x000000FFU

/* Values used for timeout */
#define RTC_INITMODE_TIMEOUT         1000U /* 1s when tick set to 1ms */
#define RTC_SYNCHRO_TIMEOUT          1000U /* 1s when tick set to 1ms */


/* Private macros ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @addtogroup RTC_EF_Init
  * @{
  */

/**
  * @brief  Initializes the RTC registers to their default reset values.
  * @note   This function doesn't reset the RTC Clock source and RTC Backup Data
  *         registers.
  * @param  RtcClock RTC clock select and backup access
  *            @arg @ref MS32_RTC_CLKSOURCE_NONE       No clock used as RTC clock
  *            @arg @ref MS32_RTC_CLKSOURCE_LSE        LSE oscillator clock used as RTC clock
  *            @arg @ref MS32_RTC_CLKSOURCE_LSI        LSI oscillator clock used as RTC clock
  *            @arg @ref MS32_RTC_CLKSOURCE_HSE_DIV32  HSE oscillator clock divided by 32 used as RTC clock
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RTC clock are initialized
  *          - ERROR: no application
  */
ErrorStatus MS32_RTC_ClockInit(uint32_t RtcClock) {
  __IO uint8_t pwr_clk_en_bk;

  pwr_clk_en_bk = MS32_APB1_GRP1_IsEnabledClock(MS32_APB1_GRP1_PERIPH_PWR);
  MS32_APB1_GRP1_EnableClock(MS32_APB1_GRP1_PERIPH_PWR);
  MS32_PWR_EnableBkUpAccess();
  MS32_RCC_SetRTCClockSource(RtcClock);
  MS32_RCC_EnableRTC();
  if (!pwr_clk_en_bk) {
    MS32_APB1_GRP1_DisableClock(MS32_APB1_GRP1_PERIPH_PWR);
  }

  return SUCCESS;
}


/**
  * @brief  De-Initializes the RTC registers to their default reset values.
  * @note   This function doesn't reset the RTC Clock source and RTC Backup Data
  *         registers.
  * @param  None
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RTC registers are de-initialized
  *          - ERROR: RTC registers are not de-initialized
  */
ErrorStatus MS32_RTC_DeInit(RTC_TypeDef *RTCx) {
  ErrorStatus  status = ERROR;

  /* Disable the write protection for RTC registers */
  MS32_RTC_DisableWriteProtection(RTCx);

  /* Set Initialization mode */
  if (MS32_RTC_EnterInitMode(RTCx) != ERROR) {
    /* Reset TR, DR and CR registers */
    MS32_RTC_WriteReg(RTCx, TR,       0x00000000U);
    MS32_RTC_WriteReg(RTCx, DR, (RTC_DR_WDU_0 | RTC_DR_MU_0 | RTC_DR_DU_0));
    /* Reset All CR bits except CR[2:0] */
    MS32_RTC_WriteReg(RTCx, PRER, (RTC_PRER_PREDIV_A | RTC_SYNCH_PRESC_DEFAULT));
    MS32_RTC_WriteReg(RTCx, ALRMAR,   0x00000000U);
    MS32_RTC_WriteReg(RTCx, SHIFTR,   0x00000000U);
    MS32_RTC_WriteReg(RTCx, CALR,     0x00000000U);
    MS32_RTC_WriteReg(RTCx, ALRMASSR, 0x00000000U);

    /* Reset ISR register and exit initialization mode */
    MS32_RTC_WriteReg(RTCx, ISR,      0x00000000U);

    /* Reset Tamper and alternate functions configuration register */
    MS32_RTC_WriteReg(RTCx, TAFCR, 0x00000000U);

    /* Wait till the RTC RSF flag is set */
    status = MS32_RTC_WaitForSynchro(RTCx);
  }

  /* Enable the write protection for RTC registers */
  MS32_RTC_EnableWriteProtection(RTCx);

  return status;
}

/**
  * @brief  Set each @ref MS32_RTC_InitTypeDef field to default value.
  * @param  RtcInitStr pointer to a @ref MS32_RTC_InitTypeDef structure which will be initialized.
  * @retval None
  */
void MS32_RTC_StructInit(MS32_RTC_InitTypeDef *RtcInitStr) {
  /* Set RtcInitStr fields to default values */
  RtcInitStr->HourFormat      = MS32_RTC_HOURFORMAT_24HOUR;
  RtcInitStr->AsynchPrescaler = RTC_ASYNCH_PRESC_DEFAULT;
  RtcInitStr->SynchPrescaler  = RTC_SYNCH_PRESC_DEFAULT;
}

/**
  * @brief  Initializes the RTC registers according to the specified parameters
  *         in RtcInitStr.
  * @param  RTCx RTC Instance
  * @param  RtcInitStr pointer to a @ref MS32_RTC_InitTypeDef structure that contains
  *         the configuration information for the RTC peripheral.
  * @note   The RTC Prescaler register is write protected and can be written in
  *         initialization mode only.
  * @param  RefInEn This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @param  CoeFunc This parameter can be one of the following values:
  *         @arg @ref MS32_RTC_CALIB_OUTPUT_NONE  
  *         @arg @ref MS32_RTC_CALIB_OUTPUT_1HZ   
  *         @arg @ref MS32_RTC_CALIB_OUTPUT_512HZ 
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RTC registers are initialized
  *          - ERROR: RTC registers are not initialized
  */
ErrorStatus MS32_RTC_Init(RTC_TypeDef *RTCx, MS32_RTC_InitTypeDef *RtcInitStr, uint32_t RefInEn, uint32_t CoeFunc) {
  ErrorStatus status = ERROR;

  /* Disable the write protection for RTC registers */
  MS32_RTC_DisableWriteProtection(RTCx);

  /* Set Initialization mode */
  if (MS32_RTC_EnterInitMode(RTCx) != ERROR) {
    /* Set Hour Format */
    MS32_RTC_SetHourFormat(RTCx, RtcInitStr->HourFormat);

    /* Set Calibration output frequency */
    MS32_RTC_CAL_SetOutputFreq(RTCx, CoeFunc);

    /* Configure Synchronous and Asynchronous prescaler factor */
    if (RefInEn == ENABLE) {
      MS32_RTC_EnableRefClock(RTCx);
      MS32_RTC_SetSynchPrescaler(RTCx, 0x00FF);
    } else {
      MS32_RTC_DisableRefClock(RTCx);
      MS32_RTC_SetSynchPrescaler(RTCx, RtcInitStr->SynchPrescaler);
    }

    /* Configure Synchronous and Asynchronous prescaler factor */
    MS32_RTC_SetAsynchPrescaler(RTCx, RtcInitStr->AsynchPrescaler);

    /* Exit Initialization mode */
    MS32_RTC_DisableInitMode(RTCx);

    status = SUCCESS;
  }
  /* Enable the write protection for RTC registers */
  MS32_RTC_EnableWriteProtection(RTCx);

  return status;
}

/**
  * @brief  Initializes the RTC interrupt according to the specified parameters.
  * @param  RTCx RTC Instance
  * @param  InterruptFunc  contains the configuration information for the RTC interrupt.
  *         This parameter can be one or more of the following values:
  *         @arg @ref MS32_RTC_CR_TSIE   
  *         @arg @ref MS32_RTC_CR_ALRAIE   
  *         @arg @ref MS32_RTC_TAFCR_TAMPIE
  * @param  Priority  the interrupt priority 
  *         This parameter can be a value of 0x0~0x3
  * @retval None
  */
void MS32_RTC_ITConfig(RTC_TypeDef *RTCx, uint32_t InterruptFunc, uint32_t Priority) {
  /*-------------------------------- ALL Interrrupt --------------------------*/
  CLEAR_BIT(RTCx->ISR, MS32_RTC_ISR_ALLINTF);
  MODIFY_REG(RTCx->TAFCR, RTC_TAFCR_TAMPIE, (InterruptFunc & (~(RTC_CR_TSIE | RTC_CR_ALRAIE))));
  /* Disable the write protection for RTC registers */
  MS32_RTC_DisableWriteProtection(RTCx);
  MODIFY_REG(RTCx->CR, (RTC_CR_TSIE | RTC_CR_ALRAIE), (InterruptFunc & (~RTC_TAFCR_TAMPIE)));
  /* Enable the write protection for RTC registers */
  MS32_RTC_EnableWriteProtection(RTCx);

  /*----------------------------- NVIC configuration -------------------------*/
  if (MS32_RTC_IsEnabledIT_TS(RTCx) || MS32_RTC_IsEnabledIT_ALRA(RTCx) || MS32_RTC_IsEnabledIT_TAMP(RTCx)) {
    NVIC_EnableIRQ(RTC_IRQn);
    NVIC_SetPriority(RTC_IRQn, Priority);
  } else {
    NVIC_DisableIRQ(RTC_IRQn);
  }
}

/**
  * @brief  Set the RTC current time.
  * @param  RTCx RTC Instance
  * @param  RtcFormat This parameter can be one of the following values:
  *         @arg @ref MS32_RTC_FORMAT_BIN
  *         @arg @ref MS32_RTC_FORMAT_BCD
  * @param  RtcTimeStr pointer to a RTC_TimeTypeDef structure that contains
  *                        the time configuration information for the RTC.
  * @param  ShadowBypassEn This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RTC Time register is configured
  *          - ERROR: RTC Time register is not configured
  */
ErrorStatus MS32_RTC_SetTime(RTC_TypeDef *RTCx, uint32_t RtcFormat, MS32_RTC_TimeTypeDef *RtcTimeStr, uint32_t ShadowBypassEn) {
  ErrorStatus status = ERROR;

  if (MS32_RTC_GetHourFormat(RTCx) != MS32_RTC_HOURFORMAT_24HOUR) {
    RtcTimeStr->TimeFormat = 0x00U;
  }

  /* Disable the write protection for RTC registers */
  MS32_RTC_DisableWriteProtection(RTCx);

  /* Set Initialization mode */
  if (MS32_RTC_EnterInitMode(RTCx) != ERROR) {
    /* Check the input parameters format */
    if (RtcFormat != MS32_RTC_FORMAT_BIN) {
      MS32_RTC_TIME_Config(RTCx, RtcTimeStr->TimeFormat, RtcTimeStr->Hours,
                         RtcTimeStr->Minutes, RtcTimeStr->Seconds);
    } else {
      MS32_RTC_TIME_Config(RTCx, RtcTimeStr->TimeFormat, __MS32_RTC_CONVERT_BIN2BCD(RtcTimeStr->Hours),
                         __MS32_RTC_CONVERT_BIN2BCD(RtcTimeStr->Minutes),
                         __MS32_RTC_CONVERT_BIN2BCD(RtcTimeStr->Seconds));
    }

    /* Exit Initialization mode */
    MS32_RTC_DisableInitMode(RTC);

    /* If  RTC_CR_BYPSHAD bit = 0, wait for synchro else this check is not needed */
    if (ShadowBypassEn == ENABLE) {
      MS32_RTC_EnableShadowRegBypass(RTCx);
      status = SUCCESS;
    } else {
      MS32_RTC_DisableShadowRegBypass(RTCx);
      status = MS32_RTC_WaitForSynchro(RTCx);
    }
  }
  /* Enable the write protection for RTC registers */
  MS32_RTC_EnableWriteProtection(RTCx);

  return status;
}

/**
  * @brief  Get the RTC current time.
  * @param  RTCx RTC Instance
  * @param  RtcTimeStr pointer to a RTC_TimeTypeDef structure that contains
  *                        the time configuration information for the RTC.
  * @retval None
  */
void MS32_RTC_GetTime(RTC_TypeDef *RTCx, MS32_RTC_TimeTypeDef *RtcTimeStr) {
  RtcTimeStr->TimeFormat = MS32_RTC_TIME_GetFormat(RTCx);
  RtcTimeStr->Hours      = __MS32_RTC_CONVERT_BCD2BIN(MS32_RTC_TIME_GetHour(RTCx));
  RtcTimeStr->Minutes    = __MS32_RTC_CONVERT_BCD2BIN(MS32_RTC_TIME_GetMinute(RTCx));
  RtcTimeStr->Seconds    = __MS32_RTC_CONVERT_BCD2BIN(MS32_RTC_TIME_GetSecond(RTCx));
}

/**
  * @brief  Set the RTC current date.
  * @param  RTCx RTC Instance
  * @param  RtcFormat This parameter can be one of the following values:
  *         @arg @ref MS32_RTC_FORMAT_BIN
  *         @arg @ref MS32_RTC_FORMAT_BCD
  * @param  RtcDateStr pointer to a RTC_DateTypeDef structure that contains
  *                         the date configuration information for the RTC.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RTC Day register is configured
  *          - ERROR: RTC Day register is not configured
  */
ErrorStatus MS32_RTC_DATE_Init(RTC_TypeDef *RTCx, uint32_t RtcFormat, MS32_RTC_DateTypeDef *RtcDateStr) {
  ErrorStatus status = ERROR;

  if ((RtcFormat == MS32_RTC_FORMAT_BIN) && ((RtcDateStr->Month & 0x10U) == 0x10U)) {
    RtcDateStr->Month = (RtcDateStr->Month & (uint32_t)~(0x10U)) + 0x0AU;
  }

  /* Disable the write protection for RTC registers */
  MS32_RTC_DisableWriteProtection(RTCx);

  /* Set Initialization mode */
  if (MS32_RTC_EnterInitMode(RTCx) != ERROR) {
    /* Check the input parameters format */
    if (RtcFormat != MS32_RTC_FORMAT_BIN) {
      MS32_RTC_DATE_Config(RTCx, RtcDateStr->WeekDay, RtcDateStr->Day, RtcDateStr->Month, RtcDateStr->Year);
    } else {
      MS32_RTC_DATE_Config(RTCx, RtcDateStr->WeekDay, __MS32_RTC_CONVERT_BIN2BCD(RtcDateStr->Day),
                         __MS32_RTC_CONVERT_BIN2BCD(RtcDateStr->Month), __MS32_RTC_CONVERT_BIN2BCD(RtcDateStr->Year));
    }

    /* Exit Initialization mode */
    MS32_RTC_DisableInitMode(RTC);

    /* If  RTC_CR_BYPSHAD bit = 0, wait for synchro else this check is not needed */
    if (MS32_RTC_IsShadowRegBypassEnabled(RTCx) == 0U) {
      status = MS32_RTC_WaitForSynchro(RTCx);
    } else {
      status = SUCCESS;
    }
  }
  /* Enable the write protection for RTC registers */
  MS32_RTC_EnableWriteProtection(RTCx);

  return status;
}

/**
  * @brief  Get the RTC current date.
  * @param  RTCx RTC Instance
  * @param  RtcDateStr pointer to a RTC_DateTypeDef structure that contains
  *                         the date configuration information for the RTC.
  * @retval None
  */
void MS32_RTC_DATE_StructInit(RTC_TypeDef *RTCx, MS32_RTC_DateTypeDef *RtcDateStr) {
  RtcDateStr->WeekDay = MS32_RTC_DATE_GetWeekDay(RTCx);
  RtcDateStr->Day     = __MS32_RTC_CONVERT_BCD2BIN(MS32_RTC_DATE_GetDay(RTCx));
  RtcDateStr->Month   = __MS32_RTC_CONVERT_BCD2BIN(MS32_RTC_DATE_GetMonth(RTCx));
  RtcDateStr->Year    = __MS32_RTC_CONVERT_BCD2BIN(MS32_RTC_DATE_GetYear(RTCx));
}

/**
  * @brief  Set the RTC Alarm A.
  * @note   The Alarm register can only be written when the corresponding Alarm
  *         is disabled (Use @ref MS32_RTC_ALARM_Disable function).
  * @param  RTCx RTC Instance
  * @param  RtcFormat This parameter can be one of the following values:
  *         @arg @ref MS32_RTC_FORMAT_BIN
  *         @arg @ref MS32_RTC_FORMAT_BCD
  * @param  RtcAlarmStr pointer to a @ref MS32_RTC_AlarmTypeDef structure that
  *                         contains the alarm configuration parameters.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: ALARMA registers are configured
  *          - ERROR: ALARMA registers are not configured
  */
ErrorStatus MS32_RTC_SetAlarm(RTC_TypeDef *RTCx, uint32_t RtcFormat, MS32_RTC_AlarmTypeDef *RtcAlarmStr) {
  if (MS32_RTC_GetHourFormat(RTCx) == MS32_RTC_HOURFORMAT_24HOUR) {
    RtcAlarmStr->AlarmTime.TimeFormat = 0x00U;
  }

  /* Disable the write protection for RTC registers */
  MS32_RTC_DisableWriteProtection(RTCx);

  /* Select weekday selection */
  if (RtcAlarmStr->AlarmDateWeekDaySel == MS32_RTC_ALARM_DATEWEEKDAYSEL_DATE) {
    /* Set the date for ALARM */
    MS32_RTC_ALARM_DisableWeekday(RTCx);
    if (RtcFormat != MS32_RTC_FORMAT_BIN) {
      MS32_RTC_ALARM_SetDay(RTCx, RtcAlarmStr->AlarmDateWeekDay);
    } else {
      MS32_RTC_ALARM_SetDay(RTCx, __MS32_RTC_CONVERT_BIN2BCD(RtcAlarmStr->AlarmDateWeekDay));
    }
  } else {
    /* Set the week day for ALARM */
    MS32_RTC_ALARM_EnableWeekday(RTCx);
    MS32_RTC_ALARM_SetWeekDay(RTCx, RtcAlarmStr->AlarmDateWeekDay);
  }

  /* Configure the Alarm register */
  if (RtcFormat != MS32_RTC_FORMAT_BIN) {
    MS32_RTC_ALARM_ConfigTime(RTCx, RtcAlarmStr->AlarmTime.TimeFormat, RtcAlarmStr->AlarmTime.Hours,
                           RtcAlarmStr->AlarmTime.Minutes, RtcAlarmStr->AlarmTime.Seconds);
  } else {
    MS32_RTC_ALARM_ConfigTime(RTCx, RtcAlarmStr->AlarmTime.TimeFormat,
                           __MS32_RTC_CONVERT_BIN2BCD(RtcAlarmStr->AlarmTime.Hours),
                           __MS32_RTC_CONVERT_BIN2BCD(RtcAlarmStr->AlarmTime.Minutes),
                           __MS32_RTC_CONVERT_BIN2BCD(RtcAlarmStr->AlarmTime.Seconds));
  }
  /* Set ALARM mask */
  MS32_RTC_ALARM_SetMask(RTCx, RtcAlarmStr->AlarmMask);

  /* Enable the write protection for RTC registers */
  MS32_RTC_EnableWriteProtection(RTCx);

  return SUCCESS;
}

/**
  * @brief  Get the RTC Alarm A.
  * @param  RTCx RTC Instance
  * @param  RtcAlarmStr pointer to a @ref MS32_RTC_AlarmTypeDef structure that
  *                         contains the alarm configuration parameters.
  * @retval None
  */
void MS32_RTC_GetAlarm(RTC_TypeDef *RTCx, MS32_RTC_AlarmTypeDef *RtcAlarmStr) {
  /* Get Alarm Time */
  RtcAlarmStr->AlarmTime.TimeFormat = MS32_RTC_ALARM_GetTimeFormat(RTCx);
  RtcAlarmStr->AlarmTime.Hours      = __MS32_RTC_CONVERT_BCD2BIN(MS32_RTC_ALARM_GetHour(RTCx));
  RtcAlarmStr->AlarmTime.Minutes    = __MS32_RTC_CONVERT_BCD2BIN(MS32_RTC_ALARM_GetMinute(RTCx));
  RtcAlarmStr->AlarmTime.Seconds    = __MS32_RTC_CONVERT_BCD2BIN(MS32_RTC_ALARM_GetSecond(RTCx));

  /* Get Alarm Day or Week */
  RtcAlarmStr->AlarmDateWeekDaySel = READ_BIT(RTC->ALRMAR, RTC_ALRMAR_WDSEL);
  if (RtcAlarmStr->AlarmDateWeekDaySel == MS32_RTC_ALARM_DATEWEEKDAYSEL_DATE) {    
    RtcAlarmStr->AlarmDateWeekDay = __MS32_RTC_CONVERT_BCD2BIN(MS32_RTC_ALARM_GetDay(RTCx));
  } else {
    RtcAlarmStr->AlarmDateWeekDay = __MS32_RTC_CONVERT_BCD2BIN(MS32_RTC_ALARM_GetWeekDay(RTCx));
  }

  /* Get Alarm Masks */
  RtcAlarmStr->AlarmMask = MS32_RTC_ALARM_GetMask(RTCx);
}

/**
  * @brief  Config the RTC Alarm A.
  * @param  RTCx RTC Instance
  * @param  AlarmOutEn This parameter can be one of the following values:
  *         @arg @ref MS32_RTC_ALARMOUT_DISABLE
  *         @arg @ref MS32_RTC_ALARMOUT_ALMA   
  * @param  AlarmOutPol This parameter can be one of the following values:
  *         @arg @ref MS32_RTC_OUTPUTPOLARITY_PIN_HIGH
  *         @arg @ref MS32_RTC_OUTPUTPOLARITY_PIN_LOW 
  * @param  AlarmEn This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @retval None
  */
void MS32_RTC_AlarmConfig(RTC_TypeDef *RTCx, uint32_t AlarmOutEn, uint32_t AlarmOutPol, FunctionalState AlarmEn) {
  /* Disable the write protection for RTC registers */
  MS32_RTC_DisableWriteProtection(RTCx);

  MODIFY_REG(RTCx->CR, (RTC_CR_OSEL | RTC_CR_POL | RTC_CR_ALRAE), (AlarmOutEn | AlarmOutPol)); 

  if (AlarmEn == ENABLE) {
    MS32_RTC_ALARM_Enable(RTCx);
  }

  /* Enable the write protection for RTC registers */
  MS32_RTC_EnableWriteProtection(RTCx);
}

/**
  * @brief  Config the RTC time stamp.
  * @param  RTCx RTC Instance
  * @param  TimStampEn This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE 
  * @param  TimStampEdge This parameter can be one of the following values:
  *         @arg @ref MS32_RTC_TIMESTAMP_EDGE_RISING 
  *         @arg @ref MS32_RTC_TIMESTAMP_EDGE_FALLING
  * @retval None
  */
void MS32_RTC_TimStampConfig(RTC_TypeDef *RTCx, uint32_t TimStampEn, uint32_t TimStampEdge) {
  /* Disable the write protection for RTC registers */
  MS32_RTC_DisableWriteProtection(RTCx);

  MODIFY_REG(RTCx->CR, (RTC_CR_TSE | RTC_CR_TSEDGE), TimStampEdge); 

  if (TimStampEn == ENABLE) {
    MS32_RTC_TS_Enable(RTCx);
  }

  /* Enable the write protection for RTC registers */
  MS32_RTC_EnableWriteProtection(RTCx);
}

/**
  * @brief  Get the RTC Time Stamp
  * @param  RTCx RTC Instance
  * @param  RtcTimStampStr pointer to a @ref MS32_RTC_TimStampTypeDef structure that
  *                         contains the time stamp configuration parameters.
  * @retval None
  */
void MS32_RTC_GetTimStamp(RTC_TypeDef *RTCx, MS32_RTC_TimStampTypeDef *RtcTimStampStr) {
  /* Get Alarm Time */
  RtcTimStampStr->TimeStamp.TimeFormat = MS32_RTC_TS_GetTimeFormat(RTCx);
  RtcTimStampStr->TimeStamp.Hours      = __MS32_RTC_CONVERT_BCD2BIN(MS32_RTC_TS_GetHour(RTCx));
  RtcTimStampStr->TimeStamp.Minutes    = __MS32_RTC_CONVERT_BCD2BIN(MS32_RTC_TS_GetMinute(RTCx));
  RtcTimStampStr->TimeStamp.Seconds    = __MS32_RTC_CONVERT_BCD2BIN(MS32_RTC_TS_GetSecond(RTCx));
  RtcTimStampStr->WeekDay              = __MS32_RTC_CONVERT_BCD2BIN(MS32_RTC_TS_GetWeekDay(RTCx));
  RtcTimStampStr->Month                = __MS32_RTC_CONVERT_BCD2BIN(MS32_RTC_TS_GetMonth(RTCx));
  RtcTimStampStr->Day                  = __MS32_RTC_CONVERT_BCD2BIN(MS32_RTC_TS_GetDay(RTCx));
}

/**
  * @brief  Set the RTC Tamper
  * @param  RTCx RTC Instance
  * @param  RtcTampStr pointer to a @ref MS32_RTC_TampTypeDef structure that
  *                         contains the tamper configuration parameters.
  * @retval None
  */
void MS32_RTC_SetTamp(RTC_TypeDef *RTCx, MS32_RTC_TampTypeDef *RtcTampStr) {
  uint32_t reg_val;

  reg_val = RtcTampStr->Pullup  | RtcTampStr->Duration | RtcTampStr->Filter  | RtcTampStr->Freq | RtcTampStr->TampTs |\
            RtcTampStr->Tamp1En | RtcTampStr->Tamp1Trg | RtcTampStr->Tamp2En | RtcTampStr->Tamp1Trg;

  MODIFY_REG(RTCx->TAFCR, (RTC_CR_TSE | RTC_CR_TSEDGE), reg_val);
}

/**
  * @brief  Get the RTC flags according to the internal RTC SR registers.
  * @param  RTCx RTC Instance
  * @param  Flags specifies the function flags.
  *          This parameter can be one or more of the following values:
  *            @arg @ref MS32_RTC_ISR_RECALPF
  *            @arg @ref MS32_RTC_ISR_TAMP2F 
  *            @arg @ref MS32_RTC_ISR_TAMP1F 
  *            @arg @ref MS32_RTC_ISR_TSOVF  
  *            @arg @ref MS32_RTC_ISR_TSF    
  *            @arg @ref MS32_RTC_ISR_ALRAF  
  *            @arg @ref MS32_RTC_ISR_INITF  
  *            @arg @ref MS32_RTC_ISR_RSF    
  *            @arg @ref MS32_RTC_ISR_INITS  
  *            @arg @ref MS32_RTC_ISR_SHPF   
  *            @arg @ref MS32_RTC_ISR_ALRAWF 
  * @note   Clear flags After getting the interrupt flags equal to set. 
  * @retval A FlagStatus enumeration value:
  *          - SET:   flag set(equal to "1")
  *          - RESET: flag no set(equal to "0")
  */
FlagStatus MS32_RTC_GetStatusFlag(RTC_TypeDef *RTCx, uint32_t Flags) {
  FlagStatus flags;

  if (READ_BIT(RTCx->ISR, Flags)) {
    flags = SET;
    CLEAR_BIT(RTCx->ISR, Flags);
  } else {
    flags = RESET;
  }

  return flags;
}

/**
  * @brief  Add/Sub the RTC one hour.
  * @param  RTCx RTC Instance
  * @param  Effect specifies the function add/dec one hour.
  *          This parameter can be one or more of the following values:
  *            @arg @ref MS32_RTC_ADD_ONE_HOUR
  *            @arg @ref MS32_RTC_SUB_ONE_HOUR 
  * @retval None
  */
void MS32_RTC_ChangeOneHour(RTC_TypeDef *RTCx, uint32_t Effect) {
  /* Disable the write protection for RTC registers */
  MS32_RTC_DisableWriteProtection(RTCx);

  /* Add/Sub the RTC one hour */
  SET_BIT(RTCx->CR, Effect); 

  /* Enable the write protection for RTC registers */
  MS32_RTC_EnableWriteProtection(RTCx);
}

/**
  * @brief  Add/Sub the RTC x second (x range from 0 to 1).
  * @param  RTCx RTC Instance
  * @param  ShiftSecond This parameter can be one of the following values:
  *         @arg @ref MS32_RTC_SHIFT_SECOND_DELAY
  *         @arg @ref MS32_RTC_SHIFT_SECOND_ADVANCE
  * @param  Fraction Number of Seconds Fractions (any value from 0 to 0x7FFF)
  * @retval None
  */
void MS32_RTC_ShiftSec(RTC_TypeDef *RTCx, uint32_t ShiftSecond, uint16_t Fraction) {
  /* Disable the write protection for RTC registers */
  MS32_RTC_DisableWriteProtection(RTCx);

  CLEAR_BIT(RTCx->ISR, RTC_ISR_SHPF);
  MS32_RTC_TIME_Synchronize(RTCx, ShiftSecond, Fraction); 

  /* Enable the write protection for RTC registers */
  MS32_RTC_EnableWriteProtection(RTCx);
}

/**
  * @brief  Set the RTC Calibration.
  * @param  RTCx RTC Instance
  * @param  InsertPulse This parameter can be one of the following values:
  *         @arg @ref MS32_RTC_CALIB_INSERTPULSE_NONE
  *         @arg @ref MS32_RTC_CALIB_INSERTPULSE_SET 
  * @param  Period This parameter can be one of the following values:
  *         @arg @ref MS32_RTC_CALIB_PERIOD_32SEC
  *         @arg @ref MS32_RTC_CALIB_PERIOD_16SEC 
  *         @arg @ref MS32_RTC_CALIB_PERIOD_8SEC 
  * @param  CalMin calibration minus (any value from 0 to 0x1FF)
  * @retval None
  */
void MS32_RTC_Cal(RTC_TypeDef *RTCx, uint32_t InsertPulse, uint32_t Period, uint16_t CalMin) {
  uint32_t reg_val;

  reg_val = InsertPulse | Period;
  if (Period == MS32_RTC_CALIB_PERIOD_8SEC) {
    reg_val |= (CalMin & 0x1FC);
  } else if (Period == MS32_RTC_CALIB_PERIOD_16SEC) {
    reg_val |= (CalMin & 0x1FE);
  } else if (Period == MS32_RTC_CALIB_PERIOD_32SEC) {
    reg_val |= CalMin;
  } else {
    reg_val = 0;
  }

  /* Disable the write protection for RTC registers */
  MS32_RTC_DisableWriteProtection(RTCx);

  /* Set the RTC Calibration */
  CLEAR_BIT(RTCx->ISR, RTC_ISR_RECALPF);
  MODIFY_REG(RTCx->CALR, (RTC_CALR_CALP | RTC_CALR_CALW8 | RTC_CALR_CALW16 | RTC_CALR_CALM), reg_val); 

  /* Enable the write protection for RTC registers */
  MS32_RTC_EnableWriteProtection(RTCx);
}

/**
  * @brief  Set the RTC pin value.
  * @param  RTCx RTC Instance
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref MS32_RTC_PIN_PC13
  *         @arg @ref MS32_RTC_PIN_PC14
  *         @arg @ref MS32_RTC_PIN_PC15
  * @param  Level This parameter can be one of the following values:
  *         @arg @ref MS32_RTC_PIN_LOW 
  *         @arg @ref MS32_RTC_PIN_HIGH 
  * @retval None
  */
void MS32_RTC_SetPin(RTC_TypeDef *RTCx, uint32_t Pin, uint32_t Level) {
  uint32_t reg_val;

  reg_val = Pin | (Pin >> (1 * Level));

  MODIFY_REG(RTCx->TAFCR, Pin | (Pin >> 1), reg_val);
}

/**
  * @brief  Enters the RTC Initialization mode.
  * @note   The RTC Initialization mode is write protected, use the
  *         @ref MS32_RTC_DisableWriteProtection before calling this function.
  * @param  RTCx RTC Instance
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RTC is in Init mode
  *          - ERROR: RTC is not in Init mode
  */
ErrorStatus MS32_RTC_EnterInitMode(RTC_TypeDef *RTCx) {
  __IO uint32_t timeout = RTC_INITMODE_TIMEOUT;
  ErrorStatus status = SUCCESS;
  uint32_t tmp = 0U;

  /* Check if the Initialization mode is set */
  if (MS32_RTC_IsActiveFlag_INIT(RTCx) == 0U) {
    /* Set the Initialization mode */
    MS32_RTC_EnableInitMode(RTCx);

    /* Wait till RTC is in INIT state and if Time out is reached exit */
    tmp = MS32_RTC_IsActiveFlag_INIT(RTCx);
    while ((timeout != 0U) && (tmp != 1U)) {
      if (MS32_SYSTICK_IsActiveCounterFlag() == 1U) {
        timeout --;
      }
      tmp = MS32_RTC_IsActiveFlag_INIT(RTCx);
      if (timeout == 0U) {
        status = ERROR;
      }
    }
  }

  return status;
}

/**
  * @brief  Exit the RTC Initialization mode.
  * @note   When the initialization sequence is complete, the calendar restarts
  *         counting after 4 RTCCLK cycles.
  * @note   The RTC Initialization mode is write protected, use the
  *         @ref MS32_RTC_DisableWriteProtection before calling this function.
  * @param  RTCx RTC Instance
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RTC exited from in Init mode
  *          - ERROR: Not applicable
  */
ErrorStatus MS32_RTC_ExitInitMode(RTC_TypeDef *RTCx) {
  /* Disable initialization mode */
  MS32_RTC_DisableInitMode(RTCx);

  return SUCCESS;
}

/**
  * @brief  Waits until the RTC Time and Day registers (RTC_TR and RTC_DR) are
  *         synchronized with RTC APB clock.
  * @note   The RTC Resynchronization mode is write protected, use the
  *         @ref MS32_RTC_DisableWriteProtection before calling this function.
  * @note   To read the calendar through the shadow registers after Calendar
  *         initialization, calendar update or after wakeup from low power modes
  *         the software must first clear the RSF flag.
  *         The software must then wait until it is set again before reading
  *         the calendar, which means that the calendar registers have been
  *         correctly copied into the RTC_TR and RTC_DR shadow registers.
  * @param  RTCx RTC Instance
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RTC registers are synchronised
  *          - ERROR: RTC registers are not synchronised
  */
ErrorStatus MS32_RTC_WaitForSynchro(RTC_TypeDef *RTCx) {
  __IO uint32_t timeout = RTC_SYNCHRO_TIMEOUT;
  ErrorStatus status = SUCCESS;
  uint32_t tmp = 0U;

  /* Clear RSF flag */
  MS32_RTC_ClearFlag_RS(RTCx);

  /* Wait the registers to be synchronised */
  tmp = MS32_RTC_IsActiveFlag_RS(RTCx);
  while ((timeout != 0U) && (tmp != 0U)) {
    if (MS32_SYSTICK_IsActiveCounterFlag() == 1U) {
      timeout--;
    }
    tmp = MS32_RTC_IsActiveFlag_RS(RTCx);
    if (timeout == 0U) {
      status = ERROR;
    }
  }

  if (status != ERROR) {
    timeout = RTC_SYNCHRO_TIMEOUT;
    tmp = MS32_RTC_IsActiveFlag_RS(RTCx);
    while ((timeout != 0U) && (tmp != 1U)) {
      if (MS32_SYSTICK_IsActiveCounterFlag() == 1U) {
        timeout--;
      }
      tmp = MS32_RTC_IsActiveFlag_RS(RTCx);
      if (timeout == 0U) {
        status = ERROR;
      }
    }
  }

  return status;
}

/******************************** END OF FILE *********************************/
