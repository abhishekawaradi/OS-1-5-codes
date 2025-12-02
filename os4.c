 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <fcntl.h>
 #include <sys/stat.h>
 #include <string.h>
int main() {
    char *fifo = "myfifo";
    char buffer[100];
    mkfifo(fifo, 0666);
    pid_t pid = fork();
    if (pid < 0) {
        printf("Fork failed!\n");
        return 1;
    }
    if (pid == 0) {
        int fd;
        char message[100];
        while (1) {
            fd = open(fifo, O_WRONLY);
            printf("\nWriter: Enter message (type 'exit' to stop): ");
            fgets(message, sizeof(message), stdin);
            write(fd, message, strlen(message) + 1);
            close(fd);
            if (strncmp(message, "exit", 4) == 0) {
                break;
            }
        }
    }
    else {
        int fd;
        while (1) {
            fd = open(fifo, O_RDONLY);
            read(fd, buffer, sizeof(buffer));
            close(fd);
            if (strncmp(buffer, "exit", 4) == 0) {
                printf("\nReader: Exit message received. Stopping...\n");
                break;
            }
            printf("Reader received: %s", buffer);
        }
    }
    unlink(fifo); 
    return 0;
 }

