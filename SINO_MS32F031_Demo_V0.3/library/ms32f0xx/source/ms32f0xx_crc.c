/* Includes ------------------------------------------------------------------*/
#include "ms32f0xx_bus.h"
#include "ms32f0xx_crc.h"


/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @defgroup CRC_Type CRC Private Macros
  * @{
  */
#define TYPE8(addr, offset)      (*(((volatile uint8_t *)addr) + offset))
#define TYPE16(addr, offset)     (*(((volatile uint16_t *)addr) + offset))
#define TYPE32(addr, offset)     (*(((volatile uint32_t *)addr) + offset))


/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @addtogroup CRC_EF_Init
  * @{
  */

/**
  * @brief  De-initialize CRC registers (Registers restored to their default values).
  * @param  None
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: CRC registers are de-initialized
  *          - ERROR: not applicable
  */
ErrorStatus MS32_CRC_DeInit(void) {
  MS32_CRC_InitTypeDef crc_cfg;

  MS32_CRC_StructInit(&crc_cfg);
  return MS32_CRC_Init(&crc_cfg);
}

/**
  * @brief Set each @ref MS32_CRC_InitTypeDef field to default value.
  * @param CrcInitStr  pointer to a @ref MS32_CRC_InitTypeDef structure
  *                          whose fields will be set to default values.
  * @retval None
  */
void MS32_CRC_StructInit(MS32_CRC_InitTypeDef *CrcInitStr) {
  /* Reset CRC init structure parameters values */
  CrcInitStr->InitValue               = MS32_CRC_DEFAULT_CRC_INITVALUE;
  CrcInitStr->InputDataInversionMode  = MS32_CRC_INDATA_REVERSE_NONE;
  CrcInitStr->OutputDataInversionMode = MS32_CRC_OUTDATA_REVERSE_NONE;
}

/**
  * @brief  Initialize the CRC according to the specified
  *         parameters in the MS32_CRC_InitTypeDef and create the associated handle.
  * @param  CrcInitStr  pointer to a MS32_CRC_InitTypeDef structure that contains
  *                the configuration information for the specified WWDG module.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: CRC registers are initialized
  *          - ERROR: not applicable
  */
ErrorStatus MS32_CRC_Init(MS32_CRC_InitTypeDef *CrcInitStr) {
  /* Enable clock */
  MS32_AHB1_GRP1_EnableClock(MS32_AHB1_GRP1_PERIPH_CRC);

  /* Set CRC initial value has been picked up by user */
  MS32_CRC_SetInitialData(CRC, CrcInitStr->InitValue);

  /* Set input data inversion mode */
  MS32_CRC_SetInputDataReverseMode(CRC, CrcInitStr->InputDataInversionMode);

  /* Set output data inversion mode */
  MS32_CRC_SetOutputDataReverseMode(CRC, CrcInitStr->OutputDataInversionMode);

  /* Reset the CRC calculation unit */
  MS32_CRC_ResetCRCCalculationUnit(CRC);

  /* clear IDR value */
  MS32_CRC_Write_IDR(CRC, 0x00);

  /* Return function status */
  return SUCCESS;
}

/**
  * @brief  Calculate the 7, 8, 16 or 32-bit CRC value of an 8, 16 or 32-bit data buffer
  *         starting with hcrc->Instance->INIT as initialization value.
  * @param  CalcMethod  specifies the function flags.
  *          This parameter can be one of the following values:
  *            @arg @ref MS32_CRC_ACC_CALC  the CRC accumulate calculation
  *            @arg @ref MS32_CRC_RECALC    the CRC recalculation
  * @param  InputDataFormat  specifies the function flags.
  *          This parameter can be one of the following values:
  *            @arg @ref MS32_CRC_INPUTDATA_FORMAT_UNDEFINED  undefined input data format 
  *            @arg @ref MS32_CRC_INPUTDATA_FORMAT_BYTES      input data in byte format
  *            @arg @ref MS32_CRC_INPUTDATA_FORMAT_HALFWORDS  input data in half-word format
  *            @arg @ref MS32_CRC_INPUTDATA_FORMAT_WORDS      input data in word format
  * @param  pBuffer pointer to the input data buffer, exact input data format is
  *         provided by hcrc->InputDataFormat.
  * @param  BufferLength input data buffer length (number of bytes if pBuffer
  *         type is * uint8_t, number of half-words if pBuffer type is * uint16_t,
  *         number of words if pBuffer type is * uint32_t).
  * @note  By default, the API expects a uint32_t pointer as input buffer parameter.
  *        Input buffer pointers with other types simply need to be cast in uint32_t
  *        and the API will internally adjust its input data processing based on the
  *        handle field hcrc->InputDataFormat.
  * @retval uint32_t CRC (returned value LSBs for CRC shorter than 32 bits)
  */
uint32_t MS32_CRC_Calculate(uint32_t CalcMethod, uint32_t InputDataFormat, uint32_t pBuffer[], uint32_t BufferLength) {
  uint32_t index;          /* CRC input data buffer index */

  /* Reset CRC Calculation Unit */
  if (CalcMethod == MS32_CRC_RECALC) {
    MS32_CRC_ResetCRCCalculationUnit(CRC);
  }

  switch (InputDataFormat) {
    case MS32_CRC_INPUTDATA_FORMAT_WORDS:
      /* Enter 32-bit input data to the CRC calculator */
      for (index = 0; index < BufferLength; index++) {
        MS32_CRC_FeedData32(CRC, TYPE32(pBuffer, index));
      }
      break;
    case MS32_CRC_INPUTDATA_FORMAT_HALFWORDS:
      /* Specific 8-bit input data handling  */
      for (index = 0; index < BufferLength; index++) {
        MS32_CRC_FeedData16(CRC, TYPE16(pBuffer, index));
      }
      break;
    case MS32_CRC_INPUTDATA_FORMAT_BYTES:
      /* Specific 16-bit input data handling  */
      for (index = 0; index < BufferLength; index++) {
        MS32_CRC_FeedData8(CRC, TYPE8(pBuffer, index));
      }
      break;
    default:
      break;
  }

  /* Return the CRC computed value */
  return MS32_CRC_ReadData32(CRC);
}


/******************************** END OF FILE *********************************/

