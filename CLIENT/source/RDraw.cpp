#define CVUI_IMPLEMENTATION
#include "cvui.h"
#include "../headers/RDraw.hpp"

using namespace std;


RDraw::RDraw()
{
    cvui::init("Arena");
    m_arena = cv::imread("../../test_arena.jpg");
    m_arena_orig = m_arena.clone();

    m_arena_height = m_arena.rows;
    m_arena_width = m_arena.cols;
    m_grid = cv::Mat(m_arena_height, m_arena_width, CV_8UC3, m_overlay_color);
    m_cell_height = m_arena_height / m_grid_rows;
    m_cell_width = m_arena_width / m_grid_cols;
    m_settings = cv::Mat(m_settings_height, m_settings_width, CV_8UC3, m_overlay_color);
    m_path.resize(m_grid_rows, std::vector<bool>(m_grid_cols, false));
    m_obstacles.resize(m_grid_rows, std::vector<bool>(m_grid_cols, false));    

    // Initialize the grid with the overlay color
    for (int i = 0; i <= m_grid_rows; ++i) {
        int y = m_grid_origin.y + i * (m_cell_height);
        cv::line(m_grid, cv::Point(m_grid_origin.x, y), cv::Point(m_grid_origin.x + m_arena_width, y), m_grid_line_color, m_grid_thickness);
        cv::imshow("Arena", m_arena);
    }
    for (int j = 0; j <= m_grid_cols; ++j) {
        int x = m_grid_origin.x + j * (m_cell_width);
        cv::line(m_grid, cv::Point(x, m_grid_origin.y), cv::Point(x, m_grid_origin.y + m_arena_height), m_grid_line_color, m_grid_thickness);
        cv::imshow("Arena", m_arena);
    }

    cvui::init("GUI");
}

RDraw::~RDraw()
{
    cv::destroyAllWindows();
}

bool RDraw::drawArena()
{
    cvui::context("Arena");
    cv::Point mouse = cvui::mouse();

    // Edit Path
    if (m_edit_path) {
        if (cvui::mouse(cvui::CLICK)) {
            int mouseX = mouse.x;
            int mouseY = mouse.y;

            if (mouseX >= m_grid_origin.x && mouseX < m_grid_origin.x + m_arena_width &&
                mouseY >= m_grid_origin.y && mouseY < m_grid_origin.y + m_arena_height) {
                int cellX = (mouseX - m_grid_origin.x) / m_cell_width;
                int cellY = (mouseY - m_grid_origin.y) / m_cell_height;

                if (cellX >= 0 && cellX < m_grid_cols && cellY >= 0 && cellY < m_grid_rows) {
                    // Toggle the path state
                    m_path[cellY][cellX] = !m_path[cellY][cellX];
                }
            }
        }
    }

    // Edit Obstacles
    if (m_edit_obstacles) {
        if (cvui::mouse(cvui::CLICK)) {
            int mouseX = mouse.x;
            int mouseY = mouse.y;

            if (mouseX >= m_grid_origin.x && mouseX < m_grid_origin.x + m_arena_width &&
                mouseY >= m_grid_origin.y && mouseY < m_grid_origin.y + m_arena_height) {
                int cellX = (mouseX - m_grid_origin.x) / m_cell_width;
                int cellY = (mouseY - m_grid_origin.y) / m_cell_height;

                if (cellX >= 0 && cellX < m_grid_cols && cellY >= 0 && cellY < m_grid_rows) {
                    // Toggle the obstacle state
                    m_obstacles[cellY][cellX] = !m_obstacles[cellY][cellX];
                }
            }
        }
    }

    // Draw path and obstacles
    for (int i = 0; i < m_grid_rows; ++i) {
        for (int j = 0; j < m_grid_cols; ++j) {
            int x = m_grid_origin.x + j * m_cell_width;
            int y = m_grid_origin.y + i * m_cell_height;
            if (m_path[i][j]) {
                cv::rectangle(m_grid, cv::Rect(x + m_grid_thickness, y + m_grid_thickness,
                    m_cell_width - m_grid_thickness, m_cell_height - m_grid_thickness), m_path_color, m_highlight_thickness);
            }
            else if (m_obstacles[i][j]) {
                cv::rectangle(m_grid, cv::Rect(x + m_grid_thickness, y + m_grid_thickness,
                    m_cell_width - m_grid_thickness, m_cell_height - m_grid_thickness), m_obstacles_color, m_highlight_thickness);
            }
            else {
                cv::rectangle(m_grid, cv::Rect(x + m_grid_thickness, y + m_grid_thickness,
                    m_cell_width - m_grid_thickness, m_cell_height - m_grid_thickness), m_overlay_color, m_highlight_thickness);
            }
        }
    }

    m_arena = cv::Mat(cv::Size2i(m_arena_width, m_arena_height), CV_8UC3, cv::Scalar(0,0,0)); // Clear the arena image
    m_arena = m_arena_orig.clone(); // Reload the frame
    cv::resize(m_arena, m_arena, cv::Size2i(m_arena_width, m_arena_height));
    cv::addWeighted(m_arena, 0.5, m_grid, 0.5, 0, m_arena); // Overlay the grid on the arena image

    cvui::update();
    cv::imshow("Arena", m_arena);
    cv::waitKey(1);

    return true;
}

bool RDraw::drawUI()
{
    cvui::context("GUI");
    cv::Point m_settings_position = cv::Point(0, 0);
    cvui::window(m_settings, m_settings_position.x, m_settings_position.y, m_settings_width, m_settings_height, "GUI");
    m_settings_position += cv::Point(m_padding, m_spacing); // Start position for UI elements

    // --- Status ---
    cvui::text(m_settings, m_settings_position.x, m_settings_position.y, "Status: ");
    cvui::text(m_settings, m_settings_position.x + 50, m_settings_position.y, "ONLINE"); // Placeholder for actual status value

    // --- Mode ---
    m_settings_position += cv::Point(0, 35);
    cvui::text(m_settings, m_settings_position.x, m_settings_position.y, "Mode");

    // Mode Toggle Button
    std::string mode_label = m_auto ? "Auto" : "Manual";
    m_settings_position += cv::Point(0, 15);
    if (cvui::button(m_settings, m_settings_position.x, m_settings_position.y, 80, 30, mode_label)) {
        m_auto = !m_auto; // Toggle mode state
    }

    if(m_auto)
    {
        std::string mode_label = m_start ? "Stop" : "Start";
        m_settings_position += cv::Point(90, 0);
        if (cvui::button(m_settings, m_settings_position.x, m_settings_position.y, 80, 30, mode_label)) {
            m_start = !m_start; // Toggle mode state
        }

        m_settings_position -= cv::Point(90, 0);
    }
    else m_start = false;

    // ARENA CAM SHOW BUTTON
    std::string cam_show_label = m_showcam ? "Hide arena" : "Show arena";
    m_settings_position += cv::Point(0, 40);
    if(cvui::button(m_settings, m_settings_position.x, m_settings_position.y, 100, 30, cam_show_label))
    {
        m_showcam = !m_showcam;
    }
    
    // --- Speed ---
    m_settings_position += cv::Point(0, 40);
    cvui::text(m_settings, m_settings_position.x, m_settings_position.y, "Speed");

    // Speed Toggle Button
    std::string speed_label = m_fast ? "Fast" : "Slow";
    m_settings_position += cv::Point(0, 15);
    if (cvui::button(m_settings, m_settings_position.x, m_settings_position.y, 80, 30, speed_label)) {
        m_fast = !m_fast; // Toggle speed state
    }

    // Mutually exclusive checkboxes for path and obstacles (WIP)
    m_settings_position += cv::Point(0, 55);
    bool path_checkbox_changed = cvui::checkbox(m_settings, m_settings_position.x, m_settings_position.y, "Edit Path", &m_edit_path);
    m_settings_position += cv::Point(0, 25);
    bool obstacles_checkbox_changed = cvui::checkbox(m_settings, m_settings_position.x, m_settings_position.y, "Edit Obstacles", &m_edit_obstacles);

    if (path_checkbox_changed && m_edit_path) {
        m_edit_obstacles = false;
    }
    else if (obstacles_checkbox_changed && m_edit_obstacles) {
        m_edit_path = false;
    }

    // Exit button
    m_settings_position += cv::Point(0, 45);
    if (cvui::button(m_settings, m_settings_position.x, m_settings_position.y, 50, 30, "Exit")) {
        return false;
    }

    cvui::update();
    cv::imshow("GUI", m_settings);
    cv::waitKey(1);

    return true;
}

vector<cv::Point2i> RDraw::getPathAsPoints()
{
    vector<vector<bool>> boolpoints = getPath();
    std::vector<cv::Point2i> points;

    int rows = boolpoints.size();
    if (rows == 0) return points;

    int cols = boolpoints[0].size();

    // Size of each cell in pixels
    float cellWidth = static_cast<float>(m_arena_width) / cols;
    float cellHeight = static_cast<float>(m_arena_height) / rows;

    // Loop over the grid
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            if (boolpoints[y][x]) {
                // Map grid (x, y) to window pixel coordinates
                int px = static_cast<int>(x * cellWidth + cellWidth / 2);
                int py = static_cast<int>(y * cellHeight + cellHeight / 2);
                points.emplace_back(px, py);
            }
        }
    }

    return points;
}

vector<cv::Point2i> RDraw::getObstaclesAsPoints()
{
    vector<vector<bool>> boolpoints = getObstacles();
    std::vector<cv::Point2i> points;

    int rows = boolpoints.size();
    if (rows == 0) return points;

    int cols = boolpoints[0].size();

    // Size of each cell in pixels
    float cellWidth = static_cast<float>(m_arena_width) / cols;
    float cellHeight = static_cast<float>(m_arena_height) / rows;

    // Loop over the grid
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            if (boolpoints[y][x]) {
                // Map grid (x, y) to window pixel coordinates
                int px = static_cast<int>(x * cellWidth + cellWidth / 2);
                int py = static_cast<int>(y * cellHeight + cellHeight / 2);
                points.emplace_back(px, py);
            }
        }
    }

    return points;
}