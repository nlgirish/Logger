/* A simple code for redirecting logs in the project
   to a log file with option of enabling various trace
   level in the project */

//Compilation command
//gcc log.c -lpthread
//pass any value between 1 to 5 while running

#include<stdio.h>
#include<errno.h>
#include <pthread.h>

typedef struct mutex_lock
{
    pthread_mutex_t mutexId;

} mutex_lock;

mutex_lock* mutex_lock_create()
{
    mutex_lock* mutex_instance = (mutex_lock*)malloc(sizeof(mutex_lock));
    if(mutex_instance == NULL)	
    {
    	printf("%s:%d - Malloc failed\n", __func__, __LINE__);
	    return NULL;
    }
    pthread_mutexattr_t attr;
    if(pthread_mutexattr_init(&attr)!=0)
    {
        printf("Error initializing thread\n");
    }
    if(pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE)!=0)
    {
        printf("Error setting type for the mutex object\n");
    }
    if(pthread_mutex_init(&mutex_instance->mutexId, &attr)!=0)
    {
        printf("Error initializing thread\n");
    }
    if(pthread_mutexattr_destroy(&attr)!=0) 
    {
        printf("Error destroying thread\n");
    }
    return mutex_instance;
}   
    
int mutex_lock_lock(mutex_lock* mutex_instance)
{   
    return pthread_mutex_lock(&mutex_instance->mutexId);
}

int mutex_lock_try_lock(mutex_lock* mutex_instance)
{
    return pthread_mutex_trylock(&mutex_instance->mutexId);
}

int mutex_lock_unlock(mutex_lock* mutex_instance)
{
    return pthread_mutex_unlock(&mutex_instance->mutexId); 
}   
    
void mutex_lock_destroy(mutex_lock* mutex_instance)
{   
    if(pthread_mutex_destroy(&mutex_instance->mutexId)!=0)
    {
        printf("Error initializing thread\n");
    }
    free(mutex_instance);
    
    return;
}

#define LOG_FATAL    (1)
#define LOG_ERROR    (2)
#define LOG_WARN     (3)
#define LOG_INFO     (4)
#define LOG_DEBUG    (5)

char* enum2String(int level)
{
    switch(level)
    {
        case 1:
            return "[FATAL]";
        case 2:
            return "[ERROR]";
        case 3:
            return "[WARN] ";
        case 4:
            return "[INFO] ";
        case 5:
        default:
            return "[DEBUG]";
    }

}

#define LOG(level, ...) do {  \
                            if (level <= debug_level) { \
                            mutex_lock_lock(log_lock); \
                            fprintf(dbgstream,"%s %s:%d ", enum2String(level), __func__, __LINE__); \
                            fprintf(dbgstream, __VA_ARGS__); \
                            fprintf(dbgstream, "\n"); \
                            fflush(dbgstream); \
                            mutex_lock_unlock(log_lock);\
                            } \
                        } while (0)
int  debug_level = 5;
mutex_lock* log_lock = NULL;

int main(int argc, char *argv[])
{
    if(argc >= 2)
        debug_level = atoi(argv[1]);
    FILE *dbgstream  = fopen("test.log", "w");
    log_lock = mutex_lock_create();
    LOG(LOG_FATAL, "TEST log");
    LOG(LOG_INFO, "TEST log");
    LOG(LOG_DEBUG, "TEST log");
    LOG(LOG_WARN, "TEST log");
    LOG(LOG_ERROR, "TEST log");
    LOG(LOG_INFO, "TEST log");
    LOG(LOG_DEBUG, "TEST log");
    LOG(LOG_WARN, "TEST log");
    LOG(LOG_ERROR, "TEST log");
    LOG(LOG_INFO, "TEST log");
    LOG(LOG_DEBUG, "TEST log");
    LOG(LOG_WARN, "TEST log");
    LOG(LOG_ERROR, "TEST log");
    LOG(LOG_INFO, "TEST log");
    LOG(LOG_DEBUG, "TEST log");
    LOG(LOG_WARN, "TEST log");
    LOG(LOG_ERROR, "TEST log");
    LOG(LOG_INFO, "TEST log");
    LOG(LOG_DEBUG, "TEST log");
    LOG(LOG_WARN, "TEST log");

    return 1;
}

void log_init();

void log_exit();
