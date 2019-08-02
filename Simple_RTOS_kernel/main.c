#include <stdint.h>
#include "miros.h"
#include "bsp.h"

uint32_t stack_thread1[40];
OSThread sp_thread1;
void my_thread1() {
    while (1) {
        BSP_ledGreenOn();
        //BSP_delay(BSP_TICKS_PER_SEC / 4U);
        BSP_ledGreenOff();
        //BSP_delay(BSP_TICKS_PER_SEC * 3U / 4U);
    }
}

uint32_t stack_thread2[40];
OSThread sp_thread2;
void my_thread2() {
    while (1) {
        BSP_ledBlueOn();
        //BSP_delay(BSP_TICKS_PER_SEC / 2U);
        BSP_ledBlueOff();
        //BSP_delay(BSP_TICKS_PER_SEC / 3U);
    }
}

uint32_t stack_thread3[40];
OSThread sp_thread3;
void my_thread3() {
    while (1) {
        BSP_ledRedOn();
        //BSP_delay(BSP_TICKS_PER_SEC / 3U);
        BSP_ledRedOff();
        //BSP_delay(BSP_TICKS_PER_SEC * 3U / 5U);
    }
}

int main() {
    BSP_init();
    OS_init();

    OSThread_start(&sp_thread1, &my_thread1, stack_thread1, sizeof(stack_thread1));
	  OSThread_start(&sp_thread2, &my_thread2, stack_thread2, sizeof(stack_thread2));
	  OSThread_start(&sp_thread3, &my_thread3, stack_thread3, sizeof(stack_thread3));
    OS_run();

    //return 0;
}
