SOURCE_PATH=src
BUILD_PATH=build
INCLUDE_PATH=include
BIN_PATH=bin
LOG_PATH=log
TEST_PATH=test
APPLICATION_NAME=suede
MAIN_FILE=main.cpp
TEST_APPLICATION_NAME=suede_test
MAIN_TEST_FILE=test_main.cpp
FILES=log.cpp http_request.cpp http_response.cpp tcp_listener.cpp http_listener.cpp websocket_listener.cpp user_input_listener.cpp system_signal.cpp websocket_frame.cpp config.cpp
SOURCES = $(FILES:%.cpp=$(SOURCE_PATH)/%.cpp)
OBJ=$(FILES:%.cpp=$(BUILD_PATH)/%.o)
TEST_SRC=$(FILES:%.cpp=$(TEST_PATH)/%_test.cpp)
TEST_OBJ=$(FILES:%.cpp=$(BUILD_PATH)/%_test.o)

all: folders $(OBJ)
	g++ -std=c++11 -o $(BIN_PATH)/$(APPLICATION_NAME) -I./$(INCLUDE_PATH) $(OBJ) $(SOURCE_PATH)/$(MAIN_FILE) -L/usr/lib -lssl -lcrypto -pthread

$(BUILD_PATH)/%.o : $(SOURCE_PATH)/%.cpp
	g++ -std=c++11 -o $@ -g -I./$(INCLUDE_PATH) -c $< -L/usr/lib -lssl -lcrypto -pthread

debug: folders $(OBJ)
	g++ -std=c++11 -g -DDEBUG_MODE -o $(BIN_PATH)/$(APPLICATION_NAME) -I./$(INCLUDE_PATH) $(OBJ) -L/usr/lib -lssl -lcrypto -pthread

run: all
	$(BIN_PATH)/$(APPLICATION_NAME)
	
test: folders $(OBJ)
	g++ -o $(BIN_PATH)/$(TEST_APPLICATION_NAME) -g -I./$(INCLUDE_PATH) -I./vendor/googletest -I./vendor/googletest/include -I./vendor/googletest/include/internal $(TEST_SRC) $(OBJ) $(TEST_PATH)/$(MAIN_TEST_FILE) -L/usr/lib -lssl -lcrypto -isystem -g -pthread -std=c++11
	
runtest: test
	$(BIN_PATH)/$(TEST_APPLICATION_NAME)
	
folders:
	mkdir -p $(BIN_PATH) $(BUILD_PATH) $(LOG_PATH)
	sudo ln -s $(LOG_PATH) $(BIN_PATH)/$(LOG_PATH)
	
clean:
	rm -f $(BUILD_PATH)/*.o $(BIN_PATH)/$(APPLICATION_NAME) $(LOG_PATH)/*.log
	rm -rf $(BUILD_PATH)
	rm -rf $(BIN_PATH)
	rm -rf $(LOG_PATH)
	
googletest:
	-I./vendor/googletest/include
