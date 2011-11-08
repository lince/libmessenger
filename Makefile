CC= g++
HEADERS_DIR= /usr/local/include/libmessenger
LIB_DIR= /usr/local/lib
TARGET_LIB= libmessenger.so
PROGS= $(TARGET_LIB) test/amazontest

ACTIVEMQ_HOME=/usr/local/include/activemq-cpp-3.4.0
APR_HOME=/usr/local/apr

INCLUDES=	\
			include/Messenger.h \
			include/MsgListener.h
			
SOURCES=	\
			src/Messenger.cpp
			
LIBS= 		-lcpputil -lactivemq-cpp

PATHS= -I$(ACTIVEMQ_HOME) -I$(APR_HOME)/include/apr-1/

INSTALL_HEADERS = $(INCLUDES)

ALL: $(PROGS)

$(TARGET_LIB): $(INCLUDES) $(SOURCES)
	$(CC) $(SOURCES) $(LIBS) $(PATHS)\
		-shared -o $(TARGET_LIB) -g
		
test/amazontest: $(TARGET_LIB) test/amazontest.cpp
	$(CC) test/amazontest.cpp -o test/amazontest $(PATHS) -L. -I./include -lmessenger -lactivemq-cpp -g
		
clean:
	rm -f $(PROGS)
	
uninstall:
	rm -rf $(HEADERS_DIR)
	rm -rf $(LIB_DIR)/$(TARGET_LIB)
		
install: $(TARGET_LIB)
	install -d $(HEADERS_DIR)
	install -t $(HEADERS_DIR) $(INSTALL_HEADERS)
	install -t $(LIB_DIR) $(TARGET_LIB)