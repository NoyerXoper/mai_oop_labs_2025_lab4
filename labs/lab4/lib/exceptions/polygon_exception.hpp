#pragma once

#include <stdexcept>

namespace exceptions {

class PolygonException : public std::logic_error {
    using logic_error::logic_error;
};
}  // namespace exceptions