#pragma once
#include <sstream>
#include <iomanip>
#include "deserialize_binary_can_frame.hpp"

inline std::string toString(const CanFrame& f) {
    std::ostringstream oss;

    oss << "ID=0x" 
        << std::uppercase << std::hex << f.id << "\n";

    oss << "DLC=" << std::dec << (int)f.dlc << "\n";

    oss << "Data=[";
    for (size_t i = 0; i < 8; i++) {
        oss << std::uppercase 
            << std::hex << std::setw(2) << std::setfill('0') 
            << (int)f.data[i];
        if (i < 7)
            oss << " ";
    }
    oss << "]";

    return oss.str();
}