hexy: src/board.cpp src/main.cpp
	g++ -std=c++20 -o rokkaku_v_0.01 src/entity.cpp src/line.cpp src/circle.cpp src/board.cpp src/main.cpp -lraylib

run: rokkaku_v_0.01
	./rokkaku_v_0.01

clean:
	rm -f hexy
