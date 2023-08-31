#include <iostream>
#include "cxxopts.hpp"

constexpr int ALPHABET_LENGTH = 26;
constexpr char ALPHABET_SMALL[] = "abcdefghijklmnopqrstuvwxyz";
constexpr char ALPHABET_BIG[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int wrapping_mod(int x, int y) {
    return ((x % y) + y) % y;
}

std::string encode(const std::string &text, int rotation) {
    std::string result;
    result.reserve(text.size() + 1);

    for (auto c: text) {
        if (!std::isalpha(c)) {
            result += c;
            continue;
        }

        auto alphabet = std::isupper(c) ? ALPHABET_BIG : ALPHABET_SMALL;
        result += alphabet[wrapping_mod(c - alphabet[0] + rotation, ALPHABET_LENGTH)];
    }

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
    } else while (!std::cin.eof()) {
        std::getline(std::cin, text);
        std::cout << encode(text, key) << std::endl;
    }

    return 0;
}