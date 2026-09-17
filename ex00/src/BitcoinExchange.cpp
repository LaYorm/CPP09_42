/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yorimek <yorimek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 15:33:55 by yorimek           #+#    #+#             */
/*   Updated: 2026/09/17 11:56:32 by yorimek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/BitcoinExchange.hpp"

BtcException::BtcException(const std::string &msg): _message(msg)
{
}

// static void	ft_check_date(std::string date, size_t line_n)
// {
	
// }

// static void	ft_check_value(std::string val, size_t line_n)
// {
	
// }

static void	ft_check_line_utils(size_t line_n, std::string date, std::string val)
{
	// size_t		i = 0;
	// size_t		nb_p = 0;
	
	(void)line_n;
	(void)date;
	(void)val;
	return ;
}

static void	ft_check_line(std::string line, size_t line_n, std::map<std::string, double> &map_data)
{
	if (line_n == 1)
	{
		if (line.compare("date,exchange_rate"))
			throw BtcException("First line of data.csv must be: \"date,exchange_rate\"");
		return ;
	}
	size_t pos = line.find(',');
	if (pos == 10)
	{
		std::string	date = line.substr(0, pos);
		std::string	val = line.substr(pos + 1);
		char		*end;
		ft_check_line_utils(line_n, date, val);
		map_data.insert(std::make_pair(date, strtod(val.c_str(), &end)));
	}
	else
	{
		std::cout << "Error line: " << line_n << " ==> ";
		throw BtcException("Invalid Format. It must be: <YYYY-MM-DD,value>");
	}
	return ;
}

void	ft_check_data(std::map<std::string, double> &map_data)
{
	std::ifstream data("data.csv");
	size_t	line_n = 1;

	if (data.is_open())
	{
		std::string	line;
		while (std::getline(data, line))
		{
			ft_check_line(line, line_n, map_data);
			line_n++;
		}
	}
	data.close();
	return ;
}