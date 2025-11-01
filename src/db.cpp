#include "db.h"

namespace khyberdb {

CacheDB::CacheDB() : store{} {}

void CacheDB::put(const std::string& key, const std::string& value) {
    store[key] = value;
}

std::optional<std::string> CacheDB::get(const std::string& key) const {
    auto it = store.find(key);
    if (it != store.end()) {
        return it->second;
    }
    return std::nullopt;
}

bool CacheDB::delete_key(const std::string& key) {
    return store.erase(key) > 0;
}

size_t CacheDB::size() const {
    return store.size();
}

}

