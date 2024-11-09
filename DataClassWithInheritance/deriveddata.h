#ifndef DERIVEDDATA_H
#define DERIVEDDATA_H

#include <iostream>
#include "basedata.h"

class DerivedData : public BaseData
{
public:
    void SetValue(int tmp);
    int GetValue();
    double GetBaseValue();

private:
    int value;
};

#endif // DERIVEDDATA_H
