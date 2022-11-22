/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 23:34:14 by amejia            #+#    #+#             */
/*   Updated: 2022/11/22 23:44:26 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*read_text_file2(int fo, int fsize)
{
	int		status;
	char	c;
	char	*to_return;
	char	*to_return2;

	to_return = (char *)malloc((fsize + 1) * sizeof(char));
	to_return2 = to_return;
	status = 1;
	while (status == 1)
	{
		status = read(fo, to_return, 1);
		to_return++;
	}
	*to_return = '\0';
	return (to_return2);
}

char	*read_text_file(char *path)
{
	int		fo;
	char	*to_return;
	int		fsize;

	fo = open(path, O_RDONLY);
	if (fo <= 0)
		return (0);
	fsize = count_char(fo);
	close(fo);
	fo = open(path, O_RDONLY);
	to_return = read_text_file2(fo, fsize);
	close(fo);
	if (to_return[fsize - 2] != '\n')
		return (0);
	return (to_return);
}

int	count_lines(char *str)
{
	int		counter;
	char	*str2;

	counter = 0;
	str2 = str;
	while (str2 != 0)
	{
		str2 = ft_strstr(str2, "\n");
		if (str2 == 0)
			break ;
		str2++;
		counter++;
	}
	return (counter);
}

char	**linefy(char *str, int *n_lines)
{
	char	**lines;
	int		counter;

	*n_lines = count_lines(str);
	lines = (char **)malloc(*n_lines * sizeof (char *));
	counter = 0;
	while (counter < *n_lines)
	{
		*(lines + counter) = str;
		str = ft_strstr(str, "\n");
		if (str != 0)
		{
			*str = '\0';
			str++;
		}
		counter++;
	}
	return (lines);
}

void	print_lines(char **lines, int n_lines)
{
	int	counter;

	counter = 0;
	while (counter < n_lines)
	{
		ft_putstr(lines[counter]);
		ft_putstr("\n");
		counter++;
	}
}
