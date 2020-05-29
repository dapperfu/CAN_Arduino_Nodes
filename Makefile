
.PHONY: format
format:
	find . -print0 -name "*.cpp" -o -name "*.h" | xargs -0 -P8 clang-format -i
