#include "../include/db_wrapper.h"

namespace data_access {

DbWrapper::DbWrapper() : db_(nullptr) {
  if (sqlite3_open_v2("paard en zwaard.db", &db_, SQLITE_OPEN_READONLY, nullptr) != SQLITE_OK) {
    std::cerr << "[DbWrapper()]: Error opening SQLite3 DB file: " << sqlite3_errmsg(db_) << std::endl;
    sqlite3_close_v2(db_);
  }
}

DbWrapper::~DbWrapper() { sqlite3_close_v2(db_); }

DbWrapper *DbWrapper::GetInstance() {
  static DbWrapper instance;
  return &instance;
}

sqlite3 *DbWrapper::GetDb() { return db_; }

} // data_access