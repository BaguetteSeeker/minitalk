/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:02:14 by epinaud           #+#    #+#             */
/*   Updated: 2024/10/18 20:18:38 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_client	g_clients[100];

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
			//ft_putnbr_fd(client->msglen, 1);
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
	//usleep(50);
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
