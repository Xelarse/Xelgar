#include "colour.hpp"

std::tuple<int,int,int> colour::get_rgb() {
    return std::tuple<int,int,int>{r, g, b};
}