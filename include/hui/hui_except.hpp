#ifndef I_HUI_HUI_EXCEPTION
#define I_HUI_HUI_EXCEPTION
#include <string>
#include <stdexcept>
#include <source_location>

namespace hui
{

struct HUIException : std::runtime_error {
    HUIException(std::string msg,
                 const std::source_location& loc = std::source_location::current())
      : std::runtime_error(format(msg, loc)) {}

private:
    static std::string format(const std::string& m, const std::source_location& loc) {
        return std::string(loc.file_name()) + ":" +
               std::to_string(loc.line()) + " (" +
               loc.function_name() + "): " + m;
    }
};

}; // namespace hui

#endif // I_HUI_HUI_EXCEPTION