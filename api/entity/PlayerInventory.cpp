//
// Created by xhy on 2020/12/8.
//

#include "PlayerInventory.h"
#include "lib/mod.h"
#include "lib/SymHook.h"
#include "Item.h"

namespace trapdoor {
    using namespace SymHook;

    size_t PlayerInventory::getContainerSize() {
        return SYM_CALL(
                size_t(*)(PlayerInventory * , int),
                MSSYM_B1QE16getContainerSizeB1AE15PlayerInventoryB2AAE18QEBAHW4ContainerIDB3AAAA1Z,
                this,
                0
        );
    }

    ItemStackBase *PlayerInventory::getItem(size_t index) {
        return SYM_CALL(
                ItemStackBase * (*)(PlayerInventory * , size_t, int),
                MSSYM_B1QA7getItemB1AE15PlayerInventoryB2AAE17QEBAAEBVItemStackB2AAE14HW4ContainerIDB3AAAA1Z,
                this,
                index,
                0
        );
    }

    void PlayerInventory::setItem(size_t index, ItemStackBase *stack) {
        SYM_CALL(
                void(*)(PlayerInventory * , size_t, ItemStackBase *, int),
                MSSYM_B1QA7setItemB1AE15PlayerInventoryB2AAE19QEAAXHAEBVItemStackB2AAE13W4ContainerIDB3AAUA1NB1AA1Z,
                this,
                index,
                stack,
                0
        );
    }


    void PlayerInventory::swapItem(size_t idx1, size_t idx2) {
        auto index = this->findEmptySlot();
        if (index == -1)return;
        this->setItem(index, this->getItem(idx1));
        this->setItem(idx1, this->getItem(idx2));
        this->setItem(idx2, this->getItem(index));
        this->getFillingContainer()->clearSlot(index);
    }

    size_t PlayerInventory::findEmptySlot() {
        return containsItem("");
    }

    int PlayerInventory::containsItem(const std::string &itemName) {
        auto size = this->getContainerSize();
        for (auto i = 0; i < size; i++) {
            if (this->getItem(i)->getItemName() == itemName)
                return i;
        }
        return -1;
    }

    FillingContainer *PlayerInventory::getFillingContainer() {
        //! ServerPlayer::selectItem
        auto ptr = reinterpret_cast<char *>(this) + 176;
        return reinterpret_cast<FillingContainer *>(ptr);
    }


    int PlayerInventory::getSelectSlot() {

        auto ptr = SYM_CALL(char*(*)(PlayerInventory * ),
                            MSSYM_B1QE15getSelectedSlotB1AE15PlayerInventoryB2AAA4QEBAB1QE10AUSlotDataB1AA11B1AA2XZ,
                            this
        );
        //这个api是有问题的
        //return 0;
        return *(int *) (ptr + 4);
    }

    void FillingContainer::clearSlot(int idx) {
        SYM_CALL(
                void(*)(FillingContainer * , int),
                MSSYM_B1QA9clearSlotB1AE16FillingContainerB2AAA6UEAAXHB1AA1Z,
                this,
                idx
        );
    }

}
