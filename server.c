/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasakiyuto <sasakiyuto@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 21:32:53 by sasakiyuto        #+#    #+#             */
/*   Updated: 2024/10/18 23:10:47 by sasakiyuto       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// printfをft_printfに変える

struct s_data
{
    int bit_count;
    char current_char;
};

struct s_data g_data = {0, 0};

void handle_signal(int sig)
{
    if (sig == SIGUSR1)
        g_data.current_char |= (1 << g_data.bit_count); 
    g_data.bit_count++;
    
    if (g_data.bit_count == 8)
    {
        write(1, &g_data.current_char, 1);
        g_data.bit_count = 0;
        g_data.current_char = 0;
    }
}

int	main(void)
{
	int					pid;
	struct sigaction	sa;

	pid = getpid();
	printf("server pid = %d\n", pid);
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
