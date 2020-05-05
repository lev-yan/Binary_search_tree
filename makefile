all:binary_tree.cpp
	@./loading.sh
	@g++ -g -pthread binary_tree.cpp -o tree
	@./tree
	@ctags -R
clean:
	rm tree
