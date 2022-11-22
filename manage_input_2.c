/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_input_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 23:44:53 by amejia            #+#    #+#             */
/*   Updated: 2022/11/22 23:47:12 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	**lines_to_map(char **lines, int n_lines, char *symbols)
{
	char	**map;
	int		counter;
	int		len_str;

	map = (char **)malloc((n_lines - 1) * sizeof (char *));
	counter = 1;
	while (counter < n_lines)
	{
		*(map + counter - 1) = *(lines + counter);
		counter++;
	}
	len_str = ft_strlen(lines[0]);
	symbols[2] = lines[0][len_str - 1];
	symbols[1] = lines[0][len_str - 2];
	symbols[0] = lines[0][len_str - 4];
	return (map);
}
