// Дана шахматная доска размером 6х6 и шахматный конь.Программа должна запросить  у
// пользователя начальные координаты клетки поля и поставить туда коня.Задача программы найти и
// вывести путь коня, при котором он обойдет все клетки доски, становясь в каждую клетку
// только один раз. (Так как процесс отыскания пути для разных начальных клеток может
// затянуться, то рекомендуется сначала опробовать задачу на поле размером 6х6).В программе
// необходимо использовать рекурсию.


#include <iostream>
#include <windows.h>
using namespace std;

const int deskBorder = 6;

void CreateChessDesk(int desk[deskBorder][deskBorder]);

bool isCanMove(int x, int y);

void PrintStepHorse(int x, int y);

bool MoveHorse(int x, int y, int moveCount, int desk[deskBorder][deskBorder]);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int ChessDesk[deskBorder][deskBorder];    
    int startX, startY;
    
    CreateChessDesk(ChessDesk);    

    cout << "Укажите координаты с которых конь начнёт движение :";
    cin >> startX >> startY;

    // Проверка на допустимость координат полученных от пользователя
    if (!isCanMove(startX, startY)) {
        cout << "Не корректные координаты, размер поля 6 на 6" << endl;
        return 0;
    }        

    MoveHorse(startX, startY, 0, ChessDesk);
}


void CreateChessDesk(int desk[deskBorder][deskBorder]) {
    for (int x = 0; x < deskBorder; x++)
        for (int y = 0; y < deskBorder; y++)
            desk[x][y] = -1;
}

bool isCanMove(int x, int y) {
    return x >= 0 && x < deskBorder && y >= 0 && y < deskBorder;
}

void PrintStepHorse(int x, int y) {
    cout << "[ " << x << " ]" << "[ " << y << " ]" << endl;
}

bool MoveHorse(int x, int y, int moveCount, int desk[deskBorder][deskBorder]) {

    if (desk[x][y] == -1) {

        // Помечаю поле если зашёл на него
        desk[x][y] = moveCount;

        // Путь коняжки
        PrintStepHorse(x, y);

        if (moveCount == 35) return true;
        
        // Возможные шаги
        int possibleStepsSize = 8;
        int const dx[] = { 2, 1, -1, -2, -2, -1, 1, 2 };
        int const dy[] = { 1, 2, 2, 1, -1, -2, -2, -1 };

        // Выбор возможного шага
        for (int i = 0; i < possibleStepsSize; i++){
            int newX = x + dx[i];
            int newY = y + dy[i];

            if (isCanMove(newX, newY) && desk[newX][newY] == -1) {
                // Рекурсивный вызов
                if (MoveHorse(newX, newY, moveCount + 1, desk)) {
                    return true;
                }
            }       
        }

        // Если не шагнул, опять помечаю как нехоженную клетку
        desk[x][y] == -1;
    }

    return false; 
}