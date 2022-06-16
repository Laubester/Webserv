/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:56:58 by mafortin          #+#    #+#             */
/*   Updated: 2022/06/16 14:10:54 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"
#include "Request.hpp"
#include <string>

#pragma once

class Response
{
public:
    Response(/* args */)
    {
    }

    Response(const Request& request, std::vector<Config>& configs);

    ~Response()
    {
    }

    Config getConfig() const
    {
        return config;
    }

    void setStatusCode(size_t code);

    size_t getStatusCode() const
    {
        return status_code;
    }

    std::string getStatusCodeMsg() const
    {
        return status_code_msg;
    }

    void setHtmlBody();
    void setHtmlHeader();

private:
    void createCodeMsg();
    void buildHeaderString();

public:
    std::string body;
    std::string header;
    std::string full_content;

private:
    // std::map<int, std::string> codeList;
    Config config;
    size_t body_size;
    size_t header_size;
    size_t status_code;
    std::string status_code_msg;
    std::string full_path;
    // std::string location;
    // std::string headerString;
    // std::string codeMsg;
};