/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yorimek <yorimek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 15:33:55 by yorimek           #+#    #+#             */
/*   Updated: 2026/09/18 17:29:20 by yorimek          ###   ########.fr       */
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
			throw BtcException("Invalid format: must be an integer or a floating-point number.");
		}
		i++;
	}
	if (val[i - 1] == '.' || val[0] == '.')
	{
		std::cout << "Error line " << line_n << " ==> ";
		throw BtcException("Invalid format: must be an integer or a floating-point number.");
	}	
}

static void	ft_check_line_data(std::string line, size_t line_n, std::map<std::string, double> &map_data)
{
	if (line_n == 1)
	{
		if (line != "date,exchange_rate")
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

static void	ft_check_input_value(std::string val, size_t line_n)
{
	size_t	nb_p = 0;
	size_t	i = 0;

	if (val.empty())
	{
		std::cout << "Error line " << line_n << " ==> ";
		throw BtcException("Must contain a value");
	}
	while (val[i])
	{
		if (val[i] == '.')
			nb_p++;
		if ((!isdigit(val[i]) && val[i] != '-' && val[i] != '.') || nb_p > 1)
		{
			std::cout << "Error line " << line_n << " ==> ";
			throw BtcException("Invalid format: must be an integer or a floating-point number.");
		}
		i++;
	}
	if (val[i - 1] == '.' || val[0] == '.')
	{
		std::cout << "Error line " << line_n << " ==> ";
		throw BtcException("Invalid format: must be an integer or a floating-point number.");
	}
}

static double	ft_str_to_double(std::string val, size_t line_n)
{
	char	*end;
	double	d_val = strtod(val.c_str(), &end);

	if (d_val < 0 )
	{
		std::cout << "Error line " << line_n << " ==> ";
		throw BtcException("Not a positive value");
	}
	else if (d_val > 1000)
	{
		std::cout << "Error line " << line_n << " ==> ";
		throw BtcException("Value too large. Must be <1000");
	}
	return (d_val);
}

static void	ft_print_result(std::string date, double val, size_t line_n, std::map<std::string, double> &map_data)
{
	if (date < map_data.begin()->first)
	{
		std::cout << "Error line " << line_n << " ==> ";
		throw BtcException("Date must be >= 2009-01-02");
	}
	std::map<std::string, double>::const_iterator it = map_data.begin();
	it = map_data.lower_bound(date);
	if (it == map_data.end())
	{
		it--;
		std::cout << date << " => " << val << " = " << val * it->second << std::endl;
	}
	else
	{
		if (it->first == date)
			std::cout << date << " => " << val << " = " << val * it->second << std::endl;
		else
		{
			it--;
			std::cout << date << " => " << val << " = " << val * it->second << std::endl;
		}
	}
}

static void	ft_check_line_input(std::string line, size_t line_n, std::map<std::string, double> &map_data)
{
	size_t pos = line.find(" | ");
	if (pos == 10)
	{
		std::string	date = line.substr(0, pos);
		std::string val = line.substr(pos + 3);
		ft_check_date(date, line_n);
		ft_check_input_value(val, line_n);
		double	d_val = ft_str_to_double(val, line_n);
		ft_print_result(date, d_val, line_n, map_data);
	}
	else
	{
		std::cout << "Error line " << line_n << " ==> ";
		throw BtcException("Invalid input. It must be: <YYYY-MM-DD | value>");
	}
}

void	ft_process_input(char *argv, std::map<std::string, double> &map_data)
{
	std::ifstream	file(argv);
	size_t			line_n = 2;

	if (!file.is_open())
		throw BtcException("Error: could not open file.");
	std::string line;
	if (getline(file, line))
		if (line != "date | value")
			throw BtcException("First line of input file must be: \"date | value\"");	
	while (getline(file, line))
	{
		try
		{
			ft_check_line_input(line, line_n, map_data);
		}
		catch(const std::exception& e)
		{
			std::cerr << "in " << argv << " => " << e.what() << '\n';
			line_n++;
			continue;
		}
		line_n++;
	}
	file.close();
	return ;
}

void	ft_process_data(std::map<std::string, double> &map_data)
{
	std::ifstream data("data.csv");
	size_t	line_n = 1;

	if (data.is_open())
	{
		std::string	line;
		while (std::getline(data, line))
		{
			ft_check_line_data(line, line_n, map_data);
			line_n++;
		}
	}
	data.close();
	return ;
}