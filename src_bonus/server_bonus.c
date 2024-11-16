/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutsasak <yutsasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 21:32:53 by sasakiyuto        #+#    #+#             */
/*   Updated: 2024/11/16 17:41:04 by yutsasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	handle_signal(int sig, siginfo_t *info, void *ucontext)
{
	static int	bit_count = 0;
	static char	current_char = 0;

	(void)ucontext;
	if (sig == SIGUSR1)
		current_char |= (1 << bit_count);
	bit_count++;
	if (bit_count == 8)
	{
		write(1, &current_char, 1);
		bit_count = 0;
		current_char = 0;
	}
	usleep(1000);
	if (kill(info->si_pid, SIGUSR1) == -1)
	{
		perror("kill");
		exit(EXIT_FAILURE);
	}
}

int	main(void)
{
	int					pid;
	struct sigaction	sa;

	pid = getpid();
	ft_printf("server pid = %d\n", pid);
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		pause();
	}
	return (0);
}
