/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yorimek <yorimek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 15:02:12 by yorimek           #+#    #+#             */
/*   Updated: 2026/09/16 18:06:12 by yorimek          ###   ########.fr       */
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
int	ft_check_data(std::map<std::string, double> &map_data);
int	ft_check_line(std::string line, size_t i, std::map<std::string, double> &map_data);
int	ft_check_line_utils(std::string line, size_t pos, std::map<std::string, double> &map_data);


#endif