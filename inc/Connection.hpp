//
// Created by nanaa on 2/11/20.
//

#ifndef CSGO_WRAPPER_CONNECTION_HPP
#define CSGO_WRAPPER_CONNECTION_HPP


#include <array>
#include <memory>
#include <boost/asio.hpp>
#include "Reply.hpp"
#include "Request.hpp"
#include "request_handler.hpp"
#include "request_parser.hpp"
#include <boost/enable_shared_from_this.hpp>

using tcp = boost::asio::ip::tcp;       // from <boost/asio.hpp>

class Connection_manager;

class Connection : public std::enable_shared_from_this<Connection> {
    public:
        Connection(const Connection&) = delete;


};

#endif //CSGO_WRAPPER_CONNECTION_HPP
