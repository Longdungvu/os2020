#include <stdbool.h>
#include <stdio.h>
#include <pthread.h>


  bool checkprime (int n) {
    for (int i =2; i < sqrt(n); i++) {
      if(n%i ==0) {
        return false;
      }
    }
    return true;
  }

  void *Prime(void *param) {
    for (int i = 2; i < 1000000; i++) {
      if (checkprime(i)) {
        printf("Prime: %d\n",i);
      }
    }
  }

  void *Fibonancci(void *param) {
    int f1=1, f2=2, f3;
    while (f2 <= 1000000) {
        printf("Fibonancci: %d\n",f2);
      f3 = f1 + f2;
      f1 = f2;
      f2 = f3;
    }
  }

  int main() {
    // create a background thread to execute threadFunction
	   pthread_t tid_1;
	   pthread_t tid_2;

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
  }
