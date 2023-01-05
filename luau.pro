#-------------------------------------------------
#
# Project created by QtCreator 2011-12-13T12:06:49
#
#-------------------------------------------------

QT       -= core gui

TARGET = lua
TEMPLATE = lib
CONFIG   += silent c++17

win32 {
DEFINES += LUA_BUILD_AS_DLL LUA_CORE
}

//QMAKE_CXXFLAGS_DEBUG += -O2
QMAKE_CXXFLAGS_DEBUG += -DLUAU_ENABLE_ASSERT

defineReplace(expand) {
    names = $$1
    prefix=$$2
    suffix=$$3
    expanded =

    for(name, names) {
        expanded+= $${prefix}$${name}$${suffix}
    }
    return ($$expanded)
}

INCLUDEPATH += \
	VM/src \
	VM/include \
	Common/Include \
        Compiler/include \
        Ast/include \
        ../libgvfs

SOURCES += \
         $$expand(lapi laux lbaselib lbitlib lbuiltins lcorolib ldblib ldebug ldo lfunc lgc lgcdebug linit lint64lib liolib lmathlib lmem lnumprint lobject loslib lperf lstate lstring lstrlib \
         ltable ltablib ltm ludata lutf8lib lvmexecute lvmload lvmutils,VM/src/,.cpp) \
         $$expand(Builtins BuiltinFolding BytecodeBuilder ConstantFolding Compiler CostModel lcode PseudoCode TableShape ValueTracking,Compiler/src/,.cpp) \
         $$expand(Ast Confusables Lexer Location Parser StringUtils TimeTrace,Ast/src/,.cpp)

win32 {
LIBS += -L"../libgvfs/release" -lgvfs
}

macx {
LIBS += -L"../libgvfs" -lgvfs
}
else {

unix:!macx {
LIBS += ../libgvfs/libgvfs.so
}

}
