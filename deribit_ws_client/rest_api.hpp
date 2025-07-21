#ifndef REST_API_HPP
#define REST_API_HPP

#include "config.hpp"
#include <string>
#include <vector>

std::string authenticate(const Config& config);
std::vector<std::string> fetch_option_instruments(const std::string& token, const Config& config);

#endif 
