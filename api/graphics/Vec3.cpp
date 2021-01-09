//
// Created by xhy on 2020/10/22.
//

#include "Vec3.h"
#include "BlockPos.h"

namespace trapdoor {
    Vec3::Vec3(int _x) : Vec3(_x, _x, _x) {}

    Vec3::Vec3(float _x) : Vec3(_x, _x, _x) {}

    float Vec3::distanceTo(const Vec3 &vec3) const {
        return sqrt((vec3.x - x) * (vec3.x - x) +
                    (vec3.y - y) * (vec3.y - y) +
                    (vec3.z - z) * (vec3.z - z));
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
		auto cx = x < 0 ? x - 1 : x;
		auto cy = y < 0 ? y - 1 : y;
		auto cz = z < 0 ? z - 1 : z;
		return {cx, cy, cz};
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

    bool Vec3::operator<(const Vec3 &rhs) const {
        if (x < rhs.x)
            return true;
        if (rhs.x < x)
            return false;
        if (y < rhs.y)
            return true;
        if (rhs.y < y)
            return false;
        return z < rhs.z;
    }

    Vec3 Vec3::operator+(const Vec3 &v) const {
        return {this->x + v.x, this->y + v.y, this->z + v.z};
    }

    Vec3 Vec3::operator-(const Vec3 &v) const {
        return {this->x - v.x, this->y - v.y, this->z - v.z};
    }

    Vec3 Vec3::operator*(float times) const {
        return {x * times, y * times, z * times};
    }
}