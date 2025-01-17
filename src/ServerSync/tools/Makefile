######## General Settings ########

ifeq ($(SGX_DEBUG), 1)
        COMMON_CFLAGS += -O0 -g -DDEBUG
        Binary_Folder := debug
else
        COMMON_CFLAGS += -O2 -D_FORTIFY_SOURCE=2 -DNDEBUG
        Binary_Folder := release
endif

######## App Settings ########

Protected_Ledger_Root := ../..
Crypto_Dir := $(Protected_Ledger_Root)/CryptoLib
Common_Dir := $(Protected_Ledger_Root)/Common
Libraries_Dir := $(Protected_Ledger_Root)/lib

Common_C_Files := $(Common_Dir)/memset_s.c

Signer_CPP_Files := $(Common_Dir)/safe_copy.cpp $(Common_Dir)/app_log.cpp kds_signer.cpp
Calc_CPP_Files := $(Common_Dir)/safe_copy.cpp $(Common_Dir)/app_log.cpp ../common/parse_string.cpp kds_calculator.cpp
Creator_CPP_Files := $(Common_Dir)/safe_copy.cpp $(Common_Dir)/app_log.cpp client_keys_creator.cpp

Signer_C_Objects := $(Common_C_Files:.c=.o) $(Signer_CPP_Files:.cpp=.o)
Calc_C_Objects := $(Common_C_Files:.c=.o) $(Calc_CPP_Files:.cpp=.o)
Creator_C_Objects := $(Common_C_Files:.c=.o) $(Creator_CPP_Files:.cpp=.o)

App_Include_Paths := -I. -I../common -I$(Crypto_Dir) -I$(Crypto_Dir)/openssl/include -I$(Common_Dir)

App_C_Flags := $(COMMON_CFLAGS) -fpic -fpie -fstack-protector -Wformat -Wformat-security -Wall -Wextra -Wconversion -Wno-attributes $(App_Include_Paths)

App_CXX_Flags := $(App_C_Flags) -std=c++11

Security_Link_Flags := -Wl,-z,noexecstack -Wl,-z,relro -Wl,-z,now -pie
ifeq ($(SGX_DEBUG), 1)
	OPENSSL_CRYPTO_LIB := cryptod
else
	OPENSSL_CRYPTO_LIB := crypto
endif
OpenSsl_Link_Files := -L$(Crypto_Dir)/openssl/lib -l$(OPENSSL_CRYPTO_LIB)

App_Link_Flags := $(COMMON_CFLAGS) $(Security_Link_Flags) -L$(Libraries_Dir)/$(Binary_Folder) -lstl_crypto_u $(OpenSsl_Link_Files) -lpthread -llog4cxx

.PHONY: all run

all: kds_calculator kds_signer client_keys_creator

run: all

######## App Objects ########

%.o: %.cpp
	@$(CXX) $(App_CXX_Flags) -c $< -o $@
	@echo "$(CXX)  <=  $<"

%.o: %.c
	@$(CC) $(App_C_Flags) -c $< -o $@
	@echo "$(CC)  <=  $<"

kds_calculator: $(Calc_C_Objects)
	@$(CXX) $^ -o $@ $(App_Link_Flags)
	@echo "LINK =>  $@"

kds_signer: $(Signer_C_Objects)
	@$(CXX) $^ -o $@ $(App_Link_Flags)
	@echo "LINK =>  $@"
	
client_keys_creator: $(Creator_C_Objects)
	@$(CXX) $^ -o $@ $(App_Link_Flags)
	@echo "LINK =>  $@"

.PHONY: clean

clean:
	@rm -f kds_calculator $(Calc_C_Objects) kds_signer $(Signer_C_Objects) client_keys_creator $(Creator_C_Objects)
	
