//
// Created by xhy on 2020/12/12.
//

#include "Graphics.h"
#include "Particle.h"
#include <string>

std::map<float, int> graphics::binSplit(float start, float end) {
    std::map<float, int> lengthMap;
    int length = static_cast<int>(end - start);
    const int defaultLength = 8;
    int numOf8 = length / defaultLength;
    for (auto i = 0; i < numOf8; i++) {
        auto point = static_cast<float>(1.0 * i * defaultLength + start + 4);
        lengthMap.insert({point, defaultLength});
    }


    for (auto j = numOf8 * defaultLength + static_cast<int>(start); j < end; j++) {
        lengthMap.insert({1.0 * j + 0.5, 1});
    }
    return lengthMap;
}


void graphics::drawLine(const Vec3 &originPoint, FACING direction, float length, COLOR color) {
    if (length <= 0)return;
    float start = 0, end = 0;
    switch (direction) {
        case FACING::NEG_Y:
            start = originPoint.y - length;
            end = originPoint.y;
            break;
        case FACING::POS_Y:
            start = originPoint.y;
            end = originPoint.y + length;
            break;
        case FACING::NEG_Z:
            start = originPoint.z - length;
            end = originPoint.z;
            break;
        case FACING::POS_Z:
            start = originPoint.z;
            end = originPoint.z + length;
            break;
        case FACING::NEG_X:
            start = originPoint.x - length;
            end = originPoint.x;
            break;
        case FACING::POS_X:
            start = originPoint.x;
            end = originPoint.x + length;
            break;
    }
    //split point list;

    auto list = binSplit(start, end);
    auto particleType8 = getLineParticleType(8, direction, color);
    auto particleType8_1 = getLineParticleType(8, invFacing(direction), color);
    auto particleType1 = getLineParticleType(1, direction, color);
    auto particleType8_2 = getLineParticleType(8, invFacing(direction), color);
    std::map<Vec3, int> positionList;
    if (facingIsX(direction)) {
        for (auto i:list)
            positionList.insert({{i.first, originPoint.y, originPoint.z}, i.second});
    } else if (facingIsY(direction)) {
        for (auto i:list)
            positionList.insert({{originPoint.x, i.first, originPoint.z}, i.second});
    } else if (facingIsZ(direction)) {
        for (auto i:list)
            positionList.insert({{originPoint.x, originPoint.y, i.first}, i.second});
    }

    for (auto points: positionList) {
        if (points.second == 8) {
            spawnParticle(points.first, particleType8);
            spawnParticle(points.first, particleType8_2);
            //  std::cout << "spawn particle (" << particleType8 << ") at" << points.first.toString() << "\n";
        } else if (points.second == 1) {
            spawnParticle(points.first, particleType1);
            spawnParticle(points.first, particleType8_2);
            // std::cout << "spawn particle (" << particleType1 << ") at" << points.first.toString() << "\n";
        }
    }
}

std::string graphics::getLineParticleType(int length, FACING direction, graphics::COLOR color) {
    std::string str = "trapdoor:line";
    str += std::to_string(length);
    switch (direction) {
        case FACING::NEG_Y:
            str += "Yp";
            break;
        case FACING::POS_Y:
            str += "Ym";
            break;
        case FACING::NEG_Z:
            str += "Zp";
            break;
        case FACING::POS_Z:
            str += "Zm";
            break;
        case FACING::NEG_X:
            str += "Xp";
            break;
        case FACING::POS_X:
            str += "Xm";
            break;
    }

    switch (color) {
        case COLOR::WHITE:
            str += "W";
            break;
        case COLOR::RED:
            str += "R";
            break;
        case COLOR::YELLOW:
            str += "Y";
            break;
        case COLOR::BLUE:
            str += "B";
            break;
        case COLOR::GREEN:
            str += "G";
            break;
    }
    // return "minecraft:dragon_breath_trail";
    return str;
}
