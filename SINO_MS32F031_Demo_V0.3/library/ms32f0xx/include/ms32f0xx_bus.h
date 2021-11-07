/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MS32F0XX_BUS_H
#define __MS32F0XX_BUS_H

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
/** @defgroup BUS_EC_AHB1_GRP1_PERIPH  AHB1 GRP1 PERIPH
  * @{
  */
#define MS32_AHB1_GRP1_PERIPH_ALL            (uint32_t)0xFFFFFFFFU
#define MS32_AHB1_GRP1_PERIPH_DMA1           RCC_AHBENR_DMAEN
#define MS32_AHB1_GRP1_PERIPH_SRAM           RCC_AHBENR_SRAMEN
#define MS32_AHB1_GRP1_PERIPH_FLITF          RCC_AHBENR_FLITFEN
#define MS32_AHB1_GRP1_PERIPH_CRC            RCC_AHBENR_CRCEN
#define MS32_AHB1_GRP1_PERIPH_GPIOA          RCC_AHBENR_GPIOAEN
#define MS32_AHB1_GRP1_PERIPH_GPIOB          RCC_AHBENR_GPIOBEN
#define MS32_AHB1_GRP1_PERIPH_GPIOC          RCC_AHBENR_GPIOCEN
#define MS32_AHB1_GRP1_PERIPH_GPIOF          RCC_AHBENR_GPIOFEN


/** @defgroup BUS_EC_APB1_GRP1_PERIPH  APB1 GRP1 PERIPH
  * @{
  */
#define MS32_APB1_GRP1_PERIPH_ALL            (uint32_t)0xFFFFFFFFU
#define MS32_APB1_GRP1_PERIPH_TIM2           RCC_APB1ENR_TIM2EN
#define MS32_APB1_GRP1_PERIPH_TIM3           RCC_APB1ENR_TIM3EN
#define MS32_APB1_GRP1_PERIPH_TIM14          RCC_APB1ENR_TIM14EN
#define MS32_APB1_GRP1_PERIPH_WWDG           RCC_APB1ENR_WWDGEN
#define MS32_APB1_GRP1_PERIPH_I2C1           RCC_APB1ENR_I2C1EN
#define MS32_APB1_GRP1_PERIPH_PWR            RCC_APB1ENR_PWREN


/** @defgroup BUS_EC_APB1_GRP2_PERIPH  APB1 GRP2 PERIPH
  * @{
  */
#define MS32_APB1_GRP2_PERIPH_ALL            (uint32_t)0xFFFFFFFFU
#define MS32_APB1_GRP2_PERIPH_SYSCFG         RCC_APB2ENR_SYSCFGCOMPEN
#define MS32_APB1_GRP2_PERIPH_ADC1           RCC_APB2ENR_ADCEN
#define MS32_APB1_GRP2_PERIPH_TIM1           RCC_APB2ENR_TIM1EN
#define MS32_APB1_GRP2_PERIPH_SPI1           RCC_APB2ENR_SPI1EN
#define MS32_APB1_GRP2_PERIPH_USART1         RCC_APB2ENR_USART1EN
#define MS32_APB1_GRP2_PERIPH_TIM16          RCC_APB2ENR_TIM16EN
#define MS32_APB1_GRP2_PERIPH_TIM17          RCC_APB2ENR_TIM17EN
#define MS32_APB1_GRP2_PERIPH_DBGMCU         RCC_APB2ENR_DBGMCUEN


/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @defgroup BUS_MS32_EF_AHB1 AHB1
  * @{
  */

/**
  * @brief  Enable AHB1 peripherals clock.
  * @rmtoll AHBENR       DMA1EN        MS32_AHB1_GRP1_EnableClock\n
  *         AHBENR       SRAMEN        MS32_AHB1_GRP1_EnableClock\n
  *         AHBENR       FLITFEN       MS32_AHB1_GRP1_EnableClock\n
  *         AHBENR       CRCEN         MS32_AHB1_GRP1_EnableClock\n
  *         AHBENR       GPIOAEN       MS32_AHB1_GRP1_EnableClock\n
  *         AHBENR       GPIOBEN       MS32_AHB1_GRP1_EnableClock\n
  *         AHBENR       GPIOCEN       MS32_AHB1_GRP1_EnableClock\n
  *         AHBENR       GPIOFEN       MS32_AHB1_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref MS32_AHB1_GRP1_PERIPH_DMA1
  *         @arg @ref MS32_AHB1_GRP1_PERIPH_SRAM
  *         @arg @ref MS32_AHB1_GRP1_PERIPH_FLITF
  *         @arg @ref MS32_AHB1_GRP1_PERIPH_CRC
  *         @arg @ref MS32_AHB1_GRP1_PERIPH_GPIOA
  *         @arg @ref MS32_AHB1_GRP1_PERIPH_GPIOB
  *         @arg @ref MS32_AHB1_GRP1_PERIPH_GPIOC
  *         @arg @ref MS32_AHB1_GRP1_PERIPH_GPIOF
  * @retval None
*/
__STATIC_INLINE void MS32_AHB1_GRP1_EnableClock(uint32_t Periphs) {
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHBENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->AHBENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if AHB1 peripheral clock is enabled or not
  * @rmtoll AHBENR       DMA1EN        MS32_AHB1_GRP1_IsEnabledClock\n
  *         AHBENR       SRAMEN        MS32_AHB1_GRP1_IsEnabledClock\n
  *         AHBENR       FLITFEN       MS32_AHB1_GRP1_IsEnabledClock\n
  *         AHBENR       CRCEN         MS32_AHB1_GRP1_IsEnabledClock\n
  *         AHBENR       GPIOAEN       MS32_AHB1_GRP1_IsEnabledClock\n
  *         AHBENR       GPIOBEN       MS32_AHB1_GRP1_IsEnabledClock\n
  *         AHBENR       GPIOCEN       MS32_AHB1_GRP1_IsEnabledClock\n
  *         AHBENR       GPIOFEN       MS32_AHB1_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref MS32_AHB1_GRP1_PERIPH_DMA1
  *         @arg @ref MS32_AHB1_GRP1_PERIPH_SRAM
  *         @arg @ref MS32_AHB1_GRP1_PERIPH_FLITF
  *         @arg @ref MS32_AHB1_GRP1_PERIPH_CRC
  *         @arg @ref MS32_AHB1_GRP1_PERIPH_GPIOA
  *         @arg @ref MS32_AHB1_GRP1_PERIPH_GPIOB
  *         @arg @ref MS32_AHB1_GRP1_PERIPH_GPIOC
  *         @arg @ref MS32_AHB1_GRP1_PERIPH_GPIOF
  * @retval State of Periphs (1 or 0).
*/
__STATIC_INLINE uint32_t MS32_AHB1_GRP1_IsEnabledClock(uint32_t Periphs) {
  return (READ_BIT(RCC->AHBENR, Periphs) == Periphs);
}

/**
  * @brief  Disable AHB1 peripherals clock.
  * @rmtoll AHBENR       DMA1EN        MS32_AHB1_GRP1_DisableClock\n
  *         AHBENR       SRAMEN        MS32_AHB1_GRP1_DisableClock\n
  *         AHBENR       FLITFEN       MS32_AHB1_GRP1_DisableClock\n
  *         AHBENR       CRCEN         MS32_AHB1_GRP1_DisableClock\n
  *         AHBENR       GPIOAEN       MS32_AHB1_GRP1_DisableClock\n
  *         AHBENR       GPIOBEN       MS32_AHB1_GRP1_DisableClock\n
  *         AHBENR       GPIOCEN       MS32_AHB1_GRP1_DisableClock\n
  *         AHBENR       GPIOFEN       MS32_AHB1_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref MS32_AHB1_GRP1_PERIPH_DMA1
  *         @arg @ref MS32_AHB1_GRP1_PERIPH_SRAM
  *         @arg @ref MS32_AHB1_GRP1_PERIPH_FLITF
  *         @arg @ref MS32_AHB1_GRP1_PERIPH_CRC
  *         @arg @ref MS32_AHB1_GRP1_PERIPH_GPIOA
  *         @arg @ref MS32_AHB1_GRP1_PERIPH_GPIOB
  *         @arg @ref MS32_AHB1_GRP1_PERIPH_GPIOC
  *         @arg @ref MS32_AHB1_GRP1_PERIPH_GPIOF
  * @retval None
*/
__STATIC_INLINE void MS32_AHB1_GRP1_DisableClock(uint32_t Periphs) {
  CLEAR_BIT(RCC->AHBENR, Periphs);
}

/**
  * @brief  Force AHB1 peripherals reset.
  * @rmtoll AHBRSTR      GPIOARST      MS32_AHB1_GRP1_ForceReset\n
  *         AHBRSTR      GPIOBRST      MS32_AHB1_GRP1_ForceReset\n
  *         AHBRSTR      GPIOCRST      MS32_AHB1_GRP1_ForceReset\n
  *         AHBRSTR      GPIOFRST      MS32_AHB1_GRP1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref MS32_AHB1_GRP1_PERIPH_ALL
  *         @arg @ref MS32_AHB1_GRP1_PERIPH_GPIOA
  *         @arg @ref MS32_AHB1_GRP1_PERIPH_GPIOB
  *         @arg @ref MS32_AHB1_GRP1_PERIPH_GPIOC
  *         @arg @ref MS32_AHB1_GRP1_PERIPH_GPIOF
  * @retval None
*/
__STATIC_INLINE void MS32_AHB1_GRP1_ForceReset(uint32_t Periphs) {
  SET_BIT(RCC->AHBRSTR, Periphs);
}

/**
  * @brief  Release AHB1 peripherals reset.
  * @rmtoll AHBRSTR      GPIOARST      MS32_AHB1_GRP1_ReleaseReset\n
  *         AHBRSTR      GPIOBRST      MS32_AHB1_GRP1_ReleaseReset\n
  *         AHBRSTR      GPIOCRST      MS32_AHB1_GRP1_ReleaseReset
  *         AHBRSTR      GPIOFRST      MS32_AHB1_GRP1_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref MS32_AHB1_GRP1_PERIPH_ALL
  *         @arg @ref MS32_AHB1_GRP1_PERIPH_GPIOA
  *         @arg @ref MS32_AHB1_GRP1_PERIPH_GPIOB
  *         @arg @ref MS32_AHB1_GRP1_PERIPH_GPIOC
  *         @arg @ref MS32_AHB1_GRP1_PERIPH_GPIOF
  * @retval None
*/
__STATIC_INLINE void MS32_AHB1_GRP1_ReleaseReset(uint32_t Periphs) {
  CLEAR_BIT(RCC->AHBRSTR, Periphs);
}


/** @defgroup BUS_MS32_EF_APB1_GRP1 APB1 GRP1
  * @{
  */

/**
  * @brief  Enable APB1 peripherals clock (available in register 1).
  * @rmtoll APB1ENR      TIM2EN        MS32_APB1_GRP1_EnableClock\n
  *         APB1ENR      TIM3EN        MS32_APB1_GRP1_EnableClock\n
  *         APB1ENR      TIM14EN       MS32_APB1_GRP1_EnableClock\n
  *         APB1ENR      WWDGEN        MS32_APB1_GRP1_EnableClock\n
  *         APB1ENR      I2C1EN        MS32_APB1_GRP1_EnableClock\n
  *         APB1ENR      PWREN         MS32_APB1_GRP1_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref MS32_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref MS32_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref MS32_APB1_GRP1_PERIPH_TIM14
  *         @arg @ref MS32_APB1_GRP1_PERIPH_WWDG
  *         @arg @ref MS32_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref MS32_APB1_GRP1_PERIPH_PWR
  * @retval None
*/
__STATIC_INLINE void MS32_APB1_GRP1_EnableClock(uint32_t Periphs) {
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB1ENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB1ENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB1 peripheral clock is enabled or not (available in register 1).
  * @rmtoll APB1ENR      TIM2EN        MS32_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR      TIM3EN        MS32_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR      TIM14EN       MS32_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR      WWDGEN        MS32_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR      I2C1EN        MS32_APB1_GRP1_IsEnabledClock\n
  *         APB1ENR      PWREN         MS32_APB1_GRP1_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref MS32_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref MS32_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref MS32_APB1_GRP1_PERIPH_TIM14
  *         @arg @ref MS32_APB1_GRP1_PERIPH_WWDG
  *         @arg @ref MS32_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref MS32_APB1_GRP1_PERIPH_PWR
  * @retval State of Periphs (1 or 0).
*/
__STATIC_INLINE uint32_t MS32_APB1_GRP1_IsEnabledClock(uint32_t Periphs) {
  return (READ_BIT(RCC->APB1ENR, Periphs) == Periphs);
}

/**
  * @brief  Disable APB1 peripherals clock (available in register 1).
  * @rmtoll APB1ENR      TIM2EN        MS32_APB1_GRP1_DisableClock\n
  *         APB1ENR      TIM3EN        MS32_APB1_GRP1_DisableClock\n
  *         APB1ENR      TIM14EN       MS32_APB1_GRP1_DisableClock\n
  *         APB1ENR      WWDGEN        MS32_APB1_GRP1_DisableClock\n
  *         APB1ENR      I2C1EN        MS32_APB1_GRP1_DisableClock\n
  *         APB1ENR      PWREN         MS32_APB1_GRP1_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref MS32_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref MS32_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref MS32_APB1_GRP1_PERIPH_TIM14
  *         @arg @ref MS32_APB1_GRP1_PERIPH_WWDG
  *         @arg @ref MS32_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref MS32_APB1_GRP1_PERIPH_PWR
  * @retval None
*/
__STATIC_INLINE void MS32_APB1_GRP1_DisableClock(uint32_t Periphs) {
  CLEAR_BIT(RCC->APB1ENR, Periphs);
}

/**
  * @brief  Force APB1 peripherals reset (available in register 1).
  * @rmtoll APB1RSTR     TIM2RST       MS32_APB1_GRP1_ForceReset\n
  *         APB1RSTR     TIM3RST       MS32_APB1_GRP1_ForceReset\n
  *         APB1RSTR     TIM14RST      MS32_APB1_GRP1_ForceReset\n
  *         APB1RSTR     WWDGRST       MS32_APB1_GRP1_ForceReset\n
  *         APB1RSTR     I2C1RST       MS32_APB1_GRP1_ForceReset\n
  *         APB1RSTR     PWRRST        MS32_APB1_GRP1_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref MS32_APB1_GRP1_PERIPH_ALL
  *         @arg @ref MS32_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref MS32_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref MS32_APB1_GRP1_PERIPH_TIM14
  *         @arg @ref MS32_APB1_GRP1_PERIPH_WWDG
  *         @arg @ref MS32_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref MS32_APB1_GRP1_PERIPH_PWR
  * @retval None
*/
__STATIC_INLINE void MS32_APB1_GRP1_ForceReset(uint32_t Periphs) {
  SET_BIT(RCC->APB1RSTR, Periphs);
}

/**
  * @brief  Release APB1 peripherals reset (available in register 1).
  * @rmtoll APB1RSTR     TIM2RST       MS32_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR     TIM3RST       MS32_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR     TIM14RST      MS32_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR     WWDGRST       MS32_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR     I2C1RST       MS32_APB1_GRP1_ReleaseReset\n
  *         APB1RSTR     PWRRST        MS32_APB1_GRP1_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref MS32_APB1_GRP1_PERIPH_ALL
  *         @arg @ref MS32_APB1_GRP1_PERIPH_TIM2
  *         @arg @ref MS32_APB1_GRP1_PERIPH_TIM3
  *         @arg @ref MS32_APB1_GRP1_PERIPH_TIM14
  *         @arg @ref MS32_APB1_GRP1_PERIPH_WWDG
  *         @arg @ref MS32_APB1_GRP1_PERIPH_I2C1
  *         @arg @ref MS32_APB1_GRP1_PERIPH_PWR
  * @retval None
*/
__STATIC_INLINE void MS32_APB1_GRP1_ReleaseReset(uint32_t Periphs) {
  CLEAR_BIT(RCC->APB1RSTR, Periphs);
}


/** @defgroup BUS_MS32_EF_APB1_GRP2 APB1 GRP2
  * @{
  */

/**
  * @brief  Enable APB1 peripherals clock (available in register 2).
  * @rmtoll APB2ENR      SYSCFGEN      MS32_APB1_GRP2_EnableClock\n
  *         APB2ENR      ADC1EN        MS32_APB1_GRP2_EnableClock\n
  *         APB2ENR      TIM1EN        MS32_APB1_GRP2_EnableClock\n
  *         APB2ENR      SPI1EN        MS32_APB1_GRP2_EnableClock\n
  *         APB2ENR      USART1EN      MS32_APB1_GRP2_EnableClock\n
  *         APB2ENR      TIM16EN       MS32_APB1_GRP2_EnableClock\n
  *         APB2ENR      TIM17EN       MS32_APB1_GRP2_EnableClock\n
  *         APB2ENR      DBGMCUEN      MS32_APB1_GRP2_EnableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref MS32_APB1_GRP2_PERIPH_SYSCFG
  *         @arg @ref MS32_APB1_GRP2_PERIPH_ADC1
  *         @arg @ref MS32_APB1_GRP2_PERIPH_TIM1
  *         @arg @ref MS32_APB1_GRP2_PERIPH_SPI1
  *         @arg @ref MS32_APB1_GRP2_PERIPH_USART1
  *         @arg @ref MS32_APB1_GRP2_PERIPH_TIM16
  *         @arg @ref MS32_APB1_GRP2_PERIPH_TIM17
  *         @arg @ref MS32_APB1_GRP2_PERIPH_DBGMCU
  * @retval None
*/
__STATIC_INLINE void MS32_APB1_GRP2_EnableClock(uint32_t Periphs) {
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB2ENR, Periphs);
  /* Delay after an RCC peripheral clock enabling */
  tmpreg = READ_BIT(RCC->APB2ENR, Periphs);
  (void)tmpreg;
}

/**
  * @brief  Check if APB1 peripheral clock is enabled or not (available in register 2).
  * @rmtoll APB2ENR      SYSCFGEN      MS32_APB1_GRP2_IsEnabledClock\n
  *         APB2ENR      ADC1EN        MS32_APB1_GRP2_IsEnabledClock\n
  *         APB2ENR      TIM1EN        MS32_APB1_GRP2_IsEnabledClock\n
  *         APB2ENR      SPI1EN        MS32_APB1_GRP2_IsEnabledClock\n
  *         APB2ENR      USART1EN      MS32_APB1_GRP2_IsEnabledClock\n
  *         APB2ENR      TIM16EN       MS32_APB1_GRP2_IsEnabledClock\n
  *         APB2ENR      TIM17EN       MS32_APB1_GRP2_IsEnabledClock\n
  *         APB2ENR      DBGMCUEN      MS32_APB1_GRP2_IsEnabledClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref MS32_APB1_GRP2_PERIPH_SYSCFG
  *         @arg @ref MS32_APB1_GRP2_PERIPH_ADC1
  *         @arg @ref MS32_APB1_GRP2_PERIPH_TIM1
  *         @arg @ref MS32_APB1_GRP2_PERIPH_SPI1
  *         @arg @ref MS32_APB1_GRP2_PERIPH_USART1
  *         @arg @ref MS32_APB1_GRP2_PERIPH_TIM16
  *         @arg @ref MS32_APB1_GRP2_PERIPH_TIM17
  *         @arg @ref MS32_APB1_GRP2_PERIPH_DBGMCU
  * @retval State of Periphs (1 or 0).
*/
__STATIC_INLINE uint32_t MS32_APB1_GRP2_IsEnabledClock(uint32_t Periphs) {
  return (READ_BIT(RCC->APB2ENR, Periphs) == Periphs);
}

/**
  * @brief  Disable APB1 peripherals clock (available in register 2).
  * @rmtoll APB2ENR      SYSCFGEN      MS32_APB1_GRP2_DisableClock\n
  *         APB2ENR      ADC1EN        MS32_APB1_GRP2_DisableClock\n
  *         APB2ENR      TIM1EN        MS32_APB1_GRP2_DisableClock\n
  *         APB2ENR      SPI1EN        MS32_APB1_GRP2_DisableClock\n
  *         APB2ENR      USART1EN      MS32_APB1_GRP2_DisableClock\n
  *         APB2ENR      TIM16EN       MS32_APB1_GRP2_DisableClock\n
  *         APB2ENR      TIM17EN       MS32_APB1_GRP2_DisableClock\n
  *         APB2ENR      DBGMCUEN      MS32_APB1_GRP2_DisableClock
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref MS32_APB1_GRP2_PERIPH_SYSCFG
  *         @arg @ref MS32_APB1_GRP2_PERIPH_ADC1
  *         @arg @ref MS32_APB1_GRP2_PERIPH_TIM1
  *         @arg @ref MS32_APB1_GRP2_PERIPH_SPI1
  *         @arg @ref MS32_APB1_GRP2_PERIPH_USART1
  *         @arg @ref MS32_APB1_GRP2_PERIPH_TIM16
  *         @arg @ref MS32_APB1_GRP2_PERIPH_TIM17
  *         @arg @ref MS32_APB1_GRP2_PERIPH_DBGMCU
  * @retval None
*/
__STATIC_INLINE void MS32_APB1_GRP2_DisableClock(uint32_t Periphs) {
  CLEAR_BIT(RCC->APB2ENR, Periphs);
}

/**
  * @brief  Force APB1 peripherals reset (available in register 2).
  * @rmtoll APB2RSTR     SYSCFGRST     MS32_APB1_GRP2_ForceReset\n
  *         APB2RSTR     ADC1RST       MS32_APB1_GRP2_ForceReset\n
  *         APB2RSTR     TIM1RST       MS32_APB1_GRP2_ForceReset\n
  *         APB2RSTR     SPI1RST       MS32_APB1_GRP2_ForceReset\n
  *         APB2RSTR     USART1RST     MS32_APB1_GRP2_ForceReset\n
  *         APB2RSTR     TIM16RST      MS32_APB1_GRP2_ForceReset\n
  *         APB2RSTR     TIM17RST      MS32_APB1_GRP2_ForceReset\n
  *         APB2RSTR     DBGMCURST     MS32_APB1_GRP2_ForceReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref MS32_APB1_GRP2_PERIPH_ALL
  *         @arg @ref MS32_APB1_GRP2_PERIPH_SYSCFG
  *         @arg @ref MS32_APB1_GRP2_PERIPH_ADC1
  *         @arg @ref MS32_APB1_GRP2_PERIPH_TIM1
  *         @arg @ref MS32_APB1_GRP2_PERIPH_SPI1
  *         @arg @ref MS32_APB1_GRP2_PERIPH_USART1
  *         @arg @ref MS32_APB1_GRP2_PERIPH_TIM16
  *         @arg @ref MS32_APB1_GRP2_PERIPH_TIM17
  *         @arg @ref MS32_APB1_GRP2_PERIPH_DBGMCU
  * @retval None
*/
__STATIC_INLINE void MS32_APB1_GRP2_ForceReset(uint32_t Periphs) {
  SET_BIT(RCC->APB2RSTR, Periphs);
}

/**
  * @brief  Release APB1 peripherals reset (available in register 2).
  * @rmtoll APB2RSTR     SYSCFGRST     MS32_APB1_GRP2_ReleaseReset\n
  *         APB2RSTR     ADC1RST       MS32_APB1_GRP2_ReleaseReset\n
  *         APB2RSTR     TIM1RST       MS32_APB1_GRP2_ReleaseReset\n
  *         APB2RSTR     SPI1RST       MS32_APB1_GRP2_ReleaseReset\n
  *         APB2RSTR     USART1RST     MS32_APB1_GRP2_ReleaseReset\n
  *         APB2RSTR     TIM16RST      MS32_APB1_GRP2_ReleaseReset\n
  *         APB2RSTR     TIM17RST      MS32_APB1_GRP2_ReleaseReset\n
  *         APB2RSTR     DBGMCURST     MS32_APB1_GRP2_ReleaseReset
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref MS32_APB1_GRP2_PERIPH_ALL
  *         @arg @ref MS32_APB1_GRP2_PERIPH_SYSCFG
  *         @arg @ref MS32_APB1_GRP2_PERIPH_ADC1
  *         @arg @ref MS32_APB1_GRP2_PERIPH_TIM1
  *         @arg @ref MS32_APB1_GRP2_PERIPH_SPI1
  *         @arg @ref MS32_APB1_GRP2_PERIPH_USART1
  *         @arg @ref MS32_APB1_GRP2_PERIPH_TIM16
  *         @arg @ref MS32_APB1_GRP2_PERIPH_TIM17
  *         @arg @ref MS32_APB1_GRP2_PERIPH_DBGMCU
  * @retval None
*/
__STATIC_INLINE void MS32_APB1_GRP2_ReleaseReset(uint32_t Periphs) {
  CLEAR_BIT(RCC->APB2RSTR, Periphs);
}


#ifdef __cplusplus
}
#endif

#endif /* __MS32F0XX_BUS_H */

/******************************** END OF FILE *********************************/
