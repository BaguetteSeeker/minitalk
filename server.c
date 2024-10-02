/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:02:14 by epinaud           #+#    #+#             */
/*   Updated: 2024/10/02 00:59:45 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_SOURCE
#include <signal.h>
#include "libft/libft.h"

void sigint_handler(int sig)
{
	if (sig == SIGUSR1)
	{
		ft_printf("Signal sent from client");
	}
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
	
	ft_printf("PID -> %d", getpid());
	while (1)
		continue ;
	return (0);
}
