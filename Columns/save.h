#pragma once

#ifndef SAVE_H
#define SAVE_H

#include "definitions.h"

namespace save
{
    extern void replace_item_on_colum(column* c, int col_idx, column_items replacement);
    extern void duplicate_column(column* c);
    extern void move_item_on_column(column* c, int col_idx, bool move_down);
    extern void move_column(column* c, int col_idx, bool move_right);
    extern void remove_column(column* c);
    extern void save_board(std::string path);
    extern void load_board(std::string path);
    extern void add_item_to_column(column* c, column_items i);
    extern void add_column(column* c);
    extern void remove_item_on_column(column* c, int col_idx);
    extern void reset_board();
}

#endif
