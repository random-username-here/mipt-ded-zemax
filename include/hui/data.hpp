/**
 * @file
 * @brief Misc. utility data structures.
 */
#ifndef I_HUI_DATA
#define I_HUI_DATA

namespace hui {

/**
 * @brief Some value which can differ for diffrent borders of rectangle.
 * For example, border width, or margins.
 */
template<typename T>
struct BorderMapped {

    // In clockwise order
    T top, right, bottom, left;

    BorderMapped(T top_, T right_, T left_, T bottom_)
        :top(top_), right(right_), bottom(bottom_), left(left_) {}

    BorderMapped(T vert, T horz)
        :top(vert), right(horz), bottom(vert), left(horz) {}

    BorderMapped(T value)
        :top(value), right(value), bottom(value), left(value) {}

    BorderMapped() = default;

};

}; // namespace hui

#endif // I_HUI_DATA
