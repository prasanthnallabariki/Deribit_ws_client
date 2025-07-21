#include "ws_client.h"
#include <ixwebsocket/IXWebSocket.h>
#include <iostream>

void start_websocket_client(const std::string& access_token, const std::vector<std::string>& instruments, const Config& config) {
    std::string ws_url = "wss://test.deribit.com/ws/api/v2";
    ix::WebSocket webSocket;

    webSocket.setUrl(ws_url);
    webSocket.setOnMessageCallback([](const ix::WebSocketMessagePtr& msg) {
        if (msg->type == ix::WebSocketMessageType::Message) {
            std::cout << "[WS] Message: " << msg->str << std::endl;
        }
    });

    webSocket.start();

    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::string auth_payload = R"({
        "jsonrpc": "2.0",
        "id": 1,
        "method": "public/auth",
        "params": {
            "grant_type": "client_credentials",
            "client_id": ")" + config.client_id + R"(",
            "client_secret": ")" + config.client_secret + R"("
        }
    })";

    webSocket.send(auth_payload);

    for (const auto& instrument : instruments) {
        std::string sub_payload = R"({
            "jsonrpc": "2.0",
            "id": 2,
            "method": "public/subscribe",
            "params": {
                "channels": ["ticker.)" + instrument + R"(.raw"]
            }
        })";
        webSocket.send(sub_payload);
    }

    std::cout << "[WS] Press Enter to stop." << std::endl;
    std::cin.get();
    webSocket.stop();
}
