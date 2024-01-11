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

std::vector<std::string> DbWrapper::GetFactions() const {
  std::string q = "SELECT * FROM 'facties'";
  std::vector<std::string> results;
  sqlite3_stmt *s = nullptr;

  if (sqlite3_prepare_v2(db_, q.c_str(), -1, &s, nullptr) != SQLITE_OK) {
    std::cerr << sqlite3_errmsg(db_) << std::endl;
  }

  while (sqlite3_step(s) == SQLITE_ROW) {
    std::string f = reinterpret_cast<const char *>(sqlite3_column_text(s, 0));
    results.push_back(f);
  }

  delete &s;
  delete &q;
  return results;
}

std::pair<int, int> DbWrapper::GetThreatLevel(const int lvl) const {
  std::string q = "SELECT minimum, maximum FROM 'krijgsbende_dreiging' WHERE dreiging IS ? ";
  sqlite3_stmt *s = nullptr;

  if (sqlite3_prepare_v2(db_, q.c_str(), -1, &s, nullptr) != SQLITE_OK) {
    std::cerr << sqlite3_errmsg(db_) << std::endl;
  }

  if (sqlite3_bind_int(s, 1, lvl) != SQLITE_OK) {
    std::cerr << sqlite3_errmsg(db_) << std::endl;
  }

  int min, max;
  while (sqlite3_step(s) == SQLITE_ROW) {
    min = sqlite3_column_int(s, 0);
    max = sqlite3_column_int(s, 1);
  }

  delete &s;
  delete &q;
  return {min, max};
}

} // data_access