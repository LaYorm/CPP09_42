/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yorimek <yorimek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 14:06:04 by yorimek           #+#    #+#             */
/*   Updated: 2026/09/29 15:19:30 by yorimek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

#include <stack>
#include <iostream>
#include <cstdlib>

void	ft_rpn(std::stack<int> &pile, const char *arg);
void	ft_push_value(std::stack<int> &pile, const char *arg, size_t i);
void	ft_calculate(std::stack<int> &pile, const char *arg, size_t i);

class RpnException: public std::exception
{
        private:
                std::string     _message;

        public:
                RpnException(const std::string &msg): _message(msg){}
                virtual ~RpnException() throw(){}
                virtual const char *what() const throw()
                {
                        return (_message.c_str());
                }
};

#endif 