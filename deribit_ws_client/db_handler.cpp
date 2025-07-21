#include "db_handler.hpp"
#include <sqlite3.h>
#include <iostream>

static sqlite3* db = nullptr;

void init_db() {
    if (sqlite3_open("deribit_data.db", &db) != SQLITE_OK) {
        std::cerr << "[DB] Failed to open DB: " << sqlite3_errmsg(db) << std::endl;
    }

    const char* sql = R"(
        CREATE TABLE IF NOT EXISTS tickers (
            instrument TEXT,
            timestamp INTEGER,
            mark_price REAL,
            bid_price REAL,
            ask_price REAL
        );
    )";

    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "[DB] Create table failed: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

void insert_ticker(const std::string& instrument, uint64_t timestamp, double mark_price, double bid_price, double ask_price) {
    const char* sql = "INSERT INTO tickers (instrument, timestamp, mark_price, bid_price, ask_price) VALUES (?, ?, ?, ?, ?)";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, instrument.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int64(stmt, 2, timestamp);
        sqlite3_bind_double(stmt, 3, mark_price);
        sqlite3_bind_double(stmt, 4, bid_price);
        sqlite3_bind_double(stmt, 5, ask_price);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "[DB] Insert failed\n";
        }

        sqlite3_finalize(stmt);
    } else {
        std::cerr << "[DB] Prepare failed: " << sqlite3_errmsg(db) << std::endl;
    }
}
