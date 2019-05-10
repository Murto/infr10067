#pragma once

#include <array>
#include <bitset>
#include <cctype>
#include <string>
#include <unordered_set>


namespace rc4 {

const static std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
const static std::unordered_set<char> alphaset{alphabet.begin(), alphabet.end()};

template <std::size_t KEY_SIZE>
class RC4 {

public:

  using KeyType = std::bitset<KEY_SIZE>;

  RC4(const KeyType& key)
  : m_key{key} {
    reset();
  }

  void reset() {
    for (auto i = 0; i < BUFFER_SIZE; ++i) {
      m_buffer[i] = i;
    }
    for (auto i = 0, j = 0; i < BUFFER_SIZE; ++i) {
      j = (j + m_buffer[i] + (m_key[i % KEY_SIZE] ? 1 : 0) + BUFFER_SIZE) % BUFFER_SIZE;
      std::swap(m_buffer[i], m_buffer[j]);
    }
    m_i = 0;
    m_j = 0;
  }

  char generate_byte() {
    m_i = (m_i + 1) % BUFFER_SIZE;
    m_j = (m_j + m_buffer[m_i] + BUFFER_SIZE) % BUFFER_SIZE;
    std::swap(m_buffer[m_i], m_buffer[m_j]);
    return m_buffer[(m_buffer[m_i] + m_buffer[m_j] + BUFFER_SIZE) % BUFFER_SIZE];
  }

private:

  static const auto BUFFER_SIZE = 256;
  const KeyType m_key;
  std::array<char, BUFFER_SIZE> m_buffer;
  int m_i = 0;
  int m_j = 0;

};

template <std::size_t KEY_SIZE>
RC4<KEY_SIZE> make_rc4(const typename RC4<KEY_SIZE>::KeyType& key) {
  return {key};
}

template <std::size_t KEY_SIZE>
std::string encrypt(const typename RC4<KEY_SIZE>::KeyType& key, const std::string& plaintext) {
  auto generator = make_rc4<KEY_SIZE>(key);
  std::string ciphertext;
  ciphertext.resize(plaintext.size());
  for (auto i = 0; i < plaintext.size(); ++i) {
    auto byte = generator.generate_byte();
    ciphertext[i] = plaintext[i] ^ byte;
  }
  return ciphertext;
}

template <std::size_t KEY_SIZE>
std::string decrypt(const typename RC4<KEY_SIZE>::KeyType& key, const std::string& ciphertext) {
  auto generator = make_rc4<KEY_SIZE>(key);
  std::string plaintext;
  plaintext.resize(ciphertext.size());
  for (auto i = 0; i < ciphertext.size(); ++i) {
    auto byte = generator.generate_byte();
    plaintext[i] = ciphertext[i] ^ byte;
  }
  return plaintext;
}

} // namespace rc4
