/*
 * app.c
 * Created: 6/30/2024 6:55:47 PM
 *  Author: Mostafa Asaad
 */ 
/* --------------- Section : Includes --------------- */
#include "app.h"
/* --------------- Section: Global Variables --------------- */

static volatile uint8_t Value_Sent = 0;
UART_t uart_sender = 
{
	.UART_Tx_InterruptHandler = NULL,
	.UART_Rx_InterruptHandler = NULL, 
	.UART_BaudRate = 9600,
	.UART_DataBits = UART_DATA_BITS_8,
	.UART_DoubleSpeed_State = UART_DOUBLE_SPEED_DISABLED,
	.UART_Mode = UART_MODE_ASYNCHRONOUS,
	.UART_No_Of_StopBits = UART_STOP_ONE_BIT,
	.UART_ParityBit = UART_PARITY_BIT_DISABLED
};

Timer1_Configurations_t timer = 
{
	.timer_mode = TIMER1_CTC_OCR1A_TOP_MODE,
	.oc1A_pin_behavior = TMR1_NON_PWM_NORMAL_PORT_OPERATION,
	.oc1B_pin_behavior = TMR1_NON_PWM_NORMAL_PORT_OPERATION,
	.timer1_clk_src = TMR1_PRESCALER_256,
	.timer1_isr = timer_callBack,
	.timer1_ocra_value = 31249,
	.timer1_ocrb_value = 31249,
	.timer1_preload_value = 0
};

int main(void)
{
	Std_ReturnType ret = E_OK;

	ret |= app_init();
	

	while(1)
	{
		
	}
}

/*---------------  Section: Helper Functions Definitions --------------- */
Std_ReturnType app_init(void) 
{
	Std_ReturnType ret = E_OK;

	// ret |= ecu_layer_initialize();
	
	ret |= UART_ASYNC_Init(&uart_sender);
	ret |= UART_ASYNC_Write_String_With_Blocking("Sender\r");
	ret |= Timer1_Init(&timer);

	return ret;
}

void timer_callBack(void)
{
	UART_ASYNC_Write_Number_With_NoBlocking(Value_Sent++);
	if(Value_Sent > 9)
		Value_Sent = 0;
}