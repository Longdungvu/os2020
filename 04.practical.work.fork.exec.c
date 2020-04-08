#include <stdio.h>
#include <unistd.h>

int main() {
 int pid = fork();

 if(pid != 0) {
     wait(NULL);
     pid = fork();

     if (pid!= 0) {
         wait(NULL);
     } else {
         printf("I am the second child\n");
         char *arg[] = {"/bin/ps", "-ef", NULL};
         execvp(arg[0],arg);
     }

 } else {
     printf("I am the first child\n");
     char *arg[]={"/usr/bin/free","-h",NULL};
     execvp(arg[0],arg);
 }
}
