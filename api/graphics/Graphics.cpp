//
// Created by xhy on 2020/12/12.
//

#include <string>
#include "Graphics.h"
#include "Particle.h"
#include "Vec3.h"
#include "BDSMod.h"

namespace trapdoor {

    namespace {
        //把整数进行二进制分割，获取粒子的生成坐标
        std::map<float, int> binSplit(float start, float end) {
            std::map<float, int> lengthMap;
            int length = static_cast<int>(end - start);
            while (length >= 512) {
                length -= 256;
                auto point = static_cast<float>(128.0 + start);
                start += 256.0;
                lengthMap.insert({point, 256});
            }

            for (auto defaultLength = 256; defaultLength >= 1; defaultLength /= 2) {
                if (length >= defaultLength) {
                    length -= defaultLength;
                    auto point = static_cast<float>(0.5 * defaultLength + start);
                    start += defaultLength;
                    lengthMap.insert({point, defaultLength});
                }
            }
            return lengthMap;
        }

        std::string getLineParticleType(int length,
                                        FACING direction,
                                        GRAPHIC_COLOR color) {
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
                case GRAPHIC_COLOR::WHITE:
                    str += "W";
                    break;
                case GRAPHIC_COLOR::RED:
                    str += "R";
                    break;
                case GRAPHIC_COLOR::YELLOW:
                    str += "Y";
                    break;
                case GRAPHIC_COLOR::BLUE:
                    str += "B";
                    break;
                case GRAPHIC_COLOR::GREEN:
                    str += "G";
                    break;
            }
            return str;
        }
    }


    void drawLine(const Vec3 &originPoint,
                  FACING direction,
                  float length,
                  GRAPHIC_COLOR color, int dimType) {
        if (length <= 0)
            return;
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
        // split point list;

        auto list = binSplit(start, end);
        std::map<Vec3, int> positionList;
        if (facingIsX(direction)) {
            for (auto i : list)
                positionList.insert(
                        {{i.first, originPoint.y, originPoint.z}, i.second});
        } else if (facingIsY(direction)) {
            for (auto i : list)
                positionList.insert(
                        {{originPoint.x, i.first, originPoint.z}, i.second});
        } else if (facingIsZ(direction)) {
            for (auto i : list)
                positionList.insert(
                        {{originPoint.x, originPoint.y, i.first}, i.second});
        }

        for (auto points : positionList) {
            auto particleType =
                    getLineParticleType(points.second, direction, color);
            auto particleTypeInv =
                    getLineParticleType(points.second, invFacing(direction), color);
            spawnParticle(points.first, particleType, dimType);
            if (!bdsMod->getCfg().particlePerformanceMode)
                spawnParticle(points.first, particleTypeInv, dimType);
        }
    }
}
