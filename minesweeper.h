#include "cell.h"

// Класс, который реализует саму игру
class Minesweeper {
public:
    Minesweeper();

    // Создаёт вектор из объектов класса Cell
    void fill_field();

    // Случайным образом расставляет бомбы на поле
    void bomb_generation();

    // Расставляет цифры, исходя из того как расставлены бомбы
    void digits_spawn();

    // Метод, отвечающий за события, связанные с открытием клетки (рекурсивное открытие, выигрыш, проишрыш и тп)
    void open_cell(int x, int y);

    // Проверяет, было ли достигнуто условие выигрыша (все клетки без бомб должны быть открыты)
    bool win();

    // Обновляет экран после открытия клетки (на MacOS я не нашёл функций, которые позволяли бы удалять вывод из консоли)
    void update_screen();

    // Рекурсивная функция отвечающая за цепное открытие всех соседних пустых клеток
    int open_if_empty(int x, int y);

    // Реализует окончание игры с возможностью дальнейшего продолжения
    void game_over(bool win);

    // Вызывает ключевые методы для создания игорового поля
    void start();

    // Запускает игру
    void run();
private:
    // Хранит в объекты класса Cell, то есть информацию об игровом поле
    std::vector <std::vector<Cell> > field;

    // Если значение game станет равно false, то игра завершиться
    bool game;
};


