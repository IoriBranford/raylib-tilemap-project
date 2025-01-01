#ifndef AB0F4716_F889_4E95_8EBF_0036D400024E
#define AB0F4716_F889_4E95_8EBF_0036D400024E

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <limits.h>

typedef struct Task Task;
typedef void (*TaskFunc)(Task*);

struct Task {
    TaskFunc func;
    void *data;
    int priority;   // lower = earlier
};

void InitTasks(unsigned n);
void CloseTasks();

#define TASK_MAX_PRIORITY INT_MAX

Task* NewTask(TaskFunc func, void *data, int priority);
size_t NumTasksActive();
size_t NumTasksFree();

void EndTask(Task *task);

void UpdateTasks();

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* AB0F4716_F889_4E95_8EBF_0036D400024E */
