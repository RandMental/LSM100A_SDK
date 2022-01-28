/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    sgfx_eeprom_if.c
  * @author  MCD Application Team
  * @brief   eeprom interface to the sigfox component
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "lora_eeprom_if.h"
#include "lora_ee.h"
#include "sys_conf.h"
#include "utilities_conf.h"
#include "radio_board_if.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* External variables ---------------------------------------------------------*/
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/* Private typedef -----------------------------------------------------------*/
enum
{
  EE_BANK_0 = 0,
  EE_BANK_1 = 1
};

enum
{
  EE_CLEAN_MODE_POLLING = 0,
  EE_CLEAN_MODE_IT = 1
};

enum
{
  NO_FORMAT =         0,
  FORMAT =            1
};

/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/**
  * @brief        Read Sigfox Configuration from eeprom
  * @param addr   variable virtual address
  * @param data   pointer to a 32-bit word (allocated by the caller) containing the
  *               variable value in case of success.
  */
void E2P_LORA_Read(e_EE_LORA_ID addr, uint32_t *data);

/**
  * @brief        Write Sigfox Configuration to eeprom
  * @param addr   variable virtual address
  * @param data   32-bit data word to be written
  */
void E2P_LORA_Write(e_EE_LORA_ID addr, uint32_t data);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Exported functions --------------------------------------------------------*/
void E2P_LORA_Init(void)
{
  /* USER CODE BEGIN E2P_Init_1 */

  /* USER CODE END E2P_Init_1 */
  HAL_FLASH_Unlock();

  if (EE_LoRa_Init(NO_FORMAT, EE_LORA_BASE_ADRESS) != EE_OK)
  {
    if (EE_LoRa_Init(FORMAT, EE_LORA_BASE_ADRESS) == EE_OK)
    {
      E2P_LORA_RestoreFs();
    }
    else
    {
      Error_Handler();
    }
  }
  HAL_FLASH_Lock();
}

void E2P_LORA_RestoreFs(void)
{
  HAL_FLASH_Unlock();
  E2P_LORA_Write(EE_LORA_TYPE_ID, 2);							// 0: NONE 		1:ABP		2: OTAA 
  E2P_LORA_Write(EE_LORA_CLASS_ID, 0);							// 0: CLASS_A 	1:CLASS_B	2: CLASS_C 
//-------------------------------------------------------------------------------------------
  E2P_LORA_Write(EE_LORA_WORD0_APPKEY_ID, LORA_APPKEY_WORD_0);
  E2P_LORA_Write(EE_LORA_WORD1_APPKEY_ID, LORA_APPKEY_WORD_1);
  E2P_LORA_Write(EE_LORA_WORD2_APPKEY_ID, LORA_APPKEY_WORD_2);
  E2P_LORA_Write(EE_LORA_WORD3_APPKEY_ID, LORA_APPKEY_WORD_3);

  E2P_LORA_Write(EE_LORA_WORD0_NWKKEY_ID, LORA_NWKKEY_WORD_0);
  E2P_LORA_Write(EE_LORA_WORD1_NWKKEY_ID, LORA_NWKKEY_WORD_1);
  E2P_LORA_Write(EE_LORA_WORD2_NWKKEY_ID, LORA_NWKKEY_WORD_2);
  E2P_LORA_Write(EE_LORA_WORD3_NWKKEY_ID, LORA_NWKKEY_WORD_3);

  E2P_LORA_Write(EE_LORA_WORD0_APPSKEY_ID, LORA_APPSKEY_WORD_0);
  E2P_LORA_Write(EE_LORA_WORD1_APPSKEY_ID, LORA_APPSKEY_WORD_1);
  E2P_LORA_Write(EE_LORA_WORD2_APPSKEY_ID, LORA_APPSKEY_WORD_2);
  E2P_LORA_Write(EE_LORA_WORD3_APPSKEY_ID, LORA_APPSKEY_WORD_3);

  E2P_LORA_Write(EE_LORA_WORD0_NWKSKEY_ID, LORA_NWKSKEY_WORD_0);
  E2P_LORA_Write(EE_LORA_WORD1_NWKSKEY_ID, LORA_NWKSKEY_WORD_1);
  E2P_LORA_Write(EE_LORA_WORD2_NWKSKEY_ID, LORA_NWKSKEY_WORD_2);
  E2P_LORA_Write(EE_LORA_WORD3_NWKSKEY_ID, LORA_NWKSKEY_WORD_3);

  E2P_LORA_Write(EE_LORA_WORD0_APPEUI_ID, LORA_APPEUI_WORD_0);
  E2P_LORA_Write(EE_LORA_WORD0_APPEUI_ID, LORA_APPEUI_WORD_1);

//-------------------------------------------------------------------------------------------  
  E2P_LORA_Write(EE_LORA_MODE_ID, 1);					  		//  0: Disable	  	1: enable
  E2P_LORA_Write(EE_LORA_FW_MODE_ID, 0);			  	//  0: HIGH/LOW		1: LOW		  2: HIGH

  HAL_FLASH_Lock();
  /* USER CODE BEGIN E2P_RestoreFs_2 */

  /* USER CODE END E2P_RestoreFs_2 */
}

int16_t E2P_LORA_Read_Class(void)
{
  /* USER CODE BEGIN E2P_Read_RssiCal_1 */

  /* USER CODE END E2P_Read_RssiCal_1 */
  uint32_t Class = 0 ;
  E2P_LORA_Read(EE_LORA_CLASS_ID, &Class);
  return (int16_t) Class;
  /* USER CODE BEGIN E2P_Read_RssiCal_2 */

  /* USER CODE END E2P_Read_RssiCal_2 */
}

void E2P_LORA_Write_Class(int16_t Class)
{
  /* USER CODE BEGIN E2P_Write_RssiCal_1 */

  /* USER CODE END E2P_Write_RssiCal_1 */
  HAL_FLASH_Unlock();

  E2P_LORA_Write(EE_LORA_CLASS_ID, (uint32_t)Class);

  HAL_FLASH_Lock();
  /* USER CODE BEGIN E2P_Write_RssiCal_2 */

  /* USER CODE END E2P_Write_RssiCal_2 */
}


int16_t E2P_LORA_Read_Type(void)
{
  /* USER CODE BEGIN E2P_Read_RssiCal_1 */

  /* USER CODE END E2P_Read_RssiCal_1 */
  uint32_t Type = 0 ;
  E2P_LORA_Read(EE_LORA_TYPE_ID, &Type);
  return (int16_t) Type;
  /* USER CODE BEGIN E2P_Read_RssiCal_2 */

  /* USER CODE END E2P_Read_RssiCal_2 */
}

void E2P_LORA_Write_Type(int16_t Type)
{
  /* USER CODE BEGIN E2P_Write_RssiCal_1 */

  /* USER CODE END E2P_Write_RssiCal_1 */
  HAL_FLASH_Unlock();

  E2P_LORA_Write(EE_LORA_TYPE_ID, (uint32_t)Type);

  HAL_FLASH_Lock();
  /* USER CODE BEGIN E2P_Write_RssiCal_2 */

  /* USER CODE END E2P_Write_RssiCal_2 */
}


uint8_t E2P_LORA_Read_Mode(void)
{
  /* USER CODE BEGIN E2P_Read_Rc_1 */

  /* USER CODE END E2P_Read_Rc_1 */
  uint32_t LoRaMode = 1;
  E2P_LORA_Read(EE_LORA_MODE_ID, &LoRaMode);
  return (uint8_t) LoRaMode;
  /* USER CODE BEGIN E2P_Read_Rc_2 */

  /* USER CODE END E2P_Read_Rc_2 */
}

void E2P_LORA_Write_Mode(uint8_t LoRaMode)
{
  /* USER CODE BEGIN E2P_Write_Rc_1 */

  /* USER CODE END E2P_Write_Rc_1 */
  HAL_FLASH_Unlock();

  E2P_LORA_Write(EE_LORA_MODE_ID, (uint32_t) LoRaMode);

  HAL_FLASH_Lock();
  /* USER CODE BEGIN E2P_Write_Rc_2 */

  /* USER CODE END E2P_Write_Rc_2 */
}

uint8_t E2P_LORA_FW_Read_Mode(void)

{
  /* USER CODE BEGIN E2P_Read_Rc_1 */

  /* USER CODE END E2P_Read_Rc_1 */
  uint32_t FWLoRaMode = 0;
  E2P_LORA_Read(EE_LORA_FW_MODE_ID, &FWLoRaMode);
  return (uint8_t) FWLoRaMode;
  /* USER CODE BEGIN E2P_Read_Rc_2 */

  /* USER CODE END E2P_Read_Rc_2 */
}
void E2P_LORA_FW_Write_Mode(uint8_t LoRaMode)

{
  /* USER CODE BEGIN E2P_Write_Rc_1 */

  /* USER CODE END E2P_Write_Rc_1 */
  HAL_FLASH_Unlock();

  E2P_LORA_Write(EE_LORA_FW_MODE_ID, (uint32_t) LoRaMode);

  HAL_FLASH_Lock();
  /* USER CODE BEGIN E2P_Write_Rc_2 */

  /* USER CODE END E2P_Write_Rc_2 */
}

void E2P_LORA_Read_Appeui(lora_u32 config_words[2])
{
  E2P_LORA_Read(EE_LORA_WORD0_APPEUI_ID, (uint32_t *) &config_words[0]);
  E2P_LORA_Read(EE_LORA_WORD1_APPEUI_ID, (uint32_t *) &config_words[1]);
}

void E2P_LORA_Write_Appeui(lora_u32 config_words[2])
{
  /* USER CODE BEGIN E2P_Write_ConfigWords_1 */

  /* USER CODE END E2P_Write_ConfigWords_1 */
  HAL_FLASH_Unlock();

  E2P_LORA_Write(EE_LORA_WORD0_APPEUI_ID, config_words[0]);
  E2P_LORA_Write(EE_LORA_WORD1_APPEUI_ID, config_words[1]);

  HAL_FLASH_Lock();
  /* USER CODE BEGIN E2P_Write_ConfigWords_2 */

  /* USER CODE END E2P_Write_ConfigWords_2 */
}


void E2P_LORA_Read_Appkey(lora_u32 config_words[4])
{
  E2P_LORA_Read(EE_LORA_WORD0_APPKEY_ID, (uint32_t *) &config_words[0]);
  E2P_LORA_Read(EE_LORA_WORD1_APPKEY_ID, (uint32_t *) &config_words[1]);
  E2P_LORA_Read(EE_LORA_WORD2_APPKEY_ID, (uint32_t *) &config_words[2]);
  E2P_LORA_Read(EE_LORA_WORD3_APPKEY_ID, (uint32_t *) &config_words[3]);
}

void E2P_LORA_Write_Appkey(lora_u32 config_words[4])
{
  /* USER CODE BEGIN E2P_Write_ConfigWords_1 */

  /* USER CODE END E2P_Write_ConfigWords_1 */
  HAL_FLASH_Unlock();

  E2P_LORA_Write(EE_LORA_WORD0_APPKEY_ID, config_words[0]);
  E2P_LORA_Write(EE_LORA_WORD1_APPKEY_ID, config_words[1]);
  E2P_LORA_Write(EE_LORA_WORD2_APPKEY_ID, config_words[2]);
  E2P_LORA_Write(EE_LORA_WORD3_APPKEY_ID, config_words[3]);

  HAL_FLASH_Lock();
  /* USER CODE BEGIN E2P_Write_ConfigWords_2 */

  /* USER CODE END E2P_Write_ConfigWords_2 */
}


void E2P_LORA_Read_Nwkkey(lora_u32 config_words[4])
{
  E2P_LORA_Read(EE_LORA_WORD0_NWKKEY_ID, (uint32_t *) &config_words[0]);
  E2P_LORA_Read(EE_LORA_WORD1_NWKKEY_ID, (uint32_t *) &config_words[1]);
  E2P_LORA_Read(EE_LORA_WORD2_NWKKEY_ID, (uint32_t *) &config_words[2]);
  E2P_LORA_Read(EE_LORA_WORD3_NWKKEY_ID, (uint32_t *) &config_words[3]);
}

void E2P_LORA_Write_Nwkkey(lora_u32 config_words[4])
{
  /* USER CODE BEGIN E2P_Write_ConfigWords_1 */

  /* USER CODE END E2P_Write_ConfigWords_1 */
  HAL_FLASH_Unlock();

  E2P_LORA_Write(EE_LORA_WORD0_NWKKEY_ID, config_words[0]);
  E2P_LORA_Write(EE_LORA_WORD1_NWKKEY_ID, config_words[1]);
  E2P_LORA_Write(EE_LORA_WORD2_NWKKEY_ID, config_words[2]);
  E2P_LORA_Write(EE_LORA_WORD3_NWKKEY_ID, config_words[3]);

  HAL_FLASH_Lock();
  /* USER CODE BEGIN E2P_Write_ConfigWords_2 */

  /* USER CODE END E2P_Write_ConfigWords_2 */
}

void E2P_LORA_Read_App_S_key(lora_u32 config_words[4])
{
  E2P_LORA_Read(EE_LORA_WORD0_APPSKEY_ID, (uint32_t *) &config_words[0]);
  E2P_LORA_Read(EE_LORA_WORD1_APPSKEY_ID, (uint32_t *) &config_words[1]);
  E2P_LORA_Read(EE_LORA_WORD2_APPSKEY_ID, (uint32_t *) &config_words[2]);
  E2P_LORA_Read(EE_LORA_WORD3_APPSKEY_ID, (uint32_t *) &config_words[3]);
}

void E2P_LORA_Write_App_S_key(lora_u32 config_words[4])
{
  /* USER CODE BEGIN E2P_Write_ConfigWords_1 */

  /* USER CODE END E2P_Write_ConfigWords_1 */
  HAL_FLASH_Unlock();

  E2P_LORA_Write(EE_LORA_WORD0_APPSKEY_ID, config_words[0]);
  E2P_LORA_Write(EE_LORA_WORD1_APPSKEY_ID, config_words[1]);
  E2P_LORA_Write(EE_LORA_WORD2_APPSKEY_ID, config_words[2]);
  E2P_LORA_Write(EE_LORA_WORD3_APPSKEY_ID, config_words[3]);

  HAL_FLASH_Lock();
  /* USER CODE BEGIN E2P_Write_ConfigWords_2 */

  /* USER CODE END E2P_Write_ConfigWords_2 */
}


void E2P_LORA_Read_Nwk_S_key(lora_u32 config_words[4])
{
  E2P_LORA_Read(EE_LORA_WORD0_NWKSKEY_ID, (uint32_t *) &config_words[0]);
  E2P_LORA_Read(EE_LORA_WORD1_NWKSKEY_ID, (uint32_t *) &config_words[1]);
  E2P_LORA_Read(EE_LORA_WORD2_NWKSKEY_ID, (uint32_t *) &config_words[2]);
  E2P_LORA_Read(EE_LORA_WORD3_NWKSKEY_ID, (uint32_t *) &config_words[3]);
}

void E2P_LORA_Write_Nwk_S_key(lora_u32 config_words[4])
{
  /* USER CODE BEGIN E2P_Write_ConfigWords_1 */

  /* USER CODE END E2P_Write_ConfigWords_1 */
  HAL_FLASH_Unlock();

  E2P_LORA_Write(EE_LORA_WORD0_NWKSKEY_ID, config_words[0]);
  E2P_LORA_Write(EE_LORA_WORD1_NWKSKEY_ID, config_words[1]);
  E2P_LORA_Write(EE_LORA_WORD2_NWKSKEY_ID, config_words[2]);
  E2P_LORA_Write(EE_LORA_WORD3_NWKSKEY_ID, config_words[3]);

  HAL_FLASH_Lock();
  /* USER CODE BEGIN E2P_Write_ConfigWords_2 */

  /* USER CODE END E2P_Write_ConfigWords_2 */
}


/* Private Functions Definition -----------------------------------------------*/
void E2P_LORA_Write(e_EE_LORA_ID addr, uint32_t data)
{
  /* USER CODE BEGIN E2P_Write_1 */

  /* USER CODE END E2P_Write_1 */
  if (EE_LoRa_Write(EE_BANK_0, (uint16_t) addr, data) == EE_CLEAN_NEEDED)
  {
    EE_LoRa_Clean(EE_BANK_0, EE_CLEAN_MODE_POLLING);
  }
  /* USER CODE BEGIN E2P_Write_2 */

  /* USER CODE END E2P_Write_2 */
}

void E2P_LORA_Read(e_EE_LORA_ID addr, uint32_t *data)
{
  /* USER CODE BEGIN E2P_Read_1 */

  /* USER CODE END E2P_Read_1 */
  EE_LoRa_Read(EE_BANK_0, (uint16_t) addr, data);
  /* USER CODE BEGIN E2P_Read_2 */

  /* USER CODE END E2P_Read_2 */
}

/* USER CODE BEGIN PrFD */

/* USER CODE END PrFD */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
