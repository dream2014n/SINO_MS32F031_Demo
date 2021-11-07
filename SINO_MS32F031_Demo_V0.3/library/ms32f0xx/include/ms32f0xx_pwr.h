/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MS32F0XX_PWR_H
#define __MS32F0XX_PWR_H

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
/** @defgroup MS32_PWR_Exported_Types PWR Exported Types
  * @{
  */

/**
  * @brief PWR Init Structure definition
  */
typedef struct {
  uint32_t BackupAccessStatus;     /*!< The new state of the backup access write protection.
                                        This parameter can be a value of @ref PWR_EC_BKUP_ACCESS */
  uint32_t WakeupPin;              /*!< The new state of the wakeup pin.
                                        This parameter can be a value of @ref PWR_EC_WAKEUP_PIN */
  uint32_t PowerVoltDetectSel;     /*!< The new state of the power voltage detector and selection.
                                        This parameter can be a value of @ref PWR_EC_PVDLEVEL */
  uint32_t PowerVoltDetectLock;    /*!< The new state of the power voltage detector and selection.
                                        This parameter can be a value of @ref SYSCFG_EC_PVD_LOCK */          
} MS32_PWR_InitTypeDef;


/* Exported constants --------------------------------------------------------*/
/** @defgroup MS32_PWR_Exported_Constants PWR Exported Constants
  * @{
  */

/** @defgroup PWR_EC_BKUP_ACCESS  Access to RTC and Backup
  * @{
  */
#define MS32_PWR_BKUPACC_DIS                 (0x00000000U) /*!< Access to RTC and Backup registers disabled */
#define MS32_PWR_BKUPACC_EN                  PWR_CR_DBP    /*!< Access to RTC and Backup registers enabled  */


/** @defgroup PWR_EC_PVDLEVEL Power Voltage Detector Level
  * @{
  */
#define MS32_PWR_PVDOFF                      (0x00000000U)                   /*!< Voltage threshold off */
#define MS32_PWR_PVDON_LEVEL0                (PWR_CR_PLS_LEV0 | PWR_CR_PVDE) /*!< Voltage threshold 0   */
#define MS32_PWR_PVDON_LEVEL1                (PWR_CR_PLS_LEV1 | PWR_CR_PVDE) /*!< Voltage threshold 1   */
#define MS32_PWR_PVDON_LEVEL2                (PWR_CR_PLS_LEV2 | PWR_CR_PVDE) /*!< Voltage threshold 2   */
#define MS32_PWR_PVDON_LEVEL3                (PWR_CR_PLS_LEV3 | PWR_CR_PVDE) /*!< Voltage threshold 3   */
#define MS32_PWR_PVDON_LEVEL4                (PWR_CR_PLS_LEV4 | PWR_CR_PVDE) /*!< Voltage threshold 4   */
#define MS32_PWR_PVDON_LEVEL5                (PWR_CR_PLS_LEV5 | PWR_CR_PVDE) /*!< Voltage threshold 5   */
#define MS32_PWR_PVDON_LEVEL6                (PWR_CR_PLS_LEV6 | PWR_CR_PVDE) /*!< Voltage threshold 6   */
#define MS32_PWR_PVDON_LEVEL7                (PWR_CR_PLS_LEV7 | PWR_CR_PVDE) /*!< Voltage threshold 7   */


/** @defgroup PWR_EC_WAKEUP_PIN  Wakeup Pins
  * @{
  */
#define MS32_PWR_WAKEUP_NONE                 (0x00000000U)          /*!< No WKUP pin */
#define MS32_PWR_WAKEUP_PIN1                 PWR_CSR_EWUP1          /*!< WKUP pin 1 : PA0 */
#define MS32_PWR_WAKEUP_PIN2                 PWR_CSR_EWUP2          /*!< WKUP pin 2 : PC13 */


/** @defgroup PWR_EC_STATE_STOP_mode PWR Regulator state in STOP mode
  * @{
  */
#define PWR_MAINREGULATOR_ON                 (0x00000000U)
#define PWR_LOWPOWERREGULATOR_ON             PWR_CR_LPDS


/** @defgroup SYSCFG_EC_PVD_LOCK Sysclk PVD lock
  * @{
  */
#define MS32_SYSCFG_PVD_UNLOCK               (0x00000000U)          /*!< PVD unlock without time break */
#define MS32_SYSCFG_PVD_LOCK                 SYSCFG_CFGR2_PVD_LOCK  /*!< PVD lock with time break   */


/** @defgroup PWR_SLEEP_mode_entry PWR SLEEP mode entry
  * @{
  */
#define PWR_SLEEPENTRY_WFI                   (0x00000001U)
#define PWR_SLEEPENTRY_WFE                   (0x00000002U)


/** @defgroup PWR_STOP_mode_entry PWR STOP mode entry
  * @{
  */
#define PWR_STOPENTRY_WFI                    (0x00000001U)
#define PWR_STOPENTRY_WFE                    (0x00000002U)


/** @defgroup PWR_EC_MODE_PWR Mode Power
  * @{
  */
#define MS32_PWR_MODE_STOP_MAINREGU          (0x00000000U)          /*!< Enter Stop mode when the CPU enters deepsleep */
#define MS32_PWR_MODE_STOP_LPREGU            PWR_CR_LPDS            /*!< Enter Stop mode (with low power Regulator ON) when the CPU enters deepsleep */
#define MS32_PWR_MODE_STANDBY                PWR_CR_PDDS            /*!< Enter Standby mode when the CPU enters deepsleep */

#define MS32_PWR_REGU_DSMODE_MAIN            (0x00000000U)          /*!< Voltage Regulator in main mode during deepsleep mode */
#define MS32_PWR_REGU_DSMODE_LOW_POWER       PWR_CR_LPDS            /*!< Voltage Regulator in low-power mode during deepsleep mode */


/** @defgroup PWR_EC_CLEAR_FLAG Clear Flags Defines
  * @{
  */
#define MS32_PWR_CR_CWUF                     PWR_CR_CWUF            /*!< Clear wakeup flag  */
#define MS32_PWR_CR_CSBF                     PWR_CR_CSBF            /*!< Clear standby flag */


/** @defgroup PWR_EC_GET_FLAG Get Flags Defines
  * @{
  */
#define MS32_PWR_CSR_WUF                     PWR_CSR_WUF            /*!< Wakeup flag */
#define MS32_PWR_CSR_SBF                     PWR_CSR_SBF            /*!< Standby flag */
#define MS32_PWR_CSR_PVDO                    PWR_CSR_PVDO           /*!< Power voltage detector output flag */


/** @defgroup PWR_PVDI_Mode PWR power voltage detector interrupt Mode
  * @{
  */
#define MS32_PWR_PVDIT_DISABLE               (0x00000000U)          /*!< PVD interrupt disable */
#define MS32_PWR_PVDIT_ENABLE                (0x00000001U)          /*!< PVD interrupt enable */

/** @defgroup PWR_EC_PVDLEVEL Power Voltage Detector Level
  * @{
  */
#define MS32_PWR_PVDLEVEL_0                (PWR_CR_PLS_LEV0)      /*!< Voltage threshold 0   */
#define MS32_PWR_PVDLEVEL_1                (PWR_CR_PLS_LEV1)      /*!< Voltage threshold 1   */
#define MS32_PWR_PVDLEVEL_2                (PWR_CR_PLS_LEV2)      /*!< Voltage threshold 2   */
#define MS32_PWR_PVDLEVEL_3                (PWR_CR_PLS_LEV3)      /*!< Voltage threshold 3   */
#define MS32_PWR_PVDLEVEL_4                (PWR_CR_PLS_LEV4)      /*!< Voltage threshold 4   */
#define MS32_PWR_PVDLEVEL_5                (PWR_CR_PLS_LEV5)      /*!< Voltage threshold 5   */
#define MS32_PWR_PVDLEVEL_6                (PWR_CR_PLS_LEV6)      /*!< Voltage threshold 6   */
#define MS32_PWR_PVDLEVEL_7                (PWR_CR_PLS_LEV7)      /*!< Voltage threshold 7   */


/* Exported macro ------------------------------------------------------------*/
/** @defgroup PWR_EM_WRITE_READ Common write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in PWR register
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define MS32_PWR_WriteReg(__REG__, __VALUE__) WRITE_REG(PWR->__REG__, (__VALUE__))

/**
  * @brief  Read a value in PWR register
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define MS32_PWR_ReadReg(__REG__) READ_REG(PWR->__REG__)


/* Exported functions --------------------------------------------------------*/
/** @defgroup PWR_EF_Configuration Configuration
  * @{
  */

/**
  * @brief  Enable access to the backup domain
  * @rmtoll CR    DBP       MS32_PWR_EnableBkUpAccess
  * @retval None
  */
__STATIC_INLINE void MS32_PWR_EnableBkUpAccess(void) {
  SET_BIT(PWR->CR, PWR_CR_DBP);
}

/**
  * @brief  Disable access to the backup domain
  * @rmtoll CR    DBP       MS32_PWR_DisableBkUpAccess
  * @retval None
  */
__STATIC_INLINE void MS32_PWR_DisableBkUpAccess(void) {
  CLEAR_BIT(PWR->CR, PWR_CR_DBP);
}

/**
  * @brief  Check if the backup domain is enabled
  * @rmtoll CR    DBP       MS32_PWR_IsEnabledBkUpAccess
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_PWR_IsEnabledBkUpAccess(void) {
  return (READ_BIT(PWR->CR, PWR_CR_DBP) == (PWR_CR_DBP));
}

/**
  * @brief  Set voltage Regulator mode during deep sleep mode
  * @rmtoll CR    LPDS         MS32_PWR_SetRegulModeDS
  * @param  RegulMode This parameter can be one of the following values:
  *         @arg @ref MS32_PWR_REGU_DSMODE_MAIN
  *         @arg @ref MS32_PWR_REGU_DSMODE_LOW_POWER
  * @retval None
  */
__STATIC_INLINE void MS32_PWR_SetRegulModeDS(uint32_t RegulMode) {
  MODIFY_REG(PWR->CR, PWR_CR_LPDS, RegulMode);
}

/**
  * @brief  Get voltage Regulator mode during deep sleep mode
  * @rmtoll CR    LPDS         MS32_PWR_GetRegulModeDS
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_PWR_REGU_DSMODE_MAIN
  *         @arg @ref MS32_PWR_REGU_DSMODE_LOW_POWER
  */
__STATIC_INLINE uint32_t MS32_PWR_GetRegulModeDS(void) {
  return (uint32_t)(READ_BIT(PWR->CR, PWR_CR_LPDS));
}

/**
  * @brief  Set Power Down mode when CPU enters deepsleep
  * @rmtoll CR    PDDS         MS32_PWR_SetPowerMode\n
  * @rmtoll CR    LPDS         MS32_PWR_SetPowerMode
  * @param  PDMode This parameter can be one of the following values:
  *         @arg @ref MS32_PWR_MODE_STOP_MAINREGU
  *         @arg @ref MS32_PWR_MODE_STOP_LPREGU
  *         @arg @ref MS32_PWR_MODE_STANDBY
  * @retval None
  */
__STATIC_INLINE void MS32_PWR_SetPowerMode(uint32_t PDMode) {
  MODIFY_REG(PWR->CR, (PWR_CR_PDDS | PWR_CR_LPDS), PDMode);
}

/**
  * @brief  Get Power Down mode when CPU enters deepsleep
  * @rmtoll CR    PDDS         MS32_PWR_GetPowerMode\n
  * @rmtoll CR    LPDS         MS32_PWR_GetPowerMode
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_PWR_MODE_STOP_MAINREGU
  *         @arg @ref MS32_PWR_MODE_STOP_LPREGU
  *         @arg @ref MS32_PWR_MODE_STANDBY
  */
__STATIC_INLINE uint32_t MS32_PWR_GetPowerMode(void) {
  return (uint32_t)(READ_BIT(PWR->CR, (PWR_CR_PDDS | PWR_CR_LPDS)));
}

/**
  * @brief  Configure the voltage threshold detected by the Power Voltage Detector
  * @rmtoll CR    PLS       MS32_PWR_SetPVDLevel
  * @param  PVDLevel This parameter can be one of the following values:
  *         @arg @ref MS32_PWR_PVDLEVEL_0
  *         @arg @ref MS32_PWR_PVDLEVEL_1
  *         @arg @ref MS32_PWR_PVDLEVEL_2
  *         @arg @ref MS32_PWR_PVDLEVEL_3
  *         @arg @ref MS32_PWR_PVDLEVEL_4
  *         @arg @ref MS32_PWR_PVDLEVEL_5
  *         @arg @ref MS32_PWR_PVDLEVEL_6
  *         @arg @ref MS32_PWR_PVDLEVEL_7
  * @retval None
  */
__STATIC_INLINE void MS32_PWR_SetPVDLevel(uint32_t PVDLevel) {
  MODIFY_REG(PWR->CR, PWR_CR_PLS, PVDLevel);
}

/**
  * @brief  Get the voltage threshold detection
  * @rmtoll CR    PLS       MS32_PWR_GetPVDLevel
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_PWR_PVDLEVEL_0
  *         @arg @ref MS32_PWR_PVDLEVEL_1
  *         @arg @ref MS32_PWR_PVDLEVEL_2
  *         @arg @ref MS32_PWR_PVDLEVEL_3
  *         @arg @ref MS32_PWR_PVDLEVEL_4
  *         @arg @ref MS32_PWR_PVDLEVEL_5
  *         @arg @ref MS32_PWR_PVDLEVEL_6
  *         @arg @ref MS32_PWR_PVDLEVEL_7
  */
__STATIC_INLINE uint32_t MS32_PWR_GetPVDLevel(void) {
  return (uint32_t)(READ_BIT(PWR->CR, PWR_CR_PLS));
}

/**
  * @brief  Enable Power Voltage Detector
  * @rmtoll CR    PVDE       MS32_PWR_EnablePVD
  * @retval None
  */
__STATIC_INLINE void MS32_PWR_EnablePVD(void) {
  SET_BIT(PWR->CR, PWR_CR_PVDE);
}

/**
  * @brief  Disable Power Voltage Detector
  * @rmtoll CR    PVDE       MS32_PWR_DisablePVD
  * @retval None
  */
__STATIC_INLINE void MS32_PWR_DisablePVD(void) {
  CLEAR_BIT(PWR->CR, PWR_CR_PVDE);
}

/**
  * @brief  Check if Power Voltage Detector is enabled
  * @rmtoll CR    PVDE       MS32_PWR_IsEnabledPVD
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_PWR_IsEnabledPVD(void) {
  return (READ_BIT(PWR->CR, PWR_CR_PVDE) == (PWR_CR_PVDE));
}

/**
  * @brief  Enable the WakeUp PINx functionality
  * @rmtoll CSR   EWUP1       MS32_PWR_EnableWakeUpPin\n
  * @rmtoll CSR   EWUP2       MS32_PWR_EnableWakeUpPin
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref MS32_PWR_WAKEUP_PIN1
  *         @arg @ref MS32_PWR_WAKEUP_PIN2
  * @retval None
  */
__STATIC_INLINE void MS32_PWR_EnableWakeUpPin(uint32_t WakeUpPin) {
  SET_BIT(PWR->CSR, WakeUpPin);
}

/**
  * @brief  Disable the WakeUp PINx functionality
  * @rmtoll CSR   EWUP1       MS32_PWR_DisableWakeUpPin\n
  * @rmtoll CSR   EWUP2       MS32_PWR_DisableWakeUpPin
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref MS32_PWR_WAKEUP_PIN1
  *         @arg @ref MS32_PWR_WAKEUP_PIN2
  * @retval None
  */
__STATIC_INLINE void MS32_PWR_DisableWakeUpPin(uint32_t WakeUpPin) {
  CLEAR_BIT(PWR->CSR, WakeUpPin);
}

/**
  * @brief  Check if the WakeUp PINx functionality is enabled
  * @rmtoll CSR   EWUP1       MS32_PWR_IsEnabledWakeUpPin\n
  * @rmtoll CSR   EWUP2       MS32_PWR_IsEnabledWakeUpPin
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref MS32_PWR_WAKEUP_PIN1
  *         @arg @ref MS32_PWR_WAKEUP_PIN2
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_PWR_IsEnabledWakeUpPin(uint32_t WakeUpPin) {
  return (READ_BIT(PWR->CSR, WakeUpPin) == (WakeUpPin));
}


/** @defgroup PWR_EF_FLAG_Management FLAG_Management
  * @{
  */

/**
  * @brief  Get Wake-up Flag
  * @rmtoll CSR   WUF       MS32_PWR_IsActiveFlag_WU
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_PWR_IsActiveFlag_WU(void) {
  return (READ_BIT(PWR->CSR, PWR_CSR_WUF) == (PWR_CSR_WUF));
}

/**
  * @brief  Get Standby Flag
  * @rmtoll CSR   SBF       MS32_PWR_IsActiveFlag_SB
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_PWR_IsActiveFlag_SB(void) {
  return (READ_BIT(PWR->CSR, PWR_CSR_SBF) == (PWR_CSR_SBF));
}

/**
  * @brief  Indicate whether VDD voltage is below the selected PVD threshold
  * @rmtoll CSR   PVDO       MS32_PWR_IsActiveFlag_PVDO
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_PWR_IsActiveFlag_PVDO(void) {
  return (READ_BIT(PWR->CSR, PWR_CSR_PVDO) == (PWR_CSR_PVDO));
}

/**
  * @brief  Clear Standby Flag
  * @rmtoll CR   CSBF       MS32_PWR_ClearFlag_SB
  * @retval None
  */
__STATIC_INLINE void MS32_PWR_ClearFlag_SB(void) {
  SET_BIT(PWR->CR, PWR_CR_CSBF);
}

/**
  * @brief  Clear Wake-up Flags
  * @rmtoll CR   CWUF       MS32_PWR_ClearFlag_WU
  * @retval None
  */
__STATIC_INLINE void MS32_PWR_ClearFlag_WU(void) {
  SET_BIT(PWR->CR, PWR_CR_CWUF);
}


/** @defgroup PWR_EF_Init Initialization and de-initialization functions
  * @{
  */
ErrorStatus MS32_PWR_DeInit     (void);
void        MS32_PWR_StructInit (MS32_PWR_InitTypeDef *PwrInitStr);
ErrorStatus MS32_PWR_Init       (MS32_PWR_InitTypeDef *PwrInitStr);
void        MS32_PWR_ITConfig   (uint32_t InterruptFunc, uint32_t Priority);

/** @defgroup PWR_EF_Application function
  * @{
  */
FlagStatus MS32_PWR_GetStatusFlag    (uint32_t Flags);
void       MS32_PWR_EnterSLEEPMode   (uint32_t SLEEPEntry);
void       MS32_PWR_EnterSTOPMode    (uint32_t Regulator, uint8_t STOPEntry);
void       MS32_PWR_EnterSTANDBYMode (void);


#ifdef __cplusplus
}
#endif

#endif /* __MS32F0XX_PWR_H */

/******************************** END OF FILE *********************************/
