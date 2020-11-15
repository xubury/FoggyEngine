#ifndef CONVERTER_HPP
#define CONVERTER_HPP

namespace foggy {
namespace converter {

constexpr double PIXELS_PER_METERS = 32.0;

constexpr double PI = 3.14159265358979323846;

template <typename T>
inline constexpr T PixelsToMeters(const T& x) {
    return x / PIXELS_PER_METERS;
}

template <typename T>
inline constexpr T MetersToPixels(const T& x) {
    return x * PIXELS_PER_METERS;
}

template <typename T>
inline constexpr T DegToRad(const T& x) {
    return x * PI / 180;
}

template <typename T>
inline constexpr T RadToDeg(const T& x) {
    return x * 180 / PI;
}

} /* namespace converter */
} /* namespace foggy */

#endif
