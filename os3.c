 #include <stdio.h>
 #include <stdlib.h>
 int mutex = 1;
 int full = 0;
 int empty = 10;
 int buffer[10];
 int in = 0, out = 0;
 int wait(int s) {
    return --s;
 }
int signal(int s) {
    return ++s;
 }
void produce(int value) {
    mutex = wait(mutex);
    empty = wait(empty);
    buffer[in] = value;
    in = (in + 1) % 10;
    full = signal(full);
    mutex = signal(mutex);
 }
void consume() {
    mutex = wait(mutex);
    full = wait(full);
    int value = buffer[out];
    out = (out + 1) % 10;
    empty = signal(empty);
    mutex = signal(mutex);
    printf("The value consumed is : %d\n", value);
 }
int main() {
    int choice, value;
    while (1) {
        printf("\n1.Produce  2.Consume  3.Exit\n");
        printf("Enter your choice : ");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            if (empty == 0) {
                printf("Buffer is FULL! Cannot produce.\n");
            } else {
                printf("Enter the value : ");
                scanf("%d", &value);
                produce(value);
            }
            break;
        case 2:
            if (full == 0) {
                printf("Buffer is EMPTY! Cannot consume.\n");
            } else {
                consume();
            } break;
        case 3:
            printf("Exiting...\n");
            exit(0);
        default:
            printf("Invalid choice!\n");
        }
    }
    return 0;
 }

