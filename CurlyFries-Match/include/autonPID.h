#include "vex.h"

using namespace vex;

namespace pid {
    void rotate(float goalInches, int timeLimit = 0);
}
namespace directMove {
  void travelInches(float lInches, float rInches, int mirror);
  void travelInches(float lInches, float rInches, int mirror, bool cont);
}