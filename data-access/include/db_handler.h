#ifndef DATA_ACCESS_SRC_DB_HANDLER_H
#define DATA_ACCESS_SRC_DB_HANDLER_H

#include <iostream>
#include <mutex>
#include <thread>

#include "sqlite3.h"

namespace data_access {
class DbHandler {
 public:
  // Prohibit copy & move (Singleton)
  DbHandler(const DbHandler &) = delete;
  DbHandler(DbHandler &&) = delete;
  DbHandler &operator=(const DbHandler &) = delete;
  DbHandler &operator=(DbHandler &&) = delete;

  // Returns the singleton instance of the DbHandler.
  static DbHandler *GetInstance();

  // Destructor to clean up DB connection.
  ~DbHandler();
 private:
  sqlite3 *db_;

  DbHandler();
};

} // namespace data_access

#endif //DATA_ACCESS_SRC_DB_HANDLER_H
