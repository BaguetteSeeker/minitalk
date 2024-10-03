/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:29:06 by epinaud           #+#    #+#             */
/*   Updated: 2024/10/03 15:06:10 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.a"

static int	printerr(char *err)
{
	ft_printf("%s", err);
	return (1);
}

int	main(int argc, char *argv[])
{
	if (argc < 3)
		return (printerr("Insufficient params count during client call to main\n"));

	kill(argv[1], argv[2]);
}