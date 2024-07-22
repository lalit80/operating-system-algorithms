#include <stdio.h>
#include <stdlib.h>

void init(int*, int, int*, int);
int in_memory(int*, int, int);
int fifo(int*, int, int*, int);

int main(int argc, char** argv)
{
    int n = atoi(argv[1]);          // No of in memory frames
    int nf = atoi(argv[2]);         // No of reference strings

    int* memory = calloc(n, sizeof(int));        // IN MEMORY ARRAY
    int* ref = calloc(nf, sizeof(int));          // REFERENCE STRING
    init(memory, n, ref, nf);

    int page_fault = fifo(memory, n, ref, nf);

    printf("\n\nTotal page faults = %d\n", page_fault);

    free(memory);
    free(ref);
    return 0;
}

int fifo(int* memory, int n, int* ref, int nf)
{
    int pf = 0;
    int victim = 0;

    for(int i = 0; i < nf; ++i) {
        printf("\nReferenced Page [%d] ->\t\t", ref[i]);
        if(!in_memory(memory, n, ref[i])) {
            ++pf;
            memory[victim] = ref[i];
            victim = (victim + 1) % n;
            for(int j = 0; j < n; ++j)
                printf("%4d", memory[j]);
        }
    }

    return pf;
}

int in_memory(int* memory, int n, int page)
{
    for(int i = 0; i < n; ++i)
        if(memory[i] == page)
            return 1;
    return 0;
}

void init(int* memory, int n, int* ref, int nf)
{
    printf("Enter reference strings : ");
    
    for(int i = 0; i < nf; ++i) {
        scanf("%d", &ref[i]);
    }

    for(int i = 0; i < n; ++i) {
        memory[i] = -1;
    }
}
