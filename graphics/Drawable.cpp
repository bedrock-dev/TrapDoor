//
// Created by xhy on 2020/12/11.
//

#include "Drawable.h"

namespace graphics {
    void Drawable::tick() {
        this->timer++;
        if (this->timer == DRAW_FREQ) {
            this->timer = 0;
            this->draw();
        }
    }


    void Point::draw() const {

    }

    void Line::draw() const {

    }

    void Rectangle::draw() const {
        for (const auto &line :lines)
            line.draw();
    }

    void AABBox::draw() const {
        for (const auto &line :lines) {
            line.draw();
        }
    }
}

