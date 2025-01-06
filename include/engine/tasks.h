#ifndef AB0F4716_F889_4E95_8EBF_0036D400024E
#define AB0F4716_F889_4E95_8EBF_0036D400024E

#include <stddef.h>
#include <limits.h>

typedef struct Task Task;
typedef void (*TaskFunc)(Task*);

struct Task {
    TaskFunc func;
    union {
        void *data;
        int idata;
    };
    int priority;   // lower = earlier
    int sleeping;
};

void InitTasks(unsigned n);
void CloseTasks();

#define TASK_MAX_PRIORITY INT_MAX

Task* NewTask(TaskFunc func, void *data, int priority);
size_t NumTasksActive();
size_t NumTasksFree();

void ReleaseTask(Task *task);
void EndTask(Task *task);
void PauseTask(Task *task);
void SleepTask(Task *task, int ticks);

void UpdateTasks();

#endif /* AB0F4716_F889_4E95_8EBF_0036D400024E */
