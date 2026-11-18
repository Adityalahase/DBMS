// 8. Write a C program to demonstrate full-duplex communication
// between two independent processes using FIFOs (named pipes),
// where the first process sends sentences to the second process,
// which counts the number of characters, words, and lines, stores
// the results in a text file, and sends the file contents back to the
// first process for display

/* ================= 9-fifo1.c (Process 1) ================= */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define FIFO1 "fifo1"
#define FIFO2 "fifo2"
#define SIZE 1024

int main() {
    char line[SIZE], result[SIZE];
    int fd1, fd2, n;

    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    while (1) {
        printf("Enter a sentence (or exit to quit): ");
        fgets(line, sizeof(line), stdin);

        line[strcspn(line, "\n")] = '\0';

        fd1 = open(FIFO1, O_WRONLY);
        write(fd1, line, strlen(line) + 1);
        close(fd1);

        if (strcmp(line, "exit") == 0)
            break;

        fd2 = open(FIFO2, O_RDONLY);
        n = read(fd2, result, SIZE - 1);

        if (n < 0)
            n = 0;

        result[n] = '\0';
        close(fd2);

        printf("Result received: %s\n\n", result);
    }

    return 0;
}
