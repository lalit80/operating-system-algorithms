#include <stdio.h>
#include <stdlib.h>

void init();
int in_memory(int);
int select_victim();
int opt();

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

    int page_fault = opt();

    printf("\n\nTotal page faults = %d\n", page_fault);

    free(memory);
    free(ref);
    free(temp);
    return 0;
}

int opt()
{
    int pf = 0;
    int victim = 0;
    int flag;
    int res;

    for(int i = 0; i < nor; ++i) {
        printf("\nReferenced Page [%d] ->\t\t", ref[i]);

        res = in_memory(ref[i]);
        if(res == -1) {
            flag = 1;
            for(int j = 0; j < n; ++j) {
                if(memory[j] == -1) {
                    ++pf;
                    flag = 0;
                    memory[j] = ref[i];
                    break;
                }
            }
            if(flag) {
                for(int k = 0; k < n; ++k) temp[k] = (nor + 1);
                for(int j = 0; j < n; ++j) {

                    for(int k = i + 1; k < nor; ++k) {
                        if(ref[k] == memory[j]) {
                            temp[j] = k;
                            break;
                        }
                    }
                }
                victim = select_victim();
                memory[victim] = ref[i];
                ++pf;
            }
        }

        for(int j = 0; j < n; ++j)
                printf("%4d", memory[j]);
    }

    return pf;
}

int select_victim()
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
        temp[i] = 0;
    }
}
