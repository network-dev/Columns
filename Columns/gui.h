#pragma once

#ifndef GUI_H
#define GUI_H

#include "definitions.h"

namespace gui
{
    extern void draw_gui();
    extern void draw_top_barmenu();
    extern void draw_column(int cc, column* column_item);
    extern void draw_project_screen();

    extern void draw_addition_options(int cc, column* column_item);
}

#endif
