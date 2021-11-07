/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MS32F0XX_SYSTEM_H
#define __MS32F0XX_SYSTEM_H

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
/** @defgroup SYSTEM_Exported_Constants SYSTEM Exported Constants(APP)
  * @{
  */


/** @defgroup SYSTEM_Exported_Constants SYSTEM Exported Constants(BASE)
  * @{
  */
/** @defgroup SYSTEM_EC_REMAP SYSCFG Remap
* @{
*/
#define MS32_SYSCFG_REMAP_FLASH              (uint32_t)0x00000000U                               /*!< Main Flash memory mapped at 0x00000000 */
#define MS32_SYSCFG_REMAP_SYSTEMFLASH        SYSCFG_CFGR1_MEM_MODE_0                             /*!< System Flash memory mapped at 0x00000000 */
#define MS32_SYSCFG_REMAP_SRAM               (SYSCFG_CFGR1_MEM_MODE_1 | SYSCFG_CFGR1_MEM_MODE_0) /*!< Embedded SRAM mapped at 0x00000000 */


/** @defgroup SYSTEM_EC_USART1TX_RMP SYSCFG USART DMA Remap
  * @{
  */
#define MS32_SYSCFG_USART1TX_RMP_DMA1CH2     ((SYSCFG_CFGR1_USART1TX_DMA_RMP >> 8U) | (uint32_t)0x00000000U)         /*!< USART1_TX DMA request mapped on DMA channel 2U */
#define MS32_SYSCFG_USART1TX_RMP_DMA1CH4     ((SYSCFG_CFGR1_USART1TX_DMA_RMP >> 8U) | SYSCFG_CFGR1_USART1TX_DMA_RMP) /*!< USART1_TX DMA request mapped on DMA channel 4U */
#define MS32_SYSCFG_USART1RX_RMP_DMA1CH3     ((SYSCFG_CFGR1_USART1RX_DMA_RMP >> 8U) | (uint32_t)0x00000000U)         /*!< USART1_RX DMA request mapped on DMA channel 3U */
#define MS32_SYSCFG_USART1RX_RMP_DMA1CH5     ((SYSCFG_CFGR1_USART1RX_DMA_RMP >> 8U) | SYSCFG_CFGR1_USART1RX_DMA_RMP) /*!< USART1_RX DMA request mapped on DMA channel 5 */


/** @defgroup SYSTEM_EC_TIM16_RMP_DMA1 SYSCFG TIM DMA Remap
  * @{
  */
#define MS32_SYSCFG_TIM16_RMP_DMA1_CH3       ((SYSCFG_CFGR1_TIM16_DMA_RMP >> 8U) | (uint32_t)0x00000000U)      /*!< TIM16_CH1 and TIM16_UP DMA requests mapped on DMA channel 3 */
#define MS32_SYSCFG_TIM16_RMP_DMA1_CH4       ((SYSCFG_CFGR1_TIM16_DMA_RMP >> 8U) | SYSCFG_CFGR1_TIM16_DMA_RMP) /*!< TIM16_CH1 and TIM16_UP DMA requests mapped on DMA channel 4 */
#define MS32_SYSCFG_TIM17_RMP_DMA1_CH1       ((SYSCFG_CFGR1_TIM17_DMA_RMP >> 8U) | (uint32_t)0x00000000U)      /*!< TIM17_CH1 and TIM17_UP DMA requests mapped on DMA channel 1 */
#define MS32_SYSCFG_TIM17_RMP_DMA1_CH2       ((SYSCFG_CFGR1_TIM17_DMA_RMP >> 8U) | SYSCFG_CFGR1_TIM17_DMA_RMP) /*!< TIM17_CH1 and TIM17_UP DMA requests mapped on DMA channel 2 */


/** @defgroup SYSTEM_EC_I2C_FASTMODEPLUS SYSCFG I2C FASTMODEPLUS
  * @{
  */
#define MS32_SYSCFG_I2C_FASTMODEPLUS_PB6     SYSCFG_CFGR1_I2C_FMP_PB6  /*!< I2C PB6 Fast mode plus */
#define MS32_SYSCFG_I2C_FASTMODEPLUS_PB7     SYSCFG_CFGR1_I2C_FMP_PB7  /*!< I2C PB7 Fast mode plus */
#define MS32_SYSCFG_I2C_FASTMODEPLUS_PB8     SYSCFG_CFGR1_I2C_FMP_PB8  /*!< I2C PB8 Fast mode plus */
#define MS32_SYSCFG_I2C_FASTMODEPLUS_PB9     SYSCFG_CFGR1_I2C_FMP_PB9  /*!< I2C PB9 Fast mode plus */
#define MS32_SYSCFG_I2C_FASTMODEPLUS_I2C1    SYSCFG_CFGR1_I2C_FMP_I2C1 /*!< Enable Fast Mode Plus on PB10, PB11, PF6 and PF7  */
#define MS32_SYSCFG_I2C_FASTMODEPLUS_PA9     SYSCFG_CFGR1_I2C_FMP_PA9  /*!< Enable Fast Mode Plus on PA9  */
#define MS32_SYSCFG_I2C_FASTMODEPLUS_PA10    SYSCFG_CFGR1_I2C_FMP_PA10 /*!< Enable Fast Mode Plus on PA10 */


/** @defgroup SYSTEM_EC_EXTI_PORT SYSCFG EXTI PORT
  * @{
  */
#define MS32_SYSCFG_EXTI_PORTA               (uint32_t)(0U) /*!< EXTI PORT A */
#define MS32_SYSCFG_EXTI_PORTB               (uint32_t)(1U) /*!< EXTI PORT B */
#define MS32_SYSCFG_EXTI_PORTC               (uint32_t)(2U) /*!< EXTI PORT C */
#define MS32_SYSCFG_EXTI_PORTF               (uint32_t)(5U) /*!< EXTI PORT F */


/** @defgroup SYSTEM_EC_EXTI_LINE SYSCFG EXTI LINE
  * @{
  */
#define MS32_SYSCFG_EXTI_LINE0               (uint32_t)(0U << 16U | 0U)  /*!< EXTI_POSITION_0  | EXTICR[0] */
#define MS32_SYSCFG_EXTI_LINE1               (uint32_t)(4U << 16U | 0U)  /*!< EXTI_POSITION_4  | EXTICR[0] */
#define MS32_SYSCFG_EXTI_LINE2               (uint32_t)(8U << 16U | 0U)  /*!< EXTI_POSITION_8  | EXTICR[0] */
#define MS32_SYSCFG_EXTI_LINE3               (uint32_t)(12U << 16U | 0U) /*!< EXTI_POSITION_12 | EXTICR[0] */
#define MS32_SYSCFG_EXTI_LINE4               (uint32_t)(0U << 16U | 1U)  /*!< EXTI_POSITION_0  | EXTICR[1] */
#define MS32_SYSCFG_EXTI_LINE5               (uint32_t)(4U << 16U | 1U)  /*!< EXTI_POSITION_4  | EXTICR[1] */
#define MS32_SYSCFG_EXTI_LINE6               (uint32_t)(8U << 16U | 1U)  /*!< EXTI_POSITION_8  | EXTICR[1] */
#define MS32_SYSCFG_EXTI_LINE7               (uint32_t)(12U << 16U | 1U) /*!< EXTI_POSITION_12 | EXTICR[1] */
#define MS32_SYSCFG_EXTI_LINE8               (uint32_t)(0U << 16U | 2U)  /*!< EXTI_POSITION_0  | EXTICR[2] */
#define MS32_SYSCFG_EXTI_LINE9               (uint32_t)(4U << 16U | 2U)  /*!< EXTI_POSITION_4  | EXTICR[2] */
#define MS32_SYSCFG_EXTI_LINE10              (uint32_t)(8U << 16U | 2U)  /*!< EXTI_POSITION_8  | EXTICR[2] */
#define MS32_SYSCFG_EXTI_LINE11              (uint32_t)(12U << 16U | 2U) /*!< EXTI_POSITION_12 | EXTICR[2] */
#define MS32_SYSCFG_EXTI_LINE12              (uint32_t)(0U << 16U | 3U)  /*!< EXTI_POSITION_0  | EXTICR[3] */
#define MS32_SYSCFG_EXTI_LINE13              (uint32_t)(4U << 16U | 3U)  /*!< EXTI_POSITION_4  | EXTICR[3] */
#define MS32_SYSCFG_EXTI_LINE14              (uint32_t)(8U << 16U | 3U)  /*!< EXTI_POSITION_8  | EXTICR[3] */
#define MS32_SYSCFG_EXTI_LINE15              (uint32_t)(12U << 16U | 3U) /*!< EXTI_POSITION_12 | EXTICR[3] */


/** @defgroup SYSTEM_EC_TIMBREAK SYSCFG TIMER BREAK
  * @{
  */
#define MS32_SYSCFG_TIMBREAK_PVD             SYSCFG_CFGR2_PVD_LOCK         /*!< Enables and locks the PVD connection with TIM1/15/16U/17 Break Input and also  the PVDE and PLS bits of the Power Control Interface */
#define MS32_SYSCFG_TIMBREAK_SRAM_PARITY     SYSCFG_CFGR2_SRAM_PARITY_LOCK /*!< Enables and locks the SRAM_PARITY error signal with Break Input of TIM1/15/16/17 */
#define MS32_SYSCFG_TIMBREAK_LOCKUP          SYSCFG_CFGR2_LOCKUP_LOCK      /*!< Enables and locks the LOCKUP (Hardfault) output of CortexM0 with Break Input of TIM1/15/16/17 */


/** @defgroup SYSTEM_EC_APB1_GRP1_STOP_IP  DBGMCU APB1 GRP1 STOP IP
  * @{
  */
#define MS32_DBGMCU_APB1_GRP1_TIM2_STOP      DBGMCU_APB1_FZ_DBG_TIM2_STOP          /*!< TIM2 counter stopped when core is halted */
#define MS32_DBGMCU_APB1_GRP1_TIM3_STOP      DBGMCU_APB1_FZ_DBG_TIM3_STOP          /*!< TIM3 counter stopped when core is halted */
#define MS32_DBGMCU_APB1_GRP1_TIM14_STOP     DBGMCU_APB1_FZ_DBG_TIM14_STOP         /*!< TIM14 counter stopped when core is halted */
#define MS32_DBGMCU_APB1_GRP1_RTC_STOP       DBGMCU_APB1_FZ_DBG_RTC_STOP           /*!< RTC Calendar frozen when core is halted */
#define MS32_DBGMCU_APB1_GRP1_WWDG_STOP      DBGMCU_APB1_FZ_DBG_WWDG_STOP          /*!< Debug Window Watchdog stopped when Core is halted */
#define MS32_DBGMCU_APB1_GRP1_IWDG_STOP      DBGMCU_APB1_FZ_DBG_IWDG_STOP          /*!< Debug Independent Watchdog stopped when Core is halted */
#define MS32_DBGMCU_APB1_GRP1_I2C1_STOP      DBGMCU_APB1_FZ_DBG_I2C1_SMBUS_TIMEOUT /*!< I2C1 SMBUS timeout mode stopped when Core is halted */


/** @defgroup SYSTEM_EC_APB1 GRP2_STOP_IP DBGMCU APB1 GRP2 STOP IP
  * @{
  */
#define MS32_DBGMCU_APB1_GRP2_TIM1_STOP      DBGMCU_APB2_FZ_DBG_TIM1_STOP  /*!< TIM1 counter stopped when core is halted */
#define MS32_DBGMCU_APB1_GRP2_TIM16_STOP     DBGMCU_APB2_FZ_DBG_TIM16_STOP /*!< TIM16 counter stopped when core is halted */
#define MS32_DBGMCU_APB1_GRP2_TIM17_STOP     DBGMCU_APB2_FZ_DBG_TIM17_STOP /*!< TIM17 counter stopped when core is halted */


/** @defgroup SYSTEM_EC_LATENCY FLASH LATENCY
  * @{
  */
#define MS32_FLASH_LATENCY_0                 (0x00000000U)     /*!< FLASH Zero Latency cycle */
#define MS32_FLASH_LATENCY_1                 FLASH_ACR_LATENCY /*!< FLASH One Latency cycle */


/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @defgroup SYSTEM_EF_SYSCFG SYSCFG
  * @{
  */

/**
  * @brief  Set memory mapping at address 0x00000000
  * @rmtoll SYSCFG_CFGR1 MEM_MODE      MS32_SYSCFG_SetRemapMemory
  * @param  Memory This parameter can be one of the following values:
  *         @arg @ref MS32_SYSCFG_REMAP_FLASH
  *         @arg @ref MS32_SYSCFG_REMAP_SYSTEMFLASH
  *         @arg @ref MS32_SYSCFG_REMAP_SRAM
  * @retval None
  */
__STATIC_INLINE void MS32_SYSCFG_SetRemapMemory(uint32_t Memory) {
  MODIFY_REG(SYSCFG->CFGR1, SYSCFG_CFGR1_MEM_MODE, Memory);
}

/**
  * @brief  Get memory mapping at address 0x00000000
  * @rmtoll SYSCFG_CFGR1 MEM_MODE      MS32_SYSCFG_GetRemapMemory
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_SYSCFG_REMAP_FLASH
  *         @arg @ref MS32_SYSCFG_REMAP_SYSTEMFLASH
  *         @arg @ref MS32_SYSCFG_REMAP_SRAM
  */
__STATIC_INLINE uint32_t MS32_SYSCFG_GetRemapMemory(void) {
  return (uint32_t)(READ_BIT(SYSCFG->CFGR1, SYSCFG_CFGR1_MEM_MODE));
}

/**
  * @brief  Set DMA request remapping bits for USART
  * @rmtoll SYSCFG_CFGR1 USART1TX_DMA_RMP  MS32_SYSCFG_SetRemapDMA_USART\n
  *         SYSCFG_CFGR1 USART1RX_DMA_RMP  MS32_SYSCFG_SetRemapDMA_USART\n
  *         SYSCFG_CFGR1 USART2_DMA_RMP  MS32_SYSCFG_SetRemapDMA_USART\n
  *         SYSCFG_CFGR1 USART3_DMA_RMP  MS32_SYSCFG_SetRemapDMA_USART
  * @param  Remap This parameter can be one of the following values:
  *         @arg @ref MS32_SYSCFG_USART1TX_RMP_DMA1CH2 (*)
  *         @arg @ref MS32_SYSCFG_USART1TX_RMP_DMA1CH4 (*)
  *         @arg @ref MS32_SYSCFG_USART1RX_RMP_DMA1CH3 (*)
  *         @arg @ref MS32_SYSCFG_USART1RX_RMP_DMA1CH5 (*)
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void MS32_SYSCFG_SetRemapDMA_USART(uint32_t Remap) {
  MODIFY_REG(SYSCFG->CFGR1, (Remap & 0x00FF00FFU) << 8U, (Remap & 0xFF00FF00U));
}

/**
  * @brief  Set DMA request remapping bits for TIM
  * @rmtoll SYSCFG_CFGR1 TIM16_DMA_RMP  MS32_SYSCFG_SetRemapDMA_TIM\n
  *         SYSCFG_CFGR1 TIM17_DMA_RMP  MS32_SYSCFG_SetRemapDMA_TIM\n
  *         SYSCFG_CFGR1 TIM16_DMA_RMP2 MS32_SYSCFG_SetRemapDMA_TIM\n
  *         SYSCFG_CFGR1 TIM17_DMA_RMP2 MS32_SYSCFG_SetRemapDMA_TIM\n
  *         SYSCFG_CFGR1 TIM1_DMA_RMP   MS32_SYSCFG_SetRemapDMA_TIM\n
  *         SYSCFG_CFGR1 TIM2_DMA_RMP   MS32_SYSCFG_SetRemapDMA_TIM\n
  *         SYSCFG_CFGR1 TIM3_DMA_RMP   MS32_SYSCFG_SetRemapDMA_TIM
  * @param  Remap This parameter can be one of the following values:
  *         @arg @ref MS32_SYSCFG_TIM16_RMP_DMA1_CH3 (*)
  *         @arg @ref MS32_SYSCFG_TIM16_RMP_DMA1_CH4 (*)
  *         @arg @ref MS32_SYSCFG_TIM16_RMP_DMA1_CH6 (*)
  *         @arg @ref MS32_SYSCFG_TIM17_RMP_DMA1_CH1 (*)
  *         @arg @ref MS32_SYSCFG_TIM17_RMP_DMA1_CH2 (*)
  *         @arg @ref MS32_SYSCFG_TIM17_RMP_DMA1_CH7 (*)
  *
  *         (*) value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void MS32_SYSCFG_SetRemapDMA_TIM(uint32_t Remap) {
  MODIFY_REG(SYSCFG->CFGR1, (Remap & 0x00FF00FFU) << 8U, (Remap & 0xFF00FF00U));
}

/**
  * @brief  Enable the I2C fast mode plus driving capability.
  * @rmtoll SYSCFG_CFGR1 I2C_FMP_PB6   MS32_SYSCFG_EnableFastModePlus\n
  *         SYSCFG_CFGR1 I2C_FMP_PB7   MS32_SYSCFG_EnableFastModePlus\n
  *         SYSCFG_CFGR1 I2C_FMP_PB8   MS32_SYSCFG_EnableFastModePlus\n
  *         SYSCFG_CFGR1 I2C_FMP_PB9   MS32_SYSCFG_EnableFastModePlus\n
  *         SYSCFG_CFGR1 I2C_FMP_I2C1  MS32_SYSCFG_EnableFastModePlus\n
  *         SYSCFG_CFGR1 I2C_FMP_I2C2  MS32_SYSCFG_EnableFastModePlus\n
  *         SYSCFG_CFGR1 I2C_FMP_PA9   MS32_SYSCFG_EnableFastModePlus\n
  *         SYSCFG_CFGR1 I2C_FMP_PA10  MS32_SYSCFG_EnableFastModePlus
  * @param  ConfigFastModePlus This parameter can be a combination of the following values:
  *         @arg @ref MS32_SYSCFG_I2C_FASTMODEPLUS_PB6
  *         @arg @ref MS32_SYSCFG_I2C_FASTMODEPLUS_PB7
  *         @arg @ref MS32_SYSCFG_I2C_FASTMODEPLUS_PB8
  *         @arg @ref MS32_SYSCFG_I2C_FASTMODEPLUS_PB9
  *         @arg @ref MS32_SYSCFG_I2C_FASTMODEPLUS_I2C1
  *         @arg @ref MS32_SYSCFG_I2C_FASTMODEPLUS_PA9
  *         @arg @ref MS32_SYSCFG_I2C_FASTMODEPLUS_PA10
  *
  *         (*) value not defined in all devices
  * @retval None
  */
__STATIC_INLINE void MS32_SYSCFG_EnableFastModePlus(uint32_t ConfigFastModePlus) {
  SET_BIT(SYSCFG->CFGR1, ConfigFastModePlus);
}

/**
  * @brief  Disable the I2C fast mode plus driving capability.
  * @rmtoll SYSCFG_CFGR1 I2C_FMP_PB6   MS32_SYSCFG_DisableFastModePlus\n
  *         SYSCFG_CFGR1 I2C_FMP_PB7   MS32_SYSCFG_DisableFastModePlus\n
  *         SYSCFG_CFGR1 I2C_FMP_PB8   MS32_SYSCFG_DisableFastModePlus\n
  *         SYSCFG_CFGR1 I2C_FMP_PB9   MS32_SYSCFG_DisableFastModePlus\n
  *         SYSCFG_CFGR1 I2C_FMP_I2C1  MS32_SYSCFG_DisableFastModePlus\n
  *         SYSCFG_CFGR1 I2C_FMP_I2C2  MS32_SYSCFG_DisableFastModePlus\n
  *         SYSCFG_CFGR1 I2C_FMP_PA9   MS32_SYSCFG_DisableFastModePlus\n
  *         SYSCFG_CFGR1 I2C_FMP_PA10  MS32_SYSCFG_DisableFastModePlus
  * @param  ConfigFastModePlus This parameter can be a combination of the following values:
  *         @arg @ref MS32_SYSCFG_I2C_FASTMODEPLUS_PB6
  *         @arg @ref MS32_SYSCFG_I2C_FASTMODEPLUS_PB7
  *         @arg @ref MS32_SYSCFG_I2C_FASTMODEPLUS_PB8
  *         @arg @ref MS32_SYSCFG_I2C_FASTMODEPLUS_PB9
  *         @arg @ref MS32_SYSCFG_I2C_FASTMODEPLUS_I2C1
  *         @arg @ref MS32_SYSCFG_I2C_FASTMODEPLUS_PA9
  *         @arg @ref MS32_SYSCFG_I2C_FASTMODEPLUS_PA10
  *
  *         (*) value not defined in all devices
  * @retval None
  */
__STATIC_INLINE void MS32_SYSCFG_DisableFastModePlus(uint32_t ConfigFastModePlus) {
  CLEAR_BIT(SYSCFG->CFGR1, ConfigFastModePlus);
}

/**
  * @brief  Configure source input for the EXTI external interrupt.
  * @rmtoll SYSCFG_EXTICR1 EXTI0         MS32_SYSCFG_SetEXTISource\n
  *         SYSCFG_EXTICR1 EXTI1         MS32_SYSCFG_SetEXTISource\n
  *         SYSCFG_EXTICR1 EXTI2         MS32_SYSCFG_SetEXTISource\n
  *         SYSCFG_EXTICR1 EXTI3         MS32_SYSCFG_SetEXTISource\n
  *         SYSCFG_EXTICR2 EXTI4         MS32_SYSCFG_SetEXTISource\n
  *         SYSCFG_EXTICR2 EXTI5         MS32_SYSCFG_SetEXTISource\n
  *         SYSCFG_EXTICR2 EXTI6         MS32_SYSCFG_SetEXTISource\n
  *         SYSCFG_EXTICR2 EXTI7         MS32_SYSCFG_SetEXTISource\n
  *         SYSCFG_EXTICR3 EXTI8         MS32_SYSCFG_SetEXTISource\n
  *         SYSCFG_EXTICR3 EXTI9         MS32_SYSCFG_SetEXTISource\n
  *         SYSCFG_EXTICR3 EXTI10        MS32_SYSCFG_SetEXTISource\n
  *         SYSCFG_EXTICR3 EXTI11        MS32_SYSCFG_SetEXTISource\n
  *         SYSCFG_EXTICR4 EXTI12        MS32_SYSCFG_SetEXTISource\n
  *         SYSCFG_EXTICR4 EXTI13        MS32_SYSCFG_SetEXTISource\n
  *         SYSCFG_EXTICR4 EXTI14        MS32_SYSCFG_SetEXTISource\n
  *         SYSCFG_EXTICR4 EXTI15        MS32_SYSCFG_SetEXTISource
  * @param  Port This parameter can be one of the following values:
  *         @arg @ref MS32_SYSCFG_EXTI_PORTA
  *         @arg @ref MS32_SYSCFG_EXTI_PORTB
  *         @arg @ref MS32_SYSCFG_EXTI_PORTC
  *         @arg @ref MS32_SYSCFG_EXTI_PORTF
  *
  *         (*) value not defined in all devices
  * @param  Line This parameter can be one of the following values:
  *         @arg @ref MS32_SYSCFG_EXTI_LINE0
  *         @arg @ref MS32_SYSCFG_EXTI_LINE1
  *         @arg @ref MS32_SYSCFG_EXTI_LINE2
  *         @arg @ref MS32_SYSCFG_EXTI_LINE3
  *         @arg @ref MS32_SYSCFG_EXTI_LINE4
  *         @arg @ref MS32_SYSCFG_EXTI_LINE5
  *         @arg @ref MS32_SYSCFG_EXTI_LINE6
  *         @arg @ref MS32_SYSCFG_EXTI_LINE7
  *         @arg @ref MS32_SYSCFG_EXTI_LINE8
  *         @arg @ref MS32_SYSCFG_EXTI_LINE9
  *         @arg @ref MS32_SYSCFG_EXTI_LINE10
  *         @arg @ref MS32_SYSCFG_EXTI_LINE11
  *         @arg @ref MS32_SYSCFG_EXTI_LINE12
  *         @arg @ref MS32_SYSCFG_EXTI_LINE13
  *         @arg @ref MS32_SYSCFG_EXTI_LINE14
  *         @arg @ref MS32_SYSCFG_EXTI_LINE15
  * @retval None
  */
__STATIC_INLINE void MS32_SYSCFG_SetEXTISource(uint32_t Port, uint32_t Line) {
  MODIFY_REG(SYSCFG->EXTICR[Line & 0xFF], SYSCFG_EXTICR1_EXTI0 << (Line >> 16), Port << (Line >> 16));
}

/**
  * @brief  Get the configured defined for specific EXTI Line
  * @rmtoll SYSCFG_EXTICR1 EXTI0         MS32_SYSCFG_SetEXTISource\n
  *         SYSCFG_EXTICR1 EXTI1         MS32_SYSCFG_SetEXTISource\n
  *         SYSCFG_EXTICR1 EXTI2         MS32_SYSCFG_SetEXTISource\n
  *         SYSCFG_EXTICR1 EXTI3         MS32_SYSCFG_SetEXTISource\n
  *         SYSCFG_EXTICR2 EXTI4         MS32_SYSCFG_SetEXTISource\n
  *         SYSCFG_EXTICR2 EXTI5         MS32_SYSCFG_SetEXTISource\n
  *         SYSCFG_EXTICR2 EXTI6         MS32_SYSCFG_SetEXTISource\n
  *         SYSCFG_EXTICR2 EXTI7         MS32_SYSCFG_SetEXTISource\n
  *         SYSCFG_EXTICR3 EXTI8         MS32_SYSCFG_SetEXTISource\n
  *         SYSCFG_EXTICR3 EXTI9         MS32_SYSCFG_SetEXTISource\n
  *         SYSCFG_EXTICR3 EXTI10        MS32_SYSCFG_SetEXTISource\n
  *         SYSCFG_EXTICR3 EXTI11        MS32_SYSCFG_SetEXTISource\n
  *         SYSCFG_EXTICR4 EXTI12        MS32_SYSCFG_SetEXTISource\n
  *         SYSCFG_EXTICR4 EXTI13        MS32_SYSCFG_SetEXTISource\n
  *         SYSCFG_EXTICR4 EXTI14        MS32_SYSCFG_SetEXTISource\n
  *         SYSCFG_EXTICR4 EXTI15        MS32_SYSCFG_SetEXTISource
  * @param  Line This parameter can be one of the following values:
  *         @arg @ref MS32_SYSCFG_EXTI_LINE0
  *         @arg @ref MS32_SYSCFG_EXTI_LINE1
  *         @arg @ref MS32_SYSCFG_EXTI_LINE2
  *         @arg @ref MS32_SYSCFG_EXTI_LINE3
  *         @arg @ref MS32_SYSCFG_EXTI_LINE4
  *         @arg @ref MS32_SYSCFG_EXTI_LINE5
  *         @arg @ref MS32_SYSCFG_EXTI_LINE6
  *         @arg @ref MS32_SYSCFG_EXTI_LINE7
  *         @arg @ref MS32_SYSCFG_EXTI_LINE8
  *         @arg @ref MS32_SYSCFG_EXTI_LINE9
  *         @arg @ref MS32_SYSCFG_EXTI_LINE10
  *         @arg @ref MS32_SYSCFG_EXTI_LINE11
  *         @arg @ref MS32_SYSCFG_EXTI_LINE12
  *         @arg @ref MS32_SYSCFG_EXTI_LINE13
  *         @arg @ref MS32_SYSCFG_EXTI_LINE14
  *         @arg @ref MS32_SYSCFG_EXTI_LINE15
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_SYSCFG_EXTI_PORTA
  *         @arg @ref MS32_SYSCFG_EXTI_PORTB
  *         @arg @ref MS32_SYSCFG_EXTI_PORTC
  *         @arg @ref MS32_SYSCFG_EXTI_PORTF
  *
  *         (*) value not defined in all devices
  */
__STATIC_INLINE uint32_t MS32_SYSCFG_GetEXTISource(uint32_t Line) {
  return (uint32_t)(READ_BIT(SYSCFG->EXTICR[Line & 0xFF], (SYSCFG_EXTICR1_EXTI0 << (Line >> 16))) >> (Line >> 16));
}

/**
  * @brief  Set connections to TIMx Break inputs
  * @rmtoll SYSCFG_CFGR2 LOCKUP_LOCK   MS32_SYSCFG_SetTIMBreakInputs\n
  *         SYSCFG_CFGR2 SRAM_PARITY_LOCK  MS32_SYSCFG_SetTIMBreakInputs\n
  *         SYSCFG_CFGR2 PVD_LOCK      MS32_SYSCFG_SetTIMBreakInputs
  * @param  Break This parameter can be a combination of the following values:
  *         @arg @ref MS32_SYSCFG_TIMBREAK_PVD
  *         @arg @ref MS32_SYSCFG_TIMBREAK_SRAM_PARITY
  *         @arg @ref MS32_SYSCFG_TIMBREAK_LOCKUP
  * @retval None
  */
__STATIC_INLINE void MS32_SYSCFG_SetTIMBreakInputs(uint32_t Break) {
  MODIFY_REG(SYSCFG->CFGR2, SYSCFG_CFGR2_LOCKUP_LOCK | SYSCFG_CFGR2_SRAM_PARITY_LOCK | SYSCFG_CFGR2_PVD_LOCK, Break);
}

/**
  * @brief  Get connections to TIMx Break inputs
  * @rmtoll SYSCFG_CFGR2 LOCKUP_LOCK   MS32_SYSCFG_GetTIMBreakInputs\n
  *         SYSCFG_CFGR2 SRAM_PARITY_LOCK  MS32_SYSCFG_GetTIMBreakInputs\n
  *         SYSCFG_CFGR2 PVD_LOCK      MS32_SYSCFG_GetTIMBreakInputs
  * @retval Returned value can be can be a combination of the following values:
  *         @arg @ref MS32_SYSCFG_TIMBREAK_PVD
  *         @arg @ref MS32_SYSCFG_TIMBREAK_SRAM_PARITY
  *         @arg @ref MS32_SYSCFG_TIMBREAK_LOCKUP
  */
__STATIC_INLINE uint32_t MS32_SYSCFG_GetTIMBreakInputs(void) {
  return (uint32_t)(READ_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_LOCKUP_LOCK | SYSCFG_CFGR2_SRAM_PARITY_LOCK | SYSCFG_CFGR2_PVD_LOCK));
}

/**
  * @brief  Check if SRAM parity error detected
  * @rmtoll SYSCFG_CFGR2 SRAM_PEF      MS32_SYSCFG_IsActiveFlag_SP
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_SYSCFG_IsActiveFlag_SP(void) {
  return (READ_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_SRAM_PEF) == (SYSCFG_CFGR2_SRAM_PEF));
}

/**
  * @brief  Clear SRAM parity error flag
  * @rmtoll SYSCFG_CFGR2 SRAM_PEF      MS32_SYSCFG_ClearFlag_SP
  * @retval None
  */
__STATIC_INLINE void MS32_SYSCFG_ClearFlag_SP(void) {
  SET_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_SRAM_PEF);
}


/** @defgroup SYSTEM_EF_DBGMCU DBGMCU
  * @{
  */

/**
  * @brief  Return the device identifier
  * @note For MS32F03x devices, the device ID is 0x444
  * @rmtoll DBGMCU_IDCODE DEV_ID        MS32_DBGMCU_GetDeviceID
  * @retval Values between Min_Data=0x00 and Max_Data=0xFFF
  */
__STATIC_INLINE uint32_t MS32_DBGMCU_GetDeviceID(void) {
  return (uint32_t)(READ_BIT(DBGMCU->IDCODE, DBGMCU_IDCODE_DEV_ID));
}

/**
  * @brief  Return the device revision identifier
  * @note This field indicates the revision of the device.
          For example, it is read as 0x1000 for Revision 1.0.
  * @rmtoll DBGMCU_IDCODE REV_ID        MS32_DBGMCU_GetRevisionID
  * @retval Values between Min_Data=0x00 and Max_Data=0xFFFF
  */
__STATIC_INLINE uint32_t MS32_DBGMCU_GetRevisionID(void) {
  return (uint32_t)(READ_BIT(DBGMCU->IDCODE, DBGMCU_IDCODE_REV_ID) >> DBGMCU_IDCODE_REV_ID_Pos);
}

/**
  * @brief  Enable the Debug Module during STOP mode
  * @rmtoll DBGMCU_CR    DBG_STOP      MS32_DBGMCU_EnableDBGStopMode
  * @retval None
  */
__STATIC_INLINE void MS32_DBGMCU_EnableDBGStopMode(void) {
  SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STOP);
}

/**
  * @brief  Disable the Debug Module during STOP mode
  * @rmtoll DBGMCU_CR    DBG_STOP      MS32_DBGMCU_DisableDBGStopMode
  * @retval None
  */
__STATIC_INLINE void MS32_DBGMCU_DisableDBGStopMode(void) {
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STOP);
}

/**
  * @brief  Enable the Debug Module during STANDBY mode
  * @rmtoll DBGMCU_CR    DBG_STANDBY   MS32_DBGMCU_EnableDBGStandbyMode
  * @retval None
  */
__STATIC_INLINE void MS32_DBGMCU_EnableDBGStandbyMode(void) {
  SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STANDBY);
}

/**
  * @brief  Disable the Debug Module during STANDBY mode
  * @rmtoll DBGMCU_CR    DBG_STANDBY   MS32_DBGMCU_DisableDBGStandbyMode
  * @retval None
  */
__STATIC_INLINE void MS32_DBGMCU_DisableDBGStandbyMode(void) {
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STANDBY);
}

/**
  * @brief  Freeze APB1 peripherals (group1 peripherals)
  * @rmtoll DBGMCU_APB1FZ DBG_TIM2_STOP           MS32_DBGMCU_APB1_GRP1_FreezePeriph\n
  *         DBGMCU_APB1FZ DBG_TIM3_STOP           MS32_DBGMCU_APB1_GRP1_FreezePeriph\n
  *         DBGMCU_APB1FZ DBG_TIM6_STOP           MS32_DBGMCU_APB1_GRP1_FreezePeriph\n
  *         DBGMCU_APB1FZ DBG_TIM7_STOP           MS32_DBGMCU_APB1_GRP1_FreezePeriph\n
  *         DBGMCU_APB1FZ DBG_TIM14_STOP          MS32_DBGMCU_APB1_GRP1_FreezePeriph\n
  *         DBGMCU_APB1FZ DBG_RTC_STOP            MS32_DBGMCU_APB1_GRP1_FreezePeriph\n
  *         DBGMCU_APB1FZ DBG_WWDG_STOP           MS32_DBGMCU_APB1_GRP1_FreezePeriph\n
  *         DBGMCU_APB1FZ DBG_IWDG_STOP           MS32_DBGMCU_APB1_GRP1_FreezePeriph\n
  *         DBGMCU_APB1FZ DBG_I2C1_SMBUS_TIMEOUT  MS32_DBGMCU_APB1_GRP1_FreezePeriph\n
  *         DBGMCU_APB1FZ DBG_CAN_STOP  MS32_DBGMCU_APB1_GRP1_FreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref MS32_DBGMCU_APB1_GRP1_TIM2_STOP
  *         @arg @ref MS32_DBGMCU_APB1_GRP1_TIM3_STOP
  *         @arg @ref MS32_DBGMCU_APB1_GRP1_TIM14_STOP
  *         @arg @ref MS32_DBGMCU_APB1_GRP1_RTC_STOP
  *         @arg @ref MS32_DBGMCU_APB1_GRP1_WWDG_STOP
  *         @arg @ref MS32_DBGMCU_APB1_GRP1_IWDG_STOP
  *         @arg @ref MS32_DBGMCU_APB1_GRP1_I2C1_STOP
  *
  *         (*) value not defined in all devices
  * @retval None
  */
__STATIC_INLINE void MS32_DBGMCU_APB1_GRP1_FreezePeriph(uint32_t Periphs) {
  SET_BIT(DBGMCU->APB1FZ, Periphs);
}

/**
  * @brief  Unfreeze APB1 peripherals (group1 peripherals)
  * @rmtoll DBGMCU_APB1FZ DBG_TIM2_STOP           MS32_DBGMCU_APB1_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB1FZ DBG_TIM3_STOP           MS32_DBGMCU_APB1_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB1FZ DBG_TIM6_STOP           MS32_DBGMCU_APB1_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB1FZ DBG_TIM7_STOP           MS32_DBGMCU_APB1_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB1FZ DBG_TIM14_STOP          MS32_DBGMCU_APB1_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB1FZ DBG_RTC_STOP            MS32_DBGMCU_APB1_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB1FZ DBG_WWDG_STOP           MS32_DBGMCU_APB1_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB1FZ DBG_IWDG_STOP           MS32_DBGMCU_APB1_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB1FZ DBG_I2C1_SMBUS_TIMEOUT  MS32_DBGMCU_APB1_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB1FZ DBG_CAN_STOP            MS32_DBGMCU_APB1_GRP1_UnFreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref MS32_DBGMCU_APB1_GRP1_TIM2_STOP
  *         @arg @ref MS32_DBGMCU_APB1_GRP1_TIM3_STOP
  *         @arg @ref MS32_DBGMCU_APB1_GRP1_TIM14_STOP
  *         @arg @ref MS32_DBGMCU_APB1_GRP1_RTC_STOP
  *         @arg @ref MS32_DBGMCU_APB1_GRP1_WWDG_STOP
  *         @arg @ref MS32_DBGMCU_APB1_GRP1_IWDG_STOP
  *         @arg @ref MS32_DBGMCU_APB1_GRP1_I2C1_STOP
  *
  *         (*) value not defined in all devices
  * @retval None
  */
__STATIC_INLINE void MS32_DBGMCU_APB1_GRP1_UnFreezePeriph(uint32_t Periphs) {
  CLEAR_BIT(DBGMCU->APB1FZ, Periphs);
}

/**
  * @brief  Freeze APB1 peripherals (group2 peripherals)
  * @rmtoll DBGMCU_APB2FZ DBG_TIM1_STOP   MS32_DBGMCU_APB1_GRP2_FreezePeriph\n
  *         DBGMCU_APB2FZ DBG_TIM15_STOP  MS32_DBGMCU_APB1_GRP2_FreezePeriph\n
  *         DBGMCU_APB2FZ DBG_TIM16_STOP  MS32_DBGMCU_APB1_GRP2_FreezePeriph\n
  *         DBGMCU_APB2FZ DBG_TIM17_STOP  MS32_DBGMCU_APB1_GRP2_FreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref MS32_DBGMCU_APB1_GRP2_TIM1_STOP
  *         @arg @ref MS32_DBGMCU_APB1_GRP2_TIM16_STOP
  *         @arg @ref MS32_DBGMCU_APB1_GRP2_TIM17_STOP
  *
  *         (*) value not defined in all devices
  * @retval None
  */
__STATIC_INLINE void MS32_DBGMCU_APB1_GRP2_FreezePeriph(uint32_t Periphs) {
  SET_BIT(DBGMCU->APB2FZ, Periphs);
}

/**
  * @brief  Unfreeze APB1 peripherals (group2 peripherals)
  * @rmtoll DBGMCU_APB2FZ DBG_TIM1_STOP   MS32_DBGMCU_APB1_GRP2_UnFreezePeriph\n
  *         DBGMCU_APB2FZ DBG_TIM15_STOP  MS32_DBGMCU_APB1_GRP2_UnFreezePeriph\n
  *         DBGMCU_APB2FZ DBG_TIM16_STOP  MS32_DBGMCU_APB1_GRP2_UnFreezePeriph\n
  *         DBGMCU_APB2FZ DBG_TIM17_STOP  MS32_DBGMCU_APB1_GRP2_UnFreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref MS32_DBGMCU_APB1_GRP2_TIM1_STOP
  *         @arg @ref MS32_DBGMCU_APB1_GRP2_TIM16_STOP
  *         @arg @ref MS32_DBGMCU_APB1_GRP2_TIM17_STOP
  *
  *         (*) value not defined in all devices
  * @retval None
  */
__STATIC_INLINE void MS32_DBGMCU_APB1_GRP2_UnFreezePeriph(uint32_t Periphs) {
  CLEAR_BIT(DBGMCU->APB2FZ, Periphs);
}

/** @defgroup SYSTEM_EF_FLASH FLASH
  * @{
  */

/**
  * @brief  Set FLASH Latency
  * @rmtoll FLASH_ACR    LATENCY       MS32_FLASH_SetLatency
  * @param  Latency This parameter can be one of the following values:
  *         @arg @ref MS32_FLASH_LATENCY_0
  *         @arg @ref MS32_FLASH_LATENCY_1
  * @retval None
  */
__STATIC_INLINE void MS32_FLASH_SetLatency(uint32_t Latency) {
  MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, Latency);
}

/**
  * @brief  Get FLASH Latency
  * @rmtoll FLASH_ACR    LATENCY       MS32_FLASH_GetLatency
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_FLASH_LATENCY_0
  *         @arg @ref MS32_FLASH_LATENCY_1
  */
__STATIC_INLINE uint32_t MS32_FLASH_GetLatency(void) {
  return (uint32_t)(READ_BIT(FLASH->ACR, FLASH_ACR_LATENCY));
}

/**
  * @brief  Enable Prefetch
  * @rmtoll FLASH_ACR    PRFTBE        MS32_FLASH_EnablePrefetch
  * @retval None
  */
__STATIC_INLINE void MS32_FLASH_EnablePrefetch(void) {
  SET_BIT(FLASH->ACR, FLASH_ACR_PRFTBE);
}

/**
  * @brief  Disable Prefetch
  * @rmtoll FLASH_ACR    PRFTBE        MS32_FLASH_DisablePrefetch
  * @retval None
  */
__STATIC_INLINE void MS32_FLASH_DisablePrefetch(void) {
  CLEAR_BIT(FLASH->ACR, FLASH_ACR_PRFTBE);
}

/**
  * @brief  Check if Prefetch buffer is enabled
  * @rmtoll FLASH_ACR    PRFTBS        MS32_FLASH_IsPrefetchEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_FLASH_IsPrefetchEnabled(void) {
  return (READ_BIT(FLASH->ACR, FLASH_ACR_PRFTBS) == (FLASH_ACR_PRFTBS));
}


#ifdef __cplusplus
}
#endif

#endif /* __MS32F0XX_SYSTEM_H */

/******************************** END OF FILE *********************************/
