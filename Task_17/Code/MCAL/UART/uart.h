/*
 * uart.h
 *
 * Created: 7/28/2024 1:10:46 AM
 *  Author: Mostafa Asaad
 */ 


#ifndef UART_H_
#define UART_H_
/* --------------- Section : Includes --------------- */
#include "../Interrupts/INTI/MCAL_INTI.h"
#include "../MCAL_STD_TYPES.h"
/* --------------- Section: Macro Declarations --------------- */
/*
 * The USART Module is enabled.
 */
#define UART_ENABLE							STD_ENABLE
/*
 * The USART Module is disabled.
 */
#define UART_DISABLE						STD_DISABLE
/*
 * @brief UART Mode of Operation 
 * @defgroup UART_Operation_Mode
 */
#define UART_MODE_SYNCHRONOUS				(uint8_t)(0x01)
#define UART_MODE_ASYNCHRONOUS				(uint8_t)(0x00)

/*
* @brief UART Number of stop bits
* @defgroup UART_STOP_BIT_CFG
*/
#define UART_STOP_ONE_BIT					(uint8_t)(0x00)
#define UART_STOP_TWO_BIT					(uint8_t)(0x01)

/*
* @defgroup UART_DOUBLE_SPEED_CFGS
*/
#define UART_DOUBLE_SPEED_ENABLED			(uint8_t)(0x01)
#define UART_DOUBLE_SPEED_DISABLED			(uint8_t)(0x00)

#define UART_BAUD_RATE_REG_MAX				(0xFFF)
/* --------------- Section: Macro Functions Declarations --------------- */

#define UART_TX_ENABLE()					(UCSRBbits.TXEN = STD_ENABLE)
#define UART_TX_DISABLE()					(UCSRBbits.TXEN = STD_DISABLE)

#define UART_RX_ENABLE()					(UCSRBbits.RXEN = STD_ENABLE)
#define UART_RX_DISABLE()					(UCSRBbits.RXEN = STD_DISABLE)
/* --------------- Section: Data Type Declarations --------------- */

typedef enum
{
	UART_PARITY_BIT_DISABLED = 0,
	UART_PARITY_BIT_EVEN = 2,
	UART_PARITY_BIT_ODD = 3
} UART_ParityBit_t;

typedef enum
{
	UART_DATA_BITS_5,
	UART_DATA_BITS_6,
	UART_DATA_BITS_7,
	UART_DATA_BITS_8,
	UART_DATA_BITS_9 = 7,
} UART_No_Of_DataBits_t;

typedef struct
{
	uint32_t UART_BaudRate;							/* !< The UART Baud Rate in bps */
	interrupt_handler_t UART_Tx_InterruptHandler;	/* !< The Interrupt Service Routine for UART Transmission Complete */
	interrupt_handler_t UART_Rx_InterruptHandler;	/* !< The Interrupt Service Routine for UART Reception Complete */
	uint8_t UART_Mode;								/* !< The Mode of UART Operation, @ref UART_Operation_Mode */
	uint8_t UART_No_Of_StopBits;					/* !< The number of stop bits, @ref UART_STOP_BIT_CFG */
	UART_No_Of_DataBits_t UART_DataBits;			/* !< The number of data bits in the frame */
	UART_ParityBit_t UART_ParityBit;				/* !< The Parity bit configuration */
	uint8_t UART_DoubleSpeed_State;					/* !< The state of the double speed, @ref UART_DOUBLE_SPEED_CFGS */
} UART_t;
/*---------------  Section: Function Declarations --------------- */

/**
 * A helper software interface initializes the 
 * uart module.
 * @param uart_Obj : A pointer to an object of 
 * the uart module.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType UART_ASYNC_Init(const UART_t * uart_Obj);
/*
 * A helper software interface de-initializes the
 * uart module.
 * @param uart_Obj : A pointer to an object of 
 * the uart module.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType UART_ASYNC_DeInit(const UART_t * uart_Obj);
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
Std_ReturnType UART_ASYNC_Read_Byte_With_Blocking(uint8_t * byte_read);
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
Std_ReturnType UART_ASYNC_Read_Byte_With_NoBlocking(uint8_t * byte_read);
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
Std_ReturnType UART_ASYNC_Write_Byte_With_Blocking(const uint8_t byte_written);
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
Std_ReturnType UART_ASYNC_Write_Byte_With_NoBlocking(const uint8_t byte_written);

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
Std_ReturnType UART_ASYNC_Write_String_With_Blocking(const uint8_t * string_written);
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
Std_ReturnType UART_ASYNC_Write_String_With_NoBlocking(const uint8_t * string_written);
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
Std_ReturnType UART_ASYNC_Write_Number_With_Blocking(const sint32_t number_written);
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
Std_ReturnType UART_ASYNC_Write_Number_With_NoBlocking(const sint32_t number_written);
#endif /* UART_H_ */