#include "vigenere.hpp"

#include <cctype>
#include <sstream>
#include <string>
#include <unordered_set>


namespace vigenere {

const static std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
const static std::unordered_set<char> alphaset{alphabet.begin(), alphabet.end()};

std::string encrypt(const std::string& word, const std::string& plaintext) {
  std::string ciphertext;
  ciphertext.resize(plaintext.size());
  for (auto i = 0, j = 0; i < plaintext.size(); ++i) {
    auto c_text = std::tolower(plaintext[i]);
    if (alphaset.find(c_text) != alphaset.end()) {
      auto c_word = std::tolower(word[i]);
      auto c_text_i = c_text - 'a';
      auto c_word_j = c_word - 'a';
      auto c_i = (c_text_i + c_word_j) % 26;
      auto c = 'a' + c_i;
      ciphertext[i] = c;
      j = (j + 1) % word.size();
    }
  }
  return ciphertext;
}

std::string decrypt(const std::string& word, const std::string& ciphertext) {
  std::string plaintext;
  plaintext.resize(ciphertext.size());
  for (auto i = 0, j = 0; i < ciphertext.size(); ++i) {
    auto c_text = std::tolower(ciphertext[i]);
    if (alphaset.find(c_text) != alphaset.end()) {
      auto c_word = std::tolower(word[i]);
      auto c_text_i = c_text - 'a';
      auto c_word_j = c_word - 'a';
      auto c_i = (c_text_i - c_word_j + 26) % 26;
      auto c = 'a' + c_i;
      plaintext[i] = c;
      j = (j + 1) % word.size();
    }
  }
  return plaintext;

}

}
