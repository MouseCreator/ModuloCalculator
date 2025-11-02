#include "PrimeGenerator.h"
#include <fstream>
#include <string>
#include <random>
namespace PrimeGenerator {

    std::string padString(const std::string& str) {
        std::string padded = str;
        while (padded.length() < 7) {
            padded += '_';
        }
        return padded;
    }

    std::string restoreString(const std::string& padded) {
        std::size_t pos = padded.find('_');
        return padded.substr(0, pos);
    }

    void createBinaryFile(const std::string& textFile, const std::string& binaryFile) {
        std::ifstream input(textFile);
        std::ofstream output(binaryFile, std::ios::binary);
        if (!input || !output) {
            return;
        }

        std::string line;
        while (std::getline(input, line)) {
            std::string padded = padString(line);
            output.write(padded.c_str(), 7);
        }
        input.close();
        output.close();
    }

    size_t getNumberOfLines(const std::string& binaryFile) {
        std::ifstream input(binaryFile, std::ios::binary | std::ios::ate);
        if (!input) {
            return 0;
        }
        std::size_t fileSize = input.tellg(); 
        input.close();
        return fileSize / 7;
    }

    std::string getRandomLine(const std::string& binaryFile) {
        std::size_t numLines = getNumberOfLines(binaryFile);
        if (numLines == 0) {
            return "";
        }

        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::size_t> dist(0, numLines);
        std::size_t randomLineIndex = dist(rng);

        std::ifstream input(binaryFile, std::ios::binary);
        if (!input) {
            return "";
        }

        input.seekg(randomLineIndex * 7, std::ios::beg); 
        char buffer[8] = { 0 };
        input.read(buffer, 7);
        input.close();

        return restoreString(std::string(buffer));
    }
	std::string backup() {
        std::string options[] = { "11", "29", "101", "103", "107", "149", "199", "271", "353", "317"};
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::size_t> dist(0, 9);
        std::size_t index = dist(rng);
        return options[index];
	}
    void createFiles() {
        createBinaryFile("resource/primes.txt", "resource/primes.b");
    }
	std::string generatePrime() {
		std::string filename = "resource/primes.b";
        std::string line = getRandomLine(filename);
        return line == "" ? backup() : line;
       
	}
}