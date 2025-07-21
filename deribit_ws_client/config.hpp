#pragma once
#include <string>
#include <vector>

struct Config {
    std::string client_id;
    std::string client_secret;
    std::string base_url;
    std::string expiry_date;  // Add this line
    std::vector<std::string> instruments;
};

bool load_config_from_file(Config& config, const std::string& filename = "config.json");
