#include "blazingio.hpp"
#include <vector>
using namespace std;

struct Student {
    int group_id;
    int isu;
    int points;
};

int hash_func(int key, int table_size) {
    return key % table_size;
}

void add(vector<vector<Student>>& groups, int group, int isu, int points, int M) {
    groups[hash_func(group, M)].push_back({group, isu, points});
}

void remove(vector<vector<Student>>& groups, int group, int isu, int M) {
    vector<Student>& bucket = groups[hash_func(group, M)];
    for (Student& student : bucket) {
        if (student.isu == isu) {
            student = Student{};
            break;
        }
    }
}

int MaxScore(vector<vector<Student>>& groups, int group, int M) {
    int max_points = -1000000000;
    for (const Student& student : groups[hash_func(group, M)]) {
        if (student.group_id == group && student.isu != -1) {
            max_points = max(max_points, student.points);
        }
    }
    return max_points;
}

int AverageScore(vector<vector<Student>>& groups, int group, int M) {
    int total_points = 0, count = 0;
    for (const Student& student : groups[hash_func(group, M)]) {
        if (student.group_id == group && student.isu != -1) {
            total_points += student.points;
            count++;
        }
    }
    if (count > 0)
        return total_points / count;
    else
        return 0;
}

int main() {
    int m, q;
    char command;
    cin >> m >> q;

    vector<vector<Student>> groups(m);
    vector<int> results;

    for (int i = 0; i < q; i++) {
        cin >> command;
        int group, isu, points;

        if (command == 'a') {
            cin >> group;
            results.push_back(AverageScore(groups, group, m));
        }
        else if (command == '-') {
            cin >> group >> isu;
            remove(groups, group, isu, m);
        }
        else if (command == '+') {
            cin >> group >> isu >> points;
            add(groups, group, isu, points, m);
        }
        else if (command == 'm') {
            cin >> group;
            results.push_back(MaxScore(groups, group, m));
        }
    }

    for (int result : results) {
        cout << result << "\n";
    }
}

