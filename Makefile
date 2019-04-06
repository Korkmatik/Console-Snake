SRC = src
OBJECT = obj
DEBUG_dir = build/debug
RELEASE_dir = build/release

$(DEBUG_dir)/snake.x: $(SRC)/*
	g++ -g $(SRC)/*.cpp -o $@ -lncurses

release:
	g++ $(SRC)/*.cpp -o $(RELEASE_dir)/snake.x -lncurses

clean:
	rm $(OBJECT)/*.o $(DEBUG_dir)/* 
