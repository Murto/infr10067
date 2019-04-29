#pragma once

#include <bitset>


namespace one_time_pad {

template <std::size_t N>
std::bitset<N> encrypt(const std::bitset<N>& k, const std::bitset<N>& plaintext) {
  return k ^ plaintext;
}

template <std::size_t N>
std::bitset<N> decrypt(const std::bitset<N>& k, const std::bitset<N>& ciphertext) {
  return encrypt(k, ciphertext);
}

} // namespace one_time_pad
