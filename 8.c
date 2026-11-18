// Implement the C program for Disk Scheduling Algorithms: SSTF,
// SCAN, C-Look considering the initial head position moving away
// from the spindle.

//shortest seek time first : disk head selects the request that is closest/nearest to its current position
//ex: request queue: 82,170,43,140,24,16, 190
// head = 50, disk size = 200.

#include <stdio.h>
#include <stdlib.h>

int main(){
    int n, head, disk, temp;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    int req[n], done[n];

    printf("Enter requests: ");
    for (int i = 0; i < n; i++){
        scanf("%d", &req[i]);
        done[i] = 0;
    }

    printf("Enter head position: ");
    scanf("%d", &head);

    printf("Enter disk size (e.g. 200): ");
    scanf("%d", &disk);

    // ---------- SSTF ----------
    int total = 0, cur = head;

    printf("\nSSTF Order: %d", head);

    for (int c = 0; c < n; c++){
        int min = __INT_MAX__, idx = -1;

        for (int i = 0; i < n; i++){
            if (!done[i]){
                int d = abs(req[i] - cur);

                if (d < min){
                    min = d;
                    idx = i;
                }
            }
        }

        done[idx] = 1;
        total += min;
        cur = req[idx];

        printf(" -> %d", cur);
    }

    printf("\nSSTF Total Head Movement = %d\n", total);


    // ---------- SORT REQUESTS(bubble) ----------
    for (int i = 0; i < n - 1; i++){
        for (int j = 0; j < n - i - 1; j++){
            if (req[j] > req[j + 1]){
                temp = req[j];
                req[j] = req[j + 1];
                req[j + 1] = temp;
            }
        }
    }

    // Find first request greater than or equal to head
    int p = 0;

    while (p < n && req[p] < head){
        p++;
    }

    // ---------- SCAN ----------
    total = 0;
    cur = head;

    printf("\nSCAN Order: %d", head);

    // Move towards higher cylinders
    for (int i = p; i < n; i++){
        total += abs(req[i] - cur);
        cur = req[i];

        printf(" -> %d", cur);
    }

    // Reach the last cylinder
    if (cur != disk - 1){
        total += abs((disk - 1) - cur);
        cur = disk - 1;

        printf(" -> %d", cur);
    }

    // Reverse direction and service remaining requests
    for (int i = p - 1; i >= 0; i--){
        total += abs(cur - req[i]);
        cur = req[i];

        printf(" -> %d", cur);
    }

    printf("\nSCAN Total Head Movement = %d\n", total);


    // ---------- C-LOOK ----------
    total = 0;
    cur = head;

    printf("\nC-LOOK Order: %d", head);

    // Move towards higher cylinders
    for (int i = p; i < n; i++){
        total += abs(req[i] - cur);
        cur = req[i];

        printf(" -> %d", cur);
    }

    // Jump to the lowest/first pending request
    // Service remaining requests in ascending order
    for (int i = 0; i < p; i++){
        total += abs(req[i] - cur);
        cur = req[i];

        printf(" -> %d", cur);
    }

    printf("\nC-LOOK Total Head Movement = %d\n", total);

    return 0;
}