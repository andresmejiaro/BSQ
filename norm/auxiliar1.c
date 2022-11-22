/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliar1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 23:22:58 by amejia            #+#    #+#             */
/*   Updated: 2022/11/22 23:23:50 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	evaluator_function_n(char c)
{
	if (((c >= '0') && (c <= '9')))
		return (1);
	return (0);
}

int	ft_str_is_numeric(char *str)
{
	while (*str != '\0')
	{
		if (!evaluator_function_n (*str))
			return (0);
		str++;
	}
	return (1);
}

int	check_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\v')
		return (1);
	if (c == '\n' || c == '\f' || c == '\r')
		return (1);
	if (c == '-')
		return (2);
	if (c == '+')
		return (3);
	return (0);
}

int	ft_atoi(char *str)
{
	int	cumulative_sign;
	int	cumulative_sum;

	cumulative_sign = 0;
	cumulative_sum = 0;
	while (check_space(*str) == 1)
		str++;
	while (check_space(*str) == 2 || check_space(*str) == 3)
	{
		if (check_space(*str) == 2)
			cumulative_sign++;
		str ++;
	}
	while (*str >= '0' && *str <= '9')
	{
		cumulative_sum = 10 * cumulative_sum + *str - '0';
		str++;
	}
	if (cumulative_sign % 2 == 1)
		cumulative_sum = -cumulative_sum;
	return (cumulative_sum);
}

void	ft_delete_char(char *str)
{
	while (*str != '\0')
	{
		*str = *(str + 1);
		str++;
	}
}
