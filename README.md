# KLFZ_MiniCCompiler

## 项目结构
编译器Compiler主要由以下五个部分组成
1. KLFZ_MiniCLex: 完成词法分析并生成Token序列
2. KLFZ_MiniCYacc: 完成语法分析并生成语法树
3. KLFZ_MiniCIR: 完成中间代码的生成
4. KLFZ_MiniCIROpt: 进行编译优化
5. KLFZ_MiniCAMS: 从优化后的四元式完成汇编

## 构建依赖

需要安装 [VCPKG](https://github.com/microsoft/vcpkg) 进行依赖管理并安装以下包

1. fmtlib:x64-windows
2. args:x64-windows

```shell
vcpkg install fmtlib:x64-windows args:x64-windows
```

## 构建方式

项目代码可以跨 Linux 和 Windows 平台，经过测试可以支持的构建工具链列表如下

1. MSVC17
2. (Mingw)gcc8.3+
3. (llvm) clang14.0+

工具链版本低于上述列表，理论上只需要支持 C++17 标准也就可以完成构建。

使用 Visual Studio 构建，只需要打开 KLFZ_MiniCCompiler.sln 运行构建即可。

使用 Cmake 构建，需要将项目根目录下的 CMakeLists.txt 中的以下内容替换
```cmake
# 将其中的 vcpkg 路径替换为你的 vcpkg 安装路径
set(CMAKE_TOOLCHAIN_FILE "C:/Users/Qisumi/vcpkg/scripts/buildsystems/vcpkg.cmake")
```