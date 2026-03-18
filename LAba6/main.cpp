#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <stdexcept>

using namespace std;

class Arena;

class BaseMonster {
protected:
    int health;
    int attack_power;
    int speed;
    int x, y;
    char symbol;
    int direction;
    bool alive;

    void baseMoveLogic(Arena& arena, string* logs, int& log_count);
    void baseAttackLogic(BaseMonster* target, string* logs, int& log_count);

public:
    BaseMonster(char sym, int start_x, int start_y, int hp, int atk, int spd)
            : symbol(sym), x(start_x), y(start_y), health(hp), attack_power(atk), speed(spd), alive(true) {
        direction = (sym >= 'a' && sym <= 'z') ? -1 : 1;
    }

    virtual ~BaseMonster() {}

    virtual void move(Arena& arena, string* logs, int& log_count) = 0;
    virtual void attack(BaseMonster* target, string* logs, int& log_count) = 0;

    bool isAlive() const { return alive && health > 0; }
    int getX() const { return x; }
    int getY() const { return y; }
    char getSymbol() const { return symbol; }
    int getSpeed() const { return speed; }
    int getDirection() const { return direction; }
    int getAttack() const { return attack_power; }

    void setPosition(int nx, int ny) { x = nx; y = ny; }
    void setDirection(int dir) { direction = dir; }
    void takeDamage(int dmg) { health -= dmg; if (health <= 0) alive = false; }
};

class MonsterA : public BaseMonster {
public:
    MonsterA(char s, int x, int y) : BaseMonster(s, x, y, 30, 10, 2) {}
    void move(Arena& arena, string* logs, int& log_count) override { baseMoveLogic(arena, logs, log_count); }
    void attack(BaseMonster* target, string* logs, int& log_count) override { baseAttackLogic(target, logs, log_count); }
};

class MonsterB : public BaseMonster {
public:
    MonsterB(char s, int x, int y) : BaseMonster(s, x, y, 40, 8, 1) {}
    void move(Arena& arena, string* logs, int& log_count) override { baseMoveLogic(arena, logs, log_count); }
    void attack(BaseMonster* target, string* logs, int& log_count) override { baseAttackLogic(target, logs, log_count); }
};

class MonsterC : public BaseMonster {
public:
    MonsterC(char s, int x, int y) : BaseMonster(s, x, y, 20, 15, 3) {}
    void move(Arena& arena, string* logs, int& log_count) override { baseMoveLogic(arena, logs, log_count); }
    void attack(BaseMonster* target, string* logs, int& log_count) override { baseAttackLogic(target, logs, log_count); }
};

class Arena {
private:
    char** grid;
    int rows;
    int cols;
    BaseMonster** monsters;
    int num_monsters;

public:
    Arena(const char* filename) {
        ifstream file(filename);
        if (!file.is_open()) throw runtime_error("err f");

        int n, m;
        if (!(file >> n >> m)) throw runtime_error("err d");

        rows = n + 2;
        cols = m + 2;
        grid = new char*[rows];
        monsters = new BaseMonster*[50];
        num_monsters = 0;

        string line;
        getline(file, line);

        for (int i = 0; i < rows; ++i) {
            grid[i] = new char[cols];
            getline(file, line);
            for (int j = 0; j < cols; ++j) {
                char c = (j < line.length()) ? line[j] : ' ';
                grid[i][j] = c;

                if (c == 'A' || c == 'a') monsters[num_monsters++] = new MonsterA(c, j, i);
                else if (c == 'B' || c == 'b') monsters[num_monsters++] = new MonsterB(c, j, i);
                else if (c == 'C' || c == 'c') monsters[num_monsters++] = new MonsterC(c, j, i);
            }
        }
    }

    ~Arena() {
        for (int i = 0; i < rows; ++i) delete[] grid[i];
        delete[] grid;
        for (int i = 0; i < num_monsters; ++i) delete monsters[i];
        delete[] monsters;
    }

    char getCell(int x, int y) const { return grid[y][x]; }
    void setCell(int x, int y, char c) { grid[y][x] = c; }

    BaseMonster* getMonsterAt(int x, int y) {
        for (int i = 0; i < num_monsters; ++i) {
            if (monsters[i]->isAlive() && monsters[i]->getX() == x && monsters[i]->getY() == y) return monsters[i];
        }
        return NULL;
    }

    int getAliveCount() const {
        int count = 0;
        for (int i = 0; i < num_monsters; ++i) {
            if (monsters[i]->isAlive()) count++;
        }
        return count;
    }

    string getWinnerSymbol() const {
        for (int i = 0; i < num_monsters; ++i) {
            if (monsters[i]->isAlive()) return string(1, monsters[i]->getSymbol());
        }
        return "-";
    }

    void playTurn(string* logs, int& log_count) {
        for (int i = 0; i < num_monsters; ++i) {
            if (monsters[i]->isAlive()) monsters[i]->move(*this, logs, log_count);
        }
    }

    friend ostream& operator<<(ostream& os, const Arena& a) {
        for (int i = 0; i < a.rows; ++i) {
            for (int j = 0; j < a.cols; ++j) os << a.grid[i][j];
            os << '\n';
        }
        return os;
    }
};

void BaseMonster::baseMoveLogic(Arena& arena, string* logs, int& log_count) {
    if (!this->isAlive()) return;
    int steps_taken = 0;

    for (int s = 0; s < speed; ++s) {
        if (!this->isAlive()) break;

        int next_x = x + direction;
        char next_cell = arena.getCell(next_x, y);

        if (next_cell == '*') {
            int dy = (rand() % 2 == 0) ? 1 : -1;
            if (arena.getCell(x, y + dy) == ' ') {
                arena.setCell(x, y, ' '); y += dy; arena.setCell(x, y, symbol);
            } else if (arena.getCell(x, y - dy) == ' ') {
                arena.setCell(x, y, ' '); y -= dy; arena.setCell(x, y, symbol);
            }
            direction *= -1;
            logs[log_count++] = string(1, symbol) + " w";
        }
        else if (next_cell != ' ') {
            BaseMonster* enemy = arena.getMonsterAt(next_x, y);
            if (enemy && enemy->isAlive()) {
                this->attack(enemy, logs, log_count);
                if (!enemy->isAlive()) {
                    arena.setCell(next_x, y, ' ');
                    logs[log_count++] = string(1, symbol) + " k_mv";
                    int dy = (rand() % 2 == 0) ? 1 : -1;
                    if (arena.getCell(x, y + dy) == ' ') {
                        arena.setCell(x, y, ' '); y += dy; arena.setCell(x, y, symbol);
                    } else if (arena.getCell(x, y - dy) == ' ') {
                        arena.setCell(x, y, ' '); y -= dy; arena.setCell(x, y, symbol);
                    }
                } else {
                    break;
                }
            }
        }
        else {
            arena.setCell(x, y, ' ');
            x = next_x;
            arena.setCell(x, y, symbol);
            steps_taken++;
        }
    }
    if (steps_taken > 0) {
        logs[log_count++] = string(1, symbol) + " m " + to_string(steps_taken);
    }
}

void BaseMonster::baseAttackLogic(BaseMonster* target, string* logs, int& log_count) {
    logs[log_count++] = string(1, symbol) + " a " + target->getSymbol() + " " + to_string(attack_power);
    target->takeDamage(attack_power);
    if (!target->isAlive()) {
        logs[log_count++] = string(1, target->getSymbol()) + " d";
    }
}

int main() {
    srand(static_cast<unsigned int>(time(NULL)));

    try {
        Arena arena("arena.txt");
        int round = 1;
        string logs[500];
        int log_count = 0;

        while (arena.getAliveCount() > 1) {
            cout << "R" << round << "\n";
            log_count = 0;
            arena.playTurn(logs, log_count);
            cout << arena;
            for (int i = 0; i < log_count; ++i) cout << logs[i] << "\n";
            cout << "\n";
            round++;
        }
        cout << "W: " << arena.getWinnerSymbol() << "\n";

    } catch (const exception& e) {
        cerr << "E: " << e.what() << "\n";
    }

    return 0;
}