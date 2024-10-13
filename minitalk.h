/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 01:20:11 by epinaud           #+#    #+#             */
/*   Updated: 2024/10/14 01:36:06 by epinaud          ###   ########.fr       */
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
	int		client_pid;
	char	*msg;
	unsigned char	c;
	int		counter;
}			client;

void set_sigaction(void (sighandle)(int, siginfo_t *, void *));
#endif