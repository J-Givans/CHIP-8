#include <cstdlib>
#include <iostream>
#include <string>

int main(int argc, char const* const argv[])
{
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <Scale> <Delay> <ROM>\n";
        std::exit(EXIT_FAILURE);
    }

    [[maybe_unused]] int const videoScale { std::stoi(argv[1]) };
    [[maybe_unused]] int const cycleDelay { std::stoi(argv[2]) };
    [[maybe_unused]] char const* const filename { argv[3] };

    return EXIT_SUCCESS;
}