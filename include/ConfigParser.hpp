/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafortin <mafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 19:07:03 by mafortin          #+#    #+#             */
/*   Updated: 2022/05/31 21:06:58 by mafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <vector>
#include <map>
#include <ConfigContent.hpp>


class ConfigParser
{
public:
	ConfigParser(std::string config_file);
	~ConfigParser();
	class ConfigFileException : public std::exception{
		public:
			virtual const char* what() const throw();
	};
private:
	std::string		getContent(std::fstream& file);
	std::string		file_content;
	void			createConfig();
	ConfigContent	*config_content;

};
