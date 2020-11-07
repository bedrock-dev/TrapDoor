//
// Created by xhy on 2020/10/23.
//

#ifndef COMMANDMANAGER_ARGTYPE_H
#define COMMANDMANAGER_ARGTYPE_H


#include <string>
#include <utility>

using std::string;

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


    string getString() const;

    bool getBool() const;

};

ArgHolder *integerArg(int val);

ArgHolder *strArg(const std::string &val);

ArgHolder *boolArg(bool val);

#endif //COMMANDMANAGER_ARGTYPE_H
