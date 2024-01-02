#include "../include/db_handler.h"

namespace data_access {

DbHandler::DbHandler() : db_(nullptr) {
  if (sqlite3_open_v2("paard en zwaard.db", &db_, SQLITE_OPEN_READONLY, nullptr) != SQLITE_OK) {
    std::cerr << "[DbHandler()]: Error opening SQLite3 DB file: " << sqlite3_errmsg(db_) << std::endl;
    sqlite3_close_v2(db_);
  }
}

DbHandler *DbHandler::GetInstance() {
  static DbHandler instance;
  return &instance;
}

DbHandler::~DbHandler() {
  sqlite3_close_v2(db_);
}

} // data_access