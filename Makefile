template_matching : template_matching.cpp
	g++ -Wall template_matching.cpp `pkg-config --cflags opencv` `pkg-config --libs opencv`
