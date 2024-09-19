#include <ncurses.h>

int main() {
    initscr();            // Инициализация ncurses
    noecho();             // Отключаем отображение набираемого текста
    cbreak();             // Немедленно передавать символы без буферизации

    int height = 10, width = 20, start_y = 5, start_x = 5;
    WINDOW *win = newwin(height, width, start_y, start_x); // Создаем новое окно

    box(win, 0, 0);       // Рисуем рамку вокруг окна
    mvwprintw(win, 1, 1, "Hello World!"); // Выводим текст в окне
    wrefresh(win);        // Обновляем окно, чтобы показать изменения

   getch();              // Ожидаем нажатие клавиши
    delwin(win);          // Удаляем окно
    endwin();             // Завершаем работу с ncurses

    return 0;
}
