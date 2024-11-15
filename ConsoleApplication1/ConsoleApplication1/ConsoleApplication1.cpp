#include <iostream>
#include <vector>

using namespace std;

// 버튼을 눌렀을 때 그리드를 갱신하는 함수
void apply_press(vector<int>& grid, int button) {
    // 현재 버튼의 상태를 반전합니다.
    grid[button] = 1 - grid[button];

    // 인접한 위치의 상태를 반전합니다.
    if (button % 3 != 0) grid[button - 1] = 1 - grid[button - 1]; // 왼쪽
    if (button % 3 != 2) grid[button + 1] = 1 - grid[button + 1]; // 오른쪽
    if (button >= 3) grid[button - 3] = 1 - grid[button - 3];     // 위
    if (button < 6) grid[button + 3] = 1 - grid[button + 3];       // 아래
}

// 모든 불이 꺼져있는지 확인하는 함수
bool all_off(const vector<int>& grid) {
    for (int i = 0; i < 9; i++) {
        if (grid[i] == 1) return false;
    }
    return true;
}

int main() {
    vector<int> initial_grid(9);

    cout << "그리드 초기 상태를 입력하세요 (불이 켜진 상태는 1, 꺼진 상태는 0):\n";
    for (int i = 0; i < 9; i++) {
        cin >> initial_grid[i];
    }

    bool solution_found = false;
    vector<int> button_presses(9, 0); // 각 버튼을 누를 횟수를 나타내는 배열

    // 각 버튼을 누를 횟수를 0, 1로 설정하여 모든 경우를 탐색합니다.
    while (true) {
        vector<int> grid = initial_grid; // 초기 상태 복사
        vector<pair<int, int>> presses; // 누른 버튼 위치를 저장

        // 현재 button_presses 배열에 따라 버튼을 눌러 적용
        for (int i = 0; i < 9; i++) {
            if (button_presses[i] == 1) { // 버튼이 눌리는 경우
                apply_press(grid, i);
                presses.push_back({ i / 3, i % 3 });
            }
        }

        // 모든 불이 꺼져 있는지 확인
        if (all_off(grid)) {
            cout << "모든 불을 끄기 위해 눌러야 할 버튼 위치:\n";
            for (auto& press : presses) {
                cout << "(" << press.first << ", " << press.second << ")\n";
            }
            solution_found = true;
            break;
        }

        // 다음 조합으로 넘어가기
        int pos = 0;
        while (pos < 9 && button_presses[pos] == 1) {
            button_presses[pos] = 0; // 현재 버튼을 초기화하고
            pos++; // 다음 버튼으로 이동
        }

        if (pos == 9) break; // 모든 조합을 시도한 경우 종료
        button_presses[pos] = 1; // 현재 버튼을 누른 상태로 설정
    }

    if (!solution_found) {
        cout << "해결 가능한 솔루션이 없습니다.\n";
    }

    system("pause");
    return 0;
}
