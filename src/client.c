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

int	main(int argc, char *argv[])
{
	int	pid;

	if (argc != 3)
	{
		help(argv[0]);
		return (EXIT_FAILURE);
	}
	pid = ft_atoi(argv[1]);
	kill(pid, SIGUSR1);
	return (EXIT_SUCCESS);
}
