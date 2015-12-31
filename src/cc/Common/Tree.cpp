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

  unique_ptr<BSTNode<int>> buildTreeFigure10_1() {
    unique_ptr<BSTNode<int>> tree( new BSTNode<int>() );
    stack<BSTNode<int> *> todo;
    BSTNode<int> *node = tree.get();
    node->data = 314;
    node->left.reset(new BSTNode<int>());
    node->left->data = 6;
    node->right.reset(new BSTNode<int>());
    node->right->data = 6;
    todo.push(node->right.get());
    node = node->left.get();
    node->left.reset(new BSTNode<int>());
    node->left->data = 271;
    node->right.reset(new BSTNode<int>());
    node->right->data = 561;
    todo.push(node->right.get());
    node = node->left.get();
    node->left.reset(new BSTNode<int>());
    node->left->data = 28;
    node->right.reset(new BSTNode<int>());
    node->right->data = 0;
    node = todo.top();
    todo.pop();
    node->right.reset(new BSTNode<int>());
    node->right->data = 3;
    node = node->right.get();
    node->left.reset(new BSTNode<int>());
    node->left->data = 17;
    node = todo.top();
    todo.pop();
    node->left.reset(new BSTNode<int>());
    node->left->data = 2;
    node->right.reset(new BSTNode<int>());
    node->right->data = 271;
    node->right->right.reset(new BSTNode<int>());
    node->right->right->data = 28;
    node = node->left.get();
    node->right.reset(new BSTNode<int>());
    node->right->data = 1;
    node = node->right.get();
    node->left.reset(new BSTNode<int>());
    node->left->data = 401;
    node->right.reset(new BSTNode<int>());
    node->right->data = 257;
    node->left->right.reset(new BSTNode<int>());
    node->left->right->data = 641;
    return tree;
  }

}
