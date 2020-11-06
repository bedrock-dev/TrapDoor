//
// Created by xhy on 2020/10/22.
//

#include "Vec3.h"
#include "BlockPos.h"

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
