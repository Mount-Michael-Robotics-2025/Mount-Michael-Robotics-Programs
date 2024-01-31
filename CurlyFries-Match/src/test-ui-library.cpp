#include "vex.h"

using namespace vex;

namespace brainArt {
    class buttonHorizontal {
        public:
            int xPosition;
            int yPosition;
            int length;
            int radius;
            color* primaryColor;
            color* secondaryColor;
            void (*pressAction)();

            buttonHorizontal(int _xPosition, int _yPosition, int _length, int _radius, color* _primaryColor, color* _secondaryColor, void _pressAction()) {
                xPosition = _xPosition;
                yPosition = _yPosition;
                length = _length;
                radius = _radius;
                primaryColor = _primaryColor;
                secondaryColor = _secondaryColor;
                pressAction = _pressAction;
            }

            void pressTest(int _pressX, int _pressY) {
                if (_pressX > xPosition - radius && _pressX < xPosition + length + radius && _pressY > yPosition - radius && _pressY < yPosition + radius) {
                    pressAction();
                }
            }

            void drawToScreen() {
                Brain.Screen.setPenColor(*secondaryColor);
                Brain.Screen.setFillColor(*secondaryColor);
                Brain.Screen.drawCircle(xPosition, yPosition, radius);
                Brain.Screen.drawCircle(xPosition + length, yPosition, radius);
                Brain.Screen.drawRectangle(xPosition, yPosition - radius, length, radius * 2 + 1);
                Brain.Screen.setPenColor(*primaryColor);
                Brain.Screen.setFillColor(*primaryColor);
                Brain.Screen.drawCircle(xPosition, yPosition, radius - 2);
                Brain.Screen.drawCircle(xPosition + length, yPosition, radius - 2);
                Brain.Screen.drawRectangle(xPosition, yPosition - radius + 2, length, (radius - 2) * 2 + 1);
                Brain.Screen.setPenColor(*secondaryColor);
                Brain.Screen.setFillColor(*secondaryColor);
                Brain.Screen.drawCircle(xPosition, yPosition, radius - 4);
                Brain.Screen.drawCircle(xPosition + length, yPosition, radius - 4);
                Brain.Screen.drawRectangle(xPosition, yPosition - radius + 4, length, (radius - 4) * 2 + 1);
            }
    };
}