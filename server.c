/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:02:14 by epinaud           #+#    #+#             */
/*   Updated: 2024/10/20 03:10:01 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_client	g_clients[100];

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
		exit(print_err(7));
	i = 0;
	while (client_table[i])
		i++;
	g_clients[i] = init_client(pid);
	client_table[i] = pid;
	return (&g_clients[i]);
}

static void	parse_msglen(int sig, t_client *client)
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
	return ;
}

static void	output_msg(t_client *client)
{
	*(client->msg) = client->c;
	client->msg -= client->msglen;
	if (!client->msg || *client->msg == '\0')
		exit(print_err(8));
	ft_putendl_fd(client->msg, 1);
	free(client->msg);
	*client = init_client(client->pid);
	if (kill(client->pid, SIGUSR1) == -1)
		print_err(2);
	return ;
}

static void	signals_handler(int sig, siginfo_t *siginfo, void *context)
{
	t_client	*client;

	(void)context;
	if (siginfo->si_pid == 0)
		return (exit(print_err(3)));
	client = fetch_client(siginfo->si_pid);
	if (client->mxint_mask > 0)
		parse_msglen(sig, client);
	else
	{
		if (sig == SIGUSR1)
			client->c += client->byte_mask;
		client->byte_mask >>= 1;
		if (client->byte_mask == 0)
		{
			if (client->c == '\0')
				return (output_msg(client));
			*(client->msg)++ = client->c;
			client->c = 0;
			client->byte_mask = 0x80;
		}
	}
	if (kill(siginfo->si_pid, SIGUSR2) == -1)
		print_err(2);
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
