//
// Created by lilian on 14/12/2021.
//

#ifndef COMPLEX_BLOC_H
#define COMPLEX_BLOC_H


#include <vector>
#include "Bloc.h"
#include "BasicBloc.h"

class ComplexBloc : public Bloc {
    protected:
        std::vector<BasicBloc> blocs;

    public:
        void push() override {std::for_each(blocs.begin(), blocs.end(), [](BasicBloc& bloc){bloc.push();});};
        void moveLeft() override {std::for_each(blocs.begin(), blocs.end(), [](BasicBloc& bloc){bloc.moveLeft();});};
        void moveRight() override {std::for_each(blocs.begin(), blocs.end(), [](BasicBloc& bloc){bloc.moveRight();});};
        void moveUp() override {std::for_each(blocs.begin(), blocs.end(), [](BasicBloc& bloc){bloc.moveUp();});};
        void moveDown() override {std::for_each(blocs.begin(), blocs.end(), [](BasicBloc& bloc){bloc.moveDown();});};

        friend class NavigationGrid;
        friend class Game;
};


#endif //COMPLEX_BLOC_H
