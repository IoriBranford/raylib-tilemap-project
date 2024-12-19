#include <engine/tasks.h>
#include <util.h>

pool_typedef(Task, TaskPool)
pool_ctor(Task, TaskPool, NewTaskPool)

static TaskPool *tasks;

#define IsActive(task) (task->func)

void InitEmptyTask(Task *task) {
    *task = (Task){
        .priority = 0,
        .data = NULL,
        .func = NULL
    };
}

void RunTask(Task *task) {
    if (task->func)
        task->func(task);
}

void EndTask(Task *task) {
    task->func = NULL;
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
    const Task *a = pa, *b = pb;
    return a->priority - b->priority;
}

void PruneTasks() {
    prune_pool(tasks, IsActive);
}

void SortTasks() {
    sort_pool_active(tasks, CompareTasks);
}

void RunTasks() {
    pool_foreachactive(tasks, RunTask);
}

void UpdateTasks() {
    pool_foreachactive(tasks, RunTask);
    prune_pool(tasks, IsActive);
    sort_pool_active(tasks, CompareTasks);
}