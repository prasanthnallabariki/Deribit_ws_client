#ifndef DB_LOGGER_H
#define DB_LOGGER_H

#include <string>
#include <sqlite3.h>

class DBLogger {
public:
    DBLogger(const std::string& db_name);
    ~DBLogger();
    void log_ticker(const std::string& instrument,
                    uint64_t timestamp,
                    double mark_price,
                    double bid_price,
                    double ask_price);


private:
    sqlite3* db;
};

#endif
