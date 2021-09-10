/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgocalv <vgocalv@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 13:24:50 by vgocalv           #+#    #+#             */
/*   Updated: 2021/08/26 13:24:50 by vgocalv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include "ft_printf.h"

static int	g_response_received;

void	help(char *client)
{
	ft_printf("Usage: %s SERVER_PID MESSAGE\n", client);
}

void	send_signal(int pid, int bit)
{
	int	signal;

	if (bit)
		signal = SIGUSR1;
	else
		signal = SIGUSR2;
	if (kill(pid, signal))
		exit(EXIT_FAILURE);
	while (g_response_received == 0)
		;
	g_response_received = 0;
}

void	send_str(int pid, const char *str)
{
	char	byte;
	int		counter;

	while (*str)
	{
		byte = *str;
		counter = 1 << 7;
		while (counter)
		{
			if (counter & byte)
				send_signal(pid, 1);
			else
				send_signal(pid, 0);
			counter >>= 1;
		}
		str++;
	}
	counter = 8;
	while (counter--)
		send_signal(pid, 0);
}

void	callback(int signum)
{
	g_response_received = 1;
	(void)signum;
}

int	main(int argc, char *argv[])
{
	int					pid;
	struct sigaction	action;

	if (argc != 3)
	{
		help(argv[0]);
		return (EXIT_FAILURE);
	}
	ft_bzero(&action, sizeof(struct sigaction));
	action.sa_handler = callback;
	// TODO: error handling
	sigaction(SIGUSR1, &action, NULL);
	pid = ft_atoi(argv[1]);
	send_str(pid, argv[2]);
	return (EXIT_SUCCESS);
}
