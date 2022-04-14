#include <pthread.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

sem_t *lock;
sem_t *index;

void* thread(void* arg) {
//Thread start
   printf("Start\n");
   for(;;) {
      sem_wait(lock);
      sem_post(index);
      printf("End\n");
      //Thread exit
      sem_post(lock);
  }
}

int main(int argc, char** argv) {
   index = sem_open("/index", O_RDWR);
   lock = sem_open("/lock", O_RDWR);
   pthread_t sec;
   pthread_create(&sec, NULL, thread, NULL);
   pthread_join(sec, NULL)
   
   pthread_destroy(&sec);
   sem_destroy(&lock);
   sem_destroy(&index);
   
   return 0;
}

