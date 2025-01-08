#include <engine/tasks.h>
#include <util.h>

enum {
    PRIO_DONE = INT_MAX-1,
    PRIO_RELEASE
};

#define SLEEP_FOREVER INT_MAX

pool_typedef(Task, TaskPool)
pool_ctor(Task, TaskPool, NewTaskPool)

static TaskPool *tasks;

#define IsActive(task) (task->priority != PRIO_RELEASE)

bool IsTaskDone(Task *task) {
    return task->priority >= PRIO_DONE;
}

void InitEmptyTask(Task *task) {
    *task = (Task){0};
}

void ReleaseTask(Task *task) {
    task->priority = PRIO_RELEASE;
}

void EndTask(Task *task) {
    task->priority = PRIO_DONE;
}

void PauseTask(Task *task) {
    task->sleeping = SLEEP_FOREVER;
}

void SleepTask(Task *task, int ticks) {
    task->sleeping = ticks;
}

void InitTasks(unsigned n) {
    if (tasks)
        CloseTasks();
    tasks = NewTaskPool(n);
    pool_foreachall(tasks, InitEmptyTask);
}

void CloseTasks() {
    if (tasks)
        free_pool(tasks);
    tasks = NULL;
}

size_t NumTasksActive() {
    return tasks->nActive;
}

size_t NumTasksFree() {
    return count_free_pool_objs(tasks);
}

Task* NewTask(TaskFunc func, void *data, int priority) {
    Task *task = take_from_pool(tasks);
    if (task) {
        (*task) = (Task) {
            .func = func,
            .data = data,
            .priority = priority,
        };
    }
    return task;
}

int CompareTasks(const void *pa, const void *pb) {
    const Task *a = *(Task**)pa, *b = *(Task**)pb;
    if (a->priority < b->priority)
        return -1;
    if (a->priority > b->priority)
        return 1;
    return 0;
}

void PruneTasks() {
    prune_pool(tasks, IsActive);
}

void SortTasks() {
    sort_pool_active(tasks, CompareTasks);
}

void RunTasks() {
    Task **active = tasks->active;
    int nRunning = tasks->nActive;
    for (int i = 0; i < nRunning; ++i) {
        if (IsTaskDone(active[i]))
            nRunning = i;
    }

    for (int i = 0; i < nRunning; ++i) {
        Task *task = active[i];
        if (task->sleeping > 0) {
            if (task->sleeping < SLEEP_FOREVER)
                --task->sleeping;
        } else if (task->func) {
            task->func(task);
        }
    }
}

void UpdateTasks() {
    RunTasks();
    prune_pool(tasks, IsActive);
    sort_pool_active(tasks, CompareTasks);
}