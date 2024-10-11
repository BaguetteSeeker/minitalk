/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:29:06 by epinaud           #+#    #+#             */
/*   Updated: 2024/10/11 13:44:19 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_SOURCE 200809L
#define _XOPEN_SOURCE 700
#include <signal.h>
#include "libft/libft.h"

static int	printerr(char *err)
{
	ft_printf("%s", err);
	return (1);
}

static int	send_charasbin(int pid, char *comlen)
{
	unsigned char	bit;
	bit = 0b10000000;
	while (bit > 0)
	{
		if (bit & (unsigned char)*comlen)
		{
			ft_printf("1");
			if (kill(pid, SIGUSR1) < 0)
				return (ft_printf("Error during signal transmission : transfer aborted\n"));
		}
		else
		{
			ft_printf("0");
			if (kill(pid, SIGUSR2) < 0)
				return (ft_printf("Error during signal transmission : transfer aborted\n"));
		}
		bit >>= 1;
		pause();
	}
	return (0);
}

static int	send_strasbin(int pid, char *str)
{
	unsigned char   bit;
	char	*comlen;

	comlen = ft_itoa(pid);
	while (*comlen)
		send_strasbin(pid, *comlen++);

	while (1)
	{
		bit = 0b10000000;
		while (bit > 0)
		{
			if (bit & (unsigned char)*str)
			{
				ft_printf("1");
				if (kill(pid, SIGUSR1) < 0)
					return (ft_printf("Error during signal transmission : transfer aborted\n"));
			}
			else
			{
				ft_printf("0");
				if (kill(pid, SIGUSR2) < 0)
					return (ft_printf("Error during signal transmission : transfer aborted\n"));
			}
			bit >>= 1;
			pause();
		}
		ft_putchar_fd('\n', 1);
		if (*str == '\0')
			break;
		str++;
	}
	return (0);
}

void signals_handler(int sig, siginfo_t *siginfo, void *context)
{
	(void) context;
	(void) siginfo;
	(void) sig;
	
	//if (sig == SIGUSR2)
		//ft_printf("Signals properly translated to char; Client continue;\n");
	//else if (sig == SIGUSR1)
		//ft_printf("Failled to convert signals to char, closing client;\n");
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

int	main(int argc, char *argv[])
{
	if (argc != 3)
		return (printerr("Invalid param count sent to client\n"));
	if (ft_atoi(argv[1]) < 1)
		return (printerr("Invalid PID\n"));
	set_sigaction(&signals_handler);
	send_strasbin(ft_atoi(argv[1]), argv[2]);
	return (0);
}