#include "deriveddata.h"

void DerivedData::SetValue(int tmp)
{
    value = tmp;
}

int DerivedData::GetValue()
{
    return value;
}

double DerivedData::GetBaseValue()
{
    return base_value;
}
