//
// Created by lilian on 14/12/2021.
//

#include "NavigationGrid.h"

NavigationGrid::NavigationGrid(uint nRows, uint nCols, uint depth) : nRows(nRows), nCols(nCols), depth(depth) {
    grid = std::vector(depth, std::vector(nCols, std::vector(nRows, false)));

    slicesColors.reserve(depth);
    for (uint z = 0; z < depth; ++z)
        slicesColors.push_back(Color::random());
}

bool NavigationGrid::checkCollision(const BasicBloc &bloc) const {
    if (bloc.position.y >= depth-1)
        return true;
    if (grid[bloc.position.y+1][bloc.position.x][bloc.position.z])
        return true;
    return false;
}

bool NavigationGrid::checkCollision(const ComplexBloc &bloc) const {
    return std::any_of(bloc.blocs.cbegin(), bloc.blocs.cend(), [this](const BasicBloc& bloc){return this->checkCollision(bloc);});
}

void NavigationGrid::solidify(const BasicBloc &bloc) {
    grid[bloc.position.y][bloc.position.x][bloc.position.z] = true;
}

void NavigationGrid::solidify(const ComplexBloc &bloc) {
    for (const BasicBloc& basicBloc : bloc.blocs)
        solidify(basicBloc);
}

bool NavigationGrid::isSliceFull(unsigned int slice) const {
    for (uint x = 0; x < nCols; ++x)
        for (uint z = 0; z < nRows; ++z)
            if (!grid[slice][x][z])
                return false;
    return true;
}

void NavigationGrid::removeSlice(unsigned int slice) {
    for (uint i = slice; i > 0; --i) {
        grid[i] = grid[i - 1];
        slicesColors[i] = slicesColors[i-1];
    }
    grid[0] = std::vector(nCols, std::vector(nRows, false));
    slicesColors[0] = Color::random();
}

void NavigationGrid::removeFullSlices() {
    for (uint slice = 0; slice < depth; ++slice)
        if (isSliceFull(slice))
            removeSlice(slice);
}

bool NavigationGrid::canMove(const BasicBloc &bloc, Direction dir) const {
    switch (dir) {
        case Direction::LEFT:
            if (bloc.position.x == 0) return false;
            if (grid[bloc.position.y][bloc.position.x-1][bloc.position.z]) return false;
            break;
        case Direction::RIGHT:
            if (bloc.position.x >= nCols-1) return false;
            if (grid[bloc.position.y][bloc.position.x+1][bloc.position.z]) return false;
            break;
        case Direction::UP:
            if (bloc.position.z >= nRows-1) return false;
            if (grid[bloc.position.y][bloc.position.x][bloc.position.z+1]) return false;
            break;
        case Direction::DOWN:
            if (bloc.position.z == 0) return false;
            if (grid[bloc.position.y][bloc.position.x][bloc.position.z-1]) return false;
            break;
        case Direction::FORWARD:
            if (bloc.position.y >= depth-1) return false;
            if (grid[bloc.position.y+1][bloc.position.x][bloc.position.z]) return false;
            break;
    }
    return true;
}

bool NavigationGrid::canMove(const ComplexBloc &bloc, Direction dir) const {
    return std::all_of(bloc.blocs.cbegin(), bloc.blocs.cend(), [this, &dir](const BasicBloc& bloc){return this->canMove(bloc, dir);});
}

bool NavigationGrid::checkCollision(const Bloc * const bloc) const {
    if (auto basicBloc = dynamic_cast<const BasicBloc*>(bloc))
        return checkCollision(*basicBloc);
    else if (auto complexBloc = dynamic_cast<const ComplexBloc*>(bloc))
        return checkCollision(*complexBloc);
    else throw std::bad_cast();
}

void NavigationGrid::solidify(const Bloc *bloc) {
    if (auto basicBloc = dynamic_cast<const BasicBloc*>(bloc))
        solidify(*basicBloc);
    else if (auto complexBloc = dynamic_cast<const ComplexBloc*>(bloc))
        solidify(*complexBloc);
    else throw std::bad_cast();
}

bool NavigationGrid::canMove(const Bloc *bloc, Direction dir) const {
    if (auto basicBloc = dynamic_cast<const BasicBloc*>(bloc))
        return canMove(*basicBloc, dir);
    else if (auto complexBloc = dynamic_cast<const ComplexBloc*>(bloc))
        return canMove(*complexBloc, dir);
    else throw std::bad_cast();
}

unsigned int NavigationGrid::countBlocs(uint slice) const {
    uint count{};
    for (uint x = 0; x < nCols; ++x)
        for (uint z = 0; z < nRows; ++z)
            if (grid[slice][x][z]) ++count;
    return count;
}

unsigned int NavigationGrid::countBlocs() const {
    uint count{};
    for (uint slice = 0; slice < depth; ++slice)
        count += countBlocs(slice);
    return count;
}
