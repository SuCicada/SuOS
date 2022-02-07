CMakeCache = build/CMakeCache.txt
build_dir = build

all: $(CMakeCache)
	$(MAKE) -C $(build_dir)

$(CMakeCache): $(build_dir)
	cd $(build_dir) && cmake ..
.PHONY: $(CMakeCache)

$(build_dir):
	mkdir -p $@
.PHONY: $(build_dir)

clean:
	rm -rf $(build_dir)
