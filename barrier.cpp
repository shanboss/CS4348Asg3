#include "barrier.h"
#include <semaphore.h>

namespace synchronization
{
   
   barrier::barrier( int numberOfThreads ) {
      // Write your code here
      sem_init(&mutex, 0, 1);
      sem_init(&gate1, 0, 0);
      sem_init(&gate2, 0, 1);
      count = 0;
      n = numberOfThreads;
      return;
   }

   barrier::~barrier( ) {
      sem_destroy(&mutex);
      sem_destroy(&gate1);
      sem_destroy(&gate2);
      // Write your code here

      return;
   }

   void barrier::arriveAndWait( void ) {
      // Write your code here
      // mutex for critical section where count is incremented for each thread
      sem_wait(&mutex);
      count++;
      // if last thread, down gate2, and up gate1. this makes gate2 unavailable for the earlier threads so no thread can
      // lap all the others, and then makes gate1 available for them to progress to second turnstile
      if(count == n){
         sem_wait(&gate2);
         sem_post(&gate1);
      }
      sem_post(&mutex);

      // wait at gate1, and then open it for the thread behind them.
      sem_wait(&gate1);
      sem_post(&gate1);

      // critical section, count is decremented by each thread
      sem_wait(&mutex);
      count--;

      // if last thread has reached, make gate1 unavailable, and open gate2
      if(count == 0){
         sem_wait(&gate1);
         sem_post(&gate2);
      }
      sem_post(&mutex);

      // wait at gate2, then open it for the thread behind
      sem_wait(&gate2);
      sem_post(&gate2);
      return;
   }

}
