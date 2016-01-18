
#ifndef Books_CormenIntroductionToAlgorithms_ch11_hpp
#define Books_CormenIntroductionToAlgorithms_ch11_hpp

#include <cstdlib>
#include <tuple>
#include <utility>
#include <vector>

namespace study {

  extern uint32_t Hash(uint32_t key);

  enum class SlotState : unsigned char { AVAILABLE, OCCUPIED, DELETED };

  template <class _Key, class _Value>
  class HashTableOpenAddressLinearProbing {
  public:
    typedef _Key    key_type;
    typedef _Value  value_type;
    struct SlotElement {
      SlotElement() {}
      SlotElement(const key_type &k, const value_type &v, SlotState s)
        : key(k), value(v), state(s) { }
      key_type key {};
      value_type value {};
      SlotState state {SlotState::AVAILABLE};
    };
    typedef SlotElement slot_type;
    HashTableOpenAddressLinearProbing(size_t bucket_count);
    void add(const key_type &key, const value_type &value);
    void remove(const key_type &key);
    bool get(const key_type &key, value_type *value);
  private:
    std::vector<SlotElement> table_;
  };

}

#include "ch11-hash.cpp"

#endif // Books_CormenIntroductionToAlgorithms_ch11_hpp
