#ifndef MOVE_H
#define MOVE_H

#endif // MOVE_H

class Move
{
    public:
        int x1;
        int y1;
        int x2;
        int y2;
        bool isJump;
        Move(int x1, int y1, int x2, int y2, bool isJump) {
            this->x1 = x1;
            this->y1 = y1;
            this->x2 = x2;
            this->y2 = y2;
            this->isJump = isJump;
        };
};
