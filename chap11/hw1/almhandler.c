#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void (*mysignal(int signo, void (*handler)(int)))(int);
void alarmHandler(int signo);

int main()
{
    mysignal(SIGALRM, alarmHandler);
    alarm(5);

    short i = 0;
    while (1) {
        sleep(1);
        i++;
        printf("%d second\n", i);
    }

    return 0;
}

void alarmHandler(int signo)
{
    printf("Wake up\n");
    exit(0);
}

void (*mysignal(int signo, void (*handler)(int)))(int)
{
    struct sigaction act, oldact;
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    if (sigaction(signo, &act, &oldact) < 0)
        return SIG_ERR;

    return oldact.sa_handler;
}

