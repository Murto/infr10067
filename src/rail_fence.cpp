#include "rail_fence.hpp"

#include <string>
#include <sstream>


namespace rail_fence {

std::string encrypt(std::string::size_type k, const std::string& plaintext) {
  std::string ciphertext;
  ciphertext.resize(plaintext.size());
  for (decltype(k) i = 0; i < plaintext.size(); ++i) {
    ciphertext[(i % k) + (i / k) * k] = plaintext[i];
  }
  return ciphertext;
}

std::string decrypt(std::string::size_type k, const std::string& ciphertext) {
  std::string plaintext;
  plaintext.resize(ciphertext.size());
  auto c = ciphertext.size();
  auto dk = ((c - 1) / k) + 1;
  return encrypt(dk, ciphertext);
}

} // rail_fence
