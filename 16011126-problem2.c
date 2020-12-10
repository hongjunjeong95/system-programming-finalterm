#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

void signal_handler(int sig){
	printf("sig num : %d\n",sig);
	psignal(sig, "Received Signal:");
}

void clock_tick (int signo){
	printf("waiting for wignal to be received! Count:%d\n", time(0));
	alarm(1);
}

int main(){
	struct sigaction act;
	int i;

	act.sa_handler = signal_handler;

	act.sa_flags = SA_RESTART;
	
	sigemptyset(&act.sa_mask);
	sigprocmask(SIG_BLOCK, &act.sa_mask, NULL);

	sigaction(SIGTSTP, &act, NULL);
	sigaction(SIGINT, &act, NULL);


//	clock_tick(1);
//	alarm(1);
	for(i=0; i<100; i++){
		printf("waiting for signal to be received! Count:%d\n", i);
		sleep(1);
	}
	sigpause(SIGTSTP);
	sigpause(SIGINT);
		
}
