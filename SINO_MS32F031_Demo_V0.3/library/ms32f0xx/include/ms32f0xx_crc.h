/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MS32F0XX_CRC_H
#define __MS32F0XX_CRC_H

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
/** @defgroup CRC_Exported_Types CRC Exported Types
  * @{
  */

/**
  * @brief CRC Init Structure definition
  */
typedef struct {
  uint32_t InitValue;                 /*!< Init value to initiate CRC computation. No need to specify it if DefaultInitValueUse
                                           is set to DEFAULT_INIT_VALUE_ENABLE.   */
  uint32_t InputDataInversionMode;    /*!< This parameter is a value of @ref CRCEx_Input_Data_Inversion and specifies input data inversion mode.
                                           Can be either one of the following values
                                           @arg @ref CRC_INPUTDATA_INVERSION_NONE       no input data inversion
                                           @arg @ref CRC_INPUTDATA_INVERSION_BYTE       byte-wise inversion, 0x1A2B3C4D becomes 0x58D43CB2
                                           @arg @ref CRC_INPUTDATA_INVERSION_HALFWORD   halfword-wise inversion, 0x1A2B3C4D becomes 0xD458B23C
                                           @arg @ref CRC_INPUTDATA_INVERSION_WORD       word-wise inversion, 0x1A2B3C4D becomes 0xB23CD458 */
  uint32_t OutputDataInversionMode;   /*!< This parameter is a value of @ref CRCEx_Output_Data_Inversion and specifies output data (i.e. CRC) inversion mode.
                                            Can be either
                                            @arg @ref CRC_OUTPUTDATA_INVERSION_DISABLE   no CRC inversion,
                                            @arg @ref CRC_OUTPUTDATA_INVERSION_ENABLE    CRC 0x11223344 is converted into 0x22CC4488 */
} MS32_CRC_InitTypeDef;


/* Exported constants --------------------------------------------------------*/
/** @defgroup CRC_EC_Default_InitValue    Default CRC computation initialization value
  * @{
  */
#define MS32_CRC_DEFAULT_CRC_INITVALUE       (0xFFFFFFFFU) /*!< Default CRC computation initialization value */


/** @defgroup CRC_EC_INDATA_REVERSE Input Data Reverse
  * @{
  */
#define MS32_CRC_INDATA_REVERSE_NONE         (0x00000000U)                       /*!< Input Data bit order not affected */
#define MS32_CRC_INDATA_REVERSE_BYTE         CRC_CR_REV_IN_0                     /*!< Input Data bit reversal done by byte */
#define MS32_CRC_INDATA_REVERSE_HALFWORD     CRC_CR_REV_IN_1                     /*!< Input Data bit reversal done by half-word */
#define MS32_CRC_INDATA_REVERSE_WORD         (CRC_CR_REV_IN_1 | CRC_CR_REV_IN_0) /*!< Input Data bit reversal done by word */


/** @defgroup CRC_EC_OUTDATA_REVERSE Output Data Reverse
  * @{
  */
#define MS32_CRC_OUTDATA_REVERSE_NONE        (0x00000000U)  /*!< Output Data bit order not affected */
#define MS32_CRC_OUTDATA_REVERSE_BIT         CRC_CR_REV_OUT /*!< Output Data bit reversal done by bit */


/** @defgroup CRC_EC_Default_Polynomial_Value    Default CRC generating polynomial value
  * @brief    Normal representation of this polynomial value is
  *           X^32 + X^26 + X^23 + X^22 + X^16 + X^12 + X^11 + X^10 +X^8 + X^7 + X^5 + X^4 + X^2 + X + 1 .
  * @{
  */
#define MS32_CRC_DEFAULT_CRC32_POLY          (0x04C11DB7U) /*!< Default CRC generating polynomial value */


/** @defgroup CRC_Calculate_Method Calculate Method
  * @{
  */
#define MS32_CRC_ACC_CALC                    (0x00000000U) /*!< Accumulate calculation */
#define MS32_CRC_RECALC                      (0x00000001U) /*!< Recalculation */


/** @defgroup CRC_Input_Buffer_Format Input Buffer Format
  * @{
  */
#define MS32_CRC_INPUTDATA_FORMAT_UNDEFINED  (0x00000000U) /*!< Undefined input data format    */
#define MS32_CRC_INPUTDATA_FORMAT_BYTES      (0x00000001U) /*!< Input data in byte format      */
#define MS32_CRC_INPUTDATA_FORMAT_HALFWORDS  (0x00000002U) /*!< Input data in half-word format */
#define MS32_CRC_INPUTDATA_FORMAT_WORDS      (0x00000003U) /*!< Input data in word format      */


/* Exported macro ------------------------------------------------------------*/
/**
  * @brief  Write a value in CRC register
  * @param  __INSTANCE__ CRC Instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define MS32_CRC_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, __VALUE__)

/**
  * @brief  Read a value in CRC register
  * @param  __INSTANCE__ CRC Instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define MS32_CRC_ReadReg(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)


/* Exported functions --------------------------------------------------------*/
/** @defgroup CRC_EF_Configuration CRC Configuration functions
  * @{
  */

/**
  * @brief  Reset the CRC calculation unit.
  * @note   If Programmable Initial CRC value feature
  *         is available, also set the Data Register to the value stored in the
  *         CRC_INIT register, otherwise, reset Data Register to its default value.
  * @rmtoll CR           RESET         MS32_CRC_ResetCRCCalculationUnit
  * @param  CRCx CRC Instance
  * @retval None
  */
__STATIC_INLINE void MS32_CRC_ResetCRCCalculationUnit(CRC_TypeDef *CRCx) {
  SET_BIT(CRCx->CR, CRC_CR_RESET);
}

/**
  * @brief  Configure the reversal of the bit order of the input data
  * @rmtoll CR           REV_IN        MS32_CRC_SetInputDataReverseMode
  * @param  CRCx CRC Instance
  * @param  ReverseMode This parameter can be one of the following values:
  *         @arg @ref MS32_CRC_INDATA_REVERSE_NONE
  *         @arg @ref MS32_CRC_INDATA_REVERSE_BYTE
  *         @arg @ref MS32_CRC_INDATA_REVERSE_HALFWORD
  *         @arg @ref MS32_CRC_INDATA_REVERSE_WORD
  * @retval None
  */
__STATIC_INLINE void MS32_CRC_SetInputDataReverseMode(CRC_TypeDef *CRCx, uint32_t ReverseMode) {
  MODIFY_REG(CRCx->CR, CRC_CR_REV_IN, ReverseMode);
}

/**
  * @brief  Return type of reversal for input data bit order
  * @rmtoll CR           REV_IN        MS32_CRC_GetInputDataReverseMode
  * @param  CRCx CRC Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_CRC_INDATA_REVERSE_NONE
  *         @arg @ref MS32_CRC_INDATA_REVERSE_BYTE
  *         @arg @ref MS32_CRC_INDATA_REVERSE_HALFWORD
  *         @arg @ref MS32_CRC_INDATA_REVERSE_WORD
  */
__STATIC_INLINE uint32_t MS32_CRC_GetInputDataReverseMode(CRC_TypeDef *CRCx) {
  return (uint32_t)(READ_BIT(CRCx->CR, CRC_CR_REV_IN));
}

/**
  * @brief  Configure the reversal of the bit order of the Output data
  * @rmtoll CR           REV_OUT       MS32_CRC_SetOutputDataReverseMode
  * @param  CRCx CRC Instance
  * @param  ReverseMode This parameter can be one of the following values:
  *         @arg @ref MS32_CRC_OUTDATA_REVERSE_NONE
  *         @arg @ref MS32_CRC_OUTDATA_REVERSE_BIT
  * @retval None
  */
__STATIC_INLINE void MS32_CRC_SetOutputDataReverseMode(CRC_TypeDef *CRCx, uint32_t ReverseMode) {
  MODIFY_REG(CRCx->CR, CRC_CR_REV_OUT, ReverseMode);
}

/**
  * @brief  Configure the reversal of the bit order of the Output data
  * @rmtoll CR           REV_OUT       MS32_CRC_GetOutputDataReverseMode
  * @param  CRCx CRC Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_CRC_OUTDATA_REVERSE_NONE
  *         @arg @ref MS32_CRC_OUTDATA_REVERSE_BIT
  */
__STATIC_INLINE uint32_t MS32_CRC_GetOutputDataReverseMode(CRC_TypeDef *CRCx) {
  return (uint32_t)(READ_BIT(CRCx->CR, CRC_CR_REV_OUT));
}

/**
  * @brief  Initialize the Programmable initial CRC value.
  * @note   If the CRC size is less than 32 bits, the least significant bits
  *         are used to write the correct value
  * @note   MS32_CRC_DEFAULT_CRC_INITVALUE could be used as value for InitCrc parameter.
  * @rmtoll INIT         INIT          MS32_CRC_SetInitialData
  * @param  CRCx CRC Instance
  * @param  InitCrc Value to be programmed in Programmable initial CRC value register
  * @retval None
  */
__STATIC_INLINE void MS32_CRC_SetInitialData(CRC_TypeDef *CRCx, uint32_t InitCrc) {
  WRITE_REG(CRCx->INIT, InitCrc);
}

/**
  * @brief  Return current Initial CRC value.
  * @note   If the CRC size is less than 32 bits, the least significant bits
  *         are used to read the correct value
  * @rmtoll INIT         INIT          MS32_CRC_GetInitialData
  * @param  CRCx CRC Instance
  * @retval Value programmed in Programmable initial CRC value register
  */
__STATIC_INLINE uint32_t MS32_CRC_GetInitialData(CRC_TypeDef *CRCx) {
  return (uint32_t)(READ_REG(CRCx->INIT));
}


/** @defgroup CRC_EF_Data_Management Data_Management
  * @{
  */

/**
  * @brief  Write given 32-bit data to the CRC calculator
  * @rmtoll DR           DR            MS32_CRC_FeedData32
  * @param  CRCx CRC Instance
  * @param  InData value to be provided to CRC calculator between between Min_Data=0 and Max_Data=0xFFFFFFFF
  * @retval None
  */
__STATIC_INLINE void MS32_CRC_FeedData32(CRC_TypeDef *CRCx, uint32_t InData) {
  WRITE_REG(CRCx->DR, InData);
}

/**
  * @brief  Write given 16-bit data to the CRC calculator
  * @rmtoll DR           DR            MS32_CRC_FeedData16
  * @param  CRCx CRC Instance
  * @param  InData 16 bit value to be provided to CRC calculator between between Min_Data=0 and Max_Data=0xFFFF
  * @retval None
  */
__STATIC_INLINE void MS32_CRC_FeedData16(CRC_TypeDef *CRCx, uint16_t InData) {
  *(uint16_t __IO *)(&CRCx->DR) = (uint16_t) InData;                             /* Derogation MisraC2012 R.11.5 */
}

/**
  * @brief  Write given 8-bit data to the CRC calculator
  * @rmtoll DR           DR            MS32_CRC_FeedData8
  * @param  CRCx CRC Instance
  * @param  InData 8 bit value to be provided to CRC calculator between between Min_Data=0 and Max_Data=0xFF
  * @retval None
  */
__STATIC_INLINE void MS32_CRC_FeedData8(CRC_TypeDef *CRCx, uint8_t InData) {
  *(uint8_t __IO *)(&CRCx->DR) = (uint8_t) InData;
}

/**
  * @brief  Return current CRC calculation result. 32 bits value is returned.
  * @rmtoll DR           DR            MS32_CRC_ReadData32
  * @param  CRCx CRC Instance
  * @retval Current CRC calculation result as stored in CRC_DR register (32 bits).
  */
__STATIC_INLINE uint32_t MS32_CRC_ReadData32(CRC_TypeDef *CRCx) {
  return (uint32_t)(READ_REG(CRCx->DR));
}

/**
  * @brief  Return data stored in the Independent Data(IDR) register.
  * @note   This register can be used as a temporary storage location for one byte.
  * @rmtoll IDR          IDR           MS32_CRC_Read_IDR
  * @param  CRCx CRC Instance
  * @retval Value stored in CRC_IDR register (General-purpose 8-bit data register).
  */
__STATIC_INLINE uint32_t MS32_CRC_Read_IDR(CRC_TypeDef *CRCx) {
  return (uint32_t)(READ_REG(CRCx->IDR));
}

/**
  * @brief  Store data in the Independent Data(IDR) register.
  * @note   This register can be used as a temporary storage location for one byte.
  * @rmtoll IDR          IDR           MS32_CRC_Write_IDR
  * @param  CRCx CRC Instance
  * @param  InData value to be stored in CRC_IDR register (8-bit) between Min_Data=0 and Max_Data=0xFF
  * @retval None
  */
__STATIC_INLINE void MS32_CRC_Write_IDR(CRC_TypeDef *CRCx, uint32_t InData) {
  *((uint8_t __IO *)(&CRCx->IDR)) = (uint8_t) InData;
}


/** @defgroup CRC_EF_Init Initialization and de-initialization functions
  * @{
  */
ErrorStatus MS32_CRC_DeInit     (void);
void        MS32_CRC_StructInit (MS32_CRC_InitTypeDef *CrcInitStr);
ErrorStatus MS32_CRC_Init       (MS32_CRC_InitTypeDef *CrcInitStr);

/** @defgroup CRC_EF_Application function
  * @{
  */
uint32_t MS32_CRC_Calculate(uint32_t CalcMethod, uint32_t InputDataFormat, uint32_t pBuffer[], uint32_t BufferLength);


#ifdef __cplusplus
}
#endif

#endif /* __MS32F0XX_CRC_H */

/******************************** END OF FILE *********************************/
