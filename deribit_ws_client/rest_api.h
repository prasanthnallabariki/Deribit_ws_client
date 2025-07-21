#ifndef REST_API_H
#define REST_API_H

#include <string>
#include <vector>
#include "config.h"

std::string authenticate(const std::string& client_id, const std::string& client_secret, const std::string& base_url);
std::vector<std::string> fetch_instruments_from_deribit(const Config& config, const std::string& access_token);

#endif
