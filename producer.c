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
   index = sem_open("/index", O_CREAT | O_RDWR, 0644, 1);
   lock = sem_open("/lock", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP, 1);
   sem_post(index);
   sem_post(lock);
   pthread_t first;
   pthread_create(&first, NULL, thread, NULL);
   pthread_join(first, NULL)
   
   pthread_destroy(&first);
   sem_destroy(&lock);
   sem_destroy(&index);
   
   return 0;
}

