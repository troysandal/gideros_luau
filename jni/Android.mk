LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE            := gvfs
LOCAL_SRC_FILES         := ../../libgvfs/libs/$(TARGET_ARCH_ABI)/libgvfs.so

include $(PREBUILT_SHARED_LIBRARY)

###

include $(CLEAR_VARS)

LOCAL_MODULE := lua
LOCAL_ARM_MODE := arm
LOCAL_CFLAGS := -O2 -DLUA_USE_MKSTEMP -std=c++17
LOCAL_C_INCLUDES += $(addprefix $(LOCAL_PATH)/../,VM/src VM/include Compiler/include Ast/include ../libgvfs)

LOCAL_SRC_FILES += $(addsuffix .cpp, \
        $(addprefix ../VM/src/,lapi laux lbaselib lbitlib lbuiltins lcorolib ldblib ldebug ldo lfunc lgc lgcdebug linit lint64lib liolib lmathlib lmem lnumprint lobject loslib lperf lstate lstring lstrlib \
         ltable ltablib ltm ludata lutf8lib lvmexecute lvmload lvmutils) \
        $(addprefix ../Compiler/src/,Builtins BytecodeBuilder ConstantFolding Compiler lcode PseudoCode TableShape ValueTracking) \
        $(addprefix ../Ast/src/,Ast Confusables Lexer Location Parser StringUtils TimeTrace))

LOCAL_LDLIBS := -ldl
LOCAL_SHARED_LIBRARIES := gvfs

include $(BUILD_SHARED_LIBRARY)
