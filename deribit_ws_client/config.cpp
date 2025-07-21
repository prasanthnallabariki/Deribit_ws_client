#include "config.h"
#include <fstream>
#include <nlohmann/json.hpp>

Config load_config(const std::string& filename) {
    Config config;
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open config file.");
    }

    nlohmann::json json;
    file >> json;

    config.client_id = json.at("client_id").get<std::string>();
    config.client_secret = json.at("client_secret").get<std::string>();
    config.base_url = json.at("base_url").get<std::string>();
    config.use_dynamic_instruments = json.value("use_dynamic_instruments", false);
    config.instrument_count = json.value("instrument_count", 5);
    config.currency = json.value("currency", "BTC");
    config.kind = json.value("kind", "option");

    if (!config.use_dynamic_instruments && json.contains("instrument_names")) {
        config.instrument_names = json["instrument_names"].get<std::vector<std::string>>();
    }

    return config;
}
