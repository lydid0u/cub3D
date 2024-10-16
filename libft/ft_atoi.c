/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:14:42 by lboudjel          #+#    #+#             */
/*   Updated: 2024/10/10 20:01:21 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	if (str[i] == '-' || str[i] == '+')
		return (-1);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			return (-1);
		}
		result = result * 10 + (str[i++] - '0');
	}
	return (result);
}

/*int main()
{
	char a[] = "	  +++--+-76543ffssf654";
    printf("%d\n", ft_atoi(a));
    printf("%d\n", atoi(a));

     char b[] = "+++--+-76543ffssf654";
    printf("%d\n", ft_atoi(b));
    printf("%d\n", atoi(b));
     char c[] = "     +76543ffssf654";
    printf("%d\n", ft_atoi(c));
    printf("%d\n", atoi(c));
     char d[] = "4";
    printf("%d\n", ft_atoi(d));
    printf("%d\n", atoi(d));
}*/