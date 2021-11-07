/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MS32F0XX_H
#define __MS32F0XX_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */


/* Includes ------------------------------------------------------------------*/
#if defined (MS32F031)
  #include "ms32f031.h"
#else
 #error "Please select first the target MS32F0XX device used in your application (in ms32f0xx.h file)"
#endif


/* Exported types ------------------------------------------------------------*/
typedef enum {
  RESET = 0U,
  SET   = !RESET
} LevelStatus, FlagStatus, ITStatus;

typedef enum {
  DISABLE = 0U,
  ENABLE  = !DISABLE
} FunctionalState;

typedef enum {
  SUCCESS = 0U,
  ERROR   = !SUCCESS
} ErrorStatus;


/* Exported constants --------------------------------------------------------*/
/**
  * @brief CMSIS Device version number V1.0.0
  */
#define __MC60F_DEVICE_VERSION_MAIN   (0x01) /*!< [31:24] main version */
#define __MC60F_DEVICE_VERSION_SUB1   (0x00) /*!< [23:16] sub1 version */
#define __MC60F_DEVICE_VERSION_SUB2   (0x00) /*!< [15:8]  sub2 version */
#define __MC60F_DEVICE_VERSION_RC     (0x00) /*!< [7:0]  release candidate */
#define __MC60F_DEVICE_VERSION        ((__MC60F_DEVICE_VERSION_MAIN << 24) \
                                      |(__MC60F_DEVICE_VERSION_SUB1 << 16) \
                                      |(__MC60F_DEVICE_VERSION_SUB2 << 8 ) \
                                      |(__MC60F_DEVICE_VERSION_RC))


/* Exported macro ------------------------------------------------------------*/
#define IS_FUNCTIONAL_STATE(STATE)           (((STATE) == DISABLE) || ((STATE) == ENABLE))

#define SET_BIT(REG, BIT)                    ((REG) |= (BIT))
#define CLEAR_BIT(REG, BIT)                  ((REG) &= ~(BIT))
#define READ_BIT(REG, BIT)                   ((REG) & (BIT))
#define CLEAR_REG(REG)                       ((REG) = (0x0))
#define WRITE_REG(REG, VAL)                  ((REG) = (VAL))
#define READ_REG(REG)                        ((REG))
#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))


/* Exported library ----------------------------------------------------------*/
#if defined (MS32F031)
  #include "ms32f0xx_adc.h"
  #include "ms32f0xx_bus.h"
  #include "ms32f0xx_comp.h"
  #include "ms32f0xx_cortex.h"
  #include "ms32f0xx_crc.h"
  #include "ms32f0xx_dma.h"
  #include "ms32f0xx_exti.h"
  #include "ms32f0xx_flash.h"
  #include "ms32f0xx_gpio.h"
  #include "ms32f0xx_i2c.h"
  #include "ms32f0xx_iwdg.h"
  #include "ms32f0xx_opamp.h"
  #include "ms32f0xx_pwr.h"
  #include "ms32f0xx_rcc.h"
  #include "ms32f0xx_rtc.h"
  #include "ms32f0xx_spi.h"
  #include "ms32f0xx_system.h"
  #include "ms32f0xx_tim.h"
  #include "ms32f0xx_usart.h"
  #include "ms32f0xx_utils.h"
  #include "ms32f0xx_wwdg.h"
#endif

/* Exported functions ------------------------------------------------------- */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MS32F0XX_H */

/******************************** END OF FILE *********************************/
