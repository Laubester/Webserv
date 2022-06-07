/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:51:00 by mleblanc          #+#    #+#             */
/*   Updated: 2022/06/07 18:52:47 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ExceptionBase.hpp"
#include "ServerParser.hpp"
#include "event/EventQueue.hpp"
#include "sock/Connection.hpp"
#include "sock/SocketArray.hpp"
#include "sock/TcpStream.hpp"
#include <poll.h>
#include <vector>

class Server
{
public:
    static const int POLL_TIMEOUT = 5000;
    static const int CONNECTION_TIMEOUT = 20;
    static const size_t BUFFER_SIZE = 1024 * 32;
    static const ssize_t MAX_REQ_SIZE = 1024 * 200000;

public:
    class Exception : public ExceptionBase
    {
    public:
        Exception(const char* msg);
    };

public:
    Server();

public:
    void configure(const std::vector<Config>& blocks);
    void run();

private:
    void init_tcp_streams();
    bool is_host(int fd) const;
    void process_event_queue();
    void accept_connection(const sock::TcpStream& stream);
    void receive_data(sock::Connection& connection);
    void close_connection(sock::Connection& c);

private:
    sock::SocketArray sockets_;
    std::vector<pollfd> pfds_;
    event::EventQueue events_;
    bool configured_;
};
