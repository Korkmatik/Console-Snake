SRC = src
OBJECT = obj
DEBUG_dir = build/debug
RELEASE_dir = build/release

$(DEBUG_dir)/snake.x: $(SRC)/*.cpp
	g++ -g $^ -o $@ -lncurses

clean:
	rm $(OBJECT)/*.o $(DEBUG_dir)/* 
