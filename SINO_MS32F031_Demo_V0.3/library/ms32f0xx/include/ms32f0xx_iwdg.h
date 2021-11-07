/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MS32F0XX_IWDG_H
#define __MS32F0XX_IWDG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ms32f0xx.h"


/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @defgroup IWDG_Private_Constants IWDG Private Constants
  * @{
  */
#define MS32_IWDG_KEY_RELOAD                 0x0000AAAAU                   /*!< IWDG Reload Counter Enable   */
#define MS32_IWDG_KEY_ENABLE                 0x0000CCCCU                   /*!< IWDG Peripheral Enable       */
#define MS32_IWDG_KEY_WR_ACCESS_ENABLE       0x00005555U                   /*!< IWDG KR Write Access Enable  */
#define MS32_IWDG_KEY_WR_ACCESS_DISABLE      0x00000000U                   /*!< IWDG KR Write Access Disable */


/* Private macros ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/** @defgroup IWDG_Exported_Types IWDG Exported Types
  * @{
  */

/**
  * @brief  IWDG Init structure definition
  */
typedef struct {
  uint32_t Prescaler;  /*!< Select the prescaler of the IWDG.
                            This parameter can be a value of @ref IWDG_Prescaler */
  uint32_t Reload;     /*!< Specifies the IWDG down-counter reload value.
                            This parameter must be a number between Min_Data = 0 and Max_Data = 0x0FFF */
  uint32_t Window;     /*!< Specifies the window value to be compared to the down-counter.
                            This parameter must be a number between Min_Data = 0 and Max_Data = 0x0FFF */
} MS32_IWDG_InitTypeDef;


/* Exported constants --------------------------------------------------------*/
/** @defgroup IWDG_EC_GET_FLAG Get Flags Defines
  * @brief    Flags defines which can be used with MS32_IWDG_ReadReg function
  * @{
  */
#define MS32_IWDG_FLAG_PVU                   IWDG_SR_PVU /*!< Watchdog prescaler value update */
#define MS32_IWDG_FLAG_RVU                   IWDG_SR_RVU /*!< Watchdog counter reload value update */
#define MS32_IWDG_FLAG_WVU                   IWDG_SR_WVU /*!< Watchdog counter window value update */


/** @defgroup IWDG_EC_PRESCALER  Prescaler Divider
  * @{
  */
#define MS32_IWDG_PRESCALER_4                0x00000000U                    /*!< Divider by 4   */
#define MS32_IWDG_PRESCALER_8                (IWDG_PR_PR_0)                 /*!< Divider by 8   */
#define MS32_IWDG_PRESCALER_16               (IWDG_PR_PR_1)                 /*!< Divider by 16  */
#define MS32_IWDG_PRESCALER_32               (IWDG_PR_PR_1 | IWDG_PR_PR_0)  /*!< Divider by 32  */
#define MS32_IWDG_PRESCALER_64               (IWDG_PR_PR_2)                 /*!< Divider by 64  */
#define MS32_IWDG_PRESCALER_128              (IWDG_PR_PR_2 | IWDG_PR_PR_0)  /*!< Divider by 128 */
#define MS32_IWDG_PRESCALER_256              (IWDG_PR_PR_2 | IWDG_PR_PR_1)  /*!< Divider by 256 */


/* Exported macro ------------------------------------------------------------*/
/** @defgroup IWDG_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in IWDG register
  * @param  __INSTANCE__ IWDG Instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define MS32_IWDG_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, (__VALUE__))

/**
  * @brief  Read a value in IWDG register
  * @param  __INSTANCE__ IWDG Instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define MS32_IWDG_ReadReg(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)


/* Exported functions --------------------------------------------------------*/
/** @defgroup IWDG_EF_Configuration Configuration
  * @{
  */

/**
  * @brief  Start the Independent Watchdog
  * @note   Except if the hardware watchdog option is selected
  * @rmtoll KR           KEY           MS32_IWDG_Enable
  * @param  IWDGx IWDG Instance
  * @retval None
  */
__STATIC_INLINE void MS32_IWDG_Enable(IWDG_TypeDef *IWDGx) {
  WRITE_REG(IWDGx->KR, MS32_IWDG_KEY_ENABLE);
}

/**
  * @brief  Reloads IWDG counter with value defined in the reload register
  * @rmtoll KR           KEY           MS32_IWDG_ReloadCounter
  * @param  IWDGx IWDG Instance
  * @retval None
  */
__STATIC_INLINE void MS32_IWDG_ReloadCounter(IWDG_TypeDef *IWDGx) {
  WRITE_REG(IWDGx->KR, MS32_IWDG_KEY_RELOAD);
}

/**
  * @brief  Enable write access to IWDG_PR, IWDG_RLR and IWDG_WINR registers
  * @rmtoll KR           KEY           MS32_IWDG_EnableWriteAccess
  * @param  IWDGx IWDG Instance
  * @retval None
  */
__STATIC_INLINE void MS32_IWDG_EnableWriteAccess(IWDG_TypeDef *IWDGx) {
  WRITE_REG(IWDGx->KR, MS32_IWDG_KEY_WR_ACCESS_ENABLE);
}

/**
  * @brief  Disable write access to IWDG_PR, IWDG_RLR and IWDG_WINR registers
  * @rmtoll KR           KEY           MS32_IWDG_DisableWriteAccess
  * @param  IWDGx IWDG Instance
  * @retval None
  */
__STATIC_INLINE void MS32_IWDG_DisableWriteAccess(IWDG_TypeDef *IWDGx) {
  WRITE_REG(IWDGx->KR, MS32_IWDG_KEY_WR_ACCESS_DISABLE);
}

/**
  * @brief  Select the prescaler of the IWDG
  * @rmtoll PR           PR            MS32_IWDG_SetPrescaler
  * @param  IWDGx IWDG Instance
  * @param  Prescaler This parameter can be one of the following values:
  *         @arg @ref MS32_IWDG_PRESCALER_4
  *         @arg @ref MS32_IWDG_PRESCALER_8
  *         @arg @ref MS32_IWDG_PRESCALER_16
  *         @arg @ref MS32_IWDG_PRESCALER_32
  *         @arg @ref MS32_IWDG_PRESCALER_64
  *         @arg @ref MS32_IWDG_PRESCALER_128
  *         @arg @ref MS32_IWDG_PRESCALER_256
  * @retval None
  */
__STATIC_INLINE void MS32_IWDG_SetPrescaler(IWDG_TypeDef *IWDGx, uint32_t Prescaler) {
  WRITE_REG(IWDGx->PR, IWDG_PR_PR & Prescaler);
}

/**
  * @brief  Get the selected prescaler of the IWDG
  * @rmtoll PR           PR            MS32_IWDG_GetPrescaler
  * @param  IWDGx IWDG Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_IWDG_PRESCALER_4
  *         @arg @ref MS32_IWDG_PRESCALER_8
  *         @arg @ref MS32_IWDG_PRESCALER_16
  *         @arg @ref MS32_IWDG_PRESCALER_32
  *         @arg @ref MS32_IWDG_PRESCALER_64
  *         @arg @ref MS32_IWDG_PRESCALER_128
  *         @arg @ref MS32_IWDG_PRESCALER_256
  */
__STATIC_INLINE uint32_t MS32_IWDG_GetPrescaler(IWDG_TypeDef *IWDGx) {
  return (READ_REG(IWDGx->PR));
}

/**
  * @brief  Specify the IWDG down-counter reload value
  * @rmtoll RLR          RL            MS32_IWDG_SetReloadCounter
  * @param  IWDGx IWDG Instance
  * @param  Counter Value between Min_Data=0 and Max_Data=0x0FFF
  * @retval None
  */
__STATIC_INLINE void MS32_IWDG_SetReloadCounter(IWDG_TypeDef *IWDGx, uint32_t Counter) {
  WRITE_REG(IWDGx->RLR, IWDG_RLR_RL & Counter);
}

/**
  * @brief  Get the specified IWDG down-counter reload value
  * @rmtoll RLR          RL            MS32_IWDG_GetReloadCounter
  * @param  IWDGx IWDG Instance
  * @retval Value between Min_Data=0 and Max_Data=0x0FFF
  */
__STATIC_INLINE uint32_t MS32_IWDG_GetReloadCounter(IWDG_TypeDef *IWDGx) {
  return (READ_REG(IWDGx->RLR));
}

/**
  * @brief  Specify high limit of the window value to be compared to the down-counter.
  * @rmtoll WINR         WIN           MS32_IWDG_SetWindow
  * @param  IWDGx IWDG Instance
  * @param  Window Value between Min_Data=0 and Max_Data=0x0FFF
  * @retval None
  */
__STATIC_INLINE void MS32_IWDG_SetWindow(IWDG_TypeDef *IWDGx, uint32_t Window) {
  WRITE_REG(IWDGx->WINR, IWDG_WINR_WIN & Window);
}

/**
  * @brief  Get the high limit of the window value specified.
  * @rmtoll WINR         WIN           MS32_IWDG_GetWindow
  * @param  IWDGx IWDG Instance
  * @retval Value between Min_Data=0 and Max_Data=0x0FFF
  */
__STATIC_INLINE uint32_t MS32_IWDG_GetWindow(IWDG_TypeDef *IWDGx) {
  return (READ_REG(IWDGx->WINR));
}


/** @defgroup IWDG_EF_FLAG_Management FLAG_Management
  * @{
  */

/**
  * @brief  Check if flag Prescaler Value Update is set or not
  * @rmtoll SR           PVU           MS32_IWDG_IsActiveFlag_PVU
  * @param  IWDGx IWDG Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_IWDG_IsActiveFlag_PVU(IWDG_TypeDef *IWDGx) {
  return ((READ_BIT(IWDGx->SR, IWDG_SR_PVU) == (IWDG_SR_PVU)) ? 1UL : 0UL);
}

/**
  * @brief  Check if flag Reload Value Update is set or not
  * @rmtoll SR           RVU           MS32_IWDG_IsActiveFlag_RVU
  * @param  IWDGx IWDG Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_IWDG_IsActiveFlag_RVU(IWDG_TypeDef *IWDGx) {
  return ((READ_BIT(IWDGx->SR, IWDG_SR_RVU) == (IWDG_SR_RVU)) ? 1UL : 0UL);
}

/**
  * @brief  Check if flag Window Value Update is set or not
  * @rmtoll SR           WVU           MS32_IWDG_IsActiveFlag_WVU
  * @param  IWDGx IWDG Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_IWDG_IsActiveFlag_WVU(IWDG_TypeDef *IWDGx) {
  return ((READ_BIT(IWDGx->SR, IWDG_SR_WVU) == (IWDG_SR_WVU)) ? 1UL : 0UL);
}

/**
  * @brief  Check if all flags Prescaler, Reload & Window Value Update are reset or not
  * @rmtoll SR           PVU           MS32_IWDG_IsReady\n
  *         SR           WVU           MS32_IWDG_IsReady\n
  *         SR           RVU           MS32_IWDG_IsReady
  * @param  IWDGx IWDG Instance
  * @retval State of bits (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_IWDG_IsReady(IWDG_TypeDef *IWDGx) {
  return ((READ_BIT(IWDGx->SR, IWDG_SR_PVU | IWDG_SR_RVU | IWDG_SR_WVU) == 0U) ? 1UL : 0UL);
}


/** @defgroup WWDG_EF_Init Initialization functions
  * @{
  */
void        MS32_IWDG_StructInit (MS32_IWDG_InitTypeDef *IwdgInitStr);
ErrorStatus MS32_IWDG_Init       (MS32_IWDG_InitTypeDef *IwdgInitStr);

/** @defgroup WWDG_EF_Application function
  * @{
  */
void       MS32_IWDG_Refresh       (void);
FlagStatus MS32_IWDG_GetStatusFlag (uint32_t Flags);


#ifdef __cplusplus
}
#endif

#endif /* __MS32F0XX_IWDG_H */

/******************************** END OF FILE *********************************/
