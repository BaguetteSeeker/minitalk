/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 01:20:11 by epinaud           #+#    #+#             */
/*   Updated: 2024/10/15 02:03:18 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MINITALK_H
# define MINITALK_H
# define _POSIX_SOURCE 200809L
# define _XOPEN_SOURCE 700
# include "libft/libft.h"
# include "minitalk.h"
# include <signal.h>

typedef struct s_client
{
	int		pid;
	size_t		bits_count;
	unsigned int	msglen;
	char	*msg;
	unsigned char	c;
	int		byte_mask;
	unsigned int	mxint_mask;
}			t_client;

void set_sigaction(void (sighandle)(int, siginfo_t *, void *));
#endif