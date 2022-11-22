/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momil-vo <momil-vo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:04:55 by momil-vo          #+#    #+#             */
/*   Updated: 2022/11/22 16:25:39 by momil-vo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>

void	swap_old_new(char **map, int *sz, char *old, char *new);

//wrapper for swap_old_new
void	swap(char **map, int *sz, char *symbols, int mode)
{
	char	dflt[3];
	char	file[3];
	int		count;

	count = 2;
	while (count >= 0)
	{
		dflt[count] = symbols[count];
		file[count] = symbols[count + 3];
		count--;
	}
	if (mode == 0)
		swap_old_new(map, sz, file, dflt);
	else if (mode == 1)
		swap_old_new(map, sz, dflt, file);
	else
		write(1, "\nerror_swap()\n", 14);
}

void	swap_old_new(char **map, int *sz, char *old, char *new)
{
	int		iy;
	int		ix;
	char	*ptr;

	iy = 0;
	while (iy < sz[0])
	{
		ix = 0;
		while (ix < sz[1])
		{
			ptr = &map[iy][ix];
			if (*ptr == old[0])
				*ptr = new[0];
			else if(*ptr == old[1])
				*ptr = new[1];
			else if (*ptr == old[2])
				*ptr = new[2];
			else
			{
				write(1, "\nerror_swap_old_new()\n", 22);
				return ;
			}
			ix++;
		}
		iy++;
	}
}
