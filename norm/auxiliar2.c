/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliar2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 23:23:10 by amejia            #+#    #+#             */
/*   Updated: 2022/11/22 23:24:27 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcat(char *s1, char *s2)
{
	char	*to_return;

	to_return = s1;
	while (*s1 != '\0')
	{
		s1++;
	}
	while (*s2 != '\0')
	{
		*s1 = *s2;
		s1++;
		s2++;
	}
	*s1 = '\0';
	return (to_return);
}

char	*ft_strcpy(char *dest, char *src)
{
	char	*dest_cpy;

	dest_cpy = dest;
	while (1)
	{
		*dest = *src;
		if (*src == '\0')
		{
			return (dest_cpy);
		}
		dest++;
		src++;
	}
}

int	evaluator_function(char c)
{
	if ((c >= ' ') && (c <= '~'))
		return (1);
	return (0);
}

int	ft_str_is_printable(char *str)
{
	while (*str != '\0')
	{
		if (!evaluator_function(*str))
			return (0);
		str++;
	}
	return (1);
}

int	ft_strlen(char *str)
{
	int		counter;

	counter = 0;
	while (*str != '\0')
	{
		str++;
		counter++;
	}
	return (counter);
}
