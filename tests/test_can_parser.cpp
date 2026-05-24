#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "deserialize_binary_can_frame.hpp"
#include "print_can_frame.hpp"

TEST_CASE("Valid frame parses correctly") {
    std::vector<uint8_t> raw = {0x1F, 0xFF, 0xFF, 0xFF, 0x03, 0xDE, 0xAD, 0xBE};
    CanFrame f = parseFrame(raw);
    REQUIRE(f.id  == 0x1FFFFFFF);
    REQUIRE(f.dlc == 3);
    REQUIRE(f.data[0] == 0xDE);
    REQUIRE(f.data[1] == 0xAD);
    REQUIRE(f.data[2] == 0xBE);
}

TEST_CASE("Throws on buffer too small") {
    REQUIRE_THROWS_AS(parseFrame({0x00, 0x01, 0x02}), std::invalid_argument);
}

TEST_CASE("Throws on dlc > 8") {
    REQUIRE_THROWS_AS(parseFrame({0x00,0x00,0x00,0x01, 0x09}), std::invalid_argument);
}

TEST_CASE("Print example CAN frame") {
    std::vector<uint8_t> raw = {
        0x12, 0x34, 0x56, 0x78,
        0x04,
        0xAA, 0xBB, 0xCC, 0x00
    };

    std::cout << "Input buffer:\n";
    for (auto b : raw) {
        std::cout << std::uppercase 
                  << std::hex << std::setw(2) << std::setfill('0')
                  << (int)b << " ";
    }
    std::cout << "\n\n";

    auto frame = parseFrame(raw);

    std::cout << "Output struct:\n";
    std::cout << toString(frame) << "\n";
}