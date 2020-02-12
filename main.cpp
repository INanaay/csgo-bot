#include "Connection.hpp"

void accept_and_run(tcp::acceptor& acceptor, io_service& io_service)
{
    std::shared_ptr<session> sesh = std::make_shared<session>(io_service);
    acceptor.async_accept(sesh->socket,
                          [sesh, &acceptor, &io_service](const error_code& accept_error)
                          {
                              accept_and_run(acceptor, io_service);
                              if(!accept_error)
                              {
                                  session::interact(sesh);
                              }
                          });
}

int main(int argc, const char * argv[])
{
    io_service io_service;
    ip::tcp::endpoint endpoint{ip::tcp::v4(), 8080};
    ip::tcp::acceptor acceptor{io_service, endpoint};

    acceptor.listen();
    accept_and_run(acceptor, io_service);

    io_service.run();
    return 0;
}