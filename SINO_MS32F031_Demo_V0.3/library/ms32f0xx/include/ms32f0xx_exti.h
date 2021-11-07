/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MS32F0XX_EXTI_H
#define __MS32F0XX_EXTI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ms32f0xx.h"


/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private Macros ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/** @defgroup EXTI_ES_INIT EXTI Exported Init structure
  * @{
  */
typedef struct {
  uint32_t Line_0_31;           /*!< Specifies the EXTI lines to be enabled or disabled for Lines in range 0 to 31
                                     This parameter can be any combination of @ref EXTI_EC_LINE */
  FunctionalState LineCommand;  /*!< Specifies the new state of the selected EXTI lines.
                                     This parameter can be set either to ENABLE or DISABLE */
  uint8_t Mode;                 /*!< Specifies the mode for the EXTI lines.
                                     This parameter can be a value of @ref EXTI_EC_MODE. */
  uint8_t Trigger;              /*!< Specifies the trigger signal active edge for the EXTI lines.
                                     This parameter can be a value of @ref EXTI_EC_TRIGGER. */
} MS32_EXTI_InitTypeDef;


/* Exported constants --------------------------------------------------------*/
/** @defgroup EXTI_EC_LINE LINE
  * @{
  */
#define MS32_EXTI_LINE_0                 EXTI_IMR_IM0  /*!< Extended line 0 */
#define MS32_EXTI_LINE_1                 EXTI_IMR_IM1  /*!< Extended line 1 */
#define MS32_EXTI_LINE_2                 EXTI_IMR_IM2  /*!< Extended line 2 */
#define MS32_EXTI_LINE_3                 EXTI_IMR_IM3  /*!< Extended line 3 */
#define MS32_EXTI_LINE_4                 EXTI_IMR_IM4  /*!< Extended line 4 */
#define MS32_EXTI_LINE_5                 EXTI_IMR_IM5  /*!< Extended line 5 */
#define MS32_EXTI_LINE_6                 EXTI_IMR_IM6  /*!< Extended line 6 */
#define MS32_EXTI_LINE_7                 EXTI_IMR_IM7  /*!< Extended line 7 */
#define MS32_EXTI_LINE_8                 EXTI_IMR_IM8  /*!< Extended line 8 */
#define MS32_EXTI_LINE_9                 EXTI_IMR_IM9  /*!< Extended line 9 */
#define MS32_EXTI_LINE_10                EXTI_IMR_IM10 /*!< Extended line 10 */
#define MS32_EXTI_LINE_11                EXTI_IMR_IM11 /*!< Extended line 11 */
#define MS32_EXTI_LINE_12                EXTI_IMR_IM12 /*!< Extended line 12 */
#define MS32_EXTI_LINE_13                EXTI_IMR_IM13 /*!< Extended line 13 */
#define MS32_EXTI_LINE_14                EXTI_IMR_IM14 /*!< Extended line 14 */
#define MS32_EXTI_LINE_15                EXTI_IMR_IM15 /*!< Extended line 15 */
#define MS32_EXTI_LINE_16                EXTI_IMR_IM16 /*!< Extended line 16 */
#define MS32_EXTI_LINE_17                EXTI_IMR_IM17 /*!< Extended line 17 */
#define MS32_EXTI_LINE_19                EXTI_IMR_IM19 /*!< Extended line 19 */
#define MS32_EXTI_LINE_21                EXTI_IMR_IM21 /*!< Extended line 21 */
#define MS32_EXTI_LINE_22                EXTI_IMR_IM22 /*!< Extended line 22 */
#define MS32_EXTI_LINE_23                EXTI_IMR_IM23 /*!< Extended line 23 */
#define MS32_EXTI_LINE_25                EXTI_IMR_IM25 /*!< Extended line 25 */
#define MS32_EXTI_LINE_ALL_0_31          EXTI_IMR_IM   /*!< All Extended line not reserved*/

#define MS32_EXTI_LINE_ALL               (0xFFFFFFFFU) /*!< All Extended line */
#define MS32_EXTI_LINE_NONE              (0x00000000U) /*!< None Extended line */

/** @defgroup EXTI_EC_MODE Mode
  * @{
  */
#define MS32_EXTI_MODE_IT                 ((uint8_t)0x00U) /*!< Interrupt Mode */
#define MS32_EXTI_MODE_EVENT              ((uint8_t)0x01U) /*!< Event Mode */
#define MS32_EXTI_MODE_IT_EVENT           ((uint8_t)0x02U) /*!< Interrupt & Event Mode */

/** @defgroup EXTI_EC_TRIGGER Edge Trigger
  * @{
  */
#define MS32_EXTI_TRIGGER_NONE            ((uint8_t)0x00U) /*!< No Trigger Mode */
#define MS32_EXTI_TRIGGER_RISING          ((uint8_t)0x01U) /*!< Trigger Rising Mode */
#define MS32_EXTI_TRIGGER_FALLING         ((uint8_t)0x02U) /*!< Trigger Falling Mode */
#define MS32_EXTI_TRIGGER_RISING_FALLING  ((uint8_t)0x03U) /*!< Trigger Rising & Falling Mode */

/** @defgroup EXTI_EC_PORT Exti Trigger port
  * @{
  */
#define MS32_EXTI_PORTA                   SYSCFG_EXTICR1_EXTI0_PA /*!< PA GPIO as EXTI */
#define MS32_EXTI_PORTB                   SYSCFG_EXTICR1_EXTI0_PB /*!< PB GPIO as EXTI */
#define MS32_EXTI_PORTC                   SYSCFG_EXTICR1_EXTI0_PC /*!< PC GPIO as EXTI */
#define MS32_EXTI_PORTF                   SYSCFG_EXTICR1_EXTI0_PF /*!< PF GPIO as EXTI */


/* Exported macro ------------------------------------------------------------*/
/** @defgroup EXTI_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in EXTI register
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define MS32_EXTI_WriteReg(__REG__, __VALUE__) WRITE_REG(EXTI->__REG__, (__VALUE__))

/**
  * @brief  Read a value in EXTI register
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define MS32_EXTI_ReadReg(__REG__) READ_REG(EXTI->__REG__)


/* Exported functions --------------------------------------------------------*/
/** @defgroup EXTI_EF_IT_Management IT_Management
  * @{
  */

/**
  * @brief  Enable ExtiLine Interrupt request for Lines in range 0 to 31
  * @note The reset value for the direct or internal lines (see RM)
  *       is set to 1 in order to enable the interrupt by default.
  *       Bits are set automatically at Power on.
  * @rmtoll IMR         IMx           MS32_EXTI_EnableIT_0_31
  * @param  ExtiLine This parameter can be one of the following values:
  *         @arg @ref MS32_EXTI_LINE_0
  *         @arg @ref MS32_EXTI_LINE_1
  *         @arg @ref MS32_EXTI_LINE_2
  *         @arg @ref MS32_EXTI_LINE_3
  *         @arg @ref MS32_EXTI_LINE_4
  *         @arg @ref MS32_EXTI_LINE_5
  *         @arg @ref MS32_EXTI_LINE_6
  *         @arg @ref MS32_EXTI_LINE_7
  *         @arg @ref MS32_EXTI_LINE_8
  *         @arg @ref MS32_EXTI_LINE_9
  *         @arg @ref MS32_EXTI_LINE_10
  *         @arg @ref MS32_EXTI_LINE_11
  *         @arg @ref MS32_EXTI_LINE_12
  *         @arg @ref MS32_EXTI_LINE_13
  *         @arg @ref MS32_EXTI_LINE_14
  *         @arg @ref MS32_EXTI_LINE_15
  *         @arg @ref MS32_EXTI_LINE_16
  *         @arg @ref MS32_EXTI_LINE_17
  *         @arg @ref MS32_EXTI_LINE_19
  *         @arg @ref MS32_EXTI_LINE_21
  *         @arg @ref MS32_EXTI_LINE_22
  *         @arg @ref MS32_EXTI_LINE_23
  *         @arg @ref MS32_EXTI_LINE_25
  *         @arg @ref MS32_EXTI_LINE_ALL_0_31
  * @note   Please check each device line mapping for EXTI Line availability
  * @retval None
  */
__STATIC_INLINE void MS32_EXTI_EnableIT_0_31(uint32_t ExtiLine) {
  SET_BIT(EXTI->IMR, ExtiLine);
}

/**
  * @brief  Disable ExtiLine Interrupt request for Lines in range 0 to 31
  * @note The reset value for the direct or internal lines (see RM)
  *       is set to 1 in order to enable the interrupt by default.
  *       Bits are set automatically at Power on.
  * @rmtoll IMR         IMx           MS32_EXTI_DisableIT_0_31
  * @param  ExtiLine This parameter can be one of the following values:
  *         @arg @ref MS32_EXTI_LINE_0
  *         @arg @ref MS32_EXTI_LINE_1
  *         @arg @ref MS32_EXTI_LINE_2
  *         @arg @ref MS32_EXTI_LINE_3
  *         @arg @ref MS32_EXTI_LINE_4
  *         @arg @ref MS32_EXTI_LINE_5
  *         @arg @ref MS32_EXTI_LINE_6
  *         @arg @ref MS32_EXTI_LINE_7
  *         @arg @ref MS32_EXTI_LINE_8
  *         @arg @ref MS32_EXTI_LINE_9
  *         @arg @ref MS32_EXTI_LINE_10
  *         @arg @ref MS32_EXTI_LINE_11
  *         @arg @ref MS32_EXTI_LINE_12
  *         @arg @ref MS32_EXTI_LINE_13
  *         @arg @ref MS32_EXTI_LINE_14
  *         @arg @ref MS32_EXTI_LINE_15
  *         @arg @ref MS32_EXTI_LINE_16
  *         @arg @ref MS32_EXTI_LINE_17
  *         @arg @ref MS32_EXTI_LINE_19
  *         @arg @ref MS32_EXTI_LINE_21
  *         @arg @ref MS32_EXTI_LINE_22
  *         @arg @ref MS32_EXTI_LINE_23
  *         @arg @ref MS32_EXTI_LINE_25
  *         @arg @ref MS32_EXTI_LINE_ALL_0_31
  * @note   Please check each device line mapping for EXTI Line availability
  * @retval None
  */
__STATIC_INLINE void MS32_EXTI_DisableIT_0_31(uint32_t ExtiLine) {
  CLEAR_BIT(EXTI->IMR, ExtiLine);
}


/**
  * @brief  Indicate if ExtiLine Interrupt request is enabled for Lines in range 0 to 31
  * @note The reset value for the direct or internal lines (see RM)
  *       is set to 1 in order to enable the interrupt by default.
  *       Bits are set automatically at Power on.
  * @rmtoll IMR         IMx           MS32_EXTI_IsEnabledIT_0_31
  * @param  ExtiLine This parameter can be one of the following values:
  *         @arg @ref MS32_EXTI_LINE_0
  *         @arg @ref MS32_EXTI_LINE_1
  *         @arg @ref MS32_EXTI_LINE_2
  *         @arg @ref MS32_EXTI_LINE_3
  *         @arg @ref MS32_EXTI_LINE_4
  *         @arg @ref MS32_EXTI_LINE_5
  *         @arg @ref MS32_EXTI_LINE_6
  *         @arg @ref MS32_EXTI_LINE_7
  *         @arg @ref MS32_EXTI_LINE_8
  *         @arg @ref MS32_EXTI_LINE_9
  *         @arg @ref MS32_EXTI_LINE_10
  *         @arg @ref MS32_EXTI_LINE_11
  *         @arg @ref MS32_EXTI_LINE_12
  *         @arg @ref MS32_EXTI_LINE_13
  *         @arg @ref MS32_EXTI_LINE_14
  *         @arg @ref MS32_EXTI_LINE_15
  *         @arg @ref MS32_EXTI_LINE_16
  *         @arg @ref MS32_EXTI_LINE_17
  *         @arg @ref MS32_EXTI_LINE_19
  *         @arg @ref MS32_EXTI_LINE_21
  *         @arg @ref MS32_EXTI_LINE_22
  *         @arg @ref MS32_EXTI_LINE_23
  *         @arg @ref MS32_EXTI_LINE_25
  *         @arg @ref MS32_EXTI_LINE_ALL_0_31
  * @note   Please check each device line mapping for EXTI Line availability
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_EXTI_IsEnabledIT_0_31(uint32_t ExtiLine) {
  return (READ_BIT(EXTI->IMR, ExtiLine) == (ExtiLine));
}


/** @defgroup EXTI_EF_Event_Management Event_Management
  * @{
  */

/**
  * @brief  Enable ExtiLine Event request for Lines in range 0 to 31
  * @rmtoll EMR         EMx           MS32_EXTI_EnableEvent_0_31
  * @param  ExtiLine This parameter can be one of the following values:
  *         @arg @ref MS32_EXTI_LINE_0
  *         @arg @ref MS32_EXTI_LINE_1
  *         @arg @ref MS32_EXTI_LINE_2
  *         @arg @ref MS32_EXTI_LINE_3
  *         @arg @ref MS32_EXTI_LINE_4
  *         @arg @ref MS32_EXTI_LINE_5
  *         @arg @ref MS32_EXTI_LINE_6
  *         @arg @ref MS32_EXTI_LINE_7
  *         @arg @ref MS32_EXTI_LINE_8
  *         @arg @ref MS32_EXTI_LINE_9
  *         @arg @ref MS32_EXTI_LINE_10
  *         @arg @ref MS32_EXTI_LINE_11
  *         @arg @ref MS32_EXTI_LINE_12
  *         @arg @ref MS32_EXTI_LINE_13
  *         @arg @ref MS32_EXTI_LINE_14
  *         @arg @ref MS32_EXTI_LINE_15
  *         @arg @ref MS32_EXTI_LINE_16
  *         @arg @ref MS32_EXTI_LINE_17
  *         @arg @ref MS32_EXTI_LINE_19
  *         @arg @ref MS32_EXTI_LINE_21
  *         @arg @ref MS32_EXTI_LINE_22
  *         @arg @ref MS32_EXTI_LINE_23
  *         @arg @ref MS32_EXTI_LINE_25
  *         @arg @ref MS32_EXTI_LINE_ALL_0_31
  * @note   Please check each device line mapping for EXTI Line availability
  * @retval None
  */
__STATIC_INLINE void MS32_EXTI_EnableEvent_0_31(uint32_t ExtiLine) {
  SET_BIT(EXTI->EMR, ExtiLine);

}


/**
  * @brief  Disable ExtiLine Event request for Lines in range 0 to 31
  * @rmtoll EMR         EMx           MS32_EXTI_DisableEvent_0_31
  * @param  ExtiLine This parameter can be one of the following values:
  *         @arg @ref MS32_EXTI_LINE_0
  *         @arg @ref MS32_EXTI_LINE_1
  *         @arg @ref MS32_EXTI_LINE_2
  *         @arg @ref MS32_EXTI_LINE_3
  *         @arg @ref MS32_EXTI_LINE_4
  *         @arg @ref MS32_EXTI_LINE_5
  *         @arg @ref MS32_EXTI_LINE_6
  *         @arg @ref MS32_EXTI_LINE_7
  *         @arg @ref MS32_EXTI_LINE_8
  *         @arg @ref MS32_EXTI_LINE_9
  *         @arg @ref MS32_EXTI_LINE_10
  *         @arg @ref MS32_EXTI_LINE_11
  *         @arg @ref MS32_EXTI_LINE_12
  *         @arg @ref MS32_EXTI_LINE_13
  *         @arg @ref MS32_EXTI_LINE_14
  *         @arg @ref MS32_EXTI_LINE_15
  *         @arg @ref MS32_EXTI_LINE_16
  *         @arg @ref MS32_EXTI_LINE_17
  *         @arg @ref MS32_EXTI_LINE_19
  *         @arg @ref MS32_EXTI_LINE_21
  *         @arg @ref MS32_EXTI_LINE_22
  *         @arg @ref MS32_EXTI_LINE_23
  *         @arg @ref MS32_EXTI_LINE_25
  *         @arg @ref MS32_EXTI_LINE_ALL_0_31
  * @note   Please check each device line mapping for EXTI Line availability
  * @retval None
  */
__STATIC_INLINE void MS32_EXTI_DisableEvent_0_31(uint32_t ExtiLine) {
  CLEAR_BIT(EXTI->EMR, ExtiLine);
}


/**
  * @brief  Indicate if ExtiLine Event request is enabled for Lines in range 0 to 31
  * @rmtoll EMR         EMx           MS32_EXTI_IsEnabledEvent_0_31
  * @param  ExtiLine This parameter can be one of the following values:
  *         @arg @ref MS32_EXTI_LINE_0
  *         @arg @ref MS32_EXTI_LINE_1
  *         @arg @ref MS32_EXTI_LINE_2
  *         @arg @ref MS32_EXTI_LINE_3
  *         @arg @ref MS32_EXTI_LINE_4
  *         @arg @ref MS32_EXTI_LINE_5
  *         @arg @ref MS32_EXTI_LINE_6
  *         @arg @ref MS32_EXTI_LINE_7
  *         @arg @ref MS32_EXTI_LINE_8
  *         @arg @ref MS32_EXTI_LINE_9
  *         @arg @ref MS32_EXTI_LINE_10
  *         @arg @ref MS32_EXTI_LINE_11
  *         @arg @ref MS32_EXTI_LINE_12
  *         @arg @ref MS32_EXTI_LINE_13
  *         @arg @ref MS32_EXTI_LINE_14
  *         @arg @ref MS32_EXTI_LINE_15
  *         @arg @ref MS32_EXTI_LINE_16
  *         @arg @ref MS32_EXTI_LINE_17
  *         @arg @ref MS32_EXTI_LINE_19
  *         @arg @ref MS32_EXTI_LINE_21
  *         @arg @ref MS32_EXTI_LINE_22
  *         @arg @ref MS32_EXTI_LINE_23
  *         @arg @ref MS32_EXTI_LINE_25
  *         @arg @ref MS32_EXTI_LINE_ALL_0_31
  * @note   Please check each device line mapping for EXTI Line availability
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_EXTI_IsEnabledEvent_0_31(uint32_t ExtiLine) {
  return (READ_BIT(EXTI->EMR, ExtiLine) == (ExtiLine));

}


/** @defgroup EXTI_EF_Rising_Trigger_Management Rising_Trigger_Management
  * @{
  */

/**
  * @brief  Enable ExtiLine Rising Edge Trigger for Lines in range 0 to 31
  * @note The configurable wakeup lines are edge-triggered. No glitch must be
  *       generated on these lines. If a rising edge on a configurable interrupt
  *       line occurs during a write operation in the EXTI_RTSR register, the
  *       pending bit is not set.
  *       Rising and falling edge triggers can be set for
  *       the same interrupt line. In this case, both generate a trigger
  *       condition.
  * @rmtoll RTSR        RTx           MS32_EXTI_EnableRisingTrig_0_31
  * @param  ExtiLine This parameter can be a combination of the following values:
  *         @arg @ref MS32_EXTI_LINE_0
  *         @arg @ref MS32_EXTI_LINE_1
  *         @arg @ref MS32_EXTI_LINE_2
  *         @arg @ref MS32_EXTI_LINE_3
  *         @arg @ref MS32_EXTI_LINE_4
  *         @arg @ref MS32_EXTI_LINE_5
  *         @arg @ref MS32_EXTI_LINE_6
  *         @arg @ref MS32_EXTI_LINE_7
  *         @arg @ref MS32_EXTI_LINE_8
  *         @arg @ref MS32_EXTI_LINE_9
  *         @arg @ref MS32_EXTI_LINE_10
  *         @arg @ref MS32_EXTI_LINE_11
  *         @arg @ref MS32_EXTI_LINE_12
  *         @arg @ref MS32_EXTI_LINE_13
  *         @arg @ref MS32_EXTI_LINE_14
  *         @arg @ref MS32_EXTI_LINE_15
  *         @arg @ref MS32_EXTI_LINE_16
  *         @arg @ref MS32_EXTI_LINE_17
  *         @arg @ref MS32_EXTI_LINE_19
  *         @arg @ref MS32_EXTI_LINE_20
  *         @arg @ref MS32_EXTI_LINE_21
  *         @arg @ref MS32_EXTI_LINE_22
  * @note   Please check each device line mapping for EXTI Line availability
  * @retval None
  */
__STATIC_INLINE void MS32_EXTI_EnableRisingTrig_0_31(uint32_t ExtiLine) {
  SET_BIT(EXTI->RTSR, ExtiLine);

}


/**
  * @brief  Disable ExtiLine Rising Edge Trigger for Lines in range 0 to 31
  * @note The configurable wakeup lines are edge-triggered. No glitch must be
  *       generated on these lines. If a rising edge on a configurable interrupt
  *       line occurs during a write operation in the EXTI_RTSR register, the
  *       pending bit is not set.
  *       Rising and falling edge triggers can be set for
  *       the same interrupt line. In this case, both generate a trigger
  *       condition.
  * @rmtoll RTSR        RTx           MS32_EXTI_DisableRisingTrig_0_31
  * @param  ExtiLine This parameter can be a combination of the following values:
  *         @arg @ref MS32_EXTI_LINE_0
  *         @arg @ref MS32_EXTI_LINE_1
  *         @arg @ref MS32_EXTI_LINE_2
  *         @arg @ref MS32_EXTI_LINE_3
  *         @arg @ref MS32_EXTI_LINE_4
  *         @arg @ref MS32_EXTI_LINE_5
  *         @arg @ref MS32_EXTI_LINE_6
  *         @arg @ref MS32_EXTI_LINE_7
  *         @arg @ref MS32_EXTI_LINE_8
  *         @arg @ref MS32_EXTI_LINE_9
  *         @arg @ref MS32_EXTI_LINE_10
  *         @arg @ref MS32_EXTI_LINE_11
  *         @arg @ref MS32_EXTI_LINE_12
  *         @arg @ref MS32_EXTI_LINE_13
  *         @arg @ref MS32_EXTI_LINE_14
  *         @arg @ref MS32_EXTI_LINE_15
  *         @arg @ref MS32_EXTI_LINE_16
  *         @arg @ref MS32_EXTI_LINE_17
  *         @arg @ref MS32_EXTI_LINE_19
  *         @arg @ref MS32_EXTI_LINE_20
  *         @arg @ref MS32_EXTI_LINE_21
  *         @arg @ref MS32_EXTI_LINE_22
  * @note   Please check each device line mapping for EXTI Line availability
  * @retval None
  */
__STATIC_INLINE void MS32_EXTI_DisableRisingTrig_0_31(uint32_t ExtiLine) {
  CLEAR_BIT(EXTI->RTSR, ExtiLine);

}


/**
  * @brief  Check if rising edge trigger is enabled for Lines in range 0 to 31
  * @rmtoll RTSR        RTx           MS32_EXTI_IsEnabledRisingTrig_0_31
  * @param  ExtiLine This parameter can be a combination of the following values:
  *         @arg @ref MS32_EXTI_LINE_0
  *         @arg @ref MS32_EXTI_LINE_1
  *         @arg @ref MS32_EXTI_LINE_2
  *         @arg @ref MS32_EXTI_LINE_3
  *         @arg @ref MS32_EXTI_LINE_4
  *         @arg @ref MS32_EXTI_LINE_5
  *         @arg @ref MS32_EXTI_LINE_6
  *         @arg @ref MS32_EXTI_LINE_7
  *         @arg @ref MS32_EXTI_LINE_8
  *         @arg @ref MS32_EXTI_LINE_9
  *         @arg @ref MS32_EXTI_LINE_10
  *         @arg @ref MS32_EXTI_LINE_11
  *         @arg @ref MS32_EXTI_LINE_12
  *         @arg @ref MS32_EXTI_LINE_13
  *         @arg @ref MS32_EXTI_LINE_14
  *         @arg @ref MS32_EXTI_LINE_15
  *         @arg @ref MS32_EXTI_LINE_16
  *         @arg @ref MS32_EXTI_LINE_17
  *         @arg @ref MS32_EXTI_LINE_19
  *         @arg @ref MS32_EXTI_LINE_20
  *         @arg @ref MS32_EXTI_LINE_21
  *         @arg @ref MS32_EXTI_LINE_22
  * @note   Please check each device line mapping for EXTI Line availability
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_EXTI_IsEnabledRisingTrig_0_31(uint32_t ExtiLine) {
  return (READ_BIT(EXTI->RTSR, ExtiLine) == (ExtiLine));
}


/** @defgroup EXTI_EF_Falling_Trigger_Management Falling_Trigger_Management
  * @{
  */

/**
  * @brief  Enable ExtiLine Falling Edge Trigger for Lines in range 0 to 31
  * @note The configurable wakeup lines are edge-triggered. No glitch must be
  *       generated on these lines. If a falling edge on a configurable interrupt
  *       line occurs during a write operation in the EXTI_FTSR register, the
  *       pending bit is not set.
  *       Rising and falling edge triggers can be set for
  *       the same interrupt line. In this case, both generate a trigger
  *       condition.
  * @rmtoll FTSR        FTx           MS32_EXTI_EnableFallingTrig_0_31
  * @param  ExtiLine This parameter can be a combination of the following values:
  *         @arg @ref MS32_EXTI_LINE_0
  *         @arg @ref MS32_EXTI_LINE_1
  *         @arg @ref MS32_EXTI_LINE_2
  *         @arg @ref MS32_EXTI_LINE_3
  *         @arg @ref MS32_EXTI_LINE_4
  *         @arg @ref MS32_EXTI_LINE_5
  *         @arg @ref MS32_EXTI_LINE_6
  *         @arg @ref MS32_EXTI_LINE_7
  *         @arg @ref MS32_EXTI_LINE_8
  *         @arg @ref MS32_EXTI_LINE_9
  *         @arg @ref MS32_EXTI_LINE_10
  *         @arg @ref MS32_EXTI_LINE_11
  *         @arg @ref MS32_EXTI_LINE_12
  *         @arg @ref MS32_EXTI_LINE_13
  *         @arg @ref MS32_EXTI_LINE_14
  *         @arg @ref MS32_EXTI_LINE_15
  *         @arg @ref MS32_EXTI_LINE_16
  *         @arg @ref MS32_EXTI_LINE_17
  *         @arg @ref MS32_EXTI_LINE_19
  *         @arg @ref MS32_EXTI_LINE_20
  *         @arg @ref MS32_EXTI_LINE_21
  *         @arg @ref MS32_EXTI_LINE_22
  * @note   Please check each device line mapping for EXTI Line availability
  * @retval None
  */
__STATIC_INLINE void MS32_EXTI_EnableFallingTrig_0_31(uint32_t ExtiLine) {
  SET_BIT(EXTI->FTSR, ExtiLine);
}


/**
  * @brief  Disable ExtiLine Falling Edge Trigger for Lines in range 0 to 31
  * @note The configurable wakeup lines are edge-triggered. No glitch must be
  *       generated on these lines. If a Falling edge on a configurable interrupt
  *       line occurs during a write operation in the EXTI_FTSR register, the
  *       pending bit is not set.
  *       Rising and falling edge triggers can be set for the same interrupt line.
  *       In this case, both generate a trigger condition.
  * @rmtoll FTSR        FTx           MS32_EXTI_DisableFallingTrig_0_31
  * @param  ExtiLine This parameter can be a combination of the following values:
  *         @arg @ref MS32_EXTI_LINE_0
  *         @arg @ref MS32_EXTI_LINE_1
  *         @arg @ref MS32_EXTI_LINE_2
  *         @arg @ref MS32_EXTI_LINE_3
  *         @arg @ref MS32_EXTI_LINE_4
  *         @arg @ref MS32_EXTI_LINE_5
  *         @arg @ref MS32_EXTI_LINE_6
  *         @arg @ref MS32_EXTI_LINE_7
  *         @arg @ref MS32_EXTI_LINE_8
  *         @arg @ref MS32_EXTI_LINE_9
  *         @arg @ref MS32_EXTI_LINE_10
  *         @arg @ref MS32_EXTI_LINE_11
  *         @arg @ref MS32_EXTI_LINE_12
  *         @arg @ref MS32_EXTI_LINE_13
  *         @arg @ref MS32_EXTI_LINE_14
  *         @arg @ref MS32_EXTI_LINE_15
  *         @arg @ref MS32_EXTI_LINE_16
  *         @arg @ref MS32_EXTI_LINE_17
  *         @arg @ref MS32_EXTI_LINE_19
  *         @arg @ref MS32_EXTI_LINE_20
  *         @arg @ref MS32_EXTI_LINE_21
  *         @arg @ref MS32_EXTI_LINE_22
  * @note   Please check each device line mapping for EXTI Line availability
  * @retval None
  */
__STATIC_INLINE void MS32_EXTI_DisableFallingTrig_0_31(uint32_t ExtiLine) {
  CLEAR_BIT(EXTI->FTSR, ExtiLine);
}


/**
  * @brief  Check if falling edge trigger is enabled for Lines in range 0 to 31
  * @rmtoll FTSR        FTx           MS32_EXTI_IsEnabledFallingTrig_0_31
  * @param  ExtiLine This parameter can be a combination of the following values:
  *         @arg @ref MS32_EXTI_LINE_0
  *         @arg @ref MS32_EXTI_LINE_1
  *         @arg @ref MS32_EXTI_LINE_2
  *         @arg @ref MS32_EXTI_LINE_3
  *         @arg @ref MS32_EXTI_LINE_4
  *         @arg @ref MS32_EXTI_LINE_5
  *         @arg @ref MS32_EXTI_LINE_6
  *         @arg @ref MS32_EXTI_LINE_7
  *         @arg @ref MS32_EXTI_LINE_8
  *         @arg @ref MS32_EXTI_LINE_9
  *         @arg @ref MS32_EXTI_LINE_10
  *         @arg @ref MS32_EXTI_LINE_11
  *         @arg @ref MS32_EXTI_LINE_12
  *         @arg @ref MS32_EXTI_LINE_13
  *         @arg @ref MS32_EXTI_LINE_14
  *         @arg @ref MS32_EXTI_LINE_15
  *         @arg @ref MS32_EXTI_LINE_16
  *         @arg @ref MS32_EXTI_LINE_17
  *         @arg @ref MS32_EXTI_LINE_19
  *         @arg @ref MS32_EXTI_LINE_20
  *         @arg @ref MS32_EXTI_LINE_21
  *         @arg @ref MS32_EXTI_LINE_22
  * @note   Please check each device line mapping for EXTI Line availability
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_EXTI_IsEnabledFallingTrig_0_31(uint32_t ExtiLine) {
  return (READ_BIT(EXTI->FTSR, ExtiLine) == (ExtiLine));
}


/** @defgroup EXTI_EF_Software_Interrupt_Management Software_Interrupt_Management
  * @{
  */

/**
  * @brief  Generate a software Interrupt Event for Lines in range 0 to 31
  * @note If the interrupt is enabled on this line in the EXTI_IMR, writing a 1 to
  *       this bit when it is at '0' sets the corresponding pending bit in EXTI_PR
  *       resulting in an interrupt request generation.
  *       This bit is cleared by clearing the corresponding bit in the EXTI_PR
  *       register (by writing a 1 into the bit)
  * @rmtoll SWIER       SWIx          MS32_EXTI_GenerateSWI_0_31
  * @param  ExtiLine This parameter can be a combination of the following values:
  *         @arg @ref MS32_EXTI_LINE_0
  *         @arg @ref MS32_EXTI_LINE_1
  *         @arg @ref MS32_EXTI_LINE_2
  *         @arg @ref MS32_EXTI_LINE_3
  *         @arg @ref MS32_EXTI_LINE_4
  *         @arg @ref MS32_EXTI_LINE_5
  *         @arg @ref MS32_EXTI_LINE_6
  *         @arg @ref MS32_EXTI_LINE_7
  *         @arg @ref MS32_EXTI_LINE_8
  *         @arg @ref MS32_EXTI_LINE_9
  *         @arg @ref MS32_EXTI_LINE_10
  *         @arg @ref MS32_EXTI_LINE_11
  *         @arg @ref MS32_EXTI_LINE_12
  *         @arg @ref MS32_EXTI_LINE_13
  *         @arg @ref MS32_EXTI_LINE_14
  *         @arg @ref MS32_EXTI_LINE_15
  *         @arg @ref MS32_EXTI_LINE_16
  *         @arg @ref MS32_EXTI_LINE_17
  *         @arg @ref MS32_EXTI_LINE_19
  *         @arg @ref MS32_EXTI_LINE_20
  *         @arg @ref MS32_EXTI_LINE_21
  *         @arg @ref MS32_EXTI_LINE_22
  * @note   Please check each device line mapping for EXTI Line availability
  * @retval None
  */
__STATIC_INLINE void MS32_EXTI_GenerateSWI_0_31(uint32_t ExtiLine) {
  SET_BIT(EXTI->SWIER, ExtiLine);
}


/** @defgroup EXTI_EF_Flag_Management Flag_Management
  * @{
  */

/**
  * @brief  Check if the ExtLine Flag is set or not for Lines in range 0 to 31
  * @note This bit is set when the selected edge event arrives on the interrupt
  *       line. This bit is cleared by writing a 1 to the bit.
  * @rmtoll PR          PIFx           MS32_EXTI_IsActiveFlag_0_31
  * @param  ExtiLine This parameter can be a combination of the following values:
  *         @arg @ref MS32_EXTI_LINE_0
  *         @arg @ref MS32_EXTI_LINE_1
  *         @arg @ref MS32_EXTI_LINE_2
  *         @arg @ref MS32_EXTI_LINE_3
  *         @arg @ref MS32_EXTI_LINE_4
  *         @arg @ref MS32_EXTI_LINE_5
  *         @arg @ref MS32_EXTI_LINE_6
  *         @arg @ref MS32_EXTI_LINE_7
  *         @arg @ref MS32_EXTI_LINE_8
  *         @arg @ref MS32_EXTI_LINE_9
  *         @arg @ref MS32_EXTI_LINE_10
  *         @arg @ref MS32_EXTI_LINE_11
  *         @arg @ref MS32_EXTI_LINE_12
  *         @arg @ref MS32_EXTI_LINE_13
  *         @arg @ref MS32_EXTI_LINE_14
  *         @arg @ref MS32_EXTI_LINE_15
  *         @arg @ref MS32_EXTI_LINE_16
  *         @arg @ref MS32_EXTI_LINE_17
  *         @arg @ref MS32_EXTI_LINE_19
  *         @arg @ref MS32_EXTI_LINE_20
  *         @arg @ref MS32_EXTI_LINE_21
  *         @arg @ref MS32_EXTI_LINE_22
  * @note   Please check each device line mapping for EXTI Line availability
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_EXTI_IsActiveFlag_0_31(uint32_t ExtiLine) {
  return (READ_BIT(EXTI->PR, ExtiLine) == (ExtiLine));
}


/**
  * @brief  Read ExtLine Combination Flag for Lines in range 0 to 31
  * @note This bit is set when the selected edge event arrives on the interrupt
  *       line. This bit is cleared by writing a 1 to the bit.
  * @rmtoll PR          PIFx           MS32_EXTI_ReadFlag_0_31
  * @param  ExtiLine This parameter can be a combination of the following values:
  *         @arg @ref MS32_EXTI_LINE_0
  *         @arg @ref MS32_EXTI_LINE_1
  *         @arg @ref MS32_EXTI_LINE_2
  *         @arg @ref MS32_EXTI_LINE_3
  *         @arg @ref MS32_EXTI_LINE_4
  *         @arg @ref MS32_EXTI_LINE_5
  *         @arg @ref MS32_EXTI_LINE_6
  *         @arg @ref MS32_EXTI_LINE_7
  *         @arg @ref MS32_EXTI_LINE_8
  *         @arg @ref MS32_EXTI_LINE_9
  *         @arg @ref MS32_EXTI_LINE_10
  *         @arg @ref MS32_EXTI_LINE_11
  *         @arg @ref MS32_EXTI_LINE_12
  *         @arg @ref MS32_EXTI_LINE_13
  *         @arg @ref MS32_EXTI_LINE_14
  *         @arg @ref MS32_EXTI_LINE_15
  *         @arg @ref MS32_EXTI_LINE_16
  *         @arg @ref MS32_EXTI_LINE_17
  *         @arg @ref MS32_EXTI_LINE_19
  *         @arg @ref MS32_EXTI_LINE_20
  *         @arg @ref MS32_EXTI_LINE_21
  *         @arg @ref MS32_EXTI_LINE_22
  * @note   Please check each device line mapping for EXTI Line availability
  * @retval @note This bit is set when the selected edge event arrives on the interrupt
  */
__STATIC_INLINE uint32_t MS32_EXTI_ReadFlag_0_31(uint32_t ExtiLine) {
  return (uint32_t)(READ_BIT(EXTI->PR, ExtiLine));
}


/**
  * @brief  Clear ExtLine Flags  for Lines in range 0 to 31
  * @note This bit is set when the selected edge event arrives on the interrupt
  *       line. This bit is cleared by writing a 1 to the bit.
  * @rmtoll PR          PIFx           MS32_EXTI_ClearFlag_0_31
  * @param  ExtiLine This parameter can be a combination of the following values:
  *         @arg @ref MS32_EXTI_LINE_0
  *         @arg @ref MS32_EXTI_LINE_1
  *         @arg @ref MS32_EXTI_LINE_2
  *         @arg @ref MS32_EXTI_LINE_3
  *         @arg @ref MS32_EXTI_LINE_4
  *         @arg @ref MS32_EXTI_LINE_5
  *         @arg @ref MS32_EXTI_LINE_6
  *         @arg @ref MS32_EXTI_LINE_7
  *         @arg @ref MS32_EXTI_LINE_8
  *         @arg @ref MS32_EXTI_LINE_9
  *         @arg @ref MS32_EXTI_LINE_10
  *         @arg @ref MS32_EXTI_LINE_11
  *         @arg @ref MS32_EXTI_LINE_12
  *         @arg @ref MS32_EXTI_LINE_13
  *         @arg @ref MS32_EXTI_LINE_14
  *         @arg @ref MS32_EXTI_LINE_15
  *         @arg @ref MS32_EXTI_LINE_16
  *         @arg @ref MS32_EXTI_LINE_17
  *         @arg @ref MS32_EXTI_LINE_19
  *         @arg @ref MS32_EXTI_LINE_20
  *         @arg @ref MS32_EXTI_LINE_21
  *         @arg @ref MS32_EXTI_LINE_22
  * @note   Please check each device line mapping for EXTI Line availability
  * @retval None
  */
__STATIC_INLINE void MS32_EXTI_ClearFlag_0_31(uint32_t ExtiLine) {
  WRITE_REG(EXTI->PR, ExtiLine);
}


/** @defgroup EXTI_EF_Init Initialization and de-initialization functions
  * @{
  */
ErrorStatus MS32_EXTI_DeInit      (void);
ErrorStatus MS32_EXTI_Init        (MS32_EXTI_InitTypeDef *EXTI_InitStruct);
void        MS32_EXTI_StructInit  (MS32_EXTI_InitTypeDef *EXTI_InitStruct);
void        MS32_EXTI_PinITConfig (uint32_t ExtiLine, uint32_t ExtiPort, uint32_t Priority, FunctionalState State);

/** @defgroup EXTI_EF_Application function
  * @{
  */
void       MS32_EXTI_GenerateSWI   (uint32_t ExtiLine);
FlagStatus MS32_EXTI_GetStatusFlag (uint32_t ExtiLine);


#ifdef __cplusplus
}
#endif

#endif /* __MS32F0XX_EXTI_H */

/******************************** END OF FILE *********************************/
