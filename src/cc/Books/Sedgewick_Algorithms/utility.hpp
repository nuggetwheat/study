
#include <bitset>
#include <ostream>

template <typename K>
class Node {
public:
  Node() {};
  Node(K k) : key(k) {};
  K key {};
  Node *left {};
  Node *right {};
};

inline int bits(int x, int k, int j) {
  return (x >> k) & ((j << 1) - 1);
}

template<typename T>
inline std::ostream &show_binrep(std::ostream &out, const T& a)
{
  const char* beg = reinterpret_cast<const char*>(&a);
  const char* end = beg + sizeof(a);
  out << a << ",";
  while(beg != end)
    out << std::bitset<CHAR_BIT>(*beg++);
  return out;
}
