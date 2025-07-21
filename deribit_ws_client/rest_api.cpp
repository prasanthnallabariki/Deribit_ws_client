#include "rest_api.h"
#include <cpr/cpr.h>
#include <iostream>
#include <nlohmann/json.hpp>

std::string authenticate(const std::string& client_id, const std::string& client_secret, const std::string& base_url) {
    std::string url = base_url + "/public/auth";
    std::string params = "?grant_type=client_credentials&client_id=" + client_id + "&client_secret=" + client_secret;
    
    auto response = cpr::Get(cpr::Url{url + params});
    if (response.status_code != 200) {
        throw std::runtime_error("Failed to authenticate with Deribit");
    }

    auto json = nlohmann::json::parse(response.text);
    return json["result"]["access_token"];
}

std::vector<std::string> fetch_instruments_from_deribit(const Config& config, const std::string& access_token) {
    std::vector<std::string> instruments;

    std::string url = config.base_url + "/public/get_instruments?currency=" + config.currency + "&kind=" + config.kind;

    auto response = cpr::Get(cpr::Url{url}, cpr::Bearer{access_token});
    if (response.status_code != 200) {
        throw std::runtime_error("Failed to fetch instruments from Deribit");
    }

    auto json = nlohmann::json::parse(response.text);
    for (const auto& item : json["result"]) {
        instruments.push_back(item["instrument_name"]);
        if (instruments.size() >= static_cast<size_t>(config.instrument_count)) break;
    }

    return instruments;
}
