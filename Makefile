CC= g++
HEADERS_DIR= /usr/local/include/libmessenger
LIB_DIR= /usr/local/lib
TARGET_LIB= libmessenger.so
PROGS= $(TARGET_LIB) amazontest

INCLUDES=	\
			include/Messenger.h \
			include/MsgListener.h
			
SOURCES=	\
			src/Messenger.cpp
			
LIBS= 		-lcpputil -lactivemq-cpp -lssl

PATHS= -I/usr/local/include/activemq-cpp-3.4.0/ -I/usr/local/apr/include/apr-1/

INSTALL_HEADERS = $(INCLUDES)

ALL: $(PROGS)

$(TARGET_LIB): $(INCLUDES) $(SOURCES)
	$(CC) $(SOURCES) $(LIBS) $(PATHS) \
		-shared -fPIC -o $(TARGET_LIB)
		
amazontest: $(TARGET_LIB) test/amazontest.cpp
	$(CC) test/amazontest.cpp -o test/amazontest $(PATHS) -L. -I./include -lmessenger
		
		
clean:
	rm -f $(PROGS)
	
uninstall:
	rm -rf $(HEADERS_DIR)
	rm -rf $(LIB_DIR)/$(TARGET_LIB)
		
install: $(TARGET_LIB)
	install -d $(HEADERS_DIR)
	install -t $(HEADERS_DIR) $(INSTALL_HEADERS)
	install -t $(LIB_DIR) $(TARGET_LIB)