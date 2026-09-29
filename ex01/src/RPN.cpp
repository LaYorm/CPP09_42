/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yorimek <yorimek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 14:05:48 by yorimek           #+#    #+#             */
/*   Updated: 2026/09/29 16:14:50 by yorimek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/RPN.hpp"

void	ft_push_value(std::stack<int> &pile, const char *arg, size_t i)
{
	if (!arg[i + 1])
		throw RpnException("Error => Can't have a digit at the end");
	else if (arg[i + 1] && arg[i + 1] == ' ')
		pile.push((arg[i] - '0'));
	else
		throw RpnException("Error => Need a space after a digit");
	return ;
}

void	ft_sub(std::stack<int> &pile)
{
	int a, b;

	b = pile.top();
	pile.pop();
	a = pile.top();
	pile.pop();
	pile.push(a - b);
}

void	ft_add(std::stack<int> &pile)
{
	int a, b;

	b = pile.top();
	pile.pop();
	a = pile.top();
	pile.pop();
	pile.push(a + b);
}

void	ft_mult(std::stack<int> &pile)
{
	int a, b;

	b = pile.top();
	pile.pop();
	a = pile.top();
	pile.pop();
	pile.push(a * b);
}

void	ft_div(std::stack<int> &pile)
{
	int a, b;

	b = pile.top();
	if (b == 0)
		throw RpnException("Error => Can't divided by zero");
	pile.pop();
	a = pile.top();
	pile.pop();
	pile.push(a / b);
}

void	ft_calculate(std::stack<int> &pile, const char *arg, size_t i)
{
	(void)arg;
	(void)i;
	if (pile.size() < 2)
		throw RpnException("Error => Not enough elements on the stack");
	else
	{
		if (arg[i] == '-')
			ft_sub(pile);
		else if (arg[i] == '+')
			ft_add(pile);
		else if (arg[i] == '/')
			ft_div(pile);
		else if (arg[i] == '*')
			ft_mult(pile);
	}
}

void	ft_rpn(std::stack<int> &pile, const char *arg)
{
	size_t	i = 0;

	while (arg[i])
	{
		if (arg[i] >= '0' && arg[i] <= '9')
		{
			ft_push_value(pile, arg, i);
		}
		else if (arg[i] == '+' || arg[i] == '-' || arg[i] == '*' || arg[i] == '/')
		{
			ft_calculate(pile, arg, i);
		}
		else if (arg[i] != ' ')
			throw RpnException("Error => Invalid character");
		i++;
	}
	if (pile.size() > 1)
		throw RpnException("Error => Invalid input. Must have only one value left after all the operations");
	else if (pile.empty())
		throw RpnException("Error => Invalid input. The stack is empty");
}