/*
 * spi.c
 *
 * Created: 8/2/2024 10:27:53 PM
 *  Author: Mostafa Asaad
 */ 
/* --------------- Section : Includes --------------- */
#include "spi.h"
/* --------------- Section : Global Variables --------------- */
static interrupt_handler_t SPI_Default_Interrupt_Handler = NULL;
static uint8_t SPI_Module_Is_Initialized = 0;
static volatile uint8_t interrupt_flag = 0;
pin_config_t ss_pin = { PORTB_INDEX, PIN4_INDEX };
/*---------------  Section: Function Definitions --------------- */

/**
 * @brief Initializes the SPI module
 *
 * This function initializes the SPI module according to the provided configurations.
 *
 * @param SPI_Cfgs Pointer to the SPI module configurations structure
 * @return Std_ReturnType E_OK on success, E_NOT_OK on failure
 */
Std_ReturnType SPI_Init(const SPI_Configurations_t * SPI_Cfgs)
{
	Std_ReturnType retVal = E_OK;
	if(NULL == SPI_Cfgs)
	{
		retVal = E_NOT_OK;
	}
	else
	{
		/* Disable the SPI Module */
		SPI_SET_DISABLE();
		/* Set the SPI Mode & Configure the GPIO pins */
		switch (SPI_Cfgs->SPI_Mode)
		{
			case SPI_MODE_MASTER:
				ss_pin.direction = GPIO_DIRECTION_OUTPUT;
				ss_pin.logic = GPIO_LOW;
				retVal |= gpio_pin_direction_init(&ss_pin);
				SET_BIT(DDRB, 5);		// Configure MOSI pin as o/p
				//CLEAR_BIT(DDRB, 6);	// Configure MISO pin as i/p
				SET_BIT(DDRB, 7);		// Configure CLK  pin as o/p
				break;
			case SPI_MODE_SLAVE:
				ss_pin.direction = GPIO_DIRECTION_INPUT;
				ss_pin.logic = GPIO_LOW;
				retVal |= gpio_pin_initialize(&ss_pin);
				CLEAR_BIT(DDRB, 5);	// Configure MOSI pin as i/p
				SET_BIT(DDRB, 6);	// Configure MISO pin as o/p
				CLEAR_BIT(DDRB, 7);	// Configure CLK  pin as i/p
				break;
			default: retVal |= E_NOT_OK;
				break;
		}
		SPI_SET_MODE(SPI_Cfgs->SPI_Mode);
		/* Configure the Data Ordering */
		SPI_SET_DATA_ORDER(SPI_Cfgs->SPI_Data_Order);
		/* Configure Clock Polarity */
		SPI_SET_CLK_POLARITY(SPI_Cfgs->SPI_Clock_Polarity);
		/* Configure Clock Phase */
		SPI_SET_CLK_PHASE(SPI_Cfgs->SPI_Clock_Phase);
		/* Configure the Clock Rate */
		SPI_SET_CLK_RATE(SPI_Cfgs->SPI_Clock_Rate);
		/* Configure Double Speed Mode */
		SPI_DOUBLE_SPEED_CFG(SPI_Cfgs->SPI_Double_Speed);		
		/* Configure the Interrupts (if needed) */
		if(SPI_Cfgs->SPI_ISR)
		{
			// 1. Enable the Global Interrupts
			INTERRUPT_GI_ENABLE();
			// 2. Assign the Interrupt Handler
			SPI_Default_Interrupt_Handler = SPI_Cfgs->SPI_ISR;
			// 3. Enable the SPI Interrupts
			INTI_SPI_INTERRUPT_ENABLE();
		}
		/* Reset the data register */
		//SPDR = 0x00;
		/* Enable the SPI Module */
		SPI_SET_ENABLE();
		/* Set the Initialization flag */
		SPI_Module_Is_Initialized = 1;
	}
	return retVal;
}
/**
 * @brief De-initializes the SPI module
 *
 * This function de-initializes the SPI module.
 *
 * @return Std_ReturnType E_OK on success, E_NOT_OK on failure if the module is not initialized
 */
Std_ReturnType SPI_DeInit(void)
{
	if(SPI_Module_Is_Initialized)
	{
		/* Disable the SPI Module */
		SPI_SET_DISABLE();
		/* Disable the Interrupts for the SPI Module */
		INTI_SPI_INTERRUPT_DISABLE();
		/* Clear the Initialization flag */
		SPI_Module_Is_Initialized = 0;
		
		return E_OK;
	}
	else
	{
		return E_NOT_OK;	/* SPI Module is not initialized already */
	}
}
/**
 * @brief Transceives data over the SPI module
 *
 * This function transmits the given data and optionally receives the received data.
 *
 * @param Data_Sent Data to be transmitted
 * @param Data_Received Pointer to store the received data (optional)
 * @return Std_ReturnType E_OK on success, E_NOT_OK on failure
 */
Std_ReturnType SPI_Transceive(uint8_t Data_Sent, uint8_t * Data_Received)
{
	Std_ReturnType retVal = E_OK;
	if(SPI_Module_Is_Initialized)
	{
		if(NULL == Data_Received)
		{
			// Not Interested in the received data /* Mainly Used With Interrupts */
			retVal |= gpio_pin_write_logic(&ss_pin, STD_LOW);
			SPI_WRITE(Data_Sent);
			while(!interrupt_flag); /* Wait for the transfer To complete */
			interrupt_flag = 0;
			retVal |= gpio_pin_write_logic(&ss_pin, STD_HIGH);
		}
		else
		{
			// Interested in the received data.
			if(!SPI_IS_TRASNSFER_COMPLETE())
			{
				SPI_WRITE(Data_Sent);
				while(!interrupt_flag);/* Wait for the transfer To complete */
				*Data_Received = SPDR;
				interrupt_flag = 0;
			}
			else
			{
				retVal |= E_NOT_OK;
			}
		}
	}
	else
	{
		retVal |= E_NOT_OK;
	}

	return retVal;
}

/* --------------- Section : SPI Interrupt Routine --------------- */
void __vector_12(void) __attribute__((signal));
void __vector_12(void)
{
	interrupt_flag = 1;
	if(SPI_Default_Interrupt_Handler)
		SPI_Default_Interrupt_Handler();
}
