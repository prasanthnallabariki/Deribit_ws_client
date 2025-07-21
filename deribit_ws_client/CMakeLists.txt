cmake_minimum_required(VERSION 3.15)
project(deribit_ws_client)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_TOOLCHAIN_FILE "C:/Users/Admin/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

find_package(nlohmann_json CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(CURL REQUIRED)
find_package(SQLite3 REQUIRED)
find_package(cpr CONFIG REQUIRED)


add_executable(${PROJECT_NAME}
    main.cpp
    config.cpp
    rest_api.cpp
    ws_client.cpp
    db_logger.cpp
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        nlohmann_json::nlohmann_json
        OpenSSL::SSL
        OpenSSL::Crypto
        CURL::libcurl
        SQLite::SQLite3
        cpr::cpr                        
        ws2_32
        ZLIB::ZLIB
        crypt32
        optimized C:/Users/Admin/vcpkg/installed/x64-windows/lib/ixwebsocket.lib
)
