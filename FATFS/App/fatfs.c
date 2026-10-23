/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file   fatfs.c
  * @brief  Code for fatfs applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
#include "fatfs.h"

uint8_t retSD;    /* Return value for SD */
char SDPath[4];   /* SD logical drive path */
FATFS SDFatFS;    /* File system object for SD logical drive */
FIL SDFile;       /* File object for SD */

/* USER CODE BEGIN Variables */
FATFS SDFatFs;  /* File system object for SD card logical drive */
FIL MyFile;     /* File object */

/* USER CODE END Variables */

void MX_FATFS_Init(void)
{
  /*## FatFS: Link the SD driver ###########################*/
  retSD = FATFS_LinkDriver(&SD_Driver, SDPath);

  /* USER CODE BEGIN Init */
  if (retSD == 0){
	  if(f_mount(&SDFatFs, (TCHAR const*)SDPath, 0) != FR_OK)
	  {
		/* FatFs Initialization Error */
		  {
			HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
			HAL_Delay(500);
			HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
			HAL_Delay(100);
		  }
	  }
  }
  /* additional user code for init */
  /* USER CODE END Init */
}

/**
  * @brief  Gets Time from RTC
  * @param  None
  * @retval Time in DWORD
  */
DWORD get_fattime(void)
{
  /* USER CODE BEGIN get_fattime */
  return 0;
  /* USER CODE END get_fattime */
}

/* USER CODE BEGIN Application */
/*
uint8_t MX_FATFS_Log_Enable(void)
{
	static uint16_t sdcard_file_counter = 0;
	char header[] = "T [ms],AccX [mg],AccY [mg],AccZ [mg],GyroX [mdps],GyroY [mdps],GyroZ [mdps],MagX [mgauss],MagY [mgauss],MagZ [mgauss],P [mB],T [�C],H [%]\r\n";
	uint32_t byteswritten;
	char file_name[30] = {0};

	sprintf(file_name, "%s%.3d%s", "teste", sdcard_file_counter, ".txt");
	sdcard_file_counter++;

	HAL_Delay(100);

	if(f_open(&MyFile, (char const*)file_name, FA_CREATE_ALWAYS | FA_WRITE) != FR_OK)
	{
	sdcard_file_counter--;
	return 0;
	}

	if(f_write(&MyFile, (const void*)&header, sizeof(header)-1, (void *)&byteswritten) != FR_OK)
	{
	return 0;
	}

	return 1;

}


uint8_t MX_FATFS_writeBuf(char *s, uint32_t size)
{
  uint32_t byteswritten;

  if(f_write(&MyFile, s, size, (void *)&byteswritten) != FR_OK)
  {
    return 0;
  }
  return 1;
}*/

uint8_t MX_FATFS_Log_Enable(void)
{
	static uint16_t sdcard_file_counter = 0;
	//char header[] = "T [ms],AccX [mg],AccY [mg],AccZ [mg],GyroX [mdps],GyroY [mdps],GyroZ [mdps],MagX [mgauss],MagY [mgauss],MagZ [mgauss],P [mB],T [�C],H [%]\r\n";
	//uint32_t byteswritten;
	char file_name[30] = {0};

	sprintf(file_name, "%s%.3d%s", "audio", sdcard_file_counter, ".raw");
	sdcard_file_counter++;

	HAL_Delay(100);

	if(f_open(&MyFile, (char const*)file_name, FA_CREATE_ALWAYS | FA_WRITE) != FR_OK)
	{
	    sdcard_file_counter--;
	    return 0;
	}
	/*
	if(f_write(&MyFile, (const void*)&header, sizeof(header)-1, (void *)&byteswritten) != FR_OK) // teste apenas
	{
	    return 0;
	}
	 */
	return 1;

}
uint8_t Write_PCM_Data_32b(int32_t *pData, uint32_t size)
{
  uint32_t byteswritten;

  if(f_write(&MyFile, pData, size, (void *)&byteswritten) != FR_OK)
  {
    return 0;
  }
  return 1;
}

uint8_t Write_PCM_Data(int16_t *pData, uint32_t size)
{
  uint32_t byteswritten;

  if(f_write(&MyFile, pData, size, (void *)&byteswritten) != FR_OK)
  {
    return 0;
  }
  return 1;
}

uint8_t MX_FATFS_writeBuf(char *s, uint32_t size)
{
  uint32_t byteswritten;

  if(f_write(&MyFile, s, size, (void *)&byteswritten) != FR_OK)
  {
    return 0;
  }
  return 1;
}

void MX_FATFS_Log_Disable(void){
	f_close(&MyFile);
}

void MX_FATFS_DeInit(void){
	FATFS_UnLinkDriver(SDPath);
}
/* USER CODE END Application */
