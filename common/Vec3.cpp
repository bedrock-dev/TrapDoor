//
// Created by xhy on 2020/10/22.
//

#include "Vec3.h"
#include "BlockPos.h"

std::string facingToString(FACING facing) {
    switch (facing) {
        case FACING::POS_X:
            return "+x";
        case FACING::NEG_X:
            return "-x";
        case FACING::POS_Y:
            return "+y";
        case FACING::POS_Z:
            return "+z";
        case FACING::NEG_Y:
            return "-y";
        case FACING::NEG_Z:
            return "-z";
        default:
            return "unknown";
    }
}

std::string facingToDirString(FACING facing) {
    switch (facing) {
        case FACING::POS_X:
            return "west";
        case FACING::NEG_X:
            return "east";
        case FACING::POS_Y:
            return "up";
        case FACING::POS_Z:
            return "south";
        case FACING::NEG_Y:
            return "down";
        case FACING::NEG_Z:
            return "north";
        default:
            return "unknown";
    }
}

Vec3::Vec3(int _x) : Vec3(_x, _x, _x) {}

Vec3::Vec3(float _x) : Vec3(_x, _x, _x) {}

float Vec3::distanceTo(const Vec3 &vec3) const {
    return (vec3.x - x) * (vec3.x - x) +
           (vec3.y - y) * (vec3.y - y) +
           (vec3.z - z) * (vec3.z - z);
}

std::string Vec3::toString() const {
    char buffer[64];
    sprintf(buffer, "[%.2f %.2f %.2f]", x, y, z);
    return std::string(buffer);
}

bool Vec3::operator!=(const Vec3 &v) const {
    return x != v.x || y != v.y || z != v.z;
}

bool Vec3::operator==(const Vec3 &v) const {
    return x == v.x && y == v.y && z == v.z;
}

BlockPos Vec3::toBlockPos() const {
    return {x, y, z};
}

std::string Vec3::toDirString() const {
    FACING fx = this->x > 0 ? FACING::POS_X : FACING::NEG_X;
    FACING fz = this->x > 0 ? FACING::POS_Z : FACING::NEG_Z;
    std::string s;
    if (abs(this->x) >= abs(this->z)) {
        s = facingToDirString(fx);
        s += " (";
        s += facingToString(fx);
        s += ")";
    } else if (1.732 * abs(this->z) > abs(this->x)) {
        s = facingToDirString(fz);
        s += " (";
        s += facingToString(fz);
        s += ")";
    }
    return s;
}
