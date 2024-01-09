#ifndef DATA_ACCESS_SRC_DB_WRAPPER_H
#define DATA_ACCESS_SRC_DB_WRAPPER_H

#include <iostream>
#include <memory>

#include "sqlite3.h"

namespace data_access {
class DbWrapper {
 public:
  // Prohibit copy & move (Singleton)
  DbWrapper(const DbWrapper &) = delete;
  DbWrapper(DbWrapper &&) = delete;
  DbWrapper &operator=(const DbWrapper &) = delete;
  DbWrapper &operator=(DbWrapper &&) = delete;

  // Returns the singleton instance of the DbWrapper.
  static DbWrapper *GetInstance();

  // Returns the pointer to the db instance.
  sqlite3 *GetDb();

  // Destructor to clean up DB connection.
  ~DbWrapper();
 private:
  sqlite3 *db_;

  DbWrapper();
};
} // namespace data_access

#endif // DATA_ACCESS_SRC_DB_WRAPPER_H
