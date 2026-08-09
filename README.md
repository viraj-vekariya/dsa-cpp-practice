# dsa-cpp-practice

C++ data structures and algorithms practice, organized by difficulty. Each subfolder is a standalone program with its own `main.cpp` and a short README explaining what it does. Everything is plain C++17 — no third-party libraries.

## Build and run

Every project can be built and run directly with g++:

```
g++ -std=c++17 -Wall <folder>/main.cpp -o <folder>/out && ./<folder>/out
```

Or use the root Makefile:

```
make all              # build every project's binary
make run-all          # build and run every project, one after another
make run-<name>       # build and run a single project, e.g. make run-02_lru_cache
make clean            # remove all compiled binaries
```

## Projects

### beginner/

| Folder | Description |
|---|---|
| `01_array_basics` | Reverse an array in place, rotate left by k, find max/min/second-max, brute-force two-sum. |
| `02_string_utilities` | Palindrome check, anagram check, reverse the word order in a sentence, count vowels/consonants. |
| `03_stack_queue_from_scratch` | Stack and queue implemented on a fixed-size array (no `std::stack`/`std::queue`), used to check balanced parentheses. |
| `04_singly_linked_list` | Singly linked list from scratch: insert head/tail, delete by value, reverse, Floyd's cycle detection. |

### intermediate/

| Folder | Description |
|---|---|
| `01_binary_search_tree` | BST with insert, search, delete, all three traversals, and height. |
| `02_hashmap_from_scratch` | Hashmap built as an array of buckets with chaining, not `std::unordered_map`. |
| `03_graph_bfs_dfs` | Adjacency-list graph with BFS, DFS, and connected-components detection. |
| `04_sorting_visualizer_cli` | Bubble sort, merge sort, and quick sort from scratch, benchmarked and compared in a CLI table. |
| `05_recursion_backtracking` | N-Queens solver (all 92 solutions for N=8) and a Sudoku backtracking solver. |

### advanced/

| Folder | Description |
|---|---|
| `01_dijkstra_shortest_path` | Dijkstra's algorithm with `std::priority_queue` on a small road-network simulation. |
| `02_lru_cache` | O(1) get/put LRU cache using a doubly linked list + hashmap. |
| `03_trie_autocomplete` | Trie with insert/search/startsWith and a prefix-based autocomplete function. |
| `04_union_find_kruskal` | Union-find with path compression and union by rank, driving Kruskal's MST algorithm. |
