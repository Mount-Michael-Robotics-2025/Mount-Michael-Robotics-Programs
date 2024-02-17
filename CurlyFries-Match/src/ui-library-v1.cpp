#include "vex.h"

using namespace vex;

namespace brainArt {
    class button {
        public:
            int xPosition;
            int yPosition;
            int length;
            int radius;
            color* primaryColor;
            color* secondaryColor;
            void (*additionalDraw)();
            void (*pressAction)();
    };
    class buttonHorizontal : button {
        public:

            buttonHorizontal(int _xPosition, int _yPosition, int _length, int _radius, color* _primaryColor, color* _secondaryColor, void (*_additionalDraw)(), void (*_pressAction)()) {
                xPosition = _xPosition;
                yPosition = _yPosition;
                length = _length;
                radius = _radius;
                primaryColor = _primaryColor;
                secondaryColor = _secondaryColor;
                additionalDraw = _additionalDraw;
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
                additionalDraw();
            }
    };
    class buttonVertical : button {
        public:

            buttonVertical(int _xPosition, int _yPosition, int _length, int _radius, color* _primaryColor, color* _secondaryColor, void (*_additionalDraw)(), void (*_pressAction)()) {
                xPosition = _xPosition;
                yPosition = _yPosition;
                length = _length;
                radius = _radius;
                primaryColor = _primaryColor;
                secondaryColor = _secondaryColor;
                additionalDraw = _additionalDraw;
                pressAction = _pressAction;
            }

            void pressTest(int _pressX, int _pressY) {
                if (_pressX > xPosition - radius && _pressX < xPosition + radius && _pressY > yPosition - radius && _pressY < yPosition + length + radius) {
                    pressAction();
                }
            }

            void drawToScreen() {
                Brain.Screen.setPenColor(*secondaryColor);
                Brain.Screen.setFillColor(*secondaryColor);
                Brain.Screen.drawCircle(xPosition, yPosition, radius);
                Brain.Screen.drawCircle(xPosition, yPosition + length, radius);
                Brain.Screen.drawRectangle(xPosition - radius, yPosition, radius * 2 + 1, length);
                Brain.Screen.setPenColor(*primaryColor);
                Brain.Screen.setFillColor(*primaryColor);
                Brain.Screen.drawCircle(xPosition, yPosition, radius - 2);
                Brain.Screen.drawCircle(xPosition, yPosition + length, radius - 2);
                Brain.Screen.drawRectangle(xPosition - radius + 2, yPosition, (radius - 2) * 2 + 1, length);
                Brain.Screen.setPenColor(*secondaryColor);
                Brain.Screen.setFillColor(*secondaryColor);
                Brain.Screen.drawCircle(xPosition, yPosition, radius - 4);
                Brain.Screen.drawCircle(xPosition, yPosition + length, radius - 4);
                Brain.Screen.drawRectangle(xPosition - radius + 4, yPosition, (radius - 4) * 2 + 1, length);
                additionalDraw();
            }
    };
    class sliderHorizontal : button {
        public:
            
            int limit;
            int* displayValue;

            sliderHorizontal(int _xPosition, int _yPosition, int _length, int _radius, int _limit, int* _displayValue, color* _primaryColor, color* _secondaryColor, void (*_pressAction)()) {
                xPosition = _xPosition;
                yPosition = _yPosition;
                length = _length;
                radius = _radius;
                limit = _limit;
                displayValue = _displayValue;
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
                Brain.Screen.drawCircle(xPosition, yPosition, 4);
                Brain.Screen.drawCircle(xPosition + length, yPosition, 4);
                Brain.Screen.drawRectangle(xPosition, yPosition - 4, length, 9);
                Brain.Screen.drawCircle(xPosition + ((length / (limit - 1)) * *displayValue), yPosition, radius - 6);
            }
    };
    class sliderVertical : button {
        public:
            
            int limit;
            int* displayValue;

            sliderVertical(int _xPosition, int _yPosition, int _length, int _radius, int _limit, int* _displayValue, color* _primaryColor, color* _secondaryColor, void (*_pressAction)()) {
                xPosition = _xPosition;
                yPosition = _yPosition;
                length = _length;
                radius = _radius;
                limit = _limit;
                displayValue = _displayValue;
                primaryColor = _primaryColor;
                secondaryColor = _secondaryColor;
                pressAction = _pressAction;
            }

            void pressTest(int _pressX, int _pressY) {
                if (_pressX > xPosition - radius && _pressX < xPosition + radius && _pressY > yPosition - radius && _pressY < yPosition + length + radius) {
                    pressAction();
                }
            }

            void drawToScreen() {
                Brain.Screen.setPenColor(*secondaryColor);
                Brain.Screen.setFillColor(*secondaryColor);
                Brain.Screen.drawCircle(xPosition, yPosition, radius);
                Brain.Screen.drawCircle(xPosition, yPosition + length, radius);
                Brain.Screen.drawRectangle(xPosition - radius, yPosition, radius * 2 + 1, length);
                Brain.Screen.setPenColor(*primaryColor);
                Brain.Screen.setFillColor(*primaryColor);
                Brain.Screen.drawCircle(xPosition, yPosition, radius - 2);
                Brain.Screen.drawCircle(xPosition, yPosition + length, radius - 2);
                Brain.Screen.drawRectangle(xPosition - radius + 2, yPosition, (radius - 2) * 2 + 1, length);
                Brain.Screen.setPenColor(*secondaryColor);
                Brain.Screen.setFillColor(*secondaryColor);
                Brain.Screen.drawCircle(xPosition, yPosition, 4);
                Brain.Screen.drawCircle(xPosition, yPosition + length, 4);
                Brain.Screen.drawRectangle(xPosition - 4, yPosition, 9, length);
                Brain.Screen.drawCircle(xPosition, yPosition + ((length / (limit - 1)) * *displayValue), radius - 6);
            }
    };
}