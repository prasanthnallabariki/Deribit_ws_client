#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <vector>

struct Config {
    std::string client_id;
    std::string client_secret;
    std::string base_url;
    bool use_dynamic_instruments;
    int instrument_count;
    std::string currency;
    std::string kind;
    std::vector<std::string> instrument_names;
};

Config load_config(const std::string& filename);

#endif 
