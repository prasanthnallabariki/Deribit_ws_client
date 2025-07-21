#ifndef WS_CLIENT_H
#define WS_CLIENT_H

#include <string>
#include <vector>
#include "config.h"

void start_websocket_client(const std::string& access_token, const std::vector<std::string>& instruments, const Config& config);

#endif 
