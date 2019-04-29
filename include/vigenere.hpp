#pragma once

#include <string>


namespace vigenere {

std::string encrypt(const std::string& word, const std::string& plaintext);

std::string decrypt(const std::string& word, const std::string& ciphertext);

} // namespace vigenere
