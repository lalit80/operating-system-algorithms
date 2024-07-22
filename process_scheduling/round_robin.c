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
int execute(Process*, int, int, int);
void rr(Process*, int, int);

int main(int argc, char** argv)
{
    int n = atoi(argv[1]);
    int tq = atoi(argv[2]);     // time quantum

    Process* p_arr = create_array(n);

    rr(p_arr, n, tq);
    return (0);
}

void rr(Process* p_arr, int n, int tq)
{
    int total_burst = 0;
    int te = 0;             // time elapsed

    for(int i = 0; i < n; ++i) { total_burst += p_arr[i].bt; }

    puts("Name\tBt\tTime Remaining\t Time Elapsed");

    while(total_burst > 0) {

        for(int i = 0; i < n; ++i) {
            int tr = execute(p_arr, i, te, tq);
            if(tr) {
                total_burst -= tr;
                te += tr;
                printf("%s\t%d\t\t%d\t\t%d\n", p_arr[i].name, p_arr[i].bt, p_arr[i].time_remaining, te);
            }
        }
    }
}

int execute(Process* p_arr, int index, int arrived, int tq)
{
    int res = 0;

    if(is_executable(p_arr, index, arrived)) {
        if(p_arr[index].time_remaining >= tq) {
            p_arr[index].time_remaining -= tq;
            res = tq;
            return res;
        }
        else {
            res = p_arr[index].time_remaining;
            p_arr[index].time_remaining = 0;
            return res;
        }
    }
    return res;
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
