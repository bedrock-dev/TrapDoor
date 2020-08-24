//
// Created by xhy on 2020/8/24.
//

#ifndef TRAPDOOR_MESSAGEBUILDER_H
#define TRAPDOOR_MESSAGEBUILDER_H

#include <vector>
#include <string>

class MessageBuilder {
public:
    MessageBuilder &Text(const std::string &s) {
        messageBuffer.emplace_back(s);
        return *this;
    }
    MessageBuilder &pos(){

    }
    const static std::string POS_COLOR;
private:
    std::vector<std::string> messageBuffer;
};


#endif //TRAPDOOR_MESSAGEBUILDER_H
