//
// Created by xhy on 2020/8/24.
//

#ifndef TRAPDOOR_MSGBUILDER_H
#define TRAPDOOR_MSGBUILDER_H

#include <map>
#include <vector>
#include <string>
#include "graphics/BlockPos.h"
#include "graphics/Vec3.h"
#include "graphics/AABB.h"
#include "Message.h"
#include <cstdarg>

namespace trapdoor {
    class Actor;

    class MessageBuilder {
    public:
        static const uint8_t DARK_READ;
        static const uint8_t RED;
        static const uint8_t GOLD;
        static const uint8_t YELLOW;
        static const uint8_t GREEN;
        static const uint8_t AQUA;
        static const uint8_t BLUE;
        static const uint8_t LIGHT_PURPLE;
        static const uint8_t WHITE;
        static const uint8_t GRAY;
        static const uint8_t BLACK;

        static const uint8_t BOLD;
        static const uint8_t ITALIC;
        static const uint8_t RESET;


        MessageBuilder &text(const std::string &s);


        template<typename ...Args>
        MessageBuilder &textF(const std::string &format, Args ...args) {
            this->text(trapdoor::format(format, args...));
            return *this;
        }

        template<typename ...Args>
        MessageBuilder &sTextF(uint8_t style, const std::string &format, Args ...args) {
            this->sText(trapdoor::format(format, args...), style);
            return *this;
        }

        MessageBuilder &sText(const std::string &s, uint8_t style);

        MessageBuilder &pos(const BlockPos &pos);

        template<typename T>
        MessageBuilder &num(T x) {
            if (std::is_arithmetic<T>()) {
                if (std::is_floating_point<T>()) {
                    char buffer[32];
                    sprintf(buffer, "%.3f", (double) x);
                    std::string s(buffer);
                    sText(s, GREEN | BOLD);
                } else {
                    sText(std::to_string(x), GREEN | BOLD);
                }
            }
            return *this;
        }

        MessageBuilder &vec3(const Vec3 &vec3);

        MessageBuilder &aabb(AABB aabb);


        std::string get();

        void send(Actor *player);

        void broadcast();

        void operator+=(const std::string &str) {
            this->text(str);
        }


    private:
        const static std::map<uint8_t, std::string> STYLE_MAP;
        std::vector<std::string> messageBuffer;
    };

    typedef MessageBuilder MSG_COLOR;
}
#endif //TRAPDOOR_MSGBUILDER_H
