#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>
#include <sys/types.h>

int mCount = 0;
int fCount = 0;

static void* (*real_malloc)(size_t size)=NULL;
static void (*real_free)(void* ptr)=NULL;

static void mtrace_init(void)
{
    real_malloc = dlsym(RTLD_NEXT, "malloc");
    if (NULL == real_malloc) {
        fprintf(stderr, "Error in malloc 'dlsym': %s\n", dlerror());
    }
}

static void ftrace_init(void)
{
    real_free = dlsym(RTLD_NEXT, "free");
    if (NULL == real_free) {
        fprintf(stderr, "Error in free 'dlsym': %s\n", dlerror());
    }
}

void* malloc(size_t size)
{
	++mCount;
	if(real_malloc == NULL) {
        mtrace_init();
    }
	return real_malloc(size);
}

void free(void* ptr)
{
	++fCount;
	if(real_free == NULL) {
        ftrace_init();
    }
	real_free(ptr);
}


__attribute__((destructor))
void PrintStats()
{
    printf("\nAnalysis finished!\n"
    "Memory allocations: %d \n"
    "Memory frees: %d \n"
    "Total memory leaks found: %d \n", mCount, fCount, mCount-fCount);
}