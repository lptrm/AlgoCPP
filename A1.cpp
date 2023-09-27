
#include <iostream>
#include <vector>

void findSquareCombinations(int target, std::vector<int> &current,
                            int currentSum, int currentNum,
                            std::vector<std::vector<int>> &combinations,
                            int digits) {
  if (currentSum == target) {
    combinations.push_back(current);
    return;
  }

  if (currentSum > target || currentNum * currentNum > target ||
      current.size() >= digits) {
    return;
  }

  for (int i = currentNum; i * i <= target - currentSum; i++) {
    current.push_back(i * i);
    findSquareCombinations(target, current, currentSum + i * i, i, combinations,
                           digits);
    current.pop_back();
  }
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <n>" << std::endl;
    return 1;
  }

  int target = std::stoi(argv[1]);
  int digits = std::stoi(argv[2]);
  std::vector<std::vector<int>> combinations;

  std::vector<int> current;
  findSquareCombinations(target * target, current, 0, 1, combinations, digits);

  for (const std::vector<int> &combination : combinations) {
    for (int square : combination) {
      std::cout << square << " ";
    }
    std::cout << std::endl;
  }

  return 0;
}
