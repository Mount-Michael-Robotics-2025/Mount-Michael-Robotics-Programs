#include <vector>
#include <cmath>
#include <vex.h>

namespace differential {
    std::vector<std::vector<double>> getTransformationMatrix(double deltaR, double deltaL, double width) {
        double icr = (width / 2) * (deltaR + deltaL) / (deltaR - deltaL);
        double deltaTheta = deltaR / ((icr / 2) + icr);
        double cosTheta = std::cos(deltaTheta);
        double sinTheta = std::sin(deltaTheta);
        double deltaX = -icr + (icr * cosTheta);
        double deltaY = icr * sinTheta;

        return {
            {cosTheta, -sinTheta, deltaX},
            {sinTheta, cosTheta, deltaY},
            {0, 0, 1}
        };
    }
}

namespace odometry {
    std::vector<std::vector<double>> globalTransformationMatrix = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };

    void reset(double x, double y, double theta) {
        double cosTheta = std::cos(theta);
        double sinTheta = std::sin(theta);
        globalTransformationMatrix = {
            {cosTheta, -sinTheta, x},
            {sinTheta, cosTheta, y},
            {0, 0, 1}
        };
    }

    std::vector<std::vector<double>> multiplyMatrices(const std::vector<std::vector<double>>& A, const std::vector<std::vector<double>>& B) {
        std::vector<std::vector<double>> result(3, std::vector<double>(3, 0));
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                for (int k = 0; k < 3; ++k) {
                    result[i][j] += A[i][k] * B[k][j];
                }
            }
        }
        return result;
    }

    void updateGlobalPosition(double deltaR, double deltaL) {
        std::vector<std::vector<double>> deltaMatrix = differential::getTransformationMatrix(deltaR, deltaL, 12);
        globalTransformationMatrix = multiplyMatrices(globalTransformationMatrix, deltaMatrix);
    }

    void track() {
        double previousPositionL = 0;
        double previousPositionR = 0;
        double currentPositionL = DrivetrainL.position(degrees); 
        double currentPositionR = DrivetrainR.position(degrees);

        double deltaL = currentPositionL - previousPositionL;
        double deltaR = currentPositionR - previousPositionR;

        updateGlobalPosition(deltaR, deltaL);

        previousPositionL = currentPositionL;
        previousPositionR = currentPositionR;
    }
}