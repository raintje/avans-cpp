#include "../include/db_wrapper.h"

namespace db {

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

  return results;
}

std::pair<int, int> DbWrapper::GetThreatLevel(const int lvl) const {
  std::string q = "SELECT minimum, maximum FROM 'krijgsbende_dreiging' WHERE dreiging IS ?";
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

  return std::make_pair(min, max);
}

int DbWrapper::GetChanceToHit(const int atk, const int tar) const {
  std::string q = "SELECT raakkans FROM 'raakkans' WHERE aanvaller_id = ? AND doelwit_id = ?";
  sqlite3_stmt *s = nullptr;

  if (sqlite3_prepare_v2(db_, q.c_str(), -1, &s, nullptr) != SQLITE_OK) {
    std::cerr << sqlite3_errmsg(db_) << std::endl;
  }

  if (sqlite3_bind_int(s, 1, atk) != SQLITE_OK || sqlite3_bind_int(s, 2, tar) != SQLITE_OK) {
    std::cerr << sqlite3_errmsg(db_) << std::endl;
  }

  int chance;
  while (sqlite3_step(s) == SQLITE_ROW) {
    chance = sqlite3_column_int(s, 0);
  }

  return chance;
}

std::vector<std::string> DbWrapper::GetTroopTypes() const {
  std::string q = "SELECT * FROM 'manschap_soorten'";
  sqlite3_stmt *s = nullptr;
  std::vector<std::string> results;

  if (sqlite3_prepare_v2(db_, q.c_str(), -1, &s, nullptr) != SQLITE_OK) {
    std::cerr << sqlite3_errmsg(db_) << std::endl;
  }

  while (sqlite3_step(s) == SQLITE_ROW) {
    std::string f = reinterpret_cast<const char *>(sqlite3_column_text(s, 0));
    results.push_back(f);
  }

  return results;
}

std::tuple<int, std::string, std::string, std::string, int> DbWrapper::GetTroopData(const int id) const {
  std::string q = "SELECT factie, soort, naam, prijs FROM 'manschappen' WHERE id = ?";
  sqlite3_stmt *s = nullptr;

  if (sqlite3_prepare_v2(db_, q.c_str(), -1, &s, nullptr) != SQLITE_OK) {
    std::cerr << sqlite3_errmsg(db_) << std::endl;
  }

  if (sqlite3_bind_int(s, 1, id) != SQLITE_OK) {
    std::cerr << sqlite3_errmsg(db_) << std::endl;
  }

  std::string faction, type, name;
  int price;
  while (sqlite3_step(s) == SQLITE_ROW) {
    faction = reinterpret_cast<const char *>(sqlite3_column_text(s, 0));
    type = reinterpret_cast<const char *>(sqlite3_column_text(s, 1));
    name = reinterpret_cast<const char *>(sqlite3_column_text(s, 2));
    price = sqlite3_column_int(s, 3);
  }

  return std::make_tuple(id, faction, type, name, price);
}

} // db