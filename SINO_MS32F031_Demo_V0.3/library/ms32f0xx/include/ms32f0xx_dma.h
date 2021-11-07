/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MS32F0XX_DMA_H
#define __MS32F0XX_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ms32f0xx.h"


/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/** @defgroup DMA_MS32_Private_Variables DMA Private Variables
  * @{
  */

/* Array used to get the DMA channel register offset versus channel index MS32_DMA_CHANNEL_x */
static const uint8_t CHANNEL_OFFSET_TAB[] = {
  (uint8_t)(DMA1_Channel1_BASE - DMA1_BASE),
  (uint8_t)(DMA1_Channel2_BASE - DMA1_BASE),
  (uint8_t)(DMA1_Channel3_BASE - DMA1_BASE),
  (uint8_t)(DMA1_Channel4_BASE - DMA1_BASE),
  (uint8_t)(DMA1_Channel5_BASE - DMA1_BASE),
};


/* Private constants ---------------------------------------------------------*/
/** @defgroup DMA_MS32_Private_Constants DMA Private Constants
  * @{
  */

/* Define used to get CSELR register offset */
#define DMA_CSELR_OFFSET                  (uint32_t)(DMA1_CSELR_BASE - DMA1_BASE)

/* Defines used for the bit position in the register and perform offsets */
#define DMA_POSITION_CSELR_CXS            ((Channel-1U)*4U)


/* Private macros ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/** @defgroup DMA_MS32_ES_INIT DMA Exported Init structure
  * @{
  */
typedef struct {
  uint32_t PeriphOrM2MSrcAddress;  /*!< Specifies the peripheral base address for DMA transfer
                                        or as Source base address in case of memory to memory transfer direction.
                                        This parameter must be a value between Min_Data = 0 and Max_Data = 0xFFFFFFFF. */
  uint32_t MemoryOrM2MDstAddress;  /*!< Specifies the memory base address for DMA transfer
                                        or as Destination base address in case of memory to memory transfer direction.
                                        This parameter must be a value between Min_Data = 0 and Max_Data = 0xFFFFFFFF. */
  uint32_t Direction;              /*!< Specifies if the data will be transferred from memory to peripheral,
                                        from memory to memory or from peripheral to memory.
                                        This parameter can be a value of @ref DMA_EC_DIRECTION
                                        This feature can be modified afterwards using unitary function @ref MS32_DMA_SetDataTransferDirection(). */
  uint32_t Mode;                   /*!< Specifies the normal or circular operation mode.
                                        This parameter can be a value of @ref DMA_EC_MODE
                                        @note: The circular buffer mode cannot be used if the memory to memory
                                               data transfer direction is configured on the selected Channel
                                        This feature can be modified afterwards using unitary function @ref MS32_DMA_SetMode(). */
  uint32_t PeriphOrM2MSrcIncMode;  /*!< Specifies whether the Peripheral address or Source address in case of memory to memory transfer direction
                                        is incremented or not.
                                        This parameter can be a value of @ref DMA_EC_PERIPH
                                        This feature can be modified afterwards using unitary function @ref MS32_DMA_SetPeriphIncMode(). */
  uint32_t MemoryOrM2MDstIncMode;  /*!< Specifies whether the Memory address or Destination address in case of memory to memory transfer direction
                                        is incremented or not.
                                        This parameter can be a value of @ref DMA_EC_MEMORY
                                        This feature can be modified afterwards using unitary function @ref MS32_DMA_SetMemoryIncMode(). */
  uint32_t PeriphOrM2MSrcDataSize; /*!< Specifies the Peripheral data size alignment or Source data size alignment (byte, half word, word)
                                        in case of memory to memory transfer direction.
                                        This parameter can be a value of @ref DMA_EC_PDATAALIGN
                                        This feature can be modified afterwards using unitary function @ref MS32_DMA_SetPeriphSize(). */
  uint32_t MemoryOrM2MDstDataSize; /*!< Specifies the Memory data size alignment or Destination data size alignment (byte, half word, word)
                                        in case of memory to memory transfer direction.
                                        This parameter can be a value of @ref DMA_EC_MDATAALIGN
                                        This feature can be modified afterwards using unitary function @ref MS32_DMA_SetMemorySize(). */
  uint32_t NbData;                 /*!< Specifies the number of data to transfer, in data unit.
                                        The data unit is equal to the source buffer configuration set in PeripheralSize
                                        or MemorySize parameters depending in the transfer direction.
                                        This parameter must be a value between Min_Data = 0 and Max_Data = 0x0000FFFF
                                        This feature can be modified afterwards using unitary function @ref MS32_DMA_SetDataLength(). */
  uint32_t Priority;               /*!< Specifies the channel priority level.
                                        This parameter can be a value of @ref DMA_EC_PRIORITY
                                        This feature can be modified afterwards using unitary function @ref MS32_DMA_SetChannelPriorityLevel(). */
} MS32_DMA_InitTypeDef;


/* Exported constants --------------------------------------------------------*/
/** @defgroup MS32_DMA_Exported_Constants DMA Exported Constants
  * @{
  */

/** @defgroup DMA_EC_CLEAR_FLAG Clear Flags Defines
  * @brief    Flags defines which can be used with MS32_DMA_WriteReg function
  * @{
  */
#define MS32_DMA_IFCR_CGIF1                 DMA_IFCR_CGIF1        /*!< Channel 1 global flag            */
#define MS32_DMA_IFCR_CTCIF1                DMA_IFCR_CTCIF1       /*!< Channel 1 transfer complete flag */
#define MS32_DMA_IFCR_CHTIF1                DMA_IFCR_CHTIF1       /*!< Channel 1 half transfer flag     */
#define MS32_DMA_IFCR_CTEIF1                DMA_IFCR_CTEIF1       /*!< Channel 1 transfer error flag    */
#define MS32_DMA_IFCR_CGIF2                 DMA_IFCR_CGIF2        /*!< Channel 2 global flag            */
#define MS32_DMA_IFCR_CTCIF2                DMA_IFCR_CTCIF2       /*!< Channel 2 transfer complete flag */
#define MS32_DMA_IFCR_CHTIF2                DMA_IFCR_CHTIF2       /*!< Channel 2 half transfer flag     */
#define MS32_DMA_IFCR_CTEIF2                DMA_IFCR_CTEIF2       /*!< Channel 2 transfer error flag    */
#define MS32_DMA_IFCR_CGIF3                 DMA_IFCR_CGIF3        /*!< Channel 3 global flag            */
#define MS32_DMA_IFCR_CTCIF3                DMA_IFCR_CTCIF3       /*!< Channel 3 transfer complete flag */
#define MS32_DMA_IFCR_CHTIF3                DMA_IFCR_CHTIF3       /*!< Channel 3 half transfer flag     */
#define MS32_DMA_IFCR_CTEIF3                DMA_IFCR_CTEIF3       /*!< Channel 3 transfer error flag    */
#define MS32_DMA_IFCR_CGIF4                 DMA_IFCR_CGIF4        /*!< Channel 4 global flag            */
#define MS32_DMA_IFCR_CTCIF4                DMA_IFCR_CTCIF4       /*!< Channel 4 transfer complete flag */
#define MS32_DMA_IFCR_CHTIF4                DMA_IFCR_CHTIF4       /*!< Channel 4 half transfer flag     */
#define MS32_DMA_IFCR_CTEIF4                DMA_IFCR_CTEIF4       /*!< Channel 4 transfer error flag    */
#define MS32_DMA_IFCR_CGIF5                 DMA_IFCR_CGIF5        /*!< Channel 5 global flag            */
#define MS32_DMA_IFCR_CTCIF5                DMA_IFCR_CTCIF5       /*!< Channel 5 transfer complete flag */
#define MS32_DMA_IFCR_CHTIF5                DMA_IFCR_CHTIF5       /*!< Channel 5 half transfer flag     */
#define MS32_DMA_IFCR_CTEIF5                DMA_IFCR_CTEIF5       /*!< Channel 5 transfer error flag    */
#define MS32_DMA_IFCR_CALL                  (DMA_IFCR_CGIF1 | DMA_IFCR_CTCIF1 | DMA_IFCR_CHTIF1 | DMA_IFCR_CTEIF1 |\
                                             DMA_IFCR_CGIF2 | DMA_IFCR_CTCIF2 | DMA_IFCR_CHTIF2 | DMA_IFCR_CTEIF2 |\
                                             DMA_IFCR_CGIF3 | DMA_IFCR_CTCIF3 | DMA_IFCR_CHTIF3 | DMA_IFCR_CTEIF3 |\
                                             DMA_IFCR_CGIF4 | DMA_IFCR_CTCIF4 | DMA_IFCR_CHTIF4 | DMA_IFCR_CTEIF4 |\
                                             DMA_IFCR_CGIF5 | DMA_IFCR_CTCIF5 | DMA_IFCR_CHTIF5 | DMA_IFCR_CTEIF5)


/** @defgroup DMA_EC_GET_FLAG Get Flags Defines
  * @brief    Flags defines which can be used with MS32_DMA_ReadReg function
  * @{
  */
#define MS32_DMA_ISR_GIF1                   DMA_ISR_GIF1          /*!< Channel 1 global flag            */
#define MS32_DMA_ISR_TCIF1                  DMA_ISR_TCIF1         /*!< Channel 1 transfer complete flag */
#define MS32_DMA_ISR_HTIF1                  DMA_ISR_HTIF1         /*!< Channel 1 half transfer flag     */
#define MS32_DMA_ISR_TEIF1                  DMA_ISR_TEIF1         /*!< Channel 1 transfer error flag    */
#define MS32_DMA_ISR_GIF2                   DMA_ISR_GIF2          /*!< Channel 2 global flag            */
#define MS32_DMA_ISR_TCIF2                  DMA_ISR_TCIF2         /*!< Channel 2 transfer complete flag */
#define MS32_DMA_ISR_HTIF2                  DMA_ISR_HTIF2         /*!< Channel 2 half transfer flag     */
#define MS32_DMA_ISR_TEIF2                  DMA_ISR_TEIF2         /*!< Channel 2 transfer error flag    */
#define MS32_DMA_ISR_GIF3                   DMA_ISR_GIF3          /*!< Channel 3 global flag            */
#define MS32_DMA_ISR_TCIF3                  DMA_ISR_TCIF3         /*!< Channel 3 transfer complete flag */
#define MS32_DMA_ISR_HTIF3                  DMA_ISR_HTIF3         /*!< Channel 3 half transfer flag     */
#define MS32_DMA_ISR_TEIF3                  DMA_ISR_TEIF3         /*!< Channel 3 transfer error flag    */
#define MS32_DMA_ISR_GIF4                   DMA_ISR_GIF4          /*!< Channel 4 global flag            */
#define MS32_DMA_ISR_TCIF4                  DMA_ISR_TCIF4         /*!< Channel 4 transfer complete flag */
#define MS32_DMA_ISR_HTIF4                  DMA_ISR_HTIF4         /*!< Channel 4 half transfer flag     */
#define MS32_DMA_ISR_TEIF4                  DMA_ISR_TEIF4         /*!< Channel 4 transfer error flag    */
#define MS32_DMA_ISR_GIF5                   DMA_ISR_GIF5          /*!< Channel 5 global flag            */
#define MS32_DMA_ISR_TCIF5                  DMA_ISR_TCIF5         /*!< Channel 5 transfer complete flag */
#define MS32_DMA_ISR_HTIF5                  DMA_ISR_HTIF5         /*!< Channel 5 half transfer flag     */
#define MS32_DMA_ISR_TEIF5                  DMA_ISR_TEIF5         /*!< Channel 5 transfer error flag    */


/** @defgroup DMA_EC_IT IT Defines
  * @brief    IT defines which can be used with MS32_DMA_ReadReg and  MS32_DMA_WriteReg functions
  * @{
  */
#define MS32_DMA_CCR_TCIE                   DMA_CCR_TCIE          /*!< Transfer complete interrupt */
#define MS32_DMA_CCR_HTIE                   DMA_CCR_HTIE          /*!< Half Transfer interrupt     */
#define MS32_DMA_CCR_TEIE                   DMA_CCR_TEIE          /*!< Transfer error interrupt    */
#define MS32_DMA_CCR_ALLIE                  (DMA_CCR_TCIE | DMA_CCR_HTIE | DMA_CCR_TEIE)


/** @defgroup DMA_EC_CHANNEL CHANNEL
  * @{
  */
#define MS32_DMA_CHANNEL_1                  0x00000001U /*!< DMA Channel 1 */
#define MS32_DMA_CHANNEL_2                  0x00000002U /*!< DMA Channel 2 */
#define MS32_DMA_CHANNEL_3                  0x00000003U /*!< DMA Channel 3 */
#define MS32_DMA_CHANNEL_4                  0x00000004U /*!< DMA Channel 4 */
#define MS32_DMA_CHANNEL_5                  0x00000005U /*!< DMA Channel 5 */
#define MS32_DMA_CHANNEL_ALL                0xFFFF0000U /*!< DMA Channel all (used only for function @ref MS32_DMA_DeInit(). */


/** @defgroup DMA_EC_DIRECTION Transfer Direction
  * @{
  */
#define MS32_DMA_DIRECTION_PERIPH_TO_MEMORY 0x00000000U             /*!< Peripheral to memory direction */
#define MS32_DMA_DIRECTION_MEMORY_TO_PERIPH DMA_CCR_DIR             /*!< Memory to peripheral direction */
#define MS32_DMA_DIRECTION_MEMORY_TO_MEMORY DMA_CCR_MEM2MEM         /*!< Memory to memory direction     */


/** @defgroup DMA_EC_MODE Transfer mode
  * @{
  */
#define MS32_DMA_MODE_NORMAL                0x00000000U             /*!< Normal Mode                  */
#define MS32_DMA_MODE_CIRCULAR              DMA_CCR_CIRC            /*!< Circular Mode                */


/** @defgroup DMA_EC_PERIPH Peripheral increment mode
  * @{
  */
#define MS32_DMA_PERIPH_INCREMENT           DMA_CCR_PINC            /*!< Peripheral increment mode Enable */
#define MS32_DMA_PERIPH_NOINCREMENT         0x00000000U             /*!< Peripheral increment mode Disable */


/** @defgroup DMA_EC_MEMORY Memory increment mode
  * @{
  */
#define MS32_DMA_MEMORY_INCREMENT           DMA_CCR_MINC            /*!< Memory increment mode Enable  */
#define MS32_DMA_MEMORY_NOINCREMENT         0x00000000U             /*!< Memory increment mode Disable */


/** @defgroup DMA_EC_PDATAALIGN Peripheral data alignment
  * @{
  */
#define MS32_DMA_PDATAALIGN_BYTE            0x00000000U             /*!< Peripheral data alignment : Byte     */
#define MS32_DMA_PDATAALIGN_HALFWORD        DMA_CCR_PSIZE_0         /*!< Peripheral data alignment : HalfWord */
#define MS32_DMA_PDATAALIGN_WORD            DMA_CCR_PSIZE_1         /*!< Peripheral data alignment : Word     */


/** @defgroup DMA_EC_MDATAALIGN Memory data alignment
  * @{
  */
#define MS32_DMA_MDATAALIGN_BYTE            0x00000000U             /*!< Memory data alignment : Byte     */
#define MS32_DMA_MDATAALIGN_HALFWORD        DMA_CCR_MSIZE_0         /*!< Memory data alignment : HalfWord */
#define MS32_DMA_MDATAALIGN_WORD            DMA_CCR_MSIZE_1         /*!< Memory data alignment : Word     */


/** @defgroup DMA_EC_PRIORITY Transfer Priority level
  * @{
  */
#define MS32_DMA_PRIORITY_LOW               0x00000000U             /*!< Priority level : Low       */
#define MS32_DMA_PRIORITY_MEDIUM            DMA_CCR_PL_0            /*!< Priority level : Medium    */
#define MS32_DMA_PRIORITY_HIGH              DMA_CCR_PL_1            /*!< Priority level : High      */
#define MS32_DMA_PRIORITY_VERYHIGH          DMA_CCR_PL              /*!< Priority level : Very_High */


/* Exported macro ------------------------------------------------------------*/
/** @defgroup DMA_EM_WRITE_READ Common Write and read registers macros
  * @{
  */

/**
  * @brief  Write a value in DMA register
  * @param  __INSTANCE__ DMA Instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define MS32_DMA_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, (__VALUE__))

/**
  * @brief  Read a value in DMA register
  * @param  __INSTANCE__ DMA Instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define MS32_DMA_ReadReg(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)


/** @defgroup DMA_EM_CONVERT_DMAxCHANNELy Convert DMAxChannely
  * @{
  */

/**
  * @brief  Convert DMAx_Channely into DMAx
  * @param  __CHANNEL_INSTANCE__ DMAx_Channely
  * @retval DMAx
  */
#define __MS32_DMA_GET_INSTANCE(__CHANNEL_INSTANCE__)  (DMA1)

/**
  * @brief  Convert DMAx_Channely into MS32_DMA_CHANNEL_y
  * @param  __CHANNEL_INSTANCE__ DMAx_Channely
  * @retval MS32_DMA_CHANNEL_y
  */
#define __MS32_DMA_GET_CHANNEL(__CHANNEL_INSTANCE__)   \
(((uint32_t)(__CHANNEL_INSTANCE__) == ((uint32_t)DMA1_Channel1)) ? MS32_DMA_CHANNEL_1 : \
 ((uint32_t)(__CHANNEL_INSTANCE__) == ((uint32_t)DMA1_Channel2)) ? MS32_DMA_CHANNEL_2 : \
 ((uint32_t)(__CHANNEL_INSTANCE__) == ((uint32_t)DMA1_Channel3)) ? MS32_DMA_CHANNEL_3 : \
 ((uint32_t)(__CHANNEL_INSTANCE__) == ((uint32_t)DMA1_Channel4)) ? MS32_DMA_CHANNEL_4 : \
 MS32_DMA_CHANNEL_5)


/**
  * @brief  Convert DMA Instance DMAx and MS32_DMA_CHANNEL_y into DMAx_Channely
  * @param  __DMA_INSTANCE__ DMAx
  * @param  __CHANNEL__ MS32_DMA_CHANNEL_y
  * @retval DMAx_Channely
  */
#define __MS32_DMA_GET_CHANNEL_INSTANCE(__DMA_INSTANCE__, __CHANNEL__)   \
((((uint32_t)(__DMA_INSTANCE__) == ((uint32_t)DMA1)) && ((uint32_t)(__CHANNEL__) == ((uint32_t)MS32_DMA_CHANNEL_1))) ? DMA1_Channel1 : \
 (((uint32_t)(__DMA_INSTANCE__) == ((uint32_t)DMA1)) && ((uint32_t)(__CHANNEL__) == ((uint32_t)MS32_DMA_CHANNEL_2))) ? DMA1_Channel2 : \
 (((uint32_t)(__DMA_INSTANCE__) == ((uint32_t)DMA1)) && ((uint32_t)(__CHANNEL__) == ((uint32_t)MS32_DMA_CHANNEL_3))) ? DMA1_Channel3 : \
 (((uint32_t)(__DMA_INSTANCE__) == ((uint32_t)DMA1)) && ((uint32_t)(__CHANNEL__) == ((uint32_t)MS32_DMA_CHANNEL_4))) ? DMA1_Channel4 : \
 DMA1_Channel5)


/* Exported functions --------------------------------------------------------*/
/** @defgroup DMA_EF_Configuration Configuration
  * @{
  */

/**
  * @brief  Enable DMA channel.
  * @rmtoll CCR          EN            MS32_DMA_EnableChannel
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref MS32_DMA_CHANNEL_1
  *         @arg @ref MS32_DMA_CHANNEL_2
  *         @arg @ref MS32_DMA_CHANNEL_3
  *         @arg @ref MS32_DMA_CHANNEL_4
  *         @arg @ref MS32_DMA_CHANNEL_5
  * @retval None
  */
__STATIC_INLINE void MS32_DMA_EnableChannel(DMA_TypeDef *DMAx, uint32_t Channel) {
  SET_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR, DMA_CCR_EN);
}

/**
  * @brief  Disable DMA channel.
  * @rmtoll CCR          EN            MS32_DMA_DisableChannel
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref MS32_DMA_CHANNEL_1
  *         @arg @ref MS32_DMA_CHANNEL_2
  *         @arg @ref MS32_DMA_CHANNEL_3
  *         @arg @ref MS32_DMA_CHANNEL_4
  *         @arg @ref MS32_DMA_CHANNEL_5
  * @retval None
  */
__STATIC_INLINE void MS32_DMA_DisableChannel(DMA_TypeDef *DMAx, uint32_t Channel) {
  CLEAR_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR, DMA_CCR_EN);
}

/**
  * @brief  Check if DMA channel is enabled or disabled.
  * @rmtoll CCR          EN            MS32_DMA_IsEnabledChannel
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref MS32_DMA_CHANNEL_1
  *         @arg @ref MS32_DMA_CHANNEL_2
  *         @arg @ref MS32_DMA_CHANNEL_3
  *         @arg @ref MS32_DMA_CHANNEL_4
  *         @arg @ref MS32_DMA_CHANNEL_5
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_DMA_IsEnabledChannel(DMA_TypeDef *DMAx, uint32_t Channel) {
  return (READ_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR,
                   DMA_CCR_EN) == (DMA_CCR_EN));
}

/**
  * @brief  Configure all parameters link to DMA transfer.
  * @rmtoll CCR          DIR           MS32_DMA_ConfigTransfer\n
  *         CCR          MEM2MEM       MS32_DMA_ConfigTransfer\n
  *         CCR          CIRC          MS32_DMA_ConfigTransfer\n
  *         CCR          PINC          MS32_DMA_ConfigTransfer\n
  *         CCR          MINC          MS32_DMA_ConfigTransfer\n
  *         CCR          PSIZE         MS32_DMA_ConfigTransfer\n
  *         CCR          MSIZE         MS32_DMA_ConfigTransfer\n
  *         CCR          PL            MS32_DMA_ConfigTransfer
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref MS32_DMA_CHANNEL_1
  *         @arg @ref MS32_DMA_CHANNEL_2
  *         @arg @ref MS32_DMA_CHANNEL_3
  *         @arg @ref MS32_DMA_CHANNEL_4
  *         @arg @ref MS32_DMA_CHANNEL_5
  * @param  Configuration This parameter must be a combination of all the following values:
  *         @arg @ref MS32_DMA_DIRECTION_PERIPH_TO_MEMORY or @ref MS32_DMA_DIRECTION_MEMORY_TO_PERIPH or @ref MS32_DMA_DIRECTION_MEMORY_TO_MEMORY
  *         @arg @ref MS32_DMA_MODE_NORMAL or @ref MS32_DMA_MODE_CIRCULAR
  *         @arg @ref MS32_DMA_PERIPH_INCREMENT or @ref MS32_DMA_PERIPH_NOINCREMENT
  *         @arg @ref MS32_DMA_MEMORY_INCREMENT or @ref MS32_DMA_MEMORY_NOINCREMENT
  *         @arg @ref MS32_DMA_PDATAALIGN_BYTE or @ref MS32_DMA_PDATAALIGN_HALFWORD or @ref MS32_DMA_PDATAALIGN_WORD
  *         @arg @ref MS32_DMA_MDATAALIGN_BYTE or @ref MS32_DMA_MDATAALIGN_HALFWORD or @ref MS32_DMA_MDATAALIGN_WORD
  *         @arg @ref MS32_DMA_PRIORITY_LOW or @ref MS32_DMA_PRIORITY_MEDIUM or @ref MS32_DMA_PRIORITY_HIGH or @ref MS32_DMA_PRIORITY_VERYHIGH
  * @retval None
  */
__STATIC_INLINE void MS32_DMA_ConfigTransfer(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t Configuration) {
  MODIFY_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR,
             DMA_CCR_DIR | DMA_CCR_MEM2MEM | DMA_CCR_CIRC | DMA_CCR_PINC | DMA_CCR_MINC | DMA_CCR_PSIZE | DMA_CCR_MSIZE | DMA_CCR_PL,
             Configuration);
}

/**
  * @brief  Set Data transfer direction (read from peripheral or from memory).
  * @rmtoll CCR          DIR           MS32_DMA_SetDataTransferDirection\n
  *         CCR          MEM2MEM       MS32_DMA_SetDataTransferDirection
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref MS32_DMA_CHANNEL_1
  *         @arg @ref MS32_DMA_CHANNEL_2
  *         @arg @ref MS32_DMA_CHANNEL_3
  *         @arg @ref MS32_DMA_CHANNEL_4
  *         @arg @ref MS32_DMA_CHANNEL_5
  * @param  Direction This parameter can be one of the following values:
  *         @arg @ref MS32_DMA_DIRECTION_PERIPH_TO_MEMORY
  *         @arg @ref MS32_DMA_DIRECTION_MEMORY_TO_PERIPH
  *         @arg @ref MS32_DMA_DIRECTION_MEMORY_TO_MEMORY
  * @retval None
  */
__STATIC_INLINE void MS32_DMA_SetDataTransferDirection(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t Direction) {
  MODIFY_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR,
             DMA_CCR_DIR | DMA_CCR_MEM2MEM, Direction);
}

/**
  * @brief  Get Data transfer direction (read from peripheral or from memory).
  * @rmtoll CCR          DIR           MS32_DMA_GetDataTransferDirection\n
  *         CCR          MEM2MEM       MS32_DMA_GetDataTransferDirection
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref MS32_DMA_CHANNEL_1
  *         @arg @ref MS32_DMA_CHANNEL_2
  *         @arg @ref MS32_DMA_CHANNEL_3
  *         @arg @ref MS32_DMA_CHANNEL_4
  *         @arg @ref MS32_DMA_CHANNEL_5
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_DMA_DIRECTION_PERIPH_TO_MEMORY
  *         @arg @ref MS32_DMA_DIRECTION_MEMORY_TO_PERIPH
  *         @arg @ref MS32_DMA_DIRECTION_MEMORY_TO_MEMORY
  */
__STATIC_INLINE uint32_t MS32_DMA_GetDataTransferDirection(DMA_TypeDef *DMAx, uint32_t Channel) {
  return (READ_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR,
                   DMA_CCR_DIR | DMA_CCR_MEM2MEM));
}

/**
  * @brief  Set DMA mode circular or normal.
  * @note The circular buffer mode cannot be used if the memory-to-memory
  * data transfer is configured on the selected Channel.
  * @rmtoll CCR          CIRC          MS32_DMA_SetMode
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref MS32_DMA_CHANNEL_1
  *         @arg @ref MS32_DMA_CHANNEL_2
  *         @arg @ref MS32_DMA_CHANNEL_3
  *         @arg @ref MS32_DMA_CHANNEL_4
  *         @arg @ref MS32_DMA_CHANNEL_5
  * @param  Mode This parameter can be one of the following values:
  *         @arg @ref MS32_DMA_MODE_NORMAL
  *         @arg @ref MS32_DMA_MODE_CIRCULAR
  * @retval None
  */
__STATIC_INLINE void MS32_DMA_SetMode(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t Mode) {
  MODIFY_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR, DMA_CCR_CIRC,
             Mode);
}

/**
  * @brief  Get DMA mode circular or normal.
  * @rmtoll CCR          CIRC          MS32_DMA_GetMode
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref MS32_DMA_CHANNEL_1
  *         @arg @ref MS32_DMA_CHANNEL_2
  *         @arg @ref MS32_DMA_CHANNEL_3
  *         @arg @ref MS32_DMA_CHANNEL_4
  *         @arg @ref MS32_DMA_CHANNEL_5
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_DMA_MODE_NORMAL
  *         @arg @ref MS32_DMA_MODE_CIRCULAR
  */
__STATIC_INLINE uint32_t MS32_DMA_GetMode(DMA_TypeDef *DMAx, uint32_t Channel) {
  return (READ_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR,
                   DMA_CCR_CIRC));
}

/**
  * @brief  Set Peripheral increment mode.
  * @rmtoll CCR          PINC          MS32_DMA_SetPeriphIncMode
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref MS32_DMA_CHANNEL_1
  *         @arg @ref MS32_DMA_CHANNEL_2
  *         @arg @ref MS32_DMA_CHANNEL_3
  *         @arg @ref MS32_DMA_CHANNEL_4
  *         @arg @ref MS32_DMA_CHANNEL_5
  * @param  PeriphOrM2MSrcIncMode This parameter can be one of the following values:
  *         @arg @ref MS32_DMA_PERIPH_INCREMENT
  *         @arg @ref MS32_DMA_PERIPH_NOINCREMENT
  * @retval None
  */
__STATIC_INLINE void MS32_DMA_SetPeriphIncMode(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t PeriphOrM2MSrcIncMode) {
  MODIFY_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR, DMA_CCR_PINC,
             PeriphOrM2MSrcIncMode);
}

/**
  * @brief  Get Peripheral increment mode.
  * @rmtoll CCR          PINC          MS32_DMA_GetPeriphIncMode
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref MS32_DMA_CHANNEL_1
  *         @arg @ref MS32_DMA_CHANNEL_2
  *         @arg @ref MS32_DMA_CHANNEL_3
  *         @arg @ref MS32_DMA_CHANNEL_4
  *         @arg @ref MS32_DMA_CHANNEL_5
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_DMA_PERIPH_INCREMENT
  *         @arg @ref MS32_DMA_PERIPH_NOINCREMENT
  */
__STATIC_INLINE uint32_t MS32_DMA_GetPeriphIncMode(DMA_TypeDef *DMAx, uint32_t Channel) {
  return (READ_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR,
                   DMA_CCR_PINC));
}

/**
  * @brief  Set Memory increment mode.
  * @rmtoll CCR          MINC          MS32_DMA_SetMemoryIncMode
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref MS32_DMA_CHANNEL_1
  *         @arg @ref MS32_DMA_CHANNEL_2
  *         @arg @ref MS32_DMA_CHANNEL_3
  *         @arg @ref MS32_DMA_CHANNEL_4
  *         @arg @ref MS32_DMA_CHANNEL_5
  * @param  MemoryOrM2MDstIncMode This parameter can be one of the following values:
  *         @arg @ref MS32_DMA_MEMORY_INCREMENT
  *         @arg @ref MS32_DMA_MEMORY_NOINCREMENT
  * @retval None
  */
__STATIC_INLINE void MS32_DMA_SetMemoryIncMode(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t MemoryOrM2MDstIncMode) {
  MODIFY_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR, DMA_CCR_MINC,
             MemoryOrM2MDstIncMode);
}

/**
  * @brief  Get Memory increment mode.
  * @rmtoll CCR          MINC          MS32_DMA_GetMemoryIncMode
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref MS32_DMA_CHANNEL_1
  *         @arg @ref MS32_DMA_CHANNEL_2
  *         @arg @ref MS32_DMA_CHANNEL_3
  *         @arg @ref MS32_DMA_CHANNEL_4
  *         @arg @ref MS32_DMA_CHANNEL_5
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_DMA_MEMORY_INCREMENT
  *         @arg @ref MS32_DMA_MEMORY_NOINCREMENT
  */
__STATIC_INLINE uint32_t MS32_DMA_GetMemoryIncMode(DMA_TypeDef *DMAx, uint32_t Channel) {
  return (READ_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR,
                   DMA_CCR_MINC));
}

/**
  * @brief  Set Peripheral size.
  * @rmtoll CCR          PSIZE         MS32_DMA_SetPeriphSize
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref MS32_DMA_CHANNEL_1
  *         @arg @ref MS32_DMA_CHANNEL_2
  *         @arg @ref MS32_DMA_CHANNEL_3
  *         @arg @ref MS32_DMA_CHANNEL_4
  *         @arg @ref MS32_DMA_CHANNEL_5
  * @param  PeriphOrM2MSrcDataSize This parameter can be one of the following values:
  *         @arg @ref MS32_DMA_PDATAALIGN_BYTE
  *         @arg @ref MS32_DMA_PDATAALIGN_HALFWORD
  *         @arg @ref MS32_DMA_PDATAALIGN_WORD
  * @retval None
  */
__STATIC_INLINE void MS32_DMA_SetPeriphSize(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t PeriphOrM2MSrcDataSize) {
  MODIFY_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR, DMA_CCR_PSIZE,
             PeriphOrM2MSrcDataSize);
}

/**
  * @brief  Get Peripheral size.
  * @rmtoll CCR          PSIZE         MS32_DMA_GetPeriphSize
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref MS32_DMA_CHANNEL_1
  *         @arg @ref MS32_DMA_CHANNEL_2
  *         @arg @ref MS32_DMA_CHANNEL_3
  *         @arg @ref MS32_DMA_CHANNEL_4
  *         @arg @ref MS32_DMA_CHANNEL_5
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_DMA_PDATAALIGN_BYTE
  *         @arg @ref MS32_DMA_PDATAALIGN_HALFWORD
  *         @arg @ref MS32_DMA_PDATAALIGN_WORD
  */
__STATIC_INLINE uint32_t MS32_DMA_GetPeriphSize(DMA_TypeDef *DMAx, uint32_t Channel) {
  return (READ_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR,
                   DMA_CCR_PSIZE));
}

/**
  * @brief  Set Memory size.
  * @rmtoll CCR          MSIZE         MS32_DMA_SetMemorySize
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref MS32_DMA_CHANNEL_1
  *         @arg @ref MS32_DMA_CHANNEL_2
  *         @arg @ref MS32_DMA_CHANNEL_3
  *         @arg @ref MS32_DMA_CHANNEL_4
  *         @arg @ref MS32_DMA_CHANNEL_5
  * @param  MemoryOrM2MDstDataSize This parameter can be one of the following values:
  *         @arg @ref MS32_DMA_MDATAALIGN_BYTE
  *         @arg @ref MS32_DMA_MDATAALIGN_HALFWORD
  *         @arg @ref MS32_DMA_MDATAALIGN_WORD
  * @retval None
  */
__STATIC_INLINE void MS32_DMA_SetMemorySize(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t MemoryOrM2MDstDataSize) {
  MODIFY_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR, DMA_CCR_MSIZE,
             MemoryOrM2MDstDataSize);
}

/**
  * @brief  Get Memory size.
  * @rmtoll CCR          MSIZE         MS32_DMA_GetMemorySize
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref MS32_DMA_CHANNEL_1
  *         @arg @ref MS32_DMA_CHANNEL_2
  *         @arg @ref MS32_DMA_CHANNEL_3
  *         @arg @ref MS32_DMA_CHANNEL_4
  *         @arg @ref MS32_DMA_CHANNEL_5
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_DMA_MDATAALIGN_BYTE
  *         @arg @ref MS32_DMA_MDATAALIGN_HALFWORD
  *         @arg @ref MS32_DMA_MDATAALIGN_WORD
  */
__STATIC_INLINE uint32_t MS32_DMA_GetMemorySize(DMA_TypeDef *DMAx, uint32_t Channel) {
  return (READ_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR,
                   DMA_CCR_MSIZE));
}

/**
  * @brief  Set Channel priority level.
  * @rmtoll CCR          PL            MS32_DMA_SetChannelPriorityLevel
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref MS32_DMA_CHANNEL_1
  *         @arg @ref MS32_DMA_CHANNEL_2
  *         @arg @ref MS32_DMA_CHANNEL_3
  *         @arg @ref MS32_DMA_CHANNEL_4
  *         @arg @ref MS32_DMA_CHANNEL_5
  * @param  Priority This parameter can be one of the following values:
  *         @arg @ref MS32_DMA_PRIORITY_LOW
  *         @arg @ref MS32_DMA_PRIORITY_MEDIUM
  *         @arg @ref MS32_DMA_PRIORITY_HIGH
  *         @arg @ref MS32_DMA_PRIORITY_VERYHIGH
  * @retval None
  */
__STATIC_INLINE void MS32_DMA_SetChannelPriorityLevel(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t Priority) {
  MODIFY_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR, DMA_CCR_PL,
             Priority);
}

/**
  * @brief  Get Channel priority level.
  * @rmtoll CCR          PL            MS32_DMA_GetChannelPriorityLevel
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref MS32_DMA_CHANNEL_1
  *         @arg @ref MS32_DMA_CHANNEL_2
  *         @arg @ref MS32_DMA_CHANNEL_3
  *         @arg @ref MS32_DMA_CHANNEL_4
  *         @arg @ref MS32_DMA_CHANNEL_5
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_DMA_PRIORITY_LOW
  *         @arg @ref MS32_DMA_PRIORITY_MEDIUM
  *         @arg @ref MS32_DMA_PRIORITY_HIGH
  *         @arg @ref MS32_DMA_PRIORITY_VERYHIGH
  */
__STATIC_INLINE uint32_t MS32_DMA_GetChannelPriorityLevel(DMA_TypeDef *DMAx, uint32_t Channel) {
  return (READ_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR,
                   DMA_CCR_PL));
}

/**
  * @brief  Set Number of data to transfer.
  * @note   This action has no effect if
  *         channel is enabled.
  * @rmtoll CNDTR        NDT           MS32_DMA_SetDataLength
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
__STATIC_INLINE void MS32_DMA_SetDataLength(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t NbData) {
  MODIFY_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CNDTR,
             DMA_CNDTR_NDT, NbData);
}

/**
  * @brief  Get Number of data to transfer.
  * @note   Once the channel is enabled, the return value indicate the
  *         remaining bytes to be transmitted.
  * @rmtoll CNDTR        NDT           MS32_DMA_GetDataLength
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref MS32_DMA_CHANNEL_1
  *         @arg @ref MS32_DMA_CHANNEL_2
  *         @arg @ref MS32_DMA_CHANNEL_3
  *         @arg @ref MS32_DMA_CHANNEL_4
  *         @arg @ref MS32_DMA_CHANNEL_5
  * @retval Between Min_Data = 0 and Max_Data = 0xFFFFFFFF
  */
__STATIC_INLINE uint32_t MS32_DMA_GetDataLength(DMA_TypeDef *DMAx, uint32_t Channel) {
  return (READ_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CNDTR,
                   DMA_CNDTR_NDT));
}

/**
  * @brief  Configure the Source and Destination addresses.
  * @note   This API must not be called when the DMA channel is enabled.
  * @note   Each IP using DMA provides an API to get directly the register adress (MS32_PPP_DMA_GetRegAddr).
  * @rmtoll CPAR         PA            MS32_DMA_ConfigAddresses\n
  *         CMAR         MA            MS32_DMA_ConfigAddresses
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref MS32_DMA_CHANNEL_1
  *         @arg @ref MS32_DMA_CHANNEL_2
  *         @arg @ref MS32_DMA_CHANNEL_3
  *         @arg @ref MS32_DMA_CHANNEL_4
  *         @arg @ref MS32_DMA_CHANNEL_5
  * @param  SrcAddress Between Min_Data = 0 and Max_Data = 0xFFFFFFFF
  * @param  DstAddress Between Min_Data = 0 and Max_Data = 0xFFFFFFFF
  * @param  Direction This parameter can be one of the following values:
  *         @arg @ref MS32_DMA_DIRECTION_PERIPH_TO_MEMORY
  *         @arg @ref MS32_DMA_DIRECTION_MEMORY_TO_PERIPH
  *         @arg @ref MS32_DMA_DIRECTION_MEMORY_TO_MEMORY
  * @retval None
  */
__STATIC_INLINE void MS32_DMA_ConfigAddresses(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t SrcAddress,
                                            uint32_t DstAddress, uint32_t Direction) {
  /* Direction Memory to Periph */
  if (Direction == MS32_DMA_DIRECTION_MEMORY_TO_PERIPH) {
    WRITE_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CMAR, SrcAddress);
    WRITE_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CPAR, DstAddress);
  } else {
  /* Direction Periph to Memory and Memory to Memory */
    WRITE_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CPAR, SrcAddress);
    WRITE_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CMAR, DstAddress);
  }
}

/**
  * @brief  Set the Memory address.
  * @note   Interface used for direction MS32_DMA_DIRECTION_PERIPH_TO_MEMORY or MS32_DMA_DIRECTION_MEMORY_TO_PERIPH only.
  * @note   This API must not be called when the DMA channel is enabled.
  * @rmtoll CMAR         MA            MS32_DMA_SetMemoryAddress
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref MS32_DMA_CHANNEL_1
  *         @arg @ref MS32_DMA_CHANNEL_2
  *         @arg @ref MS32_DMA_CHANNEL_3
  *         @arg @ref MS32_DMA_CHANNEL_4
  *         @arg @ref MS32_DMA_CHANNEL_5
  * @param  MemoryAddress Between Min_Data = 0 and Max_Data = 0xFFFFFFFF
  * @retval None
  */
__STATIC_INLINE void MS32_DMA_SetMemoryAddress(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t MemoryAddress) {
  WRITE_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CMAR, MemoryAddress);
}

/**
  * @brief  Set the Peripheral address.
  * @note   Interface used for direction MS32_DMA_DIRECTION_PERIPH_TO_MEMORY or MS32_DMA_DIRECTION_MEMORY_TO_PERIPH only.
  * @note   This API must not be called when the DMA channel is enabled.
  * @rmtoll CPAR         PA            MS32_DMA_SetPeriphAddress
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref MS32_DMA_CHANNEL_1
  *         @arg @ref MS32_DMA_CHANNEL_2
  *         @arg @ref MS32_DMA_CHANNEL_3
  *         @arg @ref MS32_DMA_CHANNEL_4
  *         @arg @ref MS32_DMA_CHANNEL_5
  * @param  PeriphAddress Between Min_Data = 0 and Max_Data = 0xFFFFFFFF
  * @retval None
  */
__STATIC_INLINE void MS32_DMA_SetPeriphAddress(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t PeriphAddress) {
  WRITE_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CPAR, PeriphAddress);
}

/**
  * @brief  Get Memory address.
  * @note   Interface used for direction MS32_DMA_DIRECTION_PERIPH_TO_MEMORY or MS32_DMA_DIRECTION_MEMORY_TO_PERIPH only.
  * @rmtoll CMAR         MA            MS32_DMA_GetMemoryAddress
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref MS32_DMA_CHANNEL_1
  *         @arg @ref MS32_DMA_CHANNEL_2
  *         @arg @ref MS32_DMA_CHANNEL_3
  *         @arg @ref MS32_DMA_CHANNEL_4
  *         @arg @ref MS32_DMA_CHANNEL_5
  * @retval Between Min_Data = 0 and Max_Data = 0xFFFFFFFF
  */
__STATIC_INLINE uint32_t MS32_DMA_GetMemoryAddress(DMA_TypeDef *DMAx, uint32_t Channel) {
  return (READ_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CMAR));
}

/**
  * @brief  Get Peripheral address.
  * @note   Interface used for direction MS32_DMA_DIRECTION_PERIPH_TO_MEMORY or MS32_DMA_DIRECTION_MEMORY_TO_PERIPH only.
  * @rmtoll CPAR         PA            MS32_DMA_GetPeriphAddress
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref MS32_DMA_CHANNEL_1
  *         @arg @ref MS32_DMA_CHANNEL_2
  *         @arg @ref MS32_DMA_CHANNEL_3
  *         @arg @ref MS32_DMA_CHANNEL_4
  *         @arg @ref MS32_DMA_CHANNEL_5
  * @retval Between Min_Data = 0 and Max_Data = 0xFFFFFFFF
  */
__STATIC_INLINE uint32_t MS32_DMA_GetPeriphAddress(DMA_TypeDef *DMAx, uint32_t Channel) {
  return (READ_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CPAR));
}

/**
  * @brief  Set the Memory to Memory Source address.
  * @note   Interface used for direction MS32_DMA_DIRECTION_MEMORY_TO_MEMORY only.
  * @note   This API must not be called when the DMA channel is enabled.
  * @rmtoll CPAR         PA            MS32_DMA_SetM2MSrcAddress
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref MS32_DMA_CHANNEL_1
  *         @arg @ref MS32_DMA_CHANNEL_2
  *         @arg @ref MS32_DMA_CHANNEL_3
  *         @arg @ref MS32_DMA_CHANNEL_4
  *         @arg @ref MS32_DMA_CHANNEL_5
  * @param  MemoryAddress Between Min_Data = 0 and Max_Data = 0xFFFFFFFF
  * @retval None
  */
__STATIC_INLINE void MS32_DMA_SetM2MSrcAddress(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t MemoryAddress) {
  WRITE_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CPAR, MemoryAddress);
}

/**
  * @brief  Set the Memory to Memory Destination address.
  * @note   Interface used for direction MS32_DMA_DIRECTION_MEMORY_TO_MEMORY only.
  * @note   This API must not be called when the DMA channel is enabled.
  * @rmtoll CMAR         MA            MS32_DMA_SetM2MDstAddress
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref MS32_DMA_CHANNEL_1
  *         @arg @ref MS32_DMA_CHANNEL_2
  *         @arg @ref MS32_DMA_CHANNEL_3
  *         @arg @ref MS32_DMA_CHANNEL_4
  *         @arg @ref MS32_DMA_CHANNEL_5
  * @param  MemoryAddress Between Min_Data = 0 and Max_Data = 0xFFFFFFFF
  * @retval None
  */
__STATIC_INLINE void MS32_DMA_SetM2MDstAddress(DMA_TypeDef *DMAx, uint32_t Channel, uint32_t MemoryAddress) {
  WRITE_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CMAR, MemoryAddress);
}

/**
  * @brief  Get the Memory to Memory Source address.
  * @note   Interface used for direction MS32_DMA_DIRECTION_MEMORY_TO_MEMORY only.
  * @rmtoll CPAR         PA            MS32_DMA_GetM2MSrcAddress
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref MS32_DMA_CHANNEL_1
  *         @arg @ref MS32_DMA_CHANNEL_2
  *         @arg @ref MS32_DMA_CHANNEL_3
  *         @arg @ref MS32_DMA_CHANNEL_4
  *         @arg @ref MS32_DMA_CHANNEL_5
  * @retval Between Min_Data = 0 and Max_Data = 0xFFFFFFFF
  */
__STATIC_INLINE uint32_t MS32_DMA_GetM2MSrcAddress(DMA_TypeDef *DMAx, uint32_t Channel) {
  return (READ_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CPAR));
}

/**
  * @brief  Get the Memory to Memory Destination address.
  * @note   Interface used for direction MS32_DMA_DIRECTION_MEMORY_TO_MEMORY only.
  * @rmtoll CMAR         MA            MS32_DMA_GetM2MDstAddress
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref MS32_DMA_CHANNEL_1
  *         @arg @ref MS32_DMA_CHANNEL_2
  *         @arg @ref MS32_DMA_CHANNEL_3
  *         @arg @ref MS32_DMA_CHANNEL_4
  *         @arg @ref MS32_DMA_CHANNEL_5
  * @retval Between Min_Data = 0 and Max_Data = 0xFFFFFFFF
  */
__STATIC_INLINE uint32_t MS32_DMA_GetM2MDstAddress(DMA_TypeDef *DMAx, uint32_t Channel) {
  return (READ_REG(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CMAR));
}


/** @defgroup DMA_EF_FLAG_Management FLAG_Management
  * @{
  */

/**
  * @brief  Get Channel 1 global interrupt flag.
  * @rmtoll ISR          GIF1          MS32_DMA_IsActiveFlag_GI1
  * @param  DMAx DMAx Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_DMA_IsActiveFlag_GI1(DMA_TypeDef *DMAx) {
  return (READ_BIT(DMAx->ISR, DMA_ISR_GIF1) == (DMA_ISR_GIF1));
}

/**
  * @brief  Get Channel 2 global interrupt flag.
  * @rmtoll ISR          GIF2          MS32_DMA_IsActiveFlag_GI2
  * @param  DMAx DMAx Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_DMA_IsActiveFlag_GI2(DMA_TypeDef *DMAx) {
  return (READ_BIT(DMAx->ISR, DMA_ISR_GIF2) == (DMA_ISR_GIF2));
}

/**
  * @brief  Get Channel 3 global interrupt flag.
  * @rmtoll ISR          GIF3          MS32_DMA_IsActiveFlag_GI3
  * @param  DMAx DMAx Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_DMA_IsActiveFlag_GI3(DMA_TypeDef *DMAx) {
  return (READ_BIT(DMAx->ISR, DMA_ISR_GIF3) == (DMA_ISR_GIF3));
}

/**
  * @brief  Get Channel 4 global interrupt flag.
  * @rmtoll ISR          GIF4          MS32_DMA_IsActiveFlag_GI4
  * @param  DMAx DMAx Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_DMA_IsActiveFlag_GI4(DMA_TypeDef *DMAx) {
  return (READ_BIT(DMAx->ISR, DMA_ISR_GIF4) == (DMA_ISR_GIF4));
}

/**
  * @brief  Get Channel 5 global interrupt flag.
  * @rmtoll ISR          GIF5          MS32_DMA_IsActiveFlag_GI5
  * @param  DMAx DMAx Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_DMA_IsActiveFlag_GI5(DMA_TypeDef *DMAx) {
  return (READ_BIT(DMAx->ISR, DMA_ISR_GIF5) == (DMA_ISR_GIF5));
}

/**
  * @brief  Get Channel 1 transfer complete flag.
  * @rmtoll ISR          TCIF1         MS32_DMA_IsActiveFlag_TC1
  * @param  DMAx DMAx Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_DMA_IsActiveFlag_TC1(DMA_TypeDef *DMAx) {
  return (READ_BIT(DMAx->ISR, DMA_ISR_TCIF1) == (DMA_ISR_TCIF1));
}

/**
  * @brief  Get Channel 2 transfer complete flag.
  * @rmtoll ISR          TCIF2         MS32_DMA_IsActiveFlag_TC2
  * @param  DMAx DMAx Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_DMA_IsActiveFlag_TC2(DMA_TypeDef *DMAx) {
  return (READ_BIT(DMAx->ISR, DMA_ISR_TCIF2) == (DMA_ISR_TCIF2));
}

/**
  * @brief  Get Channel 3 transfer complete flag.
  * @rmtoll ISR          TCIF3         MS32_DMA_IsActiveFlag_TC3
  * @param  DMAx DMAx Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_DMA_IsActiveFlag_TC3(DMA_TypeDef *DMAx) {
  return (READ_BIT(DMAx->ISR, DMA_ISR_TCIF3) == (DMA_ISR_TCIF3));
}

/**
  * @brief  Get Channel 4 transfer complete flag.
  * @rmtoll ISR          TCIF4         MS32_DMA_IsActiveFlag_TC4
  * @param  DMAx DMAx Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_DMA_IsActiveFlag_TC4(DMA_TypeDef *DMAx) {
  return (READ_BIT(DMAx->ISR, DMA_ISR_TCIF4) == (DMA_ISR_TCIF4));
}

/**
  * @brief  Get Channel 5 transfer complete flag.
  * @rmtoll ISR          TCIF5         MS32_DMA_IsActiveFlag_TC5
  * @param  DMAx DMAx Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_DMA_IsActiveFlag_TC5(DMA_TypeDef *DMAx) {
  return (READ_BIT(DMAx->ISR, DMA_ISR_TCIF5) == (DMA_ISR_TCIF5));
}

/**
  * @brief  Get Channel 1 half transfer flag.
  * @rmtoll ISR          HTIF1         MS32_DMA_IsActiveFlag_HT1
  * @param  DMAx DMAx Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_DMA_IsActiveFlag_HT1(DMA_TypeDef *DMAx) {
  return (READ_BIT(DMAx->ISR, DMA_ISR_HTIF1) == (DMA_ISR_HTIF1));
}

/**
  * @brief  Get Channel 2 half transfer flag.
  * @rmtoll ISR          HTIF2         MS32_DMA_IsActiveFlag_HT2
  * @param  DMAx DMAx Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_DMA_IsActiveFlag_HT2(DMA_TypeDef *DMAx) {
  return (READ_BIT(DMAx->ISR, DMA_ISR_HTIF2) == (DMA_ISR_HTIF2));
}

/**
  * @brief  Get Channel 3 half transfer flag.
  * @rmtoll ISR          HTIF3         MS32_DMA_IsActiveFlag_HT3
  * @param  DMAx DMAx Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_DMA_IsActiveFlag_HT3(DMA_TypeDef *DMAx) {
  return (READ_BIT(DMAx->ISR, DMA_ISR_HTIF3) == (DMA_ISR_HTIF3));
}

/**
  * @brief  Get Channel 4 half transfer flag.
  * @rmtoll ISR          HTIF4         MS32_DMA_IsActiveFlag_HT4
  * @param  DMAx DMAx Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_DMA_IsActiveFlag_HT4(DMA_TypeDef *DMAx) {
  return (READ_BIT(DMAx->ISR, DMA_ISR_HTIF4) == (DMA_ISR_HTIF4));
}

/**
  * @brief  Get Channel 5 half transfer flag.
  * @rmtoll ISR          HTIF5         MS32_DMA_IsActiveFlag_HT5
  * @param  DMAx DMAx Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_DMA_IsActiveFlag_HT5(DMA_TypeDef *DMAx) {
  return (READ_BIT(DMAx->ISR, DMA_ISR_HTIF5) == (DMA_ISR_HTIF5));
}

/**
  * @brief  Get Channel 1 transfer error flag.
  * @rmtoll ISR          TEIF1         MS32_DMA_IsActiveFlag_TE1
  * @param  DMAx DMAx Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_DMA_IsActiveFlag_TE1(DMA_TypeDef *DMAx) {
  return (READ_BIT(DMAx->ISR, DMA_ISR_TEIF1) == (DMA_ISR_TEIF1));
}

/**
  * @brief  Get Channel 2 transfer error flag.
  * @rmtoll ISR          TEIF2         MS32_DMA_IsActiveFlag_TE2
  * @param  DMAx DMAx Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_DMA_IsActiveFlag_TE2(DMA_TypeDef *DMAx) {
  return (READ_BIT(DMAx->ISR, DMA_ISR_TEIF2) == (DMA_ISR_TEIF2));
}

/**
  * @brief  Get Channel 3 transfer error flag.
  * @rmtoll ISR          TEIF3         MS32_DMA_IsActiveFlag_TE3
  * @param  DMAx DMAx Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_DMA_IsActiveFlag_TE3(DMA_TypeDef *DMAx) {
  return (READ_BIT(DMAx->ISR, DMA_ISR_TEIF3) == (DMA_ISR_TEIF3));
}

/**
  * @brief  Get Channel 4 transfer error flag.
  * @rmtoll ISR          TEIF4         MS32_DMA_IsActiveFlag_TE4
  * @param  DMAx DMAx Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_DMA_IsActiveFlag_TE4(DMA_TypeDef *DMAx) {
  return (READ_BIT(DMAx->ISR, DMA_ISR_TEIF4) == (DMA_ISR_TEIF4));
}

/**
  * @brief  Get Channel 5 transfer error flag.
  * @rmtoll ISR          TEIF5         MS32_DMA_IsActiveFlag_TE5
  * @param  DMAx DMAx Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_DMA_IsActiveFlag_TE5(DMA_TypeDef *DMAx) {
  return (READ_BIT(DMAx->ISR, DMA_ISR_TEIF5) == (DMA_ISR_TEIF5));
}

/**
  * @brief  Clear Channel 1 global interrupt flag.
  * @rmtoll IFCR         CGIF1         MS32_DMA_ClearFlag_GI1
  * @param  DMAx DMAx Instance
  * @retval None
  */
__STATIC_INLINE void MS32_DMA_ClearFlag_GI1(DMA_TypeDef *DMAx) {
  WRITE_REG(DMAx->IFCR, DMA_IFCR_CGIF1);
}

/**
  * @brief  Clear Channel 2 global interrupt flag.
  * @rmtoll IFCR         CGIF2         MS32_DMA_ClearFlag_GI2
  * @param  DMAx DMAx Instance
  * @retval None
  */
__STATIC_INLINE void MS32_DMA_ClearFlag_GI2(DMA_TypeDef *DMAx) {
  WRITE_REG(DMAx->IFCR, DMA_IFCR_CGIF2);
}

/**
  * @brief  Clear Channel 3 global interrupt flag.
  * @rmtoll IFCR         CGIF3         MS32_DMA_ClearFlag_GI3
  * @param  DMAx DMAx Instance
  * @retval None
  */
__STATIC_INLINE void MS32_DMA_ClearFlag_GI3(DMA_TypeDef *DMAx) {
  WRITE_REG(DMAx->IFCR, DMA_IFCR_CGIF3);
}

/**
  * @brief  Clear Channel 4 global interrupt flag.
  * @rmtoll IFCR         CGIF4         MS32_DMA_ClearFlag_GI4
  * @param  DMAx DMAx Instance
  * @retval None
  */
__STATIC_INLINE void MS32_DMA_ClearFlag_GI4(DMA_TypeDef *DMAx) {
  WRITE_REG(DMAx->IFCR, DMA_IFCR_CGIF4);
}

/**
  * @brief  Clear Channel 5 global interrupt flag.
  * @rmtoll IFCR         CGIF5         MS32_DMA_ClearFlag_GI5
  * @param  DMAx DMAx Instance
  * @retval None
  */
__STATIC_INLINE void MS32_DMA_ClearFlag_GI5(DMA_TypeDef *DMAx) {
  WRITE_REG(DMAx->IFCR, DMA_IFCR_CGIF5);
}

/**
  * @brief  Clear Channel 1  transfer complete flag.
  * @rmtoll IFCR         CTCIF1        MS32_DMA_ClearFlag_TC1
  * @param  DMAx DMAx Instance
  * @retval None
  */
__STATIC_INLINE void MS32_DMA_ClearFlag_TC1(DMA_TypeDef *DMAx) {
  WRITE_REG(DMAx->IFCR, DMA_IFCR_CTCIF1);
}

/**
  * @brief  Clear Channel 2  transfer complete flag.
  * @rmtoll IFCR         CTCIF2        MS32_DMA_ClearFlag_TC2
  * @param  DMAx DMAx Instance
  * @retval None
  */
__STATIC_INLINE void MS32_DMA_ClearFlag_TC2(DMA_TypeDef *DMAx) {
  WRITE_REG(DMAx->IFCR, DMA_IFCR_CTCIF2);
}

/**
  * @brief  Clear Channel 3  transfer complete flag.
  * @rmtoll IFCR         CTCIF3        MS32_DMA_ClearFlag_TC3
  * @param  DMAx DMAx Instance
  * @retval None
  */
__STATIC_INLINE void MS32_DMA_ClearFlag_TC3(DMA_TypeDef *DMAx) {
  WRITE_REG(DMAx->IFCR, DMA_IFCR_CTCIF3);
}

/**
  * @brief  Clear Channel 4  transfer complete flag.
  * @rmtoll IFCR         CTCIF4        MS32_DMA_ClearFlag_TC4
  * @param  DMAx DMAx Instance
  * @retval None
  */
__STATIC_INLINE void MS32_DMA_ClearFlag_TC4(DMA_TypeDef *DMAx) {
  WRITE_REG(DMAx->IFCR, DMA_IFCR_CTCIF4);
}

/**
  * @brief  Clear Channel 5  transfer complete flag.
  * @rmtoll IFCR         CTCIF5        MS32_DMA_ClearFlag_TC5
  * @param  DMAx DMAx Instance
  * @retval None
  */
__STATIC_INLINE void MS32_DMA_ClearFlag_TC5(DMA_TypeDef *DMAx) {
  WRITE_REG(DMAx->IFCR, DMA_IFCR_CTCIF5);
}

/**
  * @brief  Clear Channel 1  half transfer flag.
  * @rmtoll IFCR         CHTIF1        MS32_DMA_ClearFlag_HT1
  * @param  DMAx DMAx Instance
  * @retval None
  */
__STATIC_INLINE void MS32_DMA_ClearFlag_HT1(DMA_TypeDef *DMAx) {
  WRITE_REG(DMAx->IFCR, DMA_IFCR_CHTIF1);
}

/**
  * @brief  Clear Channel 2  half transfer flag.
  * @rmtoll IFCR         CHTIF2        MS32_DMA_ClearFlag_HT2
  * @param  DMAx DMAx Instance
  * @retval None
  */
__STATIC_INLINE void MS32_DMA_ClearFlag_HT2(DMA_TypeDef *DMAx) {
  WRITE_REG(DMAx->IFCR, DMA_IFCR_CHTIF2);
}

/**
  * @brief  Clear Channel 3  half transfer flag.
  * @rmtoll IFCR         CHTIF3        MS32_DMA_ClearFlag_HT3
  * @param  DMAx DMAx Instance
  * @retval None
  */
__STATIC_INLINE void MS32_DMA_ClearFlag_HT3(DMA_TypeDef *DMAx) {
  WRITE_REG(DMAx->IFCR, DMA_IFCR_CHTIF3);
}

/**
  * @brief  Clear Channel 4  half transfer flag.
  * @rmtoll IFCR         CHTIF4        MS32_DMA_ClearFlag_HT4
  * @param  DMAx DMAx Instance
  * @retval None
  */
__STATIC_INLINE void MS32_DMA_ClearFlag_HT4(DMA_TypeDef *DMAx) {
  WRITE_REG(DMAx->IFCR, DMA_IFCR_CHTIF4);
}

/**
  * @brief  Clear Channel 5  half transfer flag.
  * @rmtoll IFCR         CHTIF5        MS32_DMA_ClearFlag_HT5
  * @param  DMAx DMAx Instance
  * @retval None
  */
__STATIC_INLINE void MS32_DMA_ClearFlag_HT5(DMA_TypeDef *DMAx) {
  WRITE_REG(DMAx->IFCR, DMA_IFCR_CHTIF5);
}

/**
  * @brief  Clear Channel 1 transfer error flag.
  * @rmtoll IFCR         CTEIF1        MS32_DMA_ClearFlag_TE1
  * @param  DMAx DMAx Instance
  * @retval None
  */
__STATIC_INLINE void MS32_DMA_ClearFlag_TE1(DMA_TypeDef *DMAx) {
  WRITE_REG(DMAx->IFCR, DMA_IFCR_CTEIF1);
}

/**
  * @brief  Clear Channel 2 transfer error flag.
  * @rmtoll IFCR         CTEIF2        MS32_DMA_ClearFlag_TE2
  * @param  DMAx DMAx Instance
  * @retval None
  */
__STATIC_INLINE void MS32_DMA_ClearFlag_TE2(DMA_TypeDef *DMAx) {
  WRITE_REG(DMAx->IFCR, DMA_IFCR_CTEIF2);
}

/**
  * @brief  Clear Channel 3 transfer error flag.
  * @rmtoll IFCR         CTEIF3        MS32_DMA_ClearFlag_TE3
  * @param  DMAx DMAx Instance
  * @retval None
  */
__STATIC_INLINE void MS32_DMA_ClearFlag_TE3(DMA_TypeDef *DMAx) {
  WRITE_REG(DMAx->IFCR, DMA_IFCR_CTEIF3);
}

/**
  * @brief  Clear Channel 4 transfer error flag.
  * @rmtoll IFCR         CTEIF4        MS32_DMA_ClearFlag_TE4
  * @param  DMAx DMAx Instance
  * @retval None
  */
__STATIC_INLINE void MS32_DMA_ClearFlag_TE4(DMA_TypeDef *DMAx) {
  WRITE_REG(DMAx->IFCR, DMA_IFCR_CTEIF4);
}

/**
  * @brief  Clear Channel 5 transfer error flag.
  * @rmtoll IFCR         CTEIF5        MS32_DMA_ClearFlag_TE5
  * @param  DMAx DMAx Instance
  * @retval None
  */
__STATIC_INLINE void MS32_DMA_ClearFlag_TE5(DMA_TypeDef *DMAx) {
  WRITE_REG(DMAx->IFCR, DMA_IFCR_CTEIF5);
}


/** @defgroup DMA_EF_IT_Management IT_Management
  * @{
  */
/**
  * @brief  Enable Transfer complete interrupt.
  * @rmtoll CCR          TCIE          MS32_DMA_EnableIT_TC
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref MS32_DMA_CHANNEL_1
  *         @arg @ref MS32_DMA_CHANNEL_2
  *         @arg @ref MS32_DMA_CHANNEL_3
  *         @arg @ref MS32_DMA_CHANNEL_4
  *         @arg @ref MS32_DMA_CHANNEL_5
  * @retval None
  */
__STATIC_INLINE void MS32_DMA_EnableIT_TC(DMA_TypeDef *DMAx, uint32_t Channel) {
  SET_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR, DMA_CCR_TCIE);
}

/**
  * @brief  Enable Half transfer interrupt.
  * @rmtoll CCR          HTIE          MS32_DMA_EnableIT_HT
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref MS32_DMA_CHANNEL_1
  *         @arg @ref MS32_DMA_CHANNEL_2
  *         @arg @ref MS32_DMA_CHANNEL_3
  *         @arg @ref MS32_DMA_CHANNEL_4
  *         @arg @ref MS32_DMA_CHANNEL_5
  * @retval None
  */
__STATIC_INLINE void MS32_DMA_EnableIT_HT(DMA_TypeDef *DMAx, uint32_t Channel) {
  SET_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR, DMA_CCR_HTIE);
}

/**
  * @brief  Enable Transfer error interrupt.
  * @rmtoll CCR          TEIE          MS32_DMA_EnableIT_TE
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref MS32_DMA_CHANNEL_1
  *         @arg @ref MS32_DMA_CHANNEL_2
  *         @arg @ref MS32_DMA_CHANNEL_3
  *         @arg @ref MS32_DMA_CHANNEL_4
  *         @arg @ref MS32_DMA_CHANNEL_5
  * @retval None
  */
__STATIC_INLINE void MS32_DMA_EnableIT_TE(DMA_TypeDef *DMAx, uint32_t Channel) {
  SET_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR, DMA_CCR_TEIE);
}

/**
  * @brief  Disable Transfer complete interrupt.
  * @rmtoll CCR          TCIE          MS32_DMA_DisableIT_TC
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref MS32_DMA_CHANNEL_1
  *         @arg @ref MS32_DMA_CHANNEL_2
  *         @arg @ref MS32_DMA_CHANNEL_3
  *         @arg @ref MS32_DMA_CHANNEL_4
  *         @arg @ref MS32_DMA_CHANNEL_5
  * @retval None
  */
__STATIC_INLINE void MS32_DMA_DisableIT_TC(DMA_TypeDef *DMAx, uint32_t Channel) {
  CLEAR_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR, DMA_CCR_TCIE);
}

/**
  * @brief  Disable Half transfer interrupt.
  * @rmtoll CCR          HTIE          MS32_DMA_DisableIT_HT
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref MS32_DMA_CHANNEL_1
  *         @arg @ref MS32_DMA_CHANNEL_2
  *         @arg @ref MS32_DMA_CHANNEL_3
  *         @arg @ref MS32_DMA_CHANNEL_4
  *         @arg @ref MS32_DMA_CHANNEL_5
  * @retval None
  */
__STATIC_INLINE void MS32_DMA_DisableIT_HT(DMA_TypeDef *DMAx, uint32_t Channel) {
  CLEAR_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR, DMA_CCR_HTIE);
}

/**
  * @brief  Disable Transfer error interrupt.
  * @rmtoll CCR          TEIE          MS32_DMA_DisableIT_TE
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref MS32_DMA_CHANNEL_1
  *         @arg @ref MS32_DMA_CHANNEL_2
  *         @arg @ref MS32_DMA_CHANNEL_3
  *         @arg @ref MS32_DMA_CHANNEL_4
  *         @arg @ref MS32_DMA_CHANNEL_5
  * @retval None
  */
__STATIC_INLINE void MS32_DMA_DisableIT_TE(DMA_TypeDef *DMAx, uint32_t Channel) {
  CLEAR_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR, DMA_CCR_TEIE);
}

/**
  * @brief  Check if Transfer complete Interrupt is enabled.
  * @rmtoll CCR          TCIE          MS32_DMA_IsEnabledIT_TC
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref MS32_DMA_CHANNEL_1
  *         @arg @ref MS32_DMA_CHANNEL_2
  *         @arg @ref MS32_DMA_CHANNEL_3
  *         @arg @ref MS32_DMA_CHANNEL_4
  *         @arg @ref MS32_DMA_CHANNEL_5
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_DMA_IsEnabledIT_TC(DMA_TypeDef *DMAx, uint32_t Channel) {
  return (READ_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR,
                   DMA_CCR_TCIE) == (DMA_CCR_TCIE));
}

/**
  * @brief  Check if Half transfer Interrupt is enabled.
  * @rmtoll CCR          HTIE          MS32_DMA_IsEnabledIT_HT
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref MS32_DMA_CHANNEL_1
  *         @arg @ref MS32_DMA_CHANNEL_2
  *         @arg @ref MS32_DMA_CHANNEL_3
  *         @arg @ref MS32_DMA_CHANNEL_4
  *         @arg @ref MS32_DMA_CHANNEL_5
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_DMA_IsEnabledIT_HT(DMA_TypeDef *DMAx, uint32_t Channel) {
  return (READ_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR,
                   DMA_CCR_HTIE) == (DMA_CCR_HTIE));
}

/**
  * @brief  Check if Transfer error Interrupt is enabled.
  * @rmtoll CCR          TEIE          MS32_DMA_IsEnabledIT_TE
  * @param  DMAx DMAx Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref MS32_DMA_CHANNEL_1
  *         @arg @ref MS32_DMA_CHANNEL_2
  *         @arg @ref MS32_DMA_CHANNEL_3
  *         @arg @ref MS32_DMA_CHANNEL_4
  *         @arg @ref MS32_DMA_CHANNEL_5
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_DMA_IsEnabledIT_TE(DMA_TypeDef *DMAx, uint32_t Channel) {
  return (READ_BIT(((DMA_Channel_TypeDef *)((uint32_t)((uint32_t)DMAx + CHANNEL_OFFSET_TAB[Channel - 1U])))->CCR,
                   DMA_CCR_TEIE) == (DMA_CCR_TEIE));
}


/** @defgroup DMA_EF_Init Initialization and de-initialization functions
  * @{
  */
ErrorStatus MS32_DMA_DeInit     (DMA_TypeDef *DMAx, uint32_t Channel);
void        MS32_DMA_StructInit (MS32_DMA_InitTypeDef *DmaInitStr);
ErrorStatus MS32_DMA_Init       (DMA_TypeDef *DMAx, uint32_t Channel, MS32_DMA_InitTypeDef *DmaInitStr);
void        MS32_DMA_ITConfig   (DMA_TypeDef *DMAx, uint32_t Channel, uint32_t InterruptFunc, uint32_t Priority);

/** @defgroup DMA_EF_Application function
  * @{
  */
FlagStatus  MS32_DMA_GetStatusFlag (DMA_TypeDef *DMAx, uint32_t Flags);
void        MS32_DMA_Restart       (DMA_TypeDef *DMAx, uint32_t Channel, uint32_t NbData);


#ifdef __cplusplus
}
#endif

#endif /* __MS32F0XX_DMA_H */

/******************************** END OF FILE *********************************/
