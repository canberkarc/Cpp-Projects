#ifndef POSITION_H
#define POSITION_H


class Position
{
public:
    Position();
    Position(int x, int y);
    bool isEquals(Position pos);
    int getXPos() const;
    void setXPos(int value);

    int getYPos() const;
    void setYPos(int value);

private:
    int xPos;
    int yPos;
};

#endif // POSITION_H
