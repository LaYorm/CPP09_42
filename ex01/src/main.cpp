/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yorimek <yorimek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 14:06:21 by yorimek           #+#    #+#             */
/*   Updated: 2026/09/29 16:24:57 by yorimek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/RPN.hpp"

int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "Input expected: ./RPN \"reverse polish expression\"\n";
		return (1);
	}
	std::stack<int>	pile;
	try
	{
		ft_rpn(pile, argv[1]);
		std::cout << pile.top() << std::endl;	
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}
