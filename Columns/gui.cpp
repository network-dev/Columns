#include "gui.h"

#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_dx9.h"
#include "imgui_stdlib.h"

#include "globals.h"
#include "save.h"
#include <random>
#include <direct.h>
#include <iostream>

#pragma comment(lib, "urlmon.lib")

PDIRECT3DTEXTURE9 up_arrow_txt;
PDIRECT3DTEXTURE9 down_arrow_txt;

PDIRECT3DTEXTURE9 left_arrow_txt;
PDIRECT3DTEXTURE9 right_arrow_txt;

std::string random_string(float len)
{
    std::string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

    std::random_device rd;
    std::mt19937 generator(rd());

    std::shuffle(str.begin(), str.end(), generator);

    return str.substr(0, len);    // assumes 32 < number of characters in str         
}

void gui::draw_addition_options(int cc, column* column_item)
{
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(10.f, 10.f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10.f, 10.f));

    std::string addition_ooo = "##additionoptions_" + std::to_string(cc);

    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 2);
    ImGui::BeginChild(addition_ooo.c_str(), ImVec2(globals::size_of_columns - 3, 100), true, 0);

    std::string newww_wi22 = "##combo_" + std::to_string(cc);

    const char* items[] = { "Text", "Image" };

    ImGui::SetCursorPosX(ImGui::GetCursorPosX() - 5.f);
    ImGui::SetNextItemWidth(globals::size_of_columns - 10.f);
    ImGui::Combo(newww_wi22.c_str(), &column_item->selected_combo_item, items, IM_ARRAYSIZE(items));

    std::string newww_wi = "";

    column_items c_items = column_items();

    switch (column_item->selected_combo_item)
    {
    case 1:
    {
        // ADD IMAGE

        newww_wi = "Add Image from PATH##new_path_" + std::to_string(cc);
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() - 5.f);
        if (ImGui::Button(newww_wi.c_str(), ImVec2(globals::size_of_columns - 13, 20)))
        {
            column_item->current_img_path = utils::open_file_dialog(L"Image Files (*.bmp *.png *.jpg *.jpeg)\0*.bmp;*.png;*.jpg;*.jpeg");
            if (column_item->current_img_path.length() > 0)
            {
                column_image cc_image = column_image(column_item->current_img_path);
                c_items.add_image(column_item, cc_image);

                save::add_item_to_column(column_item, c_items);
            }
        }

        newww_wi = "Add Image from URL##new_weburl_" + std::to_string(cc);
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() - 5.f);
        if (ImGui::Button(newww_wi.c_str(), ImVec2(globals::size_of_columns - 13, 20)))
        {
            column_item->enter_url_frame = true;
        }
    }
        break; 
    case 0:
    {
        // ADD TEXT

        std::string newww_wisd = "Label##label_" + std::to_string(cc);

        ImGui::SetCursorPosX(ImGui::GetCursorPosX() - 5.f);
        ImGui::SetNextItemWidth(globals::size_of_columns - 50.f);
        ImGui::InputText(newww_wisd.c_str(), &column_item->add_label_);

        newww_wi = "Add##new_" + std::to_string(cc);
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() - 5.f);
        if (ImGui::Button(newww_wi.c_str(), ImVec2(globals::size_of_columns - 13, 20)))
        {
            column_input cc_input = column_input();
            cc_input.label = column_item->add_label_;
            c_items.add_input(column_item, cc_input);

            save::add_item_to_column(column_item, c_items);
            

        }
    }
        break;
    default:
        break;
    }

    newww_wi = "Replace selected##replace_" + std::to_string(cc);
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() - 5.f);
    ImGui::Checkbox(newww_wi.c_str(), &column_item->replace_with_next_addition);

    ImGui::EndChild();

    ImGui::PopStyleVar();
    ImGui::PopStyleVar();
}

void gui::draw_column(int cc, column* column_item)
{
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(10.f, 10.f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10.f, 10.f));

    if (column_item->editing_title)
    {
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (globals::size_of_columns / 6.f));

        std::string title_ = "##edit_title_" + std::to_string(cc);
        ImGui::InputText(title_.c_str(), &column_item->title);

        float button_width = globals::size_of_columns / 4.f;

        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (globals::size_of_columns / 2.f) - ((button_width) + 7.f));

        title_ = "Duplicate##duplicate_" + std::to_string(cc);
        if (ImGui::Button(title_.c_str(), ImVec2(button_width, 20)))
        {
            save::duplicate_column(column_item);
            column_item->editing_title = false;
        }
        ImGui::SameLine();
        title_ = "Remove##remove_" + std::to_string(cc);
        if (ImGui::Button(title_.c_str(), ImVec2(button_width, 20)))
        {
            save::remove_column(column_item);
            column_item->editing_title = false;
        }
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (globals::size_of_columns / 2.f) - ((button_width / 2.f) + 7.f));
        title_ = "Done##save_title_" + std::to_string(cc);
        if (ImGui::Button(title_.c_str(), ImVec2(button_width, 20)))
        {
            column_item->editing_title = false;
        }
    }
    else {
        std::string component_text = "##left_arrow_" + std::to_string(cc);

        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 15.f);
        ImGui::PushID(component_text.c_str());
        if (ImGui::ImageButton((void*)left_arrow_txt, ImVec2(12, 12)))
        {
            save::move_column(column_item, cc, false);
        }
        ImGui::PopID();

        ImGui::SameLine();

        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + globals::size_of_columns - 80.f);
        component_text = "##right_arrow" + std::to_string(cc);
        ImGui::PushID(component_text.c_str());
        if (ImGui::ImageButton((void*)right_arrow_txt, ImVec2(12, 12)))
        {
            save::move_column(column_item, cc, true);
        }
        ImGui::PopID();

        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + globals::size_of_columns / 2.f - ImGui::CalcTextSize(column_item->title.c_str()).x / 2.f);
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 25.f);

        ImGui::Text(column_item->title.c_str());

        if (ImGui::IsItemHovered() && ImGui::IsMouseDown(1))
        {
            column_item->editing_title = true;
        }
    }

    std::string child_name = "##scrollingregion_column_" + std::to_string(cc);
    ImGui::BeginChild(child_name.c_str(), ImVec2(0, globals::height_of_board - (column_item->editing_title ? 213.f : 150.f)), false, 0);

    for (int col_n = 0; col_n < column_item->column_num; col_n++)
    {
        std::string ttt_id = "";

        column_items &item_ = column_item->columns_i_l[col_n];

        switch (item_.get_type())
        {
            case column_type::COLUMN_T_IMAGE:
            {
                column_image& cim = item_.get_image();

                if (!cim.editing)
                {
                    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 3);

                    bool selected = (column_item->selected_row_idx == col_n);

                    if (selected)
                    {
                        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 4.0f);
                        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.f, 1.f, 1.f, 1.f));
                    }

                    int click = ImGui::ImageButton2((void*)cim.texture, ImVec2(globals::size_of_columns - 7.f, item_.get_height()), ImVec2(0, 0), ImVec2(1, 1), 1);

                    if (selected)
                    {
                        ImGui::PopStyleVar();
                        ImGui::PopStyleColor();
                    }

                    if (click >= 0)
                    {
                        switch (click)
                        {
                        case 0:
                            break;
                        case 1:
                            cim.editing = true;
                            break;
                        case 2:
                            column_item->selected_row_idx = col_n;
                            break;
                        default:
                            break;
                        }
                    }
                }
                else {
                    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 5);

                    float avg_size = (globals::size_of_columns - 12.f) / 3.f;

                    ImGui::PushItemWidth(avg_size);

                  /*  ttt_id = "Keep Ratio##keep_aspect_ratio_" + std::to_string(col_n) + "_" + std::to_string(cc) + "_";

                    ImGui::Checkbox(ttt_id.c_str(), &cim.keep_aspect_ratio);*/

                    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 5);

                    if (!cim.keep_aspect_ratio)
                    {
                        ttt_id = "##edit_height_cim_" + std::to_string(col_n) + "_" + std::to_string(cc) + "_";
                        ImGui::InputInt(ttt_id.c_str(), &item_.get_height());

                        ImGui::SameLine();
                    }
                    else {
                        ImGui::SameLine();
                    }

                    std::string component_text = "##up_arrow_txt_" + std::to_string(cc) + "_" + std::to_string(col_n);
                    ImGui::PushID(component_text.c_str());
                    if (ImGui::ImageButton((void*)up_arrow_txt, ImVec2(12, 12)))
                    {
                        save::move_item_on_column(column_item, col_n, false);
                    }
                    ImGui::PopID();

                    ImGui::SameLine();

                    component_text = "##down_arrow_txt_" + std::to_string(cc) + "_" + std::to_string(col_n);
                    ImGui::PushID(component_text.c_str());
                    if (ImGui::ImageButton((void*)down_arrow_txt, ImVec2(12, 12)))
                    {
                        save::move_item_on_column(column_item, col_n, true);
                    }
                    ImGui::PopID();

                    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 5);

                    ttt_id = "Remove##remove_cim" + std::to_string(col_n) + "_" + std::to_string(cc) + "_";

                    if (ImGui::Button(ttt_id.c_str(), ImVec2(avg_size, 20)))
                    {
                        save::remove_item_on_column(column_item, col_n);
                    }

                    ImGui::SameLine();
                    ttt_id = "Done##edit_cim" + std::to_string(col_n) + "_" + std::to_string(cc) + "_";
                    if (ImGui::Button(ttt_id.c_str(), ImVec2(avg_size, 20)))
                    {
                        cim.editing = false;
                    }
                }

                break;
            }
            case column_type::COLUMN_T_INPUT:
            {
                column_input& cin = item_.get_input();

                if (cin.label.length() > 0)
                {
                    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 4);
                    ImGui::Text(cin.label.c_str());
                }

                if (!cin.editing)
                {
                    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 4);
                    ttt_id = "##input_cin" + std::to_string(col_n) + "_" + std::to_string(cc) + "_";

                    ImGui::PushStyleColor(ImGuiCol_FrameBg, cin.bg_color);

                    ImGui::PushItemWidth(globals::size_of_columns - 7);


                    bool selected = (column_item->selected_row_idx == col_n);

                    if (selected)
                    {
                        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 4.0f);
                        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.f, 1.f, 1.f, 1.f));
                    }


                    if (ImGui::InputText(ttt_id.c_str(), &cin.content))
                    {
                        if (ImGui::IsMouseClicked(1))
                        {
                            cin.editing = true;
                        }
                        else {
                            if (ImGui::IsMouseClicked(2))
                            {
                                std::cout << "Middle mouse" << std::endl;
                                column_item->selected_row_idx = col_n;
                            }
                        }
                    }

                    if (selected)
                    {
                        ImGui::PopStyleVar();
                        ImGui::PopStyleColor();
                    }

                    ImGui::PopStyleColor();
                }
                else {
                    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 5);

                    float avg_size = (globals::size_of_columns - 12.f) / 3.f;

                    ImGui::PushItemWidth(avg_size);

                    float col1[4] = { cin.bg_color.x, cin.bg_color.y, cin.bg_color.z, 1.f };

                    ttt_id = "Background##bg_cin" + std::to_string(col_n) + "_" + std::to_string(cc) + "_";

                    ImGui::ColorEdit4(ttt_id.c_str(), col1, ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_NoInputs);

                    cin.bg_color = ImVec4(col1[0], col1[1], col1[2], col1[3]);

                    ImGui::SameLine();

                    std::string component_text = "##up_arrow_txt_" + std::to_string(cc) + "_" + std::to_string(col_n);
                    ImGui::PushID(component_text.c_str());
                    if (ImGui::ImageButton((void*)up_arrow_txt, ImVec2(12, 12)))
                    {
                        save::move_item_on_column(column_item, col_n, false);
                    }
                    ImGui::PopID();

                    ImGui::SameLine();

                    component_text = "##down_arrow_txt_" + std::to_string(cc) + "_" + std::to_string(col_n);
                    ImGui::PushID(component_text.c_str());
                    if (ImGui::ImageButton((void*)down_arrow_txt, ImVec2(12, 12)))
                    {
                        save::move_item_on_column(column_item, col_n, true);
                    }
                    ImGui::PopID();

                    component_text = "Label##label_txt_" + std::to_string(cc) + "_" + std::to_string(col_n);
                    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 5);
                    ImGui::InputText(component_text.c_str(), &cin.label);

                    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 5);

                    ttt_id = "Remove##remove_cin" + std::to_string(col_n) + "_" + std::to_string(cc) + "_";

                    if (ImGui::Button(ttt_id.c_str(), ImVec2(avg_size, 20)))
                    {
                        save::remove_item_on_column(column_item, col_n);
                    }

                    ImGui::SameLine();

                    ttt_id = "Done##edit_cin" + std::to_string(col_n) + "_" + std::to_string(cc) + "_";
                    if (ImGui::Button(ttt_id.c_str(), ImVec2(avg_size + 1, 20)))
                    {
                        cin.editing = false;
                    }
                }

                break;
            }
        }
    }

    if (column_item->enter_url_frame)
    {
        ImGui::SetNextWindowSize(ImVec2(300, 100));
        ImGui::SetNextWindowFocus();

        ImGui::Begin("Import Image from URL", &column_item->enter_url_frame, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

        ImGui::InputText("Image URL##asddsad_", &column_item->current_url);
        
        if (ImGui::Button("Import##image_url_import") && column_item->current_url.length() > 0)
        {
            std::string dwnld_URL = column_item->current_url;

            std::string savepath = utils::get_current_directory("tmp\\");

            _mkdir(savepath.c_str());

            savepath += random_string(6);

            std::string extension = dwnld_URL.substr(dwnld_URL.find_last_of(".") + 1);
            std::transform(extension.begin(), extension.end(), extension.begin(), std::tolower);

            savepath += ".";

            savepath += extension;

            URLDownloadToFile(NULL, utils::convert_char_array_to_wchar(dwnld_URL.c_str()), utils::convert_char_array_to_wchar(savepath.c_str()), 0, NULL);

            column_items c_items = column_items();
            column_image cc_image = column_image(savepath);
            c_items.add_image(column_item, cc_image);

            save::add_item_to_column(column_item, c_items);

            column_item->enter_url_frame = false;
        }

        ImGui::End();
    }

    ImGui::PopStyleVar();
    ImGui::PopStyleVar();
    ImGui::EndChild();
}

void gui::draw_project_screen()
{
    bool open = true;

    ImGui::SetNextWindowPos(ImVec2(-1, 0));
    ImGui::SetNextWindowSize(ImVec2(globals::width, globals::height));

    ImGui::Begin("Test", &open, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar );
    {
        ImGui::PushFont(globals::big_font);
        ImGui::SetCursorPos(ImVec2((ImGui::GetWindowSize().x / 2.f) - ImGui::CalcTextSize("Name").x / 2.f - 7.f, ImGui::GetWindowSize().y / 2.f - 90.f));
        ImGui::Text("Name");
        ImGui::PopFont();
        ImGui::SetCursorPos(ImVec2((ImGui::GetWindowSize().x / 2.f) - (57.f), ImGui::GetWindowSize().y / 2.f - 60.f));
        ImGui::SetNextItemWidth(100.f);
        ImGui::InputText("##project_name", &globals::project_name);
        ImGui::SetCursorPos(ImVec2((ImGui::GetWindowSize().x / 2.f) - (57.f), ImGui::GetWindowSize().y / 2.f - 30));
        if (ImGui::Button("New Project##asdasd", ImVec2(100.f, 0.0f)) && globals::project_name.length() > 0)
        {
            globals::intro_showed = true;
        }
        ImGui::SetCursorPos(ImVec2((ImGui::GetWindowSize().x / 2.f) - (57.f), ImGui::GetWindowSize().y / 2.f));
        if (ImGui::Button("Load Project##asdasd", ImVec2(100.f, 0.0f)))
        {
            std::string file = utils::open_file_dialog(L"Column Projects (*.clmns)\0*.clmns;");
            if (file.length() > 0)
            {
                globals::intro_showed = true;
                save::load_board(file);
            }
        }
    }
    ImGui::End();
}

void gui::draw_top_barmenu()
{
    static bool options_open = false;
    static int current_settings_tab = 0;

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(10.f, 10.f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10.f, 10.f));

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Program"))
        {
            ImGui::SetCursorPosX(ImGui::GetCursorPosX());
            if (ImGui::MenuItem("Close Project"))
            {
                globals::project_name = "";
                globals::intro_showed = false;
                save::reset_board();
            }
            ImGui::SetCursorPosX(ImGui::GetCursorPosX());
            if (ImGui::MenuItem("Exit Program"))
            {
                exit(-1);
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("File"))
        {
            ImGui::SetCursorPosX(ImGui::GetCursorPosX());
            if (globals::project_path.length() > 0)
            {
                if (ImGui::MenuItem("Save"))
                {
                    save::save_board(globals::project_path);
                }
            }
            if (ImGui::MenuItem("Save As"))
            {
                std::string path = utils::save_file_dialog(L"Column Projects (*.clmns)\0*.clmns;");
                if (path.length() > 0)
                {
                    save::save_board(path);
                }
            }
            ImGui::EndMenu();
        }
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 5.f);
        if (ImGui::BeginMenu("Project"))
        {
            ImGui::SetCursorPosX(ImGui::GetCursorPosX());

            std::string project_n = "Current: " + globals::project_name;

            ImGui::MenuItem(project_n.c_str(), NULL, false, false);

            if (ImGui::MenuItem("Clear Project"))
            {
                save::reset_board();
            }
            ImGui::EndMenu();
        }
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 5.f);
        if (ImGui::BeginMenu("Settings"))
        {
            if (ImGui::IsMouseDown(0))
            {
                current_settings_tab = 0;
                options_open = true;
            }
            else {
                if (ImGui::MenuItem("Open"))
                {
                    current_settings_tab = 0;
                    options_open = true;
                }
            }
            ImGui::EndMenu();
        }
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 5.f);
        if (ImGui::BeginMenu("Help"))
        {
            ImGui::MenuItem("You add components with the controls at the bottom", NULL, false, false);
            ImGui::MenuItem("Right click: Open settings of component", NULL, false, false);
            ImGui::MenuItem("Middle click: Select component", NULL, false, false);

            ImGui::EndMenu();
        }
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 5.f);
        if (ImGui::BeginMenu("About"))
        {
            ImGui::MenuItem("-------------------------", NULL, false, false);
            ImGui::MenuItem("Columns", NULL, false, false);
            ImGui::MenuItem("-------------------------", NULL, false, false);
            ImGui::MenuItem("Made by: Florian Dreschel", NULL, false, false);
            ImGui::MenuItem("-------------------------", NULL, false, false);
            ImGui::MenuItem("Special Thanks to:", NULL, false, false);
            ImGui::MenuItem("ImGui Library", NULL, false, false);
            ImGui::MenuItem("-------------------------", NULL, false, false);
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    if (options_open)
    {
        ImGui::SetNextWindowSize(ImVec2(350, 150));
        ImGui::SetNextWindowFocus();

        ImGui::Begin("Columns Settings", &options_open, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

        if (ImGui::Button("Columns", ImVec2(165, 20)))
        {
            current_settings_tab = 0;
        }
        ImGui::SameLine();
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() - 10);
        if (ImGui::Button("Save", ImVec2(165, 20)))
        {
            current_settings_tab = 1;
        }

        ImGui::Separator();

        switch (current_settings_tab)
        {
        case 0:
            ImGui::InputInt("Column width##column_w_id", &globals::size_of_columns);
            break;
        case 1:
            if (ImGui::Checkbox("Copy Images##asddsad_", &globals::cache_images))
            {
                if (globals::cache_images)
                {
                    if (globals::project_path.length() > 0)
                    {
                        save::save_board(globals::project_path);
                    }
                }
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip("Save project images to a new directory");
            break;
        default:
            break;
        }

        ImGui::End();
    }

    ImGui::PopStyleVar();
    ImGui::PopStyleVar();
}

void gui::load_arrows()
{
    if (!down_arrow_txt  && !up_arrow_txt 
     && !left_arrow_txt  && !right_arrow_txt)
    {
        PDIRECT3DTEXTURE9 tmp_txt = NULL;
        int w_tmp, h_tmp;

        utils::load_texture_file(
            utils::get_current_directory("system\\down_arrow.png").c_str(),
            &tmp_txt, &w_tmp, &h_tmp);

        down_arrow_txt = tmp_txt;

        utils::load_texture_file(
            utils::get_current_directory("system\\up_arrow.png").c_str(),
            &tmp_txt, &w_tmp, &h_tmp);

        up_arrow_txt = tmp_txt;

        utils::load_texture_file(
            utils::get_current_directory("system\\left_arrow.png").c_str(),
            &tmp_txt, &w_tmp, &h_tmp);

        left_arrow_txt = tmp_txt;

        utils::load_texture_file(
            utils::get_current_directory("system\\right_arrow.png").c_str(),
            &tmp_txt, &w_tmp, &h_tmp);

        right_arrow_txt = tmp_txt;
    }
}

ImGuiWindowFlags w_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoResize |
                           ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar;

void gui::draw_gui()
{
    load_arrows();

    ImGui::SetNextWindowPos(ImVec2(-1, 0));
    ImGui::SetNextWindowSize(ImVec2(globals::width - 4, globals::height));

    globals::height_of_board = globals::height - 70;

    bool open = true;
    ImGui::Begin("Main", &open, w_flags);
    {
        gui::draw_top_barmenu();

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);

        ImGui::SetNextWindowContentSize(ImVec2(globals::size_of_columns * (float)globals::column_count, 0));

        ImGui::BeginChild("##scrollingregion", ImVec2(-10, globals::height_of_board), false, ImGuiWindowFlags_AlwaysHorizontalScrollbar);

        ImGui::BeginColumns("asdasd", globals::column_count, ImGuiColumnsFlags_NoResize);

        for (int ii = 0; ii < globals::column_count; ii++)
        {
            if (ii + 1 == globals::column_count)
            {
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.f);
                if (ImGui::Button("New column"))
                {
                    globals::column_count += 1;
                    globals::item_list.push_back(new column());
                }
            }
            else {
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);

                int cc = 0;
                for (column* column_item : globals::item_list)
                {
                    if (cc == ii)
                    {
                        draw_column(cc, column_item);

                        draw_addition_options(cc, column_item);
                    }
                    cc += 1;
                }

                ImGui::NextColumn();
            }
        }

        ImGui::EndColumns();
        ImGui::EndChild();

        ImGui::Separator();
    }
    ImGui::End();
}

