#include <vector>
#include <opencv2/opencv.hpp>

class RDraw
{
    private:
        //Parameters
        int m_arena_height, m_arena_width;
        int m_cell_height, m_cell_width;
        cv::Mat m_arena, m_grid, m_settings;

        //Grid Configuration
        int m_grid_rows = 25;
        int m_grid_cols = 25;
        cv::Scalar m_overlay_color = cv::Scalar(200, 200, 200); // Light Gray
        cv::Scalar m_grid_line_color = cv::Scalar(100, 100, 100); // Gray
        cv::Scalar m_path_color = cv::Scalar(0, 255, 0); // Green
        cv::Scalar m_obstacles_color = cv::Scalar(0, 0, 255); // Red
        int m_highlight_thickness = -1; // Filled
        int m_grid_thickness = 1; // Thickness of grid lines
        bool m_edit_obstacles = false; // Edit mode for obstacles
        bool m_edit_path = false; // Edit mode for path

        //Grid Dimensions
        cv::Point m_grid_origin = cv::Point(0, 0); // Top-left corner of the grid

        //UI
        int m_settings_width = 200; // Width of the UI panel
        int m_settings_height = 300; // Height of the UI panel
        int m_padding = 10; // Padding around UI elements
        int m_spacing = 30; // Spacing between UI elements
        bool m_auto = false; // Auto mode toggle
        bool m_fast = false; // Fast mode toggle
        bool m_start = false;

        //Path
        std::vector<std::vector<bool>> m_path;

        //Obstacles
        std::vector<std::vector<bool>> m_obstacles;

    public:
        RDraw();
        ~RDraw();
    
        bool drawArena();
        bool drawUI();

        std::vector<std::vector<bool>> getPath() {return m_path;};
        std::vector<cv::Point2i> getPathAsPoints();
        std::vector<std::vector<bool>> getObstacles() {return m_obstacles;};
        std::vector<cv::Point2i> getObstaclesAsPoints();

        bool getAuto() {return m_auto;};
        bool getFast() {return m_fast;};
        bool getStart() {return m_start;};
        void setStart(bool start) {m_start = start;};
        
        void setPath(std::vector<std::vector<bool>> grid) {m_path = grid;};
        void setObstacles(std::vector<std::vector<bool>> obstacles) {m_obstacles = obstacles;};
};