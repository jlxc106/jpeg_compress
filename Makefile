all:
	g++ -o main main.cpp -I.. -Wall -Wextra -Wfatal-errors -std=c++11 -pedantic -Dcimg_use_vt100 -Dcimg_display=1   -lm -lX11 -lpthread 
	g++ -o test test.cpp -I.. -Wall -Wextra -Wfatal-errors -std=c++11 -pedantic -Dcimg_use_vt100 -Dcimg_display=1   -lm -lX11 -lpthread 


