#include <iostream>
#include <vector>

using namespace std;

vector<int> nums;
void addNum(int num) { nums.push_back(num); }

int findKthLargest(int k);

double findMedian() {
  if (nums.size() % 2) {
    return findKthLargest(nums.size() / 2 + 1);
  } else {
    return (findKthLargest(nums.size() / 2 + 1) + findKthLargest(nums.size() / 2)) / 2;
  }
}

vector<int> divide(int startIndex, int endIndex) {
  int v = nums[startIndex + (endIndex - startIndex) / 2], vIndex = startIndex;
  int temp = nums[startIndex];
  nums[startIndex] = v;
  nums[startIndex + (endIndex - startIndex) / 2] = temp;
  int firstBigIndex = startIndex + 1;
  int firstEqualIndex = endIndex;
  for (int i = startIndex + 1; i < endIndex; i++) {
    if (nums[i] < v) {
      firstBigIndex++;
    } else {
      break;
    }
  }
  for (int i = firstEqualIndex - 1; i > firstBigIndex; i++) {
    if (nums[i] == v) {
      firstEqualIndex--;
    } else {
      break;
    }
  }
  for (int i = firstBigIndex; i < firstEqualIndex; i++) {
    if (nums[i] < v) {
      int temp = nums[i];
      nums[i] = nums[firstBigIndex];
      nums[firstBigIndex] = temp;
      firstBigIndex++;
      i--;
    } else if (nums[i] == v) {
      int temp = nums[i];
      nums[i] = nums[firstEqualIndex - 1];
      nums[firstEqualIndex - 1] = temp;
      firstEqualIndex--;
      i--;
    }
    if (i < firstBigIndex)
      i = firstBigIndex;
  }
  int equalSize = endIndex - firstEqualIndex,
      bigSize = firstEqualIndex - firstBigIndex;
  if (nums[firstEqualIndex - 1] <= v)
    bigSize = 0;
  for (int i = 0; i < min(bigSize, equalSize); i++) {
    int temp = nums[firstBigIndex + i];
    nums[firstBigIndex + i] = nums[endIndex - 1 - i];
    nums[endIndex - 1 - i] = temp;
  }
  nums[startIndex] = nums[firstBigIndex - 1];
  nums[firstBigIndex - 1] = v;
  return vector<int>{startIndex, firstBigIndex - 1, firstBigIndex + equalSize,
                     endIndex};
}
int findKthLargest(int k) {
  int targetIndex = nums.size() - k;
  bool finished = false;
  vector<int> indexes = divide(0, nums.size());
  while (!finished) {
    if (targetIndex >= indexes[1] && targetIndex < indexes[2]) {
      finished = true;
      return nums[targetIndex];
    } else if (targetIndex < indexes[1]) {
      indexes = divide(indexes[0], indexes[1]);
    } else if (targetIndex >= indexes[2]) {
      indexes = divide(indexes[2], indexes[3]);
    }
  }
}

int main() {
  addNum(1);
  addNum(2);
  cout << findMedian() << endl;
  addNum(3);
  cout << findMedian() << endl;
}