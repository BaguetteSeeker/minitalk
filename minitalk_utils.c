/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 01:16:17 by epinaud           #+#    #+#             */
/*   Updated: 2024/10/15 17:15:58 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	set_sigaction(void (sighandle)(int, siginfo_t *, void *))
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = sighandle;
	if (sigaction(SIGUSR1, &act, NULL) < 0)
		return ;
	if (sigaction(SIGUSR2, &act, NULL) < 0)
		return ;
}

int	check_pid(char *pid)
{
	while (*pid++)
	{
		if (!ft_strchr("0123456789", *pid))
			return (1);
	}
	return (0);
}

int	print_err(int code)
{
	char	*msg;

	if (code == 1)
		msg = "Error during signal transmission : transfer aborted";
	else if (code == 2)
		msg = "Failled to return signal (to client)";
	else if (code == 3)
		msg = "Server missing client's PID";
	else if (code == 4)
		msg = "Invalid param count sent to client";
	else if (code == 5)
		msg = "Invalid PID";
	else if (code == 6)
		msg = "Invalid param count sent to client";
	ft_putendl_fd(msg, 1);
	return (0);
}
