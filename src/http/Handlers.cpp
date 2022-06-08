/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handlers.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 12:39:04 by mleblanc          #+#    #+#             */
/*   Updated: 2022/06/08 19:29:20 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Handlers.hpp"
#include "Buffer.hpp"
#include "Utils.hpp"
#include <iostream>

#include <fcntl.h>
#include <unistd.h>

namespace http
{

void parse_request_line(sock::Connection& c)
{
    RequestLine line;
    bool error = false;

    if (c.buffer().find(REQ_EOL, strlen(REQ_EOL)) == NULL) {
        return;
    }

    try {
        line = http::RequestLine(c.buffer());
        c.request() = http::Request(line);
    } catch (const std::exception& ex) {
        error = true;
        std::cerr << ex.what() << std::endl;
    }

    if (error) {
        // TODO: bad request
        return;
    }

    c.next_request_state();
    parse_headers(c);
}

void parse_http_request_line(sock::Connection& c)
{
    RequestLine line;
    bool error = false;

    if (c.buffer().find(REQ_EOL, strlen(REQ_EOL)) == NULL) {
        return;
    }

    try {
        line = http::RequestLine(c.buffer());
        c.request() = http::Request(line);
    } catch (const std::exception& ex) {
        error = true;
        std::cerr << ex.what() << std::endl;
    }

    if (error) {
        // TODO: bad request
        return;
    }

    c.next_request_state();
    parse_headers(c);
}

void parse_headers(sock::Connection& c)
{
    Buffer& buf = c.buffer();
    const char* ptr;
    while ((ptr = buf.find(REQ_EOL, strlen(REQ_EOL))) != NULL) {
        if (ptr == buf.cursor()) {
            c.next_request_state();
            buf.advance_cursor(strlen(REQ_EOL));
            c.request().print();
            break;
        }

        try {
            http::Header header(get_next_word(buf, REQ_EOL, strlen(REQ_EOL)));
            c.request().add_header(header);
        } catch (const std::exception& ex) {
            std::cout << ex.what() << std::endl;
        }
    }
    buf.erase_to_cursor();

    if (c.request_state() == http::REQ_BODY) {
        parse_body(c);
    }
}

void parse_body(sock::Connection& c)
{
    http::Request& req = c.request();
    Buffer& buf = c.buffer();

    switch (req.body_type()) {
        case http::B_CONTENT_LENGTH:
            if (req.content_length() != 0) {
                size_t bytes =
                    req.content_length() > buf.size() ? buf.size() : req.content_length();

                const char* start = buf.cursor();
                const char* end = start + bytes;
                req.body().append(start, end);
                req.read_body_bytes(bytes);
                buf.advance_cursor(bytes);
                buf.erase_to_cursor();

                if (req.content_length() == 0) {
                    c.next_request_state();
                    c.set_write();
                }
            }
            break;
        case http::B_CHUNKED:
            break;
        case http::B_MULTIPART_FORMDATA:
            break;
        case http::B_NONE:
            break;
    }
}
} // namespace http
