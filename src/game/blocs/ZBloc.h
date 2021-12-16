//
// Created by lilian on 16/12/2021.
//

#ifndef Z_BLOC_H
#define Z_BLOC_H


#include "ComplexBloc.h"

class ZBloc : public ComplexBloc {
    public:
        ZBloc(unsigned int nRows, unsigned int nCols) {
            // NOLINTNEXTLINE(cert-msc30-c, cert-msc50-cpp)
            Position position{rand() % (nCols-2), 0, rand() % (nRows-1)};
            blocs = {
                BasicBloc(position),
                BasicBloc(position + Position{1, 0, 0}),
                BasicBloc(position + Position{1, 0, 1}),
                BasicBloc(position + Position{2, 0, 1}),
            };
        };
};


#endif //Z_BLOC_H
