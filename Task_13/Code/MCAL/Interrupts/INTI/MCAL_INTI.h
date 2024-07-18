/*
 * MCAL_INTI.h
 *  brief: Internal Interrupts Interface.
 *  Created: 7/16/2024 9:03:34 PM
 *  Author: Mostafa Asaad
 */ 


#ifndef MCAL_INTI_H_
#define MCAL_INTI_H_

/* --------------- Section : Includes --------------- */
#include "../../registers.h"
#include "../MCAL_interrupt_cfg.h"

/* ===========================================================================*/
/* -------- Section: ADC INTERRUPT CONFIGURATIONs -------- */
#define INTI_ADC_INTERRUPT_ENABLE()				(ADCSRAbits.ADIE = INTERRUPT_ENABLE)
#define INTI_ADC_INTERRUPT_DISABLE()			(ADCSRAbits.ADIE = INTERRUPT_DISABLE)
#define INTI_ADC_CLR_FLAG()						(ADCSRAbits.ADIF = STD_DISABLE)
/* -------- Section: End of ADC INTERRUPT CONFIGURATIONs -------- */
/* ===========================================================================*/

#endif /* MCAL_INTI_H_ */