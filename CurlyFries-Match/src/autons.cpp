#include "autonPID.h"

namespace matchAuton {
    void lightP(int* mirror) {
        DrivetrainAll.setVelocity(25, pct);
        Intake.setVelocity(100, pct);
        Belt.setVelocity(100, pct);
        GoalClamp.set(false);
        directMove::travelInches(-32, -32, *mirror);
        GoalClamp.set(true);
        directMove::travelInches(12, 12, *mirror);
        directMove::travelInches(0, 22, *mirror);
        directMove::travelInches(8, 8, *mirror);
        directMove::travelInches(0, 22, *mirror);
        directMove::travelInches(12, 12, *mirror, false);
        Intake.spinFor(20 * 360, deg, false);
        Belt.spinFor((20 * 360), deg);
        directMove::travelInches(-12, 12, *mirror);
        directMove::travelInches(48, 6, *mirror);
        DrivetrainAll.setVelocity(100, pct);
    }
    void lightN(int* mirror) {
        DrivetrainAll.setVelocity(25, pct);
        Intake.setVelocity(100, pct);
        Belt.setVelocity(100, pct);
        Belt.setVelocity(100, pct);
        GoalClamp.set(false);
        directMove::travelInches(-32, -32, *mirror);
        GoalClamp.set(true);
        directMove::travelInches(12, 12, *mirror);
        directMove::travelInches(22, 0, *mirror);
        directMove::travelInches(8, 8, *mirror);
        directMove::travelInches(22, 0, *mirror);
        directMove::travelInches(12, 12, *mirror, false);
        Intake.spinFor(20 * 360, deg, false);
        Belt.spinFor((20 * 360), deg);
        directMove::travelInches(12, -12, *mirror);
        directMove::travelInches(48, 6, *mirror);
        DrivetrainAll.setVelocity(100, pct);
    }
    void greedyP(int* mirror) {
        
    }
    void greedyN(int* mirror) {

    }
}
namespace skillsAuton {
    
}