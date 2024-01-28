#include "vex.h"

using namespace vex;

namespace brainArt {
    class buttonHorizontal {
        public:
            int xPosition;
            int yPosition;
            int length;
            int radius;
            void (*press)();

            buttonHorizontal(int _xPosition, int _yPosition, int _length, int _radius, void _press()) {
                xPosition = _xPosition;
                yPosition = _yPosition;
                length = _length;
                radius = _radius;
                press = _press;
            }
    };
}