#include <iostream>
#include <vector>
#include <array>
#include <cstdlib>
#include "minesweeper.h"

Minesweeper::Minesweeper() {}

void Minesweeper::fill_field() {
    std::vector <Cell> vec;
    for (int i = 0; i < 9; i++){
        field.push_back(vec);
        for (int j = 0; j < 9; j++){
            field[i].push_back(Cell(j, i));
        }
        vec.clear();
    }
}

void Minesweeper::bomb_generation() {
    int a, b;
    coords ab;
    srand(time(NULL));

    for (int i = 0; i < 12; i++) {
        ab.cx = a = rand() % 9;
        ab.cy = b = rand() % 9;

        field[b][a].set_status(-1);
        field[b][a].set_view(" @ ");
    }
}

void Minesweeper::digits_spawn() {
    int bombs;
    std::vector <coords> neighbors;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {

            if (field[j][i].get_status() != -1) {

                bombs = 0;
                neighbors = field[j][i].neighbors();

                for (int k = 0; k < neighbors.size(); k++) {
                    if (field[neighbors[k].cy][neighbors[k].cx].get_status() == -1) {
                        bombs++;
                    }
                }
                if (bombs > 0){
                    field[j][i].set_status(bombs);
                    field[j][i].set_view(" " + std::to_string(bombs) + " ");
                }

            }
        }
    }
}

void Minesweeper::open_cell(int x, int y) {
    switch (field[y][x].get_status()) {
        case -1:
            game_over(false);
            break;
        case 0:
            open_if_empty(x, y);
            update_screen();
            break;
        default:
            field[y][x].open();
            update_screen();
            break;
    }
    if (win()){
        game_over(true);
    }
}

int Minesweeper::open_if_empty(int x, int y) {
    if (field[y][x].get_status() != 0){
        field[y][x].open();
        return 0;
    }

    field[y][x].open();

    std::vector <coords> neighbors = field[y][x].neighbors();

    for (int i = 0; i < neighbors.size(); i++){
        if (not field[neighbors[i].cy][neighbors[i].cx].is_opened()){
            open_if_empty(neighbors[i].cx, neighbors[i].cy);
        }
    }
}

void Minesweeper::update_screen() {
    std::cout << "    0  1  2  3  4  5  6  7  8" << std::endl;
    std::cout << "   --------------------------" << std::endl;
    std::string s;
    for (int i = 0; i < 9; i++){
        s += (char)i + '0';
        s += "| ";
        for (int j = 0; j < 9; j++) {
            if (field[j][i].is_opened()){
                s += field[j][i].get_view();
            }
            else{
                s += "[ ]";
            }
        }
        std::cout << s << std::endl;
        s = "";
    }
}

void Minesweeper::game_over(bool win) {
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            field[j][i].open();
        }
    }
    update_screen();

    field.clear();

    if (win){
        std::cout << "YOU ARE COOL MAAAN" << std::endl;
    }
    else{
        std::cout << "GAME OVER MAN" << std::endl;
    }

    std::cout << "Start new game? (yes or no)" << std::endl;

    std::string answer;
    std::cin >> answer;
    while ((answer != "yes") and (answer != "no")){
        std::cin >> answer;
    }
    if (answer == "no"){
        game = false;
    }
    else{
        start();
    }
}

bool Minesweeper::win() {
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            if (not field[j][i].is_opened() and field[j][i].get_status() != -1)
                return false;
        }
    }
    return true;
}

void Minesweeper::start() {
    fill_field();
    bomb_generation();
    digits_spawn();
}

void Minesweeper::run() {
    int x, y;
    game = true;

    start();

    while (game){
        std::cin >> x >> y;
        open_cell(y, x);
    }
}
