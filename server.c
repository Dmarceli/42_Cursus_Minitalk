#include "minitalk.h"
#include <stdio.h>

void read_signal(int sig, siginfo_t *siginfo, void *unused)
{
	(void)unused;
	static char	letter;
	static int	bit;

	if(sig == SIGUSR2)
		letter |= (1 << bit);
	bit++;
	if (bit == 8)
	{
		write(1, &letter, 1);
		if (letter == '\0')
		{
			if (kill(siginfo->si_pid, SIGUSR2) == -1)
				write(1, "error\n", 7);
		}
		letter = 0;
		bit = 0;
	}
}

int main(void)
{

	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = read_signal;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	// signal(SIGUSR1, read_signal);
	// signal(SIGUSR2, read_signal);
	write(1,"PID: ", 6);
	ft_putnbr_fd((int)getpid(),1);
	write(1,"\n",1);
	while (1)
		pause();
	return(0);
}