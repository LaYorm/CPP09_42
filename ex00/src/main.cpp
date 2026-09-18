/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yorimek <yorimek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 14:22:37 by yorimek           #+#    #+#             */
/*   Updated: 2026/09/18 17:20:19 by yorimek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/BitcoinExchange.hpp"

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc != 2)
	{
		std::cout << "Input expected: ./btc <input_file>\n";
		return (1);
	}
	std::map<std::string, double>	map_data;
	try
	{
		ft_process_data(map_data);
	}
	catch(const std::exception& e)
	{
		std::cerr << "in Data => " << e.what() << '\n';
		return (1);
	}
	try
	{
		ft_process_input(argv[1], map_data);
	}
	catch(const std::exception& e)
	{
		std::cerr << "in " << argv[1] << " => " << e.what() << '\n';
	}
	return (0);
}