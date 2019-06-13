
INCLUDE = -I./ -I./json/
LIB     = -lcurl -ltencentcloud-sdk-cpp-core -ltencentcloud-sdk-cpp-cvm
SRC     = tencentcloudapi_instance_example.cpp http_instance_example.cpp http.cpp jsoncpp.cpp my_exception.cpp scenario.cpp thread_manager.cpp starter.cpp

HEADER  =
OBJ     = $(SRC:.cpp=.o)
OUT     = stress_test
CCFLAGS = -O2 -std=c++11
CC      = g++

$(OUT): $(OBJ) $(HEADER)
	$(CC) $(INCLUDE) $(CCFLAGS) $(OBJ) $(LIB) -o $(OUT)

.cpp.o:
	$(CC) $(INCLUDE) $(CCFLAGS) -c $< -o $@

.c.o:
	$(CC) $(INCLUDE) $(CCFLAGS) -c $< -o $@

debug:
	$(CC) $(INCLUDE) -g -DDEBUG $(SRC) $(LIB) -o $(OUT)

clean:
	rm -f $(OBJ) $(OUT)
