#ifndef MIROS_H
#define MIROS_H

typedef struct {
		void *sp; 
} OSThread;

typedef void (*OSThreadHandler)();

void OS_init(void);

void OS_sched(void);

void OS_run(void);

void OS_onStartup(void);

void OSThread_start(
		OSThread *me,
		OSThreadHandler threadHandler,
		void *stksto, 
		uint32_t stkSize);

#endif
