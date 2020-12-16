//
// Created by xhy on 2020/10/23.
//

#ifndef COMMANDMANAGER_ARGTYPE_H
#define COMMANDMANAGER_ARGTYPE_H


#include <string>
#include <utility>

/*
 * 用来承载命令行玩家参数的结构体，本来打算用union的，结果发现有bug，就算了，
 * 浪费点内存问题不大.jpg
 */
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

ArgHolder *integerArg(int val);

ArgHolder *strArg(const std::string &val);

ArgHolder *boolArg(bool val);

#endif //COMMANDMANAGER_ARGTYPE_H
