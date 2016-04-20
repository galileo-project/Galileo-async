CC              = gcc
CFLAGS          = -Wall -I src -atd=c99
AR              = ar
ARFLAGS         = -crv
TARGET          = libasync.a
TEST_TARGET     = test.out
NAME            = async
HEADERS_PATH    = $(wildcard ./src/*.h)
CPATH           = $(wildcard ./src/*.c)
TEST_CPATH      = $(wildcard ./test/*.c)
CFILES          = $(notdir $(CPATH))
TEST_CFILES     = $(notdir $(TEST_CPATH))
OBJS            = $(patsubst %.c, %.o, $(CFILES))
TEST_OBJS       = $(patsubst %.c, %.o, $(TEST_CFILES))
INCLUDE_DIR     = /usr/local/include/$(NAME)
LIB_DIR         = /usr/local/lib

vpath           = src:test

$(TARGET): $(OBJS) $(HEADERS_PATH)
	$(AR) $(ARFLAGS) $@ $?
    
.PHONY: test
test: $(TEST_OBJS) $(TARGET)
	$(CC) -o $(TEST_TARGET) $^
	./$(TEST_TARGET)
    
.PHONY: install
install: $(TARGET)
	-mkdir -p $(INCLUDE_DIR)
	cp -r $(HEADERS_PATH) $(INCLUDE_DIR)
	cp $(TARGET) $(LIB_DIR)
    
$(OBJS): $(CFILES)
$(TEST_OBJS): $(TEST_CFILES)

.PHONY: clean
clean:
	-rm -rf $(OBJS) $(TEST_OBJS) $(TARGET) $(TEST_TARGET)
