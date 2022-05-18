#ifndef MINITALK_H
# define MINITALK_H

# include "libft.h"
# include <signal.h>
# include <unistd.h>


int		ft_isdigit(int c);
void	ft_error(void);
int		ft_atoi(const char *str);
void	ft_putnbr_fd(int n, int fd);

#endif