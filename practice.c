#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    int p1[2], p2[2];
    char path[256], buf[1024];
    int n;
    pid_t pid;

    if(pipe(p1)==-1 || pipe(p2)==-1){
        perror("Pipe failed");
        exit(1);
    }

    pid=fork();
    if(pid<0){
        perror("fork failed");
        exit(1);
    }

    if(pid==0){
        //child
        close(p1[1]);
        close(p2[0]);
        n = read(p1[0], path, sizeof(path)-1);
        if(n<0) n=0;
        path[n] = '\0';

        FILE *fp = fopen(path, "r");
        if(fp==NULL){
            strcpy(buf, "ERROR: cannot open file");
            write(p2[1], buf, strlen(buf));
        }else{
            while((n=fread(buf, 1, sizeof(buf), fp))>0){
                write(p2[1], buf, n);
            }
            fclose(fp);
        }
        close(p1[0]);
        close(p2[1]);
        exit(0);
    }else{
        //parent
        close(p1[0]);
        close(p2[1]);

        printf("Enter file path:\n");
        scanf("%255s", path);
        write(p1[1], path, strlen(path)+1);
        close(p1[1]);

        while((n=read(p2[0], buf, sizeof(buf)))>0){
            write(1, buf, n);
        }
        close(p2[0]);
        wait(NULL);
    }
    return 0;
}