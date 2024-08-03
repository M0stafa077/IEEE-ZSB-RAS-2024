/*
 * spi.h
 *
 * Created: 8/2/2024 10:28:08 PM
 *  Author: Mostafa Asaad
 */ 
#ifndef SPI_H_
#define SPI_H_

/* --------------- Section : Includes --------------- */
#include "../Interrupts/INTI/MCAL_INTI.h"
#include "../MCAL_STD_TYPES.h"
/* --------------- Section: Macro Declarations --------------- */

/*
 * @brief		SPI Enable or disable
 * @defgroup	SPI_ENABLE_DISABLE
*/
#define SPI_ENABLE							(uint8_t)0x01
#define SPI_DISABLE							(uint8_t)0x00
/*
 * @brief		SPI Data Ordering
 * @defgroup	SPI_DATA_ORDER
*/
#define SPI_ORDER_LSB_FIRST					(uint8_t)0x01
#define SPI_ORDER_MSB_FIRST					(uint8_t)0x00
/*
 * @brief		SPI Mode
 * @defgroup	SPI_MODE
*/
#define SPI_MODE_MASTER						(uint8_t)0x01
#define SPI_MODE_SLAVE						(uint8_t)0x00
/*
 * @brief		SPI Clock Polarity
 * @defgroup	SPI_CLK_POLARITY
*/
#define SPI_CLK_POLARITY_HIGH				(uint8_t)0x01
#define SPI_CLK_POLARITY_LOW				(uint8_t)0x00
/*
 * @brief		SPI Clock Phase
 * @defgroup	SPI_CLK_PHASE
*/
#define SPI_CLK_PHASE_SAMPLE_AT_LEADING		(uint8_t)0x01
#define SPI_CLK_PHASE_SAMPLE_AT_TRAILING	(uint8_t)0x00
/*
 * @brief		SPI Double Speed Configuration
 * @defgroup	SPI_DOUBLE_SPEED_CFG
*/
#define SPI_DOUBLE_SPEED_ENABLE				(uint8_t)0x01
#define SPI_DOUBLE_SPEED_DISABLE			(uint8_t)0x00

/* --------------- Section: Macro Functions Declarations --------------- */

/*
 * @brief Enable SPI module.
*/
#define SPI_SET_ENABLE()					(SPCRbits.SPE = SPI_ENABLE)
/*
 * @brief Enable SPI module.
*/
#define SPI_SET_DISABLE()					(SPCRbits.SPE = SPI_DISABLE)
/*
 * @brief Set the data tranceiving order in SPI module
*/
#define SPI_SET_DATA_ORDER(ORDER)			(SPCRbits.DORD = ORDER)
/*
 * @brief Set the Operating Mode of SPI module
*/
#define SPI_SET_MODE(MODE)					(SPCRbits.MSTR = MODE)
/*
 * @brief Set the Clock Polarity of SPI module
*/
#define SPI_SET_CLK_POLARITY(POLARITY)		(SPCRbits.CPOL = POLARITY)
/*
 * @brief Set the Clock Phase of SPI module
*/
#define SPI_SET_CLK_PHASE(PHASE)			(SPCRbits.CPHA = PHASE)
/*
 * @brief Set the Clock Rate of the SPI module
*/
#define SPI_SET_CLK_RATE(RATE)				(SPCRbits.SPR = RATE)
/*
 * @brief Select the SPI double speed configuration
*/
#define SPI_DOUBLE_SPEED_CFG(CFG)			(SPSRbits.SPI2X = CFG)
/*
 * @brief Reads the SPI data register
*/
#define SPI_READ()							(SPDR)
/*
 * @brief Reads the SPI data register
*/
#define SPI_WRITE(DATA)						(SPDR = DATA)
/*
 * @brief SPI Interrupt Flag: When a serial transfer is complete, the SPIF Flag is set.
*/
#define SPI_IS_TRASNSFER_COMPLETE()			(SPSRbits.SPIF)
/* --------------- Section: Data Type Declarations --------------- */

typedef enum
{
	SPI_CLK_RATE_FOSC_BY_4 = 0,
	SPI_CLK_RATE_FOSC_BY_16,
	SPI_CLK_RATE_FOSC_BY_64,
	SPI_CLK_RATE_FOSC_BY_128
} SPI_ClockRate_t;

typedef struct
{
	interrupt_handler_t SPI_ISR;	/* !< SPI Interrpt Service Routine */
	uint8_t SPI_Mode;				/* !< SPI Mode, Takes value @SPI_MODE */
	uint8_t SPI_Data_Order;			/* !< SPI Data Order Configuration, takes value @SPI_DATA_ORDER */
	uint8_t SPI_Clock_Polarity;		/* !< SPI Clock Polarity Configuration, takes value @SPI_CLK_POLARITY */
	uint8_t SPI_Clock_Phase;		/* !< SPI Clock Phase Configuration, takes value @SPI_CLK_PHASE */
	uint8_t SPI_Double_Speed;		/* !< SPI Double Speed Configuration, takes value @SPI_DOUBLE_SPEED_CFG */
	SPI_ClockRate_t SPI_Clock_Rate;	/* !< SPI Clock Rate Configuration, takes value @SPI_ClockRate_t */
} SPI_Configurations_t;

/*---------------  Section: Function Declarations --------------- */

/**
 * @brief Initializes the SPI module
 *
 * This function initializes the SPI module according to the provided configurations.
 *
 * @param SPI_Cfgs Pointer to the SPI module configurations structure
 * @return Std_ReturnType E_OK on success, E_NOT_OK on failure
 */
Std_ReturnType SPI_Init(const SPI_Configurations_t * SPI_Cfgs);
/**
 * @brief De-initializes the SPI module
 *
 * This function de-initializes the SPI module.
 *
 * @return Std_ReturnType E_OK on success, E_NOT_OK on failure if the module is not initialized
 */
Std_ReturnType SPI_DeInit(void);
/**
 * @brief Transceives data over the SPI module
 *
 * This function transmits the given data and optionally receives the received data.
 *
 * @param Data_Sent Data to be transmitted
 * @param Data_Received Pointer to store the received data (optional)
 * @return Std_ReturnType E_OK on success, E_NOT_OK on failure
 */
Std_ReturnType SPI_Transceive(uint8_t Data_Sent, uint8_t * Data_Received);

#endif /* SPI_H_ */