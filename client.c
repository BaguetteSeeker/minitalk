/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:29:06 by epinaud           #+#    #+#             */
/*   Updated: 2024/10/04 02:39:31 by epinaud          ###   ########.fr       */
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

	kill(ft_atoi(argv[1]), ft_atoi(argv[2]));
	return (0);
}