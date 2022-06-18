#include <tuple>

class colour
{
public:
    colour() = default;
    colour(int r, int g, int b): r(r), g(g), b(b) {}
    ~colour() = default;

    std::tuple<int,int,int> get_rgb();

private:
    int r;
    int g;
    int b;
};