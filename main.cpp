#include <algorithm>
#include <climits>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#include "../utils/PrintUtils.hpp"
#include "../utils/VectorUtils.hpp"

// https://leetcode.com/problems/find-pivot-index/

// #include "../utils/HeapUtils.hpp"
// #include "../utils/BinarySearch.hpp"
#include "../utils/TreeUtils.hpp"

using namespace std;

#pragma GCC diagnostic ignored "-Wunknown-pragmas"

// Live coding problems, watch at
// https://www.twitch.tv/yipcubed
// https://www.youtube.com/channel/UCTV_UOPu7EWXvYWsBFxMsSA/videos
//

// makes code faster, but larger. Just for LeetCode fun!
#pragma GCC optimise("Ofast")

// makes stdin not synced so it is faster. Just for LeetCode fun!
static auto __ __attribute__((unused)) = []() { // NOLINT
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  return nullptr;
}();

class Solution {
public:
  TreeNode *deleteNode(TreeNode *root, int key) {
    if (!root)
      return nullptr;
    PV2(key, root);
    if (key < root->val) {
      root->left = deleteNode(root->left, key);
    } else if (key > root->val) {
      root->right = deleteNode(root->right, key);
    } else {
      // found key
      if (root->left && root->right) {
        // have 2 children
        // find smallest larger than root
        TreeNode *rt = root->right;
        while (rt->left) {
          rt = rt->left;
        }
        root->val = rt->val;
        // need to delete rt from right branch
        root->right = deleteNode(root->right, rt->val);
      } else if (root->left) {
        root = root->left;
      } else {
        root = root->right;
      }
    }
    return root;
  }
};

void test1() {
  Solution s;
  vector<int> v{5, 3, 6, 2, 4, INT_MIN, 7};
  auto *tx = new TreeNode(v);
  cout << *tx << endl;
  TreeNode *result = s.deleteNode(tx, 3);
  cout << *result << endl;
}

void test2() {}

void test3() {}