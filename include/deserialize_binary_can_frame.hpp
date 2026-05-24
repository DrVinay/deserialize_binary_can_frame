#pragma once
#include <vector>
#include <cstdint>

struct CanFrame {
    uint32_t id;
    uint8_t dlc;
    uint8_t  data[8];
};

CanFrame parseFrame(const std::vector<uint8_t>& raw);