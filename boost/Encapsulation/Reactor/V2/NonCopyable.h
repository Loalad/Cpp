#ifndef __NONCOPYABLE_H__
#define __NONCOPYABLE_H__

class NonCopyable {
protected:
    NonCopyable() {}
    ~NonCopyable() {}

    NonCopyable(const NonCopyable &rhs) = delete;
    NonCopyable &operator=(const NonCopyable &rhs) = delete;
};



#endif

