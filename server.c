/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:02:14 by epinaud           #+#    #+#             */
/*   Updated: 2024/10/15 02:25:22 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_client clients[100];

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

static void	clean_client(t_client *client)
{
	client->bits_count = 0;
	free(client->msg);
	client->msg = NULL;
	client->msglen = 0;
	client->mxint_mask = 0b10000000000000000000000000000000;
}

static t_client	*fetch_client(int pid)
{
	static int	client_table[100];
	size_t	i;

	i = 0;
	while (i < 100)
	{
		if (client_table[i] == pid)
			return (&clients[i]);
		i++;
	}
	i = 0;
	while (client_table[i])
		i++;
	clients[i] = init_client(pid);
	client_table[i] = pid;
	return (&clients[i]);
}

void signals_handler(int sig, siginfo_t *siginfo, void *context)
{
	t_client	*client;
	(void)context;

	client = fetch_client(siginfo->si_pid);
	if (client->mxint_mask > 0)
	{
		ft_printf("Bits count is %d\n", client->bits_count);
		client->bits_count++;
		if (sig == SIGUSR1)
		{
			ft_printf("1");
			//ft_printf("Received bit 1 \nMsglen is %d\n", client->msglen);
			client->msglen += client->mxint_mask;
		}
		else
			ft_printf("0");
		client->mxint_mask >>= 1;
		if (client->bits_count == 32)
		{
			ft_printf("Client msglen is %d\n", client->msglen);
			client->msg = malloc((client->msglen + 1) * sizeof(char));
			//client->bits_count = 0;
		}
	}
	else
	{
		if (sig == SIGUSR1)
			client->c += client->byte_mask;
		client->byte_mask /= 2;
		if (client->byte_mask == 0)
		{
			if (client->c == '\0')
			{
				*(client->msg) = client->c;
				client->msg -= client->msglen;
				ft_putstr_fd(client->msg, 1);
				clean_client(client);
				//client = NULL;
				ft_printf("\nSuccess; Client %d transmission over;\n", client->pid);
			}
			else
			{
				*(client->msg) = client->c;
				client->msg++;
			}
			client->c = 0;
			client->byte_mask = 0x80;
		}
	}
	if (siginfo->si_pid == 0)
        ft_printf("Server missing client's PID\n");
    if (kill(siginfo->si_pid, SIGUSR2) == -1)
        ft_printf("Error in returning signal (to client)\n");
}

int	main(void)
{
	set_sigaction(&signals_handler);
	ft_printf("Server starting..\n PID -> %d\n", getpid());
	while (1)
		pause();
	return (0);
}
