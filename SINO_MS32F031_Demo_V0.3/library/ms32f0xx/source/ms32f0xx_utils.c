/* Includes ------------------------------------------------------------------*/
#include "ms32f0xx_rcc.h"
#include "ms32f0xx_utils.h"
#include "ms32f0xx_system.h"


/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @addtogroup UTILS_Private_Constants
  * @{
  */

/* Defines used for PLL range */
#define UTILS_PLL_OUTPUT_MIN        16000000U       /*!< Frequency min for PLL output, in Hz  */
#define UTILS_PLL_OUTPUT_MAX        48000000U       /*!< Frequency max for PLL output, in Hz  */

/* Defines used for HSE range */
#define UTILS_HSE_FREQUENCY_MIN      4000000U       /*!< Frequency min for HSE frequency, in Hz   */
#define UTILS_HSE_FREQUENCY_MAX     32000000U       /*!< Frequency max for HSE frequency, in Hz   */

/* Defines used for FLASH latency according to SYSCLK Frequency */
#define UTILS_LATENCY1_FREQ         24000000U       /*!< SYSCLK frequency to set FLASH latency 1 */


/* Private macros ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup UTILS_Private_Functions UTILS Private functions
  * @{
  */
static uint32_t    UTILS_GetPLLOutputFrequency(uint32_t PLL_InputFrequency, MS32_UTILS_PLLInitTypeDef *UTILS_PLLInitStruct);
static ErrorStatus UTILS_SetFlashLatency(uint32_t Frequency);
static ErrorStatus UTILS_EnablePLLAndSwitchSystem(uint32_t SYSCLK_Frequency, MS32_UTILS_ClkInitTypeDef *UTILS_ClkInitStruct);
static ErrorStatus UTILS_PLL_IsBusy(void);


/* Exported functions --------------------------------------------------------*/
/** @addtogroup UTILS_EF_DELAY
  * @{
  */

/**
  * @brief  This function configures the Cortex-M SysTick source to have 1ms time base.
  * @note   When a RTOS is used, it is recommended to avoid changing the Systick
  *         configuration by calling this function, for a delay use rather osDelay RTOS service.
  * @param  HCLKFrequency HCLK frequency in Hz
  * @note   HCLK frequency can be calculated thanks to RCC helper macro or function @ref MS32_RCC_GetSystemClocksFreq
  * @retval None
  */
void MS32_Init1msTick(uint32_t HCLKFrequency) {
  /* Use frequency provided in argument */
  MS32_InitTick(HCLKFrequency, 1000U);
}

/**
  * @brief  This function provides accurate delay (in milliseconds) based
  *         on SysTick counter flag
  * @note   When a RTOS is used, it is recommended to avoid using blocking delay
  *         and use rather osDelay service.
  * @note   To respect 1ms timebase, user should call @ref MS32_Init1msTick function which
  *         will configure Systick to 1ms
  * @param  Delay specifies the delay time length, in milliseconds.
  * @retval None
  */
void MS32_mDelay(uint32_t Delay) {
  __IO uint32_t  tmp = SysTick->CTRL;  /* Clear the COUNTFLAG first */
  /* Add this code to indicate that local variable is not used */
  ((void)tmp);

  /* Add a period to guaranty minimum wait */
  if (Delay < MS32_MAX_DELAY) {
    Delay++;
  }

  while (Delay) {
    if ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) != 0U) {
      Delay--;
    }
  }
}


/** @addtogroup UTILS_EF_SYSTEM
  *  @brief    System Configuration functions
  *
  @verbatim
 ===============================================================================
           ##### System Configuration functions #####
 ===============================================================================
    [..]
         System, AHB and APB buses clocks configuration

         (+) The maximum frequency of the SYSCLK, HCLK, PCLK1 and PCLK2 is 48000000 Hz.
  @endverbatim
  @internal
             Depending on the SYSCLK frequency, the flash latency should be adapted accordingly:
             (++) +-----------------------------------------------+
             (++) | Latency       | SYSCLK clock frequency (MHz)  |
             (++) |---------------|-------------------------------|
             (++) |0WS(1CPU cycle)|       0 < SYSCLK <= 24        |
             (++) |---------------|-------------------------------|
             (++) |1WS(2CPU cycle)|      24 < SYSCLK <= 48        |
             (++) +-----------------------------------------------+
  @endinternal
  * @{
  */

/**
  * @brief  This function sets directly SystemCoreClock CMSIS variable.
  * @note   Variable can be calculated also through SystemCoreClockUpdate function.
  * @param  HCLKFrequency HCLK frequency in Hz (can be calculated thanks to RCC helper macro)
  * @retval None
  */
void MS32_SetSystemCoreClock(uint32_t HCLKFrequency) {
  /* HCLK clock frequency */
  SystemCoreClock = HCLKFrequency;
}

/**
  * @brief  This function configures system clock with HSI as clock source of the PLL
  * @note   The application need to ensure that PLL is disabled.
  * @note   Function is based on the following formula:
  *         - PLL output frequency = ((HSI frequency / PREDIV) * PLLMUL)
  *         - PREDIV: Set to 2 for few devices
  *         - PLLMUL: The application software must set correctly the PLL multiplication factor to
  *                   be in the range 16-48MHz
  * @note   FLASH latency can be modified through this function.
  * @param  UTILS_PLLInitStruct pointer to a @ref MS32_UTILS_PLLInitTypeDef structure that contains
  *                             the configuration information for the PLL.
  * @param  UTILS_ClkInitStruct pointer to a @ref MS32_UTILS_ClkInitTypeDef structure that contains
  *                             the configuration information for the BUS prescalers.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: Max frequency configuration done
  *          - ERROR: Max frequency configuration not done
  */
ErrorStatus MS32_PLL_ConfigSystemClock_HSI(MS32_UTILS_PLLInitTypeDef *UTILS_PLLInitStruct,
                                           MS32_UTILS_ClkInitTypeDef *UTILS_ClkInitStruct) {
  ErrorStatus status = SUCCESS;
  uint32_t pllfreq = 0U;

  /* Check if one of the PLL is enabled */
  if (UTILS_PLL_IsBusy() == SUCCESS) {
    /* Force PREDIV value to 2 */
    UTILS_PLLInitStruct->Prediv = MS32_RCC_PREDIV_DIV_2;
    /* Calculate the new PLL output frequency */
    pllfreq = UTILS_GetPLLOutputFrequency(HSI_VALUE, UTILS_PLLInitStruct);

    /* Enable HSI if not enabled */
    if (MS32_RCC_HSI_IsReady() != 1U) {
      MS32_RCC_HSI_Enable();
      while (MS32_RCC_HSI_IsReady() != 1U) {
        /* Wait for HSI ready */
      }
    }

    /* Configure PLL */
    MS32_RCC_PLL_ConfigDomain_SYS(MS32_RCC_PLLSOURCE_HSI_DIV_2, UTILS_PLLInitStruct->PLLMul);

    /* Enable PLL and switch system clock to PLL */
    status = UTILS_EnablePLLAndSwitchSystem(pllfreq, UTILS_ClkInitStruct);
  } else {
    /* Current PLL configuration cannot be modified */
    status = ERROR;
  }

  return status;
}

/**
  * @brief  This function configures system clock with HSE as clock source of the PLL
  * @note   The application need to ensure that PLL is disabled.
  * @note   Function is based on the following formula:
  *         - PLL output frequency = ((HSE frequency / PREDIV) * PLLMUL)
  *         - PLLMUL: The application software must set correctly the PLL multiplication factor to
  *                   be in the range 16-48MHz
  * @note   FLASH latency can be modified through this function.
  * @param  HSEFrequency Value between Min_Data = 4000000 and Max_Data = 32000000
  * @param  HSEBypass This parameter can be one of the following values:
  *         @arg @ref MS32_UTILS_HSEBYPASS_ON
  *         @arg @ref MS32_UTILS_HSEBYPASS_OFF
  * @param  UTILS_PLLInitStruct pointer to a @ref MS32_UTILS_PLLInitTypeDef structure that contains
  *                             the configuration information for the PLL.
  * @param  UTILS_ClkInitStruct pointer to a @ref MS32_UTILS_ClkInitTypeDef structure that contains
  *                             the configuration information for the BUS prescalers.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: Max frequency configuration done
  *          - ERROR: Max frequency configuration not done
  */
ErrorStatus MS32_PLL_ConfigSystemClock_HSE(uint32_t HSEFrequency, uint32_t HSEBypass,
                                         MS32_UTILS_PLLInitTypeDef *UTILS_PLLInitStruct, MS32_UTILS_ClkInitTypeDef *UTILS_ClkInitStruct) {
  ErrorStatus status = SUCCESS;
  uint32_t pllfreq = 0U;

  /* Check if one of the PLL is enabled */
  if (UTILS_PLL_IsBusy() == SUCCESS) {
    /* Calculate the new PLL output frequency */
    pllfreq = UTILS_GetPLLOutputFrequency(HSEFrequency, UTILS_PLLInitStruct);

    /* Enable HSE if not enabled */
    if (MS32_RCC_HSE_IsReady() != 1U) {
      /* Check if need to enable HSE bypass feature or not */
      if (HSEBypass == MS32_UTILS_HSEBYPASS_ON) {
        MS32_RCC_HSE_EnableBypass();
      } else {
        MS32_RCC_HSE_DisableBypass();
      }

      /* Enable HSE */
      MS32_RCC_HSE_Enable();
      while (MS32_RCC_HSE_IsReady() != 1U) {
        /* Wait for HSE ready */
      }
    }

    /* Configure PLL */
    MS32_RCC_PLL_ConfigDomain_SYS((RCC_CFGR_PLLSRC_HSE_PREDIV | UTILS_PLLInitStruct->Prediv), UTILS_PLLInitStruct->PLLMul);

    /* Enable PLL and switch system clock to PLL */
    status = UTILS_EnablePLLAndSwitchSystem(pllfreq, UTILS_ClkInitStruct);
  } else {
    /* Current PLL configuration cannot be modified */
    status = ERROR;
  }

  return status;
}


/** @addtogroup UTILS_LL_Private_Functions
  * @{
  */

/**
  * @brief  Update number of Flash wait states in line with new frequency and current
            voltage range.
  * @param  Frequency  SYSCLK frequency
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: Latency has been modified
  *          - ERROR: Latency cannot be modified
  */
static ErrorStatus UTILS_SetFlashLatency(uint32_t Frequency) {
  ErrorStatus status = SUCCESS;

  uint32_t latency = MS32_FLASH_LATENCY_0;  /* default value 0WS */

  /* Frequency cannot be equal to 0 */
  if (Frequency == 0U) {
    status = ERROR;
  } else {
    if (Frequency > UTILS_LATENCY1_FREQ) {
      /* 24 < SYSCLK <= 48 => 1WS (2 CPU cycles) */
      latency = MS32_FLASH_LATENCY_1;
    }
    /* else SYSCLK < 24MHz default MS32_FLASH_LATENCY_0 0WS */

    MS32_FLASH_SetLatency(latency);

    /* Check that the new number of wait states is taken into account to access the Flash
       memory by reading the FLASH_ACR register */
    if (MS32_FLASH_GetLatency() != latency) {
      status = ERROR;
    }
  }
  return status;
}

/**
  * @brief  Function to check that PLL can be modified
  * @param  PLL_InputFrequency  PLL input frequency (in Hz)
  * @param  UTILS_PLLInitStruct pointer to a @ref MS32_UTILS_PLLInitTypeDef structure that contains
  *                             the configuration information for the PLL.
  * @retval PLL output frequency (in Hz)
  */
static uint32_t UTILS_GetPLLOutputFrequency(uint32_t PLL_InputFrequency, MS32_UTILS_PLLInitTypeDef *UTILS_PLLInitStruct) {
  uint32_t pllfreq = 0U;

  /* Check different PLL parameters according to RM                          */
  /* The application software must set correctly the PLL multiplication factor to
     be in the range 16-48MHz */
  pllfreq = __MS32_RCC_CALC_PLLCLK_FREQ(PLL_InputFrequency / (UTILS_PLLInitStruct->Prediv + 1U), UTILS_PLLInitStruct->PLLMul);

  return pllfreq;
}

/**
  * @brief  Function to check that PLL can be modified
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: PLL modification can be done
  *          - ERROR: PLL is busy
  */
static ErrorStatus UTILS_PLL_IsBusy(void) {
  ErrorStatus status = SUCCESS;

  /* Check if PLL is busy*/
  if (MS32_RCC_PLL_IsReady() != 0U) {
    /* PLL configuration cannot be modified */
    status = ERROR;
  }

  return status;
}

/**
  * @brief  Function to enable PLL and switch system clock to PLL
  * @param  SYSCLK_Frequency SYSCLK frequency
  * @param  UTILS_ClkInitStruct pointer to a @ref MS32_UTILS_ClkInitTypeDef structure that contains
  *                             the configuration information for the BUS prescalers.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: No problem to switch system to PLL
  *          - ERROR: Problem to switch system to PLL
  */
static ErrorStatus UTILS_EnablePLLAndSwitchSystem(uint32_t SYSCLK_Frequency, MS32_UTILS_ClkInitTypeDef *UTILS_ClkInitStruct) {
  ErrorStatus status = SUCCESS;
  uint32_t sysclk_frequency_current = 0U;

  /* Calculate current SYSCLK frequency */
  sysclk_frequency_current = (SystemCoreClock << AHBPrescTable[MS32_RCC_GetAHBPrescaler() >> RCC_POSITION_HPRE]);

  /* Increasing the number of wait states because of higher CPU frequency */
  if (sysclk_frequency_current < SYSCLK_Frequency) {
    /* Set FLASH latency to highest latency */
    status = UTILS_SetFlashLatency(SYSCLK_Frequency);
  }

  /* Update system clock configuration */
  if (status == SUCCESS) {
    /* Enable PLL */
    MS32_RCC_PLL_Enable();
    while (MS32_RCC_PLL_IsReady() != 1U) {
      /* Wait for PLL ready */
    }

    /* Sysclk activation on the main PLL */
    MS32_RCC_SetAHBPrescaler(UTILS_ClkInitStruct->AHBCLKDivider);
    MS32_RCC_SetSysClkSource(MS32_RCC_SYS_CLKSOURCE_PLL);
    while (MS32_RCC_GetSysClkSource() != MS32_RCC_SYS_CLKSOURCE_STATUS_PLL) {
      /* Wait for system clock switch to PLL */
    }

    /* Set APB1 & APB2 prescaler*/
    MS32_RCC_SetAPB1Prescaler(UTILS_ClkInitStruct->APB1CLKDivider);
  }

  /* Decreasing the number of wait states because of lower CPU frequency */
  if (sysclk_frequency_current > SYSCLK_Frequency) {
    /* Set FLASH latency to lowest latency */
    status = UTILS_SetFlashLatency(SYSCLK_Frequency);
  }

  /* Update SystemCoreClock variable */
  if (status == SUCCESS) {
    MS32_SetSystemCoreClock(__MS32_RCC_CALC_HCLK_FREQ(SYSCLK_Frequency, UTILS_ClkInitStruct->AHBCLKDivider));
  }

  return status;
}

/******************************** END OF FILE *********************************/
