#include "db.h"
#include <gtest/gtest.h>

TEST(CacheDBTest, Constructor) {
    khyberdb::CacheDB db;
    EXPECT_EQ(db.size(), 0);
}

TEST(CacheDBTest, PutAndGet) {
    khyberdb::CacheDB db;
    db.put("key1", "value1");
    
    auto result = db.get("key1");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), "value1");
}

TEST(CacheDBTest, GetNonExistentKey) {
    khyberdb::CacheDB db;
    auto result = db.get("nonexistent");
    EXPECT_FALSE(result.has_value());
}

TEST(CacheDBTest, Delete) {
    khyberdb::CacheDB db;
    db.put("key1", "value1");
    
    bool deleted = db.delete_key("key1");
    EXPECT_TRUE(deleted);
    EXPECT_EQ(db.size(), 0);
    
    auto result = db.get("key1");
    EXPECT_FALSE(result.has_value());
}

TEST(CacheDBTest, DeleteNonExistentKey) {
    khyberdb::CacheDB db;
    bool deleted = db.delete_key("nonexistent");
    EXPECT_FALSE(deleted);
}

TEST(CacheDBTest, Size) {
    khyberdb::CacheDB db;
    EXPECT_EQ(db.size(), 0);
    
    db.put("key1", "value1");
    EXPECT_EQ(db.size(), 1);
    
    db.put("key2", "value2");
    EXPECT_EQ(db.size(), 2);
    
    db.delete_key("key1");
    EXPECT_EQ(db.size(), 1);
}

TEST(CacheDBTest, OverwriteValue) {
    khyberdb::CacheDB db;
    db.put("key1", "value1");
    db.put("key1", "value2");
    
    auto result = db.get("key1");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), "value2");
    EXPECT_EQ(db.size(), 1);
}

TEST(CacheDBTest, MultipleOperations) {
    khyberdb::CacheDB db;
    
    // Add multiple entries
    db.put("a", "1");
    db.put("b", "2");
    db.put("c", "3");
    EXPECT_EQ(db.size(), 3);
    
    // Verify all exist
    EXPECT_EQ(db.get("a").value(), "1");
    EXPECT_EQ(db.get("b").value(), "2");
    EXPECT_EQ(db.get("c").value(), "3");
    
    // Delete middle entry
    db.delete_key("b");
    EXPECT_EQ(db.size(), 2);
    EXPECT_FALSE(db.get("b").has_value());
    
    // Verify others still exist
    EXPECT_EQ(db.get("a").value(), "1");
    EXPECT_EQ(db.get("c").value(), "3");
}

