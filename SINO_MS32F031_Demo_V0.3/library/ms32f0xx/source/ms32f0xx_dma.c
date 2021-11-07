/* Includes ------------------------------------------------------------------*/
#include "ms32f0xx_dma.h"
#include "ms32f0xx_bus.h"


/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @addtogroup DMA_MS32_EF_Init
  * @{
  */

/**
  * @brief  De-initialize the DMA registers to their default reset values.
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref MS32_DMA_CHANNEL_1
  *         @arg @ref MS32_DMA_CHANNEL_2
  *         @arg @ref MS32_DMA_CHANNEL_3
  *         @arg @ref MS32_DMA_CHANNEL_4
  *         @arg @ref MS32_DMA_CHANNEL_5
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: DMA registers are de-initialized
  *          - ERROR: DMA registers are not de-initialized
  */
ErrorStatus MS32_DMA_DeInit(DMA_TypeDef *DMAx, uint32_t Channel) {
  DMA_Channel_TypeDef *tmp = (DMA_Channel_TypeDef *)DMA1_Channel1;
  ErrorStatus status = SUCCESS;

  /* Enable DMA clock */
  if (DMAx == DMA1) {
    MS32_AHB1_GRP1_EnableClock(MS32_AHB1_GRP1_PERIPH_DMA1);
  } else {
    status = ERROR;
  }

  if (status == SUCCESS) {
    /* Check the DMA Instance DMAx and Channel parameters*/
    tmp = (DMA_Channel_TypeDef *)(__MS32_DMA_GET_CHANNEL_INSTANCE(DMAx, Channel));

    /* Disable the selected DMAx_Channely */
    CLEAR_BIT(tmp->CCR, DMA_CCR_EN);

    /* Reset DMAx_Channely control register */
    MS32_DMA_WriteReg(tmp, CCR, 0U);

    /* Reset DMAx_Channely remaining bytes register */
    MS32_DMA_WriteReg(tmp, CNDTR, 0U);

    /* Reset DMAx_Channely peripheral address register */
    MS32_DMA_WriteReg(tmp, CPAR, 0U);

    /* Reset DMAx_Channely memory address register */
    MS32_DMA_WriteReg(tmp, CMAR, 0U);

    switch (Channel) {
      case MS32_DMA_CHANNEL_1:
        /* Reset interrupt pending bits for DMAx Channel1 */
        WRITE_REG(DMAx->IFCR, DMA_IFCR_CGIF1 | DMA_IFCR_CTCIF1 | DMA_IFCR_CHTIF1 | DMA_IFCR_CTEIF1);
        break;
      case MS32_DMA_CHANNEL_2:
        /* Reset interrupt pending bits for DMAx Channel2 */
        WRITE_REG(DMAx->IFCR, DMA_IFCR_CGIF2 | DMA_IFCR_CTCIF2 | DMA_IFCR_CHTIF2 | DMA_IFCR_CTEIF2);
        break;
      case MS32_DMA_CHANNEL_3:
        /* Reset interrupt pending bits for DMAx Channel3 */
        WRITE_REG(DMAx->IFCR, DMA_IFCR_CGIF3 | DMA_IFCR_CTCIF3 | DMA_IFCR_CHTIF3 | DMA_IFCR_CTEIF3);
        break;
      case MS32_DMA_CHANNEL_4:
        /* Reset interrupt pending bits for DMAx Channel4 */
        WRITE_REG(DMAx->IFCR, DMA_IFCR_CGIF4 | DMA_IFCR_CTCIF4 | DMA_IFCR_CHTIF4 | DMA_IFCR_CTEIF4);
        break;
      case MS32_DMA_CHANNEL_5:
        /* Reset interrupt pending bits for DMAx Channel5 */
        WRITE_REG(DMAx->IFCR, DMA_IFCR_CGIF5 | DMA_IFCR_CTCIF5 | DMA_IFCR_CHTIF5 | DMA_IFCR_CTEIF5);
        break;
      default:
        status = ERROR;
        break;
    }
  }

  return status;
}

/**
  * @brief  Set each @ref MS32_DMA_InitTypeDef field to default value.
  * @param  DmaInitStr Pointer to a @ref MS32_DMA_InitTypeDef structure.
  * @retval None
  */
void MS32_DMA_StructInit(MS32_DMA_InitTypeDef *DmaInitStr) {
  /* Set DmaInitStr fields to default values */
  DmaInitStr->PeriphOrM2MSrcAddress  = 0x00000000U;
  DmaInitStr->MemoryOrM2MDstAddress  = 0x00000000U;
  DmaInitStr->Direction              = MS32_DMA_DIRECTION_PERIPH_TO_MEMORY;
  DmaInitStr->Mode                   = MS32_DMA_MODE_NORMAL;
  DmaInitStr->PeriphOrM2MSrcIncMode  = MS32_DMA_PERIPH_NOINCREMENT;
  DmaInitStr->MemoryOrM2MDstIncMode  = MS32_DMA_MEMORY_NOINCREMENT;
  DmaInitStr->PeriphOrM2MSrcDataSize = MS32_DMA_PDATAALIGN_BYTE;
  DmaInitStr->MemoryOrM2MDstDataSize = MS32_DMA_MDATAALIGN_BYTE;
  DmaInitStr->NbData                 = 0x00000000U;
  DmaInitStr->Priority               = MS32_DMA_PRIORITY_LOW;
}

/**
  * @brief  Initialize the DMA registers according to the specified parameters in DmaInitStr.
  * @note   To convert DMAx_Channely Instance to DMAx Instance and Channely, use helper macros :
  *         @arg @ref __MS32_DMA_GET_INSTANCE
  *         @arg @ref __MS32_DMA_GET_CHANNEL
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref MS32_DMA_CHANNEL_1
  *         @arg @ref MS32_DMA_CHANNEL_2
  *         @arg @ref MS32_DMA_CHANNEL_3
  *         @arg @ref MS32_DMA_CHANNEL_4
  *         @arg @ref MS32_DMA_CHANNEL_5
  * @param  DmaInitStr pointer to a @ref MS32_DMA_InitTypeDef structure.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: DMA registers are initialized
  *          - ERROR: Not applicable
  */
ErrorStatus MS32_DMA_Init(DMA_TypeDef *DMAx, uint32_t Channel, MS32_DMA_InitTypeDef *DmaInitStr) {
  ErrorStatus status = SUCCESS;

  /* Check the DMA type */
  if (DMAx == DMA1) {
    /* Enable DMA clock */
    MS32_AHB1_GRP1_EnableClock(MS32_AHB1_GRP1_PERIPH_DMA1);
    
    /*---------------------------- DMAx CCR Configuration ------------------------
    * Configure DMAx_Channely: data transfer direction, data transfer mode,
    *                          peripheral and memory increment mode,
    *                          data size alignment and  priority level with parameters :
    * - Direction:      DMA_CCR_DIR and DMA_CCR_MEM2MEM bits
    * - Mode:           DMA_CCR_CIRC bit
    * - PeriphOrM2MSrcIncMode:  DMA_CCR_PINC bit
    * - MemoryOrM2MDstIncMode:  DMA_CCR_MINC bit
    * - PeriphOrM2MSrcDataSize: DMA_CCR_PSIZE[1:0] bits
    * - MemoryOrM2MDstDataSize: DMA_CCR_MSIZE[1:0] bits
    * - Priority:               DMA_CCR_PL[1:0] bits
    */
    MS32_DMA_ConfigTransfer(DMAx, Channel, DmaInitStr->Direction | \
                            DmaInitStr->Mode                     | \
                            DmaInitStr->PeriphOrM2MSrcIncMode    | \
                            DmaInitStr->MemoryOrM2MDstIncMode    | \
                            DmaInitStr->PeriphOrM2MSrcDataSize   | \
                            DmaInitStr->MemoryOrM2MDstDataSize   | \
                            DmaInitStr->Priority);

    /*-------------------------- DMAx CMAR Configuration -------------------------
    * Configure the memory or destination base address with parameter :
    * - MemoryOrM2MDstAddress: DMA_CMAR_MA[31:0] bits
    */
    MS32_DMA_SetMemoryAddress(DMAx, Channel, DmaInitStr->MemoryOrM2MDstAddress);

    /*-------------------------- DMAx CPAR Configuration -------------------------
    * Configure the peripheral or source base address with parameter :
    * - PeriphOrM2MSrcAddress: DMA_CPAR_PA[31:0] bits
    */
    MS32_DMA_SetPeriphAddress(DMAx, Channel, DmaInitStr->PeriphOrM2MSrcAddress);

    /*--------------------------- DMAx CNDTR Configuration -----------------------
    * Configure the peripheral base address with parameter :
    * - NbData: DMA_CNDTR_NDT[15:0] bits
    */
    MS32_DMA_SetDataLength(DMAx, Channel, DmaInitStr->NbData);
  } else {
    status = ERROR;
  }

  return status;
}

/**
  * @brief  Initializes the DMA interrupt according to the specified parameters.
  * @param  DMAx  DMAx Instance
  * @param  Channel  DMA channel
  *         This parameter can be one of the following values:
  *         @arg @ref MS32_DMA_CHANNEL_1
  *         @arg @ref MS32_DMA_CHANNEL_2
  *         @arg @ref MS32_DMA_CHANNEL_3
  *         @arg @ref MS32_DMA_CHANNEL_4
  *         @arg @ref MS32_DMA_CHANNEL_5
  * @param  InterruptFunc  contains the configuration information for the DMA interrupt.
  *         This parameter can be one or more of the following values:
  *         @arg @ref MS32_DMA_CCR_TCIE  transfer complete interrupt
  *         @arg @ref MS32_DMA_CCR_HTIE  half Transfer interrupt
  *         @arg @ref MS32_DMA_CCR_TEIE  transfer error interrupt
  * @param  Priority  the interrupt priority 
  *         This parameter can be a value of 0x0~0x3
  * @retval None
  */
void MS32_DMA_ITConfig(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t InterruptFunc, uint32_t Priority) {
  IRQn_Type dma_irq;

  /* Enable DMA clock */
  MS32_AHB1_GRP1_EnableClock(MS32_AHB1_GRP1_PERIPH_DMA1);

  /*-------------------------------- ALL Interrrupt --------------------------*/
  SET_BIT(DMAx->IFCR, MS32_DMA_IFCR_CALL);
  MODIFY_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR, MS32_DMA_CCR_ALLIE, InterruptFunc);

  /*----------------------------- NVIC configuration -------------------------*/
  switch (Channel) {
    default:
    case MS32_DMA_CHANNEL_1:
      dma_irq = DMA1_Channel1_IRQn;
      break;
    case MS32_DMA_CHANNEL_2:
    case MS32_DMA_CHANNEL_3:
      dma_irq = DMA1_Channel2_3_IRQn;
      break;
    case MS32_DMA_CHANNEL_4:
    case MS32_DMA_CHANNEL_5:
      dma_irq = DMA1_Channel4_5_IRQn;
      break;
  }
  if (READ_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR, MS32_DMA_CCR_ALLIE)) {
    NVIC_EnableIRQ(dma_irq);
    NVIC_SetPriority(dma_irq, Priority);
  } else {
    NVIC_DisableIRQ(dma_irq);
  }
}

/**
  * @brief  Get the DMA interrupt and error flags according to the internal 
  *         DMA ISR registers.
  * @param  Flags specifies the function flags.
  *          This parameter can be one of the following values:
  *            @arg @ref MS32_DMA_ISR_GIF1   the DMA programme error flag
  *            @arg @ref MS32_DMA_ISR_TCIF1  the DMA write error flag
  *            @arg @ref MS32_DMA_ISR_HTIF1  the DMA end of operartion flag
  *            @arg @ref MS32_DMA_ISR_TEIF1  the DMA end of operartion flag
  *            @arg @ref MS32_DMA_ISR_GIF2   the DMA end of operartion flag
  *            @arg @ref MS32_DMA_ISR_TCIF2  the DMA end of operartion flag
  *            @arg @ref MS32_DMA_ISR_HTIF2  the DMA end of operartion flag
  *            @arg @ref MS32_DMA_ISR_TEIF2  the DMA end of operartion flag
  *            @arg @ref MS32_DMA_ISR_GIF3   the DMA end of operartion flag
  *            @arg @ref MS32_DMA_ISR_TCIF3  the DMA end of operartion flag
  *            @arg @ref MS32_DMA_ISR_HTIF3  the DMA end of operartion flag
  *            @arg @ref MS32_DMA_ISR_TEIF3  the DMA end of operartion flag
  *            @arg @ref MS32_DMA_ISR_GIF4   the DMA end of operartion flag
  *            @arg @ref MS32_DMA_ISR_TCIF4  the DMA end of operartion flag
  *            @arg @ref MS32_DMA_ISR_HTIF4  the DMA end of operartion flag
  *            @arg @ref MS32_DMA_ISR_TEIF4  the DMA end of operartion flag
  *            @arg @ref MS32_DMA_ISR_GIF5   the DMA end of operartion flag
  *            @arg @ref MS32_DMA_ISR_TCIF5  the DMA end of operartion flag
  *            @arg @ref MS32_DMA_ISR_HTIF5  the DMA end of operartion flag
  *            @arg @ref MS32_DMA_ISR_TEIF5  the DMA end of operartion flag
  * @note   Clear flags After getting the interrupt or error flags equal to set. 
  * @retval A FlagStatus enumeration value:
  *          - SET:   flag set(equal to "1")
  *          - RESET: flag no set(equal to "0")
  */
FlagStatus MS32_DMA_GetStatusFlag(DMA_TypeDef *DMAx, uint32_t Flags) {
  FlagStatus flags;

  if (READ_BIT(DMAx->ISR, Flags)) {
    flags = SET;
    WRITE_REG(DMAx->IFCR, Flags);
  } else {
    flags = RESET;
  }

  return flags;
}

/**
  * @brief  Restart the DMA, after finishing transfer.
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref MS32_DMA_CHANNEL_1
  *         @arg @ref MS32_DMA_CHANNEL_2
  *         @arg @ref MS32_DMA_CHANNEL_3
  *         @arg @ref MS32_DMA_CHANNEL_4
  *         @arg @ref MS32_DMA_CHANNEL_5
  * @param  NbData Between Min_Data = 0 and Max_Data = 0x0000FFFF
  * @retval None
  */
void MS32_DMA_Restart(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t NbData) {
  MS32_DMA_DisableChannel(DMAx, Channel);
  MS32_DMA_SetDataLength(DMAx, Channel, NbData);
  MS32_DMA_EnableChannel(DMAx, Channel);
}

/******************************** END OF FILE *********************************/

