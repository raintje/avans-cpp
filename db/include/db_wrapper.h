#ifndef DATA_ACCESS_SRC_DB_WRAPPER_H
#define DATA_ACCESS_SRC_DB_WRAPPER_H

#include <iostream>
#include <string>
#include <vector>
#include <tuple>

#include "sqlite3.h"

namespace db {
class DbWrapper {
 public:
  // Prohibit copy & move (Singleton)
  DbWrapper(const DbWrapper &) = delete;
  DbWrapper(DbWrapper &&) = delete;
  DbWrapper &operator=(const DbWrapper &) = delete;
  DbWrapper &operator=(DbWrapper &&) = delete;

  /// @brief Returns the singleton instance of the DbWrapper.
  static DbWrapper *GetInstance();

  /// @brief Fetches all factions from the database.
  /// @return A vector containing all the factions as std::strings.
  [[nodiscard]]std::vector<std::string> GetFactions() const;

  /// @brief Fetches the threat level stored under the given int.
  ///
  /// @param lvl The threat level to fetch.
  /// @return A pair containing the min and max units associated with the threat level.
  [[nodiscard]]std::pair<int, int> GetThreatLevel(int lvl) const;

  /// @brief Fetches the chance to hit based on the given attacker and target id.
  ///
  /// @param atk The id of the attacking unit.
  /// @param tar The id of the target unit.
  ///
  /// @returns The chance to hit as a whole integer, ranging from 0 to 100.
  [[nodiscard]]int GetChanceToHit(int atk, int tar) const;

  /// @brief Fetches all troop types from the database.
  ///
  /// @returns A vector containing all the troop types as std::strings.
  [[nodiscard]]std::vector<std::string> GetTroopTypes() const;

  /// @brief Fetches troop information by faction_.
  ///
  /// @param faction The faction_ of the troop in the database.
  /// @returns A tuple containing all the information about the troop.
  [[nodiscard]]int GetTroopIdByFaction(const std::string &faction) const;

  /// @brief Fetches troop information by id.
  ///
  /// @param id The id of the troop in the database.
  /// @returns A tuple containing all the information about the troop, in this order: ID, Faction, Type, Name and Price.
  [[nodiscard]]std::tuple<int, std::string, std::string, std::string, int> GetTroopDataById(int id) const;

  [[nodiscard]]std::string GetTroopTypeById(int id) const;

  // Destructor to clean up DB connection.
  ~DbWrapper();
 private:
  sqlite3 *db_;

  DbWrapper();
};
} // namespace db

#endif // DATA_ACCESS_SRC_DB_WRAPPER_H
