#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <cstdlib>
#include <ctime>
#include <cctype>

using namespace std;

struct pos {
    int x;
    int y;
};

struct logs {
    int hod = 0;
    string t = "";
    void outLogs(string cur);
};

class BaseMonster {
protected:
    int health;
    int dmg;
    int step;
    int name;
public:
    int getHealth() const { return health; }
    int getDmg() const { return dmg; }
    int getStep() const { return step; }
    char getName() const { return name; }
    void takeDamage(int damage) { health -= damage; }

    bool MoveRight;
    pos location;

    BaseMonster(int h, int d, int s, char n) : health(h), dmg(d), step(s), name(n) { MoveRight = true; }
};

class space;

struct Queue {
    int mons = 6;
    int head = 0, tail = 0, cnt = 0;
    BaseMonster **q = nullptr;

    void fill(space* N);
    void addMonster(space* N);
    void push(BaseMonster* m);
    BaseMonster* pop();
    void delMon(BaseMonster *arr[], BaseMonster* mon, int& monCount);
    void clear();
    void shuffle();
};

class space {
protected:
    int n;
    int k;
public:
    string *Data;
    space(const string filename);
    ~space();
    void out() { cout << *this; };
    pos PMonA, PMona, PMonB, PMonb, PMonC, PMonc, PUniMon;

    logs L;
    friend struct Queue;
    friend ostream& operator<<(ostream& os, const space& Pole);

    Queue stM;

    BaseMonster** monsters;
    int monCounter = 0;
    int nextMonIndex = 0;

    void findPos();
    void move(pos &start, BaseMonster* mon);
    void DirectionLowReg(int step, pos &PUniMon, BaseMonster* mon, int indI);
    void DirectionHighReg(int step, pos &PUniMon, BaseMonster* mon, int indI);
    void attack(BaseMonster* mon1, pos &Pmon1, BaseMonster* mon2, pos &Pmon2);
    int isAlive(BaseMonster* mon);
    void beginGame();
    int findSamePos(const pos &p);
    void whoWinner();
    int monDead(BaseMonster* mon1, pos &Pmon1, BaseMonster* mon2, pos &Pmon2);
};

void logs::outLogs(string cur) {
    t = t + "Ход: " + to_string(++hod) + "\n" + cur;
    cout << t << "\n" << "\n";
    t = "";
}

class GenerateSpace {
public:
    int Min = 6;
    int Max = 8;
    int n1, k1;
    int mC = 6;
    string *GData;
    GenerateSpace();
    void FillSpace(const string& filename);
    char monArr[6] = {'A','B','C','a','b','c'};
};

GenerateSpace::GenerateSpace() {
    n1 = Min + (rand() % (Max - Min + 1));
    k1 = Min + (rand() % (Max - Min + 1));
    GData = new string[n1+2];
    string f, z;
    for (int i = 0; i < k1+2; i++) { z += "*"; }
    f += "*";

    for (int i = 0; i < k1; i++) { f += " "; }
    f += "*";

    GData[0] = z;
    for (int i = 1; i < n1+1; i++) { GData[i] = f; }
    GData[n1+1] = z;

    for (int i = 0; i < mC; i++) {
        if (!isupper(monArr[i])) {
            while (true) {
                int pos = rand() % k1 + 1;
                if (GData[pos][1] == ' ') {
                    GData[pos][1] = monArr[i];
                    break;
                }
            }
        }
        else if (isupper(monArr[i])) {
            while (true) {
                int pos = rand() % k1 + 1;
                if (GData[pos][k1] == ' ') {
                    GData[pos][k1] = monArr[i];
                    break;
                }
            }
        }
    }
}

void GenerateSpace::FillSpace(const string& filename) {
    ofstream f(filename);
    f << n1 << " " << k1 << endl;
    for (int i = 0; i < n1+2; i++) {
        f << GData[i] << endl;
    }
}

class MonsterA : public BaseMonster { public: MonsterA() : BaseMonster(15,5,3,'A'){} };
class MonsterB : public BaseMonster { public: MonsterB() : BaseMonster(14,4,3,'B'){} };
class MonsterC : public BaseMonster { public: MonsterC() : BaseMonster(16,6,4,'C'){} };
class Monstera : public BaseMonster { public: Monstera() : BaseMonster(13,11,3,'a'){} };
class Monsterb : public BaseMonster { public: Monsterb() : BaseMonster(6,6,5,'b'){} };
class Monsterc : public BaseMonster { public: Monsterc() : BaseMonster(11,7,7,'c'){} };

space::~space() {
    delete[] Data;
    for (int i = 0; i < nextMonIndex; i++) {
        if (monsters[i]) delete monsters[i];
    }
    delete[] monsters;
}

space::space(const string filename) {
    try {
        ifstream f(filename);
        if (!f.is_open()) {
            throw runtime_error("Не удалось открыть файл: " + filename);
        }

        f >> n >> k;
        n += 2; k += 2;

        Data = new string[n];
        string t;
        getline(f, t);

        for (int i = 0; i < n; i++) {
            getline(f, Data[i]);
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < k; j++) {
                if (Data[i][j] != ' ' && Data[i][j] != '*') monCounter++;
            }
        }
        monsters = new BaseMonster*[monCounter];
    }
    catch (const runtime_error& error) {
        cerr << "Ошибка: " << error.what() << endl;
    }
}

void Queue::fill(space* N) {
    if (!q) q = new BaseMonster*[mons];
    head = 0;
    cnt = 0;
    tail = 0;

    for (int i = 0; i < N->nextMonIndex; i++) {
        if (N->isAlive(N->monsters[i])) {
            q[tail] = N->monsters[i];
            tail = (tail + 1) % mons;
            cnt++;
        }
    }
}

void Queue::push(BaseMonster* m) {
    if (!q) q = new BaseMonster*[mons];
    q[tail] = m;
    tail = (tail + 1) % mons;
    cnt++;
}

BaseMonster* Queue::pop() {
    if (cnt == 0) return nullptr;
    BaseMonster* res = q[head];
    head = (head + 1) % mons;
    cnt--;
    return res;
}

void Queue::delMon(BaseMonster *arr[], BaseMonster* mon, int& monCount) {
    for (int i = 0; i < monCount; i++) {
        if (arr[i] == mon) {
            swap(arr[i], arr[monCount-1]);
            monCount--;
            break;
        }
    }

    if (!q || cnt == 0) return;

    int findMon = -1;
    for (int i = 0; i < cnt; i++) {
        int idx = (head + i) % mons;
        if (q[idx] == mon) {
            findMon = i;
            break;
        }
    }

    if (findMon == -1) return;

    for (int i = findMon; i < cnt - 1; i++) {
        int cur = (head + i) % mons;
        int nxt = (head + i + 1) % mons;
        q[cur] = q[nxt];
    }
    tail = (tail - 1 + mons) % mons;
    cnt--;
}

void Queue::clear() {
    if (q) {
        delete[] q;
        q = nullptr;
    }
    head = tail = cnt = 0;
}

void Queue::shuffle() {
    if (!q || cnt <= 1) return;

    for (int i = cnt - 1; i > 0; i--) {
        int j = rand() % (i + 1);

        int idx_i = (head + i) % mons;
        int idx_j = (head + j) % mons;

        BaseMonster* tmp = q[idx_i];
        q[idx_i] = q[idx_j];
        q[idx_j] = tmp;
    }
}

void space::DirectionLowReg(int step, pos &PUniMon, BaseMonster* mon, int indI) {
    int t;

    if (mon->MoveRight == true) t = 1;
    else t = -1;

    for (int i = indI; i < step; i++) {
        bool aF = false;
        if (Data[PUniMon.y][PUniMon.x + t] == ' ') {
            swap(Data[PUniMon.y][PUniMon.x], Data[PUniMon.y][PUniMon.x + t]);
            if (t == 1) PUniMon.x++; else PUniMon.x--;
            if (i == step-1 && t == 1) {
                L.outLogs(string(1, mon->getName()) + " сходил вправо на " + to_string(mon->getStep()));
                out();
            }
            else if (i == step-1 && t == -1) {
                L.outLogs(string(1, mon->getName()) + " сходил влево на " + to_string(mon->getStep()));
                out();
            }
        }
        else if (Data[PUniMon.y][PUniMon.x + t] == '*') {
            if (t == 1) {
                L.outLogs(string(1,mon->getName()) + " сходил вправо на " + to_string(i+1) + " шаг(а) и уперся в стену");
                out();
            }
            else {
                L.outLogs(string(1,mon->getName()) + " сходил влево на " + to_string(i+1) + " шаг(а) и уперся в стену");
                out();
            }

            afterFight:
            bool upClean = (Data[PUniMon.y - 1][PUniMon.x] == ' ');
            bool downClean = (Data[PUniMon.y + 1][PUniMon.x] == ' ');
            bool reverse = false;

            if (upClean && downClean) {
                if (rand() % 2 == 0) {
                    swap(Data[PUniMon.y][PUniMon.x], Data[PUniMon.y - 1][PUniMon.x]);
                    PUniMon.y--;
                    L.outLogs(string(1, mon->getName()) + " двигается вверх");
                    out();
                } else {
                    swap(Data[PUniMon.y][PUniMon.x], Data[PUniMon.y + 1][PUniMon.x]);
                    PUniMon.y++;
                    L.outLogs(string(1, mon->getName()) + " двигается вниз");
                    out();
                }
                reverse = true;
            }
            else if (downClean) {
                swap(Data[PUniMon.y][PUniMon.x], Data[PUniMon.y + 1][PUniMon.x]);
                PUniMon.y++;
                L.outLogs(string(1, mon->getName()) + " двигается вниз");
                out();
                reverse = true;
            }
            else if (upClean) {
                swap(Data[PUniMon.y][PUniMon.x], Data[PUniMon.y - 1][PUniMon.x]);
                PUniMon.y--;
                L.outLogs(string(1, mon->getName()) + " двигается вверх");
                out();
                reverse = true;
            }

            if (reverse && !aF) {
                mon->location = PUniMon;
                if (t == 1) mon->MoveRight = false;
                else mon->MoveRight = true;

                L.outLogs(string(1, mon->getName()) + " разворачивается на новой строке");
                DirectionLowReg(step, PUniMon, mon, i + 1);
                return;
            } else if (!reverse && !aF) {
                L.outLogs(string(1, mon->getName()) + " разворачивается на той же строке");
                if (t == 1) mon->MoveRight = false;
                else mon->MoveRight = true;
                break;
            }

            if (aF) {
                if (reverse) {
                    mon->location = PUniMon;
                    L.outLogs(string(1, mon->getName()) + " победил и продолжает движение на новой строке");
                    DirectionLowReg(step, PUniMon, mon, i + 1);
                    return;
                } else {
                    L.outLogs(string(1, mon->getName()) + " победил, но не смог сменить строку");
                    break;
                }
            }
        }
        else if (Data[PUniMon.y][PUniMon.x + t] == 'a' || Data[PUniMon.y][PUniMon.x + t] == 'b' || Data[PUniMon.y][PUniMon.x + t] == 'c') {
            mon->location = PUniMon;
            if (t == 1) mon->MoveRight = false;
            else mon->MoveRight = true;
            L.outLogs(string(1, mon->getName()) + " разворачивается, так как впереди свой монстр");
            DirectionLowReg(step, PUniMon, mon, i + 1);
            return;
        }
        else if (Data[PUniMon.y][PUniMon.x + t] == 'A' || Data[PUniMon.y][PUniMon.x + t] == 'B' || Data[PUniMon.y][PUniMon.x + t] == 'C') {
            pos Pmon2;
            Pmon2.x = PUniMon.x + t;
            Pmon2.y = PUniMon.y;
            int idx = findSamePos(Pmon2);
            if (t == 1) {
                L.outLogs(string(1, mon->getName()) + " сходил вправо на " + to_string(i+1) + " шаг(а) и встретился с " + string(1, monsters[idx]->getName()));
                out();
            }
            else {
                L.outLogs(string(1, mon->getName()) + " сходил влево на " + to_string(i+1) + " шаг(а) и встретился с " + string(1, monsters[idx]->getName()));
                out();
            }
            attack(mon, PUniMon, monsters[idx], Pmon2);
            if (isAlive(mon)) { aF = true; goto afterFight; }
            return;
        }
        else break;
    }
}

void space::DirectionHighReg(int step, pos &PUniMon, BaseMonster* mon, int indI) {
    int t;

    if (mon->MoveRight == true) t = 1;
    else t = -1;

    int dirX;
    if (L.hod == 0) out();
    cout << "Введите направление шага (1 - вправо, -1 - влево) монстра " << mon->getName() << ": ";
    cin >> dirX;
    if (dirX != 1 && dirX != -1) {
        cout << "Некорректный ввод. Введите ещё раз" << endl;
        DirectionHighReg(step, PUniMon, mon, indI);
        return;
    }
    if (dirX == 1 || dirX == -1) {
        for (int i = indI; i < step; i++) {
            if (Data[PUniMon.y][PUniMon.x + dirX] == ' ') {
                swap(Data[PUniMon.y][PUniMon.x], Data[PUniMon.y][PUniMon.x + dirX]);
                if (dirX == 1) PUniMon.x++; else PUniMon.x--;
                if (i == step-1 && dirX == 1) {
                    L.outLogs(string(1, mon->getName()) + " сходил вправо на " + to_string(mon->getStep()));
                    out();
                }
                else if (i == step-1 && dirX == -1) {
                    L.outLogs(string(1, mon->getName()) + " сходил влево на " + to_string(mon->getStep()));
                    out();
                }
            }
            else if (Data[PUniMon.y][PUniMon.x + dirX] == '*') {
                L.outLogs("Монстр " + string(1, mon->getName()) + " уперся в стену. ");

                afterBigFight:
                cout << "Выберите направление (2 - вверх, -2 - вниз) монстра " << mon->getName() << ": ";
                int dirY;
                cin >> dirY;
                if (dirY != 2 && dirY != -2) {
                    cout << "Некорректный ввод. Введите ещё раз" << endl;
                    goto afterBigFight;
                }
                if (dirY == 2 && Data[PUniMon.y - 1][PUniMon.x] == ' ') {
                    swap(Data[PUniMon.y][PUniMon.x], Data[PUniMon.y - 1][PUniMon.x]);
                    PUniMon.y--;
                    L.outLogs(string(1, mon->getName()) + " двигается вверх");
                    out();
                    DirectionHighReg(step, PUniMon, mon, i + 1);
                    return;
                }
                else if (dirY == 2 && Data[PUniMon.y - 1][PUniMon.x] != ' ') {
                    cout << "Сверху нет места" << endl;
                    goto afterBigFight;
                }
                else if (dirY == -2 && Data[PUniMon.y + 1][PUniMon.x] == ' ') {
                    swap(Data[PUniMon.y][PUniMon.x], Data[PUniMon.y + 1][PUniMon.x]);
                    PUniMon.y++;
                    L.outLogs(string(1, mon->getName()) + " двигается вниз");
                    out();
                    DirectionHighReg(step, PUniMon, mon, i + 1);
                    return;
                }
                else if (dirY == -2 && Data[PUniMon.y + 1][PUniMon.x] != ' ') {
                    cout << "Снизу нет места" << endl;
                    goto afterBigFight;
                }
            }
            else if (Data[PUniMon.y][PUniMon.x + dirX] == 'a' || Data[PUniMon.y][PUniMon.x + dirX] == 'b' || Data[PUniMon.y][PUniMon.x + dirX] == 'c') {
                pos Pmon2;
                Pmon2.x = PUniMon.x + dirX;
                Pmon2.y = PUniMon.y;
                int idx = findSamePos(Pmon2);
                if (dirX == 1) {
                    L.outLogs(string(1, mon->getName()) + " сходил вправо на " + to_string(i+1) + " шаг(а) и встретился с " + string(1, monsters[idx]->getName()));
                    out();
                }
                else {
                   L.outLogs(string(1, mon->getName()) + " сходил влево на " + to_string(i+1) + " шаг(а) и встретился с " + string(1, monsters[idx]->getName()));
                   out();
                }
                attack(mon, PUniMon, monsters[idx], Pmon2);
                if (isAlive(mon)) { goto afterBigFight; }
                return;
            }
            else if (Data[PUniMon.y][PUniMon.x + dirX] == 'A' || Data[PUniMon.y][PUniMon.x + dirX] == 'B' || Data[PUniMon.y][PUniMon.x + dirX] == 'C') {
                L.outLogs(string(1, mon->getName()) + " разворачивается, так как впереди свой монстр");
                DirectionHighReg(step, PUniMon, mon, i + 1);
                return;
            }
            else break;
        }
    }
}

int space::monDead(BaseMonster* mon1, pos &Pmon1, BaseMonster* mon2, pos &Pmon2) {
    if (!isAlive(mon2)) {
        L.outLogs(string(1, mon2->getName()) + " мертв.");
        Data[Pmon2.y][Pmon2.x] = ' ';
        mon2->location.x = -1;
        mon2->location.y = -1;
        stM.delMon(monsters, mon2, monCounter);
        return 1;
    }
    else return 0;
}

void space::attack(BaseMonster* mon1, pos &Pmon1, BaseMonster* mon2, pos &Pmon2) {
    while (mon1->getHealth() > 0 && mon2->getHealth() > 0) {
        mon2->takeDamage(mon1->getDmg());
        L.outLogs(string(1, mon1->getName()) + " атакует " + string(1, mon2->getName()) + " на " + to_string(mon1->getDmg()) + " урона. Здоровье " + string(1, mon2->getName()) + ": " + to_string(mon2->getHealth()));

        if (monDead(mon1, Pmon1, mon2, Pmon2)) break;

        mon1->takeDamage(mon2->getDmg());
        L.outLogs(string(1, mon2->getName()) + " атакует " + string(1, mon1->getName()) + " на " + to_string(mon2->getDmg()) + " урона. Здоровье " + string(1, mon1->getName()) + ": " + to_string(mon1->getHealth()));

        if (monDead(mon2, Pmon2, mon1, Pmon1)) break;
    }
}

void Queue::addMonster(space* N) {
    for (int i = 0; i < N->n; i++) {
        for (int j = 0; j < N->k; j++) {
            BaseMonster* m = nullptr;

            switch (N->Data[i][j]) {
                case 'A': m = new MonsterA(); m->location.x = j; m->location.y = i; break;
                case 'B': m = new MonsterB(); m->location.x = j; m->location.y = i; break;
                case 'C': m = new MonsterC(); m->location.x = j; m->location.y = i; break;
                case 'a': m = new Monstera(); m->location.x = j; m->location.y = i; break;
                case 'b': m = new Monsterb(); m->location.x = j; m->location.y = i; break;
                case 'c': m = new Monsterc(); m->location.x = j; m->location.y = i; break;
            }

            if (m) N->monsters[N->nextMonIndex++] = m;
        }
    }
}

int space::findSamePos(const pos &p) {
    for (int i = 0; i < monCounter; i++) {
        BaseMonster* m = monsters[i];
        if (m->location.x == p.x && m->location.y == p.y) return i;
    }
    return -1;
}

int space::isAlive(BaseMonster* mon) {
    return (mon->getHealth() > 0) ? 1 : 0;
}

void space::beginGame() {
    for (int i = 0; i < monCounter; i++) {
        BaseMonster* m = monsters[i];
        if (isupper(Data[m->location.y][m->location.x]))
            m->MoveRight = false;
        else
            m->MoveRight = true;
    }

    while (true) {
        int countPlayer = 0, countRobot = 0;
        for (int i = 0; i < monCounter; i++) {
            BaseMonster* m = monsters[i];
            if (isAlive(m)) {
                if (isupper(m->getName())) countPlayer++;
                else countRobot++;
            }
        }

        if (countPlayer == 0) {
            cout << "Монстры робота победили!" << endl;
            break;
        }
        if (countRobot == 0) {
            cout << "Монстры игрока победили!" << endl;
            break;
        }

        stM.clear();
        stM.fill(this);
        stM.shuffle();

        int roundSize = stM.cnt;
        for (int i = 0; i < roundSize; i++) {
            BaseMonster* m = stM.pop();
            if (m && isAlive(m)) {
                move(m->location, m);
            }
        }
    }
}


void space::move(pos &start, BaseMonster* mon) {
    if (!isAlive(mon)) return;

    PUniMon = start;
    int step = mon->getStep();

    if (isupper(mon->getName()))
        DirectionHighReg(step, PUniMon, mon, 0);
    else
        DirectionLowReg(step, PUniMon, mon, 0);

    if (isAlive(mon)) {
        start = PUniMon;
        mon->location = PUniMon;
    }
    else {
        Data[PUniMon.y][PUniMon.x] = ' ';
        mon->location.x = -1;
        mon->location.y = -1;
    }
}

void space::findPos() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            switch (Data[i][j]) {
                case 'A': PMonA.y = i; PMonA.x = j; break;
                case 'a': PMona.y = i; PMona.x = j; break;
                case 'C': PMonC.y = i; PMonC.x = j; break;
                case 'c': PMonc.y = i; PMonc.x = j; break;
                case 'B': PMonB.y = i; PMonB.x = j; break;
                case 'b': PMonb.y = i; PMonb.x = j; break;
            }
        }
    }
}

void space::whoWinner() {
    for (int i = 0; i < monCounter; i++) {
        if (isAlive(monsters[i])) {
            cout << endl << "Монстр " << monsters[i]->getName() << " остался жив." << endl;
        }
    }
}

ostream& operator<<(ostream& os, const space& Pole) {
    for (int i = 0; i < Pole.n; i++) {
        os << Pole.Data[i] << endl;
    }
    return os;
}

int main() {
    system("chcp 65001");

    GenerateSpace *A = new GenerateSpace();
    A->FillSpace("genSpace.txt");
    delete A;

    space *X = new space("genSpace.txt");
    srand(time(0));

    X->findPos();

    X->stM.addMonster(X);

    X->beginGame();
    X->out();
    X->whoWinner();
    cout << endl;

    delete X;
    return 0;
}