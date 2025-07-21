#include "db_logger.h"
#include <iostream>

DBLogger::DBLogger(const std::string& db_name) {
    if (sqlite3_open(db_name.c_str(), &db)) {
        std::cerr << "Can't open DB: " << sqlite3_errmsg(db) << std::endl;
        db = nullptr;
    } else {
        const char* sql = R"(
            CREATE TABLE IF NOT EXISTS ticker_data (
                instrument TEXT,
                timestamp INTEGER,
                mark_price REAL,
                bid_price REAL,
                ask_price REAL
            );
        )";
        char* err = nullptr;
        if (sqlite3_exec(db, sql, nullptr, nullptr, &err) != SQLITE_OK) {
            std::cerr << "Create table failed: " << err << std::endl;
            sqlite3_free(err);
        }
    }
}

DBLogger::~DBLogger() {
    if (db) sqlite3_close(db);
}

void DBLogger::log_ticker(const std::string &instrument, uint64_t timestamp, double mark_price, double bid_price, double ask_price) {
    if (!db) return;

    const char* sql = "INSERT INTO ticker_data (instrument, timestamp, mark_price, bid_price, ask_price) VALUES (?, ?, ?, ?, ?)";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, instrument.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int64(stmt, 2, timestamp);
        sqlite3_bind_double(stmt, 3, mark_price);
        sqlite3_bind_double(stmt, 4, bid_price);
        sqlite3_bind_double(stmt, 5, ask_price);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "[DB] Insert failed: " << sqlite3_errmsg(db) << "\n";
        }

        sqlite3_finalize(stmt);
    } else {
        std::cerr << "[DB] Prepare failed: " << sqlite3_errmsg(db) << "\n";
    }
}
