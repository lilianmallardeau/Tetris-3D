//
// Created by lilian on 14/12/2021.
//

#ifndef BASIC_BLOC_H
#define BASIC_BLOC_H


#include <cstdlib>
#include "Bloc.h"

class BasicBloc : public Bloc {
    private:
        Position position{};

    public:
        BasicBloc() : position{} {};
        explicit BasicBloc(Position position) : position(position) {};
        // NOLINTNEXTLINE(cert-msc30-c, cert-msc50-cpp)
        BasicBloc(unsigned int nRows, unsigned int nCols) : position{rand() % nCols, 0, rand() % nRows} {};

        void push() override {++position.y;};
        void moveLeft() override {--position.x;};
        void moveRight() override {++position.x;};
        void moveUp() override {++position.z;};
        void moveDown() override {--position.z;};

        friend class ComplexBloc;
        friend class NavigationGrid;
        friend class Game;
};


#endif //BASIC_BLOC_H
