/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafortin <mafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:21:49 by mleblanc          #+#    #+#             */
/*   Updated: 2022/06/08 00:29:54 by mafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigParser.hpp"
#include "Server.hpp"

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cout << "Error, program argument" << std::endl;
        return 1;
    }
    std::string config_file(argv[1]);
    ConfigParser config_parser(config_file);

    config_parser.serverparser[0].generate_fake_config();
    Config fake_config = config_parser.serverparser[0].config;
    fake_config.print_config();

    Server server;
    std::vector<Config> configs;
    configs.push_back(fake_config);

    try {
        server.configure(configs);
        server.run();
    } catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
}
