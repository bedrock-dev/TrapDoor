//
// Created by xhy on 2020/12/8.
//

#ifndef TRAPDOOR_PLAYERINVENTORY_H
#define TRAPDOOR_PLAYERINVENTORY_H

#include <string>

namespace trapdoor {
    class ItemStackBase;

    class FillingContainer {
    public:
        void clearSlot(int);
    };

    class PlayerInventory {
    public:
        size_t getContainerSize();

        ItemStackBase *getItem(size_t index);

        void setItem(size_t index, ItemStackBase *stack);

        void swapItem(size_t idx1, size_t idx2);

        size_t findEmptySlot();

        FillingContainer *getFillingContainer();

        int containsItem(const std::string &itemName);

        int getSelectSlot();
    };
}


#endif //TRAPDOOR_PLAYERINVENTORY_H
