#pragma once

#include "lfsr.hpp"

#include <bitset>
#include <initializer_list>
#include <string>


namespace css {

class CSS {

public:

  using KeyType = std::bitset<40>;
  using TapType = std::size_t;

  CSS(KeyType key, std::initializer_list<TapType> taps_17, std::initializer_list<TapType> taps_25)
  : m_key{key}, m_lfsr_17{key.to_ulong(), taps_17}, m_lfsr_25{key.to_ulong(), taps_25} {}

  void reset() {
    m_lfsr_17.reset();
    m_lfsr_25.reset();
  }

  char generate_byte() {
    char byte_17 = m_lfsr_17.generate_byte();
    char byte_25 = m_lfsr_25.generate_byte();
    char output = byte_17 + byte_25 + (m_carry ? 1 : 0);
    m_carry = byte_17 & byte_25 & 0x80;
    return output;
  }

private:

  const KeyType m_key;
  lfsr::LFSR<17> m_lfsr_17;
  lfsr::LFSR<25> m_lfsr_25;
  bool m_carry = false;

};

std::string encrypt(CSS::KeyType key, std::initializer_list<CSS::TapType> taps_17, std::initializer_list<CSS::TapType> taps_25, std::string plaintext) {
  CSS generator{key, taps_17, taps_25};
  std::string ciphertext;
  ciphertext.resize(plaintext.size());
  for (auto i = 0; i < plaintext.size(); ++i) {
    auto byte = generator.generate_byte();
    ciphertext[i] = plaintext[i] + byte;
  }
  return ciphertext;
}

std::string decrypt(CSS::KeyType key, std::initializer_list<CSS::TapType> taps_17, std::initializer_list<CSS::TapType> taps_25, std::string ciphertext) {
  CSS generator{key, taps_17, taps_25};
  std::string plaintext;
  plaintext.resize(ciphertext.size());
  for (auto i = 0; i < ciphertext.size(); ++i) {
    auto byte = generator.generate_byte();
    plaintext[i] = ciphertext[i] - byte;
  }
  return plaintext;
}

}
