//
// Created by xhy on 2020/10/23.
//

#ifndef COMMANDMANAGER_ARGTYPE_H
#define COMMANDMANAGER_ARGTYPE_H


#include <string>
#include <utility>

/*
 * @author hhhxiao
 * 用来承载命令行参数
 * 浪费点内存问题不大.jpg
 */
namespace trapdoor {
    //本来想用union的，可以减少一些内存，但是非基本类型可能会炸，用char[]又不好控制最大长度，还不如直接struct
    struct ArgHolder {
        int intVal = 0;
        std::string strVal;
        bool boolVal = true;
    public:
        explicit ArgHolder(int arg) : intVal(arg) {}

        explicit ArgHolder(const char *arg) : strVal(arg) {}

        explicit ArgHolder(bool arg) : boolVal(arg) {}

        explicit ArgHolder(std::string arg) : strVal(std::move(arg)) {}

        int getInt() const;

        std::string getString() const;

        bool getBool() const;

    };

    //y1s1下面这三个方法都可以不要了，懒得换了
    ArgHolder *integerArg(int val);

    ArgHolder *strArg(const std::string &val);

    ArgHolder *boolArg(bool val);
}
#endif //COMMANDMANAGER_ARGTYPE_H
