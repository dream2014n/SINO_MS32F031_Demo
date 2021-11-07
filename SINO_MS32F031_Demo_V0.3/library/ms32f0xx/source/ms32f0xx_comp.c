/* Includes ------------------------------------------------------------------*/
#include "ms32f0xx_comp.h"


/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
#define VREF_ANALOG_WAIT     4800   /* 100 / (1 / 48) */

/* Private macros ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @addtogroup COMP_EF_Init
  * @{
  */

/**
  * @brief  De-initialize the CMP registers to their default reset values.
  * @param  CmpUnit This parameter can be one of the following values:
  *            @arg @ref MS32_COMP1     comparison 1 unit
  *            @arg @ref MS32_COMP2     comparison 2 unit
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: CMP registers are de-initialized
  *          - ERROR: CMP registers aren't de-initialized
  */
ErrorStatus MS32_CMP_DeInit(uint32_t CmpUnit) {
  ErrorStatus status = SUCCESS;

  /* Enable clock */
  MS32_APB1_GRP2_EnableClock(MS32_APB1_GRP2_PERIPH_SYSCFG);

  switch (CmpUnit) {
    /* comparison 1 */
    case MS32_COMP1:
      /* CP1CR set to default reset values */
      MS32_CMP_WriteReg(CP1CR,  0x00000180U);
      /* CP1CAL set to default reset values */
      MS32_CMP_WriteReg(CP1CAL, 0x00000000U);
      /* CPANA set to default reset values */
      MS32_CMP_WriteReg(CPANA,  0x00000000U);
      break;
    /* comparison 2 */
    case MS32_COMP2:
      /* CP2CR set to default reset values */
      MS32_CMP_WriteReg(CP2CR,  0x00000180U);
      /* CP2CAL set to default reset values */
      MS32_CMP_WriteReg(CP2CAL, 0x00000000U);
      /* CPANA set to default reset values */
      MS32_CMP_WriteReg(CPANA,  0x00000000U);
      break;
    default:
      status = ERROR;
      break;
  }

  return status;
}

/**
  * @brief Set each @ref MS32_CMP_InitTypeDef field to default value.
  * @param CmpInitStr  pointer to a @ref MS32_CMP_InitTypeDef structure
  *                          whose fields will be set to default values.
  * @retval None
  */
void MS32_CMP_StructInit(MS32_CMP_InitTypeDef *CmpInitStr) {
  /* Reset CMP init structure parameters values */
  CmpInitStr->Lock           = MS32_COMP_UNLOCK;
  CmpInitStr->OutputSel      = MS32_COMP_OUT_TIM1_BKIN;
  CmpInitStr->OutputPolarity = MS32_COMP_OUT_POL_POS;
  CmpInitStr->OutputFilter   = MS32_COMP_OUT_FILTER_CLK1;
  CmpInitStr->CrvSel         = MS32_COMP_CRV_AVDD;
  CmpInitStr->CrvDivSel      = MS32_COMP_CRV_1_DIV_8;
  CmpInitStr->NegativeSel    = MS32_COMP_NEG_PIN;
  CmpInitStr->PositionSel    = MS32_COMP_POS_CPxP_PIN;
  CmpInitStr->HysteresisSel  = MS32_COMP_HYST_0MV;
}

/**
  * @brief  Initialize the CMP according to the specified
  *         parameters in the MS32_CMP_InitTypeDef and create the associated handle.
  * @param  CmpUnit This parameter can be one of the following values:
  *            @arg @ref MS32_COMP1  comparison 1 unit
  *            @arg @ref MS32_COMP2  comparison 2 unit
  * @param  CmpInitStr  pointer to a MS32_CMP_InitTypeDef structure that contains
  *                the configuration information for the specified CMP module.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: CMP registers are initialized
  *          - ERROR: not applicable
  */
ErrorStatus MS32_CMP_Init(uint32_t CmpUnit, MS32_CMP_InitTypeDef *CmpInitStr) {
  ErrorStatus   status = SUCCESS;
  uint32_t      reg_val = 0;
  __IO uint32_t delay_cnt;

  /* Enable clock */
  MS32_APB1_GRP2_EnableClock(MS32_APB1_GRP2_PERIPH_SYSCFG);

  switch (CmpUnit) {
    /* comparison 1 config */
    case MS32_COMP1:
      /* enable/disable vref and select voltage reference */
      if (CmpInitStr->CrvSel == MS32_COMP_CRV_VREF) {
        SET_BIT(CMP_OP->CPANA, CMP_CPANA_CPVREFEN);
        SET_BIT(CMP_OP->CPANA, CMP_CPANA_CP1VOLT);
        delay_cnt = VREF_ANALOG_WAIT;
        while (delay_cnt--);
      } else {
        CLEAR_BIT(CMP_OP->CPANA, CMP_CPANA_CP1VOLT);
      }
      /* auto calibration comparison 1 */
      MS32_CMP1_Disable();
      SET_BIT(CMP_OP->CP1CAL, CMP_CPxCAL_CPxCALEN);
      while (READ_BIT(CMP_OP->CP1CAL, CMP_CPxCAL_CPxCALEN));
      /* set comparison 1 */
      reg_val = CmpInitStr->Lock      | CmpInitStr->OutputSel   | CmpInitStr->OutputPolarity | CmpInitStr->OutputFilter |\
                CmpInitStr->CrvDivSel | CmpInitStr->NegativeSel | CmpInitStr->PositionSel    | CmpInitStr->HysteresisSel;
      MODIFY_REG(CMP_OP->CP1CR, (CMP_CPxCR_CPxLCK   | CMP_CPxCR_CPxOUTSEL | CMP_CPxCR_CPxPOL  | CMP_CPxCR_CPxOFLT |\
                                 CMP_CPxCR_CPxRVSEL | CMP_CPxCR_CPxNSEL   | CMP_CPxCR_CPxPSEL | CMP_CPxCR_CPxHYST), reg_val);
      MS32_CMP1_Enable();
      break;
    /* comparison 2 config */
    case MS32_COMP2:
      /* enable/disable vref and select voltage reference */
      if (CmpInitStr->CrvSel == MS32_COMP_CRV_VREF) {
        SET_BIT(CMP_OP->CPANA, CMP_CPANA_CPVREFEN);
        SET_BIT(CMP_OP->CPANA, CMP_CPANA_CP2VOLT);
        delay_cnt = VREF_ANALOG_WAIT;
        while (delay_cnt--);
      } else {
        CLEAR_BIT(CMP_OP->CPANA, CMP_CPANA_CP2VOLT);
      }
      /* auto calibration comparison 2 */
      MS32_CMP2_Disable();
      SET_BIT(CMP_OP->CP2CAL, CMP_CPxCAL_CPxCALEN);
      while (READ_BIT(CMP_OP->CP2CAL, CMP_CPxCAL_CPxCALEN));
      /* set comparison 2 */
      if (CmpInitStr->PositionSel <= MS32_COMP_POS_CPx3P_PIN) {
        reg_val = MS32_COMP_POS_CPxP_PIN;
      } else {
        reg_val = CmpInitStr->PositionSel - 2;
      }
      reg_val |= (CmpInitStr->Lock      | CmpInitStr->OutputSel   | CmpInitStr->OutputPolarity | CmpInitStr->OutputFilter |\
                  CmpInitStr->CrvDivSel | CmpInitStr->NegativeSel | CmpInitStr->HysteresisSel);
      MODIFY_REG(CMP_OP->CP2CR, (CMP_CPxCR_CPxLCK   | CMP_CPxCR_CPxOUTSEL | CMP_CPxCR_CPxPOL  | CMP_CPxCR_CPxOFLT |\
                                 CMP_CPxCR_CPxRVSEL | CMP_CPxCR_CPxNSEL   | CMP_CPxCR_CPxHYST), reg_val);
      MS32_CMP2_Enable();
      break;
    default:
      status = ERROR;
      break;
  }

  /* Return function status */
  return status;
}

/**
  * @brief  Initializes the CMP1/2 interrupt according to the specified parameters.
  * @param  InterruptFunc  contains the configuration information for the CMP1/2 interrupt.
  *         This parameter can be one or more of the following values:
  *         @arg @ref MS32_COMP_IT_DISABLE  COMP interrupt disable
  *         @arg @ref MS32_COMP_IT_ENABLE   COMP interrupt enable
  * @param  Priority  the interrupt priority 
  *         This parameter can be a value of 0x0~0x3
  * @retval None
  */
void MS32_CMP_ITConfig(uint32_t InterruptFunc, uint32_t Priority) {
  /*----------------------------- NVIC configuration -------------------------*/
  if (InterruptFunc == MS32_COMP_IT_ENABLE) {
    NVIC_EnableIRQ(ADC1_COMP_IRQn);
    NVIC_SetPriority(ADC1_COMP_IRQn, Priority);
  } else {
    NVIC_DisableIRQ(ADC1_COMP_IRQn);
  }
}

/**
  * @brief  Get the CMP output level according to the internal CMP CR registers.
  * @param  CmpUnit This parameter can be one of the following values:
  *            @arg @ref MS32_COMP1  comparison 1 unit
  *            @arg @ref MS32_COMP2  comparison 2 unit 
  * @retval A FlagStatus enumeration value:
  *          - SET:   flag set(equal to "1")
  *          - RESET: flag no set(equal to "0")
  */
FlagStatus MS32_CMP_GetOutputStatus(uint32_t CmpUnit) {
  FlagStatus flags;

  if (((CmpUnit == MS32_COMP1) && READ_BIT(CMP_OP->CP1CR, CMP_CPxCR_CPxOUT)) || \
      ((CmpUnit == MS32_COMP2) && READ_BIT(CMP_OP->CP2CR, CMP_CPxCR_CPxOUT))) {
    flags = SET;
  } else {
    flags = RESET;
  }

  return flags;
}

/**
  * @brief  Get the CMP calibration value according to the internal CPxCAL registers.
  * @param  CmpUnit This parameter can be one of the following values:
  *            @arg @ref MS32_COMP1  comparison 1 unit
  *            @arg @ref MS32_COMP2  comparison 2 unit 
  * @param  CmpCaliStr  pointer to a MS32_CMP_CaliTypeDef structure that contains
  *                the calibration information for the specified CMP module.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: CMP calibration are success
  *          - ERROR: CMP calibration are fail
  */
ErrorStatus MS32_CMP_GetCaliValue(uint32_t CmpUnit, MS32_CMP_CaliTypeDef *CmpCaliStr) {
  ErrorStatus status = SUCCESS;

  switch (CmpUnit) {
    /* comparison 1 */
    case MS32_COMP1:
      CmpCaliStr->CmpPosCaliData = READ_BIT(CMP_OP->CP1CAL, CMP_CPxCAL_CPxCALDATP) >> CMP_CPxCAL_CPxCALDATP_Pos;
      CmpCaliStr->CmpNegCaliData = READ_BIT(CMP_OP->CP1CAL, CMP_CPxCAL_CPxCALDATN);
      break;
    /* comparison 2 */
    case MS32_COMP2:
      CmpCaliStr->CmpPosCaliData = READ_BIT(CMP_OP->CP2CAL, CMP_CPxCAL_CPxCALDATP) >> CMP_CPxCAL_CPxCALDATP_Pos;
      CmpCaliStr->CmpNegCaliData = READ_BIT(CMP_OP->CP2CAL, CMP_CPxCAL_CPxCALDATN);
      break;
    default:
      status = ERROR;
      break;
  }

  return status;
}

/**
  * @brief  Set the CMP calibration value according to the internal CPxCAL registers.
  * @param  CmpUnit This parameter can be one of the following values:
  *            @arg @ref MS32_COMP1  comparison 1 unit
  *            @arg @ref MS32_COMP2  comparison 2 unit 
  * @param  CmpCaliStr  pointer to a MS32_CMP_CaliTypeDef structure that contains
  *                the calibration information for the specified CMP module.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: CMP calibration are success
  *          - ERROR: CMP calibration are fail
  */
ErrorStatus MS32_CMP_SetCaliValue(uint32_t CmpUnit, MS32_CMP_CaliTypeDef *CmpCaliStr) {
  ErrorStatus status = SUCCESS;

  /* Enable clock */
  MS32_APB1_GRP2_EnableClock(MS32_APB1_GRP2_PERIPH_SYSCFG);

  switch (CmpUnit) {
    /* comparison 1 */
    case MS32_COMP1:
      MODIFY_REG(CMP_OP->CP1CAL, CMP_CPxCAL_CPxCALDATP, ((uint32_t)CmpCaliStr->CmpPosCaliData << CMP_CPxCAL_CPxCALDATP_Pos));
      while (READ_BIT(CMP_OP->CP1CAL, CMP_CPxCAL_CPxSYNC));
      MODIFY_REG(CMP_OP->CP1CAL, CMP_CPxCAL_CPxCALDATN, (uint32_t)CmpCaliStr->CmpNegCaliData);
      while (READ_BIT(CMP_OP->CP1CAL, CMP_CPxCAL_CPxSYNC));
      break;
    /* comparison 2 */
    case MS32_COMP2:
      MODIFY_REG(CMP_OP->CP2CAL, CMP_CPxCAL_CPxCALDATP, ((uint32_t)CmpCaliStr->CmpPosCaliData << CMP_CPxCAL_CPxCALDATP_Pos));
      while (READ_BIT(CMP_OP->CP2CAL, CMP_CPxCAL_CPxSYNC));
      MODIFY_REG(CMP_OP->CP2CAL, CMP_CPxCAL_CPxCALDATN, (uint32_t)CmpCaliStr->CmpNegCaliData);
      while (READ_BIT(CMP_OP->CP2CAL, CMP_CPxCAL_CPxSYNC));
      break;
    default:
      status = ERROR;
      break;
  }

  return status;
}


/******************************** END OF FILE *********************************/

