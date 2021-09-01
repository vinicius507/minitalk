/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgocalv <vgocalv@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 13:24:14 by vgocalv           #+#    #+#             */
/*   Updated: 2021/08/26 13:24:14 by vgocalv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_printf.h"

void	callback(int signum)
{
	static int	counter;
	static char	current;

	if (current)
		current = (current << 1) | (signum == SIGUSR1);
	else
		current = (signum == SIGUSR1);
	counter++;
	if (counter >= 7)
	{
		counter = 0;
		ft_printf("%c", current);
		current = 0;
	}
	(void)signum;
}

int	register_actions(void)
{
	sigset_t			mask;
	struct sigaction	action;

	if (sigemptyset(&mask))
		exit(EXIT_FAILURE);
	if (sigaddset(&mask, SIGUSR1))
		exit(EXIT_FAILURE);
	if (sigaddset(&mask, SIGUSR2))
		exit(EXIT_FAILURE);
	ft_bzero(&action, sizeof(struct sigaction));
	action.sa_mask = mask;
	action.sa_handler = callback;
	if (sigaction(SIGUSR1, &action, NULL))
		exit(EXIT_FAILURE);
	if (sigaction(SIGUSR2, &action, NULL))
		exit(EXIT_FAILURE);
	return (0);
}

int	main(void)
{
	ft_printf("PID: %d\n", getpid());
	register_actions();
	while (1)
		pause();
	return (0);
}
