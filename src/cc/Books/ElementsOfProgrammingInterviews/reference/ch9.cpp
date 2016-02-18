
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

namespace reference {

  StackWithMax::StackWithMax() {
    state_ = new stack_with_max_state;
  }

  StackWithMax::~StackWithMax() {
    stack_with_max_state *state = (stack_with_max_state *)state_;
    delete state;
  }

  void StackWithMax::push(int x) {
    stack_with_max_state *state = (stack_with_max_state *)state_;
    if (state->max.empty() || state->max.back().first < x)
      state->max.push_back(make_pair(x, 1));
    else
      state->max.back().second++;
    state->values.push_back(x);
  }

  int StackWithMax::pop() {
    stack_with_max_state *state = (stack_with_max_state *)state_;
    assert(!state->values.empty() && !state->max.empty());
    int ret = state->values.back();
    state->values.pop_back();
    if (--(state->max.back().second) == 0)
      state->max.pop_back();
    return ret;
  }

  int StackWithMax::max() const {
    stack_with_max_state *state = (stack_with_max_state *)state_;
    assert(!state->max.empty());
    return state->max.back().first;
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

  std::vector<int> BSTInSortedOrder(const std::unique_ptr<study::BSTNode<int>> &tree) {
    std::vector<int> results;
    stack<const study::BSTNode<int> *> tbd;
    const study::BSTNode<int> *node = tree.get();
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

    void SetJumpOrderRecursiveHelper(const std::shared_ptr<PostingListNode> &node, int *order) {
      if (node && node->order == -1) {
        node->order = (*order)++;
        SetJumpOrderRecursiveHelper(node->jump, order);
        SetJumpOrderRecursiveHelper(node->next, order);
      }
    }

    void SetJumpOrderRecursive(const std::shared_ptr<PostingListNode> &list) {
      int order = 0;
      SetJumpOrderRecursiveHelper(list, &order);
    }

    void SetJumpOrderIterative(const std::shared_ptr<PostingListNode> &list) {
      if (list) {
        int order = 0;
        stack<std::shared_ptr<PostingListNode>> tbd;
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

  std::vector<std::vector<int>> BinaryTreeDepthOrder(const std::unique_ptr<study::BSTNode<int>> &tree) {
    vector<vector<int>> result;
    queue<study::BSTNode<int> *> next;
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
    estack_.push(x);
  }

  int QueueImplementedWithStacks::dequeue() {
    int ret;
    if (dstack_.empty()) {
      while (!estack_.empty()) {
        dstack_.push(estack_.top());
        estack_.pop();
      }
    }
    else if (!estack_.empty()) {
      stack<int> tmp;
      while (!dstack_.empty()) {
        tmp.push(dstack_.top());
        dstack_.pop();
      }
      while (!estack_.empty()) {
        dstack_.push(estack_.top());
        estack_.pop();
      }
      while (!tmp.empty()) {
        dstack_.push(tmp.top());
        tmp.pop();
      }
    }
    assert(!dstack_.empty());
    ret = dstack_.top();
    dstack_.pop();
    return ret;
  }

  QueueWithMax::QueueWithMax() {
    state_ = new queue_with_max_state;
  }

  QueueWithMax::~QueueWithMax() {
    queue_with_max_state *state = (queue_with_max_state *)state_;
    delete state;
  }

  void QueueWithMax::enqueue(int x) {
    queue_with_max_state *state = (queue_with_max_state *)state_;
    while (!state->max.empty() && state->max.back() < x)
      state->max.pop_back();
    state->max.push_back(x);
    state->values.push(x);
  }

  int QueueWithMax::dequeue() {
    queue_with_max_state *state = (queue_with_max_state *)state_;
    assert(!state->values.empty() && !state->max.empty());
    int ret = state->values.front();
    state->values.pop();
    if (state->max.front() == ret)
      state->max.pop_front();
    return ret;
  }

  int QueueWithMax::max() const {
    queue_with_max_state *state = (queue_with_max_state *)state_;
    assert(!state->max.empty());
    return state->max.front();
  }
}
