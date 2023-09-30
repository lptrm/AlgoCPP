
#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <ostream>
#include <string>
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
  int negatedPermutations = 1;
  for (int value : uniqueValues) {
    int count = std::count(combination.begin(), combination.end(), value);
    denominator *= factorial(count);
    negatedPermutations *= pow(2, count);
  }
  uniquePermutations =
      factorial(maxDigits) / (denominator * factorial(zeroCount));
  return negatedPermutations * uniquePermutations;
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
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <n>" << std::endl;
    return 1;
  }

  int target = std::stoi(argv[1]);
  int digits = std::stoi(argv[2]);
  std::vector<std::vector<int>> combinations;

  std::vector<int> current;
  auto start = std::chrono::high_resolution_clock::now();
  findSquareCombinations(target * target, current, 0, 1, combinations, digits);
  int permutations = 0;
  for (const std::vector<int> &combination : combinations) {
    for (int square : combination) {
      std::cout << square << " ";
    }
    int uniquePermutations = countUniquePermutations(digits, combination);
    permutations += uniquePermutations;

    std::cout << "(Unique Permutations: " << uniquePermutations << std::endl;
  }
  auto end = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  ;
  std::cout << "Total Permutations " << permutations << std::endl;
  std::cout << "Took: " << duration.count() << " mcs" << std::endl;
  return 0;
}
