/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:02:14 by epinaud           #+#    #+#             */
/*   Updated: 2024/10/14 16:09:20 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_client clients[100];

static t_client	init_client(int pid)
{
	t_client	client;
	
	client.pid = pid;
	client.msglen = 0;
	client.msg = NULL;
	client.c = 0;
	client.byte_mask = 0x80;
	client.mxint_mask = 0b1000000000000000000000000000000;
	return (client);
}

static t_client	*fetch_client(int pid)
{
	static int	client_table[100];
	size_t	i;

	i = 0;
	while (i++ < 100)
	{
		if (client_table[i] == pid)
			return (&clients[i]);
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
	static int	bits_counter = 0;
	(void)context;

	client = fetch_client(siginfo->si_pid);
	bits_counter++;
	if (client->mxint_mask > 0)
	{
			//ft_printf("Msglen is %d\n", client->msglen);
		if (sig == SIGUSR1)
		{
			//ft_printf("Received bit 1 \nMsglen is %d\n", client->msglen);
			client->msglen += client->mxint_mask;
		}
		client->mxint_mask >>= 1;
		if (bits_counter == 32)
		{
			ft_printf("Bits counter is %d\nClient msglen is %d\n", bits_counter, client->msglen);
			client->msg = malloc((client->msglen + 1) * sizeof(char));
			bits_counter = 0;
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
				client->mxint_mask = 0b1000000000000000000000000000000;
				bits_counter =  0;
				free(client->msg);
				client->msg = NULL;
				client->msglen = 0;
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
