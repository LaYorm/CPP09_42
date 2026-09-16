/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yorimek <yorimek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 15:33:55 by yorimek           #+#    #+#             */
/*   Updated: 2026/09/16 18:07:45 by yorimek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/BitcoinExchange.hpp"

int	ft_check_line_utils(std::string line, size_t pos, std::map<std::string, double> &map_data)
{
	std::string	date = line.substr(0, pos);
	std::string	val = line.substr(pos + 1);
	size_t		i = 0;
	size_t		nb_p = 0;
	char		*end;
	
	while (date[i])
	{
		if (i != 4 && i != 7)
		{
			if (!isdigit(date[i]))
				return (1);		
		}
		else
			if (date[i] != '-')
				return (1);
		i++;
	}
	if (!isdigit(val[0]))
		return (1);
	i = 1;
	while (val[i])
	{
		if (val[i] == '.')
			nb_p++;
		if ((!isdigit(val[i]) && val[i] != '.') || nb_p > 1)
			return (1);
		i++;
	}
	map_data.insert(std::make_pair(date, strtod(val.c_str(), &end)));
	return (0);
}

int	ft_check_line(std::string line, size_t i, std::map<std::string, double> &map_data)
{
	if (i == 1)
	{
		if (line.compare("date,exchange_rate"))
		{
			std::cout << "First line of data.csv must be: \"date,exchange_rate\"" << i << std::endl;
			return (1);
		}
		return (0);
	}
	size_t pos = line.find(',');
	if (pos != 10 || ft_check_line_utils(line, pos, map_data))
	{
		std::cout << "Invalid format of data.csv at line: " << i << std::endl;
		return (1);
	}
	
	return (0);
}

int	ft_check_data(std::map<std::string, double> &map_data)
{
	std::ifstream data("data.csv");
	size_t	i = 1;

	if (data.is_open())
	{
		std::string	line;
		while (std::getline(data, line))
		{
			if (ft_check_line(line, i, map_data))
				return (1);
			i++;
		}
	}
	data.close();
	return (0);
}