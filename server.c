/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epinaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:02:14 by epinaud           #+#    #+#             */
/*   Updated: 2024/10/14 02:06:05 by epinaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

//client client_lst[];

static int	printerr(char *err)
{
	ft_printf("%s", err);
	return (1);
}

// static void	init_client_vars(unsigned char *c, int *counter, char *str)
// {
// 	*c = 0;
// 	*counter = 128;
// 	free(str);
// 	str = malloc(sizeof(char) * 1);
// }

// static char	*expand_str(char *str, char c)
// {
// 	char	*grown_str;

// 	if (c)
// 		ft_putstr_fd("Char is true", 1);
// 	grown_str = malloc(sizeof(char) * (ft_strlen(str) + 1 + 1));
// 	//assign new memory from old chain
// 	free(str);
// 	return (grown_str);
// }

void signals_handler(int sig, siginfo_t *siginfo, void *context)
{
	static unsigned char	c = 0;
	static int	bit_mask = 0x80;
	static int	msglen = 0;
	static int	bits_counter = 0;
	static unsigned int	mxint_mask = 0b10000000000000000000000000000000;
	static char	*msg;
	(void)context;

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
				ft_putstr_fd(msg - bits_counter / 8, 1);
				ft_printf("'\n'Success; Client transmission over;\n");
				free(msg - bits_counter / 8);
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
        printerr("Server missing client's PID\n");
    if (kill(siginfo->si_pid, SIGUSR2) == -1)
        printerr("Error in returning signal (to client)\n");
}

int	main(void)
{
	set_sigaction(&signals_handler);
	ft_printf("Server starting..\n PID -> %d\n", getpid());
	while (1)
		pause();
	return (0);
}
