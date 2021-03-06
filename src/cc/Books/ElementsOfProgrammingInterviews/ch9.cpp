
#include "ch9.hpp"

#include <algorithm>
#include <cassert>
#include <cctype>
#include <deque>
#include <fstream>
#include <iostream>
#include <istream>
#include <map>
#include <queue>
#include <random>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

extern "C" {
#include <math.h>
}

using namespace std;

namespace {
  std::default_random_engine dre;

  struct stack_with_max_state {
    vector<int> values;
    vector<pair<int, int>> max;
  };

  struct queue_with_max_state {
    queue<int> values;
    deque<int> max;
  };
}

namespace study {

  void StackWithMax::push(int x) {
    reference::StackWithMax::push(x);
  }

  int StackWithMax::pop() {
    return reference::StackWithMax::pop();
  }

  int StackWithMax::max() const {
    return reference::StackWithMax::max();
  }

  bool isOperator(const string &token) {
    return token == "+" || token == "-" || token == "*" || token == "/";
  }

  std::string PolishToReversePolish(const std::string &expression) {
    stack<string> tstack;
    stringstream ss(expression);
    string token;
    while (getline(ss, token, ',')) {
      if (token == "+" || token == "-" || token == "*" || token == "/") {
        tstack.push(token);
      }
      else {
        while (!tstack.empty() && !isOperator(tstack.top())) {
          auto left = tstack.top();
          tstack.pop();
          assert(!tstack.empty() && isOperator(tstack.top()));
          auto op = tstack.top();
          tstack.pop();
          token = left + "," + token + "," + op;
        }
        tstack.push(token);
      }
    }
    assert(tstack.size() == 1);
    return tstack.top();
  }

  std::string ReversePolishToPolish(const std::string &expression) {
    stack<string> estack;
    stringstream ss(expression);
    string token;
    
    while (getline(ss, token, ',')) {
      if (token == "+" || token == "-" || token == "*" || token == "/") {
        assert(estack.size() >= 2);
        std::string expr(token);
        expr.append(",");
        auto right = estack.top();
        estack.pop();
        auto left = estack.top();
        estack.pop();
        expr.append(left);
        expr.append(",");
        expr.append(right);
        estack.push(expr);
      }
      else
        estack.push(token);
    }
    assert(estack.size() == 1);
    return estack.top();
  }


  int EvalReversePolish(const std::string &expression) {
    stack<int> state;
    stringstream ss(expression);
    string token;
    
    while (getline(ss, token, ',')) {
      if (token == "+" || token == "-" || token == "*" || token == "/") {
        assert(state.size() >= 2);
        int operand2 = state.top();
        state.pop();
        int operand1 = state.top();
        state.pop();
        if (token == "+")
          state.emplace(operand1 + operand2);
        else if (token == "-")
          state.emplace(operand1 + operand2);
        else if (token == "*")
          state.emplace(operand1 * operand2);
        else if (token == "/")
          state.emplace(operand1 / operand2);
      }
      else
        state.emplace(stoi(token));
    }
    assert(state.size() == 1);
    return state.top();
  }

  int EvalPolish(const std::string &expression) {
    return EvalReversePolish(PolishToReversePolish(expression));
  }

  bool matching(char open, char close) {
    return (open == '(' && close == ')') ||
      (open == '{' && close == '}') ||
      (open == '[' && close == ']');
  }

  bool IsWellFormed(const std::string &expr) {
    stack<char> open;
    for (size_t i=0; i<expr.size(); ++i) {
      if (expr[i] == '(' || expr[i] == '{' || expr[i] == '[')
        open.push(expr[i]);
      else {
        assert(expr[i] == ')' || expr[i] == '}' || expr[i] == ']');
        if (open.empty() || !matching(open.top(), expr[i]))
          return false;
        open.pop();
      }
    }
    return open.empty();
  }

  std::string ShortestEquivalentPath(const std::string &path) {
    vector<std::string> components;
    stringstream ss(path);
    string token;
    bool isAbsolute {};
    bool trailingSlash {};

    if (!path.empty()) {
      isAbsolute = path.front() == '/';
      trailingSlash = path.back() == '/';
      while (getline(ss, token, '/')) {
        if (token == "..") {
          if (!components.empty())
            components.pop_back();
          else
            components.push_back(token);
        }
        else if (token == ".") {
          if (components.empty())
            components.push_back(token);
        }
        else if (!token.empty())
          components.push_back(token);
      }
    }
    string canonical_path;
    if (isAbsolute)
      canonical_path.append(1, '/');
    bool first {true};
    for (const auto &component : components) {
      if (first)
        first = false;
      else
        canonical_path.append(1, '/');
      canonical_path.append(component);
    }
    if (trailingSlash)
      canonical_path.append(1, '/');

    return canonical_path;
  }

  std::vector<int> BSTInSortedOrder(const std::unique_ptr<BSTNode<int>> &tree) {
    std::vector<int> results;
    stack<const BSTNode<int> *> tbd;
    const BSTNode<int> *node = tree.get();
    while (node) {
      while (node) {
        tbd.push(node);
        node = node->left.get();
      }
      do {
        node = tbd.top();
        tbd.pop();
        results.push_back(node->data);
        node = node->right.get();
      } while (!tbd.empty() && node == nullptr);
    }
    return results;
  }

    void SetJumpOrderRecursiveHelper(const std::shared_ptr<reference::PostingListNode> &node, int *order) {
      if (node && node->order == -1) {
        node->order = (*order)++;
        SetJumpOrderRecursiveHelper(node->jump, order);
        SetJumpOrderRecursiveHelper(node->next, order);
      }
    }

    void SetJumpOrderRecursive(const std::shared_ptr<reference::PostingListNode> &list) {
      int order = 0;
      SetJumpOrderRecursiveHelper(list, &order);
    }

    void SetJumpOrderIterative(const std::shared_ptr<reference::PostingListNode> &list) {
      if (list) {
        int order = 0;
        stack<std::shared_ptr<reference::PostingListNode>> tbd;
        tbd.push(list);
        while (!tbd.empty()) {
          auto node = tbd.top();
          tbd.pop();
          if (node->order == -1) {
            node->order = order++;
            if (node->next)
              tbd.push(node->next);
            if (node->jump)
              tbd.push(node->jump);
          }
        }
      }
    }

  std::vector<size_t> ExamineBuildingsWithSunset(std::istringstream *sin) {
    stack<pair<size_t,size_t>> candidates;
    size_t height;
    size_t i {};
    while (*sin >> height) {
      while (!candidates.empty() && height > candidates.top().second)
        candidates.pop();
      candidates.push(make_pair(i++, height));
    }
    vector<size_t> views;
    views.reserve(candidates.size());
    while (!candidates.empty()) {
      views.push_back(candidates.top().first);
      candidates.pop();
    }
    return views;
  }

  void insert(int val, std::stack<int> *sp) {
    if (sp->empty() || sp->top() <= val)
      sp->push(val);
    else {
      int tmp = sp->top();
      sp->pop();
      insert(val, sp);
      sp->push(tmp);
    }
  }

  void SortDescending(std::stack<int> *sp) {
    if (!sp->empty()) {
      int tmp = sp->top();
      sp->pop();
      SortDescending(sp);
      insert(tmp, sp);
    }
  }

  std::vector<std::vector<int>> BinaryTreeDepthOrder(const std::unique_ptr<BSTNode<int>> &tree) {
    vector<vector<int>> result;
    queue<BSTNode<int> *> next;
    next.push(tree.get());
    while (!next.empty()) {
      vector<int> level;
      auto nelem = next.size();
      for (size_t i=0; i<nelem; ++i) {
        level.push_back(next.front()->data);
        if (next.front()->left)
          next.push(next.front()->left.get());
        if (next.front()->right)
          next.push(next.front()->right.get());
        next.pop();
      }
      result.push_back(level);
    }
    return result;
  }

  void QueueImplementedWithStacks::enqueue(int x){
    reference::QueueImplementedWithStacks::enqueue(x);
  }

  int QueueImplementedWithStacks::dequeue() {
    return reference::QueueImplementedWithStacks::dequeue();
  }

  void QueueWithMax::enqueue(int x) {
    reference::QueueWithMax::enqueue(x);
  }

  int QueueWithMax::dequeue() {
    return reference::QueueWithMax::dequeue();
  }

  int QueueWithMax::max() const {
    return reference::QueueWithMax::max();
  }
}
