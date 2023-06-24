#include <utility> // for std::pair

class Pixel {
    unsigned x, y;
    inline static unsigned screen_x = 640, screen_y = 480; // only one instance of these variables
public:
    Pixel(unsigned x, unsigned y) {
        setX(x);
        setY(y);
    }
    Pixel& setX(unsigned new_x) {
        x = (new_x < screen_x) ? new_x : screen_x - 1;
        return *this;
    }
    Pixel& setY(unsigned new_y) {
        y = (new_y < screen_y) ? new_y : screen_y - 1;
        return *this;
    }
    const std::pair<unsigned,unsigned> getXY() const {
        return { x, y };
    }
    static void setScreen(unsigned sx, unsigned sy) {
        screen_x = sx;
        screen_y = sy;
        // assume screen cleared and all Pixels deleted
    }
};

int main() {
    Pixel::setScreen(800, 600);
    Pixel p(20, 50);
    p.setX(100).setY(200);
    auto [ px, py ] = p.getXY();
}
