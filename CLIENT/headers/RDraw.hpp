#include "cvui.h"
#include <vector>

using namespace std;
using namespace cv;
using namespace cvui;

class RDraw
{
    private:
        //Parameters
        int m_arena_height, m_arena_width;
        int m_settings_height, m_settings_width;
        int m_cell_height, m_cell_width;
        Mat m_arena, m_grid, m_settings;

        //Grid Configuration
        int m_grid_rows = 25;
        int m_grid_cols = 25;
        Scalar m_overlay_color = Scalar(200, 200, 200); // Light Gray
        Scalar m_grid_line_color = Scalar(100, 100, 100); // Gray
        Scalar m_path_color = Scalar(0, 255, 0); // Green
        Scalar m_obstacles_color = Scalar(0, 0, 255); // Red
        int m_highlight_thickness = -1; // Filled
        int m_grid_thickness = 1; // Thickness of grid lines
        int m_padding = 1; // Padding between grid cells

        //Grid Dimensions
        Point m_grid_origin = Point(0, 0); // Top-left corner of the grid

        //UI

        //Obstacles
        vector<vector<bool>> m_obstacles;

    public:
        RDraw();
        ~RDraw();

        bool drawArena();
        bool drawUI();
};