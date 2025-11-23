#include "RNG.h"

std::string RNG::generateRandomNumber() {
    std::random_device rd;

    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> dist(1, 1000000);

    int random_number = dist(rng);

    std::string random_number_str = std::to_string(random_number);

    return random_number_str;
}