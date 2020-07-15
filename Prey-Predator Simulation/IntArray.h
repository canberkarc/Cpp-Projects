#ifndef INTARRAY_H
#define INTARRAY_H


class IntArray
{
public:
    IntArray();
    ~IntArray();
    int getAt(int position)const;
    void append(int value);
    int size()const;
    bool contains(int value);

private:
    int * innerArray;
    int length;
};

#endif // INTARRAY_H
