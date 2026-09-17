/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yorimek <yorimek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 15:33:55 by yorimek           #+#    #+#             */
/*   Updated: 2026/09/17 15:24:32 by yorimek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/BitcoinExchange.hpp"

BtcException::BtcException(const std::string &msg): _message(msg)
{
}

static bool	ft_is_leap(int year)
{
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		return true;
	return false;
}

static bool	ft_all_digit(std::string str)
{
	size_t i = 0;
	while (str[i])
	{
		if (!isdigit(str[i]))
			return false;
		i++;
	}
	return true;	
}

static void ft_check_month(int month, size_t line_n)
{
	if (month < 1 || month > 12)
	{
		std::cout << "Error line " << line_n << " ==> ";
		throw BtcException("Invalid month input");
	}
}

static void ft_check_day(int year, int month, int day, size_t line_n)
{
	bool	is_leap = ft_is_leap(year);

	if (((month == 4 || month == 6 || month == 9 || month == 11) && (day < 1 || day > 30))
			|| day < 1 || day > 31)
	{
		std::cout << "Error line " << line_n << " ==> ";
		throw BtcException("Invalid day input");
	}
	if (month == 2 && ((is_leap && day > 29) || (!is_leap && day > 28)))
	{
		std::cout << "Error line " << line_n << " ==> ";
		throw BtcException("Invalid day input");
	}
}

static void	ft_check_date(std::string date, size_t line_n)
{
	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
	{
		std::cout << "Error line: " << line_n << " ==> ";
		throw BtcException("Invalid input. It must be: <YYYY-MM-DD,value>");
	}
	std::string	s_year = date.substr(0, 4);
	std::string	s_month = date.substr(5, 2);
	std::string	s_day = date.substr(8, 2);
	if (!ft_all_digit(s_year) || !ft_all_digit(s_month) || !ft_all_digit(s_day))
	{
		std::cout << "Error line: " << line_n << " ==> ";
		throw BtcException("Invalid date format (only digit accepted)");
	}
	int	year = atoi(s_year.c_str());
	int	month = atoi(s_month.c_str());
	int	day = atoi(s_day.c_str());
	ft_check_month(month, line_n);
	ft_check_day(year, month, day,line_n);
	return ;
}

static void	ft_check_value(std::string val, size_t line_n)
{
	size_t	nb_point = 0;
	size_t	i = 0;

	if (val.empty())
	{
		std::cout << "Error line " << line_n << " ==> ";
		throw BtcException("Must contain an exchange rate");
	}
	while (val[i])
	{
		if (val[i] == '.')
			nb_point++;
		if ((!isdigit(val[i]) && val[i] != '.') || nb_point > 1)
		{
			std::cout << "Error line " << line_n << " ==> ";
			throw BtcException("The exchange rate must be composed by number and maximum one \".\"");
		}
		i++;
	}
	if (val[i - 1] == '.' || val[0] == '.')
	{
		std::cout << "Error line " << line_n << " ==> ";
		throw BtcException("The exchange rate can't have a \".\" at the begining or at the end");
	}	
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
		ft_check_date(date, line_n);
		ft_check_value(val, line_n);
		map_data.insert(std::make_pair(date, strtod(val.c_str(), &end)));
	}
	else
	{
		std::cout << "Error line " << line_n << " ==> ";
		throw BtcException("Invalid input. It must be: <YYYY-MM-DD,value>");
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