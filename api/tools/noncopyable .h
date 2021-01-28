//
// Created by xhy on 2021/1/11.
//

#ifndef MOD_NONCOPYABLE_H
#define MOD_NONCOPYABLE_H
//from boost
namespace trapdoor {
    class noncopyable {
    protected:
        noncopyable() {}

        ~noncopyable() {}

    private:  // emphasize the following members are private
        noncopyable(const noncopyable &);

        const noncopyable &operator=(const noncopyable &);
    };
}
typedef trapdoor::noncopyable noncopyable;
#endif //MOD_NONCOPYABLE_H

