/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MS32F0XX_OPAMP_H
#define __MS32F0XX_OPAMP_H

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
/**
  * @brief OP Init Structure definition
  */
typedef struct {
  uint32_t OutputEn;          /*!< The new state of the operation output polarity.
                                   This parameter can be a value of @ref OP_OUT_EN */
  uint32_t GAIN;              /*!< The new state of the operation gaom selection.
                                   This parameter can be a value of @ref OP_GAIN_SEL */
  uint32_t NegitiveInputSel;  /*!< The new state of the operation negitive input selection.
                                   This parameter can be a value of @ref OP_OUTPUT_FILTER */
} MS32_OP_InitTypeDef;

/**
  * @brief OP calibration Structure definition
  */
typedef struct {
  uint8_t OpPosCaliData;      /*!< The value of the operation position calibration register. */
  uint8_t OpNegCaliData;      /*!< The value of the operation negative calibration register. */
} MS32_OP_CaliTypeDef;


/* Exported constants --------------------------------------------------------*/
/** @defgroup OP_UNIT Operation unit
  * @{
  */
#define MS32_OP1                     (0x00000001U)
#define MS32_OP2                     (0x00000002U)
#define MS32_OP3                     (0x00000004U)


/** @defgroup OP_LOCK Operation lock
  * @{
  */
#define MS32_OP_UNLOCK               (0x00000000U)
#define MS32_OP_LOCK                 OPAMP_OPCR_OPAMPLCK


/** @defgroup OP_OUT_EN Operation output enable
  * @{
  */
#define MS32_OP_OUT_DIS              (0x00000000U)
#define MS32_OP_OUT_EN               OPAMP_OPCR_OPAMP1OUTEN


/** @defgroup OP_GAIN_SEL Operation gain selection
  * @{
  */
#define MS32_OP_GAIN2               (0x00000000U)
#define MS32_OP_GAIN4               OPAMP_OPCR_OPAMP1GAIN_0
#define MS32_OP_GAIN8               OPAMP_OPCR_OPAMP1GAIN_1
#define MS32_OP_GAIN16              (OPAMP_OPCR_OPAMP1GAIN_1 | OPAMP_OPCR_OPAMP1GAIN_0)


/** @defgroup OP_NEG_INPUT_SEL Operation negative input selection
  * @{
  */
#define MS32_OP_NEGINPUT_PIN        (0x00000000U)
#define MS32_OP_NEGINPUT_OPOUT      OPAMP_OPCR_OPAMP1NSEL_0
#define MS32_OP_NEGINPUT_GAIN       OPAMP_OPCR_OPAMP1NSEL_1
#define MS32_OP_NEGINPUT_GAIN_PIN   (OPAMP_OPCR_OPAMP1NSEL_1 | OPAMP_OPCR_OPAMP1NSEL_0)


/* Exported macro ------------------------------------------------------------*/
/** @defgroup OP_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in OP register
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define MS32_OP_WriteReg(__REG__, __VALUE__) WRITE_REG(CMP_OP->__REG__, (__VALUE__))

/**
  * @brief  Read a value in OP register
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define MS32_OP_ReadReg(__REG__) READ_REG(CMP_OP->__REG__)


/* Exported functions --------------------------------------------------------*/
/**
  * @brief  Enable operation 1
  * @rmtoll OPCR           OP1ON         MS32_OP1_Enable
  * @retval None
  */
__STATIC_INLINE void MS32_OP1_Enable(void) {
  SET_BIT(CMP_OP->OPCR, OPAMP_OPCR_OPAMP1EN);
}

/**
  * @brief  Disable operation 1
  * @rmtoll OPCR           OP1ON         MS32_OP1_Disable
  * @retval None
  */
__STATIC_INLINE void MS32_OP1_Disable(void) {
  CLEAR_BIT(CMP_OP->OPCR, OPAMP_OPCR_OPAMP1EN);
}

/**
  * @brief  Enable operation 2
  * @rmtoll OPCR           OP2ON         MS32_OP2_Enable
  * @retval None
  */
__STATIC_INLINE void MS32_OP2_Enable(void) {
  SET_BIT(CMP_OP->OPCR, OPAMP_OPCR_OPAMP2EN);
}

/**
  * @brief  Disable operation 2
  * @rmtoll OPCR           OP2ON         MS32_OP2_Disable
  * @retval None
  */
__STATIC_INLINE void MS32_OP2_Disable(void) {
  CLEAR_BIT(CMP_OP->OPCR, OPAMP_OPCR_OPAMP2EN);
}

/**
  * @brief  Enable operation 3
  * @rmtoll OPCR           OP3ON         MS32_OP3_Enable
  * @retval None
  */
__STATIC_INLINE void MS32_OP3_Enable(void) {
  SET_BIT(CMP_OP->OPCR, OPAMP_OPCR_OPAMP3EN);
}

/**
  * @brief  Disable operation 3
  * @rmtoll OPCR           OP3ON         MS32_OP3_Disable
  * @retval None
  */
__STATIC_INLINE void MS32_OP3_Disable(void) {
  CLEAR_BIT(CMP_OP->OPCR, OPAMP_OPCR_OPAMP3EN);
}


/** @defgroup OP_EF_Init Initialization and de-initialization functions
  * @{
  */
ErrorStatus MS32_OP_DeInit     (uint32_t OpUnit);
void        MS32_OP_StructInit (MS32_OP_InitTypeDef *OpInitStr);
ErrorStatus MS32_OP_Init       (uint32_t OpUnit, MS32_OP_InitTypeDef *OpInitStr);

/** @defgroup OP_EF_Application function
  * @{
  */
ErrorStatus MS32_OP_GetCaliValue (uint32_t OpUnit, MS32_OP_CaliTypeDef *OpCaliStr);
ErrorStatus MS32_OP_SetCaliValue (uint32_t OpUnit, MS32_OP_CaliTypeDef *OpCaliStr);
void        MS32_OP_LockEn       (void);


#ifdef __cplusplus
}
#endif

#endif /* __MS32F0XX_OPAMP_H */

/******************************** END OF FILE *********************************/
