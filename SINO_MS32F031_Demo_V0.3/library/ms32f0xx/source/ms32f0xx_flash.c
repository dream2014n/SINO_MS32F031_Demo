/* Includes ------------------------------------------------------------------*/
#include "ms32f0xx_flash.h"


/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @defgroup FLASH_Size FLASH Private Constants
  * @{
  */
#define MAIN_FLASH_START_ADDR      (0x08000000)
#define MAIN_FLASH_SIZE            (0x8000)
#define MAIN_FLASH_PAGE_SIZE       (0x400)
#define MAIN_FLASH_PAGE_MAX        (31)
#define OPTIONBYTE_START_ADDR      (0x1FFFF800)
#define OPTIONBYTE_SIZE            (16)
#define OPTIONBYTE_MAX             (OPTIONBYTE_SIZE - 1)


/* Private macros ------------------------------------------------------------*/
/** @defgroup FLASH_Type FLASH Private Macros
  * @{
  */
#define TYPE8(addr)                (*((volatile uint8_t *) (addr)))
#define TYPE16(addr)               (*((volatile uint16_t *) (addr)))
#define TYPE32(addr)               (*((volatile uint32_t *) (addr)))


/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @defgroup FLASH_EF_Config
  * @{
  */
/**
  * @brief  Initializes the FLASH interrupt according to the specified parameters.
  * @param  InterruptFunc  contains the configuration information for the FLASH interrupt.
  *         This parameter can be one or more of the following values:
  *         @arg @ref MS32_FLASH_IT_ERRIE  FLASH Error Interrupt Enable
  *         @arg @ref MS32_FLASH_IT_EOPIE  FLASH End of operation Interrupt Enable
  * @param  Priority  the interrupt priority 
  *         This parameter can be a value of 0x0~0x3
  * @retval None
  */
void MS32_FLASH_ITConfig(uint32_t InterruptFunc, uint32_t Priority) {
  /*-------------------------------- ALL Interrrupt --------------------------*/
  WRITE_REG(FLASH->SR, MS32_FLASH_FLAG_ALLFSH);
  MODIFY_REG(FLASH->CR, MS32_FLASH_IT_ALLFSHIE, InterruptFunc);

  /*----------------------------- NVIC configuration -------------------------*/
  if (READ_BIT(FLASH->CR, MS32_FLASH_IT_ALLFSHIE)) {
    NVIC_EnableIRQ(FLASH_IRQn);
    NVIC_SetPriority(FLASH_IRQn, Priority);
  } else {
    NVIC_DisableIRQ(FLASH_IRQn);
  }
}

/**
  * @brief  Get the FLASH interrupt and error flags according to the internal 
  *         FLASH SR registers.
  * @param  Flags specifies the function flags.
  *          This parameter can be one of the following values:
  *            @arg @ref MS32_FLAG_FSHPGERR  the FLASH programme error flag
  *            @arg @ref MS32_FLAG_FSHWRERR  the FLASH write error flag
  *            @arg @ref MS32_FLAG_FSHEOP    the FLASH end of operartion flag
  * @note   Clear flags After getting the interrupt or error flags equal to set. 
  * @retval A FlagStatus enumeration value:
  *          - SET:   flag set(equal to "1")
  *          - RESET: flag no set(equal to "0")
  */
FlagStatus MS32_FLASH_GetStatusFlag(uint32_t Flags) {
  FlagStatus flags;

  if (READ_BIT(FLASH->SR, Flags)) {
    flags = SET;
    WRITE_REG(FLASH->SR, Flags);
  } else {
    flags = RESET;
  }

  return flags;
}

/**
  * @brief  Erase the flash with chip.
  * @param  None
  * @retval A ErrorStatus enumeration value:
  *          - SUCCESS: finish erasing chip
  *          - ERROR: not applicable
  */
ErrorStatus MS32_FLASH_ChipErase(void) {
  ErrorStatus state;

  /* flash unlock */
  FLASH->KEYR = FLASH_KEY1;
  FLASH->KEYR = FLASH_KEY2;

  /* chip erase */ 
  WRITE_REG(FLASH->SR, (FLASH_SR_EOP | FLASH_SR_WRPRTERR | FLASH_SR_PGERR));
  SET_BIT(FLASH->CR, FLASH_CR_MER);
  SET_BIT(FLASH->CR, FLASH_CR_STRT);
  while (READ_BIT(FLASH->SR, FLASH_SR_BSY));
  CLEAR_BIT(FLASH->CR, FLASH_CR_MER);

  /* flash lock */
  SET_BIT(FLASH->CR, FLASH_CR_LOCK);

  /* check flag */ 
  if (READ_BIT(FLASH->SR, FLASH_SR_EOP) && (!READ_BIT(FLASH->SR, FLASH_SR_WRPRTERR))) {
    state = SUCCESS;
  } else {
    state = ERROR;
  }

  return state;
}

/**
  * @brief  Erase the flash with page.
  * @param  page specifies the flash page number.
  *          This parameter can range from 0 to MAIN_FLASH_PAGE_MAX
  * @retval A ErrorStatus enumeration value:
  *          - SUCCESS: finish erasing chip
  *          - ERROR: not applicable
  */
ErrorStatus MS32_FLASH_PageErase(uint32_t page) {
  ErrorStatus state;

  if (page <= MAIN_FLASH_PAGE_MAX) {
    /* flash unlock */
    FLASH->KEYR = FLASH_KEY1;
    FLASH->KEYR = FLASH_KEY2;

    /* page erase */ 
    WRITE_REG(FLASH->SR, (FLASH_SR_EOP | FLASH_SR_WRPRTERR | FLASH_SR_PGERR));
    SET_BIT(FLASH->CR, FLASH_CR_PER);
    WRITE_REG(FLASH->AR, MAIN_FLASH_START_ADDR + page * MAIN_FLASH_PAGE_SIZE);
    SET_BIT(FLASH->CR, FLASH_CR_STRT);
    while (READ_BIT(FLASH->SR, FLASH_SR_BSY));
    CLEAR_BIT(FLASH->CR, FLASH_CR_PER);

    /* flash lock */
    SET_BIT(FLASH->CR, FLASH_CR_LOCK);

    /* check flag */ 
    if (READ_BIT(FLASH->SR, FLASH_SR_EOP) && (!READ_BIT(FLASH->SR, FLASH_SR_WRPRTERR))) {
      state = SUCCESS;
    } else {
      state = ERROR;
    }
  } else {
    state = ERROR;
  }

  return state;
}

/**
  * @brief  Write the flash byte.
  * @param  addr specifies the flash address(start).
  *          This parameter can range from (MAIN_FLASH_START_ADDR) to 
  *          (MAIN_FLASH_START_ADDR+MAIN_FLASH_SIZE - 2)
  * @note   This parameter(addr) must be even number in this function
  * @param  dat_buf specifies the data buffer address(start, type: uint8_t).
  * @note   This parameter can't be NULL
  * @param  len specifies the data buffer length.
  * @retval A ErrorStatus enumeration value:
  *          - SUCCESS: finish writing chip
  *          - ERROR: not applicable
  */
ErrorStatus MS32_FLASH_Write(uint32_t addr, uint8_t *dat_buf, uint32_t len) {
  ErrorStatus state;
  uint32_t    index;

  /*
   * Error1: the start address less than (MAIN_FLASH_START_ADDR)
   * Error2: the last address more than or equal to (MAIN_FLASH_START_ADDR + MAIN_FLASH_SIZE)
   * Error3: the start address is odd number
   */
  if ((addr < MAIN_FLASH_START_ADDR) \
   || ((addr + len - 1) >= (MAIN_FLASH_START_ADDR + MAIN_FLASH_SIZE)) \
   || (addr & 0x00000001)) {
    state = ERROR;
  } else {
    /* flash unlock */
    FLASH->KEYR = FLASH_KEY1;
    FLASH->KEYR = FLASH_KEY2;

    /* write */ 
    WRITE_REG(FLASH->SR, (FLASH_SR_EOP | FLASH_SR_WRPRTERR | FLASH_SR_PGERR));
    SET_BIT(FLASH->CR, FLASH_CR_PG);
    for (index = 0; index < len; index += 2) {
      /* need fill up '0xFF' when length is odd number */
      if ((index + 2) > len) {
        TYPE16(addr) = 0xFF00 | ((uint16_t)(*(dat_buf + index)));
      } else {
        TYPE16(addr) = ((uint16_t)(*(dat_buf + index + 1))) << 8 | ((uint16_t)(*(dat_buf + index)));
      }
      while (READ_BIT(FLASH->SR, FLASH_SR_BSY));
    }
    CLEAR_BIT(FLASH->CR, FLASH_CR_PG);

    /* flash lock */
    SET_BIT(FLASH->CR, FLASH_CR_LOCK);

    /* check flag */ 
    if (READ_BIT(FLASH->SR, FLASH_SR_EOP) && (!READ_BIT(FLASH->SR, FLASH_SR_PGERR))) {
      state = SUCCESS;
    } else {
      state = ERROR;
    }
  }

  return state;
}

/**
  * @brief  Read the flash byte.
  * @param  addr specifies the flash address(start).
  *          This parameter can range from (MAIN_FLASH_START_ADDR) to 
  *          (MAIN_FLASH_START_ADDR+MAIN_FLASH_SIZE - 2)
  * @param  dat_buf specifies the data buffer address(start, type: uint8_t).
  * @note   This parameter can't be NULL
  * @param  len specifies the data buffer length.
  * @retval A ErrorStatus enumeration value:
  *          - SUCCESS: finish reading chip
  *          - ERROR: not applicable
  */
ErrorStatus MS32_FLASH_Read(uint32_t addr, uint8_t *dat_buf, uint32_t len) {
  ErrorStatus state;
  uint32_t    index;

  /*
   * Error1: the start address less than (MAIN_FLASH_START_ADDR)
   * Error2: the last address more than or equal to (MAIN_FLASH_START_ADDR + MAIN_FLASH_SIZE)
   */
  if ((addr < MAIN_FLASH_START_ADDR) \
   || ((addr + len - 1) >= (MAIN_FLASH_START_ADDR + MAIN_FLASH_SIZE))) {
    state = ERROR;
  } else {
    /* Read */ 
    for (index = 0; index < len; index ++) {
      *(dat_buf + index) = TYPE8(addr);
    }
    state = SUCCESS;
  }

  return state;
}

/**
  * @brief  Erase the option byte.
  * @param  None
  * @retval A ErrorStatus enumeration value:
  *          - SUCCESS: finish erasing option
  *          - ERROR: not applicable
  */
ErrorStatus MS32_FLASH_OptionErase(void) {
  ErrorStatus state;

  /* option unlock */
  FLASH->KEYR = FLASH_KEY1;
  FLASH->KEYR = FLASH_KEY2;
  FLASH->OPTKEYR = FLASH_OPTKEY1;
  FLASH->OPTKEYR = FLASH_OPTKEY2;

  /* chip erase */ 
  WRITE_REG(FLASH->SR, (FLASH_SR_EOP | FLASH_SR_WRPRTERR | FLASH_SR_PGERR));
  SET_BIT(FLASH->CR, FLASH_CR_OPTER);
  SET_BIT(FLASH->CR, FLASH_CR_STRT);
  while (READ_BIT(FLASH->SR, FLASH_SR_BSY));
  CLEAR_BIT(FLASH->CR, FLASH_CR_OPTER);

  /* option lock */
  CLEAR_BIT(FLASH->CR, FLASH_CR_OPTWRE);

  /* check flag */ 
  if (READ_BIT(FLASH->SR, FLASH_SR_EOP) && (!READ_BIT(FLASH->SR, FLASH_SR_WRPRTERR))) {
    state = SUCCESS;
  } else {
    state = ERROR;
  }

  return state;
}

/**
  * @brief  Write the option byte.
  * @param  addr specifies the option address(start).
  *          This parameter can range from (OPTIONBYTE_START_ADDR) to 
  *          (OPTIONBYTE_START_ADDR+OPTIONBYTE_SIZE - 2)
  * @note   This parameter(addr) must be even number in this function
  * @param  dat_buf specifies the data buffer address(start, type: uint8_t).
  * @note   This parameter can't be NULL
  * @param  len specifies the data buffer length.
  * @retval A ErrorStatus enumeration value:
  *          - SUCCESS: finish writing chip
  *          - ERROR: not applicable
  */
ErrorStatus MS32_FLASH_OptionWrite(uint32_t addr, uint8_t *dat_buf, uint32_t len) {
  ErrorStatus state;
  uint32_t    index;

  /*
   * Error1: the start address less than (OPTIONBYTE_START_ADDR)
   * Error2: the last address more than or equal to (OPTIONBYTE_START_ADDR + OPTIONBYTE_SIZE)
   * Error3: the start address is odd number
   */
  if ((addr < OPTIONBYTE_START_ADDR) \
   || ((addr + len - 1) >= (OPTIONBYTE_START_ADDR + OPTIONBYTE_SIZE)) \
   || (addr & 0x00000001)) {
    state = ERROR;
  } else {
    /* option unlock */
    FLASH->KEYR = FLASH_KEY1;
    FLASH->KEYR = FLASH_KEY2;
    FLASH->OPTKEYR = FLASH_OPTKEY1;
    FLASH->OPTKEYR = FLASH_OPTKEY2;

    /* write */ 
    WRITE_REG(FLASH->SR, (FLASH_SR_EOP | FLASH_SR_WRPRTERR | FLASH_SR_PGERR));
    SET_BIT(FLASH->CR, FLASH_CR_OPTPG);
    for (index = 0; index < len; index += 2) {
      /* need fill up '0xFF' when length is odd number */
      if ((index + 2) > len) {
        TYPE16(addr) = 0xFF00 | ((uint16_t)(*(dat_buf + index)));
      } else {
        TYPE16(addr) = ((uint16_t)(*(dat_buf + index + 1))) << 8 | ((uint16_t)(*(dat_buf + index)));
      }
      while (READ_BIT(FLASH->SR, FLASH_SR_BSY));
    }
    CLEAR_BIT(FLASH->CR, FLASH_CR_OPTPG);

    /* option lock */
    CLEAR_BIT(FLASH->CR, FLASH_CR_OPTWRE);

    /* check flag */ 
    if (READ_BIT(FLASH->SR, FLASH_SR_EOP) && (!READ_BIT(FLASH->SR, FLASH_SR_PGERR))) {
      state = SUCCESS;
    } else {
      state = ERROR;
    }
  }

  return state;
}

/**
  * @brief  Read the option byte.
  * @param  addr specifies the option address(start).
  *          This parameter can range from (OPTIONBYTE_START_ADDR) to 
  *          (OPTIONBYTE_START_ADDR+OPTIONBYTE_SIZE - 2)
  * @param  dat_buf specifies the data buffer address(start, type: uint8_t).
  * @note   This parameter can't be NULL
  * @param  len specifies the data buffer length.
  * @retval A ErrorStatus enumeration value:
  *          - SUCCESS: finish reading chip
  *          - ERROR: not applicable
  */
ErrorStatus MS32_FLASH_OptionRead(uint32_t addr, uint8_t *dat_buf, uint32_t len) {
  ErrorStatus state;
  uint32_t    index;

  /*
   * Error1: the start address less than (OPTIONBYTE_START_ADDR)
   * Error2: the last address more than or equal to (OPTIONBYTE_START_ADDR + OPTIONBYTE_SIZE)
   */
  if ((addr < OPTIONBYTE_START_ADDR) \
   || ((addr + len - 1) >= (OPTIONBYTE_START_ADDR + OPTIONBYTE_SIZE))) {
    state = ERROR;
  } else {
    /* Read */ 
    for (index = 0; index < len; index ++) {
      *(dat_buf + index) = TYPE8(addr);
    }
    state = SUCCESS;
  }

  return state;
}

/******************************** END OF FILE *********************************/
