#include "substitution.hpp"

#include <cctype>
#include <iterator>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>


namespace substitution {

const static std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
const static std::unordered_set<char> alphaset{alphabet.begin(), alphabet.end()};

std::string encrypt(const std::string& varpi, const std::string& plaintext) {
  if (varpi.size() != alphabet.size()) {
    throw std::runtime_error{"Wrong size of varpi"};
  } else if (std::unordered_set<char>{varpi.begin(), varpi.end()} != alphaset) {
    throw std::runtime_error{"Invalid varpi"};
  }
  std::unordered_map<char, char> varpi_map;
  for (auto i = 0; i < varpi.size(); ++i) {
    varpi_map[alphabet[i]] = varpi[i];
  }
  std::string ciphertext;
  ciphertext.reserve(plaintext.size());
  for (char c : plaintext) {
    c = std::tolower(c);
    if (varpi_map.find(c) != varpi_map.end()) {
      ciphertext += varpi_map[c];
    } else {
      ciphertext += c;
    }
  }
  return ciphertext;
}

std::string decrypt(const std::string& varpi, const std::string& ciphertext) {
  if (varpi.size() != alphabet.size()) {
    throw std::runtime_error{"Wrong size of varpi"};
  } else if (std::unordered_set<char>{varpi.begin(), varpi.end()} != alphaset) {
    throw std::runtime_error{"Invalid varpi"};
  }
  std::unordered_map<char, char> varpi_map;
  for (auto i = 0; i < varpi.size(); ++i) {
    varpi_map[varpi[i]] = alphabet[i];
  }
  std::string plaintext;
  plaintext.reserve(ciphertext.size());
  for (char c : ciphertext) {
    c = std::tolower(c);
    if (varpi_map.find(c) != varpi_map.end()) {
      plaintext += varpi_map[c];
    } else {
      plaintext += c;
    }
  }
  return plaintext;
}

} // namespace substitution
