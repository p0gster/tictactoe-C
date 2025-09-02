#include <array>
#include <iostream>

using namespace std;

class TicTacToe {
public:
    TicTacToe() : currentPlayer(1), turns(0) {
        grid.fill({0, 0, 0});
    }

    void play() {
        render();
        cout << playerChar(currentPlayer) << "'s turn!\n";

        while (turns < 9) {
            array<int, 2> pos = getMove();
            grid[pos[0]][pos[1]] = currentPlayer;
            render();

            if (isWinner(pos)) {
                cout << playerChar(currentPlayer) << " wins!\n";
                return;
            }

            nextPlayer();
            cout << playerChar(currentPlayer) << "'s turn!\n";
            ++turns;
        }

        cout << "It's a draw!\n";
    }

private:
    array<array<int, 3>, 3> grid;
    int currentPlayer;
    int turns;

    char playerChar(int player) const {
        switch (player) {
            case 1: return 'X';
            case 2: return 'O';
            default: return ' ';
        }
    }

    void nextPlayer() {
        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }

    void render() const {
        cout << "+---+\n";
        for (int i = 2; i >= 0; --i) {
            cout << "|";
            for (int j = 0; j < 3; ++j) {
                cout << playerChar(grid[j][i]);
            }
            cout << "|\n";
        }
        cout << "+---+\n\n";
    }

    array<int, 2> getMove() const {
        array<int, 2> pos;
        for (int i = 0; i < 2; ++i) {
            char input;
            while (true) {
                cin >> input;
                if (input >= '1' && input <= '3') {
                    pos[i] = input - '1';
                    break;
                }
            }
        }
        return pos;
    }

    bool isWinner(const array<int, 2>& pos) const {
        array<array<int, 2>, 4> directions = {{{1, 0}, {0, 1}, {1, 1}, {1, -1}}};

        for (auto dir : directions) {
            int count = 1;
            count += countInDirection(pos, dir);
            negate(dir);
            count += countInDirection(pos, dir);

            if (count >= 3) return true;
        }
        return false;
    }

    int countInDirection(array<int, 2> pos, const array<int, 2>& dir) const {
        int count = 0;
        while (true) {
            pos[0] += dir[0];
            pos[1] += dir[1];

            if (pos[0] < 0 || pos[0] > 2 || pos[1] < 0 || pos[1] > 2) break;
            if (grid[pos[0]][pos[1]] == currentPlayer) ++count;
            else break;
        }
        return count;
    }

    void negate(array<int, 2>& vec) const {
        for (auto& v : vec) v = -v;
    }
};

int main() {
    TicTacToe game;
    game.play();
}
