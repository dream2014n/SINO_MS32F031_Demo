/* Includes ------------------------------------------------------------------*/
#include "ms32f0xx_bus.h"
#include "ms32f0xx_gpio.h"
#include "ms32f0xx_pwr.h"
#include "ms32f0xx_rcc.h"
#include "ms32f0xx_system.h"


/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @defgroup RCC_Over_Time RCC Private Constants
  * @{
  */
#define HSI_READY_TIME        (96)       /* = 2us / (1 / 48MHz) */ 
#define HSE_READY_TIME        (96000)    /* = 2000us / (1 / 48MHz) */  
#define LSI_READY_TIME        (4080)     /* = 85us / (1 / 48MHz) */
#define LSE_READY_TIME        (96000000) /* = 2000000us / (1 / 48MHz) */
#define PLL_READY_TIME        (9600)     /* = 200us / (1 / 48MHz) */
#define PRE_READY_TIME        (100)
#define SYSCLK_SW_TIME        (100)


/** @defgroup RCC_Freq RCC Private Constants
  * @{
  */
#define SYSCLK_DELAY_FREQ1    (24000000)


/** @defgroup FUNC_FLAG Defines
  * @{
  */
#define CLEAR_FLAG_OFFSET     (RCC_CIR_LSIRDYC_Pos - RCC_CIR_LSIRDYF_Pos)


/* Private macros ------------------------------------------------------------*/
/** @defgroup RCC_Private_Macros RCC Private Macros
  * @{
  */
#define MCO_CLK_ENABLE()     MS32_AHB1_GRP1_EnableClock(MS32_AHB1_GRP1_PERIPH_GPIOA)
#define MCO_GPIO_PORT        GPIOA
#define MCO_PIN              MS32_GPIO_PIN_8
#define MCO_AF               MS32_GPIO_AF_0


/* Private function prototypes -----------------------------------------------*/
/** @defgroup RCC_Private_Functions RCC Private functions
  * @{
  */
static uint32_t RCC_GetSystemClockFreq     (uint32_t SYSCLK_Sws);
static uint32_t RCC_GetHCLKClockFreq       (uint32_t SYSCLK_Frequency);
static uint32_t RCC_GetPCLK1ClockFreq      (uint32_t HCLK_Frequency);
static uint32_t RCC_PLL_GetFreqDomain_SYS  (void);


/* Exported functions --------------------------------------------------------*/
/** @addtogroup RCC_EF_Init
  * @{
  */

/**
  * @brief  Reset the RCC clock configuration to the default reset state.
  * @note   The default reset state of the clock configuration is given below:
  *         - HSI ON and used as system clock source
  *         - HSE and PLL OFF
  *         - AHB and APB1 prescaler set to 1.
  *         - CSS, MCO OFF
  *         - All interrupts disabled
  * @note   This function doesn't modify the configuration of the
  *         - Peripheral clocks
  *         - LSI, LSE and RTC clocks
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RCC registers are de-initialized
  *          - ERROR: not applicable
  */
ErrorStatus MS32_RCC_DeInit(void) {
  __IO uint32_t vl_mask;

  /* Set HSION bit */
  MS32_RCC_HSI_Enable();

  /* Wait for HSI READY bit */
  while(MS32_RCC_HSI_IsReady() != 1U) {
    ;
  }

  /* Reset SW, HPRE, PPRE and MCOSEL bits */
  vl_mask = 0xFFFFFFFFU;
  CLEAR_BIT(vl_mask, (RCC_CFGR_SW | RCC_CFGR_HPRE | RCC_CFGR_PPRE | RCC_CFGR_MCO));

  /* Write new value in CFGR register */
  MS32_RCC_WriteReg(CFGR, vl_mask);

  /* Wait till system clock source is ready */
  while(MS32_RCC_GetSysClkSource() != MS32_RCC_SYS_CLKSOURCE_STATUS_HSI) {
    ;
  }

  /* Read CR register */
  vl_mask = MS32_RCC_ReadReg(CR);

  /* Reset HSEON, CSSON, PLLON bits */
  CLEAR_BIT(vl_mask, (RCC_CR_PLLON | RCC_CR_CSSON | RCC_CR_HSEON));

  /* Write new value in CR register */
  MS32_RCC_WriteReg(CR, vl_mask);

  /* Wait for PLL READY bit to be reset */
  while(MS32_RCC_PLL_IsReady() != 0U) {
    ;
  }

  /* Reset HSEBYP bit */
  MS32_RCC_HSE_DisableBypass();

  /* Reset CFGR register */
  MS32_RCC_WriteReg(CFGR, 0x00000000U);

  /* Reset CFGR2 register */
  MS32_RCC_WriteReg(CFGR2, 0x00000000U);

  /* Reset CFGR3 register */
  MS32_RCC_WriteReg(CFGR3, 0x00000000U);

  /* Clear pending flags */
  vl_mask = (MS32_RCC_CIR_LSIRDYC | MS32_RCC_CIR_LSERDYC | MS32_RCC_CIR_HSIRDYC | MS32_RCC_CIR_HSERDYC |\
             MS32_RCC_CIR_PLLRDYC | MS32_RCC_CIR_CSSC);

  /* Write new value in CIR register */
  MS32_RCC_WriteReg(CIR, vl_mask);

  /* Disable all interrupts */
  MS32_RCC_WriteReg(CIR, 0x00000000U);

  /* Clear reset flags */
  MS32_RCC_ClearResetFlags();

  return SUCCESS;
}


/** @defgroup RCC_EF_Config
  * @{
  */

/**
  * @brief  Initializes the RCC Oscillators according to the specified parameters in the
  *         MS32_RCC_OscInitTypeDef.
  * @param  OscInitStr pointer to an MS32_RCC_OscInitTypeDef structure that
  *         contains the configuration information for the RCC Oscillators.
  * @note   Transitions LSE Bypass to LSE On and LSE On to LSE Bypass are not
  *         supported by this macro. User should request a transition to LSE Off
  *         first and then LSE On or LSE Bypass.
  * @note   Transition HSE Bypass to HSE On and HSE On to HSE Bypass are not
  *         supported by this macro. User should request a transition to HSE Off
  *         first and then HSE On or HSE Bypass.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: HSI/HSE/LSI/LSE are initialized
  *          - ERROR: not applicable
  */
ErrorStatus MS32_RCC_OscConfig(MS32_RCC_OscInitTypeDef *OscInitStr) {
  ErrorStatus state = SUCCESS;
  uint32_t    wait_time;
  __IO uint8_t pwr_clk_en_bk, rtc_dm_acc_bk;

  /*------------------------------- HSI Configuration ------------------------*/
  wait_time = HSI_READY_TIME;
  switch (OscInitStr->HSIState) {
    case MS32_RCC_HSI_OFF:
      if ((MS32_RCC_GetSysClkSource() != MS32_RCC_SYS_CLKSOURCE_STATUS_HSI) \
        && (MS32_RCC_PLL_GetMainSource() != MS32_RCC_PLLSOURCE_HSI_DIV_2)) {
        MS32_RCC_HSI_Disable();
        while (MS32_RCC_HSI_IsReady() && (--wait_time));
      } else {
        state = ERROR;
      }
      break;
    case MS32_RCC_HSI_ON:
      MS32_RCC_HSI_Enable();
      while (!MS32_RCC_HSI_IsReady() && (--wait_time));
      break;
    default:
      state = ERROR;
      break;
  }
  if (!wait_time) {
    state = ERROR;
  }

  /*------------------------------- HSE Configuration ------------------------*/
  wait_time = HSE_READY_TIME;
  switch (OscInitStr->HSEState) {
    case MS32_RCC_HSE_OFF:
      if ((MS32_RCC_GetSysClkSource() != MS32_RCC_SYS_CLKSOURCE_STATUS_HSE) \
        && (MS32_RCC_PLL_GetMainSource() != MS32_RCC_PLLSOURCE_HSE)) {
        MS32_RCC_HSE_Disable();
        while (MS32_RCC_HSE_IsReady() && (--wait_time));
        if (wait_time) {
          MS32_RCC_HSE_DisableBypass();
        }
      } else {
        state = ERROR;
      }
      break;
    case MS32_RCC_HSE_BYPASS:
      MS32_RCC_HSE_EnableBypass();
    case MS32_RCC_HSE_ON:
      MS32_RCC_HSE_Enable();
      if (OscInitStr->HSEState == MS32_RCC_HSE_ON) {
        while (!MS32_RCC_HSE_IsReady() && (--wait_time));
      }
      break;
    default:
      state = ERROR;
      break;
  }
  if (!wait_time) {
    state = ERROR;
  }

  /*------------------------------- LSI Configuration ------------------------*/
  wait_time = LSI_READY_TIME;
  switch (OscInitStr->LSIState) {
    case MS32_RCC_LSI_OFF:
      MS32_RCC_LSI_Disable();
      while (MS32_RCC_LSI_IsReady() && (--wait_time));
      break;
    case MS32_RCC_LSI_ON:
      MS32_RCC_LSI_Enable();
      wait_time = LSI_READY_TIME;
      while (!MS32_RCC_LSI_IsReady() && (--wait_time));
      break;
    default:
      state = ERROR;
      break;
  }
  if (!wait_time) {
    state = ERROR;
  }

  /*------------------------------- LSE Configuration ------------------------*/
  wait_time = LSE_READY_TIME;
  pwr_clk_en_bk = MS32_APB1_GRP1_IsEnabledClock(MS32_APB1_GRP1_PERIPH_PWR);
  rtc_dm_acc_bk = MS32_PWR_IsEnabledBkUpAccess();
  MS32_APB1_GRP1_EnableClock(MS32_APB1_GRP1_PERIPH_PWR);
  MS32_PWR_EnableBkUpAccess();
  switch (OscInitStr->LSEState) {
    case MS32_RCC_LSE_OFF:
      MS32_RCC_LSE_Disable();
      while (MS32_RCC_LSE_IsReady() && (--wait_time));
      if (wait_time) {
        MS32_RCC_LSE_DisableBypass();
      }
      break;
    case MS32_RCC_LSE_BYPASS:
      MS32_RCC_LSE_EnableBypass();
    case MS32_RCC_LSE_ON_DRV_L:
    case MS32_RCC_LSE_ON_DRV_ML:
    case MS32_RCC_LSE_ON_DRV_MH:
    case MS32_RCC_LSE_ON_DRV_H:
      MS32_RCC_LSE_SetDriveCapability(OscInitStr->LSEState & RCC_BDCR_LSEDRV);
      MS32_RCC_LSE_Enable();
      while (!MS32_RCC_LSE_IsReady() && (--wait_time));
      break;
    default:
      state = ERROR;
      break;
  }
  if (!rtc_dm_acc_bk) {
    MS32_PWR_DisableBkUpAccess();
  }
  if (!pwr_clk_en_bk) {
    MS32_APB1_GRP1_DisableClock(MS32_APB1_GRP1_PERIPH_PWR);
  }
  if (!wait_time) {
    state = ERROR;
  }

  return state;
}

/**
  * @brief  Configures the OscInitStr according to the internal 
  *         RCC configuration registers.
  * @param  OscInitStr pointer to an MS32_RCC_PllInitTypeDef structure that 
  *         will be configured.
  * @retval None
  */
void MS32_RCC_GetOscConfig(MS32_RCC_OscInitTypeDef *OscInitStr) {
  /* Get the HSI configuration -----------------------------------------------*/
  if (MS32_RCC_HSI_IsReady()) {
    OscInitStr->HSIState = MS32_RCC_HSI_ON;
  } else {
    OscInitStr->HSIState = MS32_RCC_HSI_OFF;
  }

  /* Get the HSE configuration -----------------------------------------------*/
  if (MS32_RCC_HSE_IsBypass()) {
    OscInitStr->HSEState = MS32_RCC_HSE_BYPASS;
  } else if(MS32_RCC_HSE_IsReady()) {
    OscInitStr->HSEState = MS32_RCC_HSE_ON;
  } else {
    OscInitStr->HSEState = MS32_RCC_HSE_OFF;
  }
  
  /* Get the LSI configuration -----------------------------------------------*/
  if(MS32_RCC_LSI_IsReady()) {
    OscInitStr->LSIState = MS32_RCC_LSI_ON;
  } else {
    OscInitStr->LSIState = MS32_RCC_LSI_OFF;
  }

  /* Get the LSE configuration -----------------------------------------------*/
  if (MS32_RCC_LSE_IsBypass()) {
    OscInitStr->LSEState = MS32_RCC_LSE_BYPASS;
  } else if(MS32_RCC_LSE_IsReady()) {
    OscInitStr->LSEState = MS32_RCC_LSE_GetDriveCapability() | RCC_BDCR_LSEON;
  } else {
    OscInitStr->LSEState = MS32_RCC_LSE_OFF;
  }
}

/**
  * @brief  Initializes the RCC PLL according to the specified parameters in the
  *         MS32_RCC_PllInitTypeDef.
  * @param  PllInitStr pointer to an MS32_RCC_PllInitTypeDef structure that
  *         contains the configuration information for the RCC PLL.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: PLL are initialized
  *          - ERROR: not applicable
  */
ErrorStatus MS32_RCC_PllConfig(MS32_RCC_PllInitTypeDef *PllInitStr) {
  ErrorStatus status = SUCCESS;
  uint32_t    wait_time;

  wait_time = PLL_READY_TIME;
  switch (PllInitStr->PLLState) {
    case MS32_RCC_PLL_OFF:
      if (MS32_RCC_GetSysClkSource() != MS32_RCC_SYS_CLKSOURCE_STATUS_PLL) {
        MS32_RCC_PLL_Disable();
        while (MS32_RCC_PLL_IsReady() && (--wait_time));
      } else {
        status = ERROR;
      }
      break;
    case MS32_RCC_PLL_ON:
      if (MS32_RCC_PLL_IsReady()) {
        /* Check whether PLL clock used as system clock or not, when PLL is ready */
        if (MS32_RCC_GetSysClkSource() != MS32_RCC_SYS_CLKSOURCE_STATUS_PLL) {
          /* PLL disable */
          MS32_RCC_PLL_Disable();
          while (MS32_RCC_PLL_IsReady() && (--wait_time));
          if (!wait_time) {
            status = ERROR;
          }
        } else {
          status = ERROR;
        }
      }
      /* Set PLL config and enable PLL */
      if (status == SUCCESS) {
        MS32_RCC_PLL_SetMainSource(PllInitStr->PLLSource);
        MS32_RCC_PLL_SetMultiplicator(PllInitStr->PLLMUL);
        MS32_RCC_PLL_SetPrediv(PllInitStr->PREDIV);
        MS32_RCC_PLL_Enable();
        wait_time = PLL_READY_TIME;
        while (!MS32_RCC_PLL_IsReady() && (--wait_time));
      }
      break;
    default:
      status = ERROR;
      break;
  }
  if (!wait_time) {
    status = ERROR;
  }

  return status;
}

/**
  * @brief  Configures the PllInitStr according to the internal 
  *         RCC configuration registers.
  * @param  PllInitStr pointer to an MS32_RCC_PllInitTypeDef structure that 
  *         will be configured.
  * @retval None
  */
void MS32_RCC_GetPllConfig(MS32_RCC_PllInitTypeDef *PllInitStr) {
  /* Get the PLL configuration -----------------------------------------------*/
  if (MS32_RCC_PLL_IsReady()) {
    PllInitStr->PLLState = MS32_RCC_PLL_ON;
  } else {
    PllInitStr->PLLState = MS32_RCC_PLL_OFF;
  }

  /* Get the PLL clock source ------------------------------------------------*/
  PllInitStr->PLLSource = MS32_RCC_PLL_GetMainSource();

  /* Get the PLL multiplicator -----------------------------------------------*/
  PllInitStr->PLLMUL = MS32_RCC_PLL_GetMultiplicator();

  /* Get the PLL clock prediv ------------------------------------------------*/
  PllInitStr->PREDIV = MS32_RCC_PLL_GetPrediv();
}

/**
  * @brief  Initializes the RCC clock according to the specified parameters in the
  *         MS32_RCC_ClkInitTypeDef.
  * @param  ClkInitStr pointer to an MS32_RCC_ClkInitTypeDef structure that
  *         contains the configuration information for the RCC peripheral.
  * @note   Code enable latency and prefetch when system clock greater than 24MHz.
  *         Code disable latency and prefetch when system clock less than or equal to 24MHz.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: clock are initialized
  *          - ERROR: not applicable
  */
ErrorStatus MS32_RCC_ClockConfig(MS32_RCC_ClkInitTypeDef *ClkInitStr) {
  ErrorStatus status = SUCCESS;
  uint32_t    sysclk, ahb_clk, wait_time;

  /*----------------------------- SYSCLK Configuration -----------------------*/
	ahb_clk = 0xFFFFFFFF;
  switch (ClkInitStr->SYSCLKSource) {
    case MS32_RCC_SYSCLK_SOURCE_HSI:
      sysclk = MS32_RCC_SYS_CLKSOURCE_STATUS_HSI;
      break;
    case MS32_RCC_SYSCLK_SOURCE_HSE:
      sysclk = MS32_RCC_SYS_CLKSOURCE_STATUS_HSE;
      break;
    case MS32_RCC_SYSCLK_SOURCE_PLL:
      sysclk = MS32_RCC_SYS_CLKSOURCE_STATUS_PLL;
      break;
    default:
      ahb_clk = 0;
      break;
  }
  /* Calculate system clock */
  if (ahb_clk) {
    ahb_clk = __MS32_RCC_CALC_HCLK_FREQ(RCC_GetSystemClockFreq(sysclk), ClkInitStr->AHBCLKDivider);
    /* Greater than 24000000 */
    if (ahb_clk > SYSCLK_DELAY_FREQ1) {
      /* Flash delay one time */
      MS32_FLASH_SetLatency(MS32_FLASH_LATENCY_1);
      /* Enable prefetch */
      MS32_FLASH_EnablePrefetch();
      wait_time = PRE_READY_TIME;
      while (!MS32_FLASH_IsPrefetchEnabled() && (--wait_time));
      if (wait_time) {
				/* Change system clock */
        MS32_RCC_SetSysClkSource(ClkInitStr->SYSCLKSource);
        wait_time = SYSCLK_SW_TIME;
        while ((MS32_RCC_GetSysClkSource() != sysclk) && (--wait_time));
        if (wait_time) {
          /* Set AHB and APB clock */
          MS32_RCC_SetAHBPrescaler(ClkInitStr->AHBCLKDivider);
          MS32_RCC_SetAPB1Prescaler(ClkInitStr->APB1CLKDivider);
        } else {
          status = ERROR;
        }
      } else {
        status = ERROR;
      }
    /* Less than or equal to 24000000 */
    } else {
			/* Set AHB and APB clock */
			MS32_RCC_SetAHBPrescaler(ClkInitStr->AHBCLKDivider);
			MS32_RCC_SetAPB1Prescaler(ClkInitStr->APB1CLKDivider);
			/* Change system clock */
      MS32_RCC_SetSysClkSource(ClkInitStr->SYSCLKSource);
      wait_time = SYSCLK_SW_TIME;
      while ((MS32_RCC_GetSysClkSource() != sysclk) && (--wait_time));
      if (wait_time) {
        /* Disable prefetch */
        MS32_FLASH_DisablePrefetch();
        wait_time = PRE_READY_TIME;
        while (MS32_FLASH_IsPrefetchEnabled() && (--wait_time));
        if (wait_time) {
          /* Flash delay no time */
          MS32_FLASH_SetLatency(MS32_FLASH_LATENCY_0);
        } else {
          status = ERROR;
        }
      } else {
        status = ERROR;
      }
    }
  } else {
    status = ERROR;
  }

  return status;
}

/**
  * @brief  Configures the ClkInitStr according to the internal 
  *         RCC configuration registers.
  * @param  ClkInitStr pointer to an MS32_RCC_ClkInitTypeDef structure that 
  *         will be configured.
  * @retval None
  */
void MS32_RCC_GetClockConfig(MS32_RCC_ClkInitTypeDef *ClkInitStr) {
  /* Get system clock configuration ------------------------------------------*/
  switch (MS32_RCC_GetSysClkSource()) {
    case MS32_RCC_SYS_CLKSOURCE_STATUS_HSI:
      ClkInitStr->SYSCLKSource = MS32_RCC_SYSCLK_SOURCE_HSI;
      break;
    case MS32_RCC_SYS_CLKSOURCE_STATUS_HSE:
      ClkInitStr->SYSCLKSource = MS32_RCC_SYSCLK_SOURCE_HSE;
      break;
    case MS32_RCC_SYS_CLKSOURCE_STATUS_PLL:
      ClkInitStr->SYSCLKSource = MS32_RCC_SYSCLK_SOURCE_PLL;
      break;
    default:
      break;
  }

  /* Get the PLL clock source ------------------------------------------------*/
  ClkInitStr->AHBCLKDivider = MS32_RCC_GetAHBPrescaler();

  /* Get the PLL multiplicator -----------------------------------------------*/
  ClkInitStr->APB1CLKDivider = MS32_RCC_GetAPB1Prescaler();
}

/**
  * @brief  Selects the clock source to output on MCO pin.
  * @note   MCO pin should be configured in alternate function mode.
  * @note   This function include gpio configuration.
  * @param  McoSource specifies the clock source to output.
  *          This parameter can be one of the following values:
  *            @arg @ref MS32_MCO_SOURCE_NOCLOCK  No clock selected
  *            @arg @ref MS32_MCO_SOURCE_HSI16    internal RC 16M selected as MCO clock
  *            @arg @ref MS32_MCO_SOURCE_LSI      LSI selected as MCO clock
  *            @arg @ref MS32_MCO_SOURCE_LSE      LSE selected as MCO clock
  *            @arg @ref MS32_MCO_SOURCE_SYSCLK   System Clock selected as MCO clock
  *            @arg @ref MS32_MCO_SOURCE_HSI      HSI selected as MCO clock
  *            @arg @ref MS32_MCO_SOURCE_HSE      HSE selected as MCO clock
  *            @arg @ref MS32_MCO_SOURCE_PLL_DIV2 PLLCLK Divided by 2 selected as MCO clock
  *            @arg @ref MS32_MCO_SOURCE_PLL      PLLCLK selected as MCO clock
  * @param  McoDiv specifies the MCO DIV.
  *          This parameter can be one of the following values:
  *            @arg @ref MS32_MCO_DIV1   no division applied to MCO clock
  *            @arg @ref MS32_MCO_DIV2   division by 2 applied to MCO clock
  *            @arg @ref MS32_MCO_DIV4   division by 4 applied to MCO clock
  *            @arg @ref MS32_MCO_DIV8   division by 8 applied to MCO clock
  *            @arg @ref MS32_MCO_DIV16  division by 16 applied to MCO clock
  *            @arg @ref MS32_MCO_DIV32  division by 32 applied to MCO clock
  *            @arg @ref MS32_MCO_DIV64  division by 64 applied to MCO clock
  *            @arg @ref MS32_MCO_DIV128 division by 128 applied to MCO clock
  * @retval None
  */
void MS32_RCC_MCOConfig(uint32_t McoSource, uint32_t McoDiv) {
  MS32_GPIO_InitTypeDef gpio_init_str;

  /* MCO Clock Enable */
  MCO_CLK_ENABLE();
  /* Configure the MCO pin in alternate function mode */
  gpio_init_str.Mode      = MS32_GPIO_MODE_ALTERNATE;
  gpio_init_str.Speed     = MS32_GPIO_SPEED_FREQ_HIGH;
  gpio_init_str.Pull      = MS32_GPIO_PULL_NO;
  gpio_init_str.Pin       = MCO_PIN;
  gpio_init_str.Alternate = MCO_AF;
  MS32_GPIO_Init(MCO_GPIO_PORT, &gpio_init_str);

  /* Configure the MCO clock source */
  MS32_RCC_ConfigMCO(McoSource, McoDiv);
}

/**
  * @brief  Enable/disable the Clock Security System.
  * @note   If a failure is detected on the HSE oscillator clock, this oscillator
  *         is automatically disabled and an interrupt is generated to inform the
  *         software about the failure (Clock Security System Interrupt, CSSI),
  *         allowing the MCU to perform rescue operations. The CSSI is linked to 
  *         the Cortex-M0 NMI (Non-Maskable Interrupt) exception vector. 
  * @param  CssState specifies the HSE CSS.
  *          This parameter can be one of the following values:
  *            @arg @ref ENABLE  enable the Clock Security System
  *            @arg @ref DISABLE disable the Clock Security System 
  * @retval None
  */
void MS32_RCC_CSS(FunctionalState CssState) {
  if (CssState == ENABLE) {
    MS32_RCC_HSE_EnableCSS();
  } else {
    MS32_RCC_HSE_DisableCSS();
  }
}

/**
  * @brief  Initializes the RCC interrupt according to the specified parameters.
  * @param  InterruptFunc  contains the configuration information for the RCC interrupt.
  *         This parameter can be one or more of the following values:
  *         @arg @ref MS32_RCC_IT_LSIRDYIE  LSI Ready Interrupt Enable
  *         @arg @ref MS32_RCC_IT_LSERDYIE  LSE Ready Interrupt Enable
  *         @arg @ref MS32_RCC_IT_HSIRDYIE  HSI Ready Interrupt Enable
  *         @arg @ref MS32_RCC_IT_HSERDYIE  HSE Ready Interrupt Enable
  *         @arg @ref MS32_RCC_IT_PLLRDYIE  PLL Ready Interrupt Enable
  * @param  Priority  the interrupt priority 
  *         This parameter can be a value of 0x0~0x3
  * @retval None
  */
void MS32_RCC_ITConfig(uint32_t InterruptFunc, uint32_t Priority) {
  /*-------------------------------- ALL Interrrupt --------------------------*/
  SET_BIT(RCC->CIR, (MS32_RCC_FLAG_ALLRDY << CLEAR_FLAG_OFFSET));
  MODIFY_REG(RCC->CIR, MS32_RCC_IT_ALLRDYIE, InterruptFunc);

  /*----------------------------- NVIC configuration -------------------------*/
  if (READ_BIT(RCC->CIR, MS32_RCC_IT_ALLRDYIE)) {
    NVIC_EnableIRQ(RCC_IRQn);
    NVIC_SetPriority(RCC_IRQn, Priority);
  } else {
    NVIC_DisableIRQ(RCC_IRQn);
  }
}

/**
  * @brief  Get the interrupt and error flags according to the internal 
  *         RCC CIR registers.
  * @param  Flags specifies the function flags.
  *          This parameter can be one of the following values:
  *            @arg @ref MS32_FLAG_LSIRDY  the LSI ready flag
  *            @arg @ref MS32_FLAG_LSERDY  the LSE ready flag
  *            @arg @ref MS32_FLAG_HSIRDY  the HSI ready flag
  *            @arg @ref MS32_FLAG_HSERDY  the HSE ready flag
  *            @arg @ref MS32_FLAG_PLLRDY  the PLL ready flag
  *            @arg @ref MS32_FLAG_CSS     the Clock Security System flag
  * @note   Clear flags After getting the interrupt or error flags equal to set. 
  * @retval A FlagStatus enumeration value:
  *          - SET:   flag set(equal to "1")
  *          - RESET: flag no set(equal to "0")
  */
FlagStatus MS32_RCC_GetStatusFlag(uint32_t Flags) {
  FlagStatus flags;

  if (READ_BIT(RCC->CIR, Flags)) {
    flags = SET;
    SET_BIT(RCC->CIR, (Flags << CLEAR_FLAG_OFFSET));
  } else {
    flags = RESET;
  }

  return flags;
}

/**
  * @brief  Get the reset flags according to the internal 
  *         RCC CSR registers.
  * @param  FlagClrCtrl specifies whether clear reset all flag or net.
  *          This parameter can be one of the following values:
  *            @arg @ref ENABLE   clear all reset flag
  *            @arg @ref DISABLE  no action
  * @retval All Flags value(registor):
  *          This parameter can be one or more of the following values:
  *          - MS32_FLAG_OBLRSTF:    OBL reset flag
  *          - MS32_FLAG_PINRSTF:    PIN reset flag
  *          - MS32_FLAG_PORRSTF:    POR/PDR reset flag
  *          - MS32_FLAG_SFTRSTF:    Software Reset flag
  *          - MS32_FLAG_IWDGRSTF:   Independent Watchdog reset flag
  *          - MS32_FLAG_WWDGRSTF:   Window watchdog reset flag
  *          - MS32_FLAG_LPWRRSTF:   Low-Power reset flag
  *          - MS32_FLAG_V15PWRRSTF: Reset flag of the 1.5 V domain
  */
uint32_t MS32_RCC_GetResetFlag(FunctionalState FlagClrCtrl) {
  uint32_t flags;

  flags = READ_BIT(RCC->CSR, MS32_RCC_FLAG_ALLRSTF);
  if (FlagClrCtrl == ENABLE) {
    MS32_RCC_ClearResetFlags();
  }
  return flags;
}


/** @defgroup RCC_EF_Get_Freq
  * @{
  */
/**
  * @brief  Return the frequencies of different on chip clocks;  System, AHB and APB1 buses clocks
  * @note   Each time SYSCLK, HCLK and/or PCLK1 clock changes, this function
  *         must be called to update structure fields. Otherwise, any
  *         configuration based on this function will be incorrect.
  * @param  RCC_Clocks pointer to a @ref MS32_RCC_ClocksTypeDef structure which will hold the clocks frequencies
  * @retval None
  */
void MS32_RCC_GetSystemClocksFreq(MS32_RCC_ClocksTypeDef *RccClocks) {
  /* Get SYSCLK frequency */
  RccClocks->SYSCLK_Frequency = RCC_GetSystemClockFreq(MS32_RCC_GetSysClkSource());

  /* HCLK clock frequency */
  RccClocks->HCLK_Frequency   = RCC_GetHCLKClockFreq(RccClocks->SYSCLK_Frequency);

  /* PCLK1 clock frequency */
  RccClocks->PCLK1_Frequency  = RCC_GetPCLK1ClockFreq(RccClocks->HCLK_Frequency);
}

/**
  * @brief  Return USARTx clock frequency
  * @param  UsartxSource This parameter can be one of the following values:
  *         @arg @ref MS32_RCC_USART1_CLKSOURCE
  * @retval USART clock frequency (in Hz)
  *         @arg @ref MS32_RCC_PERIPH_FREQUENCY_NO indicates that oscillator (HSI or LSE) is not ready
  */
uint32_t MS32_RCC_GetUSARTClockFreq(uint32_t UsartxSource) {
  uint32_t usart_frequency = MS32_RCC_PERIPH_FREQUENCY_NO;

  if (UsartxSource == MS32_RCC_USART1_CLKSOURCE) {
    /* USART1CLK clock frequency */
    switch (MS32_RCC_GetUSARTClockSource(UsartxSource)) {
      case MS32_RCC_USART1_CLKSOURCE_SYSCLK: /* USART1 Clock is System Clock */
        usart_frequency = RCC_GetSystemClockFreq(MS32_RCC_GetSysClkSource());
        break;

      case MS32_RCC_USART1_CLKSOURCE_HSI:    /* USART1 Clock is HSI Osc. */
        if (MS32_RCC_HSI_IsReady()) {
          usart_frequency = HSI_VALUE;
        }
        break;

      case MS32_RCC_USART1_CLKSOURCE_LSE:    /* USART1 Clock is LSE Osc. */
        if (MS32_RCC_LSE_IsReady()) {
          usart_frequency = LSE_VALUE;
        }
        break;

      case MS32_RCC_USART1_CLKSOURCE_PCLK1:  /* USART1 Clock is PCLK1 */
      default:
        usart_frequency = RCC_GetPCLK1ClockFreq(RCC_GetHCLKClockFreq(RCC_GetSystemClockFreq(MS32_RCC_GetSysClkSource())));
        break;
    }
  }
  return usart_frequency;
}

/**
  * @brief  Return I2Cx clock frequency
  * @param  I2cxSource This parameter can be one of the following values:
  *         @arg @ref MS32_RCC_I2C1_CLKSOURCE
  * @retval I2C clock frequency (in Hz)
  *         @arg @ref MS32_RCC_PERIPH_FREQUENCY_NO indicates that HSI oscillator is not ready
  */
uint32_t MS32_RCC_GetI2CClockFreq(uint32_t I2cxSource) {
  uint32_t i2c_frequency = MS32_RCC_PERIPH_FREQUENCY_NO;

  /* I2C1 CLK clock frequency */
  if (I2cxSource == MS32_RCC_I2C1_CLKSOURCE) {
    switch (MS32_RCC_GetI2CClockSource(I2cxSource)) {
      case MS32_RCC_I2C1_CLKSOURCE_SYSCLK: /* I2C1 Clock is System Clock */
        i2c_frequency = RCC_GetSystemClockFreq(MS32_RCC_GetSysClkSource());
        break;

      case MS32_RCC_I2C1_CLKSOURCE_HSI:    /* I2C1 Clock is HSI Osc. */
      default:
        if (MS32_RCC_HSI_IsReady()) {
          i2c_frequency = HSI_VALUE;
        }
        break;
    }
  }

  return i2c_frequency;
}


/** @addtogroup RCC_MS32_Private_Functions
  * @{
  */

/**
  * @brief  Return SYSTEM clock frequency
  * @param  SYSCLK_Sws This parameter can be one of the following values:
  *         @arg @ref MS32_RCC_SYS_CLKSOURCE_STATUS_HSI
  *         @arg @ref MS32_RCC_SYS_CLKSOURCE_STATUS_HSE
  *         @arg @ref MS32_RCC_SYS_CLKSOURCE_STATUS_PLL
  * @retval SYSTEM clock frequency (in Hz)
  */
static uint32_t RCC_GetSystemClockFreq(uint32_t SYSCLK_Sws) {
  uint32_t frequency = 0U;

  /* Get SYSCLK source -------------------------------------------------------*/
  switch (SYSCLK_Sws) {
    case MS32_RCC_SYS_CLKSOURCE_STATUS_HSI:  /* HSI used as system clock source */
      frequency = HSI_VALUE;
      break;

    case MS32_RCC_SYS_CLKSOURCE_STATUS_HSE:  /* HSE used as system clock source */
      frequency = HSE_VALUE;
      break;

    case MS32_RCC_SYS_CLKSOURCE_STATUS_PLL:  /* PLL used as system clock source */
      frequency = RCC_PLL_GetFreqDomain_SYS();
      break;

    default:
      frequency = HSI_VALUE;
      break;
  }

  return frequency;
}

/**
  * @brief  Return HCLK clock frequency
  * @param  SYSCLK_Frequency SYSCLK clock frequency
  * @retval HCLK clock frequency (in Hz)
  */
static uint32_t RCC_GetHCLKClockFreq(uint32_t SYSCLK_Frequency) {
  /* HCLK clock frequency */
  return __MS32_RCC_CALC_HCLK_FREQ(SYSCLK_Frequency, MS32_RCC_GetAHBPrescaler());
}

/**
  * @brief  Return PCLK1 clock frequency
  * @param  HCLK_Frequency HCLK clock frequency
  * @retval PCLK1 clock frequency (in Hz)
  */
static uint32_t RCC_GetPCLK1ClockFreq(uint32_t HCLK_Frequency) {
  /* PCLK1 clock frequency */
  return __MS32_RCC_CALC_PCLK1_FREQ(HCLK_Frequency, MS32_RCC_GetAPB1Prescaler());
}

/**
  * @brief  Return PLL clock frequency used for system domain
  * @retval PLL clock frequency (in Hz)
  */
static uint32_t RCC_PLL_GetFreqDomain_SYS(void) {
  uint32_t pllinputfreq = 0U, pllsource = 0U;

  /* PLL_VCO = (HSE_VALUE or HSI_VALUE / PLL divider) * PLL Multiplicator */

  /* Get PLL source */
  pllsource = MS32_RCC_PLL_GetMainSource();

  switch (pllsource) {
    case MS32_RCC_PLLSOURCE_HSI_DIV_2: /* HSI used as PLL clock source */
      pllinputfreq = HSI_VALUE >> 1U;
      break;

    case MS32_RCC_PLLSOURCE_HSE:       /* HSE used as PLL clock source */
      pllinputfreq = HSE_VALUE;
      break;

    default:
      pllinputfreq = HSI_VALUE >> 1U;
      break;
  }

  return __MS32_RCC_CALC_PLLCLK_FREQ((pllinputfreq / (MS32_RCC_PLL_GetPrediv() + 1U)), MS32_RCC_PLL_GetMultiplicator());
}


/******************************** END OF FILE *********************************/
