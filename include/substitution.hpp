#pragma once

#include <string>


namespace substitution {

std::string encrypt(const std::string& varpi, const std::string& plaintext);

std::string decrypt(const std::string& varpi, const std::string& ciphertext);

} // namespace substitution
