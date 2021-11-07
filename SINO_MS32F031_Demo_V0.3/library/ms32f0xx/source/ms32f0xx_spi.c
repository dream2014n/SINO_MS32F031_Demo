/* Includes ------------------------------------------------------------------*/
#include "ms32f0xx_spi.h"
#include "ms32f0xx_bus.h"
#include "ms32f0xx_rcc.h"


/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @defgroup SPI_Private_Constants SPI Private Constants
  * @{
  */
/* SPI registers Masks */
#define SPI_CR1_CLEAR_MASK                 (SPI_CR1_CPHA    | SPI_CR1_CPOL     | SPI_CR1_MSTR   | \
                                            SPI_CR1_BR      | SPI_CR1_LSBFIRST | SPI_CR1_SSI    | \
                                            SPI_CR1_SSM     | SPI_CR1_RXONLY   | SPI_CR1_CRCL   | \
                                            SPI_CR1_CRCNEXT | SPI_CR1_CRCEN    | SPI_CR1_BIDIOE | \
                                            SPI_CR1_BIDIMODE)

/** @defgroup I2S_Private_Constants I2S Private Constants
  * @{
  */
/* I2S registers Masks */
#define I2S_I2SCFGR_CLEAR_MASK             (SPI_I2SCFGR_CHLEN   | SPI_I2SCFGR_DATLEN | \
                                            SPI_I2SCFGR_CKPOL   | SPI_I2SCFGR_I2SSTD | \
                                            SPI_I2SCFGR_I2SCFG  | SPI_I2SCFGR_I2SMOD )

#define I2S_I2SPR_CLEAR_MASK               0x0002U


/* Private macros ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @addtogroup SPI_EF_Init
  * @{
  */

/**
  * @brief  De-initialize the SPI registers to their default reset values.
  * @param  SPIx SPI Instance
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: SPI registers are de-initialized
  *          - ERROR: Not applicable
  */
ErrorStatus MS32_SPI_DeInit(SPI_TypeDef *SPIx) {
  /* Enable clock */
  MS32_APB1_GRP2_EnableClock(MS32_APB1_GRP2_PERIPH_SPI1);
  /* Force reset of SPI clock */
  MS32_APB1_GRP2_ForceReset(MS32_APB1_GRP2_PERIPH_SPI1);
  /* Release reset of SPI clock */
  MS32_APB1_GRP2_ReleaseReset(MS32_APB1_GRP2_PERIPH_SPI1);

  return SUCCESS;
}

/**
  * @brief  Initialize the SPI registers according to the specified parameters in SpiInitStr.
  * @note   As some bits in SPI configuration registers can only be written when the SPI is disabled (SPI_CR1_SPE bit =0),
  *         SPI peripheral should be in disabled state prior calling this function. Otherwise, ERROR result will be returned.
  * @param  SPIx SPI Instance
  * @param  SpiInitStr pointer to a @ref MS32_SPI_InitTypeDef structure
  * @retval An ErrorStatus enumeration value. (Return always SUCCESS)
  */
ErrorStatus MS32_SPI_Init(SPI_TypeDef *SPIx, MS32_SPI_InitTypeDef *SpiInitStr) {
  ErrorStatus status = ERROR;

  /* Enable clock */
  MS32_APB1_GRP2_EnableClock(MS32_APB1_GRP2_PERIPH_SPI1);

  if (MS32_SPI_IsEnabled(SPIx) == 0x00000000U) {
    /*---------------------------- SPIx CR1 Configuration ------------------------
     * Configure SPIx CR1 with parameters:
     * - TransferDirection:  SPI_CR1_BIDIMODE, SPI_CR1_BIDIOE and SPI_CR1_RXONLY bits
     * - Master/Slave Mode:  SPI_CR1_MSTR bit
     * - ClockPolarity:      SPI_CR1_CPOL bit
     * - ClockPhase:         SPI_CR1_CPHA bit
     * - NSS management:     SPI_CR1_SSM bit
     * - BaudRate prescaler: SPI_CR1_BR[2:0] bits
     * - BitOrder:           SPI_CR1_LSBFIRST bit
     * - CRCCalculation:     SPI_CR1_CRCEN bit
     */
    MODIFY_REG(SPIx->CR1,
               SPI_CR1_CLEAR_MASK,
               SpiInitStr->TransferDirection | SpiInitStr->Mode |
               SpiInitStr->ClockPolarity | SpiInitStr->ClockPhase |
               SpiInitStr->NSS | SpiInitStr->BaudRate |
               SpiInitStr->BitOrder | SpiInitStr->CRCCalculation);

    /*---------------------------- SPIx CR2 Configuration ------------------------
     * Configure SPIx CR2 with parameters:
     * - DataWidth:          DS[3:0] bits
     * - NSS management:     SSOE bit
     */
    MODIFY_REG(SPIx->CR2,
               SPI_CR2_DS | SPI_CR2_SSOE,
               SpiInitStr->DataWidth | (SpiInitStr->NSS >> 16U));

    /*---------------------------- SPIx CRCPR Configuration ----------------------
     * Configure SPIx CRCPR with parameters:
     * - CRCPoly:            CRCPOLY[15:0] bits
     */
    if (SpiInitStr->CRCCalculation == MS32_SPI_CRCCALCULATION_ENABLE) {
      MS32_SPI_SetCRCPolynomial(SPIx, SpiInitStr->CRCPoly);
    }

    status = SUCCESS;
  }

  /* Activate the SPI mode (Reset I2SMOD bit in I2SCFGR register) */
  CLEAR_BIT(SPIx->I2SCFGR, SPI_I2SCFGR_I2SMOD);

  return status;
}

/**
  * @brief  Set each @ref MS32_SPI_InitTypeDef field to default value.
  * @param  SpiInitStr pointer to a @ref MS32_SPI_InitTypeDef structure
  * whose fields will be set to default values.
  * @retval None
  */
void MS32_SPI_StructInit(MS32_SPI_InitTypeDef *SpiInitStr) {
  /* Set SpiInitStr fields to default values */
  SpiInitStr->TransferDirection = MS32_SPI_FUMS32_DUPLEX;
  SpiInitStr->Mode              = MS32_SPI_MODE_SLAVE;
  SpiInitStr->DataWidth         = MS32_SPI_DATAWIDTH_8BIT;
  SpiInitStr->ClockPolarity     = MS32_SPI_POLARITY_LOW;
  SpiInitStr->ClockPhase        = MS32_SPI_PHASE_1EDGE;
  SpiInitStr->NSS               = MS32_SPI_NSS_HARD_INPUT;
  SpiInitStr->BaudRate          = MS32_SPI_BAUDRATEPRESCALER_DIV2;
  SpiInitStr->BitOrder          = MS32_SPI_MSB_FIRST;
  SpiInitStr->CRCCalculation    = MS32_SPI_CRCCALCULATION_DISABLE;
  SpiInitStr->CRCPoly           = 7U;
}


/** @addtogroup I2S_EF_Init
  * @{
  */

/**
  * @brief  De-initialize the SPI/I2S registers to their default reset values.
  * @param  SPIx SPI Instance
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: SPI registers are de-initialized
  *          - ERROR: SPI registers are not de-initialized
  */
ErrorStatus MS32_I2S_DeInit(SPI_TypeDef *SPIx) {
  return MS32_SPI_DeInit(SPIx);
}

/**
  * @brief  Initializes the SPI/I2S registers according to the specified parameters in I2S_InitStruct.
  * @note   As some bits in SPI configuration registers can only be written when the SPI is disabled (SPI_CR1_SPE bit =0),
  *         SPI peripheral should be in disabled state prior calling this function. Otherwise, ERROR result will be returned.
  * @param  SPIx SPI Instance
  * @param  I2S_InitStruct pointer to a @ref MS32_I2S_InitTypeDef structure
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: SPI registers are Initialized
  *          - ERROR: SPI registers are not Initialized
  */
ErrorStatus MS32_I2S_Init(SPI_TypeDef *SPIx, MS32_I2S_InitTypeDef *I2S_InitStruct) {
  uint32_t i2sdiv = 2U;
  uint32_t i2sodd = 0U;
  uint32_t packetlength = 1U;
  uint32_t tmp;
  MS32_RCC_ClocksTypeDef rcc_clocks;
  uint32_t sourceclock;
  ErrorStatus status = ERROR;

  /* Enable clock */
  MS32_APB1_GRP2_EnableClock(MS32_APB1_GRP2_PERIPH_SPI1);

  if (MS32_I2S_IsEnabled(SPIx) == 0x00000000U) {
    /*---------------------------- SPIx I2SCFGR Configuration --------------------
     * Configure SPIx I2SCFGR with parameters:
     * - Mode:          SPI_I2SCFGR_I2SCFG[1:0] bit
     * - Standard:      SPI_I2SCFGR_I2SSTD[1:0] and SPI_I2SCFGR_PCMSYNC bits
     * - DataFormat:    SPI_I2SCFGR_CHLEN and SPI_I2SCFGR_DATLEN bits
     * - ClockPolarity: SPI_I2SCFGR_CKPOL bit
     */

    /* Write to SPIx I2SCFGR */
    MODIFY_REG(SPIx->I2SCFGR,
               I2S_I2SCFGR_CLEAR_MASK,
               I2S_InitStruct->Mode | I2S_InitStruct->Standard |
               I2S_InitStruct->DataFormat | I2S_InitStruct->ClockPolarity |
               SPI_I2SCFGR_I2SMOD);

    /*---------------------------- SPIx I2SPR Configuration ----------------------
     * Configure SPIx I2SPR with parameters:
     * - MCLKOutput:    SPI_I2SPR_MCKOE bit
     * - AudioFreq:     SPI_I2SPR_I2SDIV[7:0] and SPI_I2SPR_ODD bits
     */

    /* If the requested audio frequency is not the default, compute the prescaler (i2sodd, i2sdiv)
     * else, default values are used:  i2sodd = 0U, i2sdiv = 2U.
     */
    if (I2S_InitStruct->AudioFreq != MS32_I2S_AUDIOFREQ_DEFAULT) {
      /* Check the frame length (For the Prescaler computing)
       * Default value: MS32_I2S_DATAFORMAT_16B (packetlength = 1U).
       */
      if (I2S_InitStruct->DataFormat != MS32_I2S_DATAFORMAT_16B) {
        /* Packet length is 32 bits */
        packetlength = 2U;
      }

      /* I2S Clock source is System clock: Get System Clock frequency */
      MS32_RCC_GetSystemClocksFreq(&rcc_clocks);

      /* Get the source clock value: based on System Clock value */
      sourceclock = rcc_clocks.SYSCLK_Frequency;

      /* Compute the Real divider depending on the MCLK output state with a floating point */
      if (I2S_InitStruct->MCLKOutput == MS32_I2S_MCLK_OUTPUT_ENABLE) {
        /* MCLK output is enabled */
        tmp = (((((sourceclock / 256U) * 10U) / I2S_InitStruct->AudioFreq)) + 5U);
      } else {
        /* MCLK output is disabled */
        tmp = (((((sourceclock / (32U * packetlength)) * 10U) / I2S_InitStruct->AudioFreq)) + 5U);
      }

      /* Remove the floating point */
      tmp = tmp / 10U;

      /* Check the parity of the divider */
      i2sodd = (tmp & (uint16_t)0x0001U);

      /* Compute the i2sdiv prescaler */
      i2sdiv = ((tmp - i2sodd) / 2U);

      /* Get the Mask for the Odd bit (SPI_I2SPR[8]) register */
      i2sodd = (i2sodd << 8U);
    }

    /* Test if the divider is 1 or 0 or greater than 0xFF */
    if ((i2sdiv < 2U) || (i2sdiv > 0xFFU)) {
      /* Set the default values */
      i2sdiv = 2U;
      i2sodd = 0U;
    }

    /* Write to SPIx I2SPR register the computed value */
    WRITE_REG(SPIx->I2SPR, i2sdiv | i2sodd | I2S_InitStruct->MCLKOutput);

    status = SUCCESS;
  }

  return status;
}

/**
  * @brief  Set each @ref MS32_I2S_InitTypeDef field to default value.
  * @param  I2S_InitStruct pointer to a @ref MS32_I2S_InitTypeDef structure
  *         whose fields will be set to default values.
  * @retval None
  */
void MS32_I2S_StructInit(MS32_I2S_InitTypeDef *I2S_InitStruct) {
  /*--------------- Reset I2S init structure parameters values -----------------*/
  I2S_InitStruct->Mode              = MS32_I2S_MODE_SLAVE_TX;
  I2S_InitStruct->Standard          = MS32_I2S_STANDARD_PHILIPS;
  I2S_InitStruct->DataFormat        = MS32_I2S_DATAFORMAT_16B;
  I2S_InitStruct->MCLKOutput        = MS32_I2S_MCLK_OUTPUT_DISABLE;
  I2S_InitStruct->AudioFreq         = MS32_I2S_AUDIOFREQ_DEFAULT;
  I2S_InitStruct->ClockPolarity     = MS32_I2S_POLARITY_LOW;
}

/**
  * @brief  Set linear and parity prescaler.
  * @note   To calculate value of PrescalerLinear(I2SDIV[7:0] bits) and PrescalerParity(ODD bit)\n
  *         Check Audio frequency table and formulas inside Reference Manual (SPI/I2S).
  * @param  SPIx SPI Instance
  * @param  PrescalerLinear value Min_Data=0x02 and Max_Data=0xFF.
  * @param  PrescalerParity This parameter can be one of the following values:
  *         @arg @ref MS32_I2S_PRESCALER_PARITY_EVEN
  *         @arg @ref MS32_I2S_PRESCALER_PARITY_ODD
  * @retval None
  */
void MS32_I2S_ConfigPrescaler(SPI_TypeDef *SPIx, uint32_t PrescalerLinear, uint32_t PrescalerParity) {
  /* Enable clock */
  MS32_APB1_GRP2_EnableClock(MS32_APB1_GRP2_PERIPH_SPI1);
  /* Write to SPIx I2SPR */
  MODIFY_REG(SPIx->I2SPR, SPI_I2SPR_I2SDIV | SPI_I2SPR_ODD, PrescalerLinear | (PrescalerParity << 8U));
}

/**
  * @brief  Initializes the SPI interrupt according to the specified parameters.
  * @param  SPIx SPI Instance
  * @param  InterruptFunc  contains the configuration information for the SPI interrupt.
  *         This parameter can be one or more of the following values:
  *         @arg @ref MS32_SPI_CR2_RXNEIE
  *         @arg @ref MS32_SPI_CR2_TXEIE 
  *         @arg @ref MS32_SPI_CR2_ERRIE 
  * @param  Priority  the interrupt priority 
  *         This parameter can be a value of 0x0~0x3
  * @retval None
  */
void MS32_SPI_ITConfig(SPI_TypeDef *SPIx, uint32_t InterruptFunc, uint32_t Priority) {
  /* Enable clock */
  MS32_APB1_GRP2_EnableClock(MS32_APB1_GRP2_PERIPH_SPI1);

  /*-------------------------------- ALL Interrrupt --------------------------*/
  CLEAR_BIT(SPIx->SR, MS32_SPI_SR_ALLIF);
  SET_BIT(SPIx->CR2, InterruptFunc);

  /*----------------------------- NVIC configuration -------------------------*/
  if (READ_BIT(SPIx->CR2, MS32_SPI_CR2_ALLIE)) {
    NVIC_EnableIRQ(SPI1_IRQn);
    NVIC_SetPriority(SPI1_IRQn, Priority);
  } else {
    NVIC_DisableIRQ(SPI1_IRQn);
  }
}

/**
  * @brief  Get the SPI flags according to the internal SPI ISR registers.
  * @param  SPIx SPI Instance
  * @param  Flags specifies the function flags.
  *          This parameter can be one or more of the following values:
  *            @arg @ref MS32_SPI_SR_RXNE   
  *            @arg @ref MS32_SPI_SR_TXE    
  *            @arg @ref MS32_SPI_SR_BSY    
  *            @arg @ref MS32_SPI_SR_CRCERR 
  *            @arg @ref MS32_SPI_SR_MODF   
  *            @arg @ref MS32_SPI_SR_OVR    
  *            @arg @ref MS32_SPI_SR_FRE   
  * @note   Clear flags(only crc) After getting the interrupt flags equal to set. 
  * @retval A FlagStatus enumeration value:
  *          - SET:   flag set(equal to "1")
  *          - RESET: flag no set(equal to "0")
  */
FlagStatus MS32_SPI_GetStatusFlag(SPI_TypeDef *SPIx, uint32_t Flags) {
  FlagStatus flags;

  if (READ_BIT(SPIx->SR, Flags)) {
    flags = SET;
    WRITE_REG(SPIx->SR, Flags);
  } else {
    flags = RESET;
  }

  return flags;
}


/******************************** END OF FILE *********************************/
