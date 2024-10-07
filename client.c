/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:29:06 by epinaud           #+#    #+#             */
/*   Updated: 2024/10/07 18:34:26 by epinaud          ###   ########.fr       */
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

static int	send_strasbin(int pid, char *str)
{
	unsigned char   bit;

	while (*str)
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
			//pause();
		}
		ft_putchar_fd('\n', 1);
		str++;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	if (argc != 3)
		return (printerr("Insufficient params count during client call to main\n"));

	send_strasbin(ft_atoi(argv[1]), argv[2]);

	return (0);
}