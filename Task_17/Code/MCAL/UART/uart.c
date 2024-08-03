/*
 * uart.c
 *
 * Created: 7/28/2024 1:10:46 AM
 *  Author: Mostafa Asaad
 */

/* --------------- Section : Includes --------------- */
#include "uart.h"
/* --------------- Section : Global Variables --------------- */
static interrupt_handler_t UART_Tx_DefaultInterruptHandler = NULL;
static interrupt_handler_t UART_Rx_DefaultInterruptHandler = NULL;
/*---------------  Section: Helper Functions Declaration --------------- */
Std_ReturnType UART_BaudRate_Cfg(const uint32_t baudRate);
void UART_Frame_Cfg(const UART_t * uart_Obj);
/*---------------  Section: Function Definitions --------------- */

/**
 * A helper software interface initializes the 
 * uart module.
 * @param uart_Obj : A pointer to an object of 
 * the uart module.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType UART_ASYNC_Init(const UART_t * uart_Obj)
{
	Std_ReturnType retVal = E_OK;
	if(NULL == uart_Obj)
		{ retVal |= E_NOT_OK; }
	else
	{
		/* Disable the Global Interrupts */
		INTERRUPT_GI_DISABLE();
		/* Disable the UART Module, Tx and Rx */
		UART_TX_DISABLE();
		UART_RX_DISABLE();
		/* Configure the Baud-Rate */
		retVal |= UART_BaudRate_Cfg(uart_Obj->UART_BaudRate);
		/* Configure the Frame */
		UART_Frame_Cfg(uart_Obj);
		/* Configure the UART Mode */
		UCSRC |= (uint8_t)((1U << 7U) | (uart_Obj->UART_Mode << 6));
		/* Configure the Interrupts */
		// Enable the Global Interrupts
		INTERRUPT_GI_ENABLE();
		// Enable the Tx Interrupts
		INTI_UART_TX_INTERRUPT_ENABLE();
		// Enable the Rx Interrupts
		INTI_UART_RX_INTERRUPT_ENABLE();
		// Assign the Interrupt Handlers
		UART_Rx_DefaultInterruptHandler = uart_Obj->UART_Rx_InterruptHandler;
		UART_Tx_DefaultInterruptHandler = uart_Obj->UART_Tx_InterruptHandler;
		/* Enable the UART Module, Tx and Rx */
		UART_TX_ENABLE();
		UART_RX_ENABLE();
	}
	return retVal;
}
/*
 * A helper software interface de-initializes the
 * uart module.
 * @param uart_Obj : A pointer to an object of 
 * the uart module.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType UART_ASYNC_DeInit(const UART_t * uart_Obj)
{
	Std_ReturnType retVal = E_OK;
	if(NULL == uart_Obj)
		{ retVal = E_NOT_OK; }
	else
	{
		/* Disable the Interrupts */
		INTI_UART_TX_INTERRUPT_DISABLE();
		INTI_UART_RX_INTERRUPT_DISABLE();
		/* Disable the UART Module, Tx and Rx */
		UART_TX_DISABLE();
		UART_RX_DISABLE();
	}
	return retVal;
}
/**
 * A helper software interface reads a byte with 
 * the uart module.
 * @param uart_Obj : A pointer to an object of 
 * the uart module.
 * @param byte_read
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType UART_ASYNC_Read_Byte_With_Blocking(uint8_t * byte_read)
{
	Std_ReturnType retVal = E_OK;
	if(NULL == byte_read)
	{ retVal = E_NOT_OK; }
	else
	{
		while(!(UCSRAbits.RXC))
			;
		*byte_read = UDR;
	}
	return retVal;
}
/**
 * A helper software interface reads a byte with 
 * the uart module.
 * @param uart_Obj : A pointer to an object of 
 * the uart module.
 * @param byte_read : A pointer to the byte in which the data
 *                      will be stored.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType UART_ASYNC_Read_Byte_With_NoBlocking(uint8_t * byte_read)
{
	Std_ReturnType retVal = E_OK;
	if(NULL == byte_read)
	{ retVal = E_NOT_OK; }
	else
	{
		if(UCSRAbits.RXC)
			{ *byte_read = UDR; }
		else
			{ retVal |= E_NOT_OK; }
	}
	return retVal;
}
/**
 * A helper software interface sends/writes a 
 * byte with the uart module.
 * @param uart_Obj : A pointer to an object of 
 * the uart module.  
 * @param byte_written
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType UART_ASYNC_Write_Byte_With_Blocking(const uint8_t byte_written)
{
	Std_ReturnType retVal = E_OK;
	
	/* Wait till the last frame is sent */
	while(!UCSRAbits.UDRE);
	/* Write the data to the data register */
	UDR = byte_written;
	
	return retVal;
}
/**
 * A helper software interface sends/writes a 
 * byte with the uart module.
 * @param uart_Obj : A pointer to an object of 
 * the uart module.  
 * @param byte_read : The byte to be written.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType UART_ASYNC_Write_Byte_With_NoBlocking(const uint8_t byte_written)
{
	/* Send the data if the last frame is sent */
	if(UCSRAbits.UDRE)
	{
		UDR = byte_written;
	}
	else
	{
		return E_NOT_OK;
	}
	return E_OK;
}

/**
 * A helper software interface sends/writes a 
 * string with the uart module.
 * @param uart_Obj : A pointer to an object of 
 * the uart module.  
 * @param byte_written
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType UART_ASYNC_Write_String_With_Blocking(const uint8_t * string_written)
{
	Std_ReturnType retVal = E_OK;
	if(NULL == string_written)
		{ retVal = E_NOT_OK; }
	else
	{
		uint16_t counter = ZERO_INIT;
		for(; string_written[counter] != '\0'; ++counter)
		{
			retVal |= UART_ASYNC_Write_Byte_With_Blocking(string_written[counter]);
		}
	}
	return retVal;
}
/**
 * A helper software interface sends/writes a 
 * byte with the uart module.
 * @param uart_Obj : A pointer to an object of 
 * the uart module.  
 * @param byte_written
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType UART_ASYNC_Write_String_With_NoBlocking(const uint8_t * string_written)
{
	Std_ReturnType retVal = E_OK;
	if(NULL == string_written)
		{ retVal = E_NOT_OK; }
	else
	{
		uint16_t counter = ZERO_INIT;
		for(; string_written[counter] != '\0'; ++counter)
		{
			retVal |= UART_ASYNC_Write_Byte_With_NoBlocking(string_written[counter]);
		}
	}
	return retVal;
}
/**
 * A helper software interface sends/writes a 
 * number with the uart module.
 * @param uart_Obj : A pointer to an object of 
 * the uart module.  
 * @param byte_written
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType UART_ASYNC_Write_Number_With_Blocking(const sint32_t number_written)
{
	Std_ReturnType retVal = E_OK;
	uint8_t sent_string[30] = { '\0' };
	snprintf(sent_string, sizeof(sent_string), "%ld", number_written);
	retVal |= UART_ASYNC_Write_String_With_Blocking(sent_string);
	
	return retVal;
}
/**
 * A helper software interface sends/writes a 
 * number with the uart module.
 * @param uart_Obj : A pointer to an object of 
 * the uart module.  
 * @param byte_written
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType UART_ASYNC_Write_Number_With_NoBlocking(const sint32_t number_written)
{
	Std_ReturnType retVal = E_OK;
	uint8_t sent_string[30] = { '\0' };
	snprintf(sent_string, sizeof(sent_string), "%ld", number_written);
	retVal |= UART_ASYNC_Write_String_With_NoBlocking(sent_string);
	
	return retVal;
}

/*---------------  Section: Helper Functions Definitions --------------- */

Std_ReturnType UART_BaudRate_Cfg(const uint32_t baudRate)
{
	Std_ReturnType retVal = E_OK;
	if(UART_BAUD_RATE_REG_MAX < (F_CPU / (16 * baudRate)) - 1)
		{ retVal |= E_NOT_OK; }
	else
	{
		uint16_t register_value = 0;
		register_value = (F_CPU / (16 * baudRate)) - 1;
		UBRRH = (uint8_t)(register_value >> 8);
		UBRRL = (uint8_t)(register_value);
	}
	return retVal;
}

void UART_Frame_Cfg(const UART_t * uart_Obj)
{
	/* 1. Configure the number of data bits */
	UCSRBbits.UCSZ2 = (uart_Obj->UART_DataBits >> 2U) << 2;
	UCSRC |= (uint8_t)((1U << 7U) | ((uart_Obj->UART_DataBits & 3U) << 1U));
	/* 2. Configure the Parity Bit */
	UCSRC |= (uint8_t)((1U << 7U) | (((uint8_t)(uart_Obj->UART_ParityBit) & 3U) << 4U));
	/* 3. Configure the Stop Bit */
	UCSRC |= (uint8_t)((1U << 7U) | (uart_Obj->UART_No_Of_StopBits << 3U));
}

/* ----------- Section: UART Interrupt Service Routines ------------ */
void __vector_13(void) __attribute__((signal));
void __vector_13(void)
{
	if(UART_Rx_DefaultInterruptHandler)
		{ UART_Rx_DefaultInterruptHandler(); }
}

void __vector_15(void) __attribute__((signal));
void __vector_15(void)
{
	if(UART_Tx_DefaultInterruptHandler)
	{ UART_Tx_DefaultInterruptHandler(); }
}