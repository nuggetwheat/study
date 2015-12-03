
#undef NDEBUG

#include <cassert>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

#include "tree.hpp"

using namespace std;
using namespace study;

namespace {

  Node<char> *populate_test_tree() {
    Node<char> *tree, *node;
    tree = new Node<char>('P');
    tree->left = new Node<char>('M');
    node = tree->left;
    node->left = new Node<char>('S');
    node = node->left;
    node->left = new Node<char>('A');
    node->right = new Node<char>('A');
    tree->right = new Node<char>('L');
    node = tree->right;
    node->right = new Node<char>('E');
    node = node->right;
    node->right = new Node<char>('R');
    node = node->right;
    node->left = new Node<char>('T');
    node->right = new Node<char>('E');
    node = node->right;
    node->left = new Node<char>('E');
    return tree;
  }

  const vector<char> expected_output_levelorder {
    'P', 'M', 'L', 'S', 'E', 'A', 'A', 'R', 'T', 'E', 'E'
      };

  const vector<char> expected_output_preorder {
    'P', 'M', 'S', 'A', 'A', 'L', 'E', 'R', 'T', 'E', 'E'
      };

  const vector<char> expected_output_inorder {
    'A', 'S', 'A', 'M', 'P', 'L', 'E', 'T', 'R', 'E', 'E'
      }; 

  const vector<char> expected_output_postorder {
    'A', 'A', 'S', 'M', 'T', 'E', 'E', 'R', 'E', 'L', 'P' 
      };

}

namespace study {

  void test_tree() {
    vector<char> output;
    Node<char> *tree = populate_test_tree();

    // level-order
    output.clear();
    levelorder_traversal(tree, output);
    assert(output == expected_output_levelorder);

    // pre-order
    output.clear();
    preorder_traversal(tree, output);
    assert(output == expected_output_preorder);

    // in-order
    output.clear();
    inorder_traversal(tree, output);
    assert(output == expected_output_inorder);

    // post-order
    output.clear();
    postorder_traversal(tree, output);
    assert(output == expected_output_postorder);

    // pre-order (non-recursive)
    output.clear();
    preorder_traversal_nonrecursive(tree, output);
    assert(output == expected_output_preorder);

    // in-order (non-recursive)
    output.clear();
    inorder_traversal_nonrecursive(tree, output);
    assert(output == expected_output_inorder);

    // post-order (non-recursive)
    output.clear();
    postorder_traversal_nonrecursive(tree, output);
    assert(output == expected_output_postorder);

  }

}
