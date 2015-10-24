
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stack>
#include <stdexcept>
#include <string>
#include <queue>

using namespace std;

enum {
  TT_EOF=1,
  TT_LPAREN,
  TT_RPAREN,
  TT_NUM,
  TT_OP
};

typedef struct {
  int type;
  union {
    char c;
    int num;
  } val;
  int precedence;
} TokenT;

ostream &operator<<(ostream &os, const TokenT &token) {
  os << "TOKEN: ";
  if (token.type == TT_EOF)
    os << "EOF";
  else if (token.type == TT_NUM)
    os << token.val.num;
  else
    os << "'" << token.val.c << "'";
  return os;
}

typedef queue<TokenT> TokenQueueT;

void input_infix_to_postfix_queue(TokenQueueT &pq) {
  TokenT token;
  stack<char> ops;
  char next = ' ';

  while (cin >> next) {

    while (isspace(next)) {
      if (!(cin >> next))
        break;
    }

    if (next == ')') {
      if (ops.empty())
        throw runtime_error("Invalid expression");
      token.type = TT_OP;
      token.val.c = ops.top();
      pq.push(token);
      ops.pop();
    }
    else if (isdigit(next)) {
      string num(1, next);
      while (isdigit(cin.peek())) {
        cin >> next;
        num.append(1, next);
      }
      token.type = TT_NUM;
      token.val.num = atoi(num.c_str());
      pq.push(token);
    }
    else if (next == '+' || next == '-' || next == '*' || next == '/')
      ops.push(next);
  }

  while (!ops.empty()) {
    token.type = TT_OP;
    token.val.c = ops.top();
    pq.push(token);
    ops.pop();
  }
}

int evaluate(TokenQueueT &pq) {
  TokenT left, right, token;
  stack<TokenT> operands;
  while (!pq.empty()) {
    if (pq.front().type == TT_NUM) {
      operands.push(pq.front());
    }
    else if (pq.front().type == TT_OP) {
      if (operands.size() < 2)
        throw runtime_error("Invalid expression");
      left = operands.top();
      operands.pop();
      right = operands.top();
      operands.pop();
      token = left;
      if (pq.front().val.c == '*') 
        token.val.num *= right.val.num;
      else if (pq.front().val.c == '/') 
        token.val.num /= right.val.num;        
      else if (pq.front().val.c == '+') 
        token.val.num += right.val.num;        
      else if (pq.front().val.c == '-') 
        token.val.num -= right.val.num;        
      else
        throw runtime_error("Invalid expression");      
      operands.push(token);
    }
    else
      throw runtime_error("Invalid expression");
    pq.pop();
  }
  if (operands.size() != 1 || operands.top().type != TT_NUM)
    throw runtime_error("Invalid expression");
  return operands.top().val.num;
}

int main(int argc, char **argv) {
  TokenQueueT input;
  input_infix_to_postfix_queue(input);
  cout << evaluate(input);
  return 0;
}
