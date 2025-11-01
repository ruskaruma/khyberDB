#pragma once

#include <unordered_map>
#include <string>
#include <optional>

namespace khyberdb {

class CacheDB {
public:
    CacheDB();
    
    // inserting data into the cache
    void put(const std::string& key, const std::string& value);
    
    // fetching data from the cache using its key
    std::optional<std::string> get(const std::string& key) const;
    
    // deleting/removing data key from table and returns true/false accordingly
    bool delete_key(const std::string& key);
    
    // how many entries are there in cache
    size_t size() const;

private:
    std::unordered_map<std::string, std::string> store;
};

}

