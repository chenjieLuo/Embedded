//This is a simple and general RTOS kernel writeen for small applications in embedded project.

#include <stdint.h>
#include "miros.h"
#include "qassert.h"

Q_DEFINE_THIS_FILE

OSThread * volatile OS_curr;
OSThread * volatile OS_next;

OSThread *OS_thread[32 + 1];
uint8_t OS_threadNum;
uint8_t OS_currIdx;

void OS_init(void) {
    *(uint32_t volatile *)0xE000ED20 |= (0xFFU << 16);
}

void OS_sched(void) {
    ++OS_currIdx;
    if (OS_currIdx == OS_threadNum) {
        OS_currIdx = 0U;
    }
    OS_next = OS_thread[OS_currIdx];
    
    if (OS_next != OS_curr) {
        *(uint32_t volatile *)0xE000ED04 = (1U << 28);
    }
}

void OS_run(void) {
    OS_onStartup();

    __disable_irq();
    OS_sched();
    __enable_irq();

    Q_ERROR();
}

void OSThread_start(
    OSThread *me,
    OSThreadHandler threadHandler,
    void *stkSto, uint32_t stkSize)
{
    uint32_t *sp = (uint32_t *)((((uint32_t)stkSto + stkSize) / 8) * 8);
    uint32_t *stk_limit;
    
    *(--sp) = (1U << 24);  /* xPSR */
    *(--sp) = (uint32_t)threadHandler; /* PC */
    *(--sp) = 0x0000000EU; /* LR  */
    *(--sp) = 0x0000000CU; /* R12 */
    *(--sp) = 0x00000003U; /* R3  */
    *(--sp) = 0x00000002U; /* R2  */
    *(--sp) = 0x00000001U; /* R1  */
    *(--sp) = 0x00000000U; /* R0  */
    *(--sp) = 0x0000000BU; /* R11 */
    *(--sp) = 0x0000000AU; /* R10 */
    *(--sp) = 0x00000009U; /* R9 */
    *(--sp) = 0x00000008U; /* R8 */
    *(--sp) = 0x00000007U; /* R7 */
    *(--sp) = 0x00000006U; /* R6 */
    *(--sp) = 0x00000005U; /* R5 */
    *(--sp) = 0x00000004U; /* R4 */

    me->sp = sp;
    
    stk_limit = (uint32_t *)(((((uint32_t)stkSto - 1U) / 8) + 1U) * 8);

    for (sp = sp - 1U; sp >= stk_limit; --sp) {
        *sp = 0xDEADBEEFU;
    }

    Q_ASSERT(OS_threadNum < Q_DIM(OS_thread));

    OS_thread[OS_threadNum] = me;
    ++OS_threadNum;
}

__asm
void PendSV_Handler(void) {
    IMPORT  OS_curr
    IMPORT  OS_next
   
    CPSID         I

    LDR           r1,=OS_curr
    LDR           r1,[r1,#0x00]
    CBZ           r1,PendSV_restore

    PUSH          {r4-r11}    

    LDR           r1,=OS_curr
    LDR           r1,[r1,#0x00]
    STR           sp,[r1,#0x00]

PendSV_restore    
    LDR           r1,=OS_next
    LDR           r1,[r1,#0x00]
    LDR           sp,[r1,#0x00]

    LDR           r1,=OS_next
    LDR           r1,[r1,#0x00]
    LDR           r2,=OS_curr
    STR           r1,[r2,#0x00]

    POP           {r4-r11}    

    CPSIE         I

    BX            lr    
}
