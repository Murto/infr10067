#pragma once

#include <bitset>
#include <initializer_list>
#include <string>
#include <vector>


namespace lfsr {

template <std::size_t KEY_SIZE>
class LFSR {

public:

  using KeyType = typename std::bitset<KEY_SIZE>;
  using RegisterType = KeyType;
  using TapType = std::size_t;

  LFSR(const KeyType& key, std::initializer_list<TapType> taps)
  : m_key{key}, m_taps{taps.begin(), taps.end()} {
    reset();
  }

  void reset() {
    m_register = m_key;
  }

  char generate_byte() {
    char output = 0x00;
    for (auto i = 0; i < sizeof(char); ++i) {
      output <<= 1;
      output |= (generate_bit() ? 0x01 : 0x00);
    }
    return output;
  }

private:

  const KeyType m_key;
  const std::vector<TapType> m_taps;
  RegisterType m_register;

  bool generate_bit() {
    bool output = m_register[0];
    char feedback = false;
    for (auto tap : m_taps) {
       feedback = feedback != m_register[tap];
    }
    m_register >>= 1;
    m_register[KEY_SIZE - 1] = feedback;
    return output;
  }

};

template <std::size_t KEY_SIZE>
LFSR<KEY_SIZE> make_lfsr(const typename LFSR<KEY_SIZE>::KeyType& key, std::initializer_list<typename LFSR<KEY_SIZE>::TapType> taps) {
  return {key, taps};
}

template <std::size_t KEY_SIZE>
std::string encrypt(const typename LFSR<KEY_SIZE>::KeyType& key, std::initializer_list<typename LFSR<KEY_SIZE>::TapType> taps, const std::string& plaintext) {
  auto generator = make_lfsr<KEY_SIZE>(key, taps);
  std::string ciphertext;
  ciphertext.resize(plaintext.size());
  for (auto i = 0; i < plaintext.size(); ++i) {
    auto byte = generator.generate_byte();
    ciphertext[i] = plaintext[i] + byte;
  }
  return ciphertext;
}

template <std::size_t KEY_SIZE>
std::string decrypt(const typename LFSR<KEY_SIZE>::KeyType& key, std::initializer_list<typename LFSR<KEY_SIZE>::TapType> taps, const std::string& ciphertext) {
  auto generator = make_lfsr<KEY_SIZE>(key, taps);
  std::string plaintext;
  plaintext.resize(ciphertext.size());
  for (auto i = 0; i < ciphertext.size(); ++i) {
    auto byte = generator.generate_byte();
    plaintext[i] = ciphertext[i] - byte;
  }
  return plaintext;
}

} // namespace lfsr
