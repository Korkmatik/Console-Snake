SRC = src
OBJECT = obj
DEBUG_dir = build/debug

$(DEBUG_dir)/snake.x: $(SRC)/*.cpp
	g++ -g $^ -o $@

clean:
	rm $(OBJECT)/*.o $(DEBUG_dir)/* 
