#include <iostream>
#include <vector>

using namespace std;

int HashFunction1(const string& str, int n) {
    const int p = 31;
    int hash = 0;
    for (char c : str) {
        hash += hash * 228 + c;
    }
    return hash % 1000001;
}

int HashFunction2(const string& str, int n) {
    const int m = 107;
    int hash = 0;
    for (char c : str) {
        hash += hash * 228 + c;
    }
    return (hash + 123) % (1000001);
}

void InsertStudentA(vector<string>& student, string& solution, int n) {
    int hash1 = HashFunction1(solution, n);
    int hash2 = HashFunction2(solution, n);

    if (student[hash1].empty()) {
        student[hash1] = solution;
    } else if (student[hash2].empty()) {
        student[hash2] = solution;
    } else {
        student[hash1] = solution;
        while (!student[hash1].empty() && student[hash1] != solution) {
            if (HashFunction1(student[hash1], n) == hash1)
                swap(student[hash2], student[hash1]);
            else
                swap(student[hash1], student[hash2]);
        }

        student[hash2] = solution;
        while (!student[hash2].empty() && student[hash2] != solution) {
            if (HashFunction1(student[hash2], n) == hash1)
                swap(student[hash2], student[hash1]);
            else
                swap(student[hash1], student[hash2]);
        }
    }
}

bool CheckSolution(vector<string>& student, string& solution, int n) {
    return (student[HashFunction1(solution, n)] == solution) || (student[HashFunction2(solution, n)] == solution);
}

int main() {
    int n;
    cin >> n;

    vector<string> studentA(1000001);
    vector<string> studentB(1000001);
    vector<string> studentC(1000001);

    vector<string> solutionsA;
    vector<string> solutionsB;
    vector<string> solutionsC;

    for (int i = 0; i < n; i++) {
        string solution;
        cin >> solution;
        InsertStudentA(studentA, solution, n);
        solutionsA.push_back(solution);
    }

    for (int i = 0; i < n; i++) {
        string solution;
        cin >> solution;
        InsertStudentA(studentB, solution, n);
        solutionsB.push_back(solution);
    }

    for (int i = 0; i < n; i++) {
        string solution;
        cin >> solution;
        InsertStudentA(studentC, solution, n);
        solutionsC.push_back(solution);
    }

    int scores[3] = {0, 0, 0};

    for (string& solution : solutionsA) {
        if (!CheckSolution(studentB, solution, n) && !CheckSolution(studentC, solution, n))
            scores[0] += 3;
        else if (CheckSolution(studentB, solution, n) && CheckSolution(studentC, solution, n))
            scores[0] += 0;
        else
            scores[0] += 1;
    }

    for (string& solution : solutionsB) {
        if (!CheckSolution(studentA, solution, n) && !CheckSolution(studentC, solution, n))
            scores[1] += 3;
        else if (CheckSolution(studentA, solution, n) && CheckSolution(studentC, solution, n))
            scores[1] += 0;
        else
            scores[1] += 1;
    }

    for (string& solution : solutionsC) {
        if (!CheckSolution(studentA, solution, n) && !CheckSolution(studentB, solution, n))
            scores[2] += 3;
        else if (CheckSolution(studentA, solution, n) && CheckSolution(studentB, solution, n))
            scores[2] += 0;
        else
            scores[2] += 1;
    }

    for (int score : scores) {
        cout << score << " ";
    }
}

