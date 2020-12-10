#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void signal_handler(int signo, siginfo_t *si){
	if(si->si_code == SI_QUEUE){
		printf("User RTS signal %d\n", si->si_pid);
		printf("Sig Number %d\n", si->si_signo);
		printf("User Data is %d\n", si->si_value.sival_int);
		getchar();
	}
	else{
		printf("Get none realtime signal %d\n", signo);
	}
}

int main(){
	struct sigaction act;

	printf("My pid %d\n", getpid());

	act.sa_sigaction = signal_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	act.sa_restorer = NULL;

	if(sigaction(SIGTSTP, &act, 0) == -1){
		printf("signal erro\n");
		exit(0);
	}
	while(1){
		sleep(1);
	}	
}
