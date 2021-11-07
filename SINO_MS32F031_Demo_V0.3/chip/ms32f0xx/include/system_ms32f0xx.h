/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SYSTEM_MS32F0XX_H
#define __SYSTEM_MS32F0XX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
  /* This variable is updated in three ways:
      by calling CMSIS function SystemCoreClockUpdate()
      Note: If you use this function to configure the system clock; then there
            is no need to call the 2 first functions listed above, since SystemCoreClock
            variable is updated automatically.
  */
extern       uint32_t SystemCoreClock;     /*!< System Clock Frequency (Core Clock) */
extern const uint8_t  AHBPrescTable[16];   /*!< AHB prescalers table values */
extern const uint8_t  APBPrescTable[8];    /*!< APB prescalers table values */


/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
extern void SystemInit            (void);
extern void SystemCoreClockUpdate (void);


#ifdef __cplusplus
}
#endif

#endif/*__SYSTEM_MS32F0XX_H */

/******************************** END OF FILE *********************************/
