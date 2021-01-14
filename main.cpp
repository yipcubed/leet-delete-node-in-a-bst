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
    if (key < root->val) {
      root->left = deleteNode(root->left, key);
    } else if (key > root->val) {
      root->right = deleteNode(root->right, key);
    } else {
      // found key
      if (root->left && root->right) {
        // have 2 children
        // find smallest larger than root
        auto *rt = root->right;
        while (rt->left) {
          rt = rt->left;
        }
        root->val = rt->val;
        // need to delete rt from right branch
        root->right = deleteNode(root->right, rt->val);
      } else if (root->left) {
        return root->left;
      } else {
        return root->right;
      }
    }
    return root;
  }

  // sticks the left-subtree from key under the inorder-successor
  // creates very unbalanced trees quickly
  TreeNode *deleteNode2(TreeNode *root, int key) {
    if (!root)
      return nullptr;
    if (root->val == key) {
      if (root->left && root->right) {
        auto *newroot = root->right;
        while (newroot->left)
          newroot = newroot->left;
        PV1(newroot->val);
        newroot->left = root->left;
        newroot = root->right;
        return newroot;
      } else if (root->left) {
        return root->left;
      } else // root->right must exist
        return root->right;
    } else if (root->val > key) {
      root->left = deleteNode(root->left, key);
    } else {
      root->right = deleteNode(root->right, key);
    }
    return root;
  }
};

bool sameTree(TreeNode *a, TreeNode *b) {
  if (!a && !b)
    return true;
  return (a && b && a->val == b->val && sameTree(a->left, b->left) &&
          sameTree(a->right, b->right));
}
void test1() {
  Solution s;
  //   vector<int> v{5, 3, 6, 2, 4, INT_MIN, 7};
  vector<int> v{10, 3, 20, 2, 4, 15, 30, 1, INT_MIN, INT_MIN, INT_MIN, 12, 16};
  for (int elt : v) {
    if (elt == INT_MIN)
      continue;
    auto *tx = new TreeNode(v);
    auto *ty = new TreeNode(v);
    auto *t1 = s.deleteNode(tx, elt);
    cout << t1 << endl;
    auto *t2 = s.deleteNode2(ty, elt);
    cout << t2 << endl;
    return;
    if (!sameTree(t1, t2)) {
      cout << t1 << endl;
      cout << t2 << endl;
      return;
    }
  }
}

void test2() {}

void test3() {}