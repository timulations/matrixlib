#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <cstdarg>
#include <stdexcept>

namespace Utils {
    template<typename... Args>
    std::string format_str(const std::string& format, Args&&... args) {
        size_t size = std::snprintf(nullptr, 0, format.c_str(), std::forward<Args>(args)...);
        std::string output(size + 1, '\0');
        std::snprintf(&output[0], size + 1, format.c_str(), std::forward<Args>(args)...);
        output.resize(size);
        return output;
    }

    template<typename... Args>
    inline void throw_runtime_error(const std::string& format, Args&&... args) {
        throw std::runtime_error(format_str(format, std::forward<Args>(args)...));
    }

    template <typename... Args>
    inline void throw_invalid_argument_error(const std::string& format, Args&&... args) {
        throw std::invalid_argument(format_str(format, std::forward<Args>(args)...));
    }

    template <typename... Args>
    inline void throw_out_of_range_error(const std::string& format, Args&&... args) {
        throw std::out_of_range(format_str(format, std::forward<Args>(args)...));
    }

}

#endif /* UTILS_H */