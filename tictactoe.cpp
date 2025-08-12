#include <iostream>
#include <vector>
#include <array>
using namespace std;

const int BLANK = 2;
const int X = 3;
const int O = 5;

vector<int> Board(10, BLANK); 
int Turn = 1;                 

const array<array<int,3>,8> LINES = {{
    {{1,2,3}}, {{4,5,6}}, {{7,8,9}}, 
    {{1,4,7}}, {{2,5,8}}, {{3,6,9}}, 
    {{1,5,9}}, {{3,5,7}}             
}};

void printBoard() {
    auto ch = [](int v)->char {
        if (v == X) return 'X';
        if (v == O) return 'O';
        return ' ';
    };
    cout << "\n";
    for (int r = 0; r < 3; ++r) {
        cout << " " << ch(Board[1 + r*3]) << " | " << ch(Board[2 + r*3]) << " | " << ch(Board[3 + r*3]) << "\n";
        if (r < 2) cout << "---+---+---\n";
    }
    cout << "\n";
}

int find_any_blank() {
    for (int i = 1; i <= 9; ++i) if (Board[i] == BLANK) return i;
    return 0;
}

int Posswin(int p) {
    int target = p * p * BLANK; 
    for (auto &line : LINES) {
        int a = line[0], b = line[1], c = line[2];
        int prod = Board[a] * Board[b] * Board[c];
        if (prod == target) {
            if (Board[a] == BLANK) return a;
            if (Board[b] == BLANK) return b;
            return c;
        }
    }
    return 0;
}

int Make2() {
    if (Board[5] == BLANK) return 5;
    for (int pos : {2,4,6,8}) if (Board[pos] == BLANK) return pos;
    return find_any_blank();
}

void place_move_ai(int desired) {
    int n = desired;
    if (n < 1 || n > 9 || Board[n] != BLANK) {
        for (int pos : {1,3,7,9,2,4,6,8,5}) {
            if (Board[pos] == BLANK) { n = pos; break; }
        }
    }
    Board[n] = (Turn % 2 == 1) ? X : O;
    cout << "Turn " << Turn << ": Player " << ((Turn % 2 == 1) ? 'X' : 'O') << " plays " << n << "\n";
    Turn++;
}

int check_winner() {
    for (auto &line : LINES) {
        int prod = Board[line[0]] * Board[line[1]] * Board[line[2]];
        if (prod == X*X*X) return X;
        if (prod == O*O*O) return O;
    }
    return 0;
}

void ai_move_logic() {
    switch (Turn) {
        case 1:
            place_move_ai(1);
            break;
        case 2:
            if (Board[5] == BLANK) place_move_ai(5);
            else place_move_ai(1);
            break;
        case 3:
            if (Board[9] == BLANK) place_move_ai(9);
            else place_move_ai(3);
            break;
        case 4: {
            int block = Posswin(X);
            if (block != 0) place_move_ai(block);
            else place_move_ai(Make2());
            break;
        }
        case 5: {
            int win = Posswin(X);
            if (win != 0) { place_move_ai(win); break; }
            int oppWin = Posswin(O);
            if (oppWin != 0) { place_move_ai(oppWin); break; }
            if (Board[7] == BLANK) place_move_ai(7);
            else place_move_ai(3);
            break;
        }
        default: {
            int me = ( (Turn %2==1) ? X : O );
            int opp = (me == X ? O : X);
            int myWin = Posswin(me);
            if (myWin != 0) { place_move_ai(myWin); break; }
            int oppWin2 = Posswin(opp);
            if (oppWin2 != 0) { place_move_ai(oppWin2); break; }
            int m2 = Make2();
            if (m2 != 0) { place_move_ai(m2); break; }
            place_move_ai(find_any_blank());
            break;
        }
    }
}

int main() {
    cout << "Tic-Tac-Toe: AI vs AI simulation\n";
    printBoard();
    
    while (Turn <= 9) {
        ai_move_logic();
        printBoard();
        int winner = check_winner();
        if (winner == X) { cout << "X wins!\n"; break; }
        if (winner == O) { cout << "O wins!\n"; break; }
        if (Turn > 9) { cout << "Game is a draw.\n"; break; }
    }
    return 0;
}
