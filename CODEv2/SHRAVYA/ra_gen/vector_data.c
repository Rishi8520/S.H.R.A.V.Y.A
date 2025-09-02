/* generated vector source file - do not edit */
#include "bsp_api.h"
/* Do not build these data structures if no interrupts are currently allocated because IAR will have build errors. */
#if VECTOR_DATA_IRQ_COUNT > 0
        BSP_DONT_REMOVE const fsp_vector_t g_vector_table[BSP_ICU_VECTOR_NUM_ENTRIES] BSP_PLACE_IN_SECTION(BSP_SECTION_APPLICATION_VECTORS) =
        {
                        [0] = ssi_txi_isr, /* SSI0 TXI (Transmit data empty) */
            [1] = ssi_int_isr, /* SSI0 INT (Error interrupt) */
            [2] = spi_b_rxi_isr, /* SPI0 RXI (Receive buffer full) */
            [3] = spi_b_txi_isr, /* SPI0 TXI (Transmit buffer empty) */
            [4] = spi_b_tei_isr, /* SPI0 TEI (Transmission complete event) */
            [5] = spi_b_eri_isr, /* SPI0 ERI (Error) */
            [6] = r_icu_isr, /* ICU IRQ0 (External pin interrupt 0) */
        };
        #if BSP_FEATURE_ICU_HAS_IELSR
        const bsp_interrupt_event_t g_interrupt_event_link_select[BSP_ICU_VECTOR_NUM_ENTRIES] =
        {
            [0] = BSP_PRV_VECT_ENUM(EVENT_SSI0_TXI,GROUP0), /* SSI0 TXI (Transmit data empty) */
            [1] = BSP_PRV_VECT_ENUM(EVENT_SSI0_INT,GROUP1), /* SSI0 INT (Error interrupt) */
            [2] = BSP_PRV_VECT_ENUM(EVENT_SPI0_RXI,GROUP2), /* SPI0 RXI (Receive buffer full) */
            [3] = BSP_PRV_VECT_ENUM(EVENT_SPI0_TXI,GROUP3), /* SPI0 TXI (Transmit buffer empty) */
            [4] = BSP_PRV_VECT_ENUM(EVENT_SPI0_TEI,GROUP4), /* SPI0 TEI (Transmission complete event) */
            [5] = BSP_PRV_VECT_ENUM(EVENT_SPI0_ERI,GROUP5), /* SPI0 ERI (Error) */
            [6] = BSP_PRV_VECT_ENUM(EVENT_ICU_IRQ0,GROUP6), /* ICU IRQ0 (External pin interrupt 0) */
        };
        #endif
        #endif
