/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MS32F0XX_FLASH_H
#define __MS32F0XX_FLASH_H

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
/* Exported constants --------------------------------------------------------*/
/** @defgroup MS32_FLASH_Exported_Constants FLASH Exported Constants
  * @{
  */

/** @defgroup FLASH_IT  Flash Interrupt
  * @{
  */
#define MS32_FLASH_IT_ERRIE            FLASH_CR_ERRIE /*!< FLASH Error Interrupt Enable            */
#define MS32_FLASH_IT_EOPIE            FLASH_CR_EOPIE /*!< FLASH End of operation Interrupt Enable */
#define MS32_FLASH_IT_ALLFSHIE         (FLASH_CR_ERRIE | FLASH_CR_EOPIE) /*!< All FLASH Interrupt Enable */

/** @defgroup INT_ERR_Flags  Interrupt Error flags
  * @{
  */
#define MS32_FLASH_FLAG_PGERR          FLASH_SR_PGERR    /*!< FLASH Programme Error Interrupt flag  */
#define MS32_FLASH_FLAG_WRERR          FLASH_SR_WRPRTERR /*!< FLASH Write Error Interrupt flag      */
#define MS32_FLASH_FLAG_EOP            FLASH_SR_EOP      /*!< FLASH End of Operation Interrupt flag */
#define MS32_FLASH_FLAG_ALLFSH         (FLASH_SR_PGERR | FLASH_SR_WRPRTERR | FLASH_SR_EOP) /*!< ALL FLASH Interrupt flag */


/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @defgroup FLASH_EF_Init Initialization functions
  * @{
  */
void MS32_FLASH_ITConfig (uint32_t InterruptFunc, uint32_t Priority);

/** @defgroup FLASH_EF_Application function
  * @{
  */
FlagStatus  MS32_FLASH_GetStatusFlag (uint32_t Flags);
ErrorStatus MS32_FLASH_ChipErase     (void);
ErrorStatus MS32_FLASH_PageErase     (uint32_t page);
ErrorStatus MS32_FLASH_Write         (uint32_t addr, uint8_t *dat_buf, uint32_t len);
ErrorStatus MS32_FLASH_Read          (uint32_t addr, uint8_t *dat_buf, uint32_t len);
ErrorStatus MS32_FLASH_OptionErase   (void);
ErrorStatus MS32_FLASH_OptionWrite   (uint32_t addr, uint8_t *dat_buf, uint32_t len);
ErrorStatus MS32_FLASH_OptionRead    (uint32_t addr, uint8_t *dat_buf, uint32_t len);


#ifdef __cplusplus
}
#endif

#endif /* __MS32F0XX_FLASH_H */

/******************************** END OF FILE *********************************/
