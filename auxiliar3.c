/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliar3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 23:25:12 by amejia            #+#    #+#             */
/*   Updated: 2022/11/22 23:28:34 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(char *s1, char *s2)
{
	char	*s1_aux;
	char	*s2_aux;

	if (ft_strlen(s2) == 0)
		return (s1);
	while (*s1 != '\0')
	{
		if (*s1 == *s2)
		{
			s1_aux = s1;
			s2_aux = s2;
			while (*s1_aux == *s2_aux)
			{
				s1_aux++;
				s2_aux++;
				if (*s2_aux == '\0')
					return (s1);
				if (*s1_aux == '\0')
					return (0);
			}
		}
		s1++;
	}
	return (0);
}

void	ft_putstr(char *str)
{
	char	*original;
	int		counter;

	original = str;
	counter = 1;
	while (*str != '\0')
	{
		str++;
		counter++;
	}
	write(1, original, counter - 1);
}

int	count_char(int fo)
{
	int		counter;
	int		status;
	char	c;

	counter = 0;
	status = 1;
	while (status == 1)
	{
		status = read(fo, &c, 1);
		counter ++;
	}
	return (counter);
}
