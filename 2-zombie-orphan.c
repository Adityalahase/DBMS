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

int main()
{
    int choice;

    printf("1. Zombie process\n");
    printf("2. Orphan process\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice != 1 && choice != 2)
    {
        printf("Invalid choice\n");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        exit(1);
    }

    if (choice == 1)
    {
        if (pid == 0)
        {
            printf("[Child] PID = %d, exiting now\n", getpid());
            exit(0);
        }
        else
        {
            printf("[Parent] PID = %d\n", getpid());
            printf("Child is now a ZOMBIE. Check using ps -l\n");

            sleep(30);

            wait(NULL);

            printf("[Parent] Zombie removed using wait().\n");
        }
    }
    else
    {
        if (pid == 0)
        {
            printf("[Child] PID = %d, Parent PID = %d\n", getpid(), getppid());

            sleep(10);

            printf("[Child] New Parent PID = %d\n", getppid());
            printf("[Child] I am now an ORPHAN.\n");
        }
        else
        {
            printf("[Parent] PID = %d exiting immediately\n", getpid());
            exit(0);
        }
    }

    return 0;
}