#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
void* func(void* p) {
   printf("From the function, the thread id = %lu\n", pthread_self()); //get current thread id
      pthread_exit(NULL);
   return NULL;
}
int main() {
   pthread_t thread; // declare thread
   pthread_t thread2; // declare thread
   pthread_create(&thread, NULL, func, NULL);
   pthread_create(&thread2, NULL, func, NULL);
   printf("From the main function, the thread id = %lu\n", thread);
   printf("From the main function, the thread id = %lu\n", thread2);
   pthread_join(thread, NULL); //join with main thread
   pthread_join(thread2, NULL); //join with main thread
   return 0;
}