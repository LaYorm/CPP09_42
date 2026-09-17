/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yorimek <yorimek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 15:02:12 by yorimek           #+#    #+#             */
/*   Updated: 2026/09/17 11:53:38 by yorimek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <map>
#include <exception>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <cctype>
#include <cstdlib>
#include <utility>
#include <iomanip>

/*-----------Check data.csv---------*/
void	ft_check_data(std::map<std::string, double> &map_data);

/*-----------Exception---------*/
class BtcException: public std::exception
{
	private:
		std::string	_message;
	
	public:
		BtcException(const std::string &msg);
		virtual ~BtcException() throw(){}
		virtual const char *what() const throw()
		{
			return (_message.c_str());
		}
};

#endif