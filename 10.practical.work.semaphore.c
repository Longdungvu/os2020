#include <stdbool.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include "math.h"

  int s = 1;
  sem_t x ;
  void wait() {
    while (s <= 0);
    s--;
  }

  void signal() {
    s++;
  }

  bool checkprime (int n) {
    for (int i =2; i < sqrt(n); i++) {
      if(n%i ==0) {
        return false;
      }
    }
    return true;
  }

  void *Prime(void *param) {

    wait();

    for (int i = 2; i < 1000000; i++) {
      if (checkprime(i)) {
        printf("Prime: %d\n",i);
      }
    }

    signal();

  }

  void *Fibonancci(void *param) {

    wait();

    int f1=1, f2=2, f3;
    while (f2 <= 1000000) {
        printf("Fibonancci: %d\n",f2);
      f3 = f1 + f2;
      f1 = f2;
      f2 = f3;
    }

    signal();

  }


  void *PrimeX2(void *param) {

    sem_wait(&x);

    for (int i = 2; i < 1000000; i++) {
      if (checkprime(i)) {
        printf("Prime: %d\n",i);
      }
    }

    sem_post(&x);

  }

  void *FibonancciX2(void *param) {

    sem_wait(&x);

    int f1=1, f2=2, f3;
    while (f2 <= 1000000) {
        printf("Fibonancci: %d\n",f2);
      f3 = f1 + f2;
      f1 = f2;
      f2 = f3;
    }

    sem_post(&x);

  }

  int main() {
    // create a background thread to execute threadFunction
	   pthread_t tid_1;
	   pthread_t tid_2;
	   pthread_t tid_3;
	   pthread_t tid_4;

     pthread_create(
       &tid_1,
       NULL,
       Prime,
       NULL
     );


     pthread_create(
       &tid_2,
       NULL,
       Fibonancci,
       NULL
     );

     pthread_join(tid_1, NULL);
     pthread_join(tid_2, NULL);

     sem_init(&x,0,1);

     pthread_create(
       &tid_3,
       NULL,
       PrimeX2,
       NULL
     );

     pthread_create(
       &tid_4,
       NULL,
       FibonancciX2,
       NULL
     );

     pthread_join(tid_3, NULL);
     pthread_join(tid_4, NULL);

     sem_destroy(&x);
  }
