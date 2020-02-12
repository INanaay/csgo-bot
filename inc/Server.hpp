//
// Created by nanaa on 2/11/20.
//

#ifndef CSGO_WRAPPER_SERVER_HPP
#define CSGO_WRAPPER_SERVER_HPP

#include <boost/asio.hpp>
#include <string>

namespace ip = boost::asio::ip;         // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio.hpp>

class Server {
    public:
        Server(const Server&) = delete;

        explicit Server(const std::string adress, const std::string port);
        void run();

    private:
    boost::asio::io_context _ioContext;
    boost::asio::signal_set _signals;
    tcp::acceptor _acceptor;


    void accept();
    void await_stop();

};

#endif //CSGO_WRAPPER_SERVER_HPP
