#pragma once

#ifndef GLOBALS_H
#define GLOBALS_H

#include <vector>
#include "definitions.h"

namespace globals
{
    extern std::vector<column*> item_list;

    extern int size_of_columns;
    extern int height_of_board;
    extern int column_count;
    extern int height;
    extern int width;
    extern bool cache_images;

    extern float x_dist;

    extern bool intro_showed;

    extern std::string project_name;
    extern std::string project_version;
    extern std::string project_path;

    extern ImFont* big_font;

    extern PDIRECT3DTEXTURE9 folder_texture;

    extern LPDIRECT3D9              g_pD3D;
    extern LPDIRECT3DDEVICE9        g_pd3dDevice;
    extern D3DPRESENT_PARAMETERS    g_d3dpp;
}

#endif
