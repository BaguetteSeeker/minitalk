/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:02:14 by epinaud           #+#    #+#             */
/*   Updated: 2024/10/18 11:20:01 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_client	g_clients[100];

static t_client	init_client(int pid)
{
	t_client	client;

	client.pid = pid;
	client.bits_count = 0;
	client.msglen = 0;
	client.msg = NULL;
	client.c = 0;
	client.byte_mask = 0x80;
	client.mxint_mask = 0b10000000000000000000000000000000;
	return (client);
}

static t_client	*fetch_client(int pid)
{
	static int	client_table[100];
	size_t		i;

	i = 0;
	while (i < 100)
	{
		if (client_table[i] == pid)
			return (&g_clients[i]);
		i++;
	}
	if (g_clients[i].pid > 0)
	{
		print_err(7);
		exit(1);
	}
	i = 0;
	while (client_table[i])
		i++;
	g_clients[i] = init_client(pid);
	client_table[i] = pid;
	return (&g_clients[i]);
}

static void	append_msgbyte(t_client *client)
{
	if (client->c == '\0')
	{
		*(client->msg) = client->c;
		client->msg -= client->msglen;
		ft_putendl_fd(client->msg, 1);
		free(client->msg);
		*client = init_client(client->pid);
		if (client->pid == 0)
			print_err(3);
		if (kill(client->pid, SIGUSR1) == -1)
			print_err(2);
		return ;
	}
	*(client->msg) = client->c;
	client->msg++;
	client->c = 0;
	client->byte_mask = 0x80;
}

static void	signals_handler(int sig, siginfo_t *siginfo, void *context)
{
	t_client	*client;

	(void)context;
	if (siginfo->si_pid == 0)
		return (exit(print_err(3)));
	client = fetch_client(siginfo->si_pid);
	if (client->mxint_mask > 0)
	{
		client->bits_count++;
		if (sig == SIGUSR1)
			client->msglen += client->mxint_mask;
		client->mxint_mask >>= 1;
		if (client->bits_count == 32)
		{
			client->msg = malloc((client->msglen + 1) * sizeof(char));
			if (!client->msg)
				exit(print_err(8));
		}
	}
	else
	{
		if (sig == SIGUSR1)
			client->c += client->byte_mask;
		client->byte_mask /= 2;
		if (client->byte_mask == 0)
			append_msgbyte(client);
	}
	//usleep(25);
	if (kill(siginfo->si_pid, SIGUSR2) == -1)
		print_err(2);
	//ft_putchar_fd(' ', 1);
}

int	main(void)
{
	set_sigaction(&signals_handler);
	ft_printf("Server starting..\n PID -> %d\n", getpid());
	while (1)
		pause();
	return (0);
}
