#include "utils.h"

#include <sstream>

#include "globals.h"

wchar_t* utils::convert_char_array_to_wchar(const char* charArray)
{
    wchar_t* w_string = new wchar_t[4096];
    MultiByteToWideChar(CP_ACP, 0, charArray, -1, w_string, 4096);
    return w_string;
}

std::string utils::save_file_dialog(LPCWSTR filter)
{
    OPENFILENAME ofn;
    TCHAR szFile[260] = { 0 };

    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = filter;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetSaveFileName(&ofn) == TRUE)
    {
        std::wstring ws(ofn.lpstrFile);
        return std::string(ws.begin(), ws.end());
    }
    return "";
}

std::string utils::open_file_dialog(LPCWSTR filter)
{
    OPENFILENAME ofn;   
    TCHAR szFile[260] = { 0 };      

    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = filter;
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&ofn) == TRUE)
    {
        std::wstring ws(ofn.lpstrFile);
        return std::string(ws.begin(), ws.end());
    }
    return "";
}

bool utils::load_texture_file(const char* filename, PDIRECT3DTEXTURE9* out_texture, int* out_width, int* out_height)
{
    PDIRECT3DTEXTURE9 texture;
    HRESULT hr = D3DXCreateTextureFromFileA(globals::g_pd3dDevice, filename, &texture);
    if (hr != S_OK)
        return false;

    // Retrieve description of the texture surface so we can access its size
    D3DSURFACE_DESC my_image_desc;
    texture->GetLevelDesc(0, &my_image_desc);
    *out_texture = texture;
    *out_width = (int)my_image_desc.Width;
    *out_height = (int)my_image_desc.Height;
    return true;
}

std::string utils::get_current_directory(std::string sub_text)
{
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    std::string::size_type pos = std::string(buffer).find_last_of("\\/");

    return std::string(buffer).substr(0, pos) + "\\" + sub_text;
}

std::vector<std::string> utils::split_string(std::string s, char delim)
{
    std::vector<std::string> elems;
    std::string curr_buff = "";

    if (s.find(delim) == std::string::npos)
    {
        return elems;
    }

    for (char c : s)
    {
        if (c == delim)
        {
            elems.push_back(curr_buff);
            curr_buff = "";
        }
        else {
            curr_buff += c;
        }
    }
    if (curr_buff.length() > 0)
    {
        elems.push_back(curr_buff);
    }

    return elems;
}
