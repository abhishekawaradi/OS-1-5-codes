 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <sys/types.h>
 #include <sys/wait.h>
 
int main() {
    pid_t pid;
    int i;
 
    pid = fork();   
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    if (pid == 0) {
        printf("It is the child process and pid is %d\n", getpid());
        for (i = 0; i < 8; i++) {
            printf("%d\n", i);
        }
        exit(0);  
    }
    else {
        printf("It is the parent process and pid is %d\n", getpid());
        wait(NULL);   
        printf("Child is reaped\n");
    }
    return 0;
 }

