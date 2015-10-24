
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stack>
#include <stdexcept>
#include <string>

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

int g_lineno = 0;
TokenT g_next_token;

void extract_next_token(TokenT &prev) {
  char next_char;

  if (cin.peek() == EOF) {
    g_next_token.type = TT_EOF;
    return;
  }

  if (!(cin >> next_char)) {
    g_next_token.type = TT_EOF;
    return;
  }
  g_lineno++;

  // skip whitespace
  while (isspace(next_char)) {
    if (!(cin >> next_char)) {
      g_next_token.type = TT_EOF;
      return;
    }
    g_lineno++;
  }

  g_next_token.val.c = next_char;

  if (next_char == '(')
    g_next_token.type = TT_LPAREN;
  else if (next_char == ')')
    g_next_token.type = TT_RPAREN;
  else if (next_char == '*' || next_char == '/') {
    g_next_token.type = TT_OP;
    g_next_token.precedence = 2;
  }
  else if (next_char == '+' ||
           (next_char == '-' && prev.type != TT_OP && prev.type != 0)) {
    g_next_token.type = TT_OP;
    g_next_token.precedence = 1;
  }
  else if (isdigit(next_char) || next_char == '-') {
    bool got_num = isdigit(next_char);
    string num(1, next_char);
    while (isdigit(cin.peek())) {
      cin >> next_char;
      g_lineno++;
      num.append(1, next_char);
      got_num = true;
    }
    if (got_num) {
      g_next_token.type = TT_NUM;
      g_next_token.val.num = atoi(num.c_str());
    }
    else {
      g_next_token.type = TT_OP;
      g_next_token.precedence = 1;
    }
  }
  else {
    cout << "Invalid character '" << next_char << "' encountered at position " << g_lineno << endl;
    exit(1);
  }

}

bool next_token(TokenT &token) {

  if (g_next_token.type == 0)
    extract_next_token(token);

  memcpy(&token, &g_next_token, sizeof(token));

  if (g_next_token.type == TT_EOF)
    return false;

  extract_next_token(token);

  return true;
}

TokenT evaluate(TokenT left, TokenT op, TokenT right) {
  TokenT token;
  token.type = TT_NUM;
  if (op.val.c == '+')
    token.val.num = left.val.num + right.val.num;
  else if (op.val.c == '-')
    token.val.num = left.val.num - right.val.num;
  else if (op.val.c == '*')
    token.val.num = left.val.num * right.val.num;
  else if (op.val.c == '/')
    token.val.num = left.val.num / right.val.num;
  else {
    cout << "Invalid operator '" << op.val.c << "'" << endl;
    exit(1);
  }
  return token;
}

int main(int argc, char **argv) {
  TokenT token, op, ltoken;
  stack<TokenT> state;

  memset(&token, 0, sizeof(token));

  next_token(token);

  while (token.type != TT_EOF) {

    if (token.type == TT_RPAREN) {
      if (state.top().type != TT_NUM)
        break;
      memcpy(&token, &state.top(), sizeof(token));
      state.pop();
      if (state.top().type != TT_LPAREN)
        break;
      state.pop();
      continue;
    }
    else if (token.type == TT_NUM && !state.empty() && state.top().type == TT_OP) {
      if (g_next_token.type != TT_OP || g_next_token.precedence <= token.precedence) {
        memcpy(&op, &state.top(), sizeof(op));
        state.pop();
        if (state.top().type != TT_NUM)
          break;
        memcpy(&ltoken, &state.top(), sizeof(ltoken));
        state.pop();
        token = evaluate(ltoken, op, token);
        continue;
      }
    }
    state.push(token);
    //cout << token << "(next = " << g_next_token << ")" << endl;
    next_token(token);
  }
  if (token.type == TT_EOF && 
      state.size() == 1 && state.top().type == TT_NUM) {
    cout << state.top().val.num << endl;
  }
  else {
    cout << "Mal-formed expression" << endl;
    return 1;
  }
  return 0;
}
