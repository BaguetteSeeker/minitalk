/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:29:06 by epinaud           #+#    #+#             */
/*   Updated: 2024/10/14 01:49:03 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_SOURCE 200809L
#define _XOPEN_SOURCE 700
#include "libft/libft.h"
#include "minitalk.h"

static int	send_byte(int pid, char c)
{
	unsigned char	bit;

	bit = 0b10000000;
	while (bit > 0)
	{
		if (bit & (unsigned char)c)
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
	return (0);
}

static int	send_intasbin(int pid, unsigned int integer)
{
	unsigned int	bit_msk;
	unsigned char	byte;
	size_t			counter;

	counter = 0;
	byte = 0;
	bit_msk = 0b10000000000000000000000000000000;
	while (bit_msk > 0)
	{
		counter++;
		if (bit_msk & integer)
			byte += bit_msk;
		if (counter / 8)
		{
			send_byte(pid, byte);
			byte = 0;
			counter = 0;
		}
		bit_msk >>= 1;
	}
	return (0);
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
			break;
		msg++;
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

int	check_PID(char *pid)
{
	while (*pid++)
	{
		if (!ft_strchr("0123456789", *pid))
			return (1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	if (argc != 3)
		return (ft_printf("Invalid param count sent to client\n"));
	else if (ft_strlen(argv[1]) < 1)
		return (ft_printf("Invalid PID\n"));
	else if (check_PID(argv[1]))
		return (ft_printf("Invalid character.s within PID"));
	set_sigaction(&signals_handler);
	send_strasbin(ft_atoi(argv[1]), argv[2]);
	return (0);
}
