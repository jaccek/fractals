#include <cstdio>
#include "../qttest/common_class.h"

class LibClass : public CommonClass
{
public:
    virtual ~LibClass() {}

    virtual void printNumber(int number)
    {
        printf("printNumber(%d)\n", number);
    }
};

extern "C" CommonClass* getClass()
{
    return new LibClass();
}
