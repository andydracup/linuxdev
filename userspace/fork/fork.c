#include <sys/types.h> 
#include <stdio.h>   
#include <stdlib.h> 
#include <unistd.h>
#include <errno.h> 
#include <string.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
    int i;
    int ret = 0;
    pid_t pid;

    for (i = 0; i < argc; i++) {
        printf("arg[%d] is %s\n", i, argv[i]);
    }

    pid = fork();
    if (pid < 0) {
        ret = -1;
        goto exit;
    }

    // Child 
    if (pid == 0) {
        for (i = 0; i < 5; i++) {
            sleep(1);
            printf("%d\n", i);
        }
        printf("child: exit\n");
        exit(EXIT_SUCCESS);
    }
    // Parent
    else {
        int status;
        pid = wait(&status);
        if (pid > 0) {
            printf("parent: child status is %d\n", WEXITSTATUS(status));
        }
    }
    
exit:
    return ret;
}

