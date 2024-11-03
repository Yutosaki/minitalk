/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasakiyuto <sasakiyuto@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 21:32:53 by sasakiyuto        #+#    #+#             */
/*   Updated: 2024/11/03 20:05:29 by sasakiyuto       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	handle_signal(int sig)
{
	static int	bit_count = 0;
	static char	current_char = 0;

	if (sig == SIGUSR1)
		current_char |= (1 << bit_count);
	bit_count++;
	if (bit_count == 8)
	{
		write(1, &current_char, 1);
		ssize_t bytes_written = write(1, &current_char, 1);
        if (bytes_written == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        } else if (bytes_written != 1) {
			ft_printf("bytes_written = %ld\n", bytes_written); // もっと詳しくエラーを表示する
            perror("write");
            exit(EXIT_FAILURE);
        }
		bit_count = 0;
		current_char = 0;
	}
}

int	main(void)
{
	int					pid;
	struct sigaction	sa;

	pid = getpid();
	ft_printf("server pid = %d\n", pid);
	sa.sa_handler = handle_signal;
	sa.sa_flags = 0;
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
