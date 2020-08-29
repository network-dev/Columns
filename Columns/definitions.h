#pragma once

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <string>
#include <d3d9.h>
#include <vector>
#include "utils.h"
#include "imgui.h"

enum column_type
{
    COLUMN_T_NONE,
    COLUMN_T_INPUT,
    COLUMN_T_IMAGE
};

struct column_input
{
    column_input()
    {
        label = "";
        content = "";
        bg_color = ImVec4(0.16f, 0.29f, 0.48f, 1.f);
    }

    ImVec4 bg_color;

    std::string label;
    std::string content;
    bool editing = false;
};

struct column_image
{
    column_image() {}
    column_image(std::string url)
    {
        PDIRECT3DTEXTURE9 tmp_txt = NULL;
        int w_tmp, h_tmp;

        utils::load_texture_file(url.c_str(), &tmp_txt, &w_tmp, &h_tmp);

        path = url;

        texture = tmp_txt;
        w = w_tmp;
        h = h_tmp;

        editing = false;
        keep_aspect_ratio = false;
    }

    PDIRECT3DTEXTURE9 texture;
    bool editing = false;
    bool keep_aspect_ratio = false;
    std::string path;
    int w, h;
};

struct column_items;

struct column
{
    column()
    {
        column_num = 0;
        selected_combo_item = 0;

        new_input_label = "input";
        add_label_ = "";
        title = "Column";

        enter_url_frame = false;
        editing_title = false;

        selected_row_idx = 0;

        replace_with_next_addition = false;
    }

    std::string new_input_label = "";
    std::string add_label_ = "";

    std::string current_img_path = "";
    std::string current_url = ""; 

    std::string title;

    int column_num;
    bool enter_url_frame;
    int selected_combo_item;
    bool editing_title;

    bool replace_with_next_addition;

    int selected_row_idx;

    std::vector<column_items> columns_i_l;
};

struct column_items
{
public:
    column_items() {}

    // TODO: Fix ->
    // Height is unused for the inputs
    void add_input(column* c, column_input i, int h = 40) 
    {
        input = i;
        type = column_type::COLUMN_T_INPUT;
        height = h;
    }

    void add_image(column* c, column_image i, int h = 150)
    {
        image = i;
        type = column_type::COLUMN_T_IMAGE;
        height = h;
    }

    column_input& get_input()
    {
        return input;
    }

    column_image& get_image()
    {
        return image;
    }

    column* get_parent_column()
    {
        return column;
    }

    column_type get_type()
    {
        return type;
    }

    int& get_height()
    {
        return height;
    }

private:
    column_input input;
    column_image image;
    column* column;
    column_type type;
    int height;
};

#endif
