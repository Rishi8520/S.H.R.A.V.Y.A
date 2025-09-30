/* generated vector header file - do not edit */
#ifndef VECTOR_DATA_H
#define VECTOR_DATA_H
#ifdef __cplusplus
        extern "C" {
        #endif
/* Number of interrupts allocated */
#ifndef VECTOR_DATA_IRQ_COUNT
#define VECTOR_DATA_IRQ_COUNT    (7)
#endif
/* ISR prototypes */
void ssi_txi_isr(void);
void ssi_int_isr(void);
void spi_b_rxi_isr(void);
void spi_b_txi_isr(void);
void spi_b_tei_isr(void);
void spi_b_eri_isr(void);
void r_icu_isr(void);

/* Vector table allocations */
#define VECTOR_NUMBER_SSI0_TXI ((IRQn_Type) 0) /* SSI0 TXI (Transmit data empty) */
#define SSI0_TXI_IRQn          ((IRQn_Type) 0) /* SSI0 TXI (Transmit data empty) */
#define VECTOR_NUMBER_SSI0_INT ((IRQn_Type) 1) /* SSI0 INT (Error interrupt) */
#define SSI0_INT_IRQn          ((IRQn_Type) 1) /* SSI0 INT (Error interrupt) */
#define VECTOR_NUMBER_SPI0_RXI ((IRQn_Type) 2) /* SPI0 RXI (Receive buffer full) */
#define SPI0_RXI_IRQn          ((IRQn_Type) 2) /* SPI0 RXI (Receive buffer full) */
#define VECTOR_NUMBER_SPI0_TXI ((IRQn_Type) 3) /* SPI0 TXI (Transmit buffer empty) */
#define SPI0_TXI_IRQn          ((IRQn_Type) 3) /* SPI0 TXI (Transmit buffer empty) */
#define VECTOR_NUMBER_SPI0_TEI ((IRQn_Type) 4) /* SPI0 TEI (Transmission complete event) */
#define SPI0_TEI_IRQn          ((IRQn_Type) 4) /* SPI0 TEI (Transmission complete event) */
#define VECTOR_NUMBER_SPI0_ERI ((IRQn_Type) 5) /* SPI0 ERI (Error) */
#define SPI0_ERI_IRQn          ((IRQn_Type) 5) /* SPI0 ERI (Error) */
#define VECTOR_NUMBER_ICU_IRQ0 ((IRQn_Type) 6) /* ICU IRQ0 (External pin interrupt 0) */
#define ICU_IRQ0_IRQn          ((IRQn_Type) 6) /* ICU IRQ0 (External pin interrupt 0) */
/* The number of entries required for the ICU vector table. */
#define BSP_ICU_VECTOR_NUM_ENTRIES (7)

#ifdef __cplusplus
        }
        #endif
#endif /* VECTOR_DATA_H */
