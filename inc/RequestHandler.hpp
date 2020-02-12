//
// Created by nanaa on 2/11/20.
//

#ifndef CSGO_WRAPPER_REQUESTHANDLER_HPP
#define CSGO_WRAPPER_REQUESTHANDLER_HPP

#include <string>

struct Reply;
struct Request;

class RequestHandler {
    public:
        RequestHandler(const RequestHandler&) = delete;

        explicit RequestHandler() = default;
        void handleRequest(const Request &req, Reply &rep);

    private:
        static bool urlDecode(const std::string &in, std::string &out);
};

#endif //CSGO_WRAPPER_REQUESTHANDLER_HPP
