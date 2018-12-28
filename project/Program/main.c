
/* Includes --------------------------------------------------------------------------------*/
#include "drivers\nrf5x_system.h"
#include "modules\serial.h"
#include "nrf5x_bsp.h"
#include "nrf5x_bootloader.h"
#include "IAP_GPIO_BINRARY.h"


int main( void )
{
  BSP_CLOCK_Config();
  BSP_GPIO_Config();
  if (KEY_Read()) 
  {
		BSP_UART_SERIAL_Config(NULL);
		nrf_bootloader_set_receiver(Serial_RecvData);

		LED_R_Reset();
		delay_ms(100);

		uint32_t binaryFileSize = 0;
		uint8_t binaryFile[4096] = {0};
		binaryFileSize = nrf_bootloader_download(binaryFile);
		nrf_bootloader_upload(binaryFile, binaryFileSize);

		delay_ms(1000);
		LED_R_Set();
		NVIC_SystemReset();
  }
  else 
  {
		nrf_bootloader_app_start(APPLICATION_ADDR);
  }
}

/*************************************** END OF FILE ****************************************/
