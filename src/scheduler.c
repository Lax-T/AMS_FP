#include "scheduler.h"

void (*g_thread_functions[TOTAL_THREADS])();
unsigned char g_thread_priorities[TOTAL_THREADS];
unsigned char g_thread_run_flags[TOTAL_THREADS];
unsigned int g_thread_timeouts_cnt[TOTAL_THREADS];

unsigned int g_schedule_timeouts_fifo[SCH_FIFO_LEN];
unsigned char g_schedule_targets_fifo[SCH_FIFO_LEN];
unsigned char g_schedule_fifo_write_ptr = 0;
unsigned char g_schedule_fifo_read_ptr = 0;

unsigned int g_intschedule_timeouts_fifo[SCH_FIFO_LEN];
unsigned char g_intschedule_targets_fifo[SCH_FIFO_LEN];
unsigned char g_intschedule_fifo_write_ptr = 0;
unsigned char g_intschedule_fifo_read_ptr = 0;

unsigned char g_running_thread_id;


void sch_RegisterThread(void (*thread_method)(), unsigned char thread_id,  unsigned char thread_priority, unsigned int run_shedule) {
	g_thread_functions[thread_id] = (*thread_method);
	g_thread_priorities[thread_id] = thread_priority;
	g_thread_timeouts_cnt[thread_id] = run_shedule;
}

void sch_ScheduleSelfRun(unsigned int run_timeout) {
	g_schedule_targets_fifo[g_schedule_fifo_write_ptr] = g_running_thread_id;
	g_schedule_timeouts_fifo[g_schedule_fifo_write_ptr] = run_timeout;
	g_schedule_fifo_write_ptr++;
	if (g_schedule_fifo_write_ptr >= SCH_FIFO_LEN) {
		g_schedule_fifo_write_ptr = 0;
	}
}

/* Schedule thread run within thread */
void sch_ScheduleThreadRun(unsigned char target_id, unsigned int run_timeout) {
	g_schedule_targets_fifo[g_schedule_fifo_write_ptr] = target_id;
	g_schedule_timeouts_fifo[g_schedule_fifo_write_ptr] = run_timeout;
	g_schedule_fifo_write_ptr++;
	if (g_schedule_fifo_write_ptr >= SCH_FIFO_LEN) {
		g_schedule_fifo_write_ptr = 0;
	}
	switch (run_timeout) {
	case THREAD_RUN_NOW:
		g_thread_run_flags[target_id] = RUN;
		break;
	case THREAD_SLEEP:
		g_thread_run_flags[target_id] = SLEEP;
		break;
	}
}

/* Schedule thread run within interrupt*/
void sch_IntScheduleThreadRun(unsigned char target_id, unsigned int run_timeout) {
	g_intschedule_targets_fifo[g_intschedule_fifo_write_ptr] = target_id;
	g_intschedule_timeouts_fifo[g_intschedule_fifo_write_ptr] = run_timeout;
	g_intschedule_fifo_write_ptr++;
	if (g_intschedule_fifo_write_ptr >= 20) {
		g_intschedule_fifo_write_ptr = 0;
	}
	switch (run_timeout) {
	case THREAD_RUN_NOW:
		g_thread_run_flags[target_id] = RUN;
		break;
	case THREAD_SLEEP:
		g_thread_run_flags[target_id] = SLEEP;
		break;
	}
}

/* Init scheduler (set all threads to sleep) */
void sch_InitScheduler() {
	unsigned char i;
	for (i=0; i < TOTAL_THREADS; i++) {
		g_thread_run_flags[i] = SLEEP;
		g_thread_timeouts_cnt[i] = 0;
	}
}

/* Scheduler timing interrupt handler */
void sch_SchedulerTickInt() {
	unsigned char i;
	unsigned int thread_time_val;
	unsigned char target_n;

	if (g_schedule_fifo_read_ptr != g_schedule_fifo_write_ptr) {
		while (g_schedule_fifo_read_ptr != g_schedule_fifo_write_ptr) {
			target_n = g_schedule_targets_fifo[g_schedule_fifo_read_ptr];
			thread_time_val = g_schedule_timeouts_fifo[g_schedule_fifo_read_ptr];
			g_thread_timeouts_cnt[target_n] = thread_time_val;
			g_schedule_fifo_read_ptr++;
			if (g_schedule_fifo_read_ptr >= 20) {
				g_schedule_fifo_read_ptr = 0;
			}
		}
	}
	if (g_intschedule_fifo_read_ptr != g_intschedule_fifo_write_ptr) {
		while (g_intschedule_fifo_read_ptr != g_intschedule_fifo_write_ptr) {
			target_n = g_intschedule_targets_fifo[g_intschedule_fifo_read_ptr];
			thread_time_val = g_intschedule_timeouts_fifo[g_intschedule_fifo_read_ptr];
			g_thread_timeouts_cnt[target_n] = thread_time_val;
			g_intschedule_fifo_read_ptr++;
			if (g_intschedule_fifo_read_ptr >= 20) {
				g_intschedule_fifo_read_ptr = 0;
			}
		}
	}
	for (i=0; i < TOTAL_THREADS; i++) {
		thread_time_val = g_thread_timeouts_cnt[i];
		if (thread_time_val > 0) {
			thread_time_val = thread_time_val - 1;
			if (thread_time_val == 0) {
				g_thread_run_flags[i] = RUN;
			}
			g_thread_timeouts_cnt[i] = thread_time_val;
		}
	}
}

/* Run scheduler, blocking */
void sch_RunScheduler() {
	unsigned char next_run_priority;
	unsigned char next_run_thread;
	unsigned char i;

	while (1) {
		next_run_priority = 0xff;
		next_run_thread = 0xff;

		for (i=0; i < TOTAL_THREADS; i++) {

			if (g_thread_run_flags[i] == RUN) {
				if (g_thread_priorities[i] < next_run_priority) {
					next_run_priority = g_thread_priorities[i];
					next_run_thread = i;
				}
			}
		}

		if (next_run_thread != 0xff) {
			g_running_thread_id = next_run_thread;
			(*g_thread_functions[next_run_thread])();
			g_thread_run_flags[next_run_thread] = SLEEP;
		}
	}
}
