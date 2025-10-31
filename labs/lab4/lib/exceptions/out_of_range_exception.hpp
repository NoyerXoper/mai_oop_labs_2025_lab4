#pragma once

#include <stdexcept>

namespace exceptions {
class OutOfRangeArrayException : std::out_of_range {
    using out_of_range::out_of_range;
};
}