/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MS32F0XX_GPIO_H
#define __MS32F0XX_GPIO_H

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
/** @defgroup GPIO_Exported_Types GPIO Exported Types
  * @{
  */

/**
  * @brief GPIO_ES_INIT GPIO Exported Init structures
  */
typedef struct {
  uint32_t Pin;          /*!< Specifies the GPIO pins to be configured.
                              This parameter can be any value of @ref GPIO_EC_PIN */
  uint32_t Mode;         /*!< Specifies the operating mode for the selected pins.
                              This parameter can be a value of @ref GPIO_EC_MODE.
                              GPIO HW configuration can be modified afterwards using unitary function @ref MS32_GPIO_SetPinMode().*/
  uint32_t Speed;        /*!< Specifies the speed for the selected pins.
                              This parameter can be a value of @ref GPIO_EC_SPEED.
                              GPIO HW configuration can be modified afterwards using unitary function @ref MS32_GPIO_SetPinSpeed().*/
  uint32_t OutputType;   /*!< Specifies the operating output type for the selected pins.
                              This parameter can be a value of @ref GPIO_EC_OUTPUT.
                              GPIO HW configuration can be modified afterwards using unitary function @ref MS32_GPIO_SetPinOutputType().*/
  uint32_t Pull;         /*!< Specifies the operating Pull-up/Pull down for the selected pins.
                              This parameter can be a value of @ref GPIO_EC_PULL.
                              GPIO HW configuration can be modified afterwards using unitary function @ref MS32_GPIO_SetPinPull().*/
  uint32_t Alternate;    /*!< Specifies the Peripheral to be connected to the selected pins.
                              This parameter can be a value of @ref GPIO_EC_AF.
                              GPIO HW configuration can be modified afterwards using unitary function @ref MS32_GPIO_SetAFPin_0_7() and MS32_GPIO_SetAFPin_8_15().*/
} MS32_GPIO_InitTypeDef;


/* Exported constants --------------------------------------------------------*/
/** @defgroup MS32_GPIO_Exported_Constants GPIO Exported Constants
  * @{
  */

/** @defgroup GPIO_EC_OUTPUT Output Type
  * @{
  */
#define MS32_GPIO_OUTPUT_HIGH                (0x00000000U)
#define MS32_GPIO_OUTPUT_LOW                 (0x00000001U)
#define MS32_GPIO_OUTPUT_REV                 (0x00000002U)

/** @defgroup GPIO_EC_PIN PIN
  * @{
  */
#define MS32_GPIO_PIN_0                      GPIO_BSRR_BS_0 /*!< Select pin 0 */
#define MS32_GPIO_PIN_1                      GPIO_BSRR_BS_1 /*!< Select pin 1 */
#define MS32_GPIO_PIN_2                      GPIO_BSRR_BS_2 /*!< Select pin 2 */
#define MS32_GPIO_PIN_3                      GPIO_BSRR_BS_3 /*!< Select pin 3 */
#define MS32_GPIO_PIN_4                      GPIO_BSRR_BS_4 /*!< Select pin 4 */
#define MS32_GPIO_PIN_5                      GPIO_BSRR_BS_5 /*!< Select pin 5 */
#define MS32_GPIO_PIN_6                      GPIO_BSRR_BS_6 /*!< Select pin 6 */
#define MS32_GPIO_PIN_7                      GPIO_BSRR_BS_7 /*!< Select pin 7 */
#define MS32_GPIO_PIN_8                      GPIO_BSRR_BS_8 /*!< Select pin 8 */
#define MS32_GPIO_PIN_9                      GPIO_BSRR_BS_9 /*!< Select pin 9 */
#define MS32_GPIO_PIN_10                     GPIO_BSRR_BS_10 /*!< Select pin 10 */
#define MS32_GPIO_PIN_11                     GPIO_BSRR_BS_11 /*!< Select pin 11 */
#define MS32_GPIO_PIN_12                     GPIO_BSRR_BS_12 /*!< Select pin 12 */
#define MS32_GPIO_PIN_13                     GPIO_BSRR_BS_13 /*!< Select pin 13 */
#define MS32_GPIO_PIN_14                     GPIO_BSRR_BS_14 /*!< Select pin 14 */
#define MS32_GPIO_PIN_15                     GPIO_BSRR_BS_15 /*!< Select pin 15 */
#define MS32_GPIO_PIN_ALL                    (GPIO_BSRR_BS_0  | GPIO_BSRR_BS_1  | GPIO_BSRR_BS_2  | \
                                              GPIO_BSRR_BS_3  | GPIO_BSRR_BS_4  | GPIO_BSRR_BS_5  | \
                                              GPIO_BSRR_BS_6  | GPIO_BSRR_BS_7  | GPIO_BSRR_BS_8  | \
                                              GPIO_BSRR_BS_9  | GPIO_BSRR_BS_10 | GPIO_BSRR_BS_11 | \
                                              GPIO_BSRR_BS_12 | GPIO_BSRR_BS_13 | GPIO_BSRR_BS_14 | \
                                              GPIO_BSRR_BS_15) /*!< Select all pins */

/** @defgroup GPIO_EC_MODE Mode
  * @{
  */
#define MS32_GPIO_MODE_INPUT                 (0x00000000U) /*!< Select input mode */
#define MS32_GPIO_MODE_OUTPUT                GPIO_MODER_MODER0_0  /*!< Select output mode */
#define MS32_GPIO_MODE_ALTERNATE             GPIO_MODER_MODER0_1  /*!< Select alternate function mode */
#define MS32_GPIO_MODE_ANALOG                GPIO_MODER_MODER0    /*!< Select analog mode */

/** @defgroup GPIO_EC_OUTPUT Output Type
  * @{
  */
#define MS32_GPIO_OUTPUT_PUSHPULL            (0x00000000U) /*!< Select push-pull as output type */
#define MS32_GPIO_OUTPUT_OPENDRAIN           GPIO_OTYPER_OT_0 /*!< Select open-drain as output type */

/** @defgroup GPIO_EC_SPEED Output Speed
  * @{
  */
#define MS32_GPIO_SPEED_FREQ_LOW             (0x00000000U) /*!< Select I/O low output speed    */
#define MS32_GPIO_SPEED_FREQ_MEDIUM          GPIO_OSPEEDR_OSPEEDR0_0 /*!< Select I/O medium output speed */
#define MS32_GPIO_SPEED_FREQ_HIGH            GPIO_OSPEEDR_OSPEEDR0   /*!< Select I/O high output speed   */
#define MS32_GPIO_SPEED_LOW                  MS32_GPIO_SPEED_FREQ_LOW
#define MS32_GPIO_SPEED_MEDIUM               MS32_GPIO_SPEED_FREQ_MEDIUM
#define MS32_GPIO_SPEED_HIGH                 MS32_GPIO_SPEED_FREQ_HIGH

/** @defgroup GPIO_EC_PULL Pull Up Pull Down
  * @{
  */
#define MS32_GPIO_PULL_NO                    (0x00000000U) /*!< Select I/O no pull */
#define MS32_GPIO_PULL_UP                    GPIO_PUPDR_PUPDR0_0 /*!< Select I/O pull up */
#define MS32_GPIO_PULL_DOWN                  GPIO_PUPDR_PUPDR0_1 /*!< Select I/O pull down */

/** @defgroup GPIO_EC_AF Alternate Function
  * @{
  */
#define MS32_GPIO_AF_0                       (0x0000000U) /*!< Select alternate function 0 */
#define MS32_GPIO_AF_1                       (0x0000001U) /*!< Select alternate function 1 */
#define MS32_GPIO_AF_2                       (0x0000002U) /*!< Select alternate function 2 */
#define MS32_GPIO_AF_3                       (0x0000003U) /*!< Select alternate function 3 */
#define MS32_GPIO_AF_4                       (0x0000004U) /*!< Select alternate function 4 */
#define MS32_GPIO_AF_5                       (0x0000005U) /*!< Select alternate function 5 */
#define MS32_GPIO_AF_6                       (0x0000006U) /*!< Select alternate function 6 */
#define MS32_GPIO_AF_7                       (0x0000007U) /*!< Select alternate function 7 */


/* Exported macro ------------------------------------------------------------*/
/** @defgroup GPIO_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in GPIO register
  * @param  __INSTANCE__ GPIO Instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define MS32_GPIO_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, (__VALUE__))

/**
  * @brief  Read a value in GPIO register
  * @param  __INSTANCE__ GPIO Instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define MS32_GPIO_ReadReg(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)


/* Exported functions --------------------------------------------------------*/
/** @defgroup GPIO_EF_Port_Configuration Port Configuration
  * @{
  */

/**
  * @brief  Configure gpio mode for a dedicated pin on dedicated port.
  * @note   I/O mode can be Input mode, General purpose output, Alternate function mode or Analog.
  * @note   Warning: only one pin can be passed as parameter.
  * @rmtoll MODER        MODEy         MS32_GPIO_SetPinMode
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref MS32_GPIO_PIN_0
  *         @arg @ref MS32_GPIO_PIN_1
  *         @arg @ref MS32_GPIO_PIN_2
  *         @arg @ref MS32_GPIO_PIN_3
  *         @arg @ref MS32_GPIO_PIN_4
  *         @arg @ref MS32_GPIO_PIN_5
  *         @arg @ref MS32_GPIO_PIN_6
  *         @arg @ref MS32_GPIO_PIN_7
  *         @arg @ref MS32_GPIO_PIN_8
  *         @arg @ref MS32_GPIO_PIN_9
  *         @arg @ref MS32_GPIO_PIN_10
  *         @arg @ref MS32_GPIO_PIN_11
  *         @arg @ref MS32_GPIO_PIN_12
  *         @arg @ref MS32_GPIO_PIN_13
  *         @arg @ref MS32_GPIO_PIN_14
  *         @arg @ref MS32_GPIO_PIN_15
  * @param  Mode This parameter can be one of the following values:
  *         @arg @ref MS32_GPIO_MODE_INPUT
  *         @arg @ref MS32_GPIO_MODE_OUTPUT
  *         @arg @ref MS32_GPIO_MODE_ALTERNATE
  *         @arg @ref MS32_GPIO_MODE_ANALOG
  * @retval None
  */
__STATIC_INLINE void MS32_GPIO_SetPinMode(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Mode) {
  MODIFY_REG(GPIOx->MODER, ((Pin * Pin) * GPIO_MODER_MODER0), ((Pin * Pin) * Mode));
}

/**
  * @brief  Return gpio mode for a dedicated pin on dedicated port.
  * @note   I/O mode can be Input mode, General purpose output, Alternate function mode or Analog.
  * @note   Warning: only one pin can be passed as parameter.
  * @rmtoll MODER        MODEy         MS32_GPIO_GetPinMode
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref MS32_GPIO_PIN_0
  *         @arg @ref MS32_GPIO_PIN_1
  *         @arg @ref MS32_GPIO_PIN_2
  *         @arg @ref MS32_GPIO_PIN_3
  *         @arg @ref MS32_GPIO_PIN_4
  *         @arg @ref MS32_GPIO_PIN_5
  *         @arg @ref MS32_GPIO_PIN_6
  *         @arg @ref MS32_GPIO_PIN_7
  *         @arg @ref MS32_GPIO_PIN_8
  *         @arg @ref MS32_GPIO_PIN_9
  *         @arg @ref MS32_GPIO_PIN_10
  *         @arg @ref MS32_GPIO_PIN_11
  *         @arg @ref MS32_GPIO_PIN_12
  *         @arg @ref MS32_GPIO_PIN_13
  *         @arg @ref MS32_GPIO_PIN_14
  *         @arg @ref MS32_GPIO_PIN_15
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_GPIO_MODE_INPUT
  *         @arg @ref MS32_GPIO_MODE_OUTPUT
  *         @arg @ref MS32_GPIO_MODE_ALTERNATE
  *         @arg @ref MS32_GPIO_MODE_ANALOG
  */
__STATIC_INLINE uint32_t MS32_GPIO_GetPinMode(GPIO_TypeDef *GPIOx, uint32_t Pin) {
  return (uint32_t)(READ_BIT(GPIOx->MODER, ((Pin * Pin) * GPIO_MODER_MODER0)) / (Pin * Pin));
}

/**
  * @brief  Configure gpio output type for several pins on dedicated port.
  * @note   Output type as to be set when gpio pin is in output or
  *         alternate modes. Possible type are Push-pull or Open-drain.
  * @rmtoll OTYPER       OTy           MS32_GPIO_SetPinOutputType
  * @param  GPIOx GPIO Port
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref MS32_GPIO_PIN_0
  *         @arg @ref MS32_GPIO_PIN_1
  *         @arg @ref MS32_GPIO_PIN_2
  *         @arg @ref MS32_GPIO_PIN_3
  *         @arg @ref MS32_GPIO_PIN_4
  *         @arg @ref MS32_GPIO_PIN_5
  *         @arg @ref MS32_GPIO_PIN_6
  *         @arg @ref MS32_GPIO_PIN_7
  *         @arg @ref MS32_GPIO_PIN_8
  *         @arg @ref MS32_GPIO_PIN_9
  *         @arg @ref MS32_GPIO_PIN_10
  *         @arg @ref MS32_GPIO_PIN_11
  *         @arg @ref MS32_GPIO_PIN_12
  *         @arg @ref MS32_GPIO_PIN_13
  *         @arg @ref MS32_GPIO_PIN_14
  *         @arg @ref MS32_GPIO_PIN_15
  *         @arg @ref MS32_GPIO_PIN_ALL
  * @param  OutputType This parameter can be one of the following values:
  *         @arg @ref MS32_GPIO_OUTPUT_PUSHPULL
  *         @arg @ref MS32_GPIO_OUTPUT_OPENDRAIN
  * @retval None
  */
__STATIC_INLINE void MS32_GPIO_SetPinOutputType(GPIO_TypeDef *GPIOx, uint32_t PinMask, uint32_t OutputType) {
  MODIFY_REG(GPIOx->OTYPER, PinMask, (PinMask * OutputType));
}

/**
  * @brief  Return gpio output type for several pins on dedicated port.
  * @note   Output type as to be set when gpio pin is in output or
  *         alternate modes. Possible type are Push-pull or Open-drain.
  * @note   Warning: only one pin can be passed as parameter.
  * @rmtoll OTYPER       OTy           MS32_GPIO_GetPinOutputType
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref MS32_GPIO_PIN_0
  *         @arg @ref MS32_GPIO_PIN_1
  *         @arg @ref MS32_GPIO_PIN_2
  *         @arg @ref MS32_GPIO_PIN_3
  *         @arg @ref MS32_GPIO_PIN_4
  *         @arg @ref MS32_GPIO_PIN_5
  *         @arg @ref MS32_GPIO_PIN_6
  *         @arg @ref MS32_GPIO_PIN_7
  *         @arg @ref MS32_GPIO_PIN_8
  *         @arg @ref MS32_GPIO_PIN_9
  *         @arg @ref MS32_GPIO_PIN_10
  *         @arg @ref MS32_GPIO_PIN_11
  *         @arg @ref MS32_GPIO_PIN_12
  *         @arg @ref MS32_GPIO_PIN_13
  *         @arg @ref MS32_GPIO_PIN_14
  *         @arg @ref MS32_GPIO_PIN_15
  *         @arg @ref MS32_GPIO_PIN_ALL
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_GPIO_OUTPUT_PUSHPULL
  *         @arg @ref MS32_GPIO_OUTPUT_OPENDRAIN
  */
__STATIC_INLINE uint32_t MS32_GPIO_GetPinOutputType(GPIO_TypeDef *GPIOx, uint32_t Pin) {
  return (uint32_t)(READ_BIT(GPIOx->OTYPER, Pin) / Pin);
}

/**
  * @brief  Configure gpio speed for a dedicated pin on dedicated port.
  * @note   I/O speed can be Low, Medium, Fast or High speed.
  * @note   Warning: only one pin can be passed as parameter.
  * @note   Refer to datasheet for frequency specifications and the power
  *         supply and load conditions for each speed.
  * @rmtoll OSPEEDR      OSPEEDy       MS32_GPIO_SetPinSpeed
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref MS32_GPIO_PIN_0
  *         @arg @ref MS32_GPIO_PIN_1
  *         @arg @ref MS32_GPIO_PIN_2
  *         @arg @ref MS32_GPIO_PIN_3
  *         @arg @ref MS32_GPIO_PIN_4
  *         @arg @ref MS32_GPIO_PIN_5
  *         @arg @ref MS32_GPIO_PIN_6
  *         @arg @ref MS32_GPIO_PIN_7
  *         @arg @ref MS32_GPIO_PIN_8
  *         @arg @ref MS32_GPIO_PIN_9
  *         @arg @ref MS32_GPIO_PIN_10
  *         @arg @ref MS32_GPIO_PIN_11
  *         @arg @ref MS32_GPIO_PIN_12
  *         @arg @ref MS32_GPIO_PIN_13
  *         @arg @ref MS32_GPIO_PIN_14
  *         @arg @ref MS32_GPIO_PIN_15
  * @param  Speed This parameter can be one of the following values:
  *         @arg @ref MS32_GPIO_SPEED_FREQ_LOW
  *         @arg @ref MS32_GPIO_SPEED_FREQ_MEDIUM
  *         @arg @ref MS32_GPIO_SPEED_FREQ_HIGH
  * @retval None
  */
__STATIC_INLINE void MS32_GPIO_SetPinSpeed(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t  Speed) {
  MODIFY_REG(GPIOx->OSPEEDR, ((Pin * Pin) * GPIO_OSPEEDR_OSPEEDR0), ((Pin * Pin) * Speed));
}

/**
  * @brief  Return gpio speed for a dedicated pin on dedicated port.
  * @note   I/O speed can be Low, Medium, Fast or High speed.
  * @note   Warning: only one pin can be passed as parameter.
  * @note   Refer to datasheet for frequency specifications and the power
  *         supply and load conditions for each speed.
  * @rmtoll OSPEEDR      OSPEEDy       MS32_GPIO_GetPinSpeed
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref MS32_GPIO_PIN_0
  *         @arg @ref MS32_GPIO_PIN_1
  *         @arg @ref MS32_GPIO_PIN_2
  *         @arg @ref MS32_GPIO_PIN_3
  *         @arg @ref MS32_GPIO_PIN_4
  *         @arg @ref MS32_GPIO_PIN_5
  *         @arg @ref MS32_GPIO_PIN_6
  *         @arg @ref MS32_GPIO_PIN_7
  *         @arg @ref MS32_GPIO_PIN_8
  *         @arg @ref MS32_GPIO_PIN_9
  *         @arg @ref MS32_GPIO_PIN_10
  *         @arg @ref MS32_GPIO_PIN_11
  *         @arg @ref MS32_GPIO_PIN_12
  *         @arg @ref MS32_GPIO_PIN_13
  *         @arg @ref MS32_GPIO_PIN_14
  *         @arg @ref MS32_GPIO_PIN_15
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_GPIO_SPEED_FREQ_LOW
  *         @arg @ref MS32_GPIO_SPEED_FREQ_MEDIUM
  *         @arg @ref MS32_GPIO_SPEED_FREQ_HIGH
  */
__STATIC_INLINE uint32_t MS32_GPIO_GetPinSpeed(GPIO_TypeDef *GPIOx, uint32_t Pin) {
  return (uint32_t)(READ_BIT(GPIOx->OSPEEDR, ((Pin * Pin) * GPIO_OSPEEDR_OSPEEDR0)) / (Pin * Pin));
}

/**
  * @brief  Configure gpio pull-up or pull-down for a dedicated pin on a dedicated port.
  * @note   Warning: only one pin can be passed as parameter.
  * @rmtoll PUPDR        PUPDy         MS32_GPIO_SetPinPull
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref MS32_GPIO_PIN_0
  *         @arg @ref MS32_GPIO_PIN_1
  *         @arg @ref MS32_GPIO_PIN_2
  *         @arg @ref MS32_GPIO_PIN_3
  *         @arg @ref MS32_GPIO_PIN_4
  *         @arg @ref MS32_GPIO_PIN_5
  *         @arg @ref MS32_GPIO_PIN_6
  *         @arg @ref MS32_GPIO_PIN_7
  *         @arg @ref MS32_GPIO_PIN_8
  *         @arg @ref MS32_GPIO_PIN_9
  *         @arg @ref MS32_GPIO_PIN_10
  *         @arg @ref MS32_GPIO_PIN_11
  *         @arg @ref MS32_GPIO_PIN_12
  *         @arg @ref MS32_GPIO_PIN_13
  *         @arg @ref MS32_GPIO_PIN_14
  *         @arg @ref MS32_GPIO_PIN_15
  * @param  Pull This parameter can be one of the following values:
  *         @arg @ref MS32_GPIO_PULL_NO
  *         @arg @ref MS32_GPIO_PULL_UP
  *         @arg @ref MS32_GPIO_PULL_DOWN
  * @retval None
  */
__STATIC_INLINE void MS32_GPIO_SetPinPull(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Pull) {
  MODIFY_REG(GPIOx->PUPDR, ((Pin * Pin) * GPIO_PUPDR_PUPDR0), ((Pin * Pin) * Pull));
}

/**
  * @brief  Return gpio pull-up or pull-down for a dedicated pin on a dedicated port
  * @note   Warning: only one pin can be passed as parameter.
  * @rmtoll PUPDR        PUPDy         MS32_GPIO_GetPinPull
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref MS32_GPIO_PIN_0
  *         @arg @ref MS32_GPIO_PIN_1
  *         @arg @ref MS32_GPIO_PIN_2
  *         @arg @ref MS32_GPIO_PIN_3
  *         @arg @ref MS32_GPIO_PIN_4
  *         @arg @ref MS32_GPIO_PIN_5
  *         @arg @ref MS32_GPIO_PIN_6
  *         @arg @ref MS32_GPIO_PIN_7
  *         @arg @ref MS32_GPIO_PIN_8
  *         @arg @ref MS32_GPIO_PIN_9
  *         @arg @ref MS32_GPIO_PIN_10
  *         @arg @ref MS32_GPIO_PIN_11
  *         @arg @ref MS32_GPIO_PIN_12
  *         @arg @ref MS32_GPIO_PIN_13
  *         @arg @ref MS32_GPIO_PIN_14
  *         @arg @ref MS32_GPIO_PIN_15
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_GPIO_PULL_NO
  *         @arg @ref MS32_GPIO_PULL_UP
  *         @arg @ref MS32_GPIO_PULL_DOWN
  */
__STATIC_INLINE uint32_t MS32_GPIO_GetPinPull(GPIO_TypeDef *GPIOx, uint32_t Pin) {
  return (uint32_t)(READ_BIT(GPIOx->PUPDR, ((Pin * Pin) * GPIO_PUPDR_PUPDR0)) / (Pin * Pin));
}

/**
  * @brief  Configure gpio alternate function of a dedicated pin from 0 to 7 for a dedicated port.
  * @note   Possible values are from AF0 to AF7 depending on target.
  * @note   Warning: only one pin can be passed as parameter.
  * @rmtoll AFRL         AFSELy        MS32_GPIO_SetAFPin_0_7
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref MS32_GPIO_PIN_0
  *         @arg @ref MS32_GPIO_PIN_1
  *         @arg @ref MS32_GPIO_PIN_2
  *         @arg @ref MS32_GPIO_PIN_3
  *         @arg @ref MS32_GPIO_PIN_4
  *         @arg @ref MS32_GPIO_PIN_5
  *         @arg @ref MS32_GPIO_PIN_6
  *         @arg @ref MS32_GPIO_PIN_7
  * @param  Alternate This parameter can be one of the following values:
  *         @arg @ref MS32_GPIO_AF_0
  *         @arg @ref MS32_GPIO_AF_1
  *         @arg @ref MS32_GPIO_AF_2
  *         @arg @ref MS32_GPIO_AF_3
  *         @arg @ref MS32_GPIO_AF_4
  *         @arg @ref MS32_GPIO_AF_5
  *         @arg @ref MS32_GPIO_AF_6
  *         @arg @ref MS32_GPIO_AF_7
  * @retval None
  */
__STATIC_INLINE void MS32_GPIO_SetAFPin_0_7(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Alternate) {
  MODIFY_REG(GPIOx->AFRL, ((((Pin * Pin) * Pin) * Pin) * GPIO_AFRL_AFSEL0),
             ((((Pin * Pin) * Pin) * Pin) * Alternate));
}

/**
  * @brief  Return gpio alternate function of a dedicated pin from 0 to 7 for a dedicated port.
  * @rmtoll AFRL         AFSELy        MS32_GPIO_GetAFPin_0_7
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref MS32_GPIO_PIN_0
  *         @arg @ref MS32_GPIO_PIN_1
  *         @arg @ref MS32_GPIO_PIN_2
  *         @arg @ref MS32_GPIO_PIN_3
  *         @arg @ref MS32_GPIO_PIN_4
  *         @arg @ref MS32_GPIO_PIN_5
  *         @arg @ref MS32_GPIO_PIN_6
  *         @arg @ref MS32_GPIO_PIN_7
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_GPIO_AF_0
  *         @arg @ref MS32_GPIO_AF_1
  *         @arg @ref MS32_GPIO_AF_2
  *         @arg @ref MS32_GPIO_AF_3
  *         @arg @ref MS32_GPIO_AF_4
  *         @arg @ref MS32_GPIO_AF_5
  *         @arg @ref MS32_GPIO_AF_6
  *         @arg @ref MS32_GPIO_AF_7
  */
__STATIC_INLINE uint32_t MS32_GPIO_GetAFPin_0_7(GPIO_TypeDef *GPIOx, uint32_t Pin) {
  return (uint32_t)(READ_BIT(GPIOx->AFRL,
                             ((((Pin * Pin) * Pin) * Pin) * GPIO_AFRL_AFSEL0)) / (((Pin * Pin) * Pin) * Pin));
}

/**
  * @brief  Configure gpio alternate function of a dedicated pin from 8 to 15 for a dedicated port.
  * @note   Possible values are from AF0 to AF7 depending on target.
  * @note   Warning: only one pin can be passed as parameter.
  * @rmtoll AFRH         AFSELy        MS32_GPIO_SetAFPin_8_15
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref MS32_GPIO_PIN_8
  *         @arg @ref MS32_GPIO_PIN_9
  *         @arg @ref MS32_GPIO_PIN_10
  *         @arg @ref MS32_GPIO_PIN_11
  *         @arg @ref MS32_GPIO_PIN_12
  *         @arg @ref MS32_GPIO_PIN_13
  *         @arg @ref MS32_GPIO_PIN_14
  *         @arg @ref MS32_GPIO_PIN_15
  * @param  Alternate This parameter can be one of the following values:
  *         @arg @ref MS32_GPIO_AF_0
  *         @arg @ref MS32_GPIO_AF_1
  *         @arg @ref MS32_GPIO_AF_2
  *         @arg @ref MS32_GPIO_AF_3
  *         @arg @ref MS32_GPIO_AF_4
  *         @arg @ref MS32_GPIO_AF_5
  *         @arg @ref MS32_GPIO_AF_6
  *         @arg @ref MS32_GPIO_AF_7
  * @retval None
  */
__STATIC_INLINE void MS32_GPIO_SetAFPin_8_15(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Alternate) {
  MODIFY_REG(GPIOx->AFRH, (((((Pin >> 8U) * (Pin >> 8U)) * (Pin >> 8U)) * (Pin >> 8U)) * GPIO_AFRH_AFSEL8),
             (((((Pin >> 8U) * (Pin >> 8U)) * (Pin >> 8U)) * (Pin >> 8U)) * Alternate));
}

/**
  * @brief  Return gpio alternate function of a dedicated pin from 8 to 15 for a dedicated port.
  * @note   Possible values are from AF0 to AF7 depending on target.
  * @rmtoll AFRH         AFSELy        MS32_GPIO_GetAFPin_8_15
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref MS32_GPIO_PIN_8
  *         @arg @ref MS32_GPIO_PIN_9
  *         @arg @ref MS32_GPIO_PIN_10
  *         @arg @ref MS32_GPIO_PIN_11
  *         @arg @ref MS32_GPIO_PIN_12
  *         @arg @ref MS32_GPIO_PIN_13
  *         @arg @ref MS32_GPIO_PIN_14
  *         @arg @ref MS32_GPIO_PIN_15
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_GPIO_AF_0
  *         @arg @ref MS32_GPIO_AF_1
  *         @arg @ref MS32_GPIO_AF_2
  *         @arg @ref MS32_GPIO_AF_3
  *         @arg @ref MS32_GPIO_AF_4
  *         @arg @ref MS32_GPIO_AF_5
  *         @arg @ref MS32_GPIO_AF_6
  *         @arg @ref MS32_GPIO_AF_7
  */
__STATIC_INLINE uint32_t MS32_GPIO_GetAFPin_8_15(GPIO_TypeDef *GPIOx, uint32_t Pin) {
  return (uint32_t)(READ_BIT(GPIOx->AFRH,
                             (((((Pin >> 8U) * (Pin >> 8U)) * (Pin >> 8U)) * (Pin >> 8U)) * GPIO_AFRH_AFSEL8)) / ((((Pin >> 8U) *
                                 (Pin >> 8U)) * (Pin >> 8U)) * (Pin >> 8U)));
}


/**
  * @brief  Lock configuration of several pins for a dedicated port.
  * @note   When the lock sequence has been applied on a port bit, the
  *         value of this port bit can no longer be modified until the
  *         next reset.
  * @note   Each lock bit freezes a specific configuration register
  *         (control and alternate function registers).
  * @rmtoll LCKR         LCKK          MS32_GPIO_LockPin
  * @param  GPIOx GPIO Port
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref MS32_GPIO_PIN_0
  *         @arg @ref MS32_GPIO_PIN_1
  *         @arg @ref MS32_GPIO_PIN_2
  *         @arg @ref MS32_GPIO_PIN_3
  *         @arg @ref MS32_GPIO_PIN_4
  *         @arg @ref MS32_GPIO_PIN_5
  *         @arg @ref MS32_GPIO_PIN_6
  *         @arg @ref MS32_GPIO_PIN_7
  *         @arg @ref MS32_GPIO_PIN_8
  *         @arg @ref MS32_GPIO_PIN_9
  *         @arg @ref MS32_GPIO_PIN_10
  *         @arg @ref MS32_GPIO_PIN_11
  *         @arg @ref MS32_GPIO_PIN_12
  *         @arg @ref MS32_GPIO_PIN_13
  *         @arg @ref MS32_GPIO_PIN_14
  *         @arg @ref MS32_GPIO_PIN_15
  *         @arg @ref MS32_GPIO_PIN_ALL
  * @retval None
  */
__STATIC_INLINE void MS32_GPIO_LockPin(GPIO_TypeDef *GPIOx, uint32_t PinMask) {
  __IO uint32_t temp;
  WRITE_REG(GPIOx->LCKR, GPIO_LCKR_LCKK | PinMask);
  WRITE_REG(GPIOx->LCKR, PinMask);
  WRITE_REG(GPIOx->LCKR, GPIO_LCKR_LCKK | PinMask);
  temp = READ_REG(GPIOx->LCKR);
  (void) temp;
}

/**
  * @brief  Return 1 if all pins passed as parameter, of a dedicated port, are locked. else Return 0.
  * @rmtoll LCKR         LCKy          MS32_GPIO_IsPinLocked
  * @param  GPIOx GPIO Port
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref MS32_GPIO_PIN_0
  *         @arg @ref MS32_GPIO_PIN_1
  *         @arg @ref MS32_GPIO_PIN_2
  *         @arg @ref MS32_GPIO_PIN_3
  *         @arg @ref MS32_GPIO_PIN_4
  *         @arg @ref MS32_GPIO_PIN_5
  *         @arg @ref MS32_GPIO_PIN_6
  *         @arg @ref MS32_GPIO_PIN_7
  *         @arg @ref MS32_GPIO_PIN_8
  *         @arg @ref MS32_GPIO_PIN_9
  *         @arg @ref MS32_GPIO_PIN_10
  *         @arg @ref MS32_GPIO_PIN_11
  *         @arg @ref MS32_GPIO_PIN_12
  *         @arg @ref MS32_GPIO_PIN_13
  *         @arg @ref MS32_GPIO_PIN_14
  *         @arg @ref MS32_GPIO_PIN_15
  *         @arg @ref MS32_GPIO_PIN_ALL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_GPIO_IsPinLocked(GPIO_TypeDef *GPIOx, uint32_t PinMask) {
  return (READ_BIT(GPIOx->LCKR, PinMask) == (PinMask));
}

/**
  * @brief  Return 1 if one of the pin of a dedicated port is locked. else return 0.
  * @rmtoll LCKR         LCKK          MS32_GPIO_IsAnyPinLocked
  * @param  GPIOx GPIO Port
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_GPIO_IsAnyPinLocked(GPIO_TypeDef *GPIOx) {
  return (READ_BIT(GPIOx->LCKR, GPIO_LCKR_LCKK) == (GPIO_LCKR_LCKK));
}


/** @defgroup GPIO_EF_Data_Access Data Access
  * @{
  */

/**
  * @brief  Return full input data register value for a dedicated port.
  * @rmtoll IDR          IDy           MS32_GPIO_ReadInputPort
  * @param  GPIOx GPIO Port
  * @retval Input data register value of port
  */
__STATIC_INLINE uint32_t MS32_GPIO_ReadInputPort(GPIO_TypeDef *GPIOx) {
  return (uint32_t)(READ_REG(GPIOx->IDR));
}

/**
  * @brief  Return if input data level for several pins of dedicated port is high or low.
  * @rmtoll IDR          IDy           MS32_GPIO_IsInputPinSet
  * @param  GPIOx GPIO Port
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref MS32_GPIO_PIN_0
  *         @arg @ref MS32_GPIO_PIN_1
  *         @arg @ref MS32_GPIO_PIN_2
  *         @arg @ref MS32_GPIO_PIN_3
  *         @arg @ref MS32_GPIO_PIN_4
  *         @arg @ref MS32_GPIO_PIN_5
  *         @arg @ref MS32_GPIO_PIN_6
  *         @arg @ref MS32_GPIO_PIN_7
  *         @arg @ref MS32_GPIO_PIN_8
  *         @arg @ref MS32_GPIO_PIN_9
  *         @arg @ref MS32_GPIO_PIN_10
  *         @arg @ref MS32_GPIO_PIN_11
  *         @arg @ref MS32_GPIO_PIN_12
  *         @arg @ref MS32_GPIO_PIN_13
  *         @arg @ref MS32_GPIO_PIN_14
  *         @arg @ref MS32_GPIO_PIN_15
  *         @arg @ref MS32_GPIO_PIN_ALL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_GPIO_IsInputPinSet(GPIO_TypeDef *GPIOx, uint32_t PinMask) {
  return (READ_BIT(GPIOx->IDR, PinMask) == (PinMask));
}

/**
  * @brief  Write output data register for the port.
  * @rmtoll ODR          ODy           MS32_GPIO_WriteOutputPort
  * @param  GPIOx GPIO Port
  * @param  PortValue Level value for each pin of the port
  * @retval None
  */
__STATIC_INLINE void MS32_GPIO_WriteOutputPort(GPIO_TypeDef *GPIOx, uint32_t PortValue) {
  WRITE_REG(GPIOx->ODR, PortValue);
}

/**
  * @brief  Return full output data register value for a dedicated port.
  * @rmtoll ODR          ODy           MS32_GPIO_ReadOutputPort
  * @param  GPIOx GPIO Port
  * @retval Output data register value of port
  */
__STATIC_INLINE uint32_t MS32_GPIO_ReadOutputPort(GPIO_TypeDef *GPIOx) {
  return (uint32_t)(READ_REG(GPIOx->ODR));
}

/**
  * @brief  Return if input data level for several pins of dedicated port is high or low.
  * @rmtoll ODR          ODy           MS32_GPIO_IsOutputPinSet
  * @param  GPIOx GPIO Port
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref MS32_GPIO_PIN_0
  *         @arg @ref MS32_GPIO_PIN_1
  *         @arg @ref MS32_GPIO_PIN_2
  *         @arg @ref MS32_GPIO_PIN_3
  *         @arg @ref MS32_GPIO_PIN_4
  *         @arg @ref MS32_GPIO_PIN_5
  *         @arg @ref MS32_GPIO_PIN_6
  *         @arg @ref MS32_GPIO_PIN_7
  *         @arg @ref MS32_GPIO_PIN_8
  *         @arg @ref MS32_GPIO_PIN_9
  *         @arg @ref MS32_GPIO_PIN_10
  *         @arg @ref MS32_GPIO_PIN_11
  *         @arg @ref MS32_GPIO_PIN_12
  *         @arg @ref MS32_GPIO_PIN_13
  *         @arg @ref MS32_GPIO_PIN_14
  *         @arg @ref MS32_GPIO_PIN_15
  *         @arg @ref MS32_GPIO_PIN_ALL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_GPIO_IsOutputPinSet(GPIO_TypeDef *GPIOx, uint32_t PinMask) {
  return (READ_BIT(GPIOx->ODR, PinMask) == (PinMask));
}

/**
  * @brief  Set several pins to high level on dedicated gpio port.
  * @rmtoll BSRR         BSy           MS32_GPIO_SetOutputPin
  * @param  GPIOx GPIO Port
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref MS32_GPIO_PIN_0
  *         @arg @ref MS32_GPIO_PIN_1
  *         @arg @ref MS32_GPIO_PIN_2
  *         @arg @ref MS32_GPIO_PIN_3
  *         @arg @ref MS32_GPIO_PIN_4
  *         @arg @ref MS32_GPIO_PIN_5
  *         @arg @ref MS32_GPIO_PIN_6
  *         @arg @ref MS32_GPIO_PIN_7
  *         @arg @ref MS32_GPIO_PIN_8
  *         @arg @ref MS32_GPIO_PIN_9
  *         @arg @ref MS32_GPIO_PIN_10
  *         @arg @ref MS32_GPIO_PIN_11
  *         @arg @ref MS32_GPIO_PIN_12
  *         @arg @ref MS32_GPIO_PIN_13
  *         @arg @ref MS32_GPIO_PIN_14
  *         @arg @ref MS32_GPIO_PIN_15
  *         @arg @ref MS32_GPIO_PIN_ALL
  * @retval None
  */
__STATIC_INLINE void MS32_GPIO_SetOutputPin(GPIO_TypeDef *GPIOx, uint32_t PinMask) {
  WRITE_REG(GPIOx->BSRR, PinMask);
}

/**
  * @brief  Set several pins to low level on dedicated gpio port.
  * @rmtoll BRR          BRy           MS32_GPIO_ResetOutputPin
  * @param  GPIOx GPIO Port
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref MS32_GPIO_PIN_0
  *         @arg @ref MS32_GPIO_PIN_1
  *         @arg @ref MS32_GPIO_PIN_2
  *         @arg @ref MS32_GPIO_PIN_3
  *         @arg @ref MS32_GPIO_PIN_4
  *         @arg @ref MS32_GPIO_PIN_5
  *         @arg @ref MS32_GPIO_PIN_6
  *         @arg @ref MS32_GPIO_PIN_7
  *         @arg @ref MS32_GPIO_PIN_8
  *         @arg @ref MS32_GPIO_PIN_9
  *         @arg @ref MS32_GPIO_PIN_10
  *         @arg @ref MS32_GPIO_PIN_11
  *         @arg @ref MS32_GPIO_PIN_12
  *         @arg @ref MS32_GPIO_PIN_13
  *         @arg @ref MS32_GPIO_PIN_14
  *         @arg @ref MS32_GPIO_PIN_15
  *         @arg @ref MS32_GPIO_PIN_ALL
  * @retval None
  */
__STATIC_INLINE void MS32_GPIO_ResetOutputPin(GPIO_TypeDef *GPIOx, uint32_t PinMask) {
  WRITE_REG(GPIOx->BRR, PinMask);
}

/**
  * @brief  Toggle data value for several pin of dedicated port.
  * @rmtoll ODR          ODy           MS32_GPIO_TogglePin
  * @param  GPIOx GPIO Port
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref MS32_GPIO_PIN_0
  *         @arg @ref MS32_GPIO_PIN_1
  *         @arg @ref MS32_GPIO_PIN_2
  *         @arg @ref MS32_GPIO_PIN_3
  *         @arg @ref MS32_GPIO_PIN_4
  *         @arg @ref MS32_GPIO_PIN_5
  *         @arg @ref MS32_GPIO_PIN_6
  *         @arg @ref MS32_GPIO_PIN_7
  *         @arg @ref MS32_GPIO_PIN_8
  *         @arg @ref MS32_GPIO_PIN_9
  *         @arg @ref MS32_GPIO_PIN_10
  *         @arg @ref MS32_GPIO_PIN_11
  *         @arg @ref MS32_GPIO_PIN_12
  *         @arg @ref MS32_GPIO_PIN_13
  *         @arg @ref MS32_GPIO_PIN_14
  *         @arg @ref MS32_GPIO_PIN_15
  *         @arg @ref MS32_GPIO_PIN_ALL
  * @retval None
  */
__STATIC_INLINE void MS32_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint32_t PinMask) {
  WRITE_REG(GPIOx->ODR, READ_REG(GPIOx->ODR) ^ PinMask);
}


/** @defgroup GPIO_EF_Init Initialization and de-initialization functions
  * @{
  */
ErrorStatus MS32_GPIO_DeInit     (GPIO_TypeDef *GPIOx);
void        MS32_GPIO_StructInit (MS32_GPIO_InitTypeDef *GpioInitStr);
ErrorStatus MS32_GPIO_Init       (GPIO_TypeDef *GPIOx, MS32_GPIO_InitTypeDef *GpioInitStr);

/** @defgroup GPIO_EF_Application function
  * @{
  */
void        MS32_GPIO_Output     (GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Output);
LevelStatus MS32_GPIO_Input      (GPIO_TypeDef *GPIOx, uint32_t Pin);
ErrorStatus MS32_GPIO_Lock       (GPIO_TypeDef *GPIOx, uint32_t Pin);


#ifdef __cplusplus
}
#endif

#endif /* __MS32F0XX_GPIO_H */

/******************************** END OF FILE *********************************/
