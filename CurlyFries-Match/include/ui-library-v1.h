#include "vex.h"

using namespace vex;

namespace brainArt {
    class buttonHorizontal {
        public:
            int xPosition;
            int yPosition;
            int length;
            int radius;
            color primaryColor;
            color secondaryColor;
            void (*pressAction)();

            buttonHorizontal(int _xPosition, int _yPosition, int _length, int _radius, color _primaryColor, color _secondaryColor, void _pressAction());

            void pressTest(int _pressX, int _pressY);

            void drawToScreen();
    };
}