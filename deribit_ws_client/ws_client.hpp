#ifndef WS_CLIENT_HPP
#define WS_CLIENT_HPP

#include "config.hpp"
#include <vector>
#include <string>

void start_websocket_client(const Config& config, const std::vector<std::string>& instruments, const std::string& token);

#endif
