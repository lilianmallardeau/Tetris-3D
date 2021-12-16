//
// Created by lilian on 14/12/2021.
//

#ifndef BLOC_H
#define BLOC_H

struct Position {
    unsigned int x, y, z;
};

class Bloc {
    public:
        virtual void push() = 0;
        virtual void moveLeft() = 0;
        virtual void moveRight() = 0;
        virtual void moveUp() = 0;
        virtual void moveDown() = 0;
};


#endif //BLOC_H
