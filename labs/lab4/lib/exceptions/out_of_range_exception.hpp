#pragma once

#include <stdexcept>

namespace exceptions {
class OutOfRangeArrayException : public std::out_of_range {
    using out_of_range::out_of_range;
};
}  // namespace exceptions