// 8. Write a C program to demonstrate full-duplex communication
// between two independent processes using FIFOs (named pipes),
// where the first process sends sentences to the second process,
// which counts the number of characters, words, and lines, stores
// the results in a text file, and sends the file contents back to the
// first process for display

// first run in ter 1
// gcc fifo1.c
//./a.out

// then ter 2
// gcc fifo2.c
//./a.out

//then we get output in teminrl 1

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
    char text[SIZE], result[SIZE];
    int fd1, fd2, n;
    int chars, words, lines, inWord;

    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    while (1) {
        fd1 = open(FIFO1, O_RDONLY);
        n = read(fd1, text, SIZE - 1);

        if (n < 0)
            n = 0;

        text[n] = '\0';
        close(fd1);

        if (strcmp(text, "exit") == 0)
            break;

        chars = words = lines = inWord = 0;

        for (int i = 0; text[i] != '\0'; i++) {
            chars++;

            if (text[i] == '\n')
                lines++;

            if (text[i] == ' ' || text[i] == '\t' ||
                text[i] == '\n') {
                inWord = 0;
            }
            else if (!inWord) {
                words++;
                inWord = 1;
            }
        }

        if (chars > 0)
            lines = 1;

        sprintf(result,
                "Characters: %d, Words: %d, Lines: %d",
                chars, words, lines);

        fd2 = open(FIFO2, O_WRONLY);
        write(fd2, result, strlen(result) + 1);
        close(fd2);
    }

    return 0;
}
