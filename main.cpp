
#include <cstdio>
#include <loguru.hpp>

int main() {
    LOG_F(INFO, "first %d", 200);
    LOG_F(INFO, "first");
    LOG_F(INFO, "first %d", 300);
    LOG_F(INFO, "first %s", "输入法字符串");
}