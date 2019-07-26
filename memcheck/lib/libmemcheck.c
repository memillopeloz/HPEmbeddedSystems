#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>
#include <sys/types.h>

int count = 0;
int mCount = 0;
int fCount = 0;

char counts[2] = {0, 0};

static void* (*real_malloc)(size_t)=NULL;
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

void macarena(int a)
{
	printf("macarena libmemcheck\n");
}

pid_t getpid(void)
{ //for returning mCount
    //pid_t (*orig_getpid)(void) = dlsym(RTLD_NEXT, "getpid");
    printf("getpid libmemcheck\n");
    //return mCount;
    return ++count; //sirve a cachete
}


int atoi(const char* nptr)
{ // For returning fCount
	printf("atoi libmemcheck\n");
	nptr = counts;
	return fCount;
}
/*
void* malloc(size_t size)
{
	if(real_malloc == NULL) {
        mtrace_init();
    }
	mCount++;
	++counts[0];

	return real_malloc(size);

	//void* (*orig_malloc)(size_t size) = dlsym(RTLD_NEXT, "malloc");
	//return orig_malloc(size);
}
*/
void free(void* ptr)
{
	if(real_free == NULL) {
        ftrace_init();
    }
	fCount++;
	++counts[1];
	real_free(ptr);
	//void (*orig_free)(void* ptr) = dlsym(RTLD_NEXT, "free");
	//orig_free(ptr);
}