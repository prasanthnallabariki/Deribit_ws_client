#ifndef DB_HANDLER_HPP
#define DB_HANDLER_HPP

#include <string>

void init_db();
void insert_ticker(const std::string& instrument, uint64_t timestamp, double mark_price, double bid_price, double ask_price);

#endif 
