#include <stdint.h>
#include "bsp.h"

uint32_t stack_thread1[40];
uint32_t *sp_thread1 = &stack_thread1[40];
void my_thread1() {
    while (1) {
        BSP_ledGreenOn();
        BSP_delay(BSP_TICKS_PER_SEC / 4U);
        BSP_ledGreenOff();
        BSP_delay(BSP_TICKS_PER_SEC * 3U / 4U);
    }
}

uint32_t stack_thread2[40];
uint32_t *sp_thread2 = &stack_thread2[40];
void my_thread2() {
    while (1) {
        BSP_ledBlueOn();
        BSP_delay(BSP_TICKS_PER_SEC / 2U);
        BSP_ledBlueOff();
        BSP_delay(BSP_TICKS_PER_SEC / 3U);
    }
}


//Background
int main() {
    BSP_init();

    //According to Cortex-M4, all right registers will be saved
    *(--sp_thread1) = (1U << 24);  /* xPSR */
    *(--sp_thread1) = (uint32_t)&my_thread1; /* PC */
    *(--sp_thread1) = 0x0000000EU; /* LR  */
    *(--sp_thread1) = 0x0000000CU; /* R12 */
    *(--sp_thread1) = 0x00000003U; /* R3  */
    *(--sp_thread1) = 0x00000002U; /* R2  */
    *(--sp_thread1) = 0x00000001U; /* R1  */
    *(--sp_thread1) = 0x00000000U; /* R0  */

    //According to Cortex-M4, all right registers will be saved
    *(--sp_thread2) = (1U << 24);  /* xPSR */
    *(--sp_thread2) = (uint32_t)&my_thread2; /* PC */
    *(--sp_thread2) = 0x0000000EU; /* LR  */
    *(--sp_thread2) = 0x0000000CU; /* R12 */
    *(--sp_thread2) = 0x00000003U; /* R3  */
    *(--sp_thread2) = 0x00000002U; /* R2  */
    *(--sp_thread2) = 0x00000001U; /* R1  */
    *(--sp_thread2) = 0x00000000U; /* R0  */

    while (1) {
    }

    return 0;
}
