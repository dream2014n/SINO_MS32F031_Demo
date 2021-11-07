/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MS32F0XX_RCC_H
#define __MS32F0XX_RCC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ms32f0xx.h"


/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Defines used for the bit position in the register and perform offsets*/
#define RCC_POSITION_HPRE       (uint32_t)4U  /*!< field position in register RCC_CFGR */
#define RCC_POSITION_PPRE1      (uint32_t)8U  /*!< field position in register RCC_CFGR */
#define RCC_POSITION_PLLMUL     (uint32_t)18U /*!< field position in register RCC_CFGR */
#define RCC_POSITION_HSICAL     (uint32_t)8U  /*!< field position in register RCC_CR */
#define RCC_POSITION_HSITRIM    (uint32_t)3U  /*!< field position in register RCC_CR */
#define RCC_POSITION_USART1SW   (uint32_t)0U  /*!< field position in register RCC_CFGR3 */


/* Private macros ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/** @defgroup RCC_Exported_Types RCC Exported Types
  * @{
  */

/**
  * @brief  RCC Clocks Frequency Structure
  */
typedef struct {
  uint32_t SYSCLK_Frequency;      /*!< SYSCLK clock frequency */
  uint32_t HCLK_Frequency;        /*!< HCLK clock frequency */
  uint32_t PCLK1_Frequency;       /*!< PCLK1 clock frequency */
} MS32_RCC_ClocksTypeDef;

/**
  * @brief  RCC Internal/External Oscillator (HSE, HSI, LSE and LSI) configuration structure definition  
  */
typedef struct {
  uint32_t HSIState;              /*!< The new state of the HSI.
                                       This parameter can be a value of @ref HSI_Config */
  uint32_t HSEState;              /*!< The new state of the HSE.
                                       This parameter can be a value of @ref HSE_Config */
  uint32_t LSIState;              /*!< The new state of the LSI.
                                       This parameter can be a value of @ref LSI_Config */ 
  uint32_t LSEState;              /*!< The new state of the LSE.
                                       This parameter can be a value of @ref LSE_Config */
} MS32_RCC_OscInitTypeDef;

/** 
  * @brief  RCC PLL configuration structure definition  
  */
typedef struct {
  uint32_t PLLState;              /*!< PLLState: The new state of the PLL.
                                       This parameter can be a value of @ref PLL_Config */
  uint32_t PLLSource;             /*!< PLLSource: PLL entry clock source.
                                       This parameter must be a value of @ref PLL_Clock_Source */          
  uint32_t PLLMUL;                /*!< PLLMUL: Multiplication factor for PLL VCO input clock
                                       This parameter must be a value of @ref PLL_Multiplication_Factor*/
  uint32_t PREDIV;                /*!< PREDIV: Predivision factor for PLL VCO input clock
                                       This parameter must be a value of @ref PLL_Prediv_Factor */
} MS32_RCC_PllInitTypeDef;

/**
  * @brief  RCC System, AHB and APB busses clock configuration structure definition  
  */
typedef struct {
  uint32_t SYSCLKSource;          /*!< The clock source (SYSCLKS) used as system clock.
                                       This parameter can be a value of @ref System_Clock_Source */
  uint32_t AHBCLKDivider;         /*!< The AHB clock (HCLK) divider. This clock is derived from the system clock (SYSCLK).
                                       This parameter can be a value of @ref AHB_Clock_Source */
  uint32_t APB1CLKDivider;        /*!< The APB1 clock (PCLK1) divider. This clock is derived from the AHB clock (HCLK).
                                       This parameter can be a value of @ref APB1_Clock_Source */
} MS32_RCC_ClkInitTypeDef;


/* Exported constants --------------------------------------------------------*/
/** @defgroup RCC_EC_OSC_VALUES Oscillator Values adaptation
  * @brief    Defines used to adapt values of different oscillators
  * @note     These values could be modified in the user environment according to
  *           HW set-up.
  * @{
  */
#if !defined  (HSE_VALUE)
#define HSE_VALUE    8000000U  /*!< Value of the HSE oscillator in Hz */
#endif /* HSE_VALUE */

#if !defined  (HSI_VALUE)
#define HSI_VALUE    8000000U  /*!< Value of the HSI oscillator in Hz */
#endif /* HSI_VALUE */

#if !defined  (LSE_VALUE)
#define LSE_VALUE    32768U    /*!< Value of the LSE oscillator in Hz */
#endif /* LSE_VALUE */

#if !defined  (LSI_VALUE)
#define LSI_VALUE    40000U    /*!< Value of the LSI oscillator in Hz */
#endif /* LSI_VALUE */


/** @defgroup MS32_RCC_Exported_Constants RCC Exported Constants(APP)
  * @{
  */
 
/** @defgroup HSI_Config HSI Config
  * @{
  */
#define MS32_RCC_HSI_OFF                (0x00000000U) /*!< HSI clock deactivation */
#define MS32_RCC_HSI_ON                 RCC_CR_HSION  /*!< HSI clock activation */


/** @defgroup HSE_Config HSE Config
  * @{
  */
#define MS32_RCC_HSE_OFF                (0x00000000U)                  /*!< HSE clock deactivation */
#define MS32_RCC_HSE_ON                 RCC_CR_HSEON                   /*!< HSE clock activation */
#define MS32_RCC_HSE_BYPASS             (RCC_CR_HSEON | RCC_CR_HSEBYP) /*!< External clock source for HSE clock */


/** @defgroup LSI_Config LSI Config
  * @{
  */
#define MS32_RCC_LSI_OFF                (0x00000000U) /*!< LSI clock deactivation */
#define MS32_RCC_LSI_ON                 RCC_CSR_LSION /*!< LSI clock activation */


/** @defgroup LSE_Config LSE Config
  * @{
  */
#define MS32_RCC_LSE_OFF                (0x00000000U)                                   /*!< LSE clock deactivation */
#define MS32_RCC_LSE_ON_DRV_L           (RCC_BDCR_LSEON | MS32_RCC_LSEDRIVE_LOW)        /*!< LSE clock activation and Xtal mode lower driving capability */
#define MS32_RCC_LSE_ON_DRV_ML          (RCC_BDCR_LSEON | MS32_RCC_LSEDRIVE_MEDIUMLOW)  /*!< LSE clock activation and Xtal mode medium low driving capability */
#define MS32_RCC_LSE_ON_DRV_MH          (RCC_BDCR_LSEON | MS32_RCC_LSEDRIVE_MEDIUMHIGH) /*!< LSE clock activation and Xtal mode medium high driving capability */
#define MS32_RCC_LSE_ON_DRV_H           (RCC_BDCR_LSEON | MS32_RCC_LSEDRIVE_HIGH)       /*!< LSE clock activation and Xtal mode higher driving capability */
#define MS32_RCC_LSE_BYPASS             (RCC_BDCR_LSEON | RCC_BDCR_LSEBYP)              /*!< External clock source for LSE clock */


/** @defgroup PLL_Config PLL Config
  * @{
  */
#define MS32_RCC_PLL_OFF                (0x00000000U) /*!< PLL deactivation */
#define MS32_RCC_PLL_ON                 RCC_CR_PLLON  /*!< PLL activation */


/** @defgroup PLL_Clock_Source PLL Clock Source
  * @{
  */
#define MS32_RCC_PLL_SOURCE_HSI_DIV_2   MS32_RCC_PLLSOURCE_HSI_DIV_2 /*!< HSI/2 clock selected as PLL entry clock source */
#define MS32_RCC_PLL_SOURCE_HSE         MS32_RCC_PLLSOURCE_HSE       /*!< HSE clock selected as PLL entry clock source */


/** @defgroup PLL_Multiplication_Factor RCC PLL Multiplication Factor
  * @{
  */
#define MS32_RCC_PLL_MUL2               MS32_RCC_PLL_MUL_2 
#define MS32_RCC_PLL_MUL3               MS32_RCC_PLL_MUL_3 
#define MS32_RCC_PLL_MUL4               MS32_RCC_PLL_MUL_4 
#define MS32_RCC_PLL_MUL5               MS32_RCC_PLL_MUL_5 
#define MS32_RCC_PLL_MUL6               MS32_RCC_PLL_MUL_6 
#define MS32_RCC_PLL_MUL7               MS32_RCC_PLL_MUL_7 
#define MS32_RCC_PLL_MUL8               MS32_RCC_PLL_MUL_8 
#define MS32_RCC_PLL_MUL9               MS32_RCC_PLL_MUL_9 
#define MS32_RCC_PLL_MUL10              MS32_RCC_PLL_MUL_10
#define MS32_RCC_PLL_MUL11              MS32_RCC_PLL_MUL_11
#define MS32_RCC_PLL_MUL12              MS32_RCC_PLL_MUL_12
#define MS32_RCC_PLL_MUL13              MS32_RCC_PLL_MUL_13
#define MS32_RCC_PLL_MUL14              MS32_RCC_PLL_MUL_14
#define MS32_RCC_PLL_MUL15              MS32_RCC_PLL_MUL_15
#define MS32_RCC_PLL_MUL16              MS32_RCC_PLL_MUL_16


/** @defgroup PLL_Prediv_Factor RCC PLL Prediv Factor
  * @{
  */
#define MS32_RCC_PLL_PREDIV_DIV1        MS32_RCC_PREDIV_DIV_1 
#define MS32_RCC_PLL_PREDIV_DIV2        MS32_RCC_PREDIV_DIV_2 
#define MS32_RCC_PLL_PREDIV_DIV3        MS32_RCC_PREDIV_DIV_3 
#define MS32_RCC_PLL_PREDIV_DIV4        MS32_RCC_PREDIV_DIV_4 
#define MS32_RCC_PLL_PREDIV_DIV5        MS32_RCC_PREDIV_DIV_5 
#define MS32_RCC_PLL_PREDIV_DIV6        MS32_RCC_PREDIV_DIV_6 
#define MS32_RCC_PLL_PREDIV_DIV7        MS32_RCC_PREDIV_DIV_7 
#define MS32_RCC_PLL_PREDIV_DIV8        MS32_RCC_PREDIV_DIV_8 
#define MS32_RCC_PLL_PREDIV_DIV9        MS32_RCC_PREDIV_DIV_9 
#define MS32_RCC_PLL_PREDIV_DIV10       MS32_RCC_PREDIV_DIV_10
#define MS32_RCC_PLL_PREDIV_DIV11       MS32_RCC_PREDIV_DIV_11
#define MS32_RCC_PLL_PREDIV_DIV12       MS32_RCC_PREDIV_DIV_12
#define MS32_RCC_PLL_PREDIV_DIV13       MS32_RCC_PREDIV_DIV_13
#define MS32_RCC_PLL_PREDIV_DIV14       MS32_RCC_PREDIV_DIV_14
#define MS32_RCC_PLL_PREDIV_DIV15       MS32_RCC_PREDIV_DIV_15
#define MS32_RCC_PLL_PREDIV_DIV16       MS32_RCC_PREDIV_DIV_16


/** @defgroup System_Clock_Source System Clock Source
  * @{
  */
#define MS32_RCC_SYSCLK_SOURCE_HSI      MS32_RCC_SYS_CLKSOURCE_HSI /*!< HSI selected as system clock */
#define MS32_RCC_SYSCLK_SOURCE_HSE      MS32_RCC_SYS_CLKSOURCE_HSE /*!< HSE selected as system clock */
#define MS32_RCC_SYSCLK_SOURCE_PLL      MS32_RCC_SYS_CLKSOURCE_PLL /*!< PLL selected as system clock */


/** @defgroup AHB_Clock_Source AHB Clock Source
  * @{
  */
#define MS32_RCC_SYSCLK_DIV1            MS32_RCC_SYSCLK_DIV_1   /*!< SYSCLK not divided */
#define MS32_RCC_SYSCLK_DIV2            MS32_RCC_SYSCLK_DIV_2   /*!< SYSCLK divided by 2 */
#define MS32_RCC_SYSCLK_DIV4            MS32_RCC_SYSCLK_DIV_4   /*!< SYSCLK divided by 4 */
#define MS32_RCC_SYSCLK_DIV8            MS32_RCC_SYSCLK_DIV_8   /*!< SYSCLK divided by 8 */
#define MS32_RCC_SYSCLK_DIV16           MS32_RCC_SYSCLK_DIV_16  /*!< SYSCLK divided by 16 */
#define MS32_RCC_SYSCLK_DIV64           MS32_RCC_SYSCLK_DIV_64  /*!< SYSCLK divided by 64 */
#define MS32_RCC_SYSCLK_DIV128          MS32_RCC_SYSCLK_DIV_128 /*!< SYSCLK divided by 128 */
#define MS32_RCC_SYSCLK_DIV256          MS32_RCC_SYSCLK_DIV_256 /*!< SYSCLK divided by 256 */
#define MS32_RCC_SYSCLK_DIV512          MS32_RCC_SYSCLK_DIV_512 /*!< SYSCLK divided by 512 */


/** @defgroup APB1_Clock_Source RCC APB1 Clock Source
  * @{
  */
#define MS32_RCC_HCLK_DIV1              MS32_RCC_APB1_DIV_1  /*!< HCLK not divided */
#define MS32_RCC_HCLK_DIV2              MS32_RCC_APB1_DIV_2  /*!< HCLK divided by 2 */
#define MS32_RCC_HCLK_DIV4              MS32_RCC_APB1_DIV_4  /*!< HCLK divided by 4 */
#define MS32_RCC_HCLK_DIV8              MS32_RCC_APB1_DIV_8  /*!< HCLK divided by 8 */
#define MS32_RCC_HCLK_DIV16             MS32_RCC_APB1_DIV_16 /*!< HCLK divided by 16 */


/** @defgroup MCO_Source  MCO SOURCE selection
  * @{
  */
#define MS32_RCC_MCO_SOURCE_NOCLOCK     MS32_RCC_MCO1SOURCE_NOCLOCK   /*!< MCO output disabled, no clock on MCO */
#define MS32_RCC_MCO_SOURCE_HSI16       MS32_RCC_MCO1SOURCE_HSI16     /*!< HSI16 oscillator clock selected */
#define MS32_RCC_MCO_SOURCE_LSI         MS32_RCC_MCO1SOURCE_LSI       /*!< LSI selection as MCO source */
#define MS32_RCC_MCO_SOURCE_LSE         MS32_RCC_MCO1SOURCE_LSE       /*!< LSE selection as MCO source */
#define MS32_RCC_MCO_SOURCE_SYSCLK      MS32_RCC_MCO1SOURCE_SYSCLK    /*!< SYSCLK selection as MCO source */
#define MS32_RCC_MCO_SOURCE_HSI         MS32_RCC_MCO1SOURCE_HSI       /*!< HSI selection as MCO source */
#define MS32_RCC_MCO_SOURCE_HSE         MS32_RCC_MCO1SOURCE_HSE       /*!< HSE selection as MCO source */
#define MS32_RCC_MCO_SOURCE_PLL_DIV2    MS32_RCC_MCO1SOURCE_PLL_DIV_2 /*!< PLL/2 selection as MCO source */
#define MS32_RCC_MCO_SOURCE_PLL         MS32_RCC_MCO1SOURCE_PLL       /*!< PLL selection as MCO source */


/** @defgroup MCO_Prescaler  MCO prescaler
  * @{
  */
#define MS32_RCC_MCO_DIV1               MS32_RCC_MCO1_DIV_1   /*!< MCO Clock divided by 1 */
#define MS32_RCC_MCO_DIV2               MS32_RCC_MCO1_DIV_2   /*!< MCO Clock divided by 2 */
#define MS32_RCC_MCO_DIV4               MS32_RCC_MCO1_DIV_4   /*!< MCO Clock divided by 4 */
#define MS32_RCC_MCO_DIV8               MS32_RCC_MCO1_DIV_8   /*!< MCO Clock divided by 8 */
#define MS32_RCC_MCO_DIV16              MS32_RCC_MCO1_DIV_16  /*!< MCO Clock divided by 16 */
#define MS32_RCC_MCO_DIV32              MS32_RCC_MCO1_DIV_32  /*!< MCO Clock divided by 32 */
#define MS32_RCC_MCO_DIV64              MS32_RCC_MCO1_DIV_64  /*!< MCO Clock divided by 64 */
#define MS32_RCC_MCO_DIV128             MS32_RCC_MCO1_DIV_128 /*!< MCO Clock divided by 128 */


/** @defgroup CLK_IT  Clock Interrupt
  * @{
  */
#define MS32_RCC_IT_LSIRDYIE            RCC_CIR_LSIRDYIE /*!< LSI Ready Interrupt Enable */
#define MS32_RCC_IT_LSERDYIE            RCC_CIR_LSERDYIE /*!< LSE Ready Interrupt Enable */
#define MS32_RCC_IT_HSIRDYIE            RCC_CIR_HSIRDYIE /*!< HSI Ready Interrupt Enable */
#define MS32_RCC_IT_HSERDYIE            RCC_CIR_HSERDYIE /*!< HSE Ready Interrupt Enable */
#define MS32_RCC_IT_PLLRDYIE            RCC_CIR_PLLRDYIE /*!< PLL Ready Interrupt Enable */
#define MS32_RCC_IT_ALLRDYIE            (RCC_CIR_LSIRDYIE | RCC_CIR_LSERDYIE | RCC_CIR_HSIRDYIE | RCC_CIR_HSERDYIE | RCC_CIR_PLLRDYIE) /*!< All clock Ready Interrupt Enable */


/** @defgroup INT_ERR_Flags  Interrupt Error flags
  * @{
  */
#define MS32_RCC_FLAG_LSIRDY            MS32_RCC_CIR_LSIRDYF /*!< LSI Ready Interrupt flag */
#define MS32_RCC_FLAG_LSERDY            MS32_RCC_CIR_LSERDYF /*!< LSE Ready Interrupt flag */
#define MS32_RCC_FLAG_HSIRDY            MS32_RCC_CIR_HSIRDYF /*!< HSI Ready Interrupt flag */
#define MS32_RCC_FLAG_HSERDY            MS32_RCC_CIR_HSERDYF /*!< HSE Ready Interrupt flag */
#define MS32_RCC_FLAG_PLLRDY            MS32_RCC_CIR_PLLRDYF /*!< PLL Ready Interrupt flag */
#define MS32_RCC_FLAG_ALLRDY            (MS32_RCC_CIR_LSIRDYF | MS32_RCC_CIR_LSERDYF | MS32_RCC_CIR_HSIRDYF | MS32_RCC_CIR_HSERDYF | MS32_RCC_CIR_PLLRDYF) /*!< ALL Ready Interrupt flag */
#define MS32_RCC_FLAG_CSS               MS32_RCC_CIR_CSSF    /*!< Clock Security System Interrupt flag */


/** @defgroup RESET_Flags  Reset flags
  * @{
  */
#define MS32_RCC_FLAG_OBLRSTF           MS32_RCC_CSR_OBLRSTF    /*!< OBL reset flag */
#define MS32_RCC_FLAG_PINRSTF           MS32_RCC_CSR_PINRSTF    /*!< PIN reset flag */
#define MS32_RCC_FLAG_PORRSTF           MS32_RCC_CSR_PORRSTF    /*!< POR/PDR reset flag */
#define MS32_RCC_FLAG_SFTRSTF           MS32_RCC_CSR_SFTRSTF    /*!< Software Reset flag */
#define MS32_RCC_FLAG_IWDGRSTF          MS32_RCC_CSR_IWDGRSTF   /*!< Independent Watchdog reset flag */
#define MS32_RCC_FLAG_WWDGRSTF          MS32_RCC_CSR_WWDGRSTF   /*!< Window watchdog reset flag */
#define MS32_RCC_FLAG_LPWRRSTF          MS32_RCC_CSR_LPWRRSTF   /*!< Low-Power reset flag */
#define MS32_RCC_FLAG_V15PWRRSTF        MS32_RCC_CSR_V15PWRRSTF /*!< Reset flag of the 1.5 V domain. */
#define MS32_RCC_FLAG_ALLRSTF           (MS32_RCC_CSR_OBLRSTF | MS32_RCC_CSR_PINRSTF | MS32_RCC_CSR_PORRSTF | MS32_RCC_CSR_SFTRSTF | MS32_RCC_CSR_IWDGRSTF | MS32_RCC_CSR_WWDGRSTF | MS32_RCC_CSR_LPWRRSTF | MS32_RCC_CSR_V15PWRRSTF) /*!< ALL Reset Interrupt flag */


/** @defgroup RCC_Exported_Constants RCC Exported Constants(BASE)
  * @{
  */
/** @defgroup RCC_EC_CLEAR_FLAG Clear Flags Defines
  * @brief    Flags defines which can be used with RCC_WriteReg function
  * @{
  */
#define MS32_RCC_CIR_LSIRDYC                RCC_CIR_LSIRDYC /*!< LSI Ready Interrupt Clear */
#define MS32_RCC_CIR_LSERDYC                RCC_CIR_LSERDYC /*!< LSE Ready Interrupt Clear */
#define MS32_RCC_CIR_HSIRDYC                RCC_CIR_HSIRDYC /*!< HSI Ready Interrupt Clear */
#define MS32_RCC_CIR_HSERDYC                RCC_CIR_HSERDYC /*!< HSE Ready Interrupt Clear */
#define MS32_RCC_CIR_PLLRDYC                RCC_CIR_PLLRDYC /*!< PLL Ready Interrupt Clear */
#define MS32_RCC_CIR_CSSC                   RCC_CIR_CSSC    /*!< Clock Security System Interrupt Clear */


/** @defgroup RCC_EC_GET_FLAG Get Flags Defines
  * @brief    Flags defines which can be used with RCC_ReadReg function
  * @{
  */
#define MS32_RCC_CIR_LSIRDYF                RCC_CIR_LSIRDYF    /*!< LSI Ready Interrupt flag */
#define MS32_RCC_CIR_LSERDYF                RCC_CIR_LSERDYF    /*!< LSE Ready Interrupt flag */
#define MS32_RCC_CIR_HSIRDYF                RCC_CIR_HSIRDYF    /*!< HSI Ready Interrupt flag */
#define MS32_RCC_CIR_HSERDYF                RCC_CIR_HSERDYF    /*!< HSE Ready Interrupt flag */
#define MS32_RCC_CIR_PLLRDYF                RCC_CIR_PLLRDYF    /*!< PLL Ready Interrupt flag */
#define MS32_RCC_CIR_CSSF                   RCC_CIR_CSSF       /*!< Clock Security System Interrupt flag */
#define MS32_RCC_CSR_OBLRSTF                RCC_CSR_OBLRSTF    /*!< OBL reset flag */
#define MS32_RCC_CSR_PINRSTF                RCC_CSR_PINRSTF    /*!< PIN reset flag */
#define MS32_RCC_CSR_PORRSTF                RCC_CSR_PORRSTF    /*!< POR/PDR reset flag */
#define MS32_RCC_CSR_SFTRSTF                RCC_CSR_SFTRSTF    /*!< Software Reset flag */
#define MS32_RCC_CSR_IWDGRSTF               RCC_CSR_IWDGRSTF   /*!< Independent Watchdog reset flag */
#define MS32_RCC_CSR_WWDGRSTF               RCC_CSR_WWDGRSTF   /*!< Window watchdog reset flag */
#define MS32_RCC_CSR_LPWRRSTF               RCC_CSR_LPWRRSTF   /*!< Low-Power reset flag */
#define MS32_RCC_CSR_V15PWRRSTF             RCC_CSR_V15PWRRSTF /*!< Reset flag of the 1.5 V domain. */


/** @defgroup RCC_EC_IT IT Defines
  * @brief    IT defines which can be used with RCC_ReadReg and  RCC_WriteReg functions
  * @{
  */
#define MS32_RCC_CIR_LSIRDYIE               RCC_CIR_LSIRDYIE /*!< LSI Ready Interrupt Enable */
#define MS32_RCC_CIR_LSERDYIE               RCC_CIR_LSERDYIE /*!< LSE Ready Interrupt Enable */
#define MS32_RCC_CIR_HSIRDYIE               RCC_CIR_HSIRDYIE /*!< HSI Ready Interrupt Enable */
#define MS32_RCC_CIR_HSERDYIE               RCC_CIR_HSERDYIE /*!< HSE Ready Interrupt Enable */
#define MS32_RCC_CIR_PLLRDYIE               RCC_CIR_PLLRDYIE /*!< PLL Ready Interrupt Enable */


/** @defgroup RCC_EC_LSEDRIVE  LSE oscillator drive capability
  * @{
  */
#define MS32_RCC_LSEDRIVE_LOW               (0x00000000U)     /*!< Xtal mode lower driving capability */
#define MS32_RCC_LSEDRIVE_MEDIUMLOW         RCC_BDCR_LSEDRV_1 /*!< Xtal mode medium low driving capability */
#define MS32_RCC_LSEDRIVE_MEDIUMHIGH        RCC_BDCR_LSEDRV_0 /*!< Xtal mode medium high driving capability */
#define MS32_RCC_LSEDRIVE_HIGH              RCC_BDCR_LSEDRV   /*!< Xtal mode higher driving capability */


/** @defgroup RCC_EC_SYS_CLKSOURCE  System clock switch
  * @{
  */
#define MS32_RCC_SYS_CLKSOURCE_HSI          RCC_CFGR_SW_HSI /*!< HSI selection as system clock */
#define MS32_RCC_SYS_CLKSOURCE_HSE          RCC_CFGR_SW_HSE /*!< HSE selection as system clock */
#define MS32_RCC_SYS_CLKSOURCE_PLL          RCC_CFGR_SW_PLL /*!< PLL selection as system clock */


/** @defgroup RCC_EC_SYS_CLKSOURCE_STATUS  System clock switch status
  * @{
  */
#define MS32_RCC_SYS_CLKSOURCE_STATUS_HSI   RCC_CFGR_SWS_HSI /*!< HSI used as system clock */
#define MS32_RCC_SYS_CLKSOURCE_STATUS_HSE   RCC_CFGR_SWS_HSE /*!< HSE used as system clock */
#define MS32_RCC_SYS_CLKSOURCE_STATUS_PLL   RCC_CFGR_SWS_PLL /*!< PLL used as system clock */


/** @defgroup RCC_EC_SYSCLK_DIV  AHB prescaler
  * @{
  */
#define MS32_RCC_SYSCLK_DIV_1               RCC_CFGR_HPRE_DIV1   /*!< SYSCLK not divided */
#define MS32_RCC_SYSCLK_DIV_2               RCC_CFGR_HPRE_DIV2   /*!< SYSCLK divided by 2 */
#define MS32_RCC_SYSCLK_DIV_4               RCC_CFGR_HPRE_DIV4   /*!< SYSCLK divided by 4 */
#define MS32_RCC_SYSCLK_DIV_8               RCC_CFGR_HPRE_DIV8   /*!< SYSCLK divided by 8 */
#define MS32_RCC_SYSCLK_DIV_16              RCC_CFGR_HPRE_DIV16  /*!< SYSCLK divided by 16 */
#define MS32_RCC_SYSCLK_DIV_64              RCC_CFGR_HPRE_DIV64  /*!< SYSCLK divided by 64 */
#define MS32_RCC_SYSCLK_DIV_128             RCC_CFGR_HPRE_DIV128 /*!< SYSCLK divided by 128 */
#define MS32_RCC_SYSCLK_DIV_256             RCC_CFGR_HPRE_DIV256 /*!< SYSCLK divided by 256 */
#define MS32_RCC_SYSCLK_DIV_512             RCC_CFGR_HPRE_DIV512 /*!< SYSCLK divided by 512 */


/** @defgroup RCC_EC_APB1_DIV  APB low-speed prescaler (APB1)
  * @{
  */
#define MS32_RCC_APB1_DIV_1                 RCC_CFGR_PPRE_DIV1  /*!< HCLK not divided */
#define MS32_RCC_APB1_DIV_2                 RCC_CFGR_PPRE_DIV2  /*!< HCLK divided by 2 */
#define MS32_RCC_APB1_DIV_4                 RCC_CFGR_PPRE_DIV4  /*!< HCLK divided by 4 */
#define MS32_RCC_APB1_DIV_8                 RCC_CFGR_PPRE_DIV8  /*!< HCLK divided by 8 */
#define MS32_RCC_APB1_DIV_16                RCC_CFGR_PPRE_DIV16 /*!< HCLK divided by 16 */


/** @defgroup RCC_EC_MCO1SOURCE  MCO1 SOURCE selection
  * @{
  */
#define MS32_RCC_MCO1SOURCE_NOCLOCK         RCC_CFGR_MCO_NOCLOCK                   /*!< MCO output disabled, no clock on MCO */
#define MS32_RCC_MCO1SOURCE_HSI16           RCC_CFGR_MCO_HSI16                     /*!< HSI16 oscillator clock selected */
#define MS32_RCC_MCO1SOURCE_LSI             RCC_CFGR_MCO_LSI                       /*!< LSI selection as MCO source */
#define MS32_RCC_MCO1SOURCE_LSE             RCC_CFGR_MCO_LSE                       /*!< LSE selection as MCO source */
#define MS32_RCC_MCO1SOURCE_SYSCLK          RCC_CFGR_MCO_SYSCLK                    /*!< SYSCLK selection as MCO source */
#define MS32_RCC_MCO1SOURCE_HSI             RCC_CFGR_MCO_HSI                       /*!< HSI selection as MCO source */
#define MS32_RCC_MCO1SOURCE_HSE             RCC_CFGR_MCO_HSE                       /*!< HSE selection as MCO source */
#define MS32_RCC_MCO1SOURCE_PLL_DIV_2       RCC_CFGR_MCO_PLL                       /*!< PLL/2 selection as MCO source */
#define MS32_RCC_MCO1SOURCE_PLL             (RCC_CFGR_MCO_PLL | RCC_CFGR_PLLNODIV) /*!< PLL selection as MCO source */


/** @defgroup RCC_EC_MCO1_DIV  MCO1 prescaler
  * @{
  */
#define MS32_RCC_MCO1_DIV_1                  RCC_CFGR_MCOPRE_DIV1    /*!< MCO Clock divided by 1 */
#define MS32_RCC_MCO1_DIV_2                  RCC_CFGR_MCOPRE_DIV2    /*!< MCO Clock divided by 2 */
#define MS32_RCC_MCO1_DIV_4                  RCC_CFGR_MCOPRE_DIV4    /*!< MCO Clock divided by 4 */
#define MS32_RCC_MCO1_DIV_8                  RCC_CFGR_MCOPRE_DIV8    /*!< MCO Clock divided by 8 */
#define MS32_RCC_MCO1_DIV_16                 RCC_CFGR_MCOPRE_DIV16   /*!< MCO Clock divided by 16 */
#define MS32_RCC_MCO1_DIV_32                 RCC_CFGR_MCOPRE_DIV32   /*!< MCO Clock divided by 32 */
#define MS32_RCC_MCO1_DIV_64                 RCC_CFGR_MCOPRE_DIV64   /*!< MCO Clock divided by 64 */
#define MS32_RCC_MCO1_DIV_128                RCC_CFGR_MCOPRE_DIV128  /*!< MCO Clock divided by 128 */


/** @defgroup RCC_EC_PERIPH_FREQUENCY Peripheral clock frequency
  * @{
  */
#define MS32_RCC_PERIPH_FREQUENCY_NO         0x00000000U /*!< No clock enabled for the peripheral            */
#define MS32_RCC_PERIPH_FREQUENCY_NA         0xFFFFFFFFU /*!< Frequency cannot be provided as external clock */


/** @defgroup RCC_EC_USART1_CLKSOURCE Peripheral USART clock source selection
  * @{
  */
#define MS32_RCC_USART1_CLKSOURCE_PCLK1      (uint32_t)((RCC_POSITION_USART1SW << 24) | RCC_CFGR3_USART1SW_PCLK)   /*!< PCLK1 clock used as USART1 clock source */
#define MS32_RCC_USART1_CLKSOURCE_SYSCLK     (uint32_t)((RCC_POSITION_USART1SW << 24) | RCC_CFGR3_USART1SW_SYSCLK) /*!< System clock selected as USART1 clock source */
#define MS32_RCC_USART1_CLKSOURCE_LSE        (uint32_t)((RCC_POSITION_USART1SW << 24) | RCC_CFGR3_USART1SW_LSE)    /*!< LSE oscillator clock used as USART1 clock source */
#define MS32_RCC_USART1_CLKSOURCE_HSI        (uint32_t)((RCC_POSITION_USART1SW << 24) | RCC_CFGR3_USART1SW_HSI)    /*!< HSI oscillator clock used as USART1 clock source */


/** @defgroup RCC_EC_I2C1_CLKSOURCE Peripheral I2C clock source selection
  * @{
  */
#define MS32_RCC_I2C1_CLKSOURCE_HSI          RCC_CFGR3_I2C1SW_HSI    /*!< HSI oscillator clock used as I2C1 clock source */
#define MS32_RCC_I2C1_CLKSOURCE_SYSCLK       RCC_CFGR3_I2C1SW_SYSCLK /*!< System clock selected as I2C1 clock source */


/** @defgroup RCC_EC_USART1 Peripheral USART get clock source
  * @{
  */
#define MS32_RCC_USART1_CLKSOURCE            RCC_POSITION_USART1SW /*!< USART1 Clock source selection */


/** @defgroup RCC_EC_I2C1 Peripheral I2C get clock source
  * @{
  */
#define MS32_RCC_I2C1_CLKSOURCE              RCC_CFGR3_I2C1SW /*!< I2C1 Clock source selection */


/** @defgroup RCC_EC_RTC_CLKSOURCE  RTC clock source selection
  * @{
  */
#define MS32_RCC_RTC_CLKSOURCE_NONE          0x00000000U       /*!< No clock used as RTC clock */
#define MS32_RCC_RTC_CLKSOURCE_LSE           RCC_BDCR_RTCSEL_0 /*!< LSE oscillator clock used as RTC clock */
#define MS32_RCC_RTC_CLKSOURCE_LSI           RCC_BDCR_RTCSEL_1 /*!< LSI oscillator clock used as RTC clock */
#define MS32_RCC_RTC_CLKSOURCE_HSE_DIV32     RCC_BDCR_RTCSEL   /*!< HSE oscillator clock divided by 32 used as RTC clock */


/** @defgroup RCC_EC_PLL_MUL PLL Multiplicator factor
  * @{
  */
#define MS32_RCC_PLL_MUL_2                   RCC_CFGR_PLLMUL2  /*!< PLL input clock*2 */
#define MS32_RCC_PLL_MUL_3                   RCC_CFGR_PLLMUL3  /*!< PLL input clock*3 */
#define MS32_RCC_PLL_MUL_4                   RCC_CFGR_PLLMUL4  /*!< PLL input clock*4 */
#define MS32_RCC_PLL_MUL_5                   RCC_CFGR_PLLMUL5  /*!< PLL input clock*5 */
#define MS32_RCC_PLL_MUL_6                   RCC_CFGR_PLLMUL6  /*!< PLL input clock*6 */
#define MS32_RCC_PLL_MUL_7                   RCC_CFGR_PLLMUL7  /*!< PLL input clock*7 */
#define MS32_RCC_PLL_MUL_8                   RCC_CFGR_PLLMUL8  /*!< PLL input clock*8 */
#define MS32_RCC_PLL_MUL_9                   RCC_CFGR_PLLMUL9  /*!< PLL input clock*9 */
#define MS32_RCC_PLL_MUL_10                  RCC_CFGR_PLLMUL10 /*!< PLL input clock*10 */
#define MS32_RCC_PLL_MUL_11                  RCC_CFGR_PLLMUL11 /*!< PLL input clock*11 */
#define MS32_RCC_PLL_MUL_12                  RCC_CFGR_PLLMUL12 /*!< PLL input clock*12 */
#define MS32_RCC_PLL_MUL_13                  RCC_CFGR_PLLMUL13 /*!< PLL input clock*13 */
#define MS32_RCC_PLL_MUL_14                  RCC_CFGR_PLLMUL14 /*!< PLL input clock*14 */
#define MS32_RCC_PLL_MUL_15                  RCC_CFGR_PLLMUL15 /*!< PLL input clock*15 */
#define MS32_RCC_PLL_MUL_16                  RCC_CFGR_PLLMUL16 /*!< PLL input clock*16 */


/** @defgroup RCC_EC_PLLSOURCE PLL SOURCE
  * @{
  */
#define MS32_RCC_PLLSOURCE_HSE               RCC_CFGR_PLLSRC_HSE_PREDIV                            /*!< HSE/PREDIV clock selected as PLL entry clock source */
#define MS32_RCC_PLLSOURCE_HSI_DIV_2         RCC_CFGR_PLLSRC_HSI_DIV2                              /*!< HSI clock divided by 2 selected as PLL entry clock source */
#define MS32_RCC_PLLSOURCE_HSE_DIV_1         (RCC_CFGR_PLLSRC_HSE_PREDIV | RCC_CFGR2_PREDIV_DIV1)  /*!< HSE clock selected as PLL entry clock source */
#define MS32_RCC_PLLSOURCE_HSE_DIV_2         (RCC_CFGR_PLLSRC_HSE_PREDIV | RCC_CFGR2_PREDIV_DIV2)  /*!< HSE/2 clock selected as PLL entry clock source */
#define MS32_RCC_PLLSOURCE_HSE_DIV_3         (RCC_CFGR_PLLSRC_HSE_PREDIV | RCC_CFGR2_PREDIV_DIV3)  /*!< HSE/3 clock selected as PLL entry clock source */
#define MS32_RCC_PLLSOURCE_HSE_DIV_4         (RCC_CFGR_PLLSRC_HSE_PREDIV | RCC_CFGR2_PREDIV_DIV4)  /*!< HSE/4 clock selected as PLL entry clock source */
#define MS32_RCC_PLLSOURCE_HSE_DIV_5         (RCC_CFGR_PLLSRC_HSE_PREDIV | RCC_CFGR2_PREDIV_DIV5)  /*!< HSE/5 clock selected as PLL entry clock source */
#define MS32_RCC_PLLSOURCE_HSE_DIV_6         (RCC_CFGR_PLLSRC_HSE_PREDIV | RCC_CFGR2_PREDIV_DIV6)  /*!< HSE/6 clock selected as PLL entry clock source */
#define MS32_RCC_PLLSOURCE_HSE_DIV_7         (RCC_CFGR_PLLSRC_HSE_PREDIV | RCC_CFGR2_PREDIV_DIV7)  /*!< HSE/7 clock selected as PLL entry clock source */
#define MS32_RCC_PLLSOURCE_HSE_DIV_8         (RCC_CFGR_PLLSRC_HSE_PREDIV | RCC_CFGR2_PREDIV_DIV8)  /*!< HSE/8 clock selected as PLL entry clock source */
#define MS32_RCC_PLLSOURCE_HSE_DIV_9         (RCC_CFGR_PLLSRC_HSE_PREDIV | RCC_CFGR2_PREDIV_DIV9)  /*!< HSE/9 clock selected as PLL entry clock source */
#define MS32_RCC_PLLSOURCE_HSE_DIV_10        (RCC_CFGR_PLLSRC_HSE_PREDIV | RCC_CFGR2_PREDIV_DIV10) /*!< HSE/10 clock selected as PLL entry clock source */
#define MS32_RCC_PLLSOURCE_HSE_DIV_11        (RCC_CFGR_PLLSRC_HSE_PREDIV | RCC_CFGR2_PREDIV_DIV11) /*!< HSE/11 clock selected as PLL entry clock source */
#define MS32_RCC_PLLSOURCE_HSE_DIV_12        (RCC_CFGR_PLLSRC_HSE_PREDIV | RCC_CFGR2_PREDIV_DIV12) /*!< HSE/12 clock selected as PLL entry clock source */
#define MS32_RCC_PLLSOURCE_HSE_DIV_13        (RCC_CFGR_PLLSRC_HSE_PREDIV | RCC_CFGR2_PREDIV_DIV13) /*!< HSE/13 clock selected as PLL entry clock source */
#define MS32_RCC_PLLSOURCE_HSE_DIV_14        (RCC_CFGR_PLLSRC_HSE_PREDIV | RCC_CFGR2_PREDIV_DIV14) /*!< HSE/14 clock selected as PLL entry clock source */
#define MS32_RCC_PLLSOURCE_HSE_DIV_15        (RCC_CFGR_PLLSRC_HSE_PREDIV | RCC_CFGR2_PREDIV_DIV15) /*!< HSE/15 clock selected as PLL entry clock source */
#define MS32_RCC_PLLSOURCE_HSE_DIV_16        (RCC_CFGR_PLLSRC_HSE_PREDIV | RCC_CFGR2_PREDIV_DIV16) /*!< HSE/16 clock selected as PLL entry clock source */


/** @defgroup RCC_EC_PREDIV_DIV PREDIV Division factor
  * @{
  */
#define MS32_RCC_PREDIV_DIV_1                RCC_CFGR2_PREDIV_DIV1  /*!< PREDIV input clock not divided */
#define MS32_RCC_PREDIV_DIV_2                RCC_CFGR2_PREDIV_DIV2  /*!< PREDIV input clock divided by 2 */
#define MS32_RCC_PREDIV_DIV_3                RCC_CFGR2_PREDIV_DIV3  /*!< PREDIV input clock divided by 3 */
#define MS32_RCC_PREDIV_DIV_4                RCC_CFGR2_PREDIV_DIV4  /*!< PREDIV input clock divided by 4 */
#define MS32_RCC_PREDIV_DIV_5                RCC_CFGR2_PREDIV_DIV5  /*!< PREDIV input clock divided by 5 */
#define MS32_RCC_PREDIV_DIV_6                RCC_CFGR2_PREDIV_DIV6  /*!< PREDIV input clock divided by 6 */
#define MS32_RCC_PREDIV_DIV_7                RCC_CFGR2_PREDIV_DIV7  /*!< PREDIV input clock divided by 7 */
#define MS32_RCC_PREDIV_DIV_8                RCC_CFGR2_PREDIV_DIV8  /*!< PREDIV input clock divided by 8 */
#define MS32_RCC_PREDIV_DIV_9                RCC_CFGR2_PREDIV_DIV9  /*!< PREDIV input clock divided by 9 */
#define MS32_RCC_PREDIV_DIV_10               RCC_CFGR2_PREDIV_DIV10 /*!< PREDIV input clock divided by 10 */
#define MS32_RCC_PREDIV_DIV_11               RCC_CFGR2_PREDIV_DIV11 /*!< PREDIV input clock divided by 11 */
#define MS32_RCC_PREDIV_DIV_12               RCC_CFGR2_PREDIV_DIV12 /*!< PREDIV input clock divided by 12 */
#define MS32_RCC_PREDIV_DIV_13               RCC_CFGR2_PREDIV_DIV13 /*!< PREDIV input clock divided by 13 */
#define MS32_RCC_PREDIV_DIV_14               RCC_CFGR2_PREDIV_DIV14 /*!< PREDIV input clock divided by 14 */
#define MS32_RCC_PREDIV_DIV_15               RCC_CFGR2_PREDIV_DIV15 /*!< PREDIV input clock divided by 15 */
#define MS32_RCC_PREDIV_DIV_16               RCC_CFGR2_PREDIV_DIV16 /*!< PREDIV input clock divided by 16 */


/* Exported macro ------------------------------------------------------------*/
/**
  * @brief  Write a value in RCC register
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define MS32_RCC_WriteReg(__REG__, __VALUE__) WRITE_REG(RCC->__REG__, (__VALUE__))

/**
  * @brief  Read a value in RCC register
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define MS32_RCC_ReadReg(__REG__) READ_REG(RCC->__REG__)


/** @defgroup RCC_MS32_EM_CALC_FREQ Calculate frequencies
  * @{
  */

/**
  * @brief  Helper macro to calculate the PLLCLK frequency
  * @note ex: @ref __MS32_RCC_CALC_PLLCLK_FREQ (HSE_VALUE / (@ref MS32_RCC_PLL_GetPrediv () + 1), @ref MS32_RCC_PLL_GetMultiplicator());
  * @param  __INPUTFREQ__ PLL Input frequency (based on HSE div Prediv / HSI div 2)
  * @param  __PLLMUL__ This parameter can be one of the following values:
  *         @arg @ref MS32_RCC_PLL_MUL_2
  *         @arg @ref MS32_RCC_PLL_MUL_3
  *         @arg @ref MS32_RCC_PLL_MUL_4
  *         @arg @ref MS32_RCC_PLL_MUL_5
  *         @arg @ref MS32_RCC_PLL_MUL_6
  *         @arg @ref MS32_RCC_PLL_MUL_7
  *         @arg @ref MS32_RCC_PLL_MUL_8
  *         @arg @ref MS32_RCC_PLL_MUL_9
  *         @arg @ref MS32_RCC_PLL_MUL_10
  *         @arg @ref MS32_RCC_PLL_MUL_11
  *         @arg @ref MS32_RCC_PLL_MUL_12
  *         @arg @ref MS32_RCC_PLL_MUL_13
  *         @arg @ref MS32_RCC_PLL_MUL_14
  *         @arg @ref MS32_RCC_PLL_MUL_15
  *         @arg @ref MS32_RCC_PLL_MUL_16
  * @retval PLL clock frequency (in Hz)
  */
#define __MS32_RCC_CALC_PLLCLK_FREQ(__INPUTFREQ__, __PLLMUL__) \
          ((__INPUTFREQ__) * ((((__PLLMUL__) & RCC_CFGR_PLLMUL) >> RCC_POSITION_PLLMUL) + 2U))

/**
  * @brief  Helper macro to calculate the HCLK frequency
  * @note: __AHBPRESCALER__ be retrieved by @ref MS32_RCC_GetAHBPrescaler
  *        ex: __MS32_RCC_CALC_HCLK_FREQ(MS32_RCC_GetAHBPrescaler())
  * @param  __SYSCLKFREQ__ SYSCLK frequency (based on HSE/HSI/PLLCLK)
  * @param  __AHBPRESCALER__ This parameter can be one of the following values:
  *         @arg @ref MS32_RCC_SYSCLK_DIV_1
  *         @arg @ref MS32_RCC_SYSCLK_DIV_2
  *         @arg @ref MS32_RCC_SYSCLK_DIV_4
  *         @arg @ref MS32_RCC_SYSCLK_DIV_8
  *         @arg @ref MS32_RCC_SYSCLK_DIV_16
  *         @arg @ref MS32_RCC_SYSCLK_DIV_64
  *         @arg @ref MS32_RCC_SYSCLK_DIV_128
  *         @arg @ref MS32_RCC_SYSCLK_DIV_256
  *         @arg @ref MS32_RCC_SYSCLK_DIV_512
  * @retval HCLK clock frequency (in Hz)
  */
#define __MS32_RCC_CALC_HCLK_FREQ(__SYSCLKFREQ__, __AHBPRESCALER__) ((__SYSCLKFREQ__) >> AHBPrescTable[((__AHBPRESCALER__) & RCC_CFGR_HPRE) >>  RCC_CFGR_HPRE_Pos])

/**
  * @brief  Helper macro to calculate the PCLK1 frequency (ABP1)
  * @note: __APB1PRESCALER__ be retrieved by @ref MS32_RCC_GetAPB1Prescaler
  *        ex: __MS32_RCC_CALC_PCLK1_FREQ(MS32_RCC_GetAPB1Prescaler())
  * @param  __HCLKFREQ__ HCLK frequency
  * @param  __APB1PRESCALER__ This parameter can be one of the following values:
  *         @arg @ref MS32_RCC_APB1_DIV_1
  *         @arg @ref MS32_RCC_APB1_DIV_2
  *         @arg @ref MS32_RCC_APB1_DIV_4
  *         @arg @ref MS32_RCC_APB1_DIV_8
  *         @arg @ref MS32_RCC_APB1_DIV_16
  * @retval PCLK1 clock frequency (in Hz)
  */
#define __MS32_RCC_CALC_PCLK1_FREQ(__HCLKFREQ__, __APB1PRESCALER__) ((__HCLKFREQ__) >> APBPrescTable[(__APB1PRESCALER__) >>  RCC_CFGR_PPRE_Pos])


/* Exported functions --------------------------------------------------------*/
/** @defgroup RCC_EF_HSE HSE
  * @{
  */

/**
  * @brief  Enable the Clock Security System.
  * @rmtoll CR           CSSON         MS32_RCC_HSE_EnableCSS
  * @retval None
  */
__STATIC_INLINE void MS32_RCC_HSE_EnableCSS(void) {
  SET_BIT(RCC->CR, RCC_CR_CSSON);
}

/**
  * @brief  Disable the Clock Security System.
  * @note Cannot be disabled in HSE is ready (only by hardware)
  * @rmtoll CR           CSSON         MS32_RCC_HSE_DisableCSS
  * @retval None
  */
__STATIC_INLINE void MS32_RCC_HSE_DisableCSS(void) {
  CLEAR_BIT(RCC->CR, RCC_CR_CSSON);
}

/**
  * @brief  Enable HSE external oscillator (HSE Bypass)
  * @rmtoll CR           HSEBYP        MS32_RCC_HSE_EnableBypass
  * @retval None
  */
__STATIC_INLINE void MS32_RCC_HSE_EnableBypass(void) {
  SET_BIT(RCC->CR, RCC_CR_HSEBYP);
}

/**
  * @brief  Disable HSE external oscillator (HSE Bypass)
  * @rmtoll CR           HSEBYP        MS32_RCC_HSE_DisableBypass
  * @retval None
  */
__STATIC_INLINE void MS32_RCC_HSE_DisableBypass(void) {
  CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP);
}

/**
  * @brief  Check if HSE external oscillator (HSE Bypass)
  * @rmtoll CR           HSEBYP        MS32_RCC_HSE_IsBypass
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_RCC_HSE_IsBypass(void) {
  return (READ_BIT(RCC->CR, RCC_CR_HSEBYP) == (RCC_CR_HSEBYP));
}

/**
  * @brief  Enable HSE crystal oscillator (HSE ON)
  * @rmtoll CR           HSEON         MS32_RCC_HSE_Enable
  * @retval None
  */
__STATIC_INLINE void MS32_RCC_HSE_Enable(void) {
  SET_BIT(RCC->CR, RCC_CR_HSEON);
}

/**
  * @brief  Disable HSE crystal oscillator (HSE ON)
  * @rmtoll CR           HSEON         MS32_RCC_HSE_Disable
  * @retval None
  */
__STATIC_INLINE void MS32_RCC_HSE_Disable(void) {
  CLEAR_BIT(RCC->CR, RCC_CR_HSEON);
}

/**
  * @brief  Check if HSE oscillator Ready
  * @rmtoll CR           HSERDY        MS32_RCC_HSE_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_RCC_HSE_IsReady(void) {
  return (READ_BIT(RCC->CR, RCC_CR_HSERDY) == (RCC_CR_HSERDY));
}


/** @defgroup RCC_EF_HSI HSI
  * @{
  */

/**
  * @brief  Enable HSI oscillator
  * @rmtoll CR           HSION         MS32_RCC_HSI_Enable
  * @retval None
  */
__STATIC_INLINE void MS32_RCC_HSI_Enable(void) {
  SET_BIT(RCC->CR, RCC_CR_HSION);
}

/**
  * @brief  Disable HSI oscillator
  * @rmtoll CR           HSION         MS32_RCC_HSI_Disable
  * @retval None
  */
__STATIC_INLINE void MS32_RCC_HSI_Disable(void) {
  CLEAR_BIT(RCC->CR, RCC_CR_HSION);
}

/**
  * @brief  Check if HSI clock is ready
  * @rmtoll CR           HSIRDY        MS32_RCC_HSI_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_RCC_HSI_IsReady(void) {
  return (READ_BIT(RCC->CR, RCC_CR_HSIRDY) == (RCC_CR_HSIRDY));
}

/**
  * @brief  Get HSI Calibration value
  * @note When HSITRIM is written, HSICAL is updated with the sum of
  *       HSITRIM and the factory trim value
  * @rmtoll CR        HSICAL        MS32_RCC_HSI_GetCalibration
  * @retval Between Min_Data = 0x00 and Max_Data = 0xFF
  */
__STATIC_INLINE uint32_t MS32_RCC_HSI_GetCalibration(void) {
  return (uint32_t)(READ_BIT(RCC->CR, RCC_CR_HSICAL) >> RCC_CR_HSICAL_Pos);
}


/** @defgroup RCC_EF_LSE LSE
  * @{
  */

/**
  * @brief  Enable  Low Speed External (LSE) crystal.
  * @rmtoll BDCR         LSEON         MS32_RCC_LSE_Enable
  * @retval None
  */
__STATIC_INLINE void MS32_RCC_LSE_Enable(void) {
  SET_BIT(RCC->BDCR, RCC_BDCR_LSEON);
}

/**
  * @brief  Disable  Low Speed External (LSE) crystal.
  * @rmtoll BDCR         LSEON         MS32_RCC_LSE_Disable
  * @retval None
  */
__STATIC_INLINE void MS32_RCC_LSE_Disable(void) {
  CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEON);
}

/**
  * @brief  Enable external clock source (LSE bypass).
  * @rmtoll BDCR         LSEBYP        MS32_RCC_LSE_EnableBypass
  * @retval None
  */
__STATIC_INLINE void MS32_RCC_LSE_EnableBypass(void) {
  SET_BIT(RCC->BDCR, RCC_BDCR_LSEBYP);
}

/**
  * @brief  Disable external clock source (LSE bypass).
  * @rmtoll BDCR         LSEBYP        MS32_RCC_LSE_DisableBypass
  * @retval None
  */
__STATIC_INLINE void MS32_RCC_LSE_DisableBypass(void) {
  CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEBYP);
}

/**
  * @brief  Check if external clock source (LSE bypass).
  * @rmtoll BDCR         LSERDY        MS32_RCC_LSE_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_RCC_LSE_IsBypass(void) {
  return (READ_BIT(RCC->BDCR, RCC_BDCR_LSEBYP) == (RCC_BDCR_LSEBYP));
}

/**
  * @brief  Set LSE oscillator drive capability
  * @note The oscillator is in Xtal mode when it is not in bypass mode.
  * @rmtoll BDCR         LSEDRV        MS32_RCC_LSE_SetDriveCapability
  * @param  LSEDrive This parameter can be one of the following values:
  *         @arg @ref MS32_RCC_LSEDRIVE_LOW
  *         @arg @ref MS32_RCC_LSEDRIVE_MEDIUMLOW
  *         @arg @ref MS32_RCC_LSEDRIVE_MEDIUMHIGH
  *         @arg @ref MS32_RCC_LSEDRIVE_HIGH
  * @retval None
  */
__STATIC_INLINE void MS32_RCC_LSE_SetDriveCapability(uint32_t LSEDrive) {
  MODIFY_REG(RCC->BDCR, RCC_BDCR_LSEDRV, LSEDrive);
}

/**
  * @brief  Get LSE oscillator drive capability
  * @rmtoll BDCR         LSEDRV        MS32_RCC_LSE_GetDriveCapability
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_RCC_LSEDRIVE_LOW
  *         @arg @ref MS32_RCC_LSEDRIVE_MEDIUMLOW
  *         @arg @ref MS32_RCC_LSEDRIVE_MEDIUMHIGH
  *         @arg @ref MS32_RCC_LSEDRIVE_HIGH
  */
__STATIC_INLINE uint32_t MS32_RCC_LSE_GetDriveCapability(void) {
  return (uint32_t)(READ_BIT(RCC->BDCR, RCC_BDCR_LSEDRV));
}

/**
  * @brief  Check if LSE oscillator Ready
  * @rmtoll BDCR         LSERDY        MS32_RCC_LSE_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_RCC_LSE_IsReady(void) {
  return (READ_BIT(RCC->BDCR, RCC_BDCR_LSERDY) == (RCC_BDCR_LSERDY));
}


/** @defgroup RCC_EF_LSI LSI
  * @{
  */

/**
  * @brief  Enable LSI Oscillator
  * @rmtoll CSR          LSION         MS32_RCC_LSI_Enable
  * @retval None
  */
__STATIC_INLINE void MS32_RCC_LSI_Enable(void) {
  SET_BIT(RCC->CSR, RCC_CSR_LSION);
}

/**
  * @brief  Disable LSI Oscillator
  * @rmtoll CSR          LSION         MS32_RCC_LSI_Disable
  * @retval None
  */
__STATIC_INLINE void MS32_RCC_LSI_Disable(void) {
  CLEAR_BIT(RCC->CSR, RCC_CSR_LSION);
}

/**
  * @brief  Check if LSI is Ready
  * @rmtoll CSR          LSIRDY        MS32_RCC_LSI_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_RCC_LSI_IsReady(void) {
  return (READ_BIT(RCC->CSR, RCC_CSR_LSIRDY) == (RCC_CSR_LSIRDY));
}


/** @defgroup RCC_EF_System System
  * @{
  */

/**
  * @brief  Configure the system clock source
  * @rmtoll CFGR         SW            MS32_RCC_SetSysClkSource
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref MS32_RCC_SYS_CLKSOURCE_HSI
  *         @arg @ref MS32_RCC_SYS_CLKSOURCE_HSE
  *         @arg @ref MS32_RCC_SYS_CLKSOURCE_PLL
  *
  *         (*) value not defined in all devices
  * @retval None
  */
__STATIC_INLINE void MS32_RCC_SetSysClkSource(uint32_t Source) {
  MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, Source);
}

/**
  * @brief  Get the system clock source
  * @rmtoll CFGR         SWS           MS32_RCC_GetSysClkSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_RCC_SYS_CLKSOURCE_STATUS_HSI
  *         @arg @ref MS32_RCC_SYS_CLKSOURCE_STATUS_HSE
  *         @arg @ref MS32_RCC_SYS_CLKSOURCE_STATUS_PLL
  *
  *         (*) value not defined in all devices
  */
__STATIC_INLINE uint32_t MS32_RCC_GetSysClkSource(void) {
  return (uint32_t)(READ_BIT(RCC->CFGR, RCC_CFGR_SWS));
}

/**
  * @brief  Set AHB prescaler
  * @rmtoll CFGR         HPRE          MS32_RCC_SetAHBPrescaler
  * @param  Prescaler This parameter can be one of the following values:
  *         @arg @ref MS32_RCC_SYSCLK_DIV_1
  *         @arg @ref MS32_RCC_SYSCLK_DIV_2
  *         @arg @ref MS32_RCC_SYSCLK_DIV_4
  *         @arg @ref MS32_RCC_SYSCLK_DIV_8
  *         @arg @ref MS32_RCC_SYSCLK_DIV_16
  *         @arg @ref MS32_RCC_SYSCLK_DIV_64
  *         @arg @ref MS32_RCC_SYSCLK_DIV_128
  *         @arg @ref MS32_RCC_SYSCLK_DIV_256
  *         @arg @ref MS32_RCC_SYSCLK_DIV_512
  * @retval None
  */
__STATIC_INLINE void MS32_RCC_SetAHBPrescaler(uint32_t Prescaler) {
  MODIFY_REG(RCC->CFGR, RCC_CFGR_HPRE, Prescaler);
}

/**
  * @brief  Set APB1 prescaler
  * @rmtoll CFGR         PPRE         MS32_RCC_SetAPB1Prescaler
  * @param  Prescaler This parameter can be one of the following values:
  *         @arg @ref MS32_RCC_APB1_DIV_1
  *         @arg @ref MS32_RCC_APB1_DIV_2
  *         @arg @ref MS32_RCC_APB1_DIV_4
  *         @arg @ref MS32_RCC_APB1_DIV_8
  *         @arg @ref MS32_RCC_APB1_DIV_16
  * @retval None
  */
__STATIC_INLINE void MS32_RCC_SetAPB1Prescaler(uint32_t Prescaler) {
  MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE, Prescaler);
}

/**
  * @brief  Get AHB prescaler
  * @rmtoll CFGR         HPRE          MS32_RCC_GetAHBPrescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_RCC_SYSCLK_DIV_1
  *         @arg @ref MS32_RCC_SYSCLK_DIV_2
  *         @arg @ref MS32_RCC_SYSCLK_DIV_4
  *         @arg @ref MS32_RCC_SYSCLK_DIV_8
  *         @arg @ref MS32_RCC_SYSCLK_DIV_16
  *         @arg @ref MS32_RCC_SYSCLK_DIV_64
  *         @arg @ref MS32_RCC_SYSCLK_DIV_128
  *         @arg @ref MS32_RCC_SYSCLK_DIV_256
  *         @arg @ref MS32_RCC_SYSCLK_DIV_512
  */
__STATIC_INLINE uint32_t MS32_RCC_GetAHBPrescaler(void) {
  return (uint32_t)(READ_BIT(RCC->CFGR, RCC_CFGR_HPRE));
}

/**
  * @brief  Get APB1 prescaler
  * @rmtoll CFGR         PPRE         MS32_RCC_GetAPB1Prescaler
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_RCC_APB1_DIV_1
  *         @arg @ref MS32_RCC_APB1_DIV_2
  *         @arg @ref MS32_RCC_APB1_DIV_4
  *         @arg @ref MS32_RCC_APB1_DIV_8
  *         @arg @ref MS32_RCC_APB1_DIV_16
  */
__STATIC_INLINE uint32_t MS32_RCC_GetAPB1Prescaler(void) {
  return (uint32_t)(READ_BIT(RCC->CFGR, RCC_CFGR_PPRE));
}


/** @defgroup RCC_EF_MCO MCO
  * @{
  */

/**
  * @brief  Configure MCOx
  * @rmtoll CFGR         MCO           MS32_RCC_ConfigMCO\n
  *         CFGR         MCOPRE        MS32_RCC_ConfigMCO\n
  *         CFGR         PLLNODIV      MS32_RCC_ConfigMCO
  * @param  MCOxSource This parameter can be one of the following values:
  *         @arg @ref MS32_RCC_MCO1SOURCE_NOCLOCK  
  *         @arg @ref MS32_RCC_MCO1SOURCE_HSI16    
  *         @arg @ref MS32_RCC_MCO1SOURCE_LSI      
  *         @arg @ref MS32_RCC_MCO1SOURCE_LSE      
  *         @arg @ref MS32_RCC_MCO1SOURCE_SYSCLK   
  *         @arg @ref MS32_RCC_MCO1SOURCE_HSI      
  *         @arg @ref MS32_RCC_MCO1SOURCE_HSE      
  *         @arg @ref MS32_RCC_MCO1SOURCE_PLL_DIV_2
  *         @arg @ref MS32_RCC_MCO1SOURCE_PLL
  * @param  MCOxPrescaler This parameter can be one of the following values:
  *         @arg @ref MS32_RCC_MCO1_DIV_1
  *         @arg @ref MS32_RCC_MCO1_DIV_2
  *         @arg @ref MS32_RCC_MCO1_DIV_4
  *         @arg @ref MS32_RCC_MCO1_DIV_8
  *         @arg @ref MS32_RCC_MCO1_DIV_16
  *         @arg @ref MS32_RCC_MCO1_DIV_32
  *         @arg @ref MS32_RCC_MCO1_DIV_64
  *         @arg @ref MS32_RCC_MCO1_DIV_128
  * @retval None
  */
__STATIC_INLINE void MS32_RCC_ConfigMCO(uint32_t MCOxSource, uint32_t MCOxPrescaler) {
  MODIFY_REG(RCC->CFGR, RCC_CFGR_MCO | RCC_CFGR_MCOPRE | RCC_CFGR_PLLNODIV, MCOxSource | MCOxPrescaler);
}


/** @defgroup RCC_EF_Peripheral_Clock_Source Peripheral Clock Source
  * @{
  */

/**
  * @brief  Configure USARTx clock source
  * @rmtoll CFGR3        USART1SW      MS32_RCC_SetUSARTClockSource
  * @param  USARTxSource This parameter can be one of the following values:
  *         @arg @ref MS32_RCC_USART1_CLKSOURCE_PCLK1
  *         @arg @ref MS32_RCC_USART1_CLKSOURCE_SYSCLK
  *         @arg @ref MS32_RCC_USART1_CLKSOURCE_LSE
  *         @arg @ref MS32_RCC_USART1_CLKSOURCE_HSI
  * @retval None
  */
__STATIC_INLINE void MS32_RCC_SetUSARTClockSource(uint32_t USARTxSource) {
  MODIFY_REG(RCC->CFGR3, (RCC_CFGR3_USART1SW << ((USARTxSource  & 0xFF000000U) >> 24U)), (USARTxSource & 0x00FFFFFFU));
}

/**
  * @brief  Configure I2Cx clock source
  * @rmtoll CFGR3        I2C1SW        MS32_RCC_SetI2CClockSource
  * @param  I2CxSource This parameter can be one of the following values:
  *         @arg @ref MS32_RCC_I2C1_CLKSOURCE_HSI
  *         @arg @ref MS32_RCC_I2C1_CLKSOURCE_SYSCLK
  * @retval None
  */
__STATIC_INLINE void MS32_RCC_SetI2CClockSource(uint32_t I2CxSource) {
  MODIFY_REG(RCC->CFGR3, RCC_CFGR3_I2C1SW, I2CxSource);
}

/**
  * @brief  Get USARTx clock source
  * @rmtoll CFGR3        USART1SW      MS32_RCC_GetUSARTClockSource
  * @param  USARTx This parameter can be one of the following values:
  *         @arg @ref MS32_RCC_USART1_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_RCC_USART1_CLKSOURCE_PCLK1
  *         @arg @ref MS32_RCC_USART1_CLKSOURCE_SYSCLK
  *         @arg @ref MS32_RCC_USART1_CLKSOURCE_LSE
  *         @arg @ref MS32_RCC_USART1_CLKSOURCE_HSI
  */
__STATIC_INLINE uint32_t MS32_RCC_GetUSARTClockSource(uint32_t USARTx) {
  return (uint32_t)(READ_BIT(RCC->CFGR3, (RCC_CFGR3_USART1SW << USARTx)) | (USARTx << 24U));
}

/**
  * @brief  Get I2Cx clock source
  * @rmtoll CFGR3        I2C1SW        MS32_RCC_GetI2CClockSource
  * @param  I2Cx This parameter can be one of the following values:
  *         @arg @ref MS32_RCC_I2C1_CLKSOURCE
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_RCC_I2C1_CLKSOURCE_HSI
  *         @arg @ref MS32_RCC_I2C1_CLKSOURCE_SYSCLK
  */
__STATIC_INLINE uint32_t MS32_RCC_GetI2CClockSource(uint32_t I2Cx) {
  return (uint32_t)(READ_BIT(RCC->CFGR3, I2Cx));
}


/** @defgroup RCC_EF_RTC RTC
  * @{
  */

/**
  * @brief  Set RTC Clock Source
  * @note Once the RTC clock source has been selected, it cannot be changed any more unless
  *       the Backup domain is reset. The BDRST bit can be used to reset them.
  * @rmtoll BDCR         RTCSEL        MS32_RCC_SetRTCClockSource
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref MS32_RCC_RTC_CLKSOURCE_NONE
  *         @arg @ref MS32_RCC_RTC_CLKSOURCE_LSE
  *         @arg @ref MS32_RCC_RTC_CLKSOURCE_LSI
  *         @arg @ref MS32_RCC_RTC_CLKSOURCE_HSE_DIV32
  * @retval None
  */
__STATIC_INLINE void MS32_RCC_SetRTCClockSource(uint32_t Source) {
  MODIFY_REG(RCC->BDCR, RCC_BDCR_RTCSEL, Source);
}

/**
  * @brief  Get RTC Clock Source
  * @rmtoll BDCR         RTCSEL        MS32_RCC_GetRTCClockSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_RCC_RTC_CLKSOURCE_NONE
  *         @arg @ref MS32_RCC_RTC_CLKSOURCE_LSE
  *         @arg @ref MS32_RCC_RTC_CLKSOURCE_LSI
  *         @arg @ref MS32_RCC_RTC_CLKSOURCE_HSE_DIV32
  */
__STATIC_INLINE uint32_t MS32_RCC_GetRTCClockSource(void) {
  return (uint32_t)(READ_BIT(RCC->BDCR, RCC_BDCR_RTCSEL));
}

/**
  * @brief  Enable RTC
  * @rmtoll BDCR         RTCEN         MS32_RCC_EnableRTC
  * @retval None
  */
__STATIC_INLINE void MS32_RCC_EnableRTC(void) {
  SET_BIT(RCC->BDCR, RCC_BDCR_RTCEN);
}

/**
  * @brief  Disable RTC
  * @rmtoll BDCR         RTCEN         MS32_RCC_DisableRTC
  * @retval None
  */
__STATIC_INLINE void MS32_RCC_DisableRTC(void) {
  CLEAR_BIT(RCC->BDCR, RCC_BDCR_RTCEN);
}

/**
  * @brief  Check if RTC has been enabled or not
  * @rmtoll BDCR         RTCEN         MS32_RCC_IsEnabledRTC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_RCC_IsEnabledRTC(void) {
  return (READ_BIT(RCC->BDCR, RCC_BDCR_RTCEN) == (RCC_BDCR_RTCEN));
}

/**
  * @brief  Force the Backup domain reset
  * @rmtoll BDCR         BDRST         MS32_RCC_ForceBackupDomainReset
  * @retval None
  */
__STATIC_INLINE void MS32_RCC_ForceBackupDomainReset(void) {
  SET_BIT(RCC->BDCR, RCC_BDCR_BDRST);
}

/**
  * @brief  Release the Backup domain reset
  * @rmtoll BDCR         BDRST         MS32_RCC_ReleaseBackupDomainReset
  * @retval None
  */
__STATIC_INLINE void MS32_RCC_ReleaseBackupDomainReset(void) {
  CLEAR_BIT(RCC->BDCR, RCC_BDCR_BDRST);
}


/** @defgroup RCC_EF_PLL PLL
  * @{
  */

/**
  * @brief  Enable PLL
  * @rmtoll CR           PLLON         MS32_RCC_PLL_Enable
  * @retval None
  */
__STATIC_INLINE void MS32_RCC_PLL_Enable(void) {
  SET_BIT(RCC->CR, RCC_CR_PLLON);
}

/**
  * @brief  Disable PLL
  * @note Cannot be disabled if the PLL clock is used as the system clock
  * @rmtoll CR           PLLON         MS32_RCC_PLL_Disable
  * @retval None
  */
__STATIC_INLINE void MS32_RCC_PLL_Disable(void) {
  CLEAR_BIT(RCC->CR, RCC_CR_PLLON);
}

/**
  * @brief  Check if PLL Ready
  * @rmtoll CR           PLLRDY        MS32_RCC_PLL_IsReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_RCC_PLL_IsReady(void) {
  return (READ_BIT(RCC->CR, RCC_CR_PLLRDY) == (RCC_CR_PLLRDY));
}

/**
  * @brief  Configure PLL used for SYSCLK Domain
  * @rmtoll CFGR         PLLSRC        MS32_RCC_PLL_ConfigDomain_SYS\n
  *         CFGR         PLLMUL        MS32_RCC_PLL_ConfigDomain_SYS\n
  *         CFGR2        PREDIV        MS32_RCC_PLL_ConfigDomain_SYS
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref MS32_RCC_PLLSOURCE_HSI_DIV_2
  *         @arg @ref MS32_RCC_PLLSOURCE_HSE_DIV_1
  *         @arg @ref MS32_RCC_PLLSOURCE_HSE_DIV_2
  *         @arg @ref MS32_RCC_PLLSOURCE_HSE_DIV_3
  *         @arg @ref MS32_RCC_PLLSOURCE_HSE_DIV_4
  *         @arg @ref MS32_RCC_PLLSOURCE_HSE_DIV_5
  *         @arg @ref MS32_RCC_PLLSOURCE_HSE_DIV_6
  *         @arg @ref MS32_RCC_PLLSOURCE_HSE_DIV_7
  *         @arg @ref MS32_RCC_PLLSOURCE_HSE_DIV_8
  *         @arg @ref MS32_RCC_PLLSOURCE_HSE_DIV_9
  *         @arg @ref MS32_RCC_PLLSOURCE_HSE_DIV_10
  *         @arg @ref MS32_RCC_PLLSOURCE_HSE_DIV_11
  *         @arg @ref MS32_RCC_PLLSOURCE_HSE_DIV_12
  *         @arg @ref MS32_RCC_PLLSOURCE_HSE_DIV_13
  *         @arg @ref MS32_RCC_PLLSOURCE_HSE_DIV_14
  *         @arg @ref MS32_RCC_PLLSOURCE_HSE_DIV_15
  *         @arg @ref MS32_RCC_PLLSOURCE_HSE_DIV_16
  * @param  PLLMul This parameter can be one of the following values:
  *         @arg @ref MS32_RCC_PLL_MUL_2
  *         @arg @ref MS32_RCC_PLL_MUL_3
  *         @arg @ref MS32_RCC_PLL_MUL_4
  *         @arg @ref MS32_RCC_PLL_MUL_5
  *         @arg @ref MS32_RCC_PLL_MUL_6
  *         @arg @ref MS32_RCC_PLL_MUL_7
  *         @arg @ref MS32_RCC_PLL_MUL_8
  *         @arg @ref MS32_RCC_PLL_MUL_9
  *         @arg @ref MS32_RCC_PLL_MUL_10
  *         @arg @ref MS32_RCC_PLL_MUL_11
  *         @arg @ref MS32_RCC_PLL_MUL_12
  *         @arg @ref MS32_RCC_PLL_MUL_13
  *         @arg @ref MS32_RCC_PLL_MUL_14
  *         @arg @ref MS32_RCC_PLL_MUL_15
  *         @arg @ref MS32_RCC_PLL_MUL_16
  * @retval None
  */
__STATIC_INLINE void MS32_RCC_PLL_ConfigDomain_SYS(uint32_t Source, uint32_t PLLMul)
{
  MODIFY_REG(RCC->CFGR, RCC_CFGR_PLLSRC | RCC_CFGR_PLLMUL, (Source & RCC_CFGR_PLLSRC) | PLLMul);
  MODIFY_REG(RCC->CFGR2, RCC_CFGR2_PREDIV, (Source & RCC_CFGR2_PREDIV));
}

/**
  * @brief  Configure PLL clock source
  * @note They can be written only when the PLL is disabled
  * @rmtoll CFGR      PLLSRC        MS32_RCC_PLL_SetMainSource
  * @param PLLSource This parameter can be one of the following values:
  *         @arg @ref MS32_RCC_PLLSOURCE_NONE
  *         @arg @ref MS32_RCC_PLLSOURCE_HSI_DIV_2 (*)
  *         @arg @ref MS32_RCC_PLLSOURCE_HSE
  *
  *         (*) value not defined in all devices
  * @retval None
  */
__STATIC_INLINE void MS32_RCC_PLL_SetMainSource(uint32_t PLLSource) {
  MODIFY_REG(RCC->CFGR, RCC_CFGR_PLLSRC, PLLSource);
}

/**
  * @brief  Get the oscillator used as PLL clock source.
  * @rmtoll CFGR         PLLSRC        MS32_RCC_PLL_GetMainSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_RCC_PLLSOURCE_NONE
  *         @arg @ref MS32_RCC_PLLSOURCE_HSI_DIV_2 (*)
  *         @arg @ref MS32_RCC_PLLSOURCE_HSE
  *
  *         (*) value not defined in all devices
  */
__STATIC_INLINE uint32_t MS32_RCC_PLL_GetMainSource(void) {
  return (uint32_t)(READ_BIT(RCC->CFGR, RCC_CFGR_PLLSRC));
}

/**
  * @brief  Set PLL multiplication Factor
  * @note They can be written only when the PLL is disabled
  * @rmtoll CFGR         PLLMUL        MS32_RCC_PLL_SetMultiplicator
  * @param PLLSource This parameter can be one of the following values:
  *         @arg @ref MS32_RCC_PLL_MUL_2
  *         @arg @ref MS32_RCC_PLL_MUL_3
  *         @arg @ref MS32_RCC_PLL_MUL_4
  *         @arg @ref MS32_RCC_PLL_MUL_5
  *         @arg @ref MS32_RCC_PLL_MUL_6
  *         @arg @ref MS32_RCC_PLL_MUL_7
  *         @arg @ref MS32_RCC_PLL_MUL_8
  *         @arg @ref MS32_RCC_PLL_MUL_9
  *         @arg @ref MS32_RCC_PLL_MUL_10
  *         @arg @ref MS32_RCC_PLL_MUL_11
  *         @arg @ref MS32_RCC_PLL_MUL_12
  *         @arg @ref MS32_RCC_PLL_MUL_13
  *         @arg @ref MS32_RCC_PLL_MUL_14
  *         @arg @ref MS32_RCC_PLL_MUL_15
  *         @arg @ref MS32_RCC_PLL_MUL_16
  * @retval None
  */
__STATIC_INLINE void MS32_RCC_PLL_SetMultiplicator(uint32_t PLLMul) {
  MODIFY_REG(RCC->CFGR, RCC_CFGR_PLLMUL, PLLMul);
}

/**
  * @brief  Get PLL multiplication Factor
  * @rmtoll CFGR         PLLMUL        MS32_RCC_PLL_GetMultiplicator
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_RCC_PLL_MUL_2
  *         @arg @ref MS32_RCC_PLL_MUL_3
  *         @arg @ref MS32_RCC_PLL_MUL_4
  *         @arg @ref MS32_RCC_PLL_MUL_5
  *         @arg @ref MS32_RCC_PLL_MUL_6
  *         @arg @ref MS32_RCC_PLL_MUL_7
  *         @arg @ref MS32_RCC_PLL_MUL_8
  *         @arg @ref MS32_RCC_PLL_MUL_9
  *         @arg @ref MS32_RCC_PLL_MUL_10
  *         @arg @ref MS32_RCC_PLL_MUL_11
  *         @arg @ref MS32_RCC_PLL_MUL_12
  *         @arg @ref MS32_RCC_PLL_MUL_13
  *         @arg @ref MS32_RCC_PLL_MUL_14
  *         @arg @ref MS32_RCC_PLL_MUL_15
  *         @arg @ref MS32_RCC_PLL_MUL_16
  */
__STATIC_INLINE uint32_t MS32_RCC_PLL_GetMultiplicator(void) {
  return (uint32_t)(READ_BIT(RCC->CFGR, RCC_CFGR_PLLMUL));
}

/**
  * @brief  Set PREDIV division factor for the main PLL
  * @note They can be written only when the PLL is disabled
  * @rmtoll CFGR2        PREDIV        MS32_RCC_PLL_SetPrediv
  * @param PLLPrediv value can be one of the following values:
  *         @arg @ref MS32_RCC_PREDIV_DIV_1
  *         @arg @ref MS32_RCC_PREDIV_DIV_2
  *         @arg @ref MS32_RCC_PREDIV_DIV_3
  *         @arg @ref MS32_RCC_PREDIV_DIV_4
  *         @arg @ref MS32_RCC_PREDIV_DIV_5
  *         @arg @ref MS32_RCC_PREDIV_DIV_6
  *         @arg @ref MS32_RCC_PREDIV_DIV_7
  *         @arg @ref MS32_RCC_PREDIV_DIV_8
  *         @arg @ref MS32_RCC_PREDIV_DIV_9
  *         @arg @ref MS32_RCC_PREDIV_DIV_10
  *         @arg @ref MS32_RCC_PREDIV_DIV_11
  *         @arg @ref MS32_RCC_PREDIV_DIV_12
  *         @arg @ref MS32_RCC_PREDIV_DIV_13
  *         @arg @ref MS32_RCC_PREDIV_DIV_14
  *         @arg @ref MS32_RCC_PREDIV_DIV_15
  *         @arg @ref MS32_RCC_PREDIV_DIV_16
  * @retval None
  */
__STATIC_INLINE void MS32_RCC_PLL_SetPrediv(uint32_t PLLPrediv) {
  MODIFY_REG(RCC->CFGR2, RCC_CFGR2_PREDIV, PLLPrediv);
}

/**
  * @brief  Get PREDIV division factor for the main PLL
  * @rmtoll CFGR2        PREDIV        MS32_RCC_PLL_GetPrediv
  * @retval Returned value can be one of the following values:
  *         @arg @ref MS32_RCC_PREDIV_DIV_1
  *         @arg @ref MS32_RCC_PREDIV_DIV_2
  *         @arg @ref MS32_RCC_PREDIV_DIV_3
  *         @arg @ref MS32_RCC_PREDIV_DIV_4
  *         @arg @ref MS32_RCC_PREDIV_DIV_5
  *         @arg @ref MS32_RCC_PREDIV_DIV_6
  *         @arg @ref MS32_RCC_PREDIV_DIV_7
  *         @arg @ref MS32_RCC_PREDIV_DIV_8
  *         @arg @ref MS32_RCC_PREDIV_DIV_9
  *         @arg @ref MS32_RCC_PREDIV_DIV_10
  *         @arg @ref MS32_RCC_PREDIV_DIV_11
  *         @arg @ref MS32_RCC_PREDIV_DIV_12
  *         @arg @ref MS32_RCC_PREDIV_DIV_13
  *         @arg @ref MS32_RCC_PREDIV_DIV_14
  *         @arg @ref MS32_RCC_PREDIV_DIV_15
  *         @arg @ref MS32_RCC_PREDIV_DIV_16
  */
__STATIC_INLINE uint32_t MS32_RCC_PLL_GetPrediv(void) {
  return (uint32_t)(READ_BIT(RCC->CFGR2, RCC_CFGR2_PREDIV));
}


/** @defgroup RCC_EF_FLAG_Management FLAG Management
  * @{
  */

/**
  * @brief  Clear LSI ready interrupt flag
  * @rmtoll CIR         LSIRDYC       MS32_RCC_ClearFlag_LSIRDY
  * @retval None
  */
__STATIC_INLINE void MS32_RCC_ClearFlag_LSIRDY(void) {
  SET_BIT(RCC->CIR, RCC_CIR_LSIRDYC);
}

/**
  * @brief  Clear LSE ready interrupt flag
  * @rmtoll CIR         LSERDYC       MS32_RCC_ClearFlag_LSERDY
  * @retval None
  */
__STATIC_INLINE void MS32_RCC_ClearFlag_LSERDY(void) {
  SET_BIT(RCC->CIR, RCC_CIR_LSERDYC);
}

/**
  * @brief  Clear HSI ready interrupt flag
  * @rmtoll CIR         HSIRDYC       MS32_RCC_ClearFlag_HSIRDY
  * @retval None
  */
__STATIC_INLINE void MS32_RCC_ClearFlag_HSIRDY(void) {
  SET_BIT(RCC->CIR, RCC_CIR_HSIRDYC);
}

/**
  * @brief  Clear HSE ready interrupt flag
  * @rmtoll CIR         HSERDYC       MS32_RCC_ClearFlag_HSERDY
  * @retval None
  */
__STATIC_INLINE void MS32_RCC_ClearFlag_HSERDY(void) {
  SET_BIT(RCC->CIR, RCC_CIR_HSERDYC);
}

/**
  * @brief  Clear PLL ready interrupt flag
  * @rmtoll CIR         PLLRDYC       MS32_RCC_ClearFlag_PLLRDY
  * @retval None
  */
__STATIC_INLINE void MS32_RCC_ClearFlag_PLLRDY(void) {
  SET_BIT(RCC->CIR, RCC_CIR_PLLRDYC);
}

/**
  * @brief  Clear Clock security system interrupt flag
  * @rmtoll CIR         CSSC          MS32_RCC_ClearFlag_HSECSS
  * @retval None
  */
__STATIC_INLINE void MS32_RCC_ClearFlag_HSECSS(void) {
  SET_BIT(RCC->CIR, RCC_CIR_CSSC);
}

/**
  * @brief  Check if LSI ready interrupt occurred or not
  * @rmtoll CIR         LSIRDYF       MS32_RCC_IsActiveFlag_LSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_RCC_IsActiveFlag_LSIRDY(void) {
  return (READ_BIT(RCC->CIR, RCC_CIR_LSIRDYF) == (RCC_CIR_LSIRDYF));
}

/**
  * @brief  Check if LSE ready interrupt occurred or not
  * @rmtoll CIR         LSERDYF       MS32_RCC_IsActiveFlag_LSERDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_RCC_IsActiveFlag_LSERDY(void) {
  return (READ_BIT(RCC->CIR, RCC_CIR_LSERDYF) == (RCC_CIR_LSERDYF));
}

/**
  * @brief  Check if HSI ready interrupt occurred or not
  * @rmtoll CIR         HSIRDYF       MS32_RCC_IsActiveFlag_HSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_RCC_IsActiveFlag_HSIRDY(void) {
  return (READ_BIT(RCC->CIR, RCC_CIR_HSIRDYF) == (RCC_CIR_HSIRDYF));
}

/**
  * @brief  Check if HSE ready interrupt occurred or not
  * @rmtoll CIR         HSERDYF       MS32_RCC_IsActiveFlag_HSERDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_RCC_IsActiveFlag_HSERDY(void) {
  return (READ_BIT(RCC->CIR, RCC_CIR_HSERDYF) == (RCC_CIR_HSERDYF));
}

/**
  * @brief  Check if PLL ready interrupt occurred or not
  * @rmtoll CIR         PLLRDYF       MS32_RCC_IsActiveFlag_PLLRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_RCC_IsActiveFlag_PLLRDY(void) {
  return (READ_BIT(RCC->CIR, RCC_CIR_PLLRDYF) == (RCC_CIR_PLLRDYF));
}

/**
  * @brief  Check if Clock security system interrupt occurred or not
  * @rmtoll CIR         CSSF          MS32_RCC_IsActiveFlag_HSECSS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_RCC_IsActiveFlag_HSECSS(void) {
  return (READ_BIT(RCC->CIR, RCC_CIR_CSSF) == (RCC_CIR_CSSF));
}

/**
  * @brief  Check if RCC flag Independent Watchdog reset is set or not.
  * @rmtoll CSR          IWDGRSTF      MS32_RCC_IsActiveFlag_IWDGRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_RCC_IsActiveFlag_IWDGRST(void) {
  return (READ_BIT(RCC->CSR, RCC_CSR_IWDGRSTF) == (RCC_CSR_IWDGRSTF));
}

/**
  * @brief  Check if RCC flag Low Power reset is set or not.
  * @rmtoll CSR          LPWRRSTF      MS32_RCC_IsActiveFlag_LPWRRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_RCC_IsActiveFlag_LPWRRST(void) {
  return (READ_BIT(RCC->CSR, RCC_CSR_LPWRRSTF) == (RCC_CSR_LPWRRSTF));
}

/**
  * @brief  Check if RCC flag is set or not.
  * @rmtoll CSR          OBLRSTF       MS32_RCC_IsActiveFlag_OBLRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_RCC_IsActiveFlag_OBLRST(void) {
  return (READ_BIT(RCC->CSR, RCC_CSR_OBLRSTF) == (RCC_CSR_OBLRSTF));
}

/**
  * @brief  Check if RCC flag Pin reset is set or not.
  * @rmtoll CSR          PINRSTF       MS32_RCC_IsActiveFlag_PINRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_RCC_IsActiveFlag_PINRST(void) {
  return (READ_BIT(RCC->CSR, RCC_CSR_PINRSTF) == (RCC_CSR_PINRSTF));
}

/**
  * @brief  Check if RCC flag POR/PDR reset is set or not.
  * @rmtoll CSR          PORRSTF       MS32_RCC_IsActiveFlag_PORRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_RCC_IsActiveFlag_PORRST(void) {
  return (READ_BIT(RCC->CSR, RCC_CSR_PORRSTF) == (RCC_CSR_PORRSTF));
}

/**
  * @brief  Check if RCC flag Software reset is set or not.
  * @rmtoll CSR          SFTRSTF       MS32_RCC_IsActiveFlag_SFTRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_RCC_IsActiveFlag_SFTRST(void) {
  return (READ_BIT(RCC->CSR, RCC_CSR_SFTRSTF) == (RCC_CSR_SFTRSTF));
}

/**
  * @brief  Check if RCC flag Window Watchdog reset is set or not.
  * @rmtoll CSR          WWDGRSTF      MS32_RCC_IsActiveFlag_WWDGRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_RCC_IsActiveFlag_WWDGRST(void) {
  return (READ_BIT(RCC->CSR, RCC_CSR_WWDGRSTF) == (RCC_CSR_WWDGRSTF));
}

/**
  * @brief  Check if RCC Reset flag of the 1.5 V domain is set or not.
  * @rmtoll CSR          V18PWRRSTF    MS32_RCC_IsActiveFlag_V18PWRRST
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_RCC_IsActiveFlag_V15PWRRST(void) {
  return (READ_BIT(RCC->CSR, RCC_CSR_V15PWRRSTF) == (RCC_CSR_V15PWRRSTF));
}

/**
  * @brief  Set RMVF bit to clear the reset flags.
  * @rmtoll CSR          RMVF          MS32_RCC_ClearResetFlags
  * @retval None
  */
__STATIC_INLINE void MS32_RCC_ClearResetFlags(void) {
  SET_BIT(RCC->CSR, RCC_CSR_RMVF);
}


/** @defgroup RCC_EF_IT_Management IT Management
  * @{
  */

/**
  * @brief  Enable LSI ready interrupt
  * @rmtoll CIR         LSIRDYIE      MS32_RCC_EnableIT_LSIRDY
  * @retval None
  */
__STATIC_INLINE void MS32_RCC_EnableIT_LSIRDY(void) {
  SET_BIT(RCC->CIR, RCC_CIR_LSIRDYIE);
}

/**
  * @brief  Enable LSE ready interrupt
  * @rmtoll CIR         LSERDYIE      MS32_RCC_EnableIT_LSERDY
  * @retval None
  */
__STATIC_INLINE void MS32_RCC_EnableIT_LSERDY(void) {
  SET_BIT(RCC->CIR, RCC_CIR_LSERDYIE);
}

/**
  * @brief  Enable HSI ready interrupt
  * @rmtoll CIR         HSIRDYIE      MS32_RCC_EnableIT_HSIRDY
  * @retval None
  */
__STATIC_INLINE void MS32_RCC_EnableIT_HSIRDY(void) {
  SET_BIT(RCC->CIR, RCC_CIR_HSIRDYIE);
}

/**
  * @brief  Enable HSE ready interrupt
  * @rmtoll CIR         HSERDYIE      MS32_RCC_EnableIT_HSERDY
  * @retval None
  */
__STATIC_INLINE void MS32_RCC_EnableIT_HSERDY(void) {
  SET_BIT(RCC->CIR, RCC_CIR_HSERDYIE);
}

/**
  * @brief  Enable PLL ready interrupt
  * @rmtoll CIR         PLLRDYIE      MS32_RCC_EnableIT_PLLRDY
  * @retval None
  */
__STATIC_INLINE void MS32_RCC_EnableIT_PLLRDY(void) {
  SET_BIT(RCC->CIR, RCC_CIR_PLLRDYIE);
}

/**
  * @brief  Disable LSI ready interrupt
  * @rmtoll CIR         LSIRDYIE      MS32_RCC_DisableIT_LSIRDY
  * @retval None
  */
__STATIC_INLINE void MS32_RCC_DisableIT_LSIRDY(void) {
  CLEAR_BIT(RCC->CIR, RCC_CIR_LSIRDYIE);
}

/**
  * @brief  Disable LSE ready interrupt
  * @rmtoll CIR         LSERDYIE      MS32_RCC_DisableIT_LSERDY
  * @retval None
  */
__STATIC_INLINE void MS32_RCC_DisableIT_LSERDY(void) {
  CLEAR_BIT(RCC->CIR, RCC_CIR_LSERDYIE);
}

/**
  * @brief  Disable HSI ready interrupt
  * @rmtoll CIR         HSIRDYIE      MS32_RCC_DisableIT_HSIRDY
  * @retval None
  */
__STATIC_INLINE void MS32_RCC_DisableIT_HSIRDY(void) {
  CLEAR_BIT(RCC->CIR, RCC_CIR_HSIRDYIE);
}

/**
  * @brief  Disable HSE ready interrupt
  * @rmtoll CIR         HSERDYIE      MS32_RCC_DisableIT_HSERDY
  * @retval None
  */
__STATIC_INLINE void MS32_RCC_DisableIT_HSERDY(void) {
  CLEAR_BIT(RCC->CIR, RCC_CIR_HSERDYIE);
}

/**
  * @brief  Disable PLL ready interrupt
  * @rmtoll CIR         PLLRDYIE      MS32_RCC_DisableIT_PLLRDY
  * @retval None
  */
__STATIC_INLINE void MS32_RCC_DisableIT_PLLRDY(void) {
  CLEAR_BIT(RCC->CIR, RCC_CIR_PLLRDYIE);
}

/**
  * @brief  Checks if LSI ready interrupt source is enabled or disabled.
  * @rmtoll CIR         LSIRDYIE      MS32_RCC_IsEnabledIT_LSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_RCC_IsEnabledIT_LSIRDY(void) {
  return (READ_BIT(RCC->CIR, RCC_CIR_LSIRDYIE) == (RCC_CIR_LSIRDYIE));
}

/**
  * @brief  Checks if LSE ready interrupt source is enabled or disabled.
  * @rmtoll CIR         LSERDYIE      MS32_RCC_IsEnabledIT_LSERDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_RCC_IsEnabledIT_LSERDY(void) {
  return (READ_BIT(RCC->CIR, RCC_CIR_LSERDYIE) == (RCC_CIR_LSERDYIE));
}

/**
  * @brief  Checks if HSI ready interrupt source is enabled or disabled.
  * @rmtoll CIR         HSIRDYIE      MS32_RCC_IsEnabledIT_HSIRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_RCC_IsEnabledIT_HSIRDY(void) {
  return (READ_BIT(RCC->CIR, RCC_CIR_HSIRDYIE) == (RCC_CIR_HSIRDYIE));
}

/**
  * @brief  Checks if HSE ready interrupt source is enabled or disabled.
  * @rmtoll CIR         HSERDYIE      MS32_RCC_IsEnabledIT_HSERDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_RCC_IsEnabledIT_HSERDY(void) {
  return (READ_BIT(RCC->CIR, RCC_CIR_HSERDYIE) == (RCC_CIR_HSERDYIE));
}

/**
  * @brief  Checks if PLL ready interrupt source is enabled or disabled.
  * @rmtoll CIR         PLLRDYIE      MS32_RCC_IsEnabledIT_PLLRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t MS32_RCC_IsEnabledIT_PLLRDY(void) {
  return (READ_BIT(RCC->CIR, RCC_CIR_PLLRDYIE) == (RCC_CIR_PLLRDYIE));
}


/** @defgroup RCC_EF_Init De-initialization function
  * @{
  */
ErrorStatus MS32_RCC_DeInit      (void);
ErrorStatus MS32_RCC_OscConfig   (MS32_RCC_OscInitTypeDef *OscInitStr);
ErrorStatus MS32_RCC_PllConfig   (MS32_RCC_PllInitTypeDef *PllInitStr);
ErrorStatus MS32_RCC_ClockConfig (MS32_RCC_ClkInitTypeDef *ClkInitStr);
void        MS32_RCC_ITConfig    (uint32_t InterruptFunc, uint32_t Priority);

/** @defgroup WWDG_EF_Application function
  * @{
  */
void        MS32_RCC_GetOscConfig   (MS32_RCC_OscInitTypeDef *OscInitStr);
void        MS32_RCC_GetPllConfig   (MS32_RCC_PllInitTypeDef *PllInitStr);
void        MS32_RCC_GetClockConfig (MS32_RCC_ClkInitTypeDef *ClkInitStr);
void        MS32_RCC_MCOConfig      (uint32_t McoSource, uint32_t McoDiv);
void        MS32_RCC_CSS            (FunctionalState CssState);
FlagStatus  MS32_RCC_GetStatusFlag  (uint32_t Flags);
uint32_t    MS32_RCC_GetResetFlag   (FunctionalState FlagClrCtrl);

/** @defgroup RCC_EF_Get_Freq Get system and peripherals clocks frequency functions
  * @{
  */
void     MS32_RCC_GetSystemClocksFreq (MS32_RCC_ClocksTypeDef *RccClocks);
uint32_t MS32_RCC_GetUSARTClockFreq   (uint32_t UsartxSource);
uint32_t MS32_RCC_GetI2CClockFreq     (uint32_t I2cxSource);


#ifdef __cplusplus
}
#endif

#endif /* __MS32F0XX_RCC_H */

/******************************** END OF FILE *********************************/
