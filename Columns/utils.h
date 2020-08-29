#pragma once

#ifndef UTILS_H
#define UTILS_H

#include <Windows.h>
#include <string>
#include <d3dx9.h>
#include <vector>

namespace utils
{
    extern wchar_t* convert_char_array_to_wchar(const char* charArray);
    extern std::string open_file_dialog(LPCWSTR filter = L"All Files (*.*)\0*.*\0");
    extern std::string save_file_dialog(LPCWSTR filter = L"");
    extern bool load_texture_file(const char* filename, PDIRECT3DTEXTURE9* out_texture, int* out_width, int* out_height);
    extern std::string get_current_directory(std::string sub_text);
    extern std::vector<std::string> split_string(std::string s, char delim);
}

#endif
