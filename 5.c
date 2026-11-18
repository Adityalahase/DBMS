// 7. Implement the C program for Deadlock Avoidance Algorithm:
// Bankers Algorithm.

/* Sample input:
   Processes = 5, Resources = 3
   Allocation: 0 1 0 / 2 0 0 / 3 0 2 / 2 1 1 / 0 0 2
   Max:        7 5 3 / 3 2 2 / 9 0 2 / 2 2 2 / 4 3 3
   Available:  3 3 2
   Safe sequence: P1 P3 P4 P0 P2 
*/


#include <stdio.h>

int main() {
    int n, m;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    int alloc[n][m], max[n][m], need[n][m];
    int avail[m], finish[n], safe[n];

    printf("Enter Allocation Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("Enter Maximum Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter Available Resources:\n");
    for (int j = 0; j < m; j++) {
        scanf("%d", &avail[j]);
    }

    // Calculate Need Matrix
    for (int i = 0; i < n; i++) {
        finish[i] = 0;
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Find Safe Sequence
    int count = 0;

    while (count < n) {
        int found = 0;

        for (int i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int j;

                for (j = 0; j < m; j++) {
                    if (need[i][j] > avail[j])
                        break;
                }

                if (j == m) {
                    for (int k = 0; k < m; k++) {
                        avail[k] += alloc[i][k];
                    }

                    safe[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (found == 0)
            break;
    }

    if (count == n) {
        printf("\nSystem is in SAFE state.\n");
        printf("Safe Sequence: ");

        for (int i = 0; i < n; i++) {
            printf("P%d", safe[i]);
            if (i < n - 1)
                printf(" -> ");
        }
        printf("\n");
    } else {
        printf("\nSystem is in UNSAFE state.\n");
    }

    return 0;
}