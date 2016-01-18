
#include <functional>
#include <stdexcept>

namespace study {

  template <class _Key, class _Value>
  HashTableOpenAddressLinearProbing<_Key, _Value>::HashTableOpenAddressLinearProbing(size_t bucket_count)
    : table_(bucket_count) {
  }

  template <class _Key, class _Value>
  void HashTableOpenAddressLinearProbing<_Key, _Value>::add(const key_type &key, const value_type &value) {
    size_t h = std::hash<key_type>()(key);
    for (size_t i=0; i<table_.size(); ++i) {
      size_t slot = (h+i) % table_.size();
      if (table_[slot].state == SlotState::AVAILABLE) {
        table_[slot].key = key;
        table_[slot].value = value;
        table_[slot].state = SlotState::OCCUPIED;
        return;
      }
    }
    throw std::runtime_error("table is full");
  }

  template <class _Key, class _Value>
  void HashTableOpenAddressLinearProbing<_Key, _Value>::remove(const key_type &key) {
    size_t h = std::hash<key_type>()(key);
    for (size_t i=0; i<table_.size(); ++i) {
      size_t slot = (h+i) % table_.size();
      if (table_[slot].state == SlotState::AVAILABLE) {
        throw std::runtime_error(std::string("Attempt to remove key ") +
                                 std::to_string(key) + std::string(" but empty slot ") +
                                 std::to_string(slot) + std::string(" (") +
                                 std::to_string(i) + std::string(") encountered"));
      }
      if (table_[slot].key == key) {
        // move slots over to fill gap
        size_t empty_slot = slot++;
        for (size_t j=0; j<table_.size()-1; ++j) {
          slot %= table_.size();
          if (table_[slot].state == SlotState::AVAILABLE) {
            table_[empty_slot].state = SlotState::AVAILABLE;
            return;
          }
          else {
            size_t home_slot = std::hash<key_type>()(table_[slot].key) % table_.size();
            if ((slot > empty_slot && (home_slot <= empty_slot || home_slot > slot)) ||
                (slot < empty_slot && (home_slot <= empty_slot && home_slot > slot))) {
              table_[empty_slot] = table_[slot];
              empty_slot = slot;
              table_[empty_slot].state = SlotState::AVAILABLE;
            }
          }
          ++slot;
        }
      }
    }
  }

  template <class _Key, class _Value>
  bool HashTableOpenAddressLinearProbing<_Key, _Value>::get(const key_type &key, value_type *value) {
    size_t h = std::hash<key_type>()(key);
    for (size_t i=0; i<table_.size(); ++i) {
      size_t slot = (h+i) % table_.size();
      if (table_[slot].state == SlotState::AVAILABLE)
        break;
      if (table_[slot].key == key) {
        *value = table_[slot].value;
        return true;
      }
    }
    return false;
  }

}
