/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasakiyuto <sasakiyuto@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 21:32:56 by sasakiyuto        #+#    #+#             */
/*   Updated: 2024/10/18 23:08:20 by sasakiyuto       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// serverに文字列とサーバーのPIDを送信する
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
		usleep(100);
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	char	*message;

	if (argc != 3)
	{
		printf("Usage: %s <pid> <string>\n", argv[0]);
		return (1);
	}
	message = argv[2];
	pid = atoi(argv[1]);
	while (*message)
	{
		send_char(pid, *message);
		message++;
	}
	send_char(pid, '\0');
	return (0);
}
