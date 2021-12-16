//
// Created by lilian on 16/12/2021.
//

#ifndef T_BLOC_H
#define T_BLOC_H


#include "ComplexBloc.h"

class TBloc : public ComplexBloc {
    public:
        TBloc(unsigned int nRows, unsigned int nCols) {
            // NOLINTNEXTLINE(cert-msc30-c, cert-msc50-cpp)
            Position position{rand() % (nCols-2), 0, rand() % (nRows-1)};
            blocs = {
                BasicBloc(position),
                BasicBloc(position + Position{1, 0, 0}),
                BasicBloc(position + Position{2, 0, 0}),
                BasicBloc(position + Position{1, 0, 1}),
            };
        };
};


#endif //T_BLOC_H
