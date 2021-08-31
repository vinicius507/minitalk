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

void	help(char *client)
{
	ft_printf("Usage: %s SERVER_PID MESSAGE\n", client);
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
			{
				if (kill(pid, SIGUSR1))
					exit(EXIT_FAILURE);
			}
			else
			{
				if (kill(pid, SIGUSR2))
					exit(EXIT_FAILURE);
			}
			if (usleep(10))
				exit(EXIT_FAILURE);
			counter >>= 1;
		}
		str++;
	}
}

int	main(int argc, char *argv[])
{
	int	pid;

	if (argc != 3)
	{
		help(argv[0]);
		return (EXIT_FAILURE);
	}
	pid = ft_atoi(argv[1]);
	send_str(pid, argv[2]);
	return (EXIT_SUCCESS);
}
