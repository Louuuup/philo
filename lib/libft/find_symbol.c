/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_symbol.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 13:43:09 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/10 15:49:40 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	find_symbol(char c, char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}