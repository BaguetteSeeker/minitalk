/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:29:06 by epinaud           #+#    #+#             */
/*   Updated: 2024/10/07 12:19:25 by epinaud          ###   ########.fr       */
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

int	main(int argc, char *argv[])
{
	if (argc != 3)
		return (printerr("Insufficient params count during client call to main\n"));

	unsigned char   bit;

	while (*argv[2])
	{
		bit = 0b10000000;
		while (bit > 0)
		{
			if (bit & (unsigned char)*argv[2])
				ft_printf("1");
			else
				ft_printf("0");
			bit >>= 1;
		}
		ft_putchar_fd('\n', 1);
		argv[2]++;
	}

	kill(ft_atoi(argv[1]), ft_atoi(argv[2]));
	return (0);
}