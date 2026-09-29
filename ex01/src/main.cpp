/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yorimek <yorimek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 14:06:21 by yorimek           #+#    #+#             */
/*   Updated: 2026/09/29 14:26:04 by yorimek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int	main(int argc, char **argv)
{
	if (argc < 1)
	{
		std::cerr << "Input expected: ./RPN \"reverse polish expression\"\n";
		return (1);
	}
	
}