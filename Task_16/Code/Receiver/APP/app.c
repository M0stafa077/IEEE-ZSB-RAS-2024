/*
 * app.c
 * Created: 6/30/2024 6:55:47 PM
 *  Author: Mostafa Asaad
 */ 
/* --------------- Section : Includes --------------- */
#include "app.h"
/* --------------- Section: Global Variables --------------- */

static volatile uint8_t Value_Received = 0;
UART_t uart_receiver = 
{
	.UART_Tx_InterruptHandler = NULL,
	.UART_Rx_InterruptHandler = uart_rx_callBack, 
	.UART_BaudRate = 9600,
	.UART_DataBits = UART_DATA_BITS_8,
	.UART_DoubleSpeed_State = UART_DOUBLE_SPEED_DISABLED,
	.UART_Mode = UART_MODE_ASYNCHRONOUS,
	.UART_No_Of_StopBits = UART_STOP_ONE_BIT,
	.UART_ParityBit = UART_PARITY_BIT_DISABLED
};

int main(void)
{
	Std_ReturnType ret = E_OK;

	ret |= app_init();
	ret |= UART_ASYNC_Write_String_With_Blocking("Receiver\r");

	while(1)
	{
		
	}
}

/*---------------  Section: Helper Functions Definitions --------------- */
Std_ReturnType app_init(void) 
{
	Std_ReturnType ret = E_OK;

	// ret |= ecu_layer_initialize();
	
	ret |= UART_ASYNC_Init(&uart_receiver);

	return ret;
}

void uart_rx_callBack(void)
{
	UART_ASYNC_Read_Byte_With_NoBlocking(&Value_Received);
	UART_ASYNC_Write_Byte_With_NoBlocking(Value_Received);
}