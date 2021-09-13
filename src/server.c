/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoncalv <vgoncalv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 13:24:14 by vgoncalv          #+#    #+#             */
/*   Updated: 2021/09/12 21:24:14 by vgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "ft_printf.h"

char	*realloc_str(char *str, size_t size)
{
	char	*ptr;

	if (str == NULL)
		return (ft_calloc(size, sizeof(char)));
	ptr = ft_calloc(size, sizeof(char));
	ft_strlcpy(ptr, str, size + 1);
	free(str);
	return (ptr);
}

void	handle_new_char(char **str, int *char_counter, int current)
{
	*str = realloc_str(*str, *char_counter + 2);
	if (current)
	{
		(*str)[*char_counter] = current;
		(*char_counter)++;
	}
	else
	{
		*char_counter = 0;
		ft_printf("[SERVER] Received message from client. Content:\n%s\n\n", *str);
		free(*str);
		*str = NULL;
	}
}

void	callback(int signum, siginfo_t *siginfo, void *context)
{
	static char	*str;
	static int	counter;
	static char	current;
	static int	char_counter;

	if (current)
		current = (current << 1) | (signum == SIGUSR1);
	else
		current = (signum == SIGUSR1);
	counter++;
	if (counter >= 8)
	{
		handle_new_char(&str, &char_counter, current);
		counter = 0;
		current = 0;
	}
	kill(siginfo->si_pid, SIGUSR1);
	(void)signum;
	(void)context;
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
	action.sa_sigaction = callback;
	action.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &action, NULL))
		exit(EXIT_FAILURE);
	if (sigaction(SIGUSR2, &action, NULL))
		exit(EXIT_FAILURE);
	return (0);
}

int	main(void)
{
	ft_printf("[SERVER] running on PID: %d\n", getpid());
	register_actions();
	while (1)
		pause();
	return (0);
}
