#include <iostream>
#include<vector>

using namespace std;

class Test {
  int x, y;
 public:
  Test(int x = 5, int y = 10) {
    this->x = x;
    this->y = y;
  }
  void disp() {
    cout << "x=" << x << ",y=" << y << endl;
  }
  Test operator++() {
    Test t = *this;
    ++x, ++y;
    return t;
  }
};
int xx() {
  Test t1, t2(10, 5);
  t1.disp();
  t2.disp();
  (++t2).disp();
  return 0;
}

class Time {
 public:
  Time(int hour, int minute, int second) {
    this->hour = hour;
    this->minute = minute;
    this->second = second;
  }
  friend Time operator+(const Time &a, int n);
  void Display() {
    cout << hour << ":" << minute << ":" << second << endl;
  }
 private:
  int hour, minute, second;
};

Time operator+(const Time &a, int n) {
  int seconds = n;
  seconds += a.hour * 3600;
  seconds += a.minute * 60;
  seconds += a.second;
  seconds = seconds % 86400;

  return Time(seconds % 3600, seconds % 60, seconds % (3600 * 60));
}

int qq() {
  Time t(23, 59, 59);
  (t + 1).Display();
  t.Display();
}

class Furniture {
 public:
  void SetWeight(int i) {
    m_weight = i;
  }
  int GetWeight() {
    return m_weight;
  }
  void Move(int i) {
    cout << "move";
  }
 protected:
  int m_weight;
};

class Bed : virtual public Furniture {
 public:
  void Sleep() {
    cout << "sleep" << endl;
  }
};

class Sofa : virtual public Furniture {
 public:
  void WatchTV() {
    cout << "watch" << endl;
  }
};

class SofaBed : public Bed, public Sofa {
 public:
  void FoldOut() {
    cout << "foldout" << endl;
  }
};

int f() {
  SofaBed ss;

  ss.SetWeight(20);
  cout << ss.GetWeight() << endl;
  ss.Move(1);

  return 0;
}

class A {
  int *v;
  int s;
 public:
  A(int a[], int n);
  ~A() {
    delete[]v;
  }
  int size() {
    return s;
  }
  int &operator[](int i);
};

A::A(int *a, int n) {
  if (n <= 0) {
    v = NULL;
    s = 0;
    return;
  }

  s = n;
  v = new int[n];
  for (int i = 0; i < n; i++) {
    v[i] = a[i];
  }
}

int &A::operator[](int i) {
  return v[i];
}


