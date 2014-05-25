
PE_AGENT_LIB=libPEAgent.so
PE_AGENT_OBJ=\
	PEAgent/oecc.o

SHM_LIB=libshm.so
SHM_OBJ=\
	shm/shm.o

all: $(PE_AGENT_LIB) $(SHM_LIB)

$(PE_AGENT_LIB): $(PE_AGENT_OBJ)
	$(CC) $(CFLAGS) -shared -Wl,-soname,$(PE_AGENT_LIB) \
		-o $(PE_AGENT_LIB) $(PE_AGENT_OBJ)

$(SHM_LIB): $(SHM_OBJ)
	$(CC) $(CFLAGS) -shared -Wl,-soname,$(SHM_LIB) \
		-o $(SHM_LIB) $(SHM_OBJ)

clean:
	rm -rf $(SHM_OBJ) $(PE_AGENT_OBJ)
	rm *.so
