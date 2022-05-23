/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarceli <dmarceli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:19:15 by dmarceli          #+#    #+#             */
/*   Updated: 2022/05/23 14:20:23 by dmarceli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*ft_strdup_char(char chr)
{
	char	*dest;

	dest = malloc(sizeof(char *) * 2);
	if (dest == NULL)
		return (NULL);
	dest[0] = chr;
	dest[1] = '\0';
	return (dest);
}

char	*ft_strjoin_char(char *s1, char s2)
{
	int		i;
	char	*temp;
	int		len;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1);
	temp = malloc((len + 2) * sizeof(char));
	if (temp == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		temp[i] = s1[i];
		i++;
	}
	temp[i] = s2;
	i++;
	temp[i] = '\0';
	return (temp);
}

void	handle_signal(int sig, siginfo_t *siginfo, void *unused)
{
	static char	letter;
	static int	bit;

	(void)unused;
	if (sig == SIGUSR2)
		letter |= (1 << bit);
	bit++;
	if (bit == 8)
	{
		write(1, &letter, 1);
		if (letter == '\0')
			kill(siginfo->si_pid, SIGUSR2);
		letter = 0;
		bit = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handle_signal;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	write(1, "PID: ", 6);
	ft_putnbr_fd((int)getpid(), 1);
	write(1, "\n", 1);
	while (1)
		pause();
	return (0);
}
