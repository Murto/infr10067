#pragma once

#include <string>


namespace rail_fence {

std::string encrypt(std::string::size_type k, const std::string& plaintext);

std::string decrypt(std::string::size_type k, const std::string& ciphertext);

} // rail_fence
