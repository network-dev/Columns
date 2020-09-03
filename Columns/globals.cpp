#include "globals.h"

namespace globals
{
    std::vector<column*> item_list = std::vector<column*>();

    int size_of_columns = 300.f;
    int height_of_board = 0.f;
    int column_count = 1;
    int height = 0.f;
    int width = 0.f;
    bool cache_images = false;

    float x_dist = 15.f;

    bool intro_showed = false;

    std::string project_name = "";
    std::string project_version = "1.1.5 - Update #2 - Change #5";
    std::string project_path = "";

    ImFont* big_font;

    PDIRECT3DTEXTURE9 folder_texture = NULL;

    LPDIRECT3D9              g_pD3D = NULL;
    LPDIRECT3DDEVICE9        g_pd3dDevice = NULL;
    D3DPRESENT_PARAMETERS    g_d3dpp = {};
}
