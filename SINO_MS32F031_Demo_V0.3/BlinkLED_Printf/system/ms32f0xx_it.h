/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MS32F0XX_IT_H
#define __MS32F0XX_IT_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "ms32f0xx.h"


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void SysTick_Handler(void);

void NMI_Handler(void);
void HardFault_Handler(void);
void SVC_Handler(void);
void PendSV_Handler(void);


#ifdef __cplusplus
}
#endif

#endif /* __MS32F0XX_IT_H */

/******************************** END OF FILE *********************************/
