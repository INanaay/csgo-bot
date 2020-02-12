//
// Created by nanaa on 2/11/20.
//

#ifndef CSGO_WRAPPER_REQUEST_HPP
#define CSGO_WRAPPER_REQUEST_HPP

#include <vector>
#include "Header.hpp"

struct Request {
    std::string method;
    std::string uri;
    int httpVersionMajor;
    int httpVersionMinor;
    std::vector<Header> headers;
};

#endif //CSGO_WRAPPER_REQUEST_HPP
