								                                                                Deribit(C++)

This is a C++ app that connects to Deribit's Testnet, pulls option instrument data via REST, subscribes to live updates over WebSocket, and logs key pricing info into a local SQLite database.

What It Does:
- Authenticates with Deribit using client credentials.
- Gets a list of active BTC option instruments (configurable).
- Subscribes to real-time market data for those instruments.
- Logs every incoming price update to db file.
 
What's Inside:
File               Purpose                                      
main.cpp         Entry point; wires everything together       
config.cpp/h     Loads `config.json` settings                 
rest_api.cpp/h   Auth + fetch instrument list via REST        
ws_client.cpp/h  Manages WebSocket connection & subscriptions 
db_logger.cpp/h  Handles SQLite DB setup + data insertion     
config.json      Your credentials + settings                  


Setup (Windows, MSVC, vcpkg):
Install dependencies: [vcpkg](https://github.com/microsoft/vcpkg):
vcpkg install cpr:x64-windows ixwebsocket:x64-windows openssl:x64-windows sqlite3:x64-windows nlohmann-json:x64-windows   zlib:x64-windows

Build the project:
step 1: cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=C:/Users/Admin/vcpkg/scripts/buildsystems/vcpkg.cmake
step 2: cmake --build build --config Release
step 3: copy config.json build\Release\
step 4: cd build\Release
step 5: deribit_ws_client.exe

To Check the Data:
Once it runs, you'll get a file named tickers.db.
sqlite3 tickers.db
SELECT * FROM ticker_data LIMIT 5;
