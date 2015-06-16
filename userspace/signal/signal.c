#include <sys/types.h> 
#include <stdio.h>   
#include <stdlib.h> 
#include <unistd.h>
#include <errno.h> 
#include <string.h>
#include <signal.h>

static void sigHandler(int);

int
main(int argc, char *argv[])
{
    int i;
    int ret = 0;

    for (i = 0; i < argc; i++) {
        printf("arg[%d] is %s\n", i, argv[i]);
    }

    if (signal(SIGINT, sigHandler) == SIG_ERR) {
        ret = -1;
        goto exit;
    }

    for (i = 0;;i++) {
        pause();
    }
exit:
    return ret;
}

static void
sigHandler(int sig)
{
    printf("SIGINT\n");
    exit(EXIT_SUCCESS);
}
