#include <stdio.h>
#include <stdlib.h>

typedef struct _Process {
    char name[10];
    int at, bt, wt, ft, tat;
    int time_remaining;
} Process;

Process* create_array(int);
int cp_for_at(const void*, const void*);
int is_executable(Process*, int, int);
int select_min(Process*, int, int);
void sjf(Process*, int);

//  Preemptive Scheduling

int main(int argc, char** argv)
{
    int n = atoi(argv[1]);

    Process* p_arr = create_array(n);

    sjf(p_arr, n);
    return (0);
}

void sjf(Process* p_arr, int n)
{
    int total_burst = 0;
    int min_index;

    for(int i = 0; i < n; ++i) { total_burst += p_arr[i].bt; }

    puts("Name\tBt\tTime Remaining\t Time Elapsed");

    for(int i = 0; i < total_burst; ++i) {
        min_index = select_min(p_arr, n, i);
        --p_arr[min_index].time_remaining;
        printf("%s\t%d\t\t%d\t\t%d\n", p_arr[min_index].name, p_arr[min_index].bt, p_arr[min_index].time_remaining, (i + 1));
    }
}

int select_min(Process* p_arr, int n, int arrived)
{
    int min = 0;
    for(int i = 0; i < n; ++i) {
        if(is_executable(p_arr, i, arrived)) {
            min = i;
            break;
        }
    }

    for(int i = 0; i < n; ++i) {
        if(is_executable(p_arr, i, arrived)) {
            if((p_arr[i].time_remaining < p_arr[min].time_remaining)) {
                min = i;
            }
        }
    }
    return min;
}

int is_executable(Process* p_arr, int i, int arrived)
{
    if((p_arr[i].at <= arrived) && (p_arr[i].time_remaining > 0))
        return 1;
    return 0;
}

Process* create_array(int n)
{
    Process* p_arr = calloc(n, sizeof(Process));
    
    printf("Enter Process Name at bt for %d processes :\n", n);
    for(int i = 0; i < n; ++i) {
        scanf("%s%d%d", p_arr[i].name, &p_arr[i].at, &p_arr[i].bt);
        p_arr[i].time_remaining = p_arr[i].bt;
    }
    qsort(p_arr, n, sizeof(Process), cp_for_at);
    return p_arr;
}

int cp_for_at(const void* a, const void* b)
{
    const Process* pa = a;
    const Process* pb = b;
    return (pa->at) - (pb->at);
}
