#include "autonPID.h"

namespace matchAuton {
    void travelWithMirror(float lDrive, float rDrive, int mirror) {
        pid::travel((lDrive * !mirror) + (rDrive * mirror), (rDrive * !mirror) + (lDrive * mirror));
    }
    void lightL(int* mirror) {
        travelWithMirror(5, 5, *mirror);
    }
    void lightR(bool* mirror) {

    }
    void greedyL(bool* mirror) {
        
    }
    void greedyR(bool* mirror) {

    }
}