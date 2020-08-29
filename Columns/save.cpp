#include "save.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <direct.h>
#include <algorithm>

#include "utils.h"
#include "globals.h"

void save::replace_item_on_colum(column* c, int col_idx, column_items replacement)
{
    if (c->columns_i_l.size() >= col_idx)
    {
        c->columns_i_l[col_idx] = replacement;
    }
    else {
        std::cout << "Impossible replacement -> " << c->columns_i_l.size() << " (" << col_idx << ") Out of bounds" << std::endl;
    }
}

void save::move_column(column* c, int col_idx, bool move_right)
{
    column* og_c = globals::item_list[col_idx];

    std::cout << globals::item_list.size() << " - " << col_idx << std::endl;

    if (move_right)
    {
        if (globals::item_list.size() > col_idx + 1)
        {
            globals::item_list[col_idx] = globals::item_list[col_idx + 1];
            globals::item_list[col_idx + 1] = og_c;
        }
    }
    else {
        if (col_idx - 1 >= 0)
        {
            globals::item_list[col_idx] = globals::item_list[col_idx - 1];
            globals::item_list[col_idx - 1] = og_c;
        }
    }
}

void save::duplicate_column(column* c)
{
    column* new_column = new column();
    new_column->columns_i_l = c->columns_i_l;
    new_column->column_num = c->column_num;
    new_column->title = c->title;

    std::vector<column*> tmp_columns;
    for (column* column_item : globals::item_list)
    {
        if (column_item == c)
        {
            tmp_columns.push_back(column_item);
            tmp_columns.push_back(new_column);
        }
        else
        {
            tmp_columns.push_back(column_item);
        }
    }

    globals::item_list = tmp_columns;
    globals::column_count += 1;
}

void save::move_item_on_column(column* c, int col_idx, bool move_down)
{
    int columns = c->columns_i_l.size() - 1; 

    std::cout << globals::item_list.size() << " - " << col_idx << std::endl;

    if (move_down)
    {
        if (columns >= col_idx + 1)
        {
            column_items og_item = c->columns_i_l[col_idx];

            c->columns_i_l[col_idx] = c->columns_i_l[col_idx + 1];
            c->columns_i_l[col_idx + 1] = og_item;
        }
    }
    else {
        if (col_idx - 1 >= 0)
        {
            column_items og_item = c->columns_i_l[col_idx];

            c->columns_i_l[col_idx] = c->columns_i_l[col_idx - 1];
            c->columns_i_l[col_idx - 1] = og_item;
        }
    }
}

void save::remove_column(column* c)
{
    std::vector<column*> tmp_column_list;
    for (column* column_item : globals::item_list)
    {
        if (c != column_item)
        {
            tmp_column_list.push_back(column_item);
        }
    }
    globals::column_count -= 1;
    globals::item_list = tmp_column_list;
}

void save::remove_item_on_column(column* c, int col_idx)
{
    std::vector<column_items> tmp_columns_items;

    int idx = 0;
    for (column_items its : c->columns_i_l)
    {
        if (idx != col_idx)
        {
            tmp_columns_items.push_back(its);
        }

        idx += 1;
    }

    c->columns_i_l = tmp_columns_items;
    c->column_num -= 1;
}

void save::reset_board()
{
    globals::item_list.clear();
    globals::column_count = 1;
    globals::size_of_columns = 300.f;
}

void save::add_column(column* c)
{
    globals::item_list.push_back(c);
    globals::column_count += 1;
}

void save::add_item_to_column(column* c, column_items i)
{
    if (c->replace_with_next_addition)
    {
        save::replace_item_on_colum(c, c->selected_row_idx, i);
    }
    else {
        c->column_num += 1;
        c->columns_i_l.push_back(i);
    }
}

void save::save_board(std::string path)
{
    if (path.find(".clmns") == std::string::npos)
    {
        path += ".clmns";
    }

    std::ofstream myfile;
    myfile.open(path);

    myfile << "Name>" << globals::project_name << std::endl;

    int column_count = 1;
    for (column* column_item : globals::item_list)
    {
        myfile << "Column>" << column_count << ">" << column_item->title << std::endl;
        for (int col_n = 0; col_n < column_item->column_num; col_n++)
        {
            column_items item_ = column_item->columns_i_l[col_n];
            switch (item_.get_type())
            {
            case column_type::COLUMN_T_IMAGE:
            {
                column_image cim = item_.get_image();

                std::string file_path_to_save = cim.path;

                if (globals::cache_images)
                {
                    std::string cache_folder = globals::project_name += "_cache";

                    std::string path_to_folder = utils::get_current_directory(cache_folder);
                    _mkdir(path_to_folder.c_str());
                    std::string img_string = cache_folder + "\\img-" + std::to_string(column_count) + "-" + std::to_string(col_n) + ".";

                    std::string extension = cim.path.substr(cim.path.find_last_of(".") + 1);
                    std::transform(extension.begin(), extension.end(), extension.begin(), std::tolower);

                    std::cout << "ext: " << extension << std::endl;

                    img_string += extension;

                    std::string path_to_img = utils::get_current_directory(img_string);

                    std::cout << "From: " << cim.path << " To: " << path_to_img << std::endl;

                    std::string src = cim.path;
                    std::string dest = path_to_img;
                    BOOL rval = CopyFile(utils::convert_char_array_to_wchar(src.c_str()), utils::convert_char_array_to_wchar(dest.c_str()), FALSE);
                    std::cout << "Result: " << rval << std::endl;

                    file_path_to_save = path_to_img;
                }

                myfile << column_count << "-" << col_n << "-image-" << item_.get_height() << "-" << file_path_to_save;

                break;
            }
            case column_type::COLUMN_T_INPUT:
            {
                column_input cin = item_.get_input();

                if (cin.content.length() > 0 || cin.label.length() > 0)
                {
                    myfile << column_count << "-" << col_n << "-input-" << cin.bg_color.x << "-" << cin.bg_color.y << "-" << cin.bg_color.z << "-" << cin.label << "-" << cin.content;
                }
                else {
                    myfile << column_count << "-" << col_n << "-emptyinput-" << cin.bg_color.x << "-" << cin.bg_color.y << "-" << cin.bg_color.z;
                }

                break;
            }
            default:
                break;
            }

            myfile << "\n";
        }
        column_count += 1;
    }

    myfile.close();
}

void save::load_board(std::string path_to_docum)
{
    std::ifstream myfile;
    myfile.open(path_to_docum);
    globals::project_path = path_to_docum;

    reset_board();

    int idx_col = 1;
    column* new_column = new column();
    bool changed_first_column = false;
    for (std::string line = ""; getline(myfile, line); )
    {
        std::vector<std::string> splitted = utils::split_string(line, '-');
        std::vector<std::string> splitted2 = utils::split_string(line, '>');

        std::cout << line << " split2_size: " << splitted2.size() << std::endl;
        std::cout << line << " line_splitted_size = " << splitted.size() << std::endl;

        if (splitted2.size() > 0)
        {
            if (splitted2[0] == "Name")
            {
                std::cout << "Loading project: "  << splitted2[1] << std::endl;
                globals::project_name = splitted2[1];
                std::cout << "------------------" << std::endl;
            }
            if (splitted2[0] == "Column")
            {
                std::cout << "Column -> " << line << std::endl;
                int column_id = std::atoi(splitted2[1].c_str());

                if (column_id != idx_col)
                {
                    add_column(new_column);

                    idx_col = column_id;

                    new_column = new column();
                }

                new_column->title = splitted2[2];
            }
        }

        if (splitted.size() > 2)
        {
            changed_first_column = true;

            globals::size_of_columns = 300.f;

            int column_ = std::atoi(splitted[0].c_str());

            if (column_ != idx_col)
            {
                add_column(new_column);

                idx_col = column_;

                new_column = new column();
            }

            column_items items__ = column_items();

            if (splitted.size() > 2)
            {
                std::string col_type_string = splitted[2];

                if (col_type_string.find("input") != std::string::npos
                    && col_type_string.find("emptyinput") == std::string::npos)
                {
                    if (splitted.size() > 6)
                    {
                        column_input input_ = column_input();
                        std::string content_string = "";

                        int count_of_separators = 0;
                        bool skiped_first_char = false;
                        for (char char_in_line : line)
                        {
                            if (char_in_line == '-')
                            {
                                count_of_separators += 1;
                            }

                            if (count_of_separators >= 7 && skiped_first_char)
                            {
                                content_string += char_in_line;
                            }
                            else {
                                skiped_first_char = count_of_separators >= 7;
                            }
                        }

                        input_.content = content_string;
                        input_.label = splitted[6];

                        float r_input = std::atof(splitted[3].c_str());
                        float g_input = std::atof(splitted[4].c_str());
                        float b_input = std::atof(splitted[5].c_str());

                        input_.bg_color = ImVec4(r_input, g_input, b_input, 1.f);

                        items__.add_input(new_column, input_);

                        add_item_to_column(new_column, items__);
                    }
                    else
                    {
                        std::string error_s = "Skipped Invalid Entry -> '" + line + "'\n(Invalid Size: " + std::to_string(splitted.size()) + " Expected: 7)";
                        MessageBoxA(NULL, error_s.c_str(), NULL, MB_ICONERROR);
                    }
                }

                if (col_type_string.find("image") != std::string::npos)
                {
                    int count_of_separators = 0;
                    bool skiped_first_char = false;
                    std::string content_string = "";
                    for (char char_in_line : line)
                    {
                        if (char_in_line == '-')
                        {
                            count_of_separators += 1;
                        }

                        if (count_of_separators >= 4 && skiped_first_char)
                        {
                            content_string += char_in_line;
                        }
                        else {
                            skiped_first_char = count_of_separators >= 4;
                        }
                    }

                    column_image image_ = column_image(content_string);
                    std::cout << "loaded image: " << content_string << std::endl;
                    items__.add_image(new_column, image_, std::atoi(splitted[3].c_str()));

                    add_item_to_column(new_column, items__);
                }

                if (col_type_string.find("emptyinput") != std::string::npos)
                {
                    if (splitted.size() > 5)
                    {
                        column_input input_ = column_input();

                        input_.content = "";
                        input_.label = "";

                        float r_input = std::atof(splitted[3].c_str());
                        float g_input = std::atof(splitted[4].c_str());
                        float b_input = std::atof(splitted[5].c_str());

                        input_.bg_color = ImVec4(r_input, g_input, b_input, 1.f);

                        items__.add_input(new_column, input_);

                        add_item_to_column(new_column, items__);
                    }
                    else
                    {
                        std::string error_s = "Skipped Invalid Entry -> '" + line + "'\n(Invalid Size: " + std::to_string(splitted.size()) + " Expected: 6)";
                        MessageBoxA(NULL, error_s.c_str(), NULL, MB_ICONERROR);
                    }
                }
            }
        }
    }

    if (changed_first_column)
    {
        add_column(new_column);
    }

    myfile.close();
}
