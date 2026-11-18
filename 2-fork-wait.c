// Process control system calls: The demonstration of FORK and
// WAIT system calls along with zombie and orphan states.
// Implement the C program in which main program accepts the
// integers to be sorted. Main program uses the FORK system call to
// create a new process called a child process. Parent process sorts the
// integers using sorting algorithm and waits for child process using
// WAIT system call to sort the integers using any sorting algorithm.
// Demonstrate zombie and orphan states.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void bubbleSort(int a[], int n) {
    int i, j, t;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (a[j] > a[j + 1]) {
                t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
            }
}

void display(int a[], int n) {
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

int main() {
    int n, i, status;
    printf("Enter number of integers: ");
    scanf("%d", &n);

    int a[n];
    printf("Enter %d integers: ", n);
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        printf("\n[Child] PID = %d, Parent PID = %d\n", getpid(), getppid());
        bubbleSort(a, n);
        printf("[Child] Sorted using bubble sort: ");
        display(a, n);
        exit(0);
    } else {
        printf("\n[Parent] PID = %d, Child PID = %d\n", getpid(), pid);
        bubbleSort(a, n);
        printf("[Parent] Sorted using bubble sort: ");
        display(a, n);
        wait(&status);
        printf("[Parent] Child has finished. wait() returned.\n");
    }
    return 0;
}