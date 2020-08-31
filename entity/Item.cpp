//
// Created by xhy on 2020/8/29.
//

#include "Item.h"
#include <string>


std::string ItemStackBase::getItemName() {
    std::string name;
    SYM_CALL(
            void(*)(ItemStackBase * , std::string *),
            MSSYM_B1QA7getNameB1AE13ItemStackBaseB2AAA4QEBAB1QA2AVB2QDA5basicB1UA6stringB1AA2DUB2QDA4charB1UA6traitsB1AA1DB1AA3stdB2AAA1VB2QDA9allocatorB1AA1DB1AA12B2AAA3stdB2AAA2XZ,
            this, &name
    );
    return name;
}

int ItemStackBase::getNum() {
    return (int) *((unsigned char *) this + 34);
}
