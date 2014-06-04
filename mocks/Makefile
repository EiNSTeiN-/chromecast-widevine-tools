
PE_AGENT_LIB=libPEAgent.so
PE_AGENT_OBJ=\
	PEAgent/oecc.o

SHM_LIB=libshm.so
SHM_OBJ=\
	shm/shm.o

OPENCRYPTO_LIB=libOpenCrypto.so
OPENCRYPTO_OBJ=\
	OpenCrypto/open_crypto.o

GTVCA_LIB=libGtvCa.so
GTVCA_OBJ=\
	GtvCa/gtv_ca.o

all: $(PE_AGENT_LIB) $(SHM_LIB) $(GTVCA_LIB) $(OPENCRYPTO_LIB)

$(PE_AGENT_LIB): $(PE_AGENT_OBJ)
	$(CC) -DDLLEXPORTS $(CFLAGS) -shared -Wl,-soname,$(PE_AGENT_LIB) \
		-o $(PE_AGENT_LIB) $(PE_AGENT_OBJ)

$(SHM_LIB): $(SHM_OBJ)
	$(CC) -DDLLEXPORTS $(CFLAGS) -shared -Wl,-soname,$(SHM_LIB) \
		-o $(SHM_LIB) $(SHM_OBJ)

$(OPENCRYPTO_LIB): $(OPENCRYPTO_OBJ)
	$(CC) -DDLLEXPORTS -DC_EXPORTS $(CFLAGS) -shared -Wl,-soname,$(OPENCRYPTO_LIB) \
		-o $(OPENCRYPTO_LIB) $(OPENCRYPTO_OBJ)

$(GTVCA_LIB): $(GTVCA_OBJ)
	$(CC) -DDLLEXPORTS $(CFLAGS) -shared -Wl,-soname,$(GTVCA_LIB) \
		-o $(GTVCA_LIB) $(GTVCA_OBJ)

clean:
	rm -rf $(SHM_OBJ) $(PE_AGENT_OBJ) $(GTVCA_OBJ) $(OPENCRYPTO_OBJ)
	rm *.so
