/*
 * The MIT License (MIT)
 * 
 * Copyright (c) 2015 Doug Judd
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "Tree.hpp"

#include <stack>

using namespace std;
using namespace study;

namespace study {

  unique_ptr<BSTNode<int>> buildTreeFigure10_1(bool include_parent) {
    unique_ptr<BSTNode<int>> tree( new BSTNode<int>(314) );
    stack<BSTNode<int> *> todo;
    BSTNode<int> *node = tree.get();
    node->left.reset(new BSTNode<int>(6, include_parent ? node : nullptr));
    node->right.reset(new BSTNode<int>(6, include_parent ? node : nullptr));
    todo.push(node->right.get());
    node = node->left.get();
    node->left.reset(new BSTNode<int>(271, include_parent ? node : nullptr));
    node->right.reset(new BSTNode<int>(561, include_parent ? node : nullptr));
    todo.push(node->right.get());
    node = node->left.get();
    node->left.reset(new BSTNode<int>(28, include_parent ? node : nullptr));
    node->right.reset(new BSTNode<int>(0, include_parent ? node : nullptr));
    node = todo.top();
    todo.pop();
    node->right.reset(new BSTNode<int>(3, include_parent ? node : nullptr));
    node = node->right.get();
    node->left.reset(new BSTNode<int>(17, include_parent ? node : nullptr));
    node = todo.top();
    todo.pop();
    node->left.reset(new BSTNode<int>(2, include_parent ? node : nullptr));
    node->right.reset(new BSTNode<int>(271, include_parent ? node : nullptr));
    node->right->right.reset(new BSTNode<int>(28, include_parent ? node->right.get() : nullptr));
    node = node->left.get();
    node->right.reset(new BSTNode<int>(1, include_parent ? node : nullptr));
    node = node->right.get();
    node->left.reset(new BSTNode<int>(401, include_parent ? node : nullptr));
    node->right.reset(new BSTNode<int>(257, include_parent ? node : nullptr));
    node->left->right.reset(new BSTNode<int>(641, include_parent ? node->left.get() : nullptr));
    return tree;
  }

  unique_ptr<BSTNode<int>> buildTreeFigure10_2(bool include_parent) {
    unique_ptr<BSTNode<int>> tree( new BSTNode<int>() );
    stack<BSTNode<int> *> todo;
    BSTNode<int> *node = tree.get();
    node->left.reset(new BSTNode<int>());
    node->right.reset(new BSTNode<int>());
    todo.push(node->right.get());
    node = node->left.get();
    node->left.reset(new BSTNode<int>());
    node->right.reset(new BSTNode<int>());
    todo.push(node->right.get());
    node = node->left.get();
    node->left.reset(new BSTNode<int>());
    node->right.reset(new BSTNode<int>());
    node = node->left.get();
    node->left.reset(new BSTNode<int>());
    node->right.reset(new BSTNode<int>());
    node = todo.top();
    todo.pop();
    node->left.reset(new BSTNode<int>());
    node->right.reset(new BSTNode<int>());
    node = todo.top();
    todo.pop();
    node->left.reset(new BSTNode<int>());
    node->right.reset(new BSTNode<int>());
    node = node->left.get();
    node->left.reset(new BSTNode<int>());
    node->right.reset(new BSTNode<int>());
    return tree;
  }

  std::unique_ptr<BSTNode<int>> buildTreeFigure10_3a(bool include_parent) {
    std::unique_ptr<BSTNode<int>> tree(new BSTNode<int>());
    BSTNode<int> *lnode, *rnode;
    tree->data = 314;
    tree->left.reset(new BSTNode<int>());
    tree->right.reset(new BSTNode<int>());
    lnode = tree->left.get();
    rnode = tree->right.get();
    lnode->data = rnode->data = 6;
    lnode->right.reset(new BSTNode<int>());
    lnode = lnode->right.get();
    rnode->left.reset(new BSTNode<int>());
    rnode = rnode->left.get();
    lnode->data = rnode->data = 2;
    lnode->right.reset(new BSTNode<int>());
    lnode = lnode->right.get();
    rnode->left.reset(new BSTNode<int>());
    rnode = rnode->left.get();
    lnode->data = rnode->data = 3;
    return tree;
  }

  std::unique_ptr<BSTNode<int>> buildTreeFigure10_3b(bool include_parent) {
    std::unique_ptr<BSTNode<int>> tree(new BSTNode<int>());
    BSTNode<int> *lnode, *rnode;
    tree->data = 314;
    tree->left.reset(new BSTNode<int>());
    tree->right.reset(new BSTNode<int>());
    lnode = tree->left.get();
    rnode = tree->right.get();
    lnode->data = rnode->data = 6;
    lnode->right.reset(new BSTNode<int>());
    lnode = lnode->right.get();
    rnode->left.reset(new BSTNode<int>());
    rnode = rnode->left.get();
    lnode->data = 561;
    rnode->data = 2;
    lnode->right.reset(new BSTNode<int>());
    lnode = lnode->right.get();
    rnode->left.reset(new BSTNode<int>());
    rnode = rnode->left.get();
    lnode->data = 3;
    rnode->data = 1;
    return tree;
  }

  std::unique_ptr<BSTNode<int>> buildTreeFigure10_3c(bool include_parent) {
    std::unique_ptr<BSTNode<int>> tree(new BSTNode<int>());
    BSTNode<int> *lnode, *rnode;
    tree->data = 314;
    tree->left.reset(new BSTNode<int>());
    tree->right.reset(new BSTNode<int>());
    lnode = tree->left.get();
    rnode = tree->right.get();
    lnode->data = rnode->data = 6;
    lnode->right.reset(new BSTNode<int>());
    lnode = lnode->right.get();
    rnode->left.reset(new BSTNode<int>());
    rnode = rnode->left.get();
    lnode->data = rnode->data = 561;
    lnode->right.reset(new BSTNode<int>());
    lnode = lnode->right.get();
    lnode->data = 3;
    return tree;
  }

  std::unique_ptr<BSTNode<int>> buildTreeFigure10_4(bool include_parent) {
    unique_ptr<BSTNode<int>> tree( new BSTNode<int>(1) );
    stack<BSTNode<int> *> todo;
    BSTNode<int> *node = tree.get();
    node->left.reset(new BSTNode<int>(0, include_parent ? node : nullptr));
    node->right.reset(new BSTNode<int>(1, include_parent ? node : nullptr));
    todo.push(node->right.get());
    node = node->left.get();
    node->left.reset(new BSTNode<int>(0, include_parent ? node : nullptr));
    node->right.reset(new BSTNode<int>(1, include_parent ? node : nullptr));
    todo.push(node->right.get());
    node = node->left.get();
    node->left.reset(new BSTNode<int>(0, include_parent ? node : nullptr));
    node->right.reset(new BSTNode<int>(1, include_parent ? node : nullptr));
    node = todo.top();
    todo.pop();
    node->right.reset(new BSTNode<int>(1, include_parent ? node : nullptr));
    node = node->right.get();
    node->left.reset(new BSTNode<int>(0, include_parent ? node : nullptr));
    node = todo.top();
    todo.pop();
    node->left.reset(new BSTNode<int>(0, include_parent ? node : nullptr));
    node->right.reset(new BSTNode<int>(0, include_parent ? node : nullptr));
    node->right->right.reset(new BSTNode<int>(0, include_parent ? node->right.get() : nullptr));
    node = node->left.get();
    node->right.reset(new BSTNode<int>(0, include_parent ? node : nullptr));
    node = node->right.get();
    node->left.reset(new BSTNode<int>(1, include_parent ? node : nullptr));
    node->right.reset(new BSTNode<int>(0, include_parent ? node : nullptr));
    node->left->right.reset(new BSTNode<int>(1, include_parent ? node->left.get() : nullptr));
    return tree;
  }

}
