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

/* ===========================================================================*/
/* -------- Section: Timer 0 INTERRUPT CONFIGURATIONs -------- */

/* !< Timer/Counter0 Overflow Interrupt Enable */
#define INTI_TMR0_OF_INTERRUPT_ENABLE()			(TIMSKbits.TOIE0 = INTERRUPT_ENABLE)
/* !< Timer/Counter0 Overflow Interrupt Disable */
#define INTI_TMR0_OF_INTERRUPT_DISABLE()		(TIMSKbits.TOIE0 = INTERRUPT_DISABLE)
/* !< Timer/Counter0 Output Compare Match Interrupt Enable */
#define INTI_TMR0_OC_INTERRUPT_ENABLE()			(TIMSKbits.OCIE0 = INTERRUPT_ENABLE)
/* !< Timer/Counter0 Output Compare Match Interrupt Disable */
#define INTI_TMR0_OC_INTERRUPT_DISABLE()		(TIMSKbits.OCIE0 = INTERRUPT_DISABLE)
/* !< Clear Timer/Counter0 Overflow Flag */
#define INTI_TMR0_OF_CLR_FLAG()					(TIFRbits.TOV0 = STD_LOW)
/* !< Clear Timer/Counter0 Output Compare Flag 0 */
#define INTI_TMR0_OC_CLR_FLAG()					(TIFRbits.OCF0 = STD_LOW)

/* -------- Section: End of Timer 0 INTERRUPT CONFIGURATIONs -------- */
/* ===========================================================================*/

/* ===========================================================================*/
/* -------- Section: Timer 1 INTERRUPT CONFIGURATIONs -------- */

/* !< Timer/Counter1 Overflow Interrupt Enable */
#define INTI_TMR1_OF_INTERRUPT_ENABLE()			(TIMSKbits.TOIE1 = INTERRUPT_ENABLE)
/* !< Timer/Counter0 Overflow Interrupt Disable */
#define INTI_TMR1_OF_INTERRUPT_DISABLE()		(TIMSKbits.TOIE1 = INTERRUPT_DISABLE)

/* !< Timer/Counter1 Output Compare Match A Interrupt Enable */
#define INTI_TMR1_OCA_INTERRUPT_ENABLE()		(TIMSKbits.OCIE1A = INTERRUPT_ENABLE)
/* !< Timer/Counter0 Output Compare Match A Interrupt Disable */
#define INTI_TMR1_OCA_INTERRUPT_DISABLE()		(TIMSKbits.OCIE1A = INTERRUPT_DISABLE)
/* !< Timer/Counter1 Output Compare Match B Interrupt Enable */
#define INTI_TMR1_OCB_INTERRUPT_ENABLE()		(TIMSKbits.OCIE1B = INTERRUPT_ENABLE)
/* !< Timer/Counter1 Output Compare Match B Interrupt Disable */
#define INTI_TMR1_OCB_INTERRUPT_DISABLE()		(TIMSKbits.OCIE1B = INTERRUPT_DISABLE)

/* !< Timer/Counter1 Input-Capture Interrupt Enable */
#define INTI_TMR1_IC_INTERRUPT_ENABLE()			(TIMSKbits.TICIE1 = INTERRUPT_ENABLE)
/* !< Timer/Counter1 Input-Capture Interrupt Disable */
#define INTI_TMR1_IC_INTERRUPT_DISABLE()		(TIMSKbits.TICIE1 = INTERRUPT_DISABLE)

/* !< Clear Timer/Counter1 Overflow Flag */
#define INTI_TMR1_OF_CLR_FLAG()					(TIFRbits.TOV1 = STD_LOW)
/* !< Clear Timer/Counter1 Output Compare A Match Flag */
#define INTI_TMR1_OCA_CLR_FLAG()				(TIFRbits.OCF1A = STD_LOW)
/* !< Clear Timer/Counter1 Output Compare B Match Flag */
#define INTI_TMR1_OCB_CLR_FLAG()				(TIFRbits.OCF1B = STD_LOW)
/* !< Clear Timer/Counter1 Input Capture Flag */
#define INTI_TMR1_IC_CLR_FLAG()					(TIFRbits.ICF1 = STD_LOW)

/* -------- Section: End of Timer 1 INTERRUPT CONFIGURATIONs -------- */
/* ===========================================================================*/

/* ===========================================================================*/
/* -------- Section: UART INTERRUPT CONFIGURATIONs -------- */

// 1. UART Tx INTERRUPT CONFIGURATIONs
/* !< Enable the UART Tx Interrupt */
#define INTI_UART_TX_INTERRUPT_ENABLE()			(UCSRBbits.TXCIE = INTERRUPT_ENABLE)
/* !< Disable the UART Tx Interrupt */
#define INTI_UART_TX_INTERRUPT_DISABLE()		(UCSRBbits.TXCIE = INTERRUPT_DISABLE)
/* !< Clear the UART Tx Interrupt Flag */
#define INTI_UART_TX_CLR_FLAG()					(UCSRAbits.TXC = STD_LOW)

// 2. UART Rx INTERRUPT CONFIGURATIONs
/* !< Enable the UART Rx Interrupt */
#define INTI_UART_RX_INTERRUPT_ENABLE()			(UCSRBbits.RXCIE = INTERRUPT_ENABLE)
/* !< Disable the UART Rx Interrupt */
#define INTI_UART_RX_INTERRUPT_DISABLE()		(UCSRBbits.RXCIE = INTERRUPT_DISABLE)

/* -------- Section: End of UART INTERRUPT CONFIGURATIONs -------- */
/* ===========================================================================*/

#endif /* MCAL_INTI_H_ */