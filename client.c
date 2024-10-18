/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:29:06 by epinaud           #+#    #+#             */
/*   Updated: 2024/10/18 20:35:57 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_client	g_client;



// static int	send_byte(int pid, char c)
// {
// 	unsigned char	bit;

// 	bit = 0b10000000;
// 	while (bit > 0)
// 	{
// 		if (bit & (unsigned char)c)
// 		{
// 			//ft_putchar_fd('1', 1);
// 			if (kill(pid, SIGUSR1) < 0)
// 				exit(print_err(1));
// 		}
// 		else
// 		{
// 			//ft_putchar_fd('0', 1);
// 			if (kill(pid, SIGUSR2) < 0)
// 				exit(print_err(1));
// 		}
// 		bit >>= 1;
// 	}
// 	//ft_putchar_fd('\n', 1);
// 	return (0);
// }

// static int	send_intasbin(int pid, unsigned int integer)
// {
// 	unsigned int	bit_msk;
// 	unsigned char	byte;
// 	size_t			counter;

// 	counter = 0;
// 	byte = 0;
// 	bit_msk = 0b10000000000000000000000000000000;
// 	while (bit_msk > 0)
// 	{
// 		counter++;
// 		if (bit_msk & integer)
// 			byte += bit_msk;
// 		if (counter / 8)
// 		{
// 			send_byte(pid, byte);
// 			byte = 0;
// 			counter = 0;
// 		}
// 		bit_msk >>= 1;
// 	}
// 	return (0);
// }

static void	prep_handshake(int pid, *str)
{

}

static int	send_strasbin(int pid, char *msg)
{
	unsigned int	msglen;

	msglen = ft_strlen(msg);
	send_intasbin(pid, msglen);
	ft_putchar_fd('\n', 1);
	while (1)
	{
		send_byte(pid, *msg);
		if (*msg == '\0')
			break ;
		msg++;
	}
	return (0);
}

static int	send_bit(int pid, char c)
{
	init_client(pid)
	if (mask & (unsigned char)c)
	{
		//ft_putchar_fd('1', 1);
		if (kill(pid, SIGUSR1) < 0)
			exit(print_err(1));
	}
	else
	{
		//ft_putchar_fd('0', 1);
		if (kill(pid, SIGUSR2) < 0)
			exit(print_err(1));
	}
	mask >>= 1;
	if (mask == 0)
		byte++;
	return (0);
}

void	signals_handler(int sig, siginfo_t *siginfo, void *context)
{
	(void) context;
	if (sig == SIGUSR1)
		ft_printf("\nMessage fully printed by server %d\n", siginfo->si_pid);
	else if (sig == SIGUSR2)
	{
		ft_putchar_fd('b', 1);
		send_bit(siginfo->si_pid, );
	}
}

int	main(int argc, char *argv[])
{
	if (argc != 3)
		return (print_err(4));
	else if (ft_strlen(argv[1]) < 1 || check_pid(argv[1]))
		return (print_err(5));
	else if (!argv[2][0])
		return (print_err(6));
	ft_printf("Client starting..\n PID -> %d\n", getpid());
	set_sigaction(&signals_handler);
	//send_strasbin(ft_atoi(argv[1]), argv[2]);
	init_client(argv[1]);
	return (0);
}
