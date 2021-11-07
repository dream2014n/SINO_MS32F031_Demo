/* Includes ------------------------------------------------------------------*/
#include "ms32f0xx_opamp.h"


/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @addtogroup OP_EF_Init
  * @{
  */

/**
  * @brief  De-initialize the OP registers to their default reset values.
  * @param  OpUnit This parameter can be one of the following values:
  *            @arg @ref MS32_OP1     1peration 1 unit
  *            @arg @ref MS32_OP2     1peration 2 unit
  *            @arg @ref MS32_OP3     1peration 3 unit
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: OP registers are de-initialized
  *          - ERROR: OP registers aren't de-initialized
  */
ErrorStatus MS32_OP_DeInit(uint32_t OpUnit) {
  ErrorStatus status = SUCCESS;

  /* Enable clock */
  MS32_APB1_GRP2_EnableClock(MS32_APB1_GRP2_PERIPH_SYSCFG);

  switch (OpUnit) {
    /* Operation 1 */
    case MS32_OP1:
      /* OP1 set to default reset values */
      CLEAR_BIT(CMP_OP->OPCR,  (OPAMP_OPCR_OPAMP1OUTEN | OPAMP_OPCR_OPAMP1GAIN | OPAMP_OPCR_OPAMP1NSEL | OPAMP_OPCR_OPAMP1EN));
      /* OP1CAL set to default reset values */
      MS32_OP_WriteReg(OP1CAL, 0x00002020);
      break;
    /* Operation 2 */
    case MS32_OP2:
      /* OP2 set to default reset values */
      CLEAR_BIT(CMP_OP->OPCR,  (OPAMP_OPCR_OPAMP2OUTEN | OPAMP_OPCR_OPAMP2GAIN | OPAMP_OPCR_OPAMP2NSEL | OPAMP_OPCR_OPAMP2EN));
      /* OP2CAL set to default reset values */
      MS32_OP_WriteReg(OP2CAL, 0x00002020);
      break;
    /* Operation 3 */
    case MS32_OP3:
      /* OP3 set to default reset values */
      CLEAR_BIT(CMP_OP->OPCR,  (OPAMP_OPCR_OPAMP3OUTEN | OPAMP_OPCR_OPAMP3GAIN | OPAMP_OPCR_OPAMP3NSEL | OPAMP_OPCR_OPAMP3EN));
      /* OP3CAL set to default reset values */
      MS32_OP_WriteReg(OP3CAL, 0x00002020);
      break;
    default:
      status = ERROR;
      break;
  }

  return status;
}

/**
  * @brief Set each @ref MS32_OP_InitTypeDef field to default value.
  * @param OpInitStr  pointer to a @ref MS32_OP_InitTypeDef structure
  *                          whose fields will be set to default values.
  * @retval None
  */
void MS32_OP_StructInit(MS32_OP_InitTypeDef *OpInitStr) {
  /* Reset OP init structure parameters values */
  OpInitStr->OutputEn         = MS32_OP_OUT_DIS;
  OpInitStr->GAIN             = MS32_OP_GAIN2;
  OpInitStr->NegitiveInputSel = MS32_OP_NEGINPUT_PIN;
}

/**
  * @brief  Initialize the OP according to the specified
  *         parameters in the MS32_OP_InitTypeDef and create the associated handle.
  * @param  OpUnit This parameter can be one of the following values:
  *            @arg @ref MS32_OP1     Operation 1 unit
  *            @arg @ref MS32_OP2     Operation 2 unit
  *            @arg @ref MS32_OP3     Operation 3 unit
  * @param  OpInitStr  pointer to a MS32_OP_InitTypeDef structure that contains
  *                the configuration information for the specified OP module.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: OP registers are initialized
  *          - ERROR: not applicable
  */
ErrorStatus MS32_OP_Init(uint32_t OpUnit, MS32_OP_InitTypeDef *OpInitStr) {
  ErrorStatus   status = SUCCESS;
  uint32_t      reg_val = 0;

  /* Enable clock */
  MS32_APB1_GRP2_EnableClock(MS32_APB1_GRP2_PERIPH_SYSCFG);

  switch (OpUnit) {
    /* Operation 1 */
    case MS32_OP1:
      /* auto calibration operation 1 */
      MS32_OP1_Disable();
      SET_BIT(CMP_OP->OP1CAL, OPAMP_OPxCAL_OPxCALEN);
      while (READ_BIT(CMP_OP->OP1CAL, OPAMP_OPxCAL_OPxCALEN));
      /* set operation 1 */
      reg_val = (OpInitStr->OutputEn | OpInitStr->GAIN | OpInitStr->NegitiveInputSel);
      MODIFY_REG(CMP_OP->OPCR, (OPAMP_OPCR_OPAMP1OUTEN | OPAMP_OPCR_OPAMP1GAIN | OPAMP_OPCR_OPAMP1NSEL), reg_val);
      MS32_OP1_Enable();
      break;
    /* Operation 2 */
    case MS32_OP2:
      /* auto calibration operation 2 */
      MS32_OP2_Disable();
      SET_BIT(CMP_OP->OP2CAL, OPAMP_OPxCAL_OPxCALEN);
      while (READ_BIT(CMP_OP->OP2CAL, OPAMP_OPxCAL_OPxCALEN));
      /* set operation 2 */
      reg_val = (OpInitStr->OutputEn | OpInitStr->GAIN | OpInitStr->NegitiveInputSel);
      MODIFY_REG(CMP_OP->OPCR, (OPAMP_OPCR_OPAMP2OUTEN | OPAMP_OPCR_OPAMP2GAIN | OPAMP_OPCR_OPAMP2NSEL), reg_val << (OPAMP_OPCR_OPAMP2EN_Pos - OPAMP_OPCR_OPAMP1EN_Pos));
      MS32_OP2_Enable();
      break;
    /* Operation 3 */
    case MS32_OP3:
      /* auto calibration operation 3 */
      MS32_OP3_Disable();
      SET_BIT(CMP_OP->OP3CAL, OPAMP_OPxCAL_OPxCALEN);
      while (READ_BIT(CMP_OP->OP3CAL, OPAMP_OPxCAL_OPxCALEN));
      /* set operation 3 */
      reg_val = (OpInitStr->OutputEn | OpInitStr->GAIN | OpInitStr->NegitiveInputSel);
      MODIFY_REG(CMP_OP->OPCR, (OPAMP_OPCR_OPAMP3OUTEN | OPAMP_OPCR_OPAMP3GAIN | OPAMP_OPCR_OPAMP3NSEL), reg_val << (OPAMP_OPCR_OPAMP3EN_Pos - OPAMP_OPCR_OPAMP1EN_Pos));
      MS32_OP3_Enable();
      break;
    default:
      status = ERROR;
      break;
  }

  /* Return function status */
  return status;
}

/**
  * @brief  Get the OP calibration value according to the internal OPxCAL registers.
  * @param  OpUnit This parameter can be one of the following values:
  *            @arg @ref MS32_OP1     Operation 1 unit
  *            @arg @ref MS32_OP2     Operation 2 unit
  *            @arg @ref MS32_OP3     Operation 3 unit 
  * @param  OpInitStr  pointer to a MS32_OP_CaliTypeDef structure that contains
  *                the configuration information for the specified OP module.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: OP calibration are success
  *          - ERROR: OP calibration are fail
  */
ErrorStatus MS32_OP_GetCaliValue(uint32_t OpUnit, MS32_OP_CaliTypeDef *OpInitStr) {
  ErrorStatus status = SUCCESS;

  switch (OpUnit) {
    /* Operation 1 */
    case MS32_OP1:
      OpInitStr->OpPosCaliData = READ_BIT(CMP_OP->OP1CAL, OPAMP_OPxCAL_OPxCALDATP) >> OPAMP_OPxCAL_OPxCALDATP_Pos;
      OpInitStr->OpNegCaliData = READ_BIT(CMP_OP->OP1CAL, OPAMP_OPxCAL_OPxCALDATN);
      break;
    /* Operation 2 */
    case MS32_OP2:
      OpInitStr->OpPosCaliData = READ_BIT(CMP_OP->OP2CAL, OPAMP_OPxCAL_OPxCALDATP) >> OPAMP_OPxCAL_OPxCALDATP_Pos;
      OpInitStr->OpNegCaliData = READ_BIT(CMP_OP->OP2CAL, OPAMP_OPxCAL_OPxCALDATN);
      break;
    /* Operation 3 */
    case MS32_OP3:
      OpInitStr->OpPosCaliData = READ_BIT(CMP_OP->OP3CAL, OPAMP_OPxCAL_OPxCALDATP) >> OPAMP_OPxCAL_OPxCALDATP_Pos;
      OpInitStr->OpNegCaliData = READ_BIT(CMP_OP->OP3CAL, OPAMP_OPxCAL_OPxCALDATN);
      break;
    default:
      status = ERROR;
      break;
  }

  return status;
}

/**
  * @brief  Set the OP calibration value according to the internal OPxCAL registers.
  * @param  OpUnit This parameter can be one of the following values:
  *            @arg @ref MS32_OP1     Operation 1 unit
  *            @arg @ref MS32_OP2     Operation 2 unit
  *            @arg @ref MS32_OP3     Operation 3 unit 
  * @param  OpInitStr  pointer to a MS32_OP_CaliTypeDef structure that contains
  *                the configuration information for the specified OP module.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: OP calibration are success
  *          - ERROR: OP calibration are fail
  */
ErrorStatus MS32_OP_SetCaliValue(uint32_t OpUnit, MS32_OP_CaliTypeDef *OpInitStr) {
  ErrorStatus status = SUCCESS;

  /* Enable clock */
  MS32_APB1_GRP2_EnableClock(MS32_APB1_GRP2_PERIPH_SYSCFG);

  switch (OpUnit) {
    /* Operation 1 */
    case MS32_OP1:
      MODIFY_REG(CMP_OP->OP1CAL, OPAMP_OPxCAL_OPxCALDATP, ((uint32_t)OpInitStr->OpPosCaliData << OPAMP_OPxCAL_OPxCALDATP_Pos));
      while (READ_BIT(CMP_OP->OP1CAL, OPAMP_OPxCAL_OPxSYNC));
      MODIFY_REG(CMP_OP->OP1CAL, OPAMP_OPxCAL_OPxCALDATN, (uint32_t)OpInitStr->OpNegCaliData);
      while (READ_BIT(CMP_OP->OP1CAL, OPAMP_OPxCAL_OPxSYNC));
      break;
    /* Operation 2 */
    case MS32_OP2:
      MODIFY_REG(CMP_OP->OP2CAL, OPAMP_OPxCAL_OPxCALDATP, ((uint32_t)OpInitStr->OpPosCaliData << OPAMP_OPxCAL_OPxCALDATP_Pos));
      while (READ_BIT(CMP_OP->OP2CAL, OPAMP_OPxCAL_OPxSYNC));
      MODIFY_REG(CMP_OP->OP2CAL, OPAMP_OPxCAL_OPxCALDATN, (uint32_t)OpInitStr->OpNegCaliData);
      while (READ_BIT(CMP_OP->OP2CAL, OPAMP_OPxCAL_OPxSYNC));
      break;
    /* Operation 3 */
    case MS32_OP3:
      MODIFY_REG(CMP_OP->OP3CAL, OPAMP_OPxCAL_OPxCALDATP, ((uint32_t)OpInitStr->OpPosCaliData << OPAMP_OPxCAL_OPxCALDATP_Pos));
      while (READ_BIT(CMP_OP->OP3CAL, OPAMP_OPxCAL_OPxSYNC));
      MODIFY_REG(CMP_OP->OP3CAL, OPAMP_OPxCAL_OPxCALDATN, (uint32_t)OpInitStr->OpNegCaliData);
      while (READ_BIT(CMP_OP->OP3CAL, OPAMP_OPxCAL_OPxSYNC));
      break;
    default:
      status = ERROR;
      break;
  }

  return status;
}

/**
  * @brief  Set the OP lock.
  * @param  None
  * @retval None
  */
void MS32_OP_LockEn(void) {
  SET_BIT(CMP_OP->OPCR, OPAMP_OPCR_OPAMPLCK);
}


/******************************** END OF FILE *********************************/

