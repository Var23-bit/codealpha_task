#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
float calculateGPA(const vector<pair<float, int>>& courses) {
    float totalPoints = 0;
    int totalCredits = 0;
    for (const auto& course : courses) {
        totalPoints += course.first * course.second;
        totalCredits += course.second;
    }
    if (totalCredits == 0) return 0;
    return totalPoints / totalCredits;
}
float calculateCGPA(const vector<vector<pair<float, int>>>& semesters) {
    float totalPoints = 0;
    int totalCredits = 0;
    for (const auto& semester : semesters) {
        for (const auto& course : semester) {
            totalPoints += course.first * course.second;
            totalCredits += course.second;
        }
    }
    if (totalCredits == 0) return 0;
    return totalPoints / totalCredits;
}

int main() {
    int numSemesters;
    cout << "Enter the number of semesters: ";
    cin >> numSemesters;

    vector<vector<pair<float, int>>> semesters(numSemesters);

    for (int i = 0; i < numSemesters; ++i) {
        int numCourses;
        cout << "Enter the number of courses for semester " << i + 1 << ": ";
        cin >> numCourses;

        for (int j = 0; j < numCourses; ++j) {
            float grade;
            int credits;
            cout << "Enter grade for course " << j + 1 << ": ";
            cin >> grade;
            cout << "Enter credits for course " << j + 1 << ": ";
            cin >> credits;
            semesters[i].push_back(make_pair(grade, credits));
        }
    }
    for (int i = 0; i < numSemesters; ++i) {
        float gpa = calculateGPA(semesters[i]);
        cout << "GPA for semester " << i + 1 << ": " << fixed << setprecision(2) << gpa << endl;
    }
    float cgpa = calculateCGPA(semesters);
    cout << "CGPA: " << fixed << setprecision(2) << cgpa << endl;
    return 0;
}
    
