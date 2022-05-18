#include "minitalk.h"

void	ft_error(void)
{
	write(1, "\e[0;31mInvalid Arguments.\n ./client <PID> <STRING>\n\033[0m", 56);
	exit(EXIT_SUCCESS);
}


void	send_byte(int pid, char byte)
{
	int i;

	i = 0;
	while (i < 8)
	{
		if (byte >> i & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(500);
		i++;
	}
	
}
void success(int sig)
{
	(void)sig;
	write(1, "\e[0;32mMessage Received!\n\033[0m", 30);
	exit(EXIT_SUCCESS);
}
void	handler(char *server_pid, char *str)
{
	int	pid;
	int	i;

	i = -1;
	pid = ft_atoi(server_pid);
	while (str[++i])
		send_byte(pid, str[i]);
	send_byte(pid, 0);
}

int	main(int argc, char **argv)
{
	signal(SIGUSR2, success);
	if(argc != 3  || ft_isdigit(ft_atoi(argv[1])))
		ft_error();
	handler(argv[1], argv[2]);
	while (1)
		pause();
}