/* communication_n8n.c - Data export to n8n workflow */
#include "hal_data.h"
#include "eeg_types.h"
#include "mtk3_bsp2/include/tk/tkernel.h"

void task_communication_entry(INT stacd, void *exinf)
{
    (void)stacd;
    (void)exinf;

    while(1)
    {
        /* Periodic data export every 30 seconds */
        tk_dly_tsk(30000); // 30 second delay

        /* TODO: Implement data export */
        // - Aggregate cognitive state data
        // - Format JSON payload
        // - Send to n8n webhook via WiFi/Bluetooth
    }
}
