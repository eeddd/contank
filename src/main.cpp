#include <iostream>
#include <curses.h>
#include <unistd.h>

bool gameover = false;
int W = 20, H = 16;
int key;

class Tank
{
    int m_x, m_y;
    int m_size;
    char m_body[9];
    int m_dir;

public:
    Tank() : m_x(0), m_y(0), m_size(9), m_body{ ' ','1',' ', '1','1','1', '1',' ','1' }
    {
    }

    bool Hit(int x, int y)
    {
        if (x >= m_x && x <= m_x + 2 
            && y >= m_y && y <= m_y + 2)
            return true;
        return false;
    }

    char GetChar(int a, int b)
    {
        if (!Hit(a, b)) return ' ';

        int x = a - m_x;
        int y = b - m_y;
        
        int i = 0;
        switch (m_dir % 4)
        {
        case 0:
            i = (y) * 3 + x;
            break;
        case 1:
            i = 6 + y - (x * 3);
            break;
        case 2:
            i = 8 - (y * 3) - x;
            break;
        case 3:
            i = 2 - y + (x * 3);
            break;
        }
        
        return m_body[i];
    }

    int& dir() { return m_dir; }

    int& x() { return m_x; }
    int& y() { return m_y; }
} tank;

void Init()
{
    tank.dir() = 0;
    tank.x() = 1;
    tank.y() = 1;
}

void Draw()
{
    for (int y = 0; y < H; y++)
    {
        for (int x = 0; x < W; x++)
        {
            move(y, x);
            if (x == 0 || x == W-1 || y == 0 || y == H-1)
                addch('#');
            else if (tank.Hit(x, y))
                addch(tank.GetChar(x, y));
            else 
                addch(' ');
        }
    }
    refresh();
}

void Input()
{
    switch (key)
    {
    case KEY_UP:
        if (tank.dir() == 0) tank.y() -= 1;
        tank.dir() = 0;
        break;
    case KEY_RIGHT:
        if (tank.dir() == 1) tank.x() += 1;
        tank.dir() = 1;
        break;
    case KEY_DOWN:
        if (tank.dir() == 2) tank.y() += 1;
        tank.dir() = 2;
        break;
    case KEY_LEFT:
        if (tank.dir() == 3) tank.x() -= 1;
        tank.dir() = 3;
        break;
    }
}

void Update()
{
    if (tank.x() <= 0)
        tank.x() = 1;
    else if (tank.x() >= W-3)
        tank.x() = W-4;
    if (tank.y() <= 0)
        tank.y() = 1;
    else if (tank.y() >= H-3)
        tank.y() = H-4;
}

int main()
{
    initscr();
    nodelay(stdscr, true);
    keypad(stdscr, true);
    cbreak();
    noecho();
    clear();
    refresh();

    Init();

    while (!gameover)
    {
        Draw();
        Input();
        Update();
        key = getch();
        if (key == 'q') break;
    }
    
    nodelay(stdscr, false);
    move(H/2, W/2-5);
    printw("Game Over!");
    getch();

    endwin();
    return 0;
}