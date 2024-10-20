/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:29:06 by epinaud           #+#    #+#             */
/*   Updated: 2024/10/20 04:14:03 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_client	g_client;

static void	mask_intbit(int *bit)
{
	if (g_client.mxint_mask & g_client.msglen)
		*bit = SIGUSR1;
	else
		*bit = SIGUSR2;
	g_client.mxint_mask >>= 1;
}

static int	send_bit(int srv_pid)
{
	static int	bit = 0;

	if (g_client.mxint_mask > 0)
		mask_intbit(&bit);
	else
	{
		if (g_client.byte_mask & *g_client.msg)
			bit = SIGUSR1;
		else
			bit = SIGUSR2;
		g_client.byte_mask >>= 1;
		if (g_client.byte_mask == 0)
		{
			g_client.msg++;
			g_client.byte_mask = 0b10000000;
		}
	}
	if (kill(srv_pid, bit) == -1)
		exit(print_err(1));
	return (0);
}

static void	signals_handler(int sig, siginfo_t *siginfo, void *context)
{
	(void) context;
	if (sig == SIGUSR1)
	{
		ft_printf("\nMessage fully printed by server %d\n", siginfo->si_pid);
		exit(0);
	}
	else if (sig == SIGUSR2)
		send_bit(siginfo->si_pid);
	else
		ft_putendl_fd("Unhandled signal", 1);
	return ;
}

int	main(int argc, char *argv[])
{
	if (argc != 3)
		return (print_err(4));
	else if (ft_strlen(argv[1]) < 1 || check_pid(argv[1]))
		return (print_err(5));
	else if (!argv[2][0])
		return (print_err(6));
	ft_printf("\nNew client starting..\n PID -> %d\n", getpid());
	set_sigaction(&signals_handler);
	g_client = init_client(ft_atoi(argv[1]));
	g_client.msglen = ft_strlen(argv[2]);
	g_client.msg = argv[2];
	send_bit(g_client.pid);
	while (1)
		continue ;
	return (0);
}
