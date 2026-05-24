#include <vector>
#include <cstdint>
#include <stdexcept>
#include <cstring>
#include <string>
#include "deserialize_binary_can_frame.hpp"

// frame parser

CanFrame parseFrame(const std::vector<uint8_t> & buffer) {
    // Minimum frame: 4 bytes (id) + 1 byte (dlc) = 5 bytes
    if (buffer.size() < 5) {
        throw std::invalid_argument("Buffer too small: need atlease 5 bytes");
    }

    CanFrame frame{};

    // Deserialize CAN ID (big-endian, network byte order)
    frame.id = (static_cast<uint32_t>(buffer[0]) << 24) |
               (static_cast<uint32_t>(buffer[1]) << 16) |
               (static_cast<uint32_t>(buffer[2]) << 8) |
               (static_cast<uint32_t>(buffer[3]));

    // Deserialize dlc
    frame.dlc = buffer[4];
    // Validate dlc
    if (frame.dlc > 8) {
        throw std::invalid_argument("Invalid DLC: value" + std::to_string(frame.dlc) + "exceeds max of 8");
    }

    // Validate that the buffer contains the promised data bytes
    if (buffer.size() < 5 + frame.dlc){
        throw std::invalid_argument("Buffer too small: DLC=0" + std::to_string(frame.dlc) + "but only" +
                                    std::to_string(buffer.size() - 5) + "data bytes present");
    }

    // Copy data bytes (zero-initialized already from frame{})
    std::memcpy(frame.data, buffer.data() + 5, frame.dlc);

    return frame;
}