/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:02:14 by epinaud           #+#    #+#             */
/*   Updated: 2024/10/03 15:00:18 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_SOURCE 200809L
#define _XOPEN_SOURCE 700
#include <signal.h>
#include "libft/libft.h"
#include <stdio.h>


void sigint_handler(int sig)
{
	if (sig == SIGINT)
		ft_printf("\nSIGINT prevented\n");
	else if (sig == SIGUSR1)
		ft_printf("\nNew chain received\n");
}

static void set_sigaction(void)
{
	struct sigaction act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = &sigint_handler;
	sigaction(SIGINT, &act, NULL);
}

int	main(void)
{
	set_sigaction();
	
	ft_printf("Server starting..\n PID -> %d\n", getpid());
	while (1)
		continue ;
	return (0);
}
