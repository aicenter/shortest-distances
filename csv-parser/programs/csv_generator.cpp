#include <algorithm>
#include <charconv>
#include <random>

#include "csv.hpp"

int main(int argc, char** argv) {
    using namespace csv;
    std::uniform_real_distribution<double> d(1, 1000000);
    std::mt19937 gen;

    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " [file]" << std::endl;
        exit(1);
    }

    std::string file = argv[1];
    std::ofstream outfile(file);

    CSVWriter<std::ofstream> writer(outfile);
    writer << std::vector<std::string>({
        "A", "B", "C", "D", "E"
        });

    for (size_t i = 0; i < 5000000; i++) {
        writer << std::vector<std::string>({
            std::to_string(d(gen)),
            std::to_string(d(gen)),
            std::to_string(d(gen)),
            std::to_string(d(gen)),
            std::to_string(d(gen))
        });
    }

    return 0;
}