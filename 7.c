// 9. Full duplex communication between parent and child processes.
// Parent process writes a pathname of a file (the contents of the
// file are desired) on one pipe to be read by child process and
// child process writes the contents of the file on second pipe to be
// read by parent process and displays on standard output.

// to run this program first create a text file sample.txt ( hello world from linux) in the same folder 
// then gcc 9.c
// ./a.out
// Enter file path: sample.txt
// hello world from linux

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int p1[2], p2[2];      /* p1: parent -> child, p2: child -> parent */
    char path[256], buf[1024];
    int n;
    pid_t pid;

    if (pipe(p1) == -1 || pipe(p2) == -1) {
        perror("pipe failed");
        exit(1);
    }

    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        /* ---------- CHILD ---------- */
        close(p1[1]);
        close(p2[0]);

        n = read(p1[0], path, sizeof(path) - 1);
        if (n < 0) n = 0;
        path[n] = '\0';

        FILE *fp = fopen(path, "r");
        if (fp == NULL) {
            strcpy(buf, "Error: cannot open file\n");
            write(p2[1], buf, strlen(buf));
        } else {
            while ((n = fread(buf, 1, sizeof(buf), fp)) > 0)
                write(p2[1], buf, n);
            fclose(fp);
        }

        close(p1[0]);
        close(p2[1]);
        exit(0);
    } else {
        /* ---------- PARENT ---------- */
        close(p1[0]);
        close(p2[1]);

        printf("Enter file path: ");
        scanf("%255s", path);
        write(p1[1], path, strlen(path) + 1);
        close(p1[1]);

        printf("\nFile contents:\n");
        while ((n = read(p2[0], buf, sizeof(buf))) > 0)
            write(1, buf, n);

        close(p2[0]);
        wait(NULL);
    }
    return 0;
}