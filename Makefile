CXX = g++
CXXFLAGS = -std=c++17 -Wall

PROJECTS = \
	beginner/01_array_basics \
	beginner/02_string_utilities \
	beginner/03_stack_queue_from_scratch \
	beginner/04_singly_linked_list \
	intermediate/01_binary_search_tree \
	intermediate/02_hashmap_from_scratch \
	intermediate/03_graph_bfs_dfs \
	intermediate/04_sorting_visualizer_cli \
	intermediate/05_recursion_backtracking \
	advanced/01_dijkstra_shortest_path \
	advanced/02_lru_cache \
	advanced/03_trie_autocomplete \
	advanced/04_union_find_kruskal \
	advanced/05_segment_tree

.PHONY: all run-all clean $(PROJECTS)

# `make` with no target builds every project's binary
all: $(PROJECTS)

$(PROJECTS):
	$(CXX) $(CXXFLAGS) $@/main.cpp -o $@/out

# a "run-<name>" target for every project, e.g:
#   make run-01_array_basics
#   make run-02_lru_cache
define RUN_RULE
run-$(notdir $(1)): $(1)
	./$(1)/out
endef
$(foreach p,$(PROJECTS),$(eval $(call RUN_RULE,$(p))))

# builds and runs every project in order
run-all: all
	@for p in $(PROJECTS); do \
		echo "=== $$p ==="; \
		./$$p/out; \
		echo; \
	done

clean:
	@for p in $(PROJECTS); do rm -f $$p/out; done
