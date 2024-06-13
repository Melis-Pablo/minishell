/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:55:37 by pmelis            #+#    #+#             */
/*   Updated: 2024/06/13 14:11:33 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
ft_isalnum:	Checks if the character is an alphanumeric character.

Parameters:	int c - the character to check.

Return:		int - 1 if the character is an alphanumeric character and 0
				otherwise.

How it works:
	1. Check if the character is a digit (0-9), uppercase letter (A-Z) or
		lowercase letter (a-z) and return 1 if it is and 0 otherwise.
*/
int	ft_isalnum(int c)
{
	return ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z'));
}

/*
ft_strlen:	Calculates the length of the string.

Parameters:	const char *s - the string to calculate the length of.

Return:		size_t len - the length of the string.

How it works:
	1. Initialize a variable len to 0.
	2. Loop through the string until the null terminator is reached.
	3. Increment len by 1 for each character in the string.
	4. Return len.
*/
size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

/*
ft_is_space:	Checks if the character is a whitespace character.

Parameters:		char c - the character to check.

Return:			int - 1 if the character is a whitespace character and 0
					otherwise.

How it works:
	1. Check if the character is a space (' '), tab ('\t'), newline ('\n'),
		carriage return ('\r'), form feed ('\f') or vertical tab ('\v') and
		return 1 if it is and 0 otherwise.
*/
int	ft_is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\f' || c == '\v')
		return (1);
	return (0);
}

/*
ft_reverse_str:	Reverses the string.

Parameters:		char *str - the string to reverse.
				int len - the length of the string.

Return:			void.

How it works:
	1. Initialize two variables i and j to 0 and len - 1 respectively.
	2. Loop while i is less than j.
	3. Swap the characters at i and j.
	4. Increment i and decrement j.
	5. Continue until i is less than j.
*/
void	ft_reverse_str(char *str, int len)
{
	int		i;
	int		j;
	char	temp;

	i = 0;
	j = len - 1;
	while (i < j)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
}

/*
ft_itoa:	Converts an integer to a string.

Parameters:	int n - the integer to convert.
			char *str - the string to store the result.

Return:		void.

How it works:
	1. Initialize two variables i and sign to 0.
	2. Check if n is less than 0 and set sign to 1 if it is.
	3. Check if n is 0 and set str[i] to '0' and increment i if it is.
	4. If n is negative, make it positive.
	5. Loop while n is not 0.
	6. Set str[i] to the remainder of n divided by 10 plus '0'.
	7. Divide n by 10.
	8. Increment i.
	9. If n was negative, set str[i] to '-' and increment i.
	10. Set str[i] to '\0'.
	11. Reverse the string.
*/
void	ft_itoa(int n, char *str)
{
	int	i;
	int	sign;

	i = 0;
	sign = (n < 0);
	if (n == 0)
		str[i++] = '0';
	if (sign)
		n = -n;
	while (n != 0)
	{
		str[i++] = (n % 10) + '0';
		n /= 10;
	}
	if (sign)
		str[i++] = '-';
	str[i] = '\0';
	ft_reverse_str(str, i);
}
