build:
	cl binary_tree.cpp test.cpp
	
clean: 
	del binary_tree.obj test.obj binary_tree.exe
	
buildr:
	cl binary_tree.cpp test.cpp
	binary_tree.exe
