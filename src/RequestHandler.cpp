//
// Created by nanaa on 2/11/20.
//

#include <RequestHandler.hpp>
#include <fstream>
#include "Reply.hpp"
#include "Request.hpp"

void RequestHandler::handleRequest(const Request &req, Reply &rep) {
    std::string requestPath;
    if (!urlDecode(req.uri, requestPath)) {
        rep = Reply::stock_reply(Reply::bad_request);
        return;
    }
    if (requestPath.empty() || requestPath[0] != '/' || requestPath.find("..") != std::string::npos) {
        rep = Reply::stock_reply(Reply::bad_request);
        return;
    }
    if (requestPath[requestPath.size() - 1] == '/') {
        requestPath += "index.html";
    }

    auto lastSlashPos = requestPath.find_last_of("/");
    auto lastDotPos = requestPath.find_last_of(".");
    std::string extension;
    if (lastDotPos != std::string::npos && lastDotPos > lastSlashPos) {
        extension = requestPath.substr(lastDotPos + 1);
    }

    std::string fullPath = requestPath;
    std::ifstream is(fullPath.c_str(), std::ios::in | std::ios::binary);
    if (!is) {
        rep = Reply::stock_reply(Reply::not_found);
        return;
    }
    rep.status = Reply::ok;
    char buff[512];
    while (is.read(buff, sizeof(buff)).gcount() > 0)
        rep.content.append(buff, is.gcount());
    rep.headers.resize(2);
    rep.headers[0].name = "Content-Length";
    rep.headers[0].value = std::to_string(rep.content.size());
    rep.headers[1].name = "Content-Type";
    rep.headers[1].value = mime_types::extension_to_type(extension);



}

bool RequestHandler::urlDecode(const std::string &in, std::string &out) {
    out.clear();
    out.reserve(in.size());
    for (std::size_t index = 0; index < in.size(); ++index) {
        if (in[index] == '%') {
            if (index + 3 <= in.size()) {
                int value = 0;
                std::istringstream is(in.substr(index + 1, 2));
                if (is >> std::hex >> value) {
                    out += static_cast<char>(value);
                    index += 2;
                }
                else return (false);
            }
            else return (false);
        }
        else if (in[index] == '+') {
            out += ' ';
        }
        else {
            out += in[index];
        }
    }
    return (true);
}

