/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MS32F0XX_WWDG_H
#define __MS32F0XX_WWDG_H

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
/** @defgroup WWDG_Exported_Types WWDG Exported Types
  * @{
  */

/**
  * @brief  WWDG Init structure definition
  */
typedef struct {
  uint32_t Prescaler;     /*!< Specifies the prescaler value of the WWDG.
                               This parameter can be a value of @ref WWDG_Prescaler */
  uint32_t Window;        /*!< Specifies the WWDG window value to be compared to the downcounter.
                               This parameter must be a number Min_Data = 0x40 and Max_Data = 0x7F */
  uint32_t Counter;       /*!< Specifies the WWDG free-running downcounter value.
                               This parameter must be a number between Min_Data = 0x40 and Max_Data = 0x7F */
} MS32_WWDG_InitTypeDef;


/* Exported constants --------------------------------------------------------*/
/** @defgroup WWDG_Exported_Constants WWDG Exported Constants
  * @{
  */

/** @defgroup WWDG_Flag_definition WWDG Flag definition
  * @brief WWDG Flag definition
  * @{
  */
#define MS32_WWDG_FLAG_EWIF                 WWDG_SR_EWIF /*!< Early wakeup interrupt flag */


/** @defgroup WWDG_Prescaler  PRESCALER
  * @{
  */
#define MS32_WWDG_PRESCALER_1               (0x00000000U)                         /*!< WWDG counter clock = (PCLK1/4096)/1 */
#define MS32_WWDG_PRESCALER_2               WWDG_CFR_WDGTB_0                      /*!< WWDG counter clock = (PCLK1/4096)/2 */
#define MS32_WWDG_PRESCALER_4               WWDG_CFR_WDGTB_1                      /*!< WWDG counter clock = (PCLK1/4096)/4 */
#define MS32_WWDG_PRESCALER_8               (WWDG_CFR_WDGTB_0 | WWDG_CFR_WDGTB_1) /*!< WWDG counter clock = (PCLK1/4096)/8 */


/** @defgroup WWDG_EWI_Mode WWDG Early Wakeup Interrupt Mode
  * @{
  */
#define MS32_WWDG_EWI_DISABLE               (0x00000000U)     /*!< EWI Disable */
#define MS32_WWDG_EWI_ENABLE                WWDG_CFR_EWI      /*!< EWI Enable */


/* Exported macro ------------------------------------------------------------*/
/** @defgroup WWDG_EM_WRITE_READ Common Write and read registers macros
  * @{
  */

/**
  * @brief  Write a value in WWDG register
  * @param  __INSTANCE__ WWDG Instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define MS32_WWDG_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, (__VALUE__))

/**
  * @brief  Read a value in WWDG register
  * @param  __INSTANCE__ WWDG Instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define MS32_WWDG_ReadReg(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)


/* Exported functions --------------------------------------------------------*/
/** @defgroup WWDG_EF_Configuration Configuration
  * @{
  */

/**
  * @brief  Enable Window Watchdog. The watchdog is always disabled after a reset.
  * @note   It is enabled by setting the WDGA bit in the WWDG_CR register,
  *         then it cannot be disabled again except by a reset.
  *         This bit is set by software and only cleared by hardware after a reset.
  *         When WDGA = 1, the watchdog can generate a reset.
  * @rmtoll CR           WDGA          MS32_WWDG_Enable
  * @param  WWDGx WWDG Instance
  * @retval None
  */
__STATIC_INLINE void MS32_WWDG_Enable(WWDG_TypeDef *WWDGx) {
  SET_BIT(WWDGx->CR, WWDG_CR_WDGA);
}

/**
  * @brief  Checks if Window Watchdog is enabled
  * @rmtoll CR           WDGA          MS32_WWDG_IsEnabled
  * @param  WWDGx WWDG Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_WWDG_IsEnabled(WWDG_TypeDef *WWDGx) {
  return ((READ_BIT(WWDGx->CR, WWDG_CR_WDGA) == (WWDG_CR_WDGA)) ? 1UL : 0UL);
}

/**
  * @brief  Set the Watchdog counter value to provided value (7-bits T[6:0])
  * @note   When writing to the WWDG_CR register, always write 1 in the MSB b6 to avoid generating an immediate reset
  *         This counter is decremented every (4096 x 2expWDGTB) PCLK cycles
  *         A reset is produced when it rolls over from 0x40 to 0x3F (bit T6 becomes cleared)
  *         Setting the counter lower then 0x40 causes an immediate reset (if WWDG enabled)
  * @rmtoll CR           T             MS32_WWDG_SetCounter
  * @param  WWDGx WWDG Instance
  * @param  Counter 0..0x7F (7 bit counter value)
  * @retval None
  */
__STATIC_INLINE void MS32_WWDG_SetCounter(WWDG_TypeDef *WWDGx, uint32_t Counter) {
  MODIFY_REG(WWDGx->CR, WWDG_CR_T, Counter);
}

/**
  * @brief  Return current Watchdog Counter Value (7 bits counter value)
  * @rmtoll CR           T             MS32_WWDG_GetCounter
  * @param  WWDGx WWDG Instance
  * @retval 7 bit Watchdog Counter value
  */
__STATIC_INLINE uint32_t MS32_WWDG_GetCounter(WWDG_TypeDef *WWDGx) {
  return (READ_BIT(WWDGx->CR, WWDG_CR_T));
}

/**
  * @brief  Set the time base of the prescaler (WDGTB).
  * @note   Prescaler is used to apply ratio on PCLK clock, so that Watchdog counter
  *         is decremented every (4096 x 2expWDGTB) PCLK cycles
  * @rmtoll CFR          WDGTB         MS32_WWDG_SetPrescaler
  * @param  WWDGx WWDG Instance
  * @param  Prescaler This parameter can be one of the following values:
  *         @arg @ref MS32_WWDG_PRESCALER_1
  *         @arg @ref MS32_WWDG_PRESCALER_2
  *         @arg @ref MS32_WWDG_PRESCALER_4
  *         @arg @ref MS32_WWDG_PRESCALER_8
  * @retval None
  */
__STATIC_INLINE void MS32_WWDG_SetPrescaler(WWDG_TypeDef *WWDGx, uint32_t Prescaler) {
  MODIFY_REG(WWDGx->CFR, WWDG_CFR_WDGTB, Prescaler);
}

/**
  * @brief  Return current Watchdog Prescaler Value
  * @rmtoll CFR          WDGTB         MS32_WWDG_GetPrescaler
  * @param  WWDGx WWDG Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_WWDG_PRESCALER_1
  *         @arg @ref MS32_WWDG_PRESCALER_2
  *         @arg @ref MS32_WWDG_PRESCALER_4
  *         @arg @ref MS32_WWDG_PRESCALER_8
  */
__STATIC_INLINE uint32_t MS32_WWDG_GetPrescaler(WWDG_TypeDef *WWDGx) {
  return (READ_BIT(WWDGx->CFR, WWDG_CFR_WDGTB));
}

/**
  * @brief  Set the Watchdog Window value to be compared to the downcounter (7-bits W[6:0]).
  * @note   This window value defines when write in the WWDG_CR register
  *         to program Watchdog counter is allowed.
  *         Watchdog counter value update must occur only when the counter value
  *         is lower than the Watchdog window register value.
  *         Otherwise, a MCU reset is generated if the 7-bit Watchdog counter value
  *         (in the control register) is refreshed before the downcounter has reached
  *         the watchdog window register value.
  *         Physically is possible to set the Window lower then 0x40 but it is not recommended.
  *         To generate an immediate reset, it is possible to set the Counter lower than 0x40.
  * @rmtoll CFR          W             MS32_WWDG_SetWindow
  * @param  WWDGx WWDG Instance
  * @param  Window 0x00..0x7F (7 bit Window value)
  * @retval None
  */
__STATIC_INLINE void MS32_WWDG_SetWindow(WWDG_TypeDef *WWDGx, uint32_t Window) {
  MODIFY_REG(WWDGx->CFR, WWDG_CFR_W, Window);
}

/**
  * @brief  Return current Watchdog Window Value (7 bits value)
  * @rmtoll CFR          W             MS32_WWDG_GetWindow
  * @param  WWDGx WWDG Instance
  * @retval 7 bit Watchdog Window value
  */
__STATIC_INLINE uint32_t MS32_WWDG_GetWindow(WWDG_TypeDef *WWDGx) {
  return (READ_BIT(WWDGx->CFR, WWDG_CFR_W));
}


/** @defgroup WWDG_EF_FLAG_Management FLAG_Management
  * @{
  */

/**
  * @brief  Indicates if the WWDG Early Wakeup Interrupt Flag is set or not.
  * @note   This bit is set by hardware when the counter has reached the value 0x40.
  *         It must be cleared by software by writing 0.
  *         A write of 1 has no effect. This bit is also set if the interrupt is not enabled.
  * @rmtoll SR           EWIF          MS32_WWDG_IsActiveFlag_EWKUP
  * @param  WWDGx WWDG Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_WWDG_IsActiveFlag_EWKUP(WWDG_TypeDef *WWDGx) {
  return ((READ_BIT(WWDGx->SR, WWDG_SR_EWIF) == (WWDG_SR_EWIF)) ? 1UL : 0UL);
}

/**
  * @brief  Clear WWDG Early Wakeup Interrupt Flag (EWIF)
  * @rmtoll SR           EWIF          MS32_WWDG_ClearFlag_EWKUP
  * @param  WWDGx WWDG Instance
  * @retval None
  */
__STATIC_INLINE void MS32_WWDG_ClearFlag_EWKUP(WWDG_TypeDef *WWDGx) {
  CLEAR_BIT(WWDGx->SR, WWDG_SR_EWIF);
}


/** @defgroup WWDG_EF_IT_Management IT_Management
  * @{
  */

/**
  * @brief  Enable the Early Wakeup Interrupt.
  * @note   When set, an interrupt occurs whenever the counter reaches value 0x40.
  *         This interrupt is only cleared by hardware after a reset
  * @rmtoll CFR          EWI           MS32_WWDG_EnableIT_EWKUP
  * @param  WWDGx WWDG Instance
  * @retval None
  */
__STATIC_INLINE void MS32_WWDG_EnableIT_EWKUP(WWDG_TypeDef *WWDGx) {
  SET_BIT(WWDGx->CFR, WWDG_CFR_EWI);
}

/**
  * @brief  Check if Early Wakeup Interrupt is enabled
  * @rmtoll CFR          EWI           MS32_WWDG_IsEnabledIT_EWKUP
  * @param  WWDGx WWDG Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_WWDG_IsEnabledIT_EWKUP(WWDG_TypeDef *WWDGx) {
  return ((READ_BIT(WWDGx->CFR, WWDG_CFR_EWI) == (WWDG_CFR_EWI)) ? 1UL : 0UL);
}


/** @defgroup WWDG_EF_Init Initialization and de-initialization functions
  * @{
  */
ErrorStatus MS32_WWDG_DeInit     (void);
void        MS32_WWDG_StructInit (MS32_WWDG_InitTypeDef *WwdgInitStr);
ErrorStatus MS32_WWDG_Init       (MS32_WWDG_InitTypeDef *WwdgInitStr);
void        MS32_WWDG_ITConfig   (uint32_t InterruptFunc, uint32_t Priority);

/** @defgroup WWDG_EF_Application function
  * @{
  */
ErrorStatus MS32_WWDG_Refresh       (uint8_t Counter);
FlagStatus  MS32_WWDG_GetStatusFlag (void);


#ifdef __cplusplus
}
#endif

#endif /* __MS32F0XX_WWDG_H */

/******************************** END OF FILE *********************************/
