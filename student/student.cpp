#include <iostream>
#include<vector>

using namespace std;

class Student {
 public:
  Student(char const *name, int score1, int score2, int score3) {
    this->name = name;
    this->score1 = score1;
    this->score2 = score2;
    this->score3 = score3;
  }
  void display() const {
    cout << name << ": " << score1 + score2 + score3 << endl;
  }
  char const *name;
  int score1, score2, score3;
  friend bool operator<(const Student &a, const Student &b);
};
bool operator<(const Student &a, const Student &b) {
  return a.score1 + a.score2 + a.score3 < b.score1 + b.score2 + b.score3;
}

int test() {
  Student ss[]{
      Student("s1", 71, 72, 73),
      Student("s2", 72, 73, 74),
      Student("s3", 69, 70, 71),
      Student("s4", 60, 70, 71),
  };

  bool keep = true;
  while (keep) {
    keep = false;

    for (int i = 0; i < 3; i++) {
      if (!(ss[i] < ss[i + 1])) {
        Student swap = ss[i];
        ss[i] = ss[i + 1];
        ss[i + 1] = swap;
        keep = true;
      }
    }
  }

  for (auto &s : ss) {
    s.display();
  }
}