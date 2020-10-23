//
// Created by Youi on 2020-10-23.
//

#include <iostream>
#include<vector>

#define TICK(X) clock_t X = clock()
#define TOCK(X) printf("time %s: %g sec.\n", (#X), (double)(clock() - (X)) / CLOCKS_PER_SEC)

int x2dm(const char *s) {
  int d = 0;
  for (int i = 0; i < 4; i++) {
    char x = s[i];
    if (x > '9') {
      d = d * 16 + (x - ('A' - 10));
    } else {
      d = d * 16 + (x - '0');
    }
  }

  return d;
}

int x2dmod(const char *s) {
  int d = 0;
  for (int i = 0; s[i] != 0; i++) {
    char x = s[i];
    if (x > '9') {
      d = d * 16 + x % ('A' - 10) % '0';
    } else {
      d = d * 16 + x % '0';
    }
  }
  return d;
}

int main() {
  TICK(TIME_A);
  {
    printf("%d\n", x2dm("1A5C"));
    int i = 0;
    while (i++ < 1e9) {
      x2dm("1A5C");
    }
  }
  TOCK(TIME_A);

  TICK(TIME_B);
  {
    printf("%d\n", x2dmod("1A5C"));
    int i = 0;
    while (i++ < 1e9) {
      x2dmod("1A5C");
    }
  }
  TOCK(TIME_B);
}