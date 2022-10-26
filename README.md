# KLFZ_MiniCCompiler

## ��Ŀ�ṹ
������Compiler��Ҫ����������������
1. KLFZ_MiniCLex: ��ɴʷ�����������Token����
2. KLFZ_MiniCYacc: ����﷨�����������﷨��
3. KLFZ_MiniCIR: ����м���������
4. KLFZ_MiniCIROpt: ���б����Ż�
5. KLFZ_MiniCAMS: ���Ż������Ԫʽ��ɻ��

## ��������

��Ҫ��װ [VCPKG](https://github.com/microsoft/vcpkg) ��������������װ���°�

1. fmtlib:x64-windows
2. args:x64-windows

```shell
vcpkg install fmtlib:x64-windows args:x64-windows
```

## ������ʽ

��Ŀ������Կ� Linux �� Windows ƽ̨���������Կ���֧�ֵĹ����������б�����

1. MSVC17
2. (Mingw)gcc8.3+
3. (llvm) clang14.0+

�������汾���������б�������ֻ��Ҫ֧�� C++17 ��׼Ҳ�Ϳ�����ɹ�����

ʹ�� Visual Studio ������ֻ��Ҫ�� KLFZ_MiniCCompiler.sln ���й������ɡ�

ʹ�� Cmake ��������Ҫ����Ŀ��Ŀ¼�µ� CMakeLists.txt �е����������滻
```cmake
# �����е� vcpkg ·���滻Ϊ��� vcpkg ��װ·��
set(CMAKE_TOOLCHAIN_FILE "C:/Users/Qisumi/vcpkg/scripts/buildsystems/vcpkg.cmake")
```