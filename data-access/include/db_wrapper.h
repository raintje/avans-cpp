#ifndef DATA_ACCESS_SRC_DB_WRAPPER_H
#define DATA_ACCESS_SRC_DB_WRAPPER_H

#include <iostream>
#include <string>
#include <vector>

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

  /// @brief Fetches all factions from the database.
  /// @return A vector containing all the factions as std::strings.
  [[nodiscard]]std::vector<std::string> GetFactions() const;

  /// @brief Fetches the threat level stored under the given int.
  ///
  /// @param lvl The threat level to fetch.
  /// @return A pair containing the min and max units associated with the threat level.
  [[nodiscard]]std::pair<int, int> GetThreatLevel(int lvl) const;


  // Destructor to clean up DB connection.
  ~DbWrapper();
 private:
  sqlite3 *db_;

  DbWrapper();
};
} // namespace data_access

#endif // DATA_ACCESS_SRC_DB_WRAPPER_H
