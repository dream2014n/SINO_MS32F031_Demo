/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MS32F0XX_RTC_H
#define __MS32F0XX_RTC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ms32f0xx.h"


/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @defgroup RTC_Private_Constants RTC Private Constants
  * @{
  */
/* Masks Definition */
#define RTC_INIT_MASK                 0xFFFFFFFFU
#define RTC_RSF_MASK                  0xFFFFFF5FU

/* Write protection defines */
#define RTC_WRITE_PROTECTION_DISABLE  ((uint8_t)0xFFU)
#define RTC_WRITE_PROTECTION_ENABLE_1 ((uint8_t)0xCAU)
#define RTC_WRITE_PROTECTION_ENABLE_2 ((uint8_t)0x53U)

/* Defines used to combine date & time */
#define RTC_OFFSET_WEEKDAY            24U
#define RTC_OFFSET_DAY                16U
#define RTC_OFFSET_MONTH              8U
#define RTC_OFFSET_HOUR               16U
#define RTC_OFFSET_MINUTE             8U


/* Private macros ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/**
  * @brief  RTC Init structures definition
  */
typedef struct {
  uint32_t HourFormat;   /*!< Specifies the RTC Hours Format.
                              This parameter can be a value of @ref RTC_EC_HOURFORMAT
                              This feature can be modified afterwards using unitary function
                              @ref MS32_RTC_SetHourFormat(). */
  uint32_t AsynchPrescaler; /*!< Specifies the RTC Asynchronous Predivider value.
                              This parameter must be a number between Min_Data = 0x00 and Max_Data = 0x7F
                              This feature can be modified afterwards using unitary function
                              @ref MS32_RTC_SetAsynchPrescaler(). */
  uint32_t SynchPrescaler;  /*!< Specifies the RTC Synchronous Predivider value.
                              This parameter must be a number between Min_Data = 0x00 and Max_Data = 0x7FFF
                              This feature can be modified afterwards using unitary function
                              @ref MS32_RTC_SetSynchPrescaler(). */
} MS32_RTC_InitTypeDef;

/**
  * @brief  RTC Time structure definition
  */
typedef struct {
  uint32_t TimeFormat; /*!< Specifies the RTC AM/PM Time.
                            This parameter can be a value of @ref RTC_EC_TIME_FORMAT
                            This feature can be modified afterwards using unitary function @ref MS32_RTC_TIME_SetFormat(). */
  uint8_t Hours;       /*!< Specifies the RTC Time Hours.
                            This parameter must be a number between Min_Data = 0 and Max_Data = 12 if the @ref MS32_RTC_TIME_FORMAT_PM is selected.
                            This parameter must be a number between Min_Data = 0 and Max_Data = 23 if the @ref MS32_RTC_TIME_FORMAT_AM_OR_24 is selected.
                            This feature can be modified afterwards using unitary function @ref MS32_RTC_TIME_SetHour(). */
  uint8_t Minutes;     /*!< Specifies the RTC Time Minutes.
                            This parameter must be a number between Min_Data = 0 and Max_Data = 59
                            This feature can be modified afterwards using unitary function @ref MS32_RTC_TIME_SetMinute(). */
  uint8_t Seconds;     /*!< Specifies the RTC Time Seconds.
                            This parameter must be a number between Min_Data = 0 and Max_Data = 59
                            This feature can be modified afterwards using unitary function @ref MS32_RTC_TIME_SetSecond(). */
} MS32_RTC_TimeTypeDef;

/**
  * @brief  RTC Date structure definition
  */
typedef struct {
  uint8_t WeekDay;  /*!< Specifies the RTC Date WeekDay.
                         This parameter can be a value of @ref RTC_EC_WEEKDAY
                         This feature can be modified afterwards using unitary function @ref MS32_RTC_DATE_SetWeekDay(). */
  uint8_t Month;    /*!< Specifies the RTC Date Month.
                         This parameter can be a value of @ref RTC_EC_MONTH
                         This feature can be modified afterwards using unitary function @ref MS32_RTC_DATE_SetMonth(). */
  uint8_t Day;      /*!< Specifies the RTC Date Day.
                         This parameter must be a number between Min_Data = 1 and Max_Data = 31
                         This feature can be modified afterwards using unitary function @ref MS32_RTC_DATE_SetDay(). */
  uint8_t Year;     /*!< Specifies the RTC Date Year.
                         This parameter must be a number between Min_Data = 0 and Max_Data = 99
                         This feature can be modified afterwards using unitary function @ref MS32_RTC_DATE_SetYear(). */
} MS32_RTC_DateTypeDef;

/**
  * @brief  RTC Alarm structure definition
  */
typedef struct {
  MS32_RTC_TimeTypeDef AlarmTime;  /*!< Specifies the RTC Alarm Time members. */
  uint32_t AlarmMask;              /*!< Specifies the RTC Alarm Masks.
                                        This parameter can be a value of @ref RTC_EC_ALARM_MASK
                                        This feature can be modified afterwards using unitary function @ref MS32_RTC_ALARM_SetMask() for ALARM A. */
  uint32_t AlarmDateWeekDaySel;    /*!< Specifies the RTC Alarm is on day or WeekDay.
                                        This parameter can be a value of @ref RTC_EC_ALARM_WEEKDAY_SELECTION
                                        This feature can be modified afterwards using unitary function @ref MS32_RTC_ALARM_EnableWeekday() or @ref MS32_RTC_ALARM_DisableWeekday() */
  uint8_t AlarmDateWeekDay;        /*!< Specifies the RTC Alarm Day/WeekDay.
                                        If AlarmDateWeekDaySel set to day, this parameter  must be a number between Min_Data = 1 and Max_Data = 31.
                                        This feature can be modified afterwards using unitary function @ref MS32_RTC_ALARM_SetDay()
                                        If AlarmDateWeekDaySel set to Weekday, this parameter can be a value of @ref RTC_EC_WEEKDAY.
                                        This feature can be modified afterwards using unitary function @ref MS32_RTC_ALARM_SetWeekDay() */
} MS32_RTC_AlarmTypeDef;

/**
  * @brief  RTC time stamp structure definition
  */
typedef struct {
  MS32_RTC_TimeTypeDef TimeStamp;  /*!< Specifies the RTC Time Stamp members. */
  uint8_t WeekDay;                 /*!< Specifies the RTC time stamp WeekDay.
                                        This parameter can be a value of @ref RTC_EC_WEEKDAY
                                        This feature can be modified afterwards using unitary function @ref MS32_RTC_TS_GetWeekDay(). */
  uint8_t Month;                   /*!< Specifies the RTC time stamp Month.
                                        This parameter can be a value of @ref RTC_EC_MONTH
                                        This feature can be modified afterwards using unitary function @ref MS32_RTC_TS_GetMonth(). */
  uint8_t Day;                     /*!< Specifies the RTC time stamp Day.
                                        This parameter must be a number between Min_Data = 1 and Max_Data = 31
                                        This feature can be modified afterwards using unitary function @ref MS32_RTC_TS_GetMonth(). */

} MS32_RTC_TimStampTypeDef;

/**
  * @brief  RTC tamper structure definition
  */
typedef struct {
  uint32_t Pullup;                 /*!< Specifies the RTC tamper pullup.
                                        This parameter can be a value of @ref RTC_EC_TAMPER_PULLUP */
  uint32_t Duration;               /*!< Specifies the RTC tamper duration.
                                        This parameter can be a value of @ref RTC_EC_TAMPER_DURATION */
  uint32_t Filter;                 /*!< Specifies the RTC tamper filter.
                                        This parameter must be a value of @ref RTC_EC_TAMPER_FILTER . */
  uint32_t Freq;                   /*!< Specifies the RTC tamper filter.
                                        This parameter must be a value of @ref RTC_EC_TAMPER_SAMPLFREQDIV . */
  uint32_t TampTs;                 /*!< Specifies the RTC tamper with timestamp.
                                        This parameter must be a value of @ref RTC_EC_TAMPER_TS . */
  uint32_t Tamp1En;                /*!< Specifies the RTC tamper1 ennable.
                                        This parameter must be a value of @ref RTC_EC_TAMPER1 . */
  uint32_t Tamp1Trg;                /*!< Specifies the RTC tamper1 trgger.
                                        This parameter must be a value of @ref RTC_EC_TAMPER1_ACTIVELEVEL . */
  uint32_t Tamp2En;                /*!< Specifies the RTC tamper2 ennable.
                                        This parameter must be a value of @ref RTC_EC_TAMPER2 . */
  uint32_t Tamp2Trg;                /*!< Specifies the RTC tamper2 trgger.
                                        This parameter must be a value of @ref RTC_EC_TAMPER2_ACTIVELEVEL . */
} MS32_RTC_TampTypeDef;


/* Exported constants --------------------------------------------------------*/
/** @defgroup RTC_CLKSOURCE  RTC clock source selection
  * @{
  */
#define MS32_RTC_CLKSOURCE_NONE              0x00000000U       /*!< No clock used as RTC clock */
#define MS32_RTC_CLKSOURCE_LSE               RCC_BDCR_RTCSEL_0 /*!< LSE oscillator clock used as RTC clock */
#define MS32_RTC_CLKSOURCE_LSI               RCC_BDCR_RTCSEL_1 /*!< LSI oscillator clock used as RTC clock */
#define MS32_RTC_CLKSOURCE_HSE_DIV32         RCC_BDCR_RTCSEL   /*!< HSE oscillator clock divided by 32 used as RTC clock */


/** @defgroup RTC_Exported_Constants RTC Exported Constants
  * @{
  */
#define MS32_RTC_FORMAT_BIN                  0x000000000U /*!< Binary data format */
#define MS32_RTC_FORMAT_BCD                  0x000000001U /*!< BCD data format */


/** @defgroup RTC_EC_ALARM_WEEKDAY_SELECTION RTC Alarm A Date WeekDay
  * @{
  */
#define MS32_RTC_ALARM_DATEWEEKDAYSEL_DATE    0x00000000U             /*!< Alarm A Date is selected */
#define MS32_RTC_ALARM_DATEWEEKDAYSEL_WEEKDAY RTC_ALRMAR_WDSEL        /*!< Alarm A WeekDay is selected */


/** @defgroup RTC_EC_GET_FLAG Get Flags Defines
  * @brief    Flags defines which can be used with MS32_RTC_ReadReg function
  * @{
  */
#define MS32_RTC_ISR_RECALPF                 RTC_ISR_RECALPF
#define MS32_RTC_ISR_TAMP2F                  RTC_ISR_TAMP2F
#define MS32_RTC_ISR_TAMP1F                  RTC_ISR_TAMP1F
#define MS32_RTC_ISR_TSOVF                   RTC_ISR_TSOVF
#define MS32_RTC_ISR_TSF                     RTC_ISR_TSF
#define MS32_RTC_ISR_ALRAF                   RTC_ISR_ALRAF
#define MS32_RTC_ISR_INITF                   RTC_ISR_INITF
#define MS32_RTC_ISR_RSF                     RTC_ISR_RSF
#define MS32_RTC_ISR_INITS                   RTC_ISR_INITS
#define MS32_RTC_ISR_SHPF                    RTC_ISR_SHPF
#define MS32_RTC_ISR_ALRAWF                  RTC_ISR_ALRAWF

#define MS32_RTC_ISR_ALLINTF                 (RTC_ISR_TAMP2F | RTC_ISR_TAMP1F | RTC_ISR_TSF | RTC_ISR_ALRAF)


/** @defgroup RTC_EC_IT IT Defines
  * @brief    IT defines which can be used with MS32_RTC_ReadReg and  MS32_RTC_WriteReg functions
  * @{
  */
#define MS32_RTC_CR_TSIE                     RTC_CR_TSIE
#define MS32_RTC_CR_WUTIE                    RTC_CR_WUTIE
#define MS32_RTC_CR_ALRAIE                   RTC_CR_ALRAIE
#define MS32_RTC_TAFCR_TAMPIE                RTC_TAFCR_TAMPIE


/** @defgroup RTC_EC_WEEKDAY  WEEK DAY
  * @{
  */
#define MS32_RTC_WEEKDAY_MONDAY              ((uint8_t)0x01U) /*!< Monday    */
#define MS32_RTC_WEEKDAY_TUESDAY             ((uint8_t)0x02U) /*!< Tuesday   */
#define MS32_RTC_WEEKDAY_WEDNESDAY           ((uint8_t)0x03U) /*!< Wednesday */
#define MS32_RTC_WEEKDAY_THURSDAY            ((uint8_t)0x04U) /*!< Thrusday  */
#define MS32_RTC_WEEKDAY_FRIDAY              ((uint8_t)0x05U) /*!< Friday    */
#define MS32_RTC_WEEKDAY_SATURDAY            ((uint8_t)0x06U) /*!< Saturday  */
#define MS32_RTC_WEEKDAY_SUNDAY              ((uint8_t)0x07U) /*!< Sunday    */


/** @defgroup RTC_EC_MONTH  MONTH
  * @{
  */
#define MS32_RTC_MONTH_JANUARY               ((uint8_t)0x01U)  /*!< January   */
#define MS32_RTC_MONTH_FEBRUARY              ((uint8_t)0x02U)  /*!< February  */
#define MS32_RTC_MONTH_MARCH                 ((uint8_t)0x03U)  /*!< March     */
#define MS32_RTC_MONTH_APRIL                 ((uint8_t)0x04U)  /*!< April     */
#define MS32_RTC_MONTH_MAY                   ((uint8_t)0x05U)  /*!< May       */
#define MS32_RTC_MONTH_JUNE                  ((uint8_t)0x06U)  /*!< June      */
#define MS32_RTC_MONTH_JULY                  ((uint8_t)0x07U)  /*!< July      */
#define MS32_RTC_MONTH_AUGUST                ((uint8_t)0x08U)  /*!< August    */
#define MS32_RTC_MONTH_SEPTEMBER             ((uint8_t)0x09U)  /*!< September */
#define MS32_RTC_MONTH_OCTOBER               ((uint8_t)0x10U)  /*!< October   */
#define MS32_RTC_MONTH_NOVEMBER              ((uint8_t)0x11U)  /*!< November  */
#define MS32_RTC_MONTH_DECEMBER              ((uint8_t)0x12U)  /*!< December  */


/** @defgroup RTC_EC_HOURFORMAT  HOUR FORMAT
  * @{
  */
#define MS32_RTC_HOURFORMAT_24HOUR           0x00000000U           /*!< 24 hour/day format */
#define MS32_RTC_HOURFORMAT_AMPM             RTC_CR_FMT            /*!< AM/PM hour format */


/** @defgroup RTC_EC_ALARMOUT  ALARM OUTPUT
  * @{
  */
#define MS32_RTC_ALARMOUT_DISABLE            0x00000000U             /*!< Output disabled */
#define MS32_RTC_ALARMOUT_ALMA               RTC_CR_OSEL_0           /*!< Alarm A output enabled */


/** @defgroup RTC_EC_ALARM_OUTPUTTYPE  ALARM OUTPUT TYPE
  * @{
  */
#define MS32_RTC_ALARM_OUTPUTTYPE_OPENDRAIN  0x00000000U           /*!< RTC_ALARM, when mapped on PC13, is open-drain output */
#define MS32_RTC_ALARM_OUTPUTTYPE_PUSHPULL   RTC_TAFCR_PC13VALUE   /*!< RTC_ALARM, when mapped on PC13, is push-pull output */


/** @defgroup RTC_EC_PIN PIN
  * @{
  */
#define MS32_RTC_PIN_PC13                    RTC_TAFCR_PC13MODE    /*!< PC13 is forced to push-pull output if all RTC alternate functions are disabled */
#define MS32_RTC_PIN_PC14                    RTC_TAFCR_PC14MODE    /*!< PC14 is forced to push-pull output if LSE is disabled */
#define MS32_RTC_PIN_PC15                    RTC_TAFCR_PC15MODE    /*!< PC15 is forced to push-pull output if LSE is disabled */


/** @defgroup RTC_EC_PIN PIN
  * @{
  */
#define MS32_RTC_PIN_LOW                     (0x00000000U)
#define MS32_RTC_PIN_HIGH                    (0x00000001U)


/** @defgroup RTC_EC_OUTPUTPOLARITY_PIN  OUTPUT POLARITY PIN
  * @{
  */
#define MS32_RTC_OUTPUTPOLARITY_PIN_HIGH     0x00000000U           /*!< Pin is high when ALRAF/ALRBF/WUTF is asserted (depending on OSEL)*/
#define MS32_RTC_OUTPUTPOLARITY_PIN_LOW      RTC_CR_POL            /*!< Pin is low when ALRAF/ALRBF/WUTF is asserted (depending on OSEL) */


/** @defgroup RTC_EC_TIME_FORMAT TIME FORMAT
  * @{
  */
#define MS32_RTC_TIME_FORMAT_AM_OR_24        0x00000000U           /*!< AM or 24-hour format */
#define MS32_RTC_TIME_FORMAT_PM              RTC_TR_PM             /*!< PM */


/** @defgroup RTC_EC_ADD_SUB_ONE_HOUR  add/sub one hour
  * @{
  */
#define MS32_RTC_ADD_ONE_HOUR                RTC_CR_ADD1H          /* Add one hour */
#define MS32_RTC_SUB_ONE_HOUR                RTC_CR_SUB1H          /* Sub one hour */


/** @defgroup RTC_EC_SHIFT_SECOND  SHIFT SECOND
  * @{
  */
#define MS32_RTC_SHIFT_SECOND_DELAY          0x00000000U           /* Delay (seconds) = SUBFS / (PREDIV_S + 1) */
#define MS32_RTC_SHIFT_SECOND_ADVANCE        RTC_SHIFTR_ADD1S      /* Advance (seconds) = (1 - (SUBFS / (PREDIV_S + 1))) */


/** @defgroup RTC_EC_ALARM_MASK  ALARMA MASK
  * @{
  */
#define MS32_RTC_ALARM_MASK_NONE              0x00000000U             /*!< No masks applied on Alarm A*/
#define MS32_RTC_ALARM_MASK_DATEWEEKDAY       RTC_ALRMAR_MSK4         /*!< Date/day do not care in Alarm A comparison */
#define MS32_RTC_ALARM_MASK_HOURS             RTC_ALRMAR_MSK3         /*!< Hours do not care in Alarm A comparison */
#define MS32_RTC_ALARM_MASK_MINUTES           RTC_ALRMAR_MSK2         /*!< Minutes do not care in Alarm A comparison */
#define MS32_RTC_ALARM_MASK_SECONDS           RTC_ALRMAR_MSK1         /*!< Seconds do not care in Alarm A comparison */
#define MS32_RTC_ALARM_MASK_ALL               (RTC_ALRMAR_MSK4 | RTC_ALRMAR_MSK3 | RTC_ALRMAR_MSK2 | RTC_ALRMAR_MSK1) /*!< Masks all */


/** @defgroup RTC_EC_ALARM_TIME_FORMAT  ALARMA TIME FORMAT
  * @{
  */
#define MS32_RTC_ALARM_TIME_FORMAT_AM         0x00000000U           /*!< AM or 24-hour format */
#define MS32_RTC_ALARM_TIME_FORMAT_PM         RTC_ALRMAR_PM         /*!< PM */


/** @defgroup RTC_EC_TIMESTAMP_EDGE  TIMESTAMP EDGE
  * @{
  */
#define MS32_RTC_TIMESTAMP_EDGE_RISING       0x00000000U           /*!< RTC_TS input rising edge generates a time-stamp event */
#define MS32_RTC_TIMESTAMP_EDGE_FALLING      RTC_CR_TSEDGE         /*!< RTC_TS input falling edge generates a time-stamp even */


/** @defgroup RTC_EC_TS_TIME_FORMAT  TIMESTAMP TIME FORMAT
  * @{
  */
#define MS32_RTC_TS_TIME_FORMAT_AM           0x00000000U           /*!< AM or 24-hour format */
#define MS32_RTC_TS_TIME_FORMAT_PM           RTC_TSTR_PM           /*!< PM */


/** @defgroup RTC_EC_TAMPER_PULLUP  TAMPER PULLUP
  * @{
  */
#define MS32_RTC_TAMPER_PULLUP_ENABLE        0x00000000U
#define MS32_RTC_TAMPER_PULLUP_DISABLE       RTC_TAFCR_TAMPPUDIS


/** @defgroup RTC_EC_TAMPER_DURATION  TAMPER DURATION
  * @{
  */
#define MS32_RTC_TAMPER_DURATION_1RTCCLK     0x00000000U           /*!< Tamper pins are pre-charged before sampling during 1 RTCCLK cycle  */
#define MS32_RTC_TAMPER_DURATION_2RTCCLK     RTC_TAFCR_TAMPPRCH_0  /*!< Tamper pins are pre-charged before sampling during 2 RTCCLK cycles */
#define MS32_RTC_TAMPER_DURATION_4RTCCLK     RTC_TAFCR_TAMPPRCH_1  /*!< Tamper pins are pre-charged before sampling during 4 RTCCLK cycles */
#define MS32_RTC_TAMPER_DURATION_8RTCCLK     RTC_TAFCR_TAMPPRCH    /*!< Tamper pins are pre-charged before sampling during 8 RTCCLK cycles */


/** @defgroup RTC_EC_TAMPER_FILTER  TAMPER FILTER
  * @{
  */
#define MS32_RTC_TAMPER_FILTER_DISABLE       0x00000000U            /*!< Tamper filter is disabled */
#define MS32_RTC_TAMPER_FILTER_2SAMPLE       RTC_TAFCR_TAMPFLT_0    /*!< Tamper is activated after 2 consecutive samples at the active level */
#define MS32_RTC_TAMPER_FILTER_4SAMPLE       RTC_TAFCR_TAMPFLT_1    /*!< Tamper is activated after 4 consecutive samples at the active level */
#define MS32_RTC_TAMPER_FILTER_8SAMPLE       RTC_TAFCR_TAMPFLT      /*!< Tamper is activated after 8 consecutive samples at the active level. */


/** @defgroup RTC_EC_TAMPER_SAMPLFREQDIV  TAMPER SAMPLING FREQUENCY DIVIDER
  * @{
  */
#define MS32_RTC_TAMPER_SAMPLFREQDIV_32768   0x00000000U                                    /*!< Each of the tamper inputs are sampled with a frequency =  RTCCLK / 32768 */
#define MS32_RTC_TAMPER_SAMPLFREQDIV_16384   RTC_TAFCR_TAMPFREQ_0                           /*!< Each of the tamper inputs are sampled with a frequency =  RTCCLK / 16384 */
#define MS32_RTC_TAMPER_SAMPLFREQDIV_8192    RTC_TAFCR_TAMPFREQ_1                           /*!< Each of the tamper inputs are sampled with a frequency =  RTCCLK / 8192 */
#define MS32_RTC_TAMPER_SAMPLFREQDIV_4096    (RTC_TAFCR_TAMPFREQ_1 | RTC_TAFCR_TAMPFREQ_0) /*!< Each of the tamper inputs are sampled with a frequency =  RTCCLK / 4096 */
#define MS32_RTC_TAMPER_SAMPLFREQDIV_2048    RTC_TAFCR_TAMPFREQ_2                           /*!< Each of the tamper inputs are sampled with a frequency =  RTCCLK / 2048 */
#define MS32_RTC_TAMPER_SAMPLFREQDIV_1024    (RTC_TAFCR_TAMPFREQ_2 | RTC_TAFCR_TAMPFREQ_0) /*!< Each of the tamper inputs are sampled with a frequency =  RTCCLK / 1024 */
#define MS32_RTC_TAMPER_SAMPLFREQDIV_512     (RTC_TAFCR_TAMPFREQ_2 | RTC_TAFCR_TAMPFREQ_1) /*!< Each of the tamper inputs are sampled with a frequency =  RTCCLK / 512 */
#define MS32_RTC_TAMPER_SAMPLFREQDIV_256     RTC_TAFCR_TAMPFREQ                             /*!< Each of the tamper inputs are sampled with a frequency =  RTCCLK / 256 */


/** @defgroup RTC_EC_TAMPER_TS  TAMPER TS
  * @{
  */
#define MS32_RTC_TAMPER_TS_DISABLE           0x00000000U
#define MS32_RTC_TAMPER_TS_ENABLE            RTC_TAFCR_TAMPTS


/** @defgroup RTC_EC_TAMPER1_ACTIVELEVEL  TAMPER1 ACTIVE LEVEL
  * @{
  */
#define MS32_RTC_TAMPER_INACTIVELEVEL_TAMP1  0x00000000U        /*!< RTC_TAMP1 input rising edge (if TAMPFLT = 00) or staying low (if TAMPFLT != 00) triggers a tamper detection event*/
#define MS32_RTC_TAMPER_ACTIVELEVEL_TAMP1    RTC_TAFCR_TAMP1TRG /*!< RTC_TAMP1 input falling edge (if TAMPFLT = 00) or staying high (if TAMPFLT != 00) triggers a tamper detection event*/


/** @defgroup RTC_EC_TAMPER2_ACTIVELEVEL  TAMPER2 ACTIVE LEVEL
  * @{
  */
#define MS32_RTC_TAMPER_INACTIVELEVEL_TAMP2  0x00000000U        /*!< RTC_TAMP2 input rising edge (if TAMPFLT = 00) or staying low (if TAMPFLT != 00) triggers a tamper detection event*/
#define MS32_RTC_TAMPER_ACTIVELEVEL_TAMP2    RTC_TAFCR_TAMP2TRG /*!< RTC_TAMP2 input falling edge (if TAMPFLT = 00) or staying high (if TAMPFLT != 00) triggers a tamper detection event*/


/** @defgroup RTC_EC_TAMPER1  TAMPER1
  * @{
  */
#define MS32_RTC_TAMPER_1_DIS                0x00000000U
#define MS32_RTC_TAMPER_1_EN                 RTC_TAFCR_TAMP1E /*!< RTC_TAMP1 input detection */


/** @defgroup RTC_EC_TAMPER2  TAMPER2
  * @{
  */
#define MS32_RTC_TAMPER_2_DIS                0x00000000U
#define MS32_RTC_TAMPER_2_EN                 RTC_TAFCR_TAMP2E /*!< RTC_TAMP2 input detection */



/** @defgroup RTC_EC_BKP  BACKUP
  * @{
  */
#define MS32_RTC_BKP_DR0                     0x00000000U
#define MS32_RTC_BKP_DR1                     0x00000001U
#define MS32_RTC_BKP_DR2                     0x00000002U
#define MS32_RTC_BKP_DR3                     0x00000003U
#define MS32_RTC_BKP_DR4                     0x00000004U


/** @defgroup RTC_EC_CALIB_OUTPUT  Calibration output
  * @{
  */
#define MS32_RTC_CALIB_OUTPUT_NONE           0x00000000U                 /*!< Calibration output disabled */
#define MS32_RTC_CALIB_OUTPUT_1HZ            (RTC_CR_COE | RTC_CR_COSEL) /*!< Calibration output is 1 Hz */
#define MS32_RTC_CALIB_OUTPUT_512HZ          (RTC_CR_COE)                /*!< Calibration output is 512 Hz */


/** @defgroup RTC_EC_CALIB_INSERTPULSE  Calibration pulse insertion
  * @{
  */
#define MS32_RTC_CALIB_INSERTPULSE_NONE      0x00000000U           /*!< No RTCCLK pulses are added */
#define MS32_RTC_CALIB_INSERTPULSE_SET       RTC_CALR_CALP         /*!< One RTCCLK pulse is effectively inserted every 2exp11 pulses (frequency increased by 488.5 ppm) */


/** @defgroup RTC_EC_CALIB_PERIOD  Calibration period
  * @{
  */
#define MS32_RTC_CALIB_PERIOD_32SEC          0x00000000U           /*!< Use a 32-second calibration cycle period */
#define MS32_RTC_CALIB_PERIOD_16SEC          RTC_CALR_CALW16       /*!< Use a 16-second calibration cycle period */
#define MS32_RTC_CALIB_PERIOD_8SEC           RTC_CALR_CALW8        /*!< Use a 8-second calibration cycle period */


/* Exported macro ------------------------------------------------------------*/
/** @defgroup RTC_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in RTC register
  * @param  __INSTANCE__ RTC Instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define MS32_RTC_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, (__VALUE__))

/**
  * @brief  Read a value in RTC register
  * @param  __INSTANCE__ RTC Instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define MS32_RTC_ReadReg(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)

/** @defgroup RTC_EM_Convert Convert helper Macros
  * @{
  */

/**
  * @brief  Helper macro to convert a value from 2 digit decimal format to BCD format
  * @param  __VALUE__ Byte to be converted
  * @retval Converted byte
  */
#define __MS32_RTC_CONVERT_BIN2BCD(__VALUE__) (uint8_t)((((__VALUE__) / 10U) << 4U) | ((__VALUE__) % 10U))

/**
  * @brief  Helper macro to convert a value from BCD format to 2 digit decimal format
  * @param  __VALUE__ BCD value to be converted
  * @retval Converted byte
  */
#define __MS32_RTC_CONVERT_BCD2BIN(__VALUE__) (uint8_t)(((uint8_t)((__VALUE__) & (uint8_t)0xF0U) >> (uint8_t)0x4U) * 10U + ((__VALUE__) & (uint8_t)0x0FU))


/** @defgroup RTC_EM_Date Date helper Macros
  * @{
  */

/**
  * @brief  Helper macro to retrieve weekday.
  * @param  __RTC_DATE__ Date returned by @ref  MS32_RTC_DATE_Get function.
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_RTC_WEEKDAY_MONDAY
  *         @arg @ref MS32_RTC_WEEKDAY_TUESDAY
  *         @arg @ref MS32_RTC_WEEKDAY_WEDNESDAY
  *         @arg @ref MS32_RTC_WEEKDAY_THURSDAY
  *         @arg @ref MS32_RTC_WEEKDAY_FRIDAY
  *         @arg @ref MS32_RTC_WEEKDAY_SATURDAY
  *         @arg @ref MS32_RTC_WEEKDAY_SUNDAY
  */
#define __MS32_RTC_GET_WEEKDAY(__RTC_DATE__) (((__RTC_DATE__) >> RTC_OFFSET_WEEKDAY) & 0x000000FFU)

/**
  * @brief  Helper macro to retrieve Year in BCD format
  * @param  __RTC_DATE__ Value returned by @ref  MS32_RTC_DATE_Get
  * @retval Year in BCD format (0x00 . . . 0x99)
  */
#define __MS32_RTC_GET_YEAR(__RTC_DATE__) ((__RTC_DATE__) & 0x000000FFU)

/**
  * @brief  Helper macro to retrieve Month in BCD format
  * @param  __RTC_DATE__ Value returned by @ref  MS32_RTC_DATE_Get
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_RTC_MONTH_JANUARY
  *         @arg @ref MS32_RTC_MONTH_FEBRUARY
  *         @arg @ref MS32_RTC_MONTH_MARCH
  *         @arg @ref MS32_RTC_MONTH_APRIL
  *         @arg @ref MS32_RTC_MONTH_MAY
  *         @arg @ref MS32_RTC_MONTH_JUNE
  *         @arg @ref MS32_RTC_MONTH_JULY
  *         @arg @ref MS32_RTC_MONTH_AUGUST
  *         @arg @ref MS32_RTC_MONTH_SEPTEMBER
  *         @arg @ref MS32_RTC_MONTH_OCTOBER
  *         @arg @ref MS32_RTC_MONTH_NOVEMBER
  *         @arg @ref MS32_RTC_MONTH_DECEMBER
  */
#define __MS32_RTC_GET_MONTH(__RTC_DATE__) (((__RTC_DATE__) >>RTC_OFFSET_MONTH) & 0x000000FFU)

/**
  * @brief  Helper macro to retrieve Day in BCD format
  * @param  __RTC_DATE__ Value returned by @ref  MS32_RTC_DATE_Get
  * @retval Day in BCD format (0x01 . . . 0x31)
  */
#define __MS32_RTC_GET_DAY(__RTC_DATE__) (((__RTC_DATE__) >>RTC_OFFSET_DAY) & 0x000000FFU)


/** @defgroup RTC_EM_Time Time helper Macros
  * @{
  */

/**
  * @brief  Helper macro to retrieve hour in BCD format
  * @param  __RTC_TIME__ RTC time returned by @ref MS32_RTC_TIME_Get function
  * @retval Hours in BCD format (0x01. . .0x12 or between Min_Data=0x00 and Max_Data=0x23)
  */
#define __MS32_RTC_GET_HOUR(__RTC_TIME__) (((__RTC_TIME__) >> RTC_OFFSET_HOUR) & 0x000000FFU)

/**
  * @brief  Helper macro to retrieve minute in BCD format
  * @param  __RTC_TIME__ RTC time returned by @ref MS32_RTC_TIME_Get function
  * @retval Minutes in BCD format (0x00. . .0x59)
  */
#define __MS32_RTC_GET_MINUTE(__RTC_TIME__) (((__RTC_TIME__) >> RTC_OFFSET_MINUTE) & 0x000000FFU)

/**
  * @brief  Helper macro to retrieve second in BCD format
  * @param  __RTC_TIME__ RTC time returned by @ref MS32_RTC_TIME_Get function
  * @retval Seconds in  format (0x00. . .0x59)
  */
#define __MS32_RTC_GET_SECOND(__RTC_TIME__) ((__RTC_TIME__) & 0x000000FFU)



/* Exported functions --------------------------------------------------------*/
/** @defgroup RTC_EF_Configuration Configuration
  * @{
  */

/**
  * @brief  Set Hours format (24 hour/day or AM/PM hour format)
  * @note   Bit is write-protected. @ref MS32_RTC_DisableWriteProtection function should be called before.
  * @note   It can be written in initialization mode only (@ref MS32_RTC_EnableInitMode function)
  * @rmtoll CR           FMT           MS32_RTC_SetHourFormat
  * @param  RTCx RTC Instance
  * @param  HourFormat This parameter can be one of the following values:
  *         @arg @ref MS32_RTC_HOURFORMAT_24HOUR
  *         @arg @ref MS32_RTC_HOURFORMAT_AMPM
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_SetHourFormat(RTC_TypeDef *RTCx, uint32_t HourFormat) {
  MODIFY_REG(RTCx->CR, RTC_CR_FMT, HourFormat);
}

/**
  * @brief  Get Hours format (24 hour/day or AM/PM hour format)
  * @rmtoll CR           FMT           MS32_RTC_GetHourFormat
  * @param  RTCx RTC Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_RTC_HOURFORMAT_24HOUR
  *         @arg @ref MS32_RTC_HOURFORMAT_AMPM
  */
__STATIC_INLINE uint32_t MS32_RTC_GetHourFormat(RTC_TypeDef *RTCx) {
  return (uint32_t)(READ_BIT(RTCx->CR, RTC_CR_FMT));
}

/**
  * @brief  Select the flag to be routed to RTC_ALARM output
  * @note   Bit is write-protected. @ref MS32_RTC_DisableWriteProtection function should be called before.
  * @rmtoll CR           OSEL          MS32_RTC_SetAlarmOutEvent
  * @param  RTCx RTC Instance
  * @param  AlarmOutput This parameter can be one of the following values:
  *         @arg @ref MS32_RTC_ALARMOUT_DISABLE
  *         @arg @ref MS32_RTC_ALARMOUT_ALMA
  *         @arg @ref MS32_RTC_ALARMOUT_ALMB
  *         @arg @ref MS32_RTC_ALARMOUT_WAKEUP
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_SetAlarmOutEvent(RTC_TypeDef *RTCx, uint32_t AlarmOutput) {
  MODIFY_REG(RTCx->CR, RTC_CR_OSEL, AlarmOutput);
}

/**
  * @brief  Get the flag to be routed to RTC_ALARM output
  * @rmtoll CR           OSEL          MS32_RTC_GetAlarmOutEvent
  * @param  RTCx RTC Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_RTC_ALARMOUT_DISABLE
  *         @arg @ref MS32_RTC_ALARMOUT_ALMA
  *         @arg @ref MS32_RTC_ALARMOUT_ALMB
  *         @arg @ref MS32_RTC_ALARMOUT_WAKEUP
  */
__STATIC_INLINE uint32_t MS32_RTC_GetAlarmOutEvent(RTC_TypeDef *RTCx) {
  return (uint32_t)(READ_BIT(RTCx->CR, RTC_CR_OSEL));
}

/**
  * @brief  Set RTC_ALARM output type (ALARM in push-pull or open-drain output)
  * @note   Used only when RTC_ALARM is mapped on PC13
  * @note   If all RTC alternate functions are disabled and PC13MODE = 1, PC13VALUE configures the
  *         PC13 output data
  * @rmtoll TAFCR        ALARMOUTTYPE  MS32_RTC_SetAlarmOutputType
  * @param  RTCx RTC Instance
  * @param  Output This parameter can be one of the following values:
  *         @arg @ref MS32_RTC_ALARM_OUTPUTTYPE_OPENDRAIN
  *         @arg @ref MS32_RTC_ALARM_OUTPUTTYPE_PUSHPULL
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_SetAlarmOutputType(RTC_TypeDef *RTCx, uint32_t Output) {
  MODIFY_REG(RTCx->TAFCR, RTC_TAFCR_PC13VALUE  , Output);
}

/**
  * @brief  Get RTC_ALARM output type (ALARM in push-pull or open-drain output)
  * @note   used only when RTC_ALARM is mapped on PC13
  * @note   If all RTC alternate functions are disabled and PC13MODE = 1, PC13VALUE configures the
  *         PC13 output data
  * @rmtoll TAFCR        ALARMOUTTYPE  MS32_RTC_GetAlarmOutputType
  * @param  RTCx RTC Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_RTC_ALARM_OUTPUTTYPE_OPENDRAIN
  *         @arg @ref MS32_RTC_ALARM_OUTPUTTYPE_PUSHPULL
  */
__STATIC_INLINE uint32_t MS32_RTC_GetAlarmOutputType(RTC_TypeDef *RTCx) {
  return (uint32_t)(READ_BIT(RTCx->TAFCR, RTC_TAFCR_PC13VALUE  ));
}

/**
  * @brief  Enable push-pull output on PC13, PC14 and/or PC15
  * @note   PC13 forced to push-pull output if all RTC alternate functions are disabled
  * @note   PC14 and PC15 forced to push-pull output if LSE is disabled
  * @rmtoll TAFCR        PC13MODE  MS32_RTC_EnablePushPullMode\n
  * @rmtoll TAFCR        PC14MODE  MS32_RTC_EnablePushPullMode\n
  * @rmtoll TAFCR        PC15MODE  MS32_RTC_EnablePushPullMode
  * @param  RTCx RTC Instance
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref MS32_RTC_PIN_PC13
  *         @arg @ref MS32_RTC_PIN_PC14
  *         @arg @ref MS32_RTC_PIN_PC15
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_EnablePushPullMode(RTC_TypeDef *RTCx, uint32_t PinMask) {
  SET_BIT(RTCx->TAFCR, PinMask);
}

/**
  * @brief  Disable push-pull output on PC13, PC14 and/or PC15
  * @note   PC13, PC14 and/or PC15 are controlled by the GPIO configuration registers.
  *         Consequently PC13, PC14 and/or PC15 are floating in Standby mode.
  * @rmtoll TAFCR        PC13MODE      MS32_RTC_DisablePushPullMode\n
  *         TAFCR        PC14MODE      MS32_RTC_DisablePushPullMode\n
  *         TAFCR        PC15MODE      MS32_RTC_DisablePushPullMode
  * @param  RTCx RTC Instance
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref MS32_RTC_PIN_PC13
  *         @arg @ref MS32_RTC_PIN_PC14
  *         @arg @ref MS32_RTC_PIN_PC15
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_DisablePushPullMode(RTC_TypeDef *RTCx, uint32_t PinMask) {
  CLEAR_BIT(RTCx->TAFCR, PinMask);
}

/**
  * @brief  Set PC14 and/or PC15 to high level.
  * @note   Output data configuration is possible if the LSE is disabled and PushPull output is enabled (through @ref MS32_RTC_EnablePushPullMode)
  * @rmtoll TAFCR        PC14VALUE     MS32_RTC_SetOutputPin\n
  *         TAFCR        PC15VALUE     MS32_RTC_SetOutputPin
  * @param  RTCx RTC Instance
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref MS32_RTC_PIN_PC14
  *         @arg @ref MS32_RTC_PIN_PC15
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_SetOutputPin(RTC_TypeDef *RTCx, uint32_t PinMask) {
  SET_BIT(RTCx->TAFCR, (PinMask >> 1));
}

/**
  * @brief  Set PC14 and/or PC15 to low level.
  * @note   Output data configuration is possible if the LSE is disabled and PushPull output is enabled (through @ref MS32_RTC_EnablePushPullMode)
  * @rmtoll TAFCR        PC14VALUE     MS32_RTC_ResetOutputPin\n
  *         TAFCR        PC15VALUE     MS32_RTC_ResetOutputPin
  * @param  RTCx RTC Instance
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref MS32_RTC_PIN_PC14
  *         @arg @ref MS32_RTC_PIN_PC15
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_ResetOutputPin(RTC_TypeDef *RTCx, uint32_t PinMask) {
  CLEAR_BIT(RTCx->TAFCR, (PinMask >> 1));
}

/**
  * @brief  Enable initialization mode
  * @note   Initialization mode is used to program time and date register (RTC_TR and RTC_DR)
  *         and prescaler register (RTC_PRER).
  *         Counters are stopped and start counting from the new value when INIT is reset.
  * @rmtoll ISR          INIT          MS32_RTC_EnableInitMode
  * @param  RTCx RTC Instance
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_EnableInitMode(RTC_TypeDef *RTCx) {
  /* Set the Initialization mode */
  WRITE_REG(RTCx->ISR, RTC_INIT_MASK);
}

/**
  * @brief  Disable initialization mode (Free running mode)
  * @rmtoll ISR          INIT          MS32_RTC_DisableInitMode
  * @param  RTCx RTC Instance
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_DisableInitMode(RTC_TypeDef *RTCx) {
  /* Exit Initialization mode */
  WRITE_REG(RTCx->ISR, (uint32_t)~RTC_ISR_INIT);
}

/**
  * @brief  Set Output polarity (pin is low when ALRAF/ALRBF/WUTF is asserted)
  * @note   Bit is write-protected. @ref MS32_RTC_DisableWriteProtection function should be called before.
  * @rmtoll CR           POL           MS32_RTC_SetOutputPolarity
  * @param  RTCx RTC Instance
  * @param  Polarity This parameter can be one of the following values:
  *         @arg @ref MS32_RTC_OUTPUTPOLARITY_PIN_HIGH
  *         @arg @ref MS32_RTC_OUTPUTPOLARITY_PIN_LOW
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_SetOutputPolarity(RTC_TypeDef *RTCx, uint32_t Polarity) {
  MODIFY_REG(RTCx->CR, RTC_CR_POL, Polarity);
}

/**
  * @brief  Get Output polarity
  * @rmtoll CR           POL           MS32_RTC_GetOutputPolarity
  * @param  RTCx RTC Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_RTC_OUTPUTPOLARITY_PIN_HIGH
  *         @arg @ref MS32_RTC_OUTPUTPOLARITY_PIN_LOW
  */
__STATIC_INLINE uint32_t MS32_RTC_GetOutputPolarity(RTC_TypeDef *RTCx) {
  return (uint32_t)(READ_BIT(RTCx->CR, RTC_CR_POL));
}

/**
  * @brief  Enable Bypass the shadow registers
  * @note   Bit is write-protected. @ref MS32_RTC_DisableWriteProtection function should be called before.
  * @rmtoll CR           BYPSHAD       MS32_RTC_EnableShadowRegBypass
  * @param  RTCx RTC Instance
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_EnableShadowRegBypass(RTC_TypeDef *RTCx) {
  SET_BIT(RTCx->CR, RTC_CR_BYPSHAD);
}

/**
  * @brief  Disable Bypass the shadow registers
  * @rmtoll CR           BYPSHAD       MS32_RTC_DisableShadowRegBypass
  * @param  RTCx RTC Instance
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_DisableShadowRegBypass(RTC_TypeDef *RTCx) {
  CLEAR_BIT(RTCx->CR, RTC_CR_BYPSHAD);
}

/**
  * @brief  Check if Shadow registers bypass is enabled or not.
  * @rmtoll CR           BYPSHAD       MS32_RTC_IsShadowRegBypassEnabled
  * @param  RTCx RTC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_RTC_IsShadowRegBypassEnabled(RTC_TypeDef *RTCx) {
  return (READ_BIT(RTCx->CR, RTC_CR_BYPSHAD) == (RTC_CR_BYPSHAD));
}

/**
  * @brief  Enable RTC_REFIN reference clock detection (50 or 60 Hz)
  * @note   Bit is write-protected. @ref MS32_RTC_DisableWriteProtection function should be called before.
  * @note   It can be written in initialization mode only (@ref MS32_RTC_EnableInitMode function)
  * @rmtoll CR           REFCKON       MS32_RTC_EnableRefClock
  * @param  RTCx RTC Instance
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_EnableRefClock(RTC_TypeDef *RTCx) {
  SET_BIT(RTCx->CR, RTC_CR_REFCKON);
}

/**
  * @brief  Disable RTC_REFIN reference clock detection (50 or 60 Hz)
  * @note   Bit is write-protected. @ref MS32_RTC_DisableWriteProtection function should be called before.
  * @note   It can be written in initialization mode only (@ref MS32_RTC_EnableInitMode function)
  * @rmtoll CR           REFCKON       MS32_RTC_DisableRefClock
  * @param  RTCx RTC Instance
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_DisableRefClock(RTC_TypeDef *RTCx) {
  CLEAR_BIT(RTCx->CR, RTC_CR_REFCKON);
}

/**
  * @brief  Set Asynchronous prescaler factor
  * @rmtoll PRER         PREDIV_A      MS32_RTC_SetAsynchPrescaler
  * @param  RTCx RTC Instance
  * @param  AsynchPrescaler Value between Min_Data = 0 and Max_Data = 0x7F
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_SetAsynchPrescaler(RTC_TypeDef *RTCx, uint32_t AsynchPrescaler) {
  MODIFY_REG(RTCx->PRER, RTC_PRER_PREDIV_A, AsynchPrescaler << RTC_PRER_PREDIV_A_Pos);
}

/**
  * @brief  Set Synchronous prescaler factor
  * @rmtoll PRER         PREDIV_S      MS32_RTC_SetSynchPrescaler
  * @param  RTCx RTC Instance
  * @param  SynchPrescaler Value between Min_Data = 0 and Max_Data = 0x7FFF
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_SetSynchPrescaler(RTC_TypeDef *RTCx, uint32_t SynchPrescaler) {
  MODIFY_REG(RTCx->PRER, RTC_PRER_PREDIV_S, SynchPrescaler);
}

/**
  * @brief  Get Asynchronous prescaler factor
  * @rmtoll PRER         PREDIV_A      MS32_RTC_GetAsynchPrescaler
  * @param  RTCx RTC Instance
  * @retval Value between Min_Data = 0 and Max_Data = 0x7F
  */
__STATIC_INLINE uint32_t MS32_RTC_GetAsynchPrescaler(RTC_TypeDef *RTCx) {
  return (uint32_t)(READ_BIT(RTCx->PRER, RTC_PRER_PREDIV_A) >> RTC_PRER_PREDIV_A_Pos);
}

/**
  * @brief  Get Synchronous prescaler factor
  * @rmtoll PRER         PREDIV_S      MS32_RTC_GetSynchPrescaler
  * @param  RTCx RTC Instance
  * @retval Value between Min_Data = 0 and Max_Data = 0x7FFF
  */
__STATIC_INLINE uint32_t MS32_RTC_GetSynchPrescaler(RTC_TypeDef *RTCx) {
  return (uint32_t)(READ_BIT(RTCx->PRER, RTC_PRER_PREDIV_S));
}

/**
  * @brief  Enable the write protection for RTC registers.
  * @rmtoll WPR          KEY           MS32_RTC_EnableWriteProtection
  * @param  RTCx RTC Instance
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_EnableWriteProtection(RTC_TypeDef *RTCx) {
  WRITE_REG(RTCx->WPR, RTC_WRITE_PROTECTION_DISABLE);
}

/**
  * @brief  Disable the write protection for RTC registers.
  * @rmtoll WPR          KEY           MS32_RTC_DisableWriteProtection
  * @param  RTCx RTC Instance
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_DisableWriteProtection(RTC_TypeDef *RTCx) {
  WRITE_REG(RTCx->WPR, RTC_WRITE_PROTECTION_ENABLE_1);
  WRITE_REG(RTCx->WPR, RTC_WRITE_PROTECTION_ENABLE_2);
}


/** @defgroup RTC_EF_Time Time
  * @{
  */

/**
  * @brief  Set time format (AM/24-hour or PM notation)
  * @note   Bit is write-protected. @ref MS32_RTC_DisableWriteProtection function should be called before.
  * @note   It can be written in initialization mode only (@ref MS32_RTC_EnableInitMode function)
  * @rmtoll TR           PM            MS32_RTC_TIME_SetFormat
  * @param  RTCx RTC Instance
  * @param  TimeFormat This parameter can be one of the following values:
  *         @arg @ref MS32_RTC_TIME_FORMAT_AM_OR_24
  *         @arg @ref MS32_RTC_TIME_FORMAT_PM
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_TIME_SetFormat(RTC_TypeDef *RTCx, uint32_t TimeFormat) {
  MODIFY_REG(RTCx->TR, RTC_TR_PM, TimeFormat);
}

/**
  * @brief  Get time format (AM or PM notation)
  * @note if shadow mode is disabled (BYPSHAD=0), need to check if RSF flag is set
  *       before reading this bit
  * @note Read either RTC_SSR or RTC_TR locks the values in the higher-order calendar
  *       shadow registers until RTC_DR is read (MS32_RTC_ReadReg(RTC, DR)).
  * @rmtoll TR           PM            MS32_RTC_TIME_GetFormat
  * @param  RTCx RTC Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_RTC_TIME_FORMAT_AM_OR_24
  *         @arg @ref MS32_RTC_TIME_FORMAT_PM
  */
__STATIC_INLINE uint32_t MS32_RTC_TIME_GetFormat(RTC_TypeDef *RTCx) {
  return (uint32_t)(READ_BIT(RTCx->TR, RTC_TR_PM));
}

/**
  * @brief  Set Hours in BCD format
  * @note   Bit is write-protected. @ref MS32_RTC_DisableWriteProtection function should be called before.
  * @note   It can be written in initialization mode only (@ref MS32_RTC_EnableInitMode function)
  * @note helper macro __MS32_RTC_CONVERT_BIN2BCD is available to convert hour from binary to BCD format
  * @rmtoll TR           HT            MS32_RTC_TIME_SetHour\n
  *         TR           HU            MS32_RTC_TIME_SetHour
  * @param  RTCx RTC Instance
  * @param  Hours Value between Min_Data=0x01 and Max_Data=0x12 or between Min_Data=0x00 and Max_Data=0x23
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_TIME_SetHour(RTC_TypeDef *RTCx, uint32_t Hours) {
  MODIFY_REG(RTCx->TR, (RTC_TR_HT | RTC_TR_HU),
             (((Hours & 0xF0U) << (RTC_TR_HT_Pos - 4U)) | ((Hours & 0x0FU) << RTC_TR_HU_Pos)));
}

/**
  * @brief  Get Hours in BCD format
  * @note if shadow mode is disabled (BYPSHAD=0), need to check if RSF flag is set
  *       before reading this bit
  * @note Read either RTC_SSR or RTC_TR locks the values in the higher-order calendar
  *       shadow registers until RTC_DR is read (MS32_RTC_ReadReg(RTC, DR)).
  * @note helper macro __MS32_RTC_CONVERT_BCD2BIN is available to convert hour from BCD to
  *       Binary format
  * @rmtoll TR           HT            MS32_RTC_TIME_GetHour\n
  *         TR           HU            MS32_RTC_TIME_GetHour
  * @param  RTCx RTC Instance
  * @retval Value between Min_Data=0x01 and Max_Data=0x12 or between Min_Data=0x00 and Max_Data=0x23
  */
__STATIC_INLINE uint32_t MS32_RTC_TIME_GetHour(RTC_TypeDef *RTCx) {
  return (uint32_t)((READ_BIT(RTCx->TR, (RTC_TR_HT | RTC_TR_HU))) >> RTC_TR_HU_Pos);
}

/**
  * @brief  Set Minutes in BCD format
  * @note   Bit is write-protected. @ref MS32_RTC_DisableWriteProtection function should be called before.
  * @note   It can be written in initialization mode only (@ref MS32_RTC_EnableInitMode function)
  * @note helper macro __MS32_RTC_CONVERT_BIN2BCD is available to convert Minutes from binary to BCD format
  * @rmtoll TR           MNT           MS32_RTC_TIME_SetMinute\n
  *         TR           MNU           MS32_RTC_TIME_SetMinute
  * @param  RTCx RTC Instance
  * @param  Minutes Value between Min_Data=0x00 and Max_Data=0x59
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_TIME_SetMinute(RTC_TypeDef *RTCx, uint32_t Minutes) {
  MODIFY_REG(RTCx->TR, (RTC_TR_MNT | RTC_TR_MNU),
             (((Minutes & 0xF0U) << (RTC_TR_MNT_Pos - 4U)) | ((Minutes & 0x0FU) << RTC_TR_MNU_Pos)));
}

/**
  * @brief  Get Minutes in BCD format
  * @note if shadow mode is disabled (BYPSHAD=0), need to check if RSF flag is set
  *       before reading this bit
  * @note Read either RTC_SSR or RTC_TR locks the values in the higher-order calendar
  *       shadow registers until RTC_DR is read (MS32_RTC_ReadReg(RTC, DR)).
  * @note helper macro __MS32_RTC_CONVERT_BCD2BIN is available to convert minute from BCD
  *       to Binary format
  * @rmtoll TR           MNT           MS32_RTC_TIME_GetMinute\n
  *         TR           MNU           MS32_RTC_TIME_GetMinute
  * @param  RTCx RTC Instance
  * @retval Value between Min_Data=0x00 and Max_Data=0x59
  */
__STATIC_INLINE uint32_t MS32_RTC_TIME_GetMinute(RTC_TypeDef *RTCx) {
  return (uint32_t)((READ_BIT(RTCx->TR, (RTC_TR_MNT | RTC_TR_MNU))) >> RTC_TR_MNU_Pos);
}

/**
  * @brief  Set Seconds in BCD format
  * @note   Bit is write-protected. @ref MS32_RTC_DisableWriteProtection function should be called before.
  * @note   It can be written in initialization mode only (@ref MS32_RTC_EnableInitMode function)
  * @note helper macro __MS32_RTC_CONVERT_BIN2BCD is available to convert Seconds from binary to BCD format
  * @rmtoll TR           ST            MS32_RTC_TIME_SetSecond\n
  *         TR           SU            MS32_RTC_TIME_SetSecond
  * @param  RTCx RTC Instance
  * @param  Seconds Value between Min_Data=0x00 and Max_Data=0x59
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_TIME_SetSecond(RTC_TypeDef *RTCx, uint32_t Seconds) {
  MODIFY_REG(RTCx->TR, (RTC_TR_ST | RTC_TR_SU),
             (((Seconds & 0xF0U) << (RTC_TR_ST_Pos - 4U)) | ((Seconds & 0x0FU) << RTC_TR_SU_Pos)));
}

/**
  * @brief  Get Seconds in BCD format
  * @note if shadow mode is disabled (BYPSHAD=0), need to check if RSF flag is set
  *       before reading this bit
  * @note Read either RTC_SSR or RTC_TR locks the values in the higher-order calendar
  *       shadow registers until RTC_DR is read (MS32_RTC_ReadReg(RTC, DR)).
  * @note helper macro __MS32_RTC_CONVERT_BCD2BIN is available to convert Seconds from BCD
  *       to Binary format
  * @rmtoll TR           ST            MS32_RTC_TIME_GetSecond\n
  *         TR           SU            MS32_RTC_TIME_GetSecond
  * @param  RTCx RTC Instance
  * @retval Value between Min_Data=0x00 and Max_Data=0x59
  */
__STATIC_INLINE uint32_t MS32_RTC_TIME_GetSecond(RTC_TypeDef *RTCx) {
  return (uint32_t)((READ_BIT(RTCx->TR, (RTC_TR_ST | RTC_TR_SU))) >> RTC_TR_SU_Pos);
}

/**
  * @brief  Set time (hour, minute and second) in BCD format
  * @note   Bit is write-protected. @ref MS32_RTC_DisableWriteProtection function should be called before.
  * @note   It can be written in initialization mode only (@ref MS32_RTC_EnableInitMode function)
  * @note TimeFormat and Hours should follow the same format
  * @rmtoll TR           PM            MS32_RTC_TIME_Config\n
  *         TR           HT            MS32_RTC_TIME_Config\n
  *         TR           HU            MS32_RTC_TIME_Config\n
  *         TR           MNT           MS32_RTC_TIME_Config\n
  *         TR           MNU           MS32_RTC_TIME_Config\n
  *         TR           ST            MS32_RTC_TIME_Config\n
  *         TR           SU            MS32_RTC_TIME_Config
  * @param  RTCx RTC Instance
  * @param  Format12_24 This parameter can be one of the following values:
  *         @arg @ref MS32_RTC_TIME_FORMAT_AM_OR_24
  *         @arg @ref MS32_RTC_TIME_FORMAT_PM
  * @param  Hours Value between Min_Data=0x01 and Max_Data=0x12 or between Min_Data=0x00 and Max_Data=0x23
  * @param  Minutes Value between Min_Data=0x00 and Max_Data=0x59
  * @param  Seconds Value between Min_Data=0x00 and Max_Data=0x59
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_TIME_Config(RTC_TypeDef *RTCx, uint32_t Format12_24, uint32_t Hours, uint32_t Minutes, uint32_t Seconds) {
  register uint32_t temp = 0U;

  temp = Format12_24                                                                                    | \
         (((Hours & 0xF0U) << (RTC_TR_HT_Pos - 4U)) | ((Hours & 0x0FU) << RTC_TR_HU_Pos))     | \
         (((Minutes & 0xF0U) << (RTC_TR_MNT_Pos - 4U)) | ((Minutes & 0x0FU) << RTC_TR_MNU_Pos)) | \
         (((Seconds & 0xF0U) << (RTC_TR_ST_Pos - 4U)) | ((Seconds & 0x0FU) << RTC_TR_SU_Pos));
  MODIFY_REG(RTCx->TR, (RTC_TR_PM | RTC_TR_HT | RTC_TR_HU | RTC_TR_MNT | RTC_TR_MNU | RTC_TR_ST | RTC_TR_SU), temp);
}

/**
  * @brief  Get time (hour, minute and second) in BCD format
  * @note if shadow mode is disabled (BYPSHAD=0), need to check if RSF flag is set
  *       before reading this bit
  * @note Read either RTC_SSR or RTC_TR locks the values in the higher-order calendar
  *       shadow registers until RTC_DR is read (MS32_RTC_ReadReg(RTC, DR)).
  * @note helper macros __MS32_RTC_GET_HOUR, __MS32_RTC_GET_MINUTE and __MS32_RTC_GET_SECOND
  *       are available to get independently each parameter.
  * @rmtoll TR           HT            MS32_RTC_TIME_Get\n
  *         TR           HU            MS32_RTC_TIME_Get\n
  *         TR           MNT           MS32_RTC_TIME_Get\n
  *         TR           MNU           MS32_RTC_TIME_Get\n
  *         TR           ST            MS32_RTC_TIME_Get\n
  *         TR           SU            MS32_RTC_TIME_Get
  * @param  RTCx RTC Instance
  * @retval Combination of hours, minutes and seconds (Format: 0x00HHMMSS).
  */
__STATIC_INLINE uint32_t MS32_RTC_TIME_Get(RTC_TypeDef *RTCx) {
  register uint32_t temp = 0U;

  temp = READ_BIT(RTCx->TR, (RTC_TR_HT | RTC_TR_HU | RTC_TR_MNT | RTC_TR_MNU | RTC_TR_ST | RTC_TR_SU));
  return (uint32_t)((((((temp & RTC_TR_HT) >> RTC_TR_HT_Pos) << 4U) | ((temp & RTC_TR_HU) >> RTC_TR_HU_Pos)) << RTC_OFFSET_HOUR) |  \
                    (((((temp & RTC_TR_MNT) >> RTC_TR_MNT_Pos) << 4U) | ((temp & RTC_TR_MNU) >> RTC_TR_MNU_Pos)) << RTC_OFFSET_MINUTE) | \
                    ((((temp & RTC_TR_ST) >> RTC_TR_ST_Pos) << 4U) | ((temp & RTC_TR_SU) >> RTC_TR_SU_Pos)));
}

/**
  * @brief  Memorize whether the daylight saving time change has been performed
  * @note   Bit is write-protected. @ref MS32_RTC_DisableWriteProtection function should be called before.
  * @rmtoll CR           BKP           MS32_RTC_TIME_EnableDayLightStore
  * @param  RTCx RTC Instance
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_TIME_EnableDayLightStore(RTC_TypeDef *RTCx) {
  SET_BIT(RTCx->CR, RTC_CR_BKP);
}

/**
  * @brief  Disable memorization whether the daylight saving time change has been performed.
  * @note   Bit is write-protected. @ref MS32_RTC_DisableWriteProtection function should be called before.
  * @rmtoll CR           BKP           MS32_RTC_TIME_DisableDayLightStore
  * @param  RTCx RTC Instance
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_TIME_DisableDayLightStore(RTC_TypeDef *RTCx) {
  CLEAR_BIT(RTCx->CR, RTC_CR_BKP);
}

/**
  * @brief  Check if RTC Day Light Saving stored operation has been enabled or not
  * @rmtoll CR           BKP           MS32_RTC_TIME_IsDayLightStoreEnabled
  * @param  RTCx RTC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_RTC_TIME_IsDayLightStoreEnabled(RTC_TypeDef *RTCx) {
  return (READ_BIT(RTCx->CR, RTC_CR_BKP) == (RTC_CR_BKP));
}

/**
  * @brief  Subtract 1 hour (winter time change)
  * @note   Bit is write-protected. @ref MS32_RTC_DisableWriteProtection function should be called before.
  * @rmtoll CR           SUB1H         MS32_RTC_TIME_DecHour
  * @param  RTCx RTC Instance
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_TIME_DecHour(RTC_TypeDef *RTCx) {
  SET_BIT(RTCx->CR, RTC_CR_SUB1H);
}

/**
  * @brief  Add 1 hour (summer time change)
  * @note   Bit is write-protected. @ref MS32_RTC_DisableWriteProtection function should be called before.
  * @rmtoll CR           ADD1H         MS32_RTC_TIME_IncHour
  * @param  RTCx RTC Instance
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_TIME_IncHour(RTC_TypeDef *RTCx) {
  SET_BIT(RTCx->CR, RTC_CR_ADD1H);
}

/**
  * @brief  Get Sub second value in the synchronous prescaler counter.
  * @note  You can use both SubSeconds value and SecondFraction (PREDIV_S through
  *        MS32_RTC_GetSynchPrescaler function) terms returned to convert Calendar
  *        SubSeconds value in second fraction ratio with time unit following
  *        generic formula:
  *          ==> Seconds fraction ratio * time_unit= [(SecondFraction-SubSeconds)/(SecondFraction+1)] * time_unit
  *        This conversion can be performed only if no shift operation is pending
  *        (ie. SHFP=0) when PREDIV_S >= SS.
  * @rmtoll SSR          SS            MS32_RTC_TIME_GetSubSecond
  * @param  RTCx RTC Instance
  * @retval Sub second value (number between 0 and 65535)
  */
__STATIC_INLINE uint32_t MS32_RTC_TIME_GetSubSecond(RTC_TypeDef *RTCx) {
  return (uint32_t)(READ_BIT(RTCx->SSR, RTC_SSR_SS));
}

/**
  * @brief  Synchronize to a remote clock with a high degree of precision.
  * @note   This operation effectively subtracts from (delays) or advance the clock of a fraction of a second.
  * @note   Bit is write-protected. @ref MS32_RTC_DisableWriteProtection function should be called before.
  * @note   When REFCKON is set, firmware must not write to Shift control register.
  * @rmtoll SHIFTR       ADD1S         MS32_RTC_TIME_Synchronize\n
  *         SHIFTR       SUBFS         MS32_RTC_TIME_Synchronize
  * @param  RTCx RTC Instance
  * @param  ShiftSecond This parameter can be one of the following values:
  *         @arg @ref MS32_RTC_SHIFT_SECOND_DELAY
  *         @arg @ref MS32_RTC_SHIFT_SECOND_ADVANCE
  * @param  Fraction Number of Seconds Fractions (any value from 0 to 0x7FFF)
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_TIME_Synchronize(RTC_TypeDef *RTCx, uint32_t ShiftSecond, uint32_t Fraction) {
  WRITE_REG(RTCx->SHIFTR, ShiftSecond | Fraction);
}


/** @defgroup RTC_EF_Date Date
  * @{
  */

/**
  * @brief  Set Year in BCD format
  * @note helper macro __MS32_RTC_CONVERT_BIN2BCD is available to convert Year from binary to BCD format
  * @rmtoll DR           YT            MS32_RTC_DATE_SetYear\n
  *         DR           YU            MS32_RTC_DATE_SetYear
  * @param  RTCx RTC Instance
  * @param  Year Value between Min_Data=0x00 and Max_Data=0x99
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_DATE_SetYear(RTC_TypeDef *RTCx, uint32_t Year) {
  MODIFY_REG(RTCx->DR, (RTC_DR_YT | RTC_DR_YU),
             (((Year & 0xF0U) << (RTC_DR_YT_Pos - 4U)) | ((Year & 0x0FU) << RTC_DR_YU_Pos)));
}

/**
  * @brief  Get Year in BCD format
  * @note if shadow mode is disabled (BYPSHAD=0), need to check if RSF flag is set
  *       before reading this bit
  * @note helper macro __MS32_RTC_CONVERT_BCD2BIN is available to convert Year from BCD to Binary format
  * @rmtoll DR           YT            MS32_RTC_DATE_GetYear\n
  *         DR           YU            MS32_RTC_DATE_GetYear
  * @param  RTCx RTC Instance
  * @retval Value between Min_Data=0x00 and Max_Data=0x99
  */
__STATIC_INLINE uint32_t MS32_RTC_DATE_GetYear(RTC_TypeDef *RTCx) {
  return (uint32_t)((READ_BIT(RTCx->DR, (RTC_DR_YT | RTC_DR_YU))) >> RTC_DR_YU_Pos);
}

/**
  * @brief  Set Week day
  * @rmtoll DR           WDU           MS32_RTC_DATE_SetWeekDay
  * @param  RTCx RTC Instance
  * @param  WeekDay This parameter can be one of the following values:
  *         @arg @ref MS32_RTC_WEEKDAY_MONDAY
  *         @arg @ref MS32_RTC_WEEKDAY_TUESDAY
  *         @arg @ref MS32_RTC_WEEKDAY_WEDNESDAY
  *         @arg @ref MS32_RTC_WEEKDAY_THURSDAY
  *         @arg @ref MS32_RTC_WEEKDAY_FRIDAY
  *         @arg @ref MS32_RTC_WEEKDAY_SATURDAY
  *         @arg @ref MS32_RTC_WEEKDAY_SUNDAY
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_DATE_SetWeekDay(RTC_TypeDef *RTCx, uint32_t WeekDay) {
  MODIFY_REG(RTCx->DR, RTC_DR_WDU, WeekDay << RTC_DR_WDU_Pos);
}

/**
  * @brief  Get Week day
  * @note if shadow mode is disabled (BYPSHAD=0), need to check if RSF flag is set
  *       before reading this bit
  * @rmtoll DR           WDU           MS32_RTC_DATE_GetWeekDay
  * @param  RTCx RTC Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_RTC_WEEKDAY_MONDAY
  *         @arg @ref MS32_RTC_WEEKDAY_TUESDAY
  *         @arg @ref MS32_RTC_WEEKDAY_WEDNESDAY
  *         @arg @ref MS32_RTC_WEEKDAY_THURSDAY
  *         @arg @ref MS32_RTC_WEEKDAY_FRIDAY
  *         @arg @ref MS32_RTC_WEEKDAY_SATURDAY
  *         @arg @ref MS32_RTC_WEEKDAY_SUNDAY
  */
__STATIC_INLINE uint32_t MS32_RTC_DATE_GetWeekDay(RTC_TypeDef *RTCx) {
  return (uint32_t)(READ_BIT(RTCx->DR, RTC_DR_WDU) >> RTC_DR_WDU_Pos);
}

/**
  * @brief  Set Month in BCD format
  * @note helper macro __MS32_RTC_CONVERT_BIN2BCD is available to convert Month from binary to BCD format
  * @rmtoll DR           MT            MS32_RTC_DATE_SetMonth\n
  *         DR           MU            MS32_RTC_DATE_SetMonth
  * @param  RTCx RTC Instance
  * @param  Month This parameter can be one of the following values:
  *         @arg @ref MS32_RTC_MONTH_JANUARY
  *         @arg @ref MS32_RTC_MONTH_FEBRUARY
  *         @arg @ref MS32_RTC_MONTH_MARCH
  *         @arg @ref MS32_RTC_MONTH_APRIL
  *         @arg @ref MS32_RTC_MONTH_MAY
  *         @arg @ref MS32_RTC_MONTH_JUNE
  *         @arg @ref MS32_RTC_MONTH_JULY
  *         @arg @ref MS32_RTC_MONTH_AUGUST
  *         @arg @ref MS32_RTC_MONTH_SEPTEMBER
  *         @arg @ref MS32_RTC_MONTH_OCTOBER
  *         @arg @ref MS32_RTC_MONTH_NOVEMBER
  *         @arg @ref MS32_RTC_MONTH_DECEMBER
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_DATE_SetMonth(RTC_TypeDef *RTCx, uint32_t Month) {
  MODIFY_REG(RTCx->DR, (RTC_DR_MT | RTC_DR_MU),
             (((Month & 0xF0U) << (RTC_DR_MT_Pos - 4U)) | ((Month & 0x0FU) << RTC_DR_MU_Pos)));
}

/**
  * @brief  Get Month in BCD format
  * @note if shadow mode is disabled (BYPSHAD=0), need to check if RSF flag is set
  *       before reading this bit
  * @note helper macro __MS32_RTC_CONVERT_BCD2BIN is available to convert Month from BCD to Binary format
  * @rmtoll DR           MT            MS32_RTC_DATE_GetMonth\n
  *         DR           MU            MS32_RTC_DATE_GetMonth
  * @param  RTCx RTC Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_RTC_MONTH_JANUARY
  *         @arg @ref MS32_RTC_MONTH_FEBRUARY
  *         @arg @ref MS32_RTC_MONTH_MARCH
  *         @arg @ref MS32_RTC_MONTH_APRIL
  *         @arg @ref MS32_RTC_MONTH_MAY
  *         @arg @ref MS32_RTC_MONTH_JUNE
  *         @arg @ref MS32_RTC_MONTH_JULY
  *         @arg @ref MS32_RTC_MONTH_AUGUST
  *         @arg @ref MS32_RTC_MONTH_SEPTEMBER
  *         @arg @ref MS32_RTC_MONTH_OCTOBER
  *         @arg @ref MS32_RTC_MONTH_NOVEMBER
  *         @arg @ref MS32_RTC_MONTH_DECEMBER
  */
__STATIC_INLINE uint32_t MS32_RTC_DATE_GetMonth(RTC_TypeDef *RTCx) {
  return (uint32_t)((READ_BIT(RTCx->DR, (RTC_DR_MT | RTC_DR_MU))) >> RTC_DR_MU_Pos);
}

/**
  * @brief  Set Day in BCD format
  * @note helper macro __MS32_RTC_CONVERT_BIN2BCD is available to convert Day from binary to BCD format
  * @rmtoll DR           DT            MS32_RTC_DATE_SetDay\n
  *         DR           DU            MS32_RTC_DATE_SetDay
  * @param  RTCx RTC Instance
  * @param  Day Value between Min_Data=0x01 and Max_Data=0x31
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_DATE_SetDay(RTC_TypeDef *RTCx, uint32_t Day) {
  MODIFY_REG(RTCx->DR, (RTC_DR_DT | RTC_DR_DU),
             (((Day & 0xF0U) << (RTC_DR_DT_Pos - 4U)) | ((Day & 0x0FU) << RTC_DR_DU_Pos)));
}

/**
  * @brief  Get Day in BCD format
  * @note if shadow mode is disabled (BYPSHAD=0), need to check if RSF flag is set
  *       before reading this bit
  * @note helper macro __MS32_RTC_CONVERT_BCD2BIN is available to convert Day from BCD to Binary format
  * @rmtoll DR           DT            MS32_RTC_DATE_GetDay\n
  *         DR           DU            MS32_RTC_DATE_GetDay
  * @param  RTCx RTC Instance
  * @retval Value between Min_Data=0x01 and Max_Data=0x31
  */
__STATIC_INLINE uint32_t MS32_RTC_DATE_GetDay(RTC_TypeDef *RTCx) {
  return (uint32_t)((READ_BIT(RTCx->DR, (RTC_DR_DT | RTC_DR_DU))) >> RTC_DR_DU_Pos);
}

/**
  * @brief  Set date (WeekDay, Day, Month and Year) in BCD format
  * @rmtoll DR           WDU           MS32_RTC_DATE_Config\n
  *         DR           MT            MS32_RTC_DATE_Config\n
  *         DR           MU            MS32_RTC_DATE_Config\n
  *         DR           DT            MS32_RTC_DATE_Config\n
  *         DR           DU            MS32_RTC_DATE_Config\n
  *         DR           YT            MS32_RTC_DATE_Config\n
  *         DR           YU            MS32_RTC_DATE_Config
  * @param  RTCx RTC Instance
  * @param  WeekDay This parameter can be one of the following values:
  *         @arg @ref MS32_RTC_WEEKDAY_MONDAY
  *         @arg @ref MS32_RTC_WEEKDAY_TUESDAY
  *         @arg @ref MS32_RTC_WEEKDAY_WEDNESDAY
  *         @arg @ref MS32_RTC_WEEKDAY_THURSDAY
  *         @arg @ref MS32_RTC_WEEKDAY_FRIDAY
  *         @arg @ref MS32_RTC_WEEKDAY_SATURDAY
  *         @arg @ref MS32_RTC_WEEKDAY_SUNDAY
  * @param  Day Value between Min_Data=0x01 and Max_Data=0x31
  * @param  Month This parameter can be one of the following values:
  *         @arg @ref MS32_RTC_MONTH_JANUARY
  *         @arg @ref MS32_RTC_MONTH_FEBRUARY
  *         @arg @ref MS32_RTC_MONTH_MARCH
  *         @arg @ref MS32_RTC_MONTH_APRIL
  *         @arg @ref MS32_RTC_MONTH_MAY
  *         @arg @ref MS32_RTC_MONTH_JUNE
  *         @arg @ref MS32_RTC_MONTH_JULY
  *         @arg @ref MS32_RTC_MONTH_AUGUST
  *         @arg @ref MS32_RTC_MONTH_SEPTEMBER
  *         @arg @ref MS32_RTC_MONTH_OCTOBER
  *         @arg @ref MS32_RTC_MONTH_NOVEMBER
  *         @arg @ref MS32_RTC_MONTH_DECEMBER
  * @param  Year Value between Min_Data=0x00 and Max_Data=0x99
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_DATE_Config(RTC_TypeDef *RTCx, uint32_t WeekDay, uint32_t Day, uint32_t Month, uint32_t Year) {
  register uint32_t temp = 0U;

  temp = (WeekDay << RTC_DR_WDU_Pos)                                                      | \
         (((Year & 0xF0U) << (RTC_DR_YT_Pos - 4U)) | ((Year & 0x0FU) << RTC_DR_YU_Pos))   | \
         (((Month & 0xF0U) << (RTC_DR_MT_Pos - 4U)) | ((Month & 0x0FU) << RTC_DR_MU_Pos)) | \
         (((Day & 0xF0U) << (RTC_DR_DT_Pos - 4U)) | ((Day & 0x0FU) << RTC_DR_DU_Pos));

  MODIFY_REG(RTCx->DR, (RTC_DR_WDU | RTC_DR_MT | RTC_DR_MU | RTC_DR_DT | RTC_DR_DU | RTC_DR_YT | RTC_DR_YU), temp);
}

/**
  * @brief  Get date (WeekDay, Day, Month and Year) in BCD format
  * @note if shadow mode is disabled (BYPSHAD=0), need to check if RSF flag is set
  *       before reading this bit
  * @note helper macros __MS32_RTC_GET_WEEKDAY, __MS32_RTC_GET_YEAR, __MS32_RTC_GET_MONTH,
  * and __MS32_RTC_GET_DAY are available to get independently each parameter.
  * @rmtoll DR           WDU           MS32_RTC_DATE_Get\n
  *         DR           MT            MS32_RTC_DATE_Get\n
  *         DR           MU            MS32_RTC_DATE_Get\n
  *         DR           DT            MS32_RTC_DATE_Get\n
  *         DR           DU            MS32_RTC_DATE_Get\n
  *         DR           YT            MS32_RTC_DATE_Get\n
  *         DR           YU            MS32_RTC_DATE_Get
  * @param  RTCx RTC Instance
  * @retval Combination of WeekDay, Day, Month and Year (Format: 0xWWDDMMYY).
  */
__STATIC_INLINE uint32_t MS32_RTC_DATE_Get(RTC_TypeDef *RTCx) {
  register uint32_t temp = 0U;

  temp = READ_BIT(RTCx->DR, (RTC_DR_WDU | RTC_DR_MT | RTC_DR_MU | RTC_DR_DT | RTC_DR_DU | RTC_DR_YT | RTC_DR_YU));
  return (uint32_t)((((temp & RTC_DR_WDU) >> RTC_DR_WDU_Pos) << RTC_OFFSET_WEEKDAY) | \
                    (((((temp & RTC_DR_DT) >> RTC_DR_DT_Pos) << 4U) | ((temp & RTC_DR_DU) >> RTC_DR_DU_Pos)) << RTC_OFFSET_DAY) | \
                    (((((temp & RTC_DR_MT) >> RTC_DR_MT_Pos) << 4U) | ((temp & RTC_DR_MU) >> RTC_DR_MU_Pos)) << RTC_OFFSET_MONTH) | \
                    ((((temp & RTC_DR_YT) >> RTC_DR_YT_Pos) << 4U) | ((temp & RTC_DR_YU) >> RTC_DR_YU_Pos)));
}


/** @defgroup RTC_EF_ALARMA ALARMA
  * @{
  */

/**
  * @brief  Enable Alarm A
  * @note   Bit is write-protected. @ref MS32_RTC_DisableWriteProtection function should be called before.
  * @rmtoll CR           ALRAE         MS32_RTC_ALARM_Enable
  * @param  RTCx RTC Instance
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_ALARM_Enable(RTC_TypeDef *RTCx) {
  SET_BIT(RTCx->CR, RTC_CR_ALRAE);
}

/**
  * @brief  Disable Alarm A
  * @note   Bit is write-protected. @ref MS32_RTC_DisableWriteProtection function should be called before.
  * @rmtoll CR           ALRAE         MS32_RTC_ALARM_Disable
  * @param  RTCx RTC Instance
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_ALARM_Disable(RTC_TypeDef *RTCx) {
  CLEAR_BIT(RTCx->CR, RTC_CR_ALRAE);
}

/**
  * @brief  Specify the Alarm A masks.
  * @rmtoll ALRMAR       MSK4          MS32_RTC_ALARM_SetMask\n
  *         ALRMAR       MSK3          MS32_RTC_ALARM_SetMask\n
  *         ALRMAR       MSK2          MS32_RTC_ALARM_SetMask\n
  *         ALRMAR       MSK1          MS32_RTC_ALARM_SetMask
  * @param  RTCx RTC Instance
  * @param  Mask This parameter can be a combination of the following values:
  *         @arg @ref MS32_RTC_ALARM_MASK_NONE
  *         @arg @ref MS32_RTC_ALARM_MASK_DATEWEEKDAY
  *         @arg @ref MS32_RTC_ALARM_MASK_HOURS
  *         @arg @ref MS32_RTC_ALARM_MASK_MINUTES
  *         @arg @ref MS32_RTC_ALARM_MASK_SECONDS
  *         @arg @ref MS32_RTC_ALARM_MASK_ALL
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_ALARM_SetMask(RTC_TypeDef *RTCx, uint32_t Mask) {
  MODIFY_REG(RTCx->ALRMAR, RTC_ALRMAR_MSK4 | RTC_ALRMAR_MSK3 | RTC_ALRMAR_MSK2 | RTC_ALRMAR_MSK1, Mask);
}

/**
  * @brief  Get the Alarm A masks.
  * @rmtoll ALRMAR       MSK4          MS32_RTC_ALARM_GetMask\n
  *         ALRMAR       MSK3          MS32_RTC_ALARM_GetMask\n
  *         ALRMAR       MSK2          MS32_RTC_ALARM_GetMask\n
  *         ALRMAR       MSK1          MS32_RTC_ALARM_GetMask
  * @param  RTCx RTC Instance
  * @retval Returned value can be can be a combination of the following values:
  *         @arg @ref MS32_RTC_ALARM_MASK_NONE
  *         @arg @ref MS32_RTC_ALARM_MASK_DATEWEEKDAY
  *         @arg @ref MS32_RTC_ALARM_MASK_HOURS
  *         @arg @ref MS32_RTC_ALARM_MASK_MINUTES
  *         @arg @ref MS32_RTC_ALARM_MASK_SECONDS
  *         @arg @ref MS32_RTC_ALARM_MASK_ALL
  */
__STATIC_INLINE uint32_t MS32_RTC_ALARM_GetMask(RTC_TypeDef *RTCx) {
  return (uint32_t)(READ_BIT(RTCx->ALRMAR, RTC_ALRMAR_MSK4 | RTC_ALRMAR_MSK3 | RTC_ALRMAR_MSK2 | RTC_ALRMAR_MSK1));
}

/**
  * @brief  Enable AlarmA Week day selection (DU[3:0] represents the week day. DT[1:0] is do not care)
  * @rmtoll ALRMAR       WDSEL         MS32_RTC_ALARM_EnableWeekday
  * @param  RTCx RTC Instance
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_ALARM_EnableWeekday(RTC_TypeDef *RTCx) {
  SET_BIT(RTCx->ALRMAR, RTC_ALRMAR_WDSEL);
}

/**
  * @brief  Disable AlarmA Week day selection (DU[3:0] represents the date )
  * @rmtoll ALRMAR       WDSEL         MS32_RTC_ALARM_DisableWeekday
  * @param  RTCx RTC Instance
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_ALARM_DisableWeekday(RTC_TypeDef *RTCx) {
  CLEAR_BIT(RTCx->ALRMAR, RTC_ALRMAR_WDSEL);
}

/**
  * @brief  Set ALARM A Day in BCD format
  * @note helper macro __MS32_RTC_CONVERT_BIN2BCD is available to convert Day from binary to BCD format
  * @rmtoll ALRMAR       DT            MS32_RTC_ALARM_SetDay\n
  *         ALRMAR       DU            MS32_RTC_ALARM_SetDay
  * @param  RTCx RTC Instance
  * @param  Day Value between Min_Data=0x01 and Max_Data=0x31
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_ALARM_SetDay(RTC_TypeDef *RTCx, uint32_t Day) {
  MODIFY_REG(RTCx->ALRMAR, (RTC_ALRMAR_DT | RTC_ALRMAR_DU),
             (((Day & 0xF0U) << (RTC_ALRMAR_DT_Pos - 4U)) | ((Day & 0x0FU) << RTC_ALRMAR_DU_Pos)));
}

/**
  * @brief  Get ALARM A Day in BCD format
  * @note helper macro __MS32_RTC_CONVERT_BCD2BIN is available to convert Day from BCD to Binary format
  * @rmtoll ALRMAR       DT            MS32_RTC_ALARM_GetDay\n
  *         ALRMAR       DU            MS32_RTC_ALARM_GetDay
  * @param  RTCx RTC Instance
  * @retval Value between Min_Data=0x01 and Max_Data=0x31
  */
__STATIC_INLINE uint32_t MS32_RTC_ALARM_GetDay(RTC_TypeDef *RTCx) {
  return (uint32_t)((READ_BIT(RTCx->ALRMAR, (RTC_ALRMAR_DT | RTC_ALRMAR_DU))) >> RTC_ALRMAR_DU_Pos);
}

/**
  * @brief  Set ALARM A Weekday
  * @rmtoll ALRMAR       DU            MS32_RTC_ALARM_SetWeekDay
  * @param  RTCx RTC Instance
  * @param  WeekDay This parameter can be one of the following values:
  *         @arg @ref MS32_RTC_WEEKDAY_MONDAY
  *         @arg @ref MS32_RTC_WEEKDAY_TUESDAY
  *         @arg @ref MS32_RTC_WEEKDAY_WEDNESDAY
  *         @arg @ref MS32_RTC_WEEKDAY_THURSDAY
  *         @arg @ref MS32_RTC_WEEKDAY_FRIDAY
  *         @arg @ref MS32_RTC_WEEKDAY_SATURDAY
  *         @arg @ref MS32_RTC_WEEKDAY_SUNDAY
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_ALARM_SetWeekDay(RTC_TypeDef *RTCx, uint32_t WeekDay) {
  MODIFY_REG(RTCx->ALRMAR, RTC_ALRMAR_DU, WeekDay << RTC_ALRMAR_DU_Pos);
}

/**
  * @brief  Get ALARM A Weekday
  * @rmtoll ALRMAR       DU            MS32_RTC_ALARM_GetWeekDay
  * @param  RTCx RTC Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_RTC_WEEKDAY_MONDAY
  *         @arg @ref MS32_RTC_WEEKDAY_TUESDAY
  *         @arg @ref MS32_RTC_WEEKDAY_WEDNESDAY
  *         @arg @ref MS32_RTC_WEEKDAY_THURSDAY
  *         @arg @ref MS32_RTC_WEEKDAY_FRIDAY
  *         @arg @ref MS32_RTC_WEEKDAY_SATURDAY
  *         @arg @ref MS32_RTC_WEEKDAY_SUNDAY
  */
__STATIC_INLINE uint32_t MS32_RTC_ALARM_GetWeekDay(RTC_TypeDef *RTCx) {
  return (uint32_t)(READ_BIT(RTCx->ALRMAR, RTC_ALRMAR_DU) >> RTC_ALRMAR_DU_Pos);
}

/**
  * @brief  Set Alarm A time format (AM/24-hour or PM notation)
  * @rmtoll ALRMAR       PM            MS32_RTC_ALARM_SetTimeFormat
  * @param  RTCx RTC Instance
  * @param  TimeFormat This parameter can be one of the following values:
  *         @arg @ref MS32_RTC_ALARM_TIME_FORMAT_AM
  *         @arg @ref MS32_RTC_ALARM_TIME_FORMAT_PM
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_ALARM_SetTimeFormat(RTC_TypeDef *RTCx, uint32_t TimeFormat) {
  MODIFY_REG(RTCx->ALRMAR, RTC_ALRMAR_PM, TimeFormat);
}

/**
  * @brief  Get Alarm A time format (AM or PM notation)
  * @rmtoll ALRMAR       PM            MS32_RTC_ALARM_GetTimeFormat
  * @param  RTCx RTC Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_RTC_ALARM_TIME_FORMAT_AM
  *         @arg @ref MS32_RTC_ALARM_TIME_FORMAT_PM
  */
__STATIC_INLINE uint32_t MS32_RTC_ALARM_GetTimeFormat(RTC_TypeDef *RTCx) {
  return (uint32_t)(READ_BIT(RTCx->ALRMAR, RTC_ALRMAR_PM));
}

/**
  * @brief  Set ALARM A Hours in BCD format
  * @note helper macro __MS32_RTC_CONVERT_BIN2BCD is available to convert Hours from binary to BCD format
  * @rmtoll ALRMAR       HT            MS32_RTC_ALARM_SetHour\n
  *         ALRMAR       HU            MS32_RTC_ALARM_SetHour
  * @param  RTCx RTC Instance
  * @param  Hours Value between Min_Data=0x01 and Max_Data=0x12 or between Min_Data=0x00 and Max_Data=0x23
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_ALARM_SetHour(RTC_TypeDef *RTCx, uint32_t Hours) {
  MODIFY_REG(RTCx->ALRMAR, (RTC_ALRMAR_HT | RTC_ALRMAR_HU),
             (((Hours & 0xF0U) << (RTC_ALRMAR_HT_Pos - 4U)) | ((Hours & 0x0FU) << RTC_ALRMAR_HU_Pos)));
}

/**
  * @brief  Get ALARM A Hours in BCD format
  * @note helper macro __MS32_RTC_CONVERT_BCD2BIN is available to convert Hours from BCD to Binary format
  * @rmtoll ALRMAR       HT            MS32_RTC_ALARM_GetHour\n
  *         ALRMAR       HU            MS32_RTC_ALARM_GetHour
  * @param  RTCx RTC Instance
  * @retval Value between Min_Data=0x01 and Max_Data=0x12 or between Min_Data=0x00 and Max_Data=0x23
  */
__STATIC_INLINE uint32_t MS32_RTC_ALARM_GetHour(RTC_TypeDef *RTCx) {
  return (uint32_t)((READ_BIT(RTCx->ALRMAR, (RTC_ALRMAR_HT | RTC_ALRMAR_HU))) >> RTC_ALRMAR_HU_Pos);
}

/**
  * @brief  Set ALARM A Minutes in BCD format
  * @note helper macro __MS32_RTC_CONVERT_BIN2BCD is available to convert Minutes from binary to BCD format
  * @rmtoll ALRMAR       MNT           MS32_RTC_ALARM_SetMinute\n
  *         ALRMAR       MNU           MS32_RTC_ALARM_SetMinute
  * @param  RTCx RTC Instance
  * @param  Minutes Value between Min_Data=0x00 and Max_Data=0x59
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_ALARM_SetMinute(RTC_TypeDef *RTCx, uint32_t Minutes) {
  MODIFY_REG(RTCx->ALRMAR, (RTC_ALRMAR_MNT | RTC_ALRMAR_MNU),
             (((Minutes & 0xF0U) << (RTC_ALRMAR_MNT_Pos - 4U)) | ((Minutes & 0x0FU) << RTC_ALRMAR_MNU_Pos)));
}

/**
  * @brief  Get ALARM A Minutes in BCD format
  * @note helper macro __MS32_RTC_CONVERT_BCD2BIN is available to convert Minutes from BCD to Binary format
  * @rmtoll ALRMAR       MNT           MS32_RTC_ALARM_GetMinute\n
  *         ALRMAR       MNU           MS32_RTC_ALARM_GetMinute
  * @param  RTCx RTC Instance
  * @retval Value between Min_Data=0x00 and Max_Data=0x59
  */
__STATIC_INLINE uint32_t MS32_RTC_ALARM_GetMinute(RTC_TypeDef *RTCx) {
  return (uint32_t)((READ_BIT(RTCx->ALRMAR, (RTC_ALRMAR_MNT | RTC_ALRMAR_MNU))) >> RTC_ALRMAR_MNU_Pos);
}

/**
  * @brief  Set ALARM A Seconds in BCD format
  * @note helper macro __MS32_RTC_CONVERT_BIN2BCD is available to convert Seconds from binary to BCD format
  * @rmtoll ALRMAR       ST            MS32_RTC_ALARM_SetSecond\n
  *         ALRMAR       SU            MS32_RTC_ALARM_SetSecond
  * @param  RTCx RTC Instance
  * @param  Seconds Value between Min_Data=0x00 and Max_Data=0x59
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_ALARM_SetSecond(RTC_TypeDef *RTCx, uint32_t Seconds) {
  MODIFY_REG(RTCx->ALRMAR, (RTC_ALRMAR_ST | RTC_ALRMAR_SU),
             (((Seconds & 0xF0U) << (RTC_ALRMAR_ST_Pos - 4U)) | ((Seconds & 0x0FU) << RTC_ALRMAR_SU_Pos)));
}

/**
  * @brief  Get ALARM A Seconds in BCD format
  * @note helper macro __MS32_RTC_CONVERT_BCD2BIN is available to convert Seconds from BCD to Binary format
  * @rmtoll ALRMAR       ST            MS32_RTC_ALARM_GetSecond\n
  *         ALRMAR       SU            MS32_RTC_ALARM_GetSecond
  * @param  RTCx RTC Instance
  * @retval Value between Min_Data=0x00 and Max_Data=0x59
  */
__STATIC_INLINE uint32_t MS32_RTC_ALARM_GetSecond(RTC_TypeDef *RTCx) {
  return (uint32_t)((READ_BIT(RTCx->ALRMAR, (RTC_ALRMAR_ST | RTC_ALRMAR_SU))) >> RTC_ALRMAR_SU_Pos);
}

/**
  * @brief  Set Alarm A Time (hour, minute and second) in BCD format
  * @rmtoll ALRMAR       PM            MS32_RTC_ALARM_ConfigTime\n
  *         ALRMAR       HT            MS32_RTC_ALARM_ConfigTime\n
  *         ALRMAR       HU            MS32_RTC_ALARM_ConfigTime\n
  *         ALRMAR       MNT           MS32_RTC_ALARM_ConfigTime\n
  *         ALRMAR       MNU           MS32_RTC_ALARM_ConfigTime\n
  *         ALRMAR       ST            MS32_RTC_ALARM_ConfigTime\n
  *         ALRMAR       SU            MS32_RTC_ALARM_ConfigTime
  * @param  RTCx RTC Instance
  * @param  Format12_24 This parameter can be one of the following values:
  *         @arg @ref MS32_RTC_ALARM_TIME_FORMAT_AM
  *         @arg @ref MS32_RTC_ALARM_TIME_FORMAT_PM
  * @param  Hours Value between Min_Data=0x01 and Max_Data=0x12 or between Min_Data=0x00 and Max_Data=0x23
  * @param  Minutes Value between Min_Data=0x00 and Max_Data=0x59
  * @param  Seconds Value between Min_Data=0x00 and Max_Data=0x59
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_ALARM_ConfigTime(RTC_TypeDef *RTCx, uint32_t Format12_24, uint32_t Hours, uint32_t Minutes, uint32_t Seconds) {
  register uint32_t temp = 0U;

  temp = Format12_24 | (((Hours & 0xF0U) << (RTC_ALRMAR_HT_Pos - 4U)) | ((Hours & 0x0FU) << RTC_ALRMAR_HU_Pos))    | \
         (((Minutes & 0xF0U) << (RTC_ALRMAR_MNT_Pos - 4U)) | ((Minutes & 0x0FU) << RTC_ALRMAR_MNU_Pos)) | \
         (((Seconds & 0xF0U) << (RTC_ALRMAR_ST_Pos - 4U)) | ((Seconds & 0x0FU) << RTC_ALRMAR_SU_Pos));

  MODIFY_REG(RTCx->ALRMAR, RTC_ALRMAR_PM | RTC_ALRMAR_HT | RTC_ALRMAR_HU | RTC_ALRMAR_MNT | RTC_ALRMAR_MNU | RTC_ALRMAR_ST | RTC_ALRMAR_SU, temp);
}

/**
  * @brief  Get Alarm B Time (hour, minute and second) in BCD format
  * @note helper macros __MS32_RTC_GET_HOUR, __MS32_RTC_GET_MINUTE and __MS32_RTC_GET_SECOND
  * are available to get independently each parameter.
  * @rmtoll ALRMAR       HT            MS32_RTC_ALARM_GetTime\n
  *         ALRMAR       HU            MS32_RTC_ALARM_GetTime\n
  *         ALRMAR       MNT           MS32_RTC_ALARM_GetTime\n
  *         ALRMAR       MNU           MS32_RTC_ALARM_GetTime\n
  *         ALRMAR       ST            MS32_RTC_ALARM_GetTime\n
  *         ALRMAR       SU            MS32_RTC_ALARM_GetTime
  * @param  RTCx RTC Instance
  * @retval Combination of hours, minutes and seconds.
  */
__STATIC_INLINE uint32_t MS32_RTC_ALARM_GetTime(RTC_TypeDef *RTCx) {
  return (uint32_t)((MS32_RTC_ALARM_GetHour(RTCx) << RTC_OFFSET_HOUR) | (MS32_RTC_ALARM_GetMinute(RTCx) << RTC_OFFSET_MINUTE) | MS32_RTC_ALARM_GetSecond(RTCx));
}

/**
  * @brief  Set Alarm A Mask the most-significant bits starting at this bit
  * @note This register can be written only when ALRAE is reset in RTC_CR register,
  *       or in initialization mode.
  * @rmtoll ALRMASSR     MASKSS        MS32_RTC_ALARM_SetSubSecondMask
  * @param  RTCx RTC Instance
  * @param  Mask Value between Min_Data=0x00 and Max_Data=0xF
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_ALARM_SetSubSecondMask(RTC_TypeDef *RTCx, uint32_t Mask) {
  MODIFY_REG(RTCx->ALRMASSR, RTC_ALRMASSR_MASKSS, Mask << RTC_ALRMASSR_MASKSS_Pos);
}

/**
  * @brief  Get Alarm A Mask the most-significant bits starting at this bit
  * @rmtoll ALRMASSR     MASKSS        MS32_RTC_ALARM_GetSubSecondMask
  * @param  RTCx RTC Instance
  * @retval Value between Min_Data=0x00 and Max_Data=0xF
  */
__STATIC_INLINE uint32_t MS32_RTC_ALARM_GetSubSecondMask(RTC_TypeDef *RTCx) {
  return (uint32_t)(READ_BIT(RTCx->ALRMASSR, RTC_ALRMASSR_MASKSS) >> RTC_ALRMASSR_MASKSS_Pos);
}

/**
  * @brief  Set Alarm A Sub seconds value
  * @rmtoll ALRMASSR     SS            MS32_RTC_ALARM_SetSubSecond
  * @param  RTCx RTC Instance
  * @param  Subsecond Value between Min_Data=0x00 and Max_Data=0x7FFF
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_ALARM_SetSubSecond(RTC_TypeDef *RTCx, uint32_t Subsecond) {
  MODIFY_REG(RTCx->ALRMASSR, RTC_ALRMASSR_SS, Subsecond);
}

/**
  * @brief  Get Alarm A Sub seconds value
  * @rmtoll ALRMASSR     SS            MS32_RTC_ALARM_GetSubSecond
  * @param  RTCx RTC Instance
  * @retval Value between Min_Data=0x00 and Max_Data=0x7FFF
  */
__STATIC_INLINE uint32_t MS32_RTC_ALARM_GetSubSecond(RTC_TypeDef *RTCx) {
  return (uint32_t)(READ_BIT(RTCx->ALRMASSR, RTC_ALRMASSR_SS));
}


/** @defgroup RTC_EF_Timestamp Timestamp
  * @{
  */

/**
  * @brief  Enable Timestamp
  * @note   Bit is write-protected. @ref MS32_RTC_DisableWriteProtection function should be called before.
  * @rmtoll CR           TSE           MS32_RTC_TS_Enable
  * @param  RTCx RTC Instance
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_TS_Enable(RTC_TypeDef *RTCx) {
  SET_BIT(RTCx->CR, RTC_CR_TSE);
}

/**
  * @brief  Disable Timestamp
  * @note   Bit is write-protected. @ref MS32_RTC_DisableWriteProtection function should be called before.
  * @rmtoll CR           TSE           MS32_RTC_TS_Disable
  * @param  RTCx RTC Instance
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_TS_Disable(RTC_TypeDef *RTCx) {
  CLEAR_BIT(RTCx->CR, RTC_CR_TSE);
}

/**
  * @brief  Set Time-stamp event active edge
  * @note   Bit is write-protected. @ref MS32_RTC_DisableWriteProtection function should be called before.
  * @note TSE must be reset when TSEDGE is changed to avoid unwanted TSF setting
  * @rmtoll CR           TSEDGE        MS32_RTC_TS_SetActiveEdge
  * @param  RTCx RTC Instance
  * @param  Edge This parameter can be one of the following values:
  *         @arg @ref MS32_RTC_TIMESTAMP_EDGE_RISING
  *         @arg @ref MS32_RTC_TIMESTAMP_EDGE_FALLING
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_TS_SetActiveEdge(RTC_TypeDef *RTCx, uint32_t Edge) {
  MODIFY_REG(RTCx->CR, RTC_CR_TSEDGE, Edge);
}

/**
  * @brief  Get Time-stamp event active edge
  * @note   Bit is write-protected. @ref MS32_RTC_DisableWriteProtection function should be called before.
  * @rmtoll CR           TSEDGE        MS32_RTC_TS_GetActiveEdge
  * @param  RTCx RTC Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_RTC_TIMESTAMP_EDGE_RISING
  *         @arg @ref MS32_RTC_TIMESTAMP_EDGE_FALLING
  */
__STATIC_INLINE uint32_t MS32_RTC_TS_GetActiveEdge(RTC_TypeDef *RTCx) {
  return (uint32_t)(READ_BIT(RTCx->CR, RTC_CR_TSEDGE));
}

/**
  * @brief  Get Timestamp AM/PM notation (AM or 24-hour format)
  * @rmtoll TSTR         PM            MS32_RTC_TS_GetTimeFormat
  * @param  RTCx RTC Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_RTC_TS_TIME_FORMAT_AM
  *         @arg @ref MS32_RTC_TS_TIME_FORMAT_PM
  */
__STATIC_INLINE uint32_t MS32_RTC_TS_GetTimeFormat(RTC_TypeDef *RTCx) {
  return (uint32_t)(READ_BIT(RTCx->TSTR, RTC_TSTR_PM));
}

/**
  * @brief  Get Timestamp Hours in BCD format
  * @note helper macro __MS32_RTC_CONVERT_BCD2BIN is available to convert Hours from BCD to Binary format
  * @rmtoll TSTR         HT            MS32_RTC_TS_GetHour\n
  *         TSTR         HU            MS32_RTC_TS_GetHour
  * @param  RTCx RTC Instance
  * @retval Value between Min_Data=0x01 and Max_Data=0x12 or between Min_Data=0x00 and Max_Data=0x23
  */
__STATIC_INLINE uint32_t MS32_RTC_TS_GetHour(RTC_TypeDef *RTCx) {
  return (uint32_t)(READ_BIT(RTCx->TSTR, RTC_TSTR_HT | RTC_TSTR_HU) >> RTC_TSTR_HU_Pos);
}

/**
  * @brief  Get Timestamp Minutes in BCD format
  * @note helper macro __MS32_RTC_CONVERT_BCD2BIN is available to convert Minutes from BCD to Binary format
  * @rmtoll TSTR         MNT           MS32_RTC_TS_GetMinute\n
  *         TSTR         MNU           MS32_RTC_TS_GetMinute
  * @param  RTCx RTC Instance
  * @retval Value between Min_Data=0x00 and Max_Data=0x59
  */
__STATIC_INLINE uint32_t MS32_RTC_TS_GetMinute(RTC_TypeDef *RTCx) {
  return (uint32_t)(READ_BIT(RTCx->TSTR, RTC_TSTR_MNT | RTC_TSTR_MNU) >> RTC_TSTR_MNU_Pos);
}

/**
  * @brief  Get Timestamp Seconds in BCD format
  * @note helper macro __MS32_RTC_CONVERT_BCD2BIN is available to convert Seconds from BCD to Binary format
  * @rmtoll TSTR         ST            MS32_RTC_TS_GetSecond\n
  *         TSTR         SU            MS32_RTC_TS_GetSecond
  * @param  RTCx RTC Instance
  * @retval Value between Min_Data=0x00 and Max_Data=0x59
  */
__STATIC_INLINE uint32_t MS32_RTC_TS_GetSecond(RTC_TypeDef *RTCx) {
  return (uint32_t)(READ_BIT(RTCx->TSTR, RTC_TSTR_ST | RTC_TSTR_SU));
}

/**
  * @brief  Get Timestamp time (hour, minute and second) in BCD format
  * @note helper macros __MS32_RTC_GET_HOUR, __MS32_RTC_GET_MINUTE and __MS32_RTC_GET_SECOND
  * are available to get independently each parameter.
  * @rmtoll TSTR         HT            MS32_RTC_TS_GetTime\n
  *         TSTR         HU            MS32_RTC_TS_GetTime\n
  *         TSTR         MNT           MS32_RTC_TS_GetTime\n
  *         TSTR         MNU           MS32_RTC_TS_GetTime\n
  *         TSTR         ST            MS32_RTC_TS_GetTime\n
  *         TSTR         SU            MS32_RTC_TS_GetTime
  * @param  RTCx RTC Instance
  * @retval Combination of hours, minutes and seconds.
  */
__STATIC_INLINE uint32_t MS32_RTC_TS_GetTime(RTC_TypeDef *RTCx) {
  return (uint32_t)(READ_BIT(RTCx->TSTR,
                             RTC_TSTR_HT | RTC_TSTR_HU | RTC_TSTR_MNT | RTC_TSTR_MNU | RTC_TSTR_ST | RTC_TSTR_SU));
}

/**
  * @brief  Get Timestamp Week day
  * @rmtoll TSDR         WDU           MS32_RTC_TS_GetWeekDay
  * @param  RTCx RTC Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_RTC_WEEKDAY_MONDAY
  *         @arg @ref MS32_RTC_WEEKDAY_TUESDAY
  *         @arg @ref MS32_RTC_WEEKDAY_WEDNESDAY
  *         @arg @ref MS32_RTC_WEEKDAY_THURSDAY
  *         @arg @ref MS32_RTC_WEEKDAY_FRIDAY
  *         @arg @ref MS32_RTC_WEEKDAY_SATURDAY
  *         @arg @ref MS32_RTC_WEEKDAY_SUNDAY
  */
__STATIC_INLINE uint32_t MS32_RTC_TS_GetWeekDay(RTC_TypeDef *RTCx) {
  return (uint32_t)(READ_BIT(RTCx->TSDR, RTC_TSDR_WDU) >> RTC_TSDR_WDU_Pos);
}

/**
  * @brief  Get Timestamp Month in BCD format
  * @note helper macro __MS32_RTC_CONVERT_BCD2BIN is available to convert Month from BCD to Binary format
  * @rmtoll TSDR         MT            MS32_RTC_TS_GetMonth\n
  *         TSDR         MU            MS32_RTC_TS_GetMonth
  * @param  RTCx RTC Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_RTC_MONTH_JANUARY
  *         @arg @ref MS32_RTC_MONTH_FEBRUARY
  *         @arg @ref MS32_RTC_MONTH_MARCH
  *         @arg @ref MS32_RTC_MONTH_APRIL
  *         @arg @ref MS32_RTC_MONTH_MAY
  *         @arg @ref MS32_RTC_MONTH_JUNE
  *         @arg @ref MS32_RTC_MONTH_JULY
  *         @arg @ref MS32_RTC_MONTH_AUGUST
  *         @arg @ref MS32_RTC_MONTH_SEPTEMBER
  *         @arg @ref MS32_RTC_MONTH_OCTOBER
  *         @arg @ref MS32_RTC_MONTH_NOVEMBER
  *         @arg @ref MS32_RTC_MONTH_DECEMBER
  */
__STATIC_INLINE uint32_t MS32_RTC_TS_GetMonth(RTC_TypeDef *RTCx) {
  return (uint32_t)(READ_BIT(RTCx->TSDR, RTC_TSDR_MT | RTC_TSDR_MU) >> RTC_TSDR_MU_Pos);
}

/**
  * @brief  Get Timestamp Day in BCD format
  * @note helper macro __MS32_RTC_CONVERT_BCD2BIN is available to convert Day from BCD to Binary format
  * @rmtoll TSDR         DT            MS32_RTC_TS_GetDay\n
  *         TSDR         DU            MS32_RTC_TS_GetDay
  * @param  RTCx RTC Instance
  * @retval Value between Min_Data=0x01 and Max_Data=0x31
  */
__STATIC_INLINE uint32_t MS32_RTC_TS_GetDay(RTC_TypeDef *RTCx) {
  return (uint32_t)(READ_BIT(RTCx->TSDR, RTC_TSDR_DT | RTC_TSDR_DU));
}

/**
  * @brief  Get Timestamp date (WeekDay, Day and Month) in BCD format
  * @note helper macros __MS32_RTC_GET_WEEKDAY, __MS32_RTC_GET_MONTH,
  * and __MS32_RTC_GET_DAY are available to get independently each parameter.
  * @rmtoll TSDR         WDU           MS32_RTC_TS_GetDate\n
  *         TSDR         MT            MS32_RTC_TS_GetDate\n
  *         TSDR         MU            MS32_RTC_TS_GetDate\n
  *         TSDR         DT            MS32_RTC_TS_GetDate\n
  *         TSDR         DU            MS32_RTC_TS_GetDate
  * @param  RTCx RTC Instance
  * @retval Combination of Weekday, Day and Month
  */
__STATIC_INLINE uint32_t MS32_RTC_TS_GetDate(RTC_TypeDef *RTCx) {
  return (uint32_t)(READ_BIT(RTCx->TSDR, RTC_TSDR_WDU | RTC_TSDR_MT | RTC_TSDR_MU | RTC_TSDR_DT | RTC_TSDR_DU));
}

/**
  * @brief  Get time-stamp sub second value
  * @rmtoll TSSSR        SS            MS32_RTC_TS_GetSubSecond
  * @param  RTCx RTC Instance
  * @retval Value between Min_Data=0x00 and Max_Data=0xFFFF
  */
__STATIC_INLINE uint32_t MS32_RTC_TS_GetSubSecond(RTC_TypeDef *RTCx) {
  return (uint32_t)(READ_BIT(RTCx->TSSSR, RTC_TSSSR_SS));
}

/**
  * @brief  Activate timestamp on tamper detection event
  * @rmtoll TAFCR       TAMPTS        MS32_RTC_TS_EnableOnTamper
  * @param  RTCx RTC Instance
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_TS_EnableOnTamper(RTC_TypeDef *RTCx) {
  SET_BIT(RTCx->TAFCR, RTC_TAFCR_TAMPTS);
}

/**
  * @brief  Disable timestamp on tamper detection event
  * @rmtoll TAFCR       TAMPTS        MS32_RTC_TS_DisableOnTamper
  * @param  RTCx RTC Instance
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_TS_DisableOnTamper(RTC_TypeDef *RTCx) {
  CLEAR_BIT(RTCx->TAFCR, RTC_TAFCR_TAMPTS);
}


/** @defgroup RTC_EF_Tamper Tamper
  * @{
  */

/**
  * @brief  Enable RTC_TAMPx input detection
  * @rmtoll TAFCR       TAMP1E        MS32_RTC_TAMPER_Enable\n
  *         TAFCR       TAMP2E        MS32_RTC_TAMPER_Enable\n
  *         TAFCR       TAMP3E        MS32_RTC_TAMPER_Enable
  * @param  RTCx RTC Instance
  * @param  Tamper This parameter can be a combination of the following values:
  *         @arg @ref MS32_RTC_TAMPER_1
  *         @arg @ref MS32_RTC_TAMPER_2
  *         @arg @ref MS32_RTC_TAMPER_3 (*)
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_TAMPER_Enable(RTC_TypeDef *RTCx, uint32_t Tamper) {
  SET_BIT(RTCx->TAFCR, Tamper);
}

/**
  * @brief  Clear RTC_TAMPx input detection
  * @rmtoll TAFCR       TAMP1E        MS32_RTC_TAMPER_Disable\n
  *         TAFCR       TAMP2E        MS32_RTC_TAMPER_Disable\n
  *         TAFCR       TAMP3E        MS32_RTC_TAMPER_Disable
  * @param  RTCx RTC Instance
  * @param  Tamper This parameter can be a combination of the following values:
  *         @arg @ref MS32_RTC_TAMPER_1
  *         @arg @ref MS32_RTC_TAMPER_2
  *         @arg @ref MS32_RTC_TAMPER_3 (*)
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_TAMPER_Disable(RTC_TypeDef *RTCx, uint32_t Tamper) {
  CLEAR_BIT(RTCx->TAFCR, Tamper);
}

/**
  * @brief  Disable RTC_TAMPx pull-up disable (Disable precharge of RTC_TAMPx pins)
  * @rmtoll TAFCR       TAMPPUDIS     MS32_RTC_TAMPER_DisablePullUp
  * @param  RTCx RTC Instance
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_TAMPER_DisablePullUp(RTC_TypeDef *RTCx) {
  SET_BIT(RTCx->TAFCR, RTC_TAFCR_TAMPPUDIS);
}

/**
  * @brief  Enable RTC_TAMPx pull-up disable ( Precharge RTC_TAMPx pins before sampling)
  * @rmtoll TAFCR       TAMPPUDIS     MS32_RTC_TAMPER_EnablePullUp
  * @param  RTCx RTC Instance
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_TAMPER_EnablePullUp(RTC_TypeDef *RTCx) {
  CLEAR_BIT(RTCx->TAFCR, RTC_TAFCR_TAMPPUDIS);
}

/**
  * @brief  Set RTC_TAMPx precharge duration
  * @rmtoll TAFCR       TAMPPRCH      MS32_RTC_TAMPER_SetPrecharge
  * @param  RTCx RTC Instance
  * @param  Duration This parameter can be one of the following values:
  *         @arg @ref MS32_RTC_TAMPER_DURATION_1RTCCLK
  *         @arg @ref MS32_RTC_TAMPER_DURATION_2RTCCLK
  *         @arg @ref MS32_RTC_TAMPER_DURATION_4RTCCLK
  *         @arg @ref MS32_RTC_TAMPER_DURATION_8RTCCLK
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_TAMPER_SetPrecharge(RTC_TypeDef *RTCx, uint32_t Duration) {
  MODIFY_REG(RTCx->TAFCR, RTC_TAFCR_TAMPPRCH, Duration);
}

/**
  * @brief  Get RTC_TAMPx precharge duration
  * @rmtoll TAFCR       TAMPPRCH      MS32_RTC_TAMPER_GetPrecharge
  * @param  RTCx RTC Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_RTC_TAMPER_DURATION_1RTCCLK
  *         @arg @ref MS32_RTC_TAMPER_DURATION_2RTCCLK
  *         @arg @ref MS32_RTC_TAMPER_DURATION_4RTCCLK
  *         @arg @ref MS32_RTC_TAMPER_DURATION_8RTCCLK
  */
__STATIC_INLINE uint32_t MS32_RTC_TAMPER_GetPrecharge(RTC_TypeDef *RTCx) {
  return (uint32_t)(READ_BIT(RTCx->TAFCR, RTC_TAFCR_TAMPPRCH));
}

/**
  * @brief  Set RTC_TAMPx filter count
  * @rmtoll TAFCR       TAMPFLT       MS32_RTC_TAMPER_SetFilterCount
  * @param  RTCx RTC Instance
  * @param  FilterCount This parameter can be one of the following values:
  *         @arg @ref MS32_RTC_TAMPER_FILTER_DISABLE
  *         @arg @ref MS32_RTC_TAMPER_FILTER_2SAMPLE
  *         @arg @ref MS32_RTC_TAMPER_FILTER_4SAMPLE
  *         @arg @ref MS32_RTC_TAMPER_FILTER_8SAMPLE
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_TAMPER_SetFilterCount(RTC_TypeDef *RTCx, uint32_t FilterCount) {
  MODIFY_REG(RTCx->TAFCR, RTC_TAFCR_TAMPFLT, FilterCount);
}

/**
  * @brief  Get RTC_TAMPx filter count
  * @rmtoll TAFCR       TAMPFLT       MS32_RTC_TAMPER_GetFilterCount
  * @param  RTCx RTC Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_RTC_TAMPER_FILTER_DISABLE
  *         @arg @ref MS32_RTC_TAMPER_FILTER_2SAMPLE
  *         @arg @ref MS32_RTC_TAMPER_FILTER_4SAMPLE
  *         @arg @ref MS32_RTC_TAMPER_FILTER_8SAMPLE
  */
__STATIC_INLINE uint32_t MS32_RTC_TAMPER_GetFilterCount(RTC_TypeDef *RTCx) {
  return (uint32_t)(READ_BIT(RTCx->TAFCR, RTC_TAFCR_TAMPFLT));
}

/**
  * @brief  Set Tamper sampling frequency
  * @rmtoll TAFCR       TAMPFREQ      MS32_RTC_TAMPER_SetSamplingFreq
  * @param  RTCx RTC Instance
  * @param  SamplingFreq This parameter can be one of the following values:
  *         @arg @ref MS32_RTC_TAMPER_SAMPLFREQDIV_32768
  *         @arg @ref MS32_RTC_TAMPER_SAMPLFREQDIV_16384
  *         @arg @ref MS32_RTC_TAMPER_SAMPLFREQDIV_8192
  *         @arg @ref MS32_RTC_TAMPER_SAMPLFREQDIV_4096
  *         @arg @ref MS32_RTC_TAMPER_SAMPLFREQDIV_2048
  *         @arg @ref MS32_RTC_TAMPER_SAMPLFREQDIV_1024
  *         @arg @ref MS32_RTC_TAMPER_SAMPLFREQDIV_512
  *         @arg @ref MS32_RTC_TAMPER_SAMPLFREQDIV_256
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_TAMPER_SetSamplingFreq(RTC_TypeDef *RTCx, uint32_t SamplingFreq) {
  MODIFY_REG(RTCx->TAFCR, RTC_TAFCR_TAMPFREQ, SamplingFreq);
}

/**
  * @brief  Get Tamper sampling frequency
  * @rmtoll TAFCR       TAMPFREQ      MS32_RTC_TAMPER_GetSamplingFreq
  * @param  RTCx RTC Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_RTC_TAMPER_SAMPLFREQDIV_32768
  *         @arg @ref MS32_RTC_TAMPER_SAMPLFREQDIV_16384
  *         @arg @ref MS32_RTC_TAMPER_SAMPLFREQDIV_8192
  *         @arg @ref MS32_RTC_TAMPER_SAMPLFREQDIV_4096
  *         @arg @ref MS32_RTC_TAMPER_SAMPLFREQDIV_2048
  *         @arg @ref MS32_RTC_TAMPER_SAMPLFREQDIV_1024
  *         @arg @ref MS32_RTC_TAMPER_SAMPLFREQDIV_512
  *         @arg @ref MS32_RTC_TAMPER_SAMPLFREQDIV_256
  */
__STATIC_INLINE uint32_t MS32_RTC_TAMPER_GetSamplingFreq(RTC_TypeDef *RTCx) {
  return (uint32_t)(READ_BIT(RTCx->TAFCR, RTC_TAFCR_TAMPFREQ));
}

/**
  * @brief  Enable Active level for Tamper input
  * @rmtoll TAFCR       TAMP1TRG      MS32_RTC_TAMPER_EnableActiveLevel\n
  *         TAFCR       TAMP2TRG      MS32_RTC_TAMPER_EnableActiveLevel\n
  *         TAFCR       TAMP3TRG      MS32_RTC_TAMPER_EnableActiveLevel
  * @param  RTCx RTC Instance
  * @param  Tamper This parameter can be a combination of the following values:
  *         @arg @ref MS32_RTC_TAMPER_ACTIVELEVEL_TAMP1
  *         @arg @ref MS32_RTC_TAMPER_ACTIVELEVEL_TAMP2
  *         @arg @ref MS32_RTC_TAMPER_ACTIVELEVEL_TAMP3 (*)
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_TAMPER_EnableActiveLevel(RTC_TypeDef *RTCx, uint32_t Tamper) {
  SET_BIT(RTCx->TAFCR, Tamper);
}

/**
  * @brief  Disable Active level for Tamper input
  * @rmtoll TAFCR       TAMP1TRG      MS32_RTC_TAMPER_DisableActiveLevel\n
  *         TAFCR       TAMP2TRG      MS32_RTC_TAMPER_DisableActiveLevel\n
  *         TAFCR       TAMP3TRG      MS32_RTC_TAMPER_DisableActiveLevel
  * @param  RTCx RTC Instance
  * @param  Tamper This parameter can be a combination of the following values:
  *         @arg @ref MS32_RTC_TAMPER_ACTIVELEVEL_TAMP1
  *         @arg @ref MS32_RTC_TAMPER_ACTIVELEVEL_TAMP2
  *         @arg @ref MS32_RTC_TAMPER_ACTIVELEVEL_TAMP3 (*)
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_TAMPER_DisableActiveLevel(RTC_TypeDef *RTCx, uint32_t Tamper) {
  CLEAR_BIT(RTCx->TAFCR, Tamper);
}


/** @defgroup RTC_EF_Backup_Registers Backup_Registers
  * @{
  */

/**
  * @brief  Writes a data in a specified RTC Backup data register.
  * @rmtoll BKPxR        BKP           MS32_RTC_BAK_SetRegister
  * @param  RTCx RTC Instance
  * @param  BackupRegister This parameter can be one of the following values:
  *         @arg @ref MS32_RTC_BKP_DR0
  *         @arg @ref MS32_RTC_BKP_DR1
  *         @arg @ref MS32_RTC_BKP_DR2
  *         @arg @ref MS32_RTC_BKP_DR3
  *         @arg @ref MS32_RTC_BKP_DR4
  * @param  Data Value between Min_Data=0x00 and Max_Data=0xFFFFFFFF
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_BAK_SetRegister(RTC_TypeDef *RTCx, uint32_t BackupRegister, uint32_t Data) {
  register uint32_t tmp = 0U;

  tmp = (uint32_t)(&(RTCx->BKP0R));
  tmp += (BackupRegister * 4U);

  /* Write the specified register */
  *(__IO uint32_t *)tmp = (uint32_t)Data;
}

/**
  * @brief  Reads data from the specified RTC Backup data Register.
  * @rmtoll BKPxR        BKP           MS32_RTC_BAK_GetRegister
  * @param  RTCx RTC Instance
  * @param  BackupRegister This parameter can be one of the following values:
  *         @arg @ref MS32_RTC_BKP_DR0
  *         @arg @ref MS32_RTC_BKP_DR1
  *         @arg @ref MS32_RTC_BKP_DR2
  *         @arg @ref MS32_RTC_BKP_DR3
  *         @arg @ref MS32_RTC_BKP_DR4
  * @retval Value between Min_Data=0x00 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE uint32_t MS32_RTC_BAK_GetRegister(RTC_TypeDef *RTCx, uint32_t BackupRegister) {
  register uint32_t tmp = 0U;

  tmp = (uint32_t)(&(RTCx->BKP0R));
  tmp += (BackupRegister * 4U);

  /* Read the specified register */
  return (*(__IO uint32_t *)tmp);
}


/** @defgroup RTC_EF_Calibration Calibration
  * @{
  */

/**
  * @brief  Set Calibration output frequency (1 Hz or 512 Hz)
  * @note Bits are write-protected. @ref MS32_RTC_DisableWriteProtection function should be called before.
  * @rmtoll CR           COE           MS32_RTC_CAL_SetOutputFreq\n
  *         CR           COSEL         MS32_RTC_CAL_SetOutputFreq
  * @param  RTCx RTC Instance
  * @param  Frequency This parameter can be one of the following values:
  *         @arg @ref MS32_RTC_CALIB_OUTPUT_NONE
  *         @arg @ref MS32_RTC_CALIB_OUTPUT_1HZ
  *         @arg @ref MS32_RTC_CALIB_OUTPUT_512HZ
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_CAL_SetOutputFreq(RTC_TypeDef *RTCx, uint32_t Frequency) {
  MODIFY_REG(RTCx->CR, RTC_CR_COE | RTC_CR_COSEL, Frequency);
}

/**
  * @brief  Get Calibration output frequency (1 Hz or 512 Hz)
  * @rmtoll CR           COE           MS32_RTC_CAL_GetOutputFreq\n
  *         CR           COSEL         MS32_RTC_CAL_GetOutputFreq
  * @param  RTCx RTC Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_RTC_CALIB_OUTPUT_NONE
  *         @arg @ref MS32_RTC_CALIB_OUTPUT_1HZ
  *         @arg @ref MS32_RTC_CALIB_OUTPUT_512HZ
  */
__STATIC_INLINE uint32_t MS32_RTC_CAL_GetOutputFreq(RTC_TypeDef *RTCx) {
  return (uint32_t)(READ_BIT(RTCx->CR, RTC_CR_COE | RTC_CR_COSEL));
}

/**
  * @brief  Insert or not One RTCCLK pulse every 2exp11 pulses (frequency increased by 488.5 ppm)
  * @note   Bit is write-protected. @ref MS32_RTC_DisableWriteProtection function should be called before.
  * @note Bit can be written only when RECALPF is set to 0 in RTC_ISR
  * @rmtoll CALR         CALP          MS32_RTC_CAL_SetPulse
  * @param  RTCx RTC Instance
  * @param  Pulse This parameter can be one of the following values:
  *         @arg @ref MS32_RTC_CALIB_INSERTPULSE_NONE
  *         @arg @ref MS32_RTC_CALIB_INSERTPULSE_SET
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_CAL_SetPulse(RTC_TypeDef *RTCx, uint32_t Pulse) {
  MODIFY_REG(RTCx->CALR, RTC_CALR_CALP, Pulse);
}

/**
  * @brief  Check if one RTCCLK has been inserted or not every 2exp11 pulses (frequency increased by 488.5 ppm)
  * @rmtoll CALR         CALP          MS32_RTC_CAL_IsPulseInserted
  * @param  RTCx RTC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_RTC_CAL_IsPulseInserted(RTC_TypeDef *RTCx) {
  return (READ_BIT(RTCx->CALR, RTC_CALR_CALP) == (RTC_CALR_CALP));
}

/**
  * @brief  Set the calibration cycle period
  * @note   Bit is write-protected. @ref MS32_RTC_DisableWriteProtection function should be called before.
  * @note   Bit can be written only when RECALPF is set to 0 in RTC_ISR
  * @rmtoll CALR         CALW8         MS32_RTC_CAL_SetPeriod\n
  *         CALR         CALW16        MS32_RTC_CAL_SetPeriod
  * @param  RTCx RTC Instance
  * @param  Period This parameter can be one of the following values:
  *         @arg @ref MS32_RTC_CALIB_PERIOD_32SEC
  *         @arg @ref MS32_RTC_CALIB_PERIOD_16SEC
  *         @arg @ref MS32_RTC_CALIB_PERIOD_8SEC
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_CAL_SetPeriod(RTC_TypeDef *RTCx, uint32_t Period) {
  MODIFY_REG(RTCx->CALR, RTC_CALR_CALW8 | RTC_CALR_CALW16, Period);
}

/**
  * @brief  Get the calibration cycle period
  * @rmtoll CALR         CALW8         MS32_RTC_CAL_GetPeriod\n
  *         CALR         CALW16        MS32_RTC_CAL_GetPeriod
  * @param  RTCx RTC Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_RTC_CALIB_PERIOD_32SEC
  *         @arg @ref MS32_RTC_CALIB_PERIOD_16SEC
  *         @arg @ref MS32_RTC_CALIB_PERIOD_8SEC
  */
__STATIC_INLINE uint32_t MS32_RTC_CAL_GetPeriod(RTC_TypeDef *RTCx) {
  return (uint32_t)(READ_BIT(RTCx->CALR, RTC_CALR_CALW8 | RTC_CALR_CALW16));
}

/**
  * @brief  Set Calibration minus
  * @note   Bit is write-protected. @ref MS32_RTC_DisableWriteProtection function should be called before.
  * @note   Bit can be written only when RECALPF is set to 0 in RTC_ISR
  * @rmtoll CALR         CALM          MS32_RTC_CAL_SetMinus
  * @param  RTCx RTC Instance
  * @param  CalibMinus Value between Min_Data=0x00 and Max_Data=0x1FF
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_CAL_SetMinus(RTC_TypeDef *RTCx, uint32_t CalibMinus) {
  MODIFY_REG(RTCx->CALR, RTC_CALR_CALM, CalibMinus);
}

/**
  * @brief  Get Calibration minus
  * @rmtoll CALR         CALM          MS32_RTC_CAL_GetMinus
  * @param  RTCx RTC Instance
  * @retval Value between Min_Data=0x00 and Max_Data= 0x1FF
  */
__STATIC_INLINE uint32_t MS32_RTC_CAL_GetMinus(RTC_TypeDef *RTCx) {
  return (uint32_t)(READ_BIT(RTCx->CALR, RTC_CALR_CALM));
}


/** @defgroup RTC_EF_FLAG_Management FLAG_Management
  * @{
  */

/**
  * @brief  Get Recalibration pending Flag
  * @rmtoll ISR          RECALPF       MS32_RTC_IsActiveFlag_RECALP
  * @param  RTCx RTC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_RTC_IsActiveFlag_RECALP(RTC_TypeDef *RTCx) {
  return (READ_BIT(RTCx->ISR, RTC_ISR_RECALPF) == (RTC_ISR_RECALPF));
}

/**
  * @brief  Get RTC_TAMP2 detection flag
  * @rmtoll ISR          TAMP2F        MS32_RTC_IsActiveFlag_TAMP2
  * @param  RTCx RTC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_RTC_IsActiveFlag_TAMP2(RTC_TypeDef *RTCx) {
  return (READ_BIT(RTCx->ISR, RTC_ISR_TAMP2F) == (RTC_ISR_TAMP2F));
}

/**
  * @brief  Get RTC_TAMP1 detection flag
  * @rmtoll ISR          TAMP1F        MS32_RTC_IsActiveFlag_TAMP1
  * @param  RTCx RTC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_RTC_IsActiveFlag_TAMP1(RTC_TypeDef *RTCx) {
  return (READ_BIT(RTCx->ISR, RTC_ISR_TAMP1F) == (RTC_ISR_TAMP1F));
}

/**
  * @brief  Get Time-stamp overflow flag
  * @rmtoll ISR          TSOVF         MS32_RTC_IsActiveFlag_TSOV
  * @param  RTCx RTC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_RTC_IsActiveFlag_TSOV(RTC_TypeDef *RTCx) {
  return (READ_BIT(RTCx->ISR, RTC_ISR_TSOVF) == (RTC_ISR_TSOVF));
}

/**
  * @brief  Get Time-stamp flag
  * @rmtoll ISR          TSF           MS32_RTC_IsActiveFlag_TS
  * @param  RTCx RTC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_RTC_IsActiveFlag_TS(RTC_TypeDef *RTCx) {
  return (READ_BIT(RTCx->ISR, RTC_ISR_TSF) == (RTC_ISR_TSF));
}

/**
  * @brief  Get Alarm A flag
  * @rmtoll ISR          ALRAF         MS32_RTC_IsActiveFlag_ALRA
  * @param  RTCx RTC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_RTC_IsActiveFlag_ALRA(RTC_TypeDef *RTCx) {
  return (READ_BIT(RTCx->ISR, RTC_ISR_ALRAF) == (RTC_ISR_ALRAF));
}

/**
  * @brief  Clear RTC_TAMP2 detection flag
  * @rmtoll ISR          TAMP2F        MS32_RTC_ClearFlag_TAMP2
  * @param  RTCx RTC Instance
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_ClearFlag_TAMP2(RTC_TypeDef *RTCx) {
  WRITE_REG(RTCx->ISR, (~((RTC_ISR_TAMP2F | RTC_ISR_INIT) & 0x0000FFFFU) | (RTCx->ISR & RTC_ISR_INIT)));
}

/**
  * @brief  Clear RTC_TAMP1 detection flag
  * @rmtoll ISR          TAMP1F        MS32_RTC_ClearFlag_TAMP1
  * @param  RTCx RTC Instance
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_ClearFlag_TAMP1(RTC_TypeDef *RTCx) {
  WRITE_REG(RTCx->ISR, (~((RTC_ISR_TAMP1F | RTC_ISR_INIT) & 0x0000FFFFU) | (RTCx->ISR & RTC_ISR_INIT)));
}

/**
  * @brief  Clear Time-stamp overflow flag
  * @rmtoll ISR          TSOVF         MS32_RTC_ClearFlag_TSOV
  * @param  RTCx RTC Instance
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_ClearFlag_TSOV(RTC_TypeDef *RTCx) {
  WRITE_REG(RTCx->ISR, (~((RTC_ISR_TSOVF | RTC_ISR_INIT) & 0x0000FFFFU) | (RTCx->ISR & RTC_ISR_INIT)));
}

/**
  * @brief  Clear Time-stamp flag
  * @rmtoll ISR          TSF           MS32_RTC_ClearFlag_TS
  * @param  RTCx RTC Instance
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_ClearFlag_TS(RTC_TypeDef *RTCx) {
  WRITE_REG(RTCx->ISR, (~((RTC_ISR_TSF | RTC_ISR_INIT) & 0x0000FFFFU) | (RTCx->ISR & RTC_ISR_INIT)));
}

/**
  * @brief  Clear Alarm A flag
  * @rmtoll ISR          ALRAF         MS32_RTC_ClearFlag_ALRA
  * @param  RTCx RTC Instance
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_ClearFlag_ALRA(RTC_TypeDef *RTCx) {
  WRITE_REG(RTCx->ISR, (~((RTC_ISR_ALRAF | RTC_ISR_INIT) & 0x0000FFFFU) | (RTCx->ISR & RTC_ISR_INIT)));
}

/**
  * @brief  Get Initialization flag
  * @rmtoll ISR          INITF         MS32_RTC_IsActiveFlag_INIT
  * @param  RTCx RTC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_RTC_IsActiveFlag_INIT(RTC_TypeDef *RTCx) {
  return (READ_BIT(RTCx->ISR, RTC_ISR_INITF) == (RTC_ISR_INITF));
}

/**
  * @brief  Get Registers synchronization flag
  * @rmtoll ISR          RSF           MS32_RTC_IsActiveFlag_RS
  * @param  RTCx RTC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_RTC_IsActiveFlag_RS(RTC_TypeDef *RTCx) {
  return (READ_BIT(RTCx->ISR, RTC_ISR_RSF) == (RTC_ISR_RSF));
}

/**
  * @brief  Clear Registers synchronization flag
  * @rmtoll ISR          RSF           MS32_RTC_ClearFlag_RS
  * @param  RTCx RTC Instance
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_ClearFlag_RS(RTC_TypeDef *RTCx) {
  WRITE_REG(RTCx->ISR, (~((RTC_ISR_RSF | RTC_ISR_INIT) & 0x0000FFFFU) | (RTCx->ISR & RTC_ISR_INIT)));
}

/**
  * @brief  Get Initialization status flag
  * @rmtoll ISR          INITS         MS32_RTC_IsActiveFlag_INITS
  * @param  RTCx RTC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_RTC_IsActiveFlag_INITS(RTC_TypeDef *RTCx) {
  return (READ_BIT(RTCx->ISR, RTC_ISR_INITS) == (RTC_ISR_INITS));
}

/**
  * @brief  Get Shift operation pending flag
  * @rmtoll ISR          SHPF          MS32_RTC_IsActiveFlag_SHP
  * @param  RTCx RTC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_RTC_IsActiveFlag_SHP(RTC_TypeDef *RTCx) {
  return (READ_BIT(RTCx->ISR, RTC_ISR_SHPF) == (RTC_ISR_SHPF));
}

/**
  * @brief  Get Alarm A write flag
  * @rmtoll ISR          ALRAWF        MS32_RTC_IsActiveFlag_ALRAW
  * @param  RTCx RTC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_RTC_IsActiveFlag_ALRAW(RTC_TypeDef *RTCx) {
  return (READ_BIT(RTCx->ISR, RTC_ISR_ALRAWF) == (RTC_ISR_ALRAWF));
}


/** @defgroup RTC_EF_IT_Management IT_Management
  * @{
  */

/**
  * @brief  Enable Time-stamp interrupt
  * @note   Bit is write-protected. @ref MS32_RTC_DisableWriteProtection function should be called before.
  * @rmtoll CR           TSIE          MS32_RTC_EnableIT_TS
  * @param  RTCx RTC Instance
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_EnableIT_TS(RTC_TypeDef *RTCx) {
  SET_BIT(RTCx->CR, RTC_CR_TSIE);
}

/**
  * @brief  Disable Time-stamp interrupt
  * @note   Bit is write-protected. @ref MS32_RTC_DisableWriteProtection function should be called before.
  * @rmtoll CR           TSIE          MS32_RTC_DisableIT_TS
  * @param  RTCx RTC Instance
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_DisableIT_TS(RTC_TypeDef *RTCx) {
  CLEAR_BIT(RTCx->CR, RTC_CR_TSIE);
}

/**
  * @brief  Enable Alarm A interrupt
  * @note   Bit is write-protected. @ref MS32_RTC_DisableWriteProtection function should be called before.
  * @rmtoll CR           ALRAIE        MS32_RTC_EnableIT_ALRA
  * @param  RTCx RTC Instance
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_EnableIT_ALRA(RTC_TypeDef *RTCx) {
  SET_BIT(RTCx->CR, RTC_CR_ALRAIE);
}

/**
  * @brief  Disable Alarm A interrupt
  * @note   Bit is write-protected. @ref MS32_RTC_DisableWriteProtection function should be called before.
  * @rmtoll CR           ALRAIE        MS32_RTC_DisableIT_ALRA
  * @param  RTCx RTC Instance
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_DisableIT_ALRA(RTC_TypeDef *RTCx) {
  CLEAR_BIT(RTCx->CR, RTC_CR_ALRAIE);
}

/**
  * @brief  Enable all Tamper Interrupt
  * @rmtoll TAFCR       TAMPIE        MS32_RTC_EnableIT_TAMP
  * @param  RTCx RTC Instance
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_EnableIT_TAMP(RTC_TypeDef *RTCx) {
  SET_BIT(RTCx->TAFCR, RTC_TAFCR_TAMPIE);
}

/**
  * @brief  Disable all Tamper Interrupt
  * @rmtoll TAFCR       TAMPIE        MS32_RTC_DisableIT_TAMP
  * @param  RTCx RTC Instance
  * @retval None
  */
__STATIC_INLINE void MS32_RTC_DisableIT_TAMP(RTC_TypeDef *RTCx) {
  CLEAR_BIT(RTCx->TAFCR, RTC_TAFCR_TAMPIE);
}

/**
  * @brief  Check if  Time-stamp interrupt is enabled or not
  * @rmtoll CR           TSIE          MS32_RTC_IsEnabledIT_TS
  * @param  RTCx RTC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_RTC_IsEnabledIT_TS(RTC_TypeDef *RTCx) {
  return (READ_BIT(RTCx->CR, RTC_CR_TSIE) == (RTC_CR_TSIE));
}

/**
  * @brief  Check if  Alarm A interrupt is enabled or not
  * @rmtoll CR           ALRAIE        MS32_RTC_IsEnabledIT_ALRA
  * @param  RTCx RTC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_RTC_IsEnabledIT_ALRA(RTC_TypeDef *RTCx) {
  return (READ_BIT(RTCx->CR, RTC_CR_ALRAIE) == (RTC_CR_ALRAIE));
}

/**
  * @brief  Check if all the TAMPER interrupts are enabled or not
  * @rmtoll TAFCR       TAMPIE        MS32_RTC_IsEnabledIT_TAMP
  * @param  RTCx RTC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_RTC_IsEnabledIT_TAMP(RTC_TypeDef *RTCx) {
  return (READ_BIT(RTCx->TAFCR,
                   RTC_TAFCR_TAMPIE) == (RTC_TAFCR_TAMPIE));
}


/** @defgroup RTC_EF_Init Initialization and de-initialization functions
  * @{
  */
ErrorStatus MS32_RTC_ClockInit      (uint32_t RtcClock);
ErrorStatus MS32_RTC_DeInit         (RTC_TypeDef *RTCx);
void        MS32_RTC_StructInit     (MS32_RTC_InitTypeDef *RtcInitStr);
ErrorStatus MS32_RTC_Init           (RTC_TypeDef *RTCx, MS32_RTC_InitTypeDef *RtcInitStr, uint32_t RefInEn, uint32_t CoeFunc);
void        MS32_RTC_ITConfig       (RTC_TypeDef *RTCx, uint32_t InterruptFunc, uint32_t Priority);

ErrorStatus MS32_RTC_SetTime        (RTC_TypeDef *RTCx, uint32_t RtcFormat, MS32_RTC_TimeTypeDef *RtcTimeStr, uint32_t ShadowBypassEn);
void        MS32_RTC_GetTime        (RTC_TypeDef *RTCx, MS32_RTC_TimeTypeDef *RtcTimeStr);
ErrorStatus MS32_RTC_SetDate        (RTC_TypeDef *RTCx, uint32_t RtcFormat, MS32_RTC_DateTypeDef *RtcDateStr);
void        MS32_RTC_GetDate        (RTC_TypeDef *RTCx, MS32_RTC_DateTypeDef *RtcDateStr);
ErrorStatus MS32_RTC_SetAlarm       (RTC_TypeDef *RTCx, uint32_t RtcFormat, MS32_RTC_AlarmTypeDef *RtcAlarmStr);
void        MS32_RTC_GetAlarm       (RTC_TypeDef *RTCx, MS32_RTC_AlarmTypeDef *RtcAlarmStr);
void        MS32_RTC_GetTimStamp    (RTC_TypeDef *RTCx, MS32_RTC_TimStampTypeDef *RtcTimStampStr);

void        MS32_RTC_AlarmConfig    (RTC_TypeDef *RTCx, uint32_t AlarmOutEn, uint32_t AlarmOutPol, FunctionalState AlarmEn);
void        MS32_RTC_TimStampConfig (RTC_TypeDef *RTCx, uint32_t TimStampEn, uint32_t TimStampEdge);
void        MS32_RTC_TampConfig     (RTC_TypeDef *RTCx, uint32_t TampPu, uint32_t TampPre, uint32_t TampFlt, uint32_t );

/** @defgroup RTC_EF_Application function
  * @{
  */
FlagStatus  MS32_RTC_GetStatusFlag  (RTC_TypeDef *RTCx, uint32_t Flags);
void        MS32_RTC_ChangeOneHour  (RTC_TypeDef *RTCx, uint32_t Effect);
void        MS32_RTC_ShiftSec       (RTC_TypeDef *RTCx, uint32_t ShiftSecond, uint16_t Fraction);
void        MS32_RTC_Cal            (RTC_TypeDef *RTCx, uint32_t InsertPulse, uint32_t Period, uint16_t CalMin);
void        MS32_RTC_SetPin         (RTC_TypeDef *RTCx, uint32_t Pin, uint32_t Level);
ErrorStatus MS32_RTC_EnterInitMode  (RTC_TypeDef *RTCx);
ErrorStatus MS32_RTC_ExitInitMode   (RTC_TypeDef *RTCx);
ErrorStatus MS32_RTC_WaitForSynchro (RTC_TypeDef *RTCx);


#endif /* __MS32F0XX_RTC_H */

/******************************** END OF FILE *********************************/
