/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:02:14 by epinaud           #+#    #+#             */
/*   Updated: 2024/10/07 18:28:00 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_SOURCE 200809L
#define _XOPEN_SOURCE 700
#include <signal.h>
#include "libft/libft.h"
#include <stdio.h>


void signals_handler(int sig)
{
	if (sig == SIGINT)
		ft_printf("\nSIGINT prevented\n");
	else if (sig == SIGUSR1)
		ft_printf("\nBit 1 received\n");
	else if (sig == SIGUSR2)
		ft_printf("\nBit 0 received\n");

}

static void set_sigaction(void (sighandle)(int))
{
	struct sigaction act;

	ft_bzero(&act, sizeof(act));
	sigemptyset(&act.sa_mask);
	act.sa_handler = sighandle;
	if (sigaction(SIGINT, &act, NULL) < 0)
		return ;
	if (sigaction(SIGUSR1, &act, NULL) < 0)
		return ;	
	if (sigaction(SIGUSR2, &act, NULL) < 0)
		return ;
}

int	main(void)
{
	set_sigaction(&signals_handler);
	
	ft_printf("Server starting..\n PID -> %d\n", getpid());
	while (1)
		pause();
	return (0);
}
