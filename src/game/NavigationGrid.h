//
// Created by lilian on 14/12/2021.
//

#ifndef NAVIGATION_GRID_H
#define NAVIGATION_GRID_H


#include <vector>
#include "blocs/BasicBloc.h"
#include "blocs/ComplexBloc.h"

enum class Direction {
    LEFT, RIGHT, UP, DOWN, FORWARD
};

struct Color {
    float r, g, b, a;
    Color() : r{}, g{}, b{}, a(1.0f) {};
    explicit Color(float c) : r(c), g(c), b(c), a(1.0f) {};
    Color(float c, float alpha) : r(c), g(c), b(c), a(alpha) {};
    Color(float r, float g, float b) : r(r), g(g), b(b), a(1.0f) {};
    Color(float r, float g, float b, float alpha) : r(r), g(g), b(b), a(alpha) {};
    static Color random() {
        // NOLINTNEXTLINE(cert-msc30-c, cert-msc50-cpp, cppcoreguidelines-narrowing-conversions)
        return {(rand() % 256) / 255.0f, (rand() % 256) / 255.0f, (rand() % 256) / 255.0f, 1.0f};
    };
};

class NavigationGrid{
    private:
        unsigned int nRows, nCols, depth;
        std::vector<std::vector<std::vector<bool>>> grid;
        std::vector<Color> slicesColors;

    public:
        NavigationGrid(uint nRows, uint nCols, uint depth);

        [[nodiscard]] bool at(const Position& pos) const {return grid[pos.y][pos.x][pos.z];};
        bool operator[](const Position& pos) const {return at(pos);};

        [[nodiscard]] bool checkCollision(const BasicBloc& bloc) const;
        [[nodiscard]] bool checkCollision(const ComplexBloc& bloc) const;
        [[nodiscard]] bool checkCollision(const Bloc *bloc) const;
        void solidify(const BasicBloc& bloc);
        void solidify(const ComplexBloc& bloc);
        void solidify(const Bloc *bloc);

        [[nodiscard]] bool isSliceFull(unsigned int slice) const;
        void removeSlice(unsigned int slice);
        void removeFullSlices();

        [[nodiscard]] bool canMove(const BasicBloc& bloc, Direction dir) const;
        [[nodiscard]] bool canMove(const ComplexBloc& bloc, Direction dir) const;
        [[nodiscard]] bool canMove(const Bloc *bloc, Direction dir) const;

        [[nodiscard]] unsigned int countBlocs(uint slice) const;
        [[nodiscard]] unsigned int countBlocs() const;

        friend class Game;
};


#endif //NAVIGATION_GRID_H
