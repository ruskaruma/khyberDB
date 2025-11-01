#include "db.h"
#include <benchmark/benchmark.h>
#include <string>

static void BM_Put(benchmark::State& state) {
    khyberdb::CacheDB db;
    std::string key = "key_" + std::to_string(state.thread_index());
    
    for (auto _ : state) {
        db.put(key, "value");
    }
    
    state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_Put);

static void BM_Get(benchmark::State& state) {
    khyberdb::CacheDB db;
    std::string key = "key";
    db.put(key, "value");
    
    for (auto _ : state) {
        benchmark::DoNotOptimize(db.get(key));
    }
    
    state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_Get);

static void BM_Delete(benchmark::State& state) {
    khyberdb::CacheDB db;
    std::string key = "key";
    db.put(key, "value");
    
    for (auto _ : state) {
        db.delete_key(key);
        if (state.iterations() == 1) break;
        db.put(key, "value");
    }
    
    state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_Delete);

BENCHMARK_MAIN();

