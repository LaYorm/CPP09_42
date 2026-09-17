/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yorimek <yorimek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 14:22:37 by yorimek           #+#    #+#             */
/*   Updated: 2026/09/17 11:58:50 by yorimek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/BitcoinExchange.hpp"

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc != 2)
	{
		std::cout << "Input expected: ./btc <file.csv>\n";
		return (1);
	}
	std::map<std::string, double>	map_data;
	try
	{
		ft_check_data(map_data);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	// std::map<std::string, double>::const_iterator it = map_data.begin();
    // while (it != map_data.end())
    // {
    //     // it->first  = la date (clé)
    //     // it->second = le taux (valeur)
    //     std::cout << std::fixed << std::setprecision(2) 
    //               << it->first << "," << it->second << std::endl;
    //     ++it;
    // }
	return (0);
}