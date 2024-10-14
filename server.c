/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:02:14 by epinaud           #+#    #+#             */
/*   Updated: 2024/10/14 14:58:39 by epinaud          ###   ########.fr       */
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
	client.mxint_mask = 0x7FFFFFFF;
	return (client);
}

static t_client	*fetch_client(int pid, int client_table[100])
{
	size_t	i;

	i = 0;
	while (i++ < 100)
	{
		if (client_table[i] == pid)
			return (&clients[i]);
	}
	i = 0;
	while (client_table[i])
		client_table++;
	clients[i] = init_client(pid);
	client_table[i] = pid;
	return (&clients[i]);
}

void signals_handler(int sig, siginfo_t *siginfo, void *context)
{
	t_client	*client;
	static int	client_table[100];
	static unsigned char	c = 0;
	static int	bit_mask = 0x80;
	static int	msglen = 0;
	static unsigned int	mxint_mask = 0b10000000000000000000000000000000;
	static char	*msg;
	static int	bits_counter = 0;
	(void)context;

	client = fetch_client(siginfo->si_pid, client_table);
	//ft_printf("Client pid is %d\n", client.pid);
	//Check struct, if pid exist fetch progression else init struct
	//if msglen == -1 if combytescount != 4 : msglen += parse_byte()
	//else parse msg
	bits_counter++;
	if (mxint_mask > 0)
	{
		if (sig == SIGUSR1)
			msglen += mxint_mask;
		mxint_mask >>= 1;
		if (bits_counter == 32)
		{
			ft_printf("Bits counter is %d\n", bits_counter);
			msg = malloc((msglen + 1) * sizeof(char));
			bits_counter = 0;
		}
		//return ;
	}
	else
	{
		if (sig == SIGUSR1)
			c += bit_mask;
		bit_mask /= 2;
		if (bit_mask == 0)
		{
			if (c == '\0')
			{
				*msg = c;
				ft_putstr_fd(msg - msglen, 1);
				//ft_printf("\nSuccess; Client transmission over;\n");
				free(msg - msglen);
				mxint_mask = 0b10000000000000000000000000000000;
				bits_counter =  0;
				msg = NULL;
				msglen = 0;
				//Maybe end of messGE SUCH AS : Cliend <pid> successfully transmission over
				//Free *str / reset struct
			}
			else
				*msg++ = c;
			//init_client_vars(&c, &counter, str);
			//ft_putchar_fd('\n', 1);
			c = 0;
			bit_mask = 0x80;
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
