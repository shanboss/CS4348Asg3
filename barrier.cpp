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
      sem_wait(&mutex);
      count++;
      if(count == n){
         sem_wait(&gate2);
         sem_post(&gate1);
      }
      sem_post(&mutex);

      sem_wait(&gate1);
      sem_post(&gate1);

      sem_wait(&mutex);
      count--;

      if(count == 0){
         sem_wait(&gate1);
         sem_post(&gate2);
      }
      sem_post(&mutex);

      sem_wait(&gate2);
      sem_post(&gate2);
      return;
   }

}
