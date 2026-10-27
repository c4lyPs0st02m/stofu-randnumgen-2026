# RandNumGen

A small application, written in C++, that uses the WinAPI
[`MessageBox`](https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-messagebox)
function to display a randomly generated integer in the range `[1, 20]`.

## Description

It uses [**Mhook**](https://github.com/SToFU-Systems/mhook/tree/master) library to hook the message
box calls and implement the following behavior:
1. If the generated integer equals `1`, replace it with `100`.
1. If the generated integer equals `2`, terminate the app abnormally by calling `std::abort()` from
`<cstdlib>`.

By using:

- [**Ghidra**](https://github.com/nationalsecurityagency/ghidra/) (v12.1.4)
- [**MCP server**](https://github.com/bethington/ghidra-mcp/) for Ghidra (v7.0.0)
- [**ImHex**](https://github.com/WerWolv/ImHex) editor (v1.24.3)
- [**Visual Studio IDE**](https://visualstudio.microsoft.com/) (v18.11.2)

the compiled app (`RandNumGen.exe`) was patched so that, if the generated number integer equals
`2`, the call to `std::abort()` is not executed and the application continues running normally.
