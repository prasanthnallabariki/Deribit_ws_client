#include "config.h"
#include "rest_api.h"
#include "ws_client.h"
#include <iostream>

int main() {
    try {
        Config config = load_config("config.json");

        std::string access_token = authenticate(config.client_id, config.client_secret, config.base_url);

        std::vector<std::string> instruments;
        if (config.use_dynamic_instruments) {
            instruments = fetch_instruments_from_deribit(config, access_token);
        } else {
            instruments = config.instrument_names;
        }

        start_websocket_client(access_token, instruments, config);

    } catch (const std::exception& e) {
        std::cerr << "[ERROR] " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
