#ifndef CONVERTER_HPP
#define CONVERTER_HPP

namespace foggy {
namespace converter {

constexpr double PIXELS_PER_METERS = 32.0;

constexpr double PI = 3.14159265358979323846;

template <typename T>
inline constexpr T pixelsToMeters(const T& x) {
    return x / PIXELS_PER_METERS;
}

template <typename T>
inline constexpr T metersToPixels(const T& x) {
    return x * PIXELS_PER_METERS;
}

template <typename T>
inline constexpr T degToRad(const T& x) {
    return x * PI / 180;
}

template <typename T>
inline constexpr T radToDeg(const T& x) {
    return x * 180 / PI;
}

} /* namespace converter */
} /* namespace foggy */

#endif /* CONVERTER_HPP */
