#include "stm32f10x.h"
#define TOTAL_THREADS 8
#define SCH_FIFO_LEN 20

#define RUN 1
#define SLEEP 0
#define THREAD_RUN_NOW 0xffff
#define THREAD_SLEEP 0


void sch_ScheduleSelfRun(unsigned int run_timeout);
void sch_InitScheduler();
void sch_SchedulerTickInt();
void sch_RegisterThread(void (*thread_method)(), unsigned char thread_id,  unsigned char thread_priority, unsigned int run_shedule);
void sch_ScheduleThreadRun(unsigned char target_id, unsigned int run_timeout);
void sch_IntScheduleThreadRun(unsigned char target_id, unsigned int run_timeout);
void sch_RunScheduler();
void PrepareScheduler();
