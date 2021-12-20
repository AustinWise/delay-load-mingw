# Delay Loading DLLs in MinGW

The Microsoft linker `link.exe` supports delay loading DLLs until a function
from the DLL is call. See [this documentation](https://docs.microsoft.com/cpp/build/reference/linker-support-for-delay-loaded-dlls)
about the `/DELAYLOAD:` command line argument.

The GNU linker `ld` does not have, to the best of my knowledge,
a similar command line argument.

To work around this limitation, we instead use the binutils
program `dlltool`. See [the documentation](https://sourceware.org/binutils/docs/binutils/dlltool.html).
This program is usually used for creating new DLLs.
We instead create a delay load library for an existing
DLL.

# This example

This example shows delay loading the Windows DLL `version.dll`.
We call the `GetFileVersionInfoW` function. We also include
a delay load hook so that we can observe the DLL being delay loaded.
