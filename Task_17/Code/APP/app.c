/*
 * app.c
 * Created: 6/30/2024 6:55:47 PM
 *  Author: Mostafa Asaad
 */ 
/* --------------- Section : Includes --------------- */
#include "app.h"
/* --------------- Section: Global Variables --------------- */
uint8_t msb = 0, lsb = 0;
uint16_t temperature = 0;
uint8_t msg[50];
uint8_t cels_msg[] = " 'C\0";
SPI_Configurations_t spi_cfg = 
{
	NULL,
	SPI_MODE_MASTER,
	SPI_ORDER_MSB_FIRST,
	SPI_CLK_POLARITY_LOW,
	SPI_CLK_PHASE_SAMPLE_AT_LEADING,
	SPI_DOUBLE_SPEED_DISABLE,
	SPI_CLK_RATE_FOSC_BY_128
};

/* --------------- Section: Main Function --------------- */
int main(void)
{
	Std_ReturnType ret = E_OK;
	
	ret |= app_init();

	while(1)
	{
		temperature = Get_Temperature();
		ret |= convert_uint16_to_string(temperature, msg);
		ret |= lcd_4bit_send_string_pos(&lcd, 2, 1, msg);
		ret |= lcd_4bit_send_string(&lcd, cels_msg);
	}
}
/*---------------  Section: Helper Functions Definitions --------------- */
Std_ReturnType app_init(void) 
{
	Std_ReturnType ret = E_OK;

	ret |= ecu_layer_initialize();

	ret |= SPI_Init(&spi_cfg);
	
	TC72_Init();
	_delay_ms(150);

	return ret;
}

void TC72_Init(void)
{
	PORTB |= (1 << 4);
	/*Select Control Register*/
	TC72_Send_Command(0x80);
	/* Select Continuous temperature Conversion */
	TC72_Send_Command(0x04);
	PORTB &= ~(1<<4);
	
	_delay_ms(150);
}

void TC72_Send_Command(char spiData)
{
	/* Start the transmission */
	SPDR = spiData;
	/* Wait for completion */
	while(!SPI_IS_TRASNSFER_COMPLETE());
	
}

char TC72_Read(void)
{
	/*Wait for the SPI buffer's full*/
	while(!SPI_IS_TRASNSFER_COMPLETE());
	/*return SPI Buffer*/
	return SPDR;
}

uint16_t Get_Temperature(void)
{
	PORTB |= (1 << 4);
	/* Read the High byte Command */
	TC72_Send_Command(0x02);
	/* Issue one more clock frame to force data out */
	TC72_Send_Command(0x00);
	PORTB &= ~(1 << 4);
		
	_delay_ms(1);
	msb = TC72_Read();
		
	PORTB |= (1 << 4);
	/* Read The Low Byte command */
	TC72_Send_Command(0x01);
	/* Issue one more clock frame to force data out */
	TC72_Send_Command(0x00);
	PORTB &= ~(1 << 4);
		
	_delay_ms(1);
	lsb = TC72_Read();
	
	return (uint16_t)(((msb << 8) + lsb) / 256.0);
}