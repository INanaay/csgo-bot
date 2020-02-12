//
// Created by nanaa on 2/11/20.
//

#include "Server.hpp"

/**
 * We first add all the signals to tell the server to quit in case they happen,
 * Then we open the acceptor with the option to reuse the adress
 * @param adress
 * @param port
 */
Server::Server(const std::string adress, const std::string port)
    : _ioContext{1}, _signals{_ioContext}, _acceptor{_ioContext}
{
    _signals.add(SIGINT);
    _signals.add(SIGTERM);
    _signals.add(SIGQUIT);

    await_stop();

    tcp::resolver resolver(_ioContext);
    tcp::endpoint endpoint = *resolver.resolve(adress, port).begin();
    _acceptor.open(endpoint.protocol());
    _acceptor.set_option(tcp::acceptor::reuse_address(true));
    _acceptor.bind(endpoint);
    _acceptor.listen();

    accept();
}

/**
 * ioContext run will block until all asynchronous operations have finished.
 * While the server is runnin, the asynchronous call accept call waiting for
 * new incoming connections is always running,
 *
 */
void Server::run() {
    _ioContext.run();
}

void Server::accept() {
    _acceptor.async_accept([this] (boost::system::error_code ec, tcp::socket socket) {
        if (!_acceptor.is_open())
            return;
        if (!ec) {
            connection_manager_.start(std::make_shared<connection>(
                         std::move(socket), connection_manager_, request_handler_));
        }
        accept();
    });
}

void Server::await_stop() {
    _signals.async_wait([this](boost::system::error_code ec, int sig) {
        _acceptor.close();
        connection_manager_.stop_all();

    });
}


