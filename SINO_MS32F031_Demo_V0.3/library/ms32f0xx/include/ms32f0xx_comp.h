/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MS32F0XX_COMP_H
#define __MS32F0XX_COMP_H

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
  * @brief CMP Init Structure definition
  */
typedef struct {
  uint32_t Lock;              /*!< The new state of the comparison register lock.
                                   This parameter can be a value of @ref COMP_LOCK */
  uint32_t OutputSel;         /*!< The new state of the comparison output selection.
                                   This parameter can be a value of @ref COMP_OUTPUT_SELECT */
  uint32_t OutputPolarity;    /*!< The new state of the comparison output polarity.
                                   This parameter can be a value of @ref COMP_OUTPUT_POL */
  uint32_t OutputFilter;      /*!< The new state of the comparison output filter.
                                   This parameter can be a value of @ref COMP_OUTPUT_FILTER */
  uint32_t CrvSel;            /*!< The new state of the comparison voltage reference selection.
                                   This parameter can be a value of @ref COMP_CRV_SELECT */
  uint32_t CrvDivSel;         /*!< The new state of the comparison voltage reference selection.
                                   This parameter can be a value of @ref COMP_CRV_DIV_SELECT */
  uint32_t NegativeSel;       /*!< The new state of the comparison negative selection.
                                   This parameter can be a value of @ref COMP_NEG_SEL */
  uint32_t PositionSel;       /*!< The new state of the comparison position selection.
                                   This parameter can be a value of @ref COMP_POS_SEL */
  uint32_t HysteresisSel;     /*!< The new state of the comparison hysteresis selection.
                                   This parameter can be a value of @ref COMP_HYST_SELECT */
} MS32_CMP_InitTypeDef;

/**
  * @brief CMP calibration Structure definition
  */
typedef struct {
  uint8_t CmpPosCaliData;     /*!< The value of the comparison position calibration register. */
  uint8_t CmpNegCaliData;     /*!< The value of the comparison negative calibration register. */
} MS32_CMP_CaliTypeDef;


/* Exported constants --------------------------------------------------------*/
/** @defgroup COMP_UNIT Comparison unit
  * @{
  */
#define MS32_COMP1                     (0x00000001U)
#define MS32_COMP2                     (0x00000002U)


/** @defgroup COMP_LOCK Comparison lock
  * @{
  */
#define MS32_COMP_UNLOCK               (0x00000000U)
#define MS32_COMP_LOCK                 CMP_CPxCR_CPxLCK


/** @defgroup COMP_OUTPUT Comparison output
  * @{
  */
#define MS32_COMP_OUTPUT_LOW           (0x00000000U)
#define MS32_COMP_OUTPUT_HIGH          CMP_CPxCR_CPxOUT


/** @defgroup COMP_OUTPUT_SELECT Comparison output select
  * @{
  */
#define MS32_COMP_OUT_TIM1_BKIN        (0x00000000U)
#define MS32_COMP_OUT_TIM1_OCREF_CLR   CMP_CPxCR_CPxOUTSEL_0
#define MS32_COMP_OUT_TIM1_IC1         CMP_CPxCR_CPxOUTSEL_1
#define MS32_COMP_OUT_TIM2_IC4         (CMP_CPxCR_CPxOUTSEL_1 | CMP_CPxCR_CPxOUTSEL_0)
#define MS32_COMP_OUT_TIM2_OCREF_CLR   CMP_CPxCR_CPxOUTSEL_2
#define MS32_COMP_OUT_TIM3_IC1         (CMP_CPxCR_CPxOUTSEL_2 | CMP_CPxCR_CPxOUTSEL_0)
#define MS32_COMP_OUT_TIM3_OCREF_CLR   (CMP_CPxCR_CPxOUTSEL_2 | CMP_CPxCR_CPxOUTSEL_1)


/** @defgroup COMP_OUTPUT_POL Comparison output polarity
  * @{
  */
#define MS32_COMP_OUT_POL_POS          (0x00000000U)
#define MS32_COMP_OUT_POL_NEG          CMP_CPxCR_CPxPOL


/** @defgroup COMP_OUTPUT_FILTER Comparison output filter
  * @{
  */
#define MS32_COMP_OUT_FILTER_CLK1      (0x00000000U)
#define MS32_COMP_OUT_FILTER_CLK4      CMP_CPxCR_CPxOFLT_0
#define MS32_COMP_OUT_FILTER_CLK16     CMP_CPxCR_CPxOFLT_1
#define MS32_COMP_OUT_FILTER_CLK32     (CMP_CPxCR_CPxOFLT_1 | CMP_CPxCR_CPxOFLT_0)
#define MS32_COMP_OUT_FILTER_CLK64     CMP_CPxCR_CPxOFLT_2
#define MS32_COMP_OUT_FILTER_CLK128    (CMP_CPxCR_CPxOFLT_2 | CMP_CPxCR_CPxOFLT_0)
#define MS32_COMP_OUT_FILTER_CLK256    (CMP_CPxCR_CPxOFLT_2 | CMP_CPxCR_CPxOFLT_1)
#define MS32_COMP_OUT_FILTER_CLK512    (CMP_CPxCR_CPxOFLT_2 | CMP_CPxCR_CPxOFLT_1 | CMP_CPxCR_CPxOFLT_0)


/** @defgroup COMP_CRV_DIV_SELECT Comparison voltage reference division select
  * @{
  */
#define MS32_COMP_CRV_1_DIV_8          (0x00000000U)
#define MS32_COMP_CRV_2_DIV_8          CMP_CPxCR_CPxRVSEL_0
#define MS32_COMP_CRV_3_DIV_8          CMP_CPxCR_CPxRVSEL_1
#define MS32_COMP_CRV_4_DIV_8          (CMP_CPxCR_CPxRVSEL_1 | CMP_CPxCR_CPxRVSEL_0)
#define MS32_COMP_CRV_5_DIV_8          CMP_CPxCR_CPxRVSEL_2
#define MS32_COMP_CRV_6_DIV_8          (CMP_CPxCR_CPxRVSEL_2 | CMP_CPxCR_CPxRVSEL_0)
#define MS32_COMP_CRV_7_DIV_8          (CMP_CPxCR_CPxRVSEL_2 | CMP_CPxCR_CPxRVSEL_1)
#define MS32_COMP_CRV_8_DIV_8          (CMP_CPxCR_CPxRVSEL_2 | CMP_CPxCR_CPxRVSEL_1 | CMP_CPxCR_CPxRVSEL_0)


/** @defgroup COMP_NEG_SELECT Comparison negative select
  * @{
  */
#define MS32_COMP_NEG_PIN              (0x00000000U)
#define MS32_COMP_NEG_CRV              CMP_CPxCR_CPxNSEL


/** @defgroup COMP_POS_SELECT Comparison positive select
  * @{
  */
#define MS32_COMP_POS_CPxP_PIN         (0x00000000U)
#define MS32_COMP_POS_CPx2P_PIN        CMP_CPxCR_CPxPSEL_0
#define MS32_COMP_POS_CPx3P_PIN        CMP_CPxCR_CPxPSEL_1
#define MS32_COMP_POS_OP1OUT           (CMP_CPxCR_CPxPSEL_1 | CMP_CPxCR_CPxPSEL_0)
#define MS32_COMP_POS_OP2OUT           CMP_CPxCR_CPxPSEL_2
#define MS32_COMP_POS_OP3OUT           (CMP_CPxCR_CPxPSEL_2 | CMP_CPxCR_CPxPSEL_0)


/** @defgroup COMP_HYST_SELECT Comparison hysteresis select
  * @{
  */
#define MS32_COMP_HYST_0MV             (0x00000000U)
#define MS32_COMP_HYST_15MV            CMP_CPxCR_CPxHYST_0
#define MS32_COMP_HYST_30MV            CMP_CPxCR_CPxHYST_1
#define MS32_COMP_HYST_90MV            (CMP_CPxCR_CPxHYST_1 | CMP_CPxCR_CPxHYST_0)


/** @defgroup COMP_CRV_SELECT Comparison voltage reference select
  * @{
  */
#define MS32_COMP_CRV_AVDD             (0x00000000U)
#define MS32_COMP_CRV_VREF             CMP_CPANA_CP1VOLT


/** @defgroup COMP_TI_Mode Comparison interrupt Mode
  * @{
  */
#define MS32_COMP_IT_DISABLE           (0x00000000U)          /*!< Comparison interrupt disable */
#define MS32_COMP_IT_ENABLE            (0x00000001U)          /*!< Comparison interrupt enable */


/* Exported macro ------------------------------------------------------------*/
/** @defgroup COMP_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in COMP register
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define MS32_CMP_WriteReg(__REG__, __VALUE__) WRITE_REG(CMP_OP->__REG__, (__VALUE__))

/**
  * @brief  Read a value in COMP register
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define MS32_CMP_ReadReg(__REG__) READ_REG(CMP_OP->__REG__)


/* Exported functions --------------------------------------------------------*/
/**
  * @brief  Enable comparision 1
  * @rmtoll CP1CR           CMP1ON         MS32_CMP1_Enable
  * @retval None
  */
__STATIC_INLINE void MS32_CMP1_Enable(void) {
  SET_BIT(CMP_OP->CP1CR, CMP_CPxCR_CPxEN);
}

/**
  * @brief  Disable comparision 1
  * @rmtoll CP1CR           CMP1ON         MS32_CMP1_Disable
  * @retval None
  */
__STATIC_INLINE void MS32_CMP1_Disable(void) {
  CLEAR_BIT(CMP_OP->CP1CR, CMP_CPxCR_CPxEN);
}

/**
  * @brief  Enable comparision 2
  * @rmtoll CP2CR           CMP2ON         MS32_CMP2_Enable
  * @retval None
  */
__STATIC_INLINE void MS32_CMP2_Enable(void) {
  SET_BIT(CMP_OP->CP2CR, CMP_CPxCR_CPxEN);
}

/**
  * @brief  Disable comparision 2
  * @rmtoll CP2CR           CMP2ON         MS32_CMP2_Disable
  * @retval None
  */
__STATIC_INLINE void MS32_CMP2_Disable(void) {
  CLEAR_BIT(CMP_OP->CP2CR, CMP_CPxCR_CPxEN);
}

/**
  * @brief  Select the hysteresis voltage by the Comparision 1
  * @rmtoll CP1CR           CP2HYST        MS32_CMP1_SetHysteresisVoltage
  * @param  HystVolt This parameter can be one of the following values:
  *         @arg @ref MS32_COMP_HYST_0MV 
  *         @arg @ref MS32_COMP_HYST_15MV
  *         @arg @ref MS32_COMP_HYST_30MV
  *         @arg @ref MS32_COMP_HYST_90MV
  * @retval None
  */
__STATIC_INLINE void MS32_CMP1_SetHysteresisVoltage(uint32_t HystVolt) {
  MODIFY_REG(CMP_OP->CP1CR, CMP_CPxCR_CPxHYST, HystVolt);
}

/**
  * @brief  Get the hysteresis voltage by the Comparision 1
  * @rmtoll CP1CR           CP2HYST        MS32_CMP1_GetHysteresisVoltage
  * @param  None
  * @retval This parameter can be one of the following values:
  *         @arg @ref MS32_COMP_HYST_0MV 
  *         @arg @ref MS32_COMP_HYST_15MV
  *         @arg @ref MS32_COMP_HYST_30MV
  *         @arg @ref MS32_COMP_HYST_90MV
  */
__STATIC_INLINE uint32_t MS32_CMP1_GetHysteresisVoltage(void) {
  return (CMP_OP->CP1CR & CMP_CPxCR_CPxHYST);
}

/**
  * @brief  Select the hysteresis voltage by the Comparision 2
  * @rmtoll CP2CR           CP2HYST        MS32_CMP2_SetHysteresisVoltage
  * @param  HystVolt This parameter can be one of the following values:
  *         @arg @ref MS32_COMP_HYST_0MV 
  *         @arg @ref MS32_COMP_HYST_15MV
  *         @arg @ref MS32_COMP_HYST_30MV
  *         @arg @ref MS32_COMP_HYST_90MV
  * @retval None
  */
__STATIC_INLINE void MS32_CMP2_SetHysteresisVoltage(uint32_t HystVolt) {
  MODIFY_REG(CMP_OP->CP2CR, CMP_CPxCR_CPxHYST, HystVolt);
}

/**
  * @brief  Get the hysteresis voltage by the Comparision 2
  * @rmtoll CP2CR           CP2HYST        MS32_CMP2_GetHysteresisVoltage
  * @param  None
  * @retval This parameter can be one of the following values:
  *         @arg @ref MS32_COMP_HYST_0MV 
  *         @arg @ref MS32_COMP_HYST_15MV
  *         @arg @ref MS32_COMP_HYST_30MV
  *         @arg @ref MS32_COMP_HYST_90MV
  */
__STATIC_INLINE uint32_t MS32_CMP2_GetHysteresisVoltage(void) {
  return (CMP_OP->CP2CR & CMP_CPxCR_CPxHYST);
}

/**
  * @brief  Select the positive input by the Comparision 1
  * @rmtoll CP1CR           CP1PSEL        MS32_CMP1_SetPostiveInput
  * @param  PosInput This parameter can be one of the following values:
  *         @arg @ref MS32_COMP_POS_CPxP_PIN 
  *         @arg @ref MS32_COMP_POS_CPx2P_PIN
  *         @arg @ref MS32_COMP_POS_CPx3P_PIN
  *         @arg @ref MS32_COMP_POS_OP1OUT   
  *         @arg @ref MS32_COMP_POS_OP2OUT   
  *         @arg @ref MS32_COMP_POS_OP3OUT   
  * @retval None
  */
__STATIC_INLINE void MS32_CMP1_SetPostiveInput(uint32_t PosInput) {
  MODIFY_REG(CMP_OP->CP1CR, CMP_CPxCR_CPxPSEL, PosInput);
}

/**
  * @brief  Get the positive input by the Comparision 1
  * @rmtoll CP1CR           CP1PSEL        MS32_CMP1_GetPostiveInput
  * @param  None
  * @retval This parameter can be one of the following values:
  *         @arg @ref MS32_COMP_POS_CPxP_PIN 
  *         @arg @ref MS32_COMP_POS_CPx2P_PIN
  *         @arg @ref MS32_COMP_POS_CPx3P_PIN
  *         @arg @ref MS32_COMP_POS_OP1OUT   
  *         @arg @ref MS32_COMP_POS_OP2OUT   
  *         @arg @ref MS32_COMP_POS_OP3OUT   
  */
__STATIC_INLINE uint32_t MS32_CMP1_GetPostiveInput(void) {
  return (CMP_OP->CP1CR & CMP_CPxCR_CPxPSEL);
}

/**
  * @brief  Select the positive input by the Comparision 2
  * @rmtoll CP2CR           CP2PSEL        MS32_CMP2_SetPostiveInput
  * @param  PosInput This parameter can be one of the following values:
  *         @arg @ref MS32_COMP_POS_CPxP_PIN
  *         @arg @ref MS32_COMP_POS_OP1OUT  
  *         @arg @ref MS32_COMP_POS_OP2OUT  
  *         @arg @ref MS32_COMP_POS_OP3OUT
  * @retval None
  */
__STATIC_INLINE void MS32_CMP2_SetPostiveInput(uint32_t PosInput) {
  if (PosInput <= MS32_COMP_POS_CPx3P_PIN) {
    CLEAR_BIT(CMP_OP->CP2CR, CMP_CPxCR_CPxPSEL);
  } else {
    MODIFY_REG(CMP_OP->CP2CR, CMP_CPxCR_CPxPSEL, PosInput - 2);
  }
}

/**
  * @brief  Get the positive input by the Comparision 2
  * @rmtoll CP2CR           CP2PSEL        MS32_CMP2_GetPostiveInput
  * @param  None
  * @retval This parameter can be one of the following values:
  *         @arg @ref MS32_COMP_POS_CPxP_PIN
  *         @arg @ref MS32_COMP_POS_OP1OUT  
  *         @arg @ref MS32_COMP_POS_OP2OUT  
  *         @arg @ref MS32_COMP_POS_OP3OUT
  */
__STATIC_INLINE uint32_t MS32_CMP2_GetPostiveInput(void) {
  uint32_t PosInput;

  PosInput = CMP_OP->CP2CR & CMP_CPxCR_CPxPSEL;
  if (PosInput) {
    PosInput += (MS32_COMP_POS_OP1OUT - MS32_COMP_POS_CPx2P_PIN);
  }
  return PosInput;
}

/**
  * @brief  Select the negitive input by the Comparision 1
  * @rmtoll CP1CR           CP1NSEL        MS32_CMP1_SetNegitiveInput
  * @param  NegInput This parameter can be one of the following values:
  *         @arg @ref MS32_COMP_NEG_PIN
  *         @arg @ref MS32_COMP_NEG_CRV
  * @retval None
  */
__STATIC_INLINE void MS32_CMP1_SetNegitiveInput(uint32_t NegInput) {
  MODIFY_REG(CMP_OP->CP1CR, CMP_CPxCR_CPxNSEL, NegInput);
}

/**
  * @brief  Get the negitive input by the Comparision 1
  * @rmtoll CP1CR           CP1NSEL        MS32_CMP1_GetNegitiveInput
  * @param  None
  * @retval This parameter can be one of the following values:
  *         @arg @ref MS32_COMP_NEG_PIN
  *         @arg @ref MS32_COMP_NEG_CRV
  */
__STATIC_INLINE uint32_t MS32_CMP1_GetNegitiveInput(void) {
  return (CMP_OP->CP1CR & CMP_CPxCR_CPxNSEL);
}

/**
  * @brief  Select the negitive input by the Comparision 2
  * @rmtoll CP2CR           CP2NSEL        MS32_CMP2_SetNegitiveInput
  * @param  NegInput This parameter can be one of the following values:
  *         @arg @ref MS32_COMP_NEG_PIN
  *         @arg @ref MS32_COMP_NEG_CRV
  * @retval None
  */
__STATIC_INLINE void MS32_CMP2_SetNegitiveInput(uint32_t NegInput) {
  MODIFY_REG(CMP_OP->CP2CR, CMP_CPxCR_CPxNSEL, NegInput);
}

/**
  * @brief  Get the negitive input by the Comparision 2
  * @rmtoll CP2CR           CP2NSEL        MS32_CMP2_GetPostiveInput
  * @param  None
  * @retval This parameter can be one of the following values:
  *         @arg @ref MS32_COMP_NEG_PIN
  *         @arg @ref MS32_COMP_NEG_CRV
  */
__STATIC_INLINE uint32_t MS32_CMP2_GetNegitiveInput(void) {
  return (CMP_OP->CP2CR & CMP_CPxCR_CPxNSEL);
}

/**
  * @brief  Select the VREF voltage by the Comparision 1
  * @rmtoll CP1CR           CP1VERFSEL        MS32_CMP1_SetVrefVoltage
  * @param  VrefVolt This parameter can be one of the following values:
  *         @arg @ref MS32_COMP_CRV_1_DIV_8
  *         @arg @ref MS32_COMP_CRV_2_DIV_8
  *         @arg @ref MS32_COMP_CRV_3_DIV_8
  *         @arg @ref MS32_COMP_CRV_4_DIV_8
  *         @arg @ref MS32_COMP_CRV_5_DIV_8
  *         @arg @ref MS32_COMP_CRV_6_DIV_8
  *         @arg @ref MS32_COMP_CRV_7_DIV_8
  *         @arg @ref MS32_COMP_CRV_8_DIV_8
  * @retval None
  */
__STATIC_INLINE void MS32_CMP1_SetVrefVoltage(uint32_t VrefVolt) {
  MODIFY_REG(CMP_OP->CP1CR, CMP_CPxCR_CPxRVSEL, VrefVolt);
}

/**
  * @brief  Get the VREF voltage by the Comparision 1
  * @rmtoll CP1CR           CP1VERFSEL        MS32_CMP1_GetVrefVoltage
  * @param  None
  * @retval This parameter can be one of the following values:
  *         @arg @ref MS32_COMP_CRV_1_DIV_8
  *         @arg @ref MS32_COMP_CRV_2_DIV_8
  *         @arg @ref MS32_COMP_CRV_3_DIV_8
  *         @arg @ref MS32_COMP_CRV_4_DIV_8
  *         @arg @ref MS32_COMP_CRV_5_DIV_8
  *         @arg @ref MS32_COMP_CRV_6_DIV_8
  *         @arg @ref MS32_COMP_CRV_7_DIV_8
  *         @arg @ref MS32_COMP_CRV_8_DIV_8
  */
__STATIC_INLINE uint32_t MS32_CMP1_GetVrefVoltage(void) {
  return (CMP_OP->CP1CR & CMP_CPxCR_CPxRVSEL);
}

/**
  * @brief  Select the VREF voltage by the Comparision 2
  * @rmtoll CP2CR           CP2VERFSEL        MS32_CMP2_SetVrefVoltage
  * @param  VrefVolt This parameter can be one of the following values:
  *         @arg @ref MS32_COMP_CRV_1_DIV_8
  *         @arg @ref MS32_COMP_CRV_2_DIV_8
  *         @arg @ref MS32_COMP_CRV_3_DIV_8
  *         @arg @ref MS32_COMP_CRV_4_DIV_8
  *         @arg @ref MS32_COMP_CRV_5_DIV_8
  *         @arg @ref MS32_COMP_CRV_6_DIV_8
  *         @arg @ref MS32_COMP_CRV_7_DIV_8
  *         @arg @ref MS32_COMP_CRV_8_DIV_8
  * @retval None
  */
__STATIC_INLINE void MS32_CMP2_SetVrefVoltage(uint32_t VrefVolt) {
  MODIFY_REG(CMP_OP->CP2CR, CMP_CPxCR_CPxRVSEL, VrefVolt);
}

/**
  * @brief  Get the VREF voltage by the Comparision 2
  * @rmtoll CP2CR           CP2VERFSEL        MS32_CMP2_GetVrefVoltage
  * @param  None
  * @retval This parameter can be one of the following values:
  *         @arg @ref MS32_COMP_CRV_1_DIV_8
  *         @arg @ref MS32_COMP_CRV_2_DIV_8
  *         @arg @ref MS32_COMP_CRV_3_DIV_8
  *         @arg @ref MS32_COMP_CRV_4_DIV_8
  *         @arg @ref MS32_COMP_CRV_5_DIV_8
  *         @arg @ref MS32_COMP_CRV_6_DIV_8
  *         @arg @ref MS32_COMP_CRV_7_DIV_8
  *         @arg @ref MS32_COMP_CRV_8_DIV_8
  */
__STATIC_INLINE uint32_t MS32_CMP2_GetVrefVoltage(void) {
  return (CMP_OP->CP2CR & CMP_CPxCR_CPxRVSEL);
}

/**
  * @brief  Select the output filter by the Comparision 1
  * @rmtoll CP1CR           CP1OFLT        MS32_CMP1_SetOutputFilter
  * @param  OutFilt This parameter can be one of the following values:
  *         @arg @ref MS32_COMP_OUT_FILTER_CLK1  
  *         @arg @ref MS32_COMP_OUT_FILTER_CLK4  
  *         @arg @ref MS32_COMP_OUT_FILTER_CLK16 
  *         @arg @ref MS32_COMP_OUT_FILTER_CLK32 
  *         @arg @ref MS32_COMP_OUT_FILTER_CLK64 
  *         @arg @ref MS32_COMP_OUT_FILTER_CLK128
  *         @arg @ref MS32_COMP_OUT_FILTER_CLK256
  *         @arg @ref MS32_COMP_OUT_FILTER_CLK512
  * @retval None
  */
__STATIC_INLINE void MS32_CMP1_SetOutputFilter(uint32_t OutFilt) {
  MODIFY_REG(CMP_OP->CP1CR, CMP_CPxCR_CPxOFLT, OutFilt);
}

/**
  * @brief  Get the output filter by the Comparision 1
  * @rmtoll CP1CR           CP1OFLT        MS32_CMP1_GetOutputFilter
  * @param  None
  * @retval This parameter can be one of the following values:
  *         @arg @ref MS32_COMP_OUT_FILTER_CLK1  
  *         @arg @ref MS32_COMP_OUT_FILTER_CLK4  
  *         @arg @ref MS32_COMP_OUT_FILTER_CLK16 
  *         @arg @ref MS32_COMP_OUT_FILTER_CLK32 
  *         @arg @ref MS32_COMP_OUT_FILTER_CLK64 
  *         @arg @ref MS32_COMP_OUT_FILTER_CLK128
  *         @arg @ref MS32_COMP_OUT_FILTER_CLK256
  *         @arg @ref MS32_COMP_OUT_FILTER_CLK512
  */
__STATIC_INLINE uint32_t MS32_CMP1_GetOutputFilter(void) {
  return (CMP_OP->CP1CR & CMP_CPxCR_CPxOFLT);
}

/**
  * @brief  Select the output filter by the Comparision 2
  * @rmtoll CP2CR           CP2OFLT        MS32_CMP2_SetOutputFilter
  * @param  OutFilt This parameter can be one of the following values:
  *         @arg @ref MS32_COMP_OUT_FILTER_CLK1  
  *         @arg @ref MS32_COMP_OUT_FILTER_CLK4  
  *         @arg @ref MS32_COMP_OUT_FILTER_CLK16 
  *         @arg @ref MS32_COMP_OUT_FILTER_CLK32 
  *         @arg @ref MS32_COMP_OUT_FILTER_CLK64 
  *         @arg @ref MS32_COMP_OUT_FILTER_CLK128
  *         @arg @ref MS32_COMP_OUT_FILTER_CLK256
  *         @arg @ref MS32_COMP_OUT_FILTER_CLK512
  * @retval None
  */
__STATIC_INLINE void MS32_CMP2_SetOutputFilter(uint32_t OutFilt) {
  MODIFY_REG(CMP_OP->CP2CR, CMP_CPxCR_CPxOFLT, OutFilt);
}

/**
  * @brief  Get the output filter by the Comparision 2
  * @rmtoll CP2CR           CP2OFLT        MS32_CMP2_GetOutputFilter
  * @param  None
  * @retval This parameter can be one of the following values:
  *         @arg @ref MS32_COMP_OUT_FILTER_CLK1  
  *         @arg @ref MS32_COMP_OUT_FILTER_CLK4  
  *         @arg @ref MS32_COMP_OUT_FILTER_CLK16 
  *         @arg @ref MS32_COMP_OUT_FILTER_CLK32 
  *         @arg @ref MS32_COMP_OUT_FILTER_CLK64 
  *         @arg @ref MS32_COMP_OUT_FILTER_CLK128
  *         @arg @ref MS32_COMP_OUT_FILTER_CLK256
  *         @arg @ref MS32_COMP_OUT_FILTER_CLK512
  */
__STATIC_INLINE uint32_t MS32_CMP2_GetOutputFilter(void) {
  return (CMP_OP->CP2CR & CMP_CPxCR_CPxOFLT);
}

/**
  * @brief  Select the output polarity by the Comparision 1
  * @rmtoll CP1CR           CP1POL        MS32_CMP1_SetOutputPol
  * @param  OutPol This parameter can be one of the following values:
  *         @arg @ref MS32_COMP_OUT_POL_POS
  *         @arg @ref MS32_COMP_OUT_POL_NEG
  * @retval None
  */
__STATIC_INLINE void MS32_CMP1_SetOutputPol(uint32_t OutPol) {
  MODIFY_REG(CMP_OP->CP1CR, CMP_CPxCR_CPxPOL, OutPol);
}

/**
  * @brief  Get the output polarity by the Comparision 1
  * @rmtoll CP1CR           CP1POL        MS32_CMP1_GetOutputPol
  * @param  None
  * @retval This parameter can be one of the following values:
  *         @arg @ref MS32_COMP_OUT_POL_POS
  *         @arg @ref MS32_COMP_OUT_POL_NEG
  */
__STATIC_INLINE uint32_t MS32_CMP1_GetOutputPol(void) {
  return (CMP_OP->CP1CR & CMP_CPxCR_CPxPOL);
}

/**
  * @brief  Select the output polarity by the Comparision 2
  * @rmtoll CP2CR           CP2POL        MS32_CMP2_SetOutputPol
  * @param  OutPol This parameter can be one of the following values:
  *         @arg @ref MS32_COMP_OUT_POL_POS
  *         @arg @ref MS32_COMP_OUT_POL_NEG
  * @retval None
  */
__STATIC_INLINE void MS32_CMP2_SetOutputPol(uint32_t OutPol) {
  MODIFY_REG(CMP_OP->CP2CR, CMP_CPxCR_CPxPOL, OutPol);
}

/**
  * @brief  Get the output polarity by the Comparision 2
  * @rmtoll CP2CR           CP2POL        MS32_CMP2_GetOutputPol
  * @param  None
  * @retval This parameter can be one of the following values:
  *         @arg @ref MS32_COMP_OUT_POL_POS
  *         @arg @ref MS32_COMP_OUT_POL_NEG
  */
__STATIC_INLINE uint32_t MS32_CMP2_GetOutputPol(void) {
  return (CMP_OP->CP2CR & CMP_CPxCR_CPxPOL);
}

/**
  * @brief  Select the inline output by the Comparision 1
  * @rmtoll CP1CR           CP1OUTSEL        MS32_CMP1_SetInlineOutput
  * @param  OutFilt This parameter can be one of the following values:
  *         @arg @ref MS32_COMP_OUT_TIM1_BKIN     
  *         @arg @ref MS32_COMP_OUT_TIM1_OCREF_CLR
  *         @arg @ref MS32_COMP_OUT_TIM1_IC1      
  *         @arg @ref MS32_COMP_OUT_TIM2_IC4      
  *         @arg @ref MS32_COMP_OUT_TIM2_OCREF_CLR
  *         @arg @ref MS32_COMP_OUT_TIM3_IC1      
  *         @arg @ref MS32_COMP_OUT_TIM3_OCREF_CLR
  * @retval None
  */
__STATIC_INLINE void MS32_CMP1_SetInlineOutput(uint32_t OutFilt) {
  MODIFY_REG(CMP_OP->CP1CR, CMP_CPxCR_CPxOUTSEL, OutFilt);
}

/**
  * @brief  Get the inline output by the Comparision 1
  * @rmtoll CP1CR           CP1OUTSEL        MS32_CMP1_GetInlineOutput
  * @param  None
  * @retval This parameter can be one of the following values:
  *         @arg @ref MS32_COMP_OUT_TIM1_BKIN     
  *         @arg @ref MS32_COMP_OUT_TIM1_OCREF_CLR
  *         @arg @ref MS32_COMP_OUT_TIM1_IC1      
  *         @arg @ref MS32_COMP_OUT_TIM2_IC4      
  *         @arg @ref MS32_COMP_OUT_TIM2_OCREF_CLR
  *         @arg @ref MS32_COMP_OUT_TIM3_IC1      
  *         @arg @ref MS32_COMP_OUT_TIM3_OCREF_CLR
  */
__STATIC_INLINE uint32_t MS32_CMP1_GetInlineOutput(void) {
  return (CMP_OP->CP1CR & CMP_CPxCR_CPxOUTSEL);
}

/**
  * @brief  Select the inline output by the Comparision 2
  * @rmtoll CP2CR           CP2OUTSEL        MS32_CMP2_SetInlineOutput
  * @param  OutFilt This parameter can be one of the following values:
  *         @arg @ref MS32_COMP_OUT_TIM1_BKIN     
  *         @arg @ref MS32_COMP_OUT_TIM1_OCREF_CLR
  *         @arg @ref MS32_COMP_OUT_TIM1_IC1      
  *         @arg @ref MS32_COMP_OUT_TIM2_IC4      
  *         @arg @ref MS32_COMP_OUT_TIM2_OCREF_CLR
  *         @arg @ref MS32_COMP_OUT_TIM3_IC1      
  *         @arg @ref MS32_COMP_OUT_TIM3_OCREF_CLR
  * @retval None
  */
__STATIC_INLINE void MS32_CMP2_SetInlineOutput(uint32_t OutFilt) {
  MODIFY_REG(CMP_OP->CP2CR, CMP_CPxCR_CPxOUTSEL, OutFilt);
}

/**
  * @brief  Get the inline output by the Comparision 2
  * @rmtoll CP2CR           CP2OUTSEL        MS32_CMP2_GetInlineOutput
  * @param  None
  * @retval This parameter can be one of the following values:
  *         @arg @ref MS32_COMP_OUT_TIM1_BKIN     
  *         @arg @ref MS32_COMP_OUT_TIM1_OCREF_CLR
  *         @arg @ref MS32_COMP_OUT_TIM1_IC1      
  *         @arg @ref MS32_COMP_OUT_TIM2_IC4      
  *         @arg @ref MS32_COMP_OUT_TIM2_OCREF_CLR
  *         @arg @ref MS32_COMP_OUT_TIM3_IC1      
  *         @arg @ref MS32_COMP_OUT_TIM3_OCREF_CLR
  */
__STATIC_INLINE uint32_t MS32_CMP2_GetInlineOutput(void) {
  return (CMP_OP->CP2CR & CMP_CPxCR_CPxOUTSEL);
}

/**
  * @brief  Get the output value by the Comparision 1
  * @rmtoll CP1CR           CP1OUT        MS32_CMP1_GetOutputValue
  * @param  None
  * @retval This parameter can be one of the following values:
  *         @arg @ref MS32_COMP_OUTPUT_LOW  
  *         @arg @ref MS32_COMP_OUTPUT_HIGH 
  */
__STATIC_INLINE uint32_t MS32_CMP1_GetOutputValue(void) {
  return (CMP_OP->CP1CR & CMP_CPxCR_CPxOUT);
}

/**
  * @brief  Get the output value by the Comparision 2
  * @rmtoll CP2CR           CP2OUT        MS32_CMP2_GetOutputValue
  * @param  None
  * @retval This parameter can be one of the following values:
  *         @arg @ref MS32_COMP_OUTPUT_LOW  
  *         @arg @ref MS32_COMP_OUTPUT_HIGH 
  */
__STATIC_INLINE uint32_t MS32_CMP2_GetOutputValue(void) {
  return (CMP_OP->CP2CR & CMP_CPxCR_CPxOUT);
}

/**
  * @brief  Lock the Comparision 1
  * @rmtoll CP1CR           CP1LCK        MS32_CMP1_Lock
  * @param  None
  * @retval None
  */
__STATIC_INLINE void MS32_CMP1_Lock(void) {
  SET_BIT(CMP_OP->CP1CR, CMP_CPxCR_CPxLCK);
}

/**
  * @brief  Get the output value by the Comparision 1
  * @rmtoll CP1CR           CP1LCK        MS32_CMP1_GetLock
  * @param  None
  * @retval This parameter can be one of the following values:
  *         @arg @ref MS32_COMP_UNLOCK 
  *         @arg @ref MS32_COMP_LOCK   
  */
__STATIC_INLINE uint32_t MS32_CMP1_GetLock(void) {
  return (CMP_OP->CP1CR & CMP_CPxCR_CPxLCK);
}

/**
  * @brief  Lock the Comparision 2
  * @rmtoll CP2CR           CP2LCK        MS32_CMP2_Lock
  * @param  None
  * @retval None
  */
__STATIC_INLINE void MS32_CMP2_Lock(void) {
  SET_BIT(CMP_OP->CP2CR, CMP_CPxCR_CPxLCK);
}

/**
  * @brief  Get the output value by the Comparision 2
  * @rmtoll CP2CR           CP2LCK        MS32_CMP2_GetLock
  * @param  None
  * @retval This parameter can be one of the following values:
  *         @arg @ref MS32_COMP_UNLOCK
  *         @arg @ref MS32_COMP_LOCK  
  */
__STATIC_INLINE uint32_t MS32_CMP2_GetLock(void) {
  return (CMP_OP->CP2CR & CMP_CPxCR_CPxLCK);
}


/** @defgroup COMP_EF_Init Initialization and de-initialization functions
  * @{
  */
ErrorStatus MS32_CMP_DeInit     (uint32_t CmpUnit);
void        MS32_CMP_StructInit (MS32_CMP_InitTypeDef *CmpInitStr);
ErrorStatus MS32_CMP_Init       (uint32_t CmpUnit, MS32_CMP_InitTypeDef *CmpInitStr);
void        MS32_CMP_ITConfig   (uint32_t InterruptFunc, uint32_t Priority);

/** @defgroup COMP_EF_Application function
  * @{
  */
FlagStatus  MS32_CMP_GetOutputStatus (uint32_t CmpUnit);
ErrorStatus MS32_CMP_GetCaliValue    (uint32_t CmpUnit, MS32_CMP_CaliTypeDef *CmpCaliStr);
ErrorStatus MS32_CMP_SetCaliValue    (uint32_t CmpUnit, MS32_CMP_CaliTypeDef *CmpCaliStr);


#ifdef __cplusplus
}
#endif

#endif /* __MS32F0XX_COMP_H */

/******************************** END OF FILE *********************************/
