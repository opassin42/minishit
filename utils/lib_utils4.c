/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouliba <ccouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 04:32:24 by ccouliba          #+#    #+#             */
/*   Updated: 2022/12/14 05:40:20 by ccouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_atoi(const char *str)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -sign;
		str++;
	}
	while (*str >= '0' && *str <= '9')
		res = res * 10 + (*(str++) - '0') * sign;
	return (res);
}

static int	get_size(long n)
{
	int	size;

	if (n <= 0)
		size = 1;
	else
		size = 0;
	while (n)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		len;
	long	nb;

	nb = n;
	len = get_size(nb);
	res = (char *)push_top(&g_data.gc, sizeof(char) * (len + 1));
	if (!res)
		return (gc_free(), NULL);
	res[len] = '\0';
	if (nb == 0)
		res[0] = '0';
	else if (nb < 0)
	{
		res[0] = '-';
		nb = -nb;
	}
	while (len-- && nb)
	{
		res[len] = (nb % 10) + '0';
		nb = nb / 10;
	}
	return (res);
}
