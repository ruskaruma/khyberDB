#include "db.h"
#include <CLI/CLI.hpp>
#include <iostream>

enum class Command {
    PUT,
    GET,
    DELETE_KEY,
    SIZE
};

struct CommandArgs {
    Command cmd;
    std::string key;
    std::string value;
};

int main(int argc, char** argv) {
    khyberdb::CacheDB db;
    
    CLI::App app{"khyberDB", "A mini cache DB"};
    app.set_version_flag("--version", "0.1.0");
    app.footer("A cache DB (just a hashmap as a db) in C++");
    
    // Subcommands
    auto putCmd = app.add_subcommand("put", "Insert a key-value pair");
    std::string putKey, putValue;
    putCmd->add_option("key", putKey, "Key to insert")->required();
    putCmd->add_option("value", putValue, "Value to insert")->required();
    
    auto getCmd = app.add_subcommand("get", "Get a value by key");
    std::string getKey;
    getCmd->add_option("key", getKey, "Key to retrieve")->required();
    
    auto delCmd = app.add_subcommand("delete", "Delete a key");
    std::string delKey;
    delCmd->add_option("key", delKey, "Key to delete")->required();
    
    auto sizeCmd = app.add_subcommand("size", "Get the database size");
    
    try {
        app.parse(argc, argv);
        
        if (*putCmd) {
            db.put(putKey, putValue);
            std::cout << "Inserted ('" << putKey << "', '" << putValue << "')\n";
        } else if (*getCmd) {
            auto result = db.get(getKey);
            if (result.has_value()) {
                std::cout << getKey << " => " << result.value() << "\n";
            } else {
                std::cout << "Key '" << getKey << "' not found\n";
            }
        } else if (*delCmd) {
            if (db.delete_key(delKey)) {
                std::cout << "Deleted key '" << delKey << "'\n";
            } else {
                std::cout << "Key '" << delKey << "' not found\n";
            }
        } else if (*sizeCmd) {
            std::cout << "DB size: " << db.size() << "\n";
        } else {
            std::cout << app.help();
        }
    } catch (const CLI::ParseError& e) {
        return app.exit(e);
    }
    
    return 0;
}

