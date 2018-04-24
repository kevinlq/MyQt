# 编译平台							DIR_PLATFORM
# 编译器名称							DIR_COMPILER
# 目标文件后缀							FILE_POSTFIX
# 静态库目标文件前缀					FILE_LIB_PREFIX
# 静态库目标文件扩展名					FILE_LIB_EXT
# 动态库目标文件前缀					FILE_DLL_PREFIX
# 动态库目标文件扩展名					FILE_DLL_EXT
# 变态库目标文件前缀					FILE_ABN_PREFIX
# 变态库目标文件扩展名					FILE_ABN_EXT

# Config Para
CONFIG(debug, debug|release):{
        FILE_POSTFIX = D
        DIR_COMPILEMODE = Debug
}
else:CONFIG(release, debug|release):{
        FILE_POSTFIX =
        DIR_COMPILEMODE = Release
}

win32:{
        CONFIG(MinGW, MinGW|MSVC):{
                DIR_COMPILER = MinGW
                FILE_LIB_PREFIX = lib
                FILE_LIB_EXT = .a
        }
        else:CONFIG(MSVC, MinGW|MSVC):{
                DIR_COMPILER = MSVC
                FILE_LIB_PREFIX =
                FILE_LIB_EXT = .lib
        }

        DIR_PLATFORM = Win32
        FILE_DLL_PREFIX =
        FILE_DLL_EXT = .dll
}
else:android:{
        CONFIG(ARM_GCC_4.4.3, ARM_GCC_4.4.3|ARM_GCC_4.6|ARM_GCC_4.7|ARM_GCC_4.8):{
                DIR_COMPILER = ARM_GCC_4.4.3
        }
        else:CONFIG(ARM_GCC_4.6, ARM_GCC_4.4.3|ARM_GCC_4.6|ARM_GCC_4.7|ARM_GCC_4.8):{
                DIR_COMPILER = ARM_GCC_4.6
        }
        else:CONFIG(ARM_GCC_4.7, ARM_GCC_4.4.3|ARM_GCC_4.6|ARM_GCC_4.7|ARM_GCC_4.8):{
                DIR_COMPILER = ARM_GCC_4.7
        }
        else:CONFIG(ARM_GCC_4.8, ARM_GCC_4.4.3|ARM_GCC_4.6|ARM_GCC_4.7|ARM_GCC_4.8):{
                DIR_COMPILER = ARM_GCC_4.8
        }

        CONFIG(X86_GCC_4.4.3, X86_GCC_4.4.3|X86_GCC_4.6|X86_GCC_4.7|X86_GCC_4.8):{
                DIR_COMPILER = X86_GCC_4.4.3
        }
        else:CONFIG(X86_GCC_4.6, X86_GCC_4.4.3|X86_GCC_4.6|X86_GCC_4.7|X86_GCC_4.8):{
                DIR_COMPILER = X86_GCC_4.6
        }
        else:CONFIG(X86_GCC_4.7, X86_GCC_4.4.3|X86_GCC_4.6|X86_GCC_4.7|X86_GCC_4.8):{
                DIR_COMPILER = X86_GCC_4.7
        }
        else:CONFIG(X86_GCC_4.8, X86_GCC_4.4.3|X86_GCC_4.6|X86_GCC_4.7|X86_GCC_4.8):{
                DIR_COMPILER = X86_GCC_4.8
        }


        DIR_PLATFORM = Android
        FILE_LIB_PREFIX = lib
        FILE_LIB_EXT = .a
        FILE_DLL_PREFIX = lib
        FILE_DLL_EXT = .so

        # 始终编译成静态库
        CONFIG += staticlib
        CONFIG += USE_LIBRARY_ABN
}
else:ios:{
        CONFIG(LLVM, LLVM):{
                DIR_COMPILER = LLVM
        }

        DEFINES += IOS
        DIR_PLATFORM = IOS
        FILE_LIB_PREFIX = lib
        FILE_LIB_EXT = .a
        FILE_DLL_PREFIX = lib
        FILE_DLL_EXT = .so

        # 始终编译成静态库
        CONFIG += staticlib
        CONFIG += USE_LIBRARY_ABN
}
else:mac:{
        CONFIG(clang, clang):{
                DIR_COMPILER = clang
        }

        DEFINES += MAC
        DIR_PLATFORM = MAC
        FILE_LIB_PREFIX = lib
        FILE_LIB_EXT = .a
        FILE_DLL_PREFIX = lib
        FILE_DLL_EXT = .so

        # 始终编译成静态库
        CONFIG += staticlib
        CONFIG += USE_LIBRARY_ABN
}
else:linux:{
        CONFIG(GCC, GCC|GCC32|GCC64):{
                        DIR_COMPILER = GCC
        }
        else:CONFIG(GCC32, GCC|GCC32|GCC64):{
                        DIR_COMPILER = GCC32
        }
        else:CONFIG(GCC64, GCC|GCC32|GCC64):{
                        DIR_COMPILER = GCC64
        }

        DIR_PLATFORM = Linux
        FILE_LIB_PREFIX = lib
        FILE_LIB_EXT = .a
        FILE_DLL_PREFIX = lib
        FILE_DLL_EXT = .so
}

CONFIG(USE_LIBRARY_ABN):{
        FILE_ABN_PREFIX = $${FILE_LIB_PREFIX}
        FILE_ABN_EXT = $${FILE_LIB_EXT}
}
else:{
        FILE_ABN_PREFIX = $${FILE_DLL_PREFIX}
        FILE_ABN_EXT = $${FILE_DLL_EXT}
}
