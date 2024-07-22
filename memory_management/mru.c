#include <stdio.h>
#include <stdlib.h>

void init();
int in_memory(int);
int mru();

int n, nor;
int* memory;
int* ref;
int* temp;
int counter = 0;

int main(int argc, char** argv)
{
    n = atoi(argv[1]);           // No of in memory frames
    nor = atoi(argv[2]);         // No of reference strings

    memory = calloc(n, sizeof(int));         // IN MEMORY ARRAY
    ref = calloc(nor, sizeof(int));          // REFERENCE STRING
    temp = calloc(n, sizeof(int));
    init();

    int page_fault = mru();

    printf("\n\nTotal page faults = %d\n", page_fault);

    free(memory);
    free(ref);
    free(temp);
    return 0;
}

int mru()
{
    int pf = 0;
    int victim = 0;

    for(int i = 0; i < nor; ++i) {
        printf("\nReferenced Page [%d] ->\t\t", ref[i]);

        if(in_memory(ref[i]) == -1) {

            ++pf;
            victim = select_victim(i);
            memory[victim] = ref[i];

            for(int j = 0; j < n; ++j)
                printf("%4d", memory[j]);
        }
        else {
            for(int j = 0; j < n; ++j) {
                if(memory[j] == ref[i]) {
                    counter += 2;
                    temp[j] = counter;
                }
            }
        }
    }

    return pf;
}

int select_victim(int index)
{
    for(int i = 0; i < n; ++i) {
        if(memory[i] == -1) {
            counter += 2;
            temp[i] = counter;
            return i;
        }
    }
    
    int max = select_max();
    counter += 2;
    temp[max] = counter;
    return max;
}

int select_max()
{
    int max = 0;
    for(int i = 1; i < n; ++i) {
        if(temp[i] > temp[max])
            max = i;
    }
    return max;
}

int in_memory(int page)
{
    for(int i = 0; i < n; ++i)
        if(memory[i] == page)
            return i;
    return (-1);
}

void init()
{
    printf("Enter reference strings : ");
    
    for(int i = 0; i < nor; ++i) {
        scanf("%d", &ref[i]);
    }

    for(int i = 0; i < n; ++i) {
        memory[i] = -1;
    }
}
