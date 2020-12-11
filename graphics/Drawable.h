//
// Created by xhy on 2020/12/11.
//

#ifndef TRAPDOOR_DRAWABLE_H
#define TRAPDOOR_DRAWABLE_H

#include "Vec3.h"
#include "BlockPos.h"
#include <array>

namespace graphics {
    enum COLOR {
        WHITE,
        RED,
        BLUE,
        GREEN,
        YELLOW
    };
    const int DRAW_FREQ = 40;

    class Drawable {
    private:
        unsigned long long timer = 0;
    protected:
        explicit Drawable(COLOR _color) : color(_color) {}

        Drawable() = default;

        const COLOR color = WHITE;

        virtual void draw() const = 0;

    public:
        void tick();
    };

    class Point : public Drawable {
        BlockPos point;

        void draw() const override;
    };

    class Line : public Drawable {
        friend class Rectangle;

        friend class AABBox;

        BlockPos originPoint{};
        FACING direction{};

        void draw() const override;

        Line(const BlockPos pos, FACING dir, COLOR color = WHITE) : Drawable(color), direction(dir), originPoint(pos) {}


        //强制把任意两点坐标转换为平行坐标轴的坐标
        //水平坐标如果不一样以低的那个个为准
        Line(const BlockPos &p1, const BlockPos &p2, FACING facing, COLOR color = WHITE)
                : Drawable(color) {
            if (facing == FACING::NEG_Y || facing == FACING::POS_Y) {
                if(p1.y > p2.y){
                    //swap
                }
            } else if (facing == FACING::NEG_X || facing == FACING::POS_X) {

            } else {

            }
        }

    };

    class Rectangle : public Drawable {
        std::array<Line, 4> lines;

        void draw() const override;
    };

    class AABBox : Drawable {
        std::array<Line, 4> lines;

        void draw() const override;
    };

}


#endif //TRAPDOOR_DRAWABLE_H
