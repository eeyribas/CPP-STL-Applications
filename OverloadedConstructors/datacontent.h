#ifndef DATACONTENT_H
#define DATACONTENT_H

class DataContent
{
public:
    unsigned char value_1;
    double value_2;
    int value_3;
    double value_4[3];
    bool value_5;

    DataContent()
    {
        value_1 = 0;
        value_2 = 0;
        value_3 = 0;
        for (int i = 0; i < 3; i++)
            value_4[i] = 0;
        value_5 = false;
    }

    DataContent(unsigned char tmp_value_1)
    {
        value_1 = tmp_value_1;
    }

    DataContent(unsigned char tmp_value_1, double tmp_value_2)
    {
        value_1 = tmp_value_1;
        value_2 = tmp_value_2;
    }

    DataContent(unsigned char tmp_value_1, double tmp_value_2,
                int tmp_value_3)
    {
        value_1 = tmp_value_1;
        value_2 = tmp_value_2;
        value_3 = tmp_value_3;
    }

    DataContent(unsigned char tmp_value_1, double tmp_value_2,
                int tmp_value_3, double tmp_value_4[])
    {
        value_1 = tmp_value_1;
        value_2 = tmp_value_2;
        value_3 = tmp_value_3;
        for (int i = 0; i < 3; i++)
            value_4[i] = tmp_value_4[i];
    }

    DataContent(unsigned char tmp_value_1, double tmp_value_2,
                int tmp_value_3, double tmp_value_4[],
                bool tmp_value_5)
    {
        value_1 = tmp_value_1;
        value_2 = tmp_value_2;
        value_3 = tmp_value_3;
        for (int i = 0; i < 3; i++)
            value_4[i] = tmp_value_4[i];
        value_5 = tmp_value_5;
    }
};

#endif // DATACONTENT_H
