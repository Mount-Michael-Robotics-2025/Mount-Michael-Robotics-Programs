#include <vector>
#include <cmath>

namespace differential {
    std::vector<std::vector<double>> getTransformationMatrix(double deltaR, double deltaL, double width);
}

namespace odometry {
    extern std::vector<std::vector<double>> globalTransformationMatrix;

    void reset(double x, double y, double theta);
}
