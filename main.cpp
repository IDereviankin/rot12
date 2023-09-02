//  Copyright 2023 Ivan Dereviankin
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//          http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.


#include <iostream>
#include "cxxopts.hpp"

constexpr int ALPHABET_LENGTH = 26;
constexpr char ALPHABET_SMALL[] = "abcdefghijklmnopqrstuvwxyz";
constexpr char ALPHABET_BIG[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int wrapping_mod(int x, int y) {
    return ((x % y) + y) % y;
}

char encode(char c, int rotation) {
    auto alphabet = std::isupper(c) ? ALPHABET_BIG : ALPHABET_SMALL;
    return alphabet[wrapping_mod(c - alphabet[0] + rotation, ALPHABET_LENGTH)];
}

std::string encode(const std::string &text, int rotation) {
    std::string result{text};

    std::transform(text.begin(), text.end(), result.begin(),
                   [rotation](auto c) { return std::isalpha(c) ? encode(c, rotation) : c; });
    return result;
}

int main(int argc, char **argv) {
    cxxopts::Options options("rot12", "Implementation of Caesar cipher");

    options.add_options()
        ("k,key", "Cipher key", cxxopts::value<int>()->default_value("12"))
        ("t,text", "Text to encode",cxxopts::value<std::string>()->default_value(""));

    auto result = options.parse(argc, argv);
    auto key = result["key"].as<int>();
    auto text = result["text"].as<std::string>();

    if (!text.empty()) {
        std::cout << encode(text, key) << std::endl;
    } else
        while (!std::cin.eof()) {
            std::getline(std::cin, text);
            std::cout << encode(text, key) << std::endl;
        }

    return 0;
}