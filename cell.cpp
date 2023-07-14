#include <vector>
#include "cell.h"

/*!
 * Класс объектов из которых будет состоять поле класса Minesweeper
 * @param _x x координата клетки
 * @param _y y координата клетки
 */
Cell::Cell(int _x, int _y) {
    y = _y;
    x = _x;
    opened = false;
    view = "   ";
}

int Cell::get_status() {return status;}

void Cell::set_status(int s) {status = s;}

void Cell::open() {opened = true;}

bool Cell::is_opened() {return opened;}

void Cell::set_view(std::string s) {view = s;}

std::string Cell::get_view() {return view;}

std::vector<coords> Cell::neighbors() {
    std::vector<coords> neighbors,  clone;
    coords b;
    int a[3] = {-1, 0, 1};

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            b.cx = x + a[i];
            b.cy = y + a[j];
            neighbors.push_back(b);
        }
    }

    for (int i = 0; i < 9; i++) {
        if (((0 <= neighbors[i].cx) and (neighbors[i].cx <= 8)) and
            ((0 <= neighbors[i].cy) and (neighbors[i].cy <= 8))) {
            clone.push_back(neighbors[i]);
        }
    }
    return clone;
}