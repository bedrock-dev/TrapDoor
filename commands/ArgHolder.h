//
// Created by xhy on 2020/10/23.
//

#ifndef COMMANDMANAGER_ARGTYPE_H
#define COMMANDMANAGER_ARGTYPE_H


#include <string>
#include <utility>
using std::string;
union ArgHolder {
    int intVal = 0;
    float floatVal;
    std::string strVal;
    bool boolVal;
public:
    explicit ArgHolder(int arg) : intVal(arg) {}

    explicit ArgHolder(float arg) : floatVal(arg) {}

    explicit ArgHolder(std::string arg) : strVal(std::move(arg)) {}

    explicit ArgHolder(bool arg) : boolVal(arg) {}

    ~ArgHolder() { strVal.~string(); };

    int getInt() const;

    float getFloat() const;


    string getString() const;

    bool getBool() const;

};

ArgHolder *integerArg(int val);

ArgHolder *floatArg(float val);

ArgHolder *strArg(const std::string &val);

ArgHolder *boolArg(bool val);

#endif //COMMANDMANAGER_ARGTYPE_H
