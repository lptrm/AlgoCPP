
#include <algorithm>
#include <cmath>
#include <iostream>
#include <unordered_set>
#include <vector>
int factorial(int n) {
  if (n <= 1) {
    return 1;
  }
  return n * factorial(n - 1);
}
int countUniquePermutations(int maxDigits,
                            const std::vector<int> &combination) {
  int nonZeroCount = combination.size();
  int zeroCount = maxDigits - nonZeroCount;

  std::unordered_set<int> uniqueValues(combination.begin(), combination.end());
  int uniquePermutations = 1;
  int denominator = 1;
  for (int value : uniqueValues) {
    int count = std::count(combination.begin(), combination.end(), value);
    denominator *= factorial(count);
  }
  uniquePermutations = factorial(maxDigits) / denominator;
  return uniquePermutations;
}
int countUniqueSquarePermutations(int maxDigits,
                                  const std::vector<int> &combination) {
  int uniqueSquarePermutations = 1;

  for (int value : combination) {
    if (value == 0) {
      continue; // Skip zero values
    }

    uniqueSquarePermutations *= 2;
  }

  // Include the possibility of zero values in the count
  int zeroCount = maxDigits - combination.size();
  uniqueSquarePermutations *= pow(2, zeroCount);

  return uniqueSquarePermutations;
}
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
    current.push_back(i);
    findSquareCombinations(target, current, currentSum + i * i, i, combinations,
                           digits);
    current.pop_back();
  }
}

int main(int argc, char *argv[]) {
  // if (argc != 3) {
  //   std::cerr << "Usage: " << argv[0] << " <n>" << std::endl;
  //   return 1;
  // }

  int target = 2;
  int digits = 8;
  std::vector<std::vector<int>> combinations;

  std::vector<int> current;
  findSquareCombinations(target * target, current, 0, 1, combinations, digits);

  for (const std::vector<int> &combination : combinations) {
    for (int square : combination) {
      std::cout << square << " ";
    }
    std::cout << std::endl;
  }
  for (const std::vector<int> &combination : combinations) {
    for (int square : combination) {
      std::cout << square << " ";
    }
    int uniquePermutations = countUniquePermutations(digits, combination);
    int uniqueSquarePermutations =
        countUniqueSquarePermutations(digits, combination);
    std::cout << "(Unique Permutations: " << uniquePermutations
              << ", Unique Square Permutations: " << uniqueSquarePermutations
              << ")" << std::endl;
  }
  return 0;
}
