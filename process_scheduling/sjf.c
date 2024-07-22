#include <stdio.h>
#include <stdlib.h>

typedef struct _Process {
    char name[10];
    int at, bt, wt, ft, tat;
} Process;

Process* create_array(int);
int cp_for_bt(const void*, const void*);
int cp_for_at(const void*, const void*);
void sjf(Process*, int);
void print(Process*, int);

int main(int argc, char** argv)
{
    int n = atoi(argv[1]);

    Process* p_arr = create_array(n);

    sjf(p_arr, n);
    print(p_arr, n);
    return (0);
}

void sjf(Process* p_arr, int n)
{
    p_arr[0].wt = 0;
    p_arr[0].ft = p_arr[0].at + p_arr[0].bt;
    p_arr[0].tat = p_arr[0].ft - p_arr[0].at;

    qsort((p_arr + 1), n, sizeof(Process), cp_for_bt);

    for(int i = 1; i < n; ++i) {
        if((p_arr[i - 1].ft - p_arr[i].at) < 0) {
            p_arr[i].wt = 0;
            p_arr[i].ft = p_arr[i - 1].ft + p_arr[i].bt + (abs(p_arr[i - 1].ft - p_arr[i].at));
        }
        else {
            p_arr[i].wt = p_arr[i - 1].ft - p_arr[i].at;
            p_arr[i].ft = p_arr[i - 1].ft + p_arr[i].bt;
        }
        p_arr[i].tat = p_arr[i].ft - p_arr[i].at;
    }
}

Process* create_array(int n)
{
    Process* p_arr = calloc(n, sizeof(Process));
    
    printf("Enter Process Name at bt for %d processes :\n", n);
    for(int i = 0; i < n; ++i) {
        scanf("%s%d%d", p_arr[i].name, &p_arr[i].at, &p_arr[i].bt);
    }
    qsort(p_arr, n, sizeof(Process), cp_for_at);
    return p_arr;
}

void print(Process* p_arr, int n)
{
    int avg_wt = 0, avg_tat = 0;
    puts("Name\tAt\tBt\tWt\tFt\tTat");
    for(int i = 0; i < n; ++i) {
        avg_wt += p_arr[i].wt;
        avg_tat += p_arr[i].tat;

        printf("%s\t%d\t%d\t%d\t%d\t%d\n", p_arr[i].name, 
                            p_arr[i].at, p_arr[i].bt, p_arr[i].wt,
                            p_arr[i].ft, p_arr[i].tat);
    }
    printf("Average Wt = %d\nAverage Tat = %d", avg_wt/n, avg_tat/n);
}

int cp_for_bt(const void* a, const void* b)
{
    const Process* pa = a;
    const Process* pb = b;
    return (pa->bt) - (pb->bt);
}

int cp_for_at(const void* a, const void* b)
{
    const Process* pa = a;
    const Process* pb = b;
    return (pa->at) - (pb->at);
}
