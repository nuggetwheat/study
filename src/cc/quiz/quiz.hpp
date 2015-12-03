
#ifndef quiz_quiz_hpp
#define quiz_quiz_hpp

#include <algorithm>
#include <initializer_list>
#include <iterator>
#include <vector>

namespace study {

  struct Item {
    const char *question;
    const char *answer;
  };

  inline void load_section(std::vector<Item> &items,
                           const std::initializer_list<Item> &section) {
    items.reserve(items.size() + section.size());
    std::copy(section.begin(), section.end(), std::back_inserter(items));
  }

}

#endif // quiz_quiz_hpp
