#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <utility>
#include <cstdlib>
#include <algorithm>
#include <set>

using namespace std;

struct Answer {
    int64_t a, b, c;
};

Answer GetAnswer(const std::vector<int64_t>& num) {
    if (num.size() < 3) {
        return { 0, 0, 0 };
    }

    multiset<int64_t> numis_ = { num[0], num[1], num[2] };

    int64_t first_ = *numis_.begin();
    int64_t second_ = *(++numis_.begin());
    int64_t third_ = *(--numis_.end());

    int64_t first_min = *numis_.begin();
    int64_t second_min = *(++numis_.begin());

    if (num.size() > 3) {
        for (uint64_t i = 3; i < num.size(); ++i) {
            if (num[i] > third_) {
                first_ = second_;
                second_ = third_;
                third_ = num[i];
            }
            else if (num[i] > second_) {
                first_ = second_;
                second_ = num[i];
            }
            else if (num[i] > first_) {
                first_ = num[i];
            }

            if (num[i] < first_min) {
                second_min = first_min;
                first_min = num[i];
            }
            else if (num[i] < second_min) {
                second_min = num[i];
            }
        }
    }
    else {
        return { first_, second_, third_ };
    }
    
    if (third_ <= 0) {
        return { first_, second_, third_ };
    }
  
    int64_t umn1 = first_ * second_;
    int64_t umn2 = first_min * second_min;

    if (umn1 > 0) {
        if (umn2 > 0) {
            if (umn1 > umn2) {
                return { first_, second_, third_ };
            }
            else {
                return { first_min, second_min, third_ };
            }
        }
        else {
            return { first_, second_, third_ };
        }
    }
    else {
        if (umn2 > 0) {
            return { first_min, second_min, third_ };
        }
        else {
            if (abs(umn1) < abs(umn2)) {
                return { first_, second_, third_ };
            }
            else {
                return { first_min, second_min, third_ };
            }
        }
    }

    return  { first_, second_, third_ };
}

int main() {
    std::vector<int64_t> numbers;
    string line;
    getline(cin, line);
    string num = ""s;
    for (char a : line) {
        if (a == ' ' && num != ""s) {
            numbers.push_back(stoi(num));
            num = ""s;
        }
        else if (a != ' ') {
            num += a;
        }
    }

    if (num != ""s) {
        numbers.push_back(stoi(num));
    }

    auto ans = GetAnswer(numbers);

    std::cout << ans.a << " "s << ans.b << " "s << ans.c << std::endl;

    return 0;
}
