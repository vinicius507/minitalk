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

static int	g_counter = 0;
static char	g_current = '\0';

static void	callback(int signum)
{
	if (g_current)
		g_current = (g_current << 1) | (signum == SIGUSR1);
	else
		g_current = (signum == SIGUSR1);
	g_counter++;
	if (g_counter == 8)
	{
		ft_putchar(g_current);
		g_counter = 0;
		g_current = 0;
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
		if (pause())
			return (EXIT_FAILURE);
	return (0);
}
