/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:02:14 by epinaud           #+#    #+#             */
/*   Updated: 2024/10/10 19:20:53 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_SOURCE 200809L
#define _XOPEN_SOURCE 700
#include <signal.h>
#include "libft/libft.h"
#include <stdio.h>

typedef struct s_client
{
	int		client_pid;
	char *	msg;
	unsigned char	c;
	int counter;
}			client;

client	cl[100];

static int	printerr(char *err)
{
	ft_printf("%s", err);
	return (1);
}

void signals_handler(int sig, siginfo_t *siginfo, void *context)
{
	static unsigned char	c = 0;
	static int	counter = 0x80;
	(void)context;

	if (sig == SIGUSR1)
	{
		c += counter;
		//ft_printf("1");
	}
	counter /= 2;
	if (counter == 0)
	{
		//ft_printf("New char %d\n", c);
		ft_putchar_fd(c, 1);
		//ft_putchar_fd('|', 1);
		//ft_putchar_fd('\n', 1);
		c = 0;
		counter = 0x80;
	}
	if (siginfo->si_pid == 0)
        printerr("Server missing client's PID\n");
    if (kill(siginfo->si_pid, SIGUSR2) == -1)
        printerr("Error in returning signal!\n");
}

static void set_sigaction(void (sighandle)(int, siginfo_t *, void *))
{
	struct sigaction act;

	ft_bzero(&act, sizeof(act));
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = sighandle;
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
