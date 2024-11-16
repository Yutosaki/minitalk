/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutsasak <yutsasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 21:32:56 by sasakiyuto        #+#    #+#             */
/*   Updated: 2024/11/16 13:23:26 by yutsasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	send_char(int pid, char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (c & (1 << i))
		{
			if (kill(pid, SIGUSR1) == -1)
			{
				perror("kill");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
			{
				perror("kill");
				exit(EXIT_FAILURE);
			}
		}
		i++;
		pause();
	}
}

void	handle_signal(int sig)
{
	(void)sig;
}

int set_signal_catching(struct sigaction *sa)
{
	sa->sa_handler =  handle_signal;
	sa->sa_flags = 0;
	sigemptyset(&sa->sa_mask);
	if (sigaction(SIGUSR1, sa, NULL) == -1)
	{
		perror("sigaction");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	char	*message;
	struct sigaction	sa;


	if (argc != 3)
	{
		ft_printf("Usage: %s <pid> <string>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	message = argv[2];
	pid = ft_atoi(argv[1]);
	if (set_signal_catching(&sa) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (*message)
	{
		send_char(pid, *message);
		message++;
	}
	send_char(pid, '\0');
	return (EXIT_SUCCESS);
}
