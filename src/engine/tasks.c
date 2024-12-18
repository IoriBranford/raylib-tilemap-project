#include <engine/tasks.h>
#include <util.h>

typedef struct Task {
    TaskFunc func;
    void *data;
    unsigned priority;   // higher = earlier, 0 = ended
} Task;

pool_typedef(Task, TaskPool)
pool_ctor(Task, TaskPool, NewTaskPool)

static TaskPool *tasks;

#define IsUsed(task) (task->priority)

void InitEmptyTask(Task *task) {
    *task = (Task){
        .priority = 0,
        .data = NULL,
        .func = NULL
    };
}

void RunTask(Task *task) {
    task->func(task->data);
}

void EndTask(Task *task) {
    task->priority = 0;
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

size_t NumTasksAvailable() {
    return count_free_pool_objs(tasks);
}

Task* NewTask(TaskFunc func, void *data, unsigned priority) {
    Task *task = take_from_pool(tasks);
    if (task) {
        if (!priority)
            priority = 1;

        (*task) = (Task) {
            .func = func,
            .data = data ? data : task,
            .priority = priority,
        };
    }
    return task;
}

int CompareTasks(const void *pa, const void *pb) {
    const Task *a = pa, *b = pb;
    if (a->priority > b->priority)
        return -1;
    if (a->priority < b->priority)
        return 1;
    return 0;
}

void PruneTasks() {
    prune_pool(tasks, IsUsed);
}

void SortTasks() {
    sort_pool_used(tasks, CompareTasks);
}

void RunTasks() {
    pool_foreachused(tasks, RunTask);
}