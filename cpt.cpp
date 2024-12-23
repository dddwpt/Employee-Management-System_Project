#include <iostream>
#include <vector>

void drawHistogram(const std::vector<int>& scores) {
    const int range = 10;
    const int n = scores.size();

    std::vector<int> histogram(range, 0);
    for (int i = 0; i < n; i++) {
        int num = scores[i] / 10;
        histogram[num]++;
    }

    std::cout << "直方图：" << std::endl;
    for (int i = 0; i < range; i++) {
        std::cout << i * 10 << "-" << (i * 10) + 9 << ": ";
        for (int j = 0; j < histogram[i]; j++) {
            std::cout << "*";
        }
        std::cout << std::endl;
    }
}

int main() {
    int repert;
    std::cout << "请输入数据组数：";
    std::cin >> repert;

    for (int i = 0; i < repert; i++) {
        int n;
        std::cout << "请输入第 " << i + 1 << " 组数据的打分人数：";
        std::cin >> n;

        std::vector<int> scores(n);

        std::cout << "请输入 " << n << " 个人的打分：" << std::endl;
        for (int j = 0; j < n; j++) {
            std::cin >> scores[j];
        }

        drawHistogram(scores);
    }

    return 0;
}
