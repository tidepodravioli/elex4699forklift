#include "../headers/RDraw.hpp"

RDraw::RDraw()
{
    cvui::init("Arena");
    m_arena = imread("test_arena.jpg");
    m_arena_height = m_arena.rows;
    m_arena_width = m_arena.cols;
    m_grid = Mat(m_arena_height, m_arena_width, CV_8UC3, m_overlay_color);
    m_cell_height = m_arena_height / m_grid_rows;
    m_cell_width = m_arena_width / m_grid_cols;
    m_obstacles.resize(m_grid_rows, vector<bool>(m_grid_cols, false));    

    // Initialize the grid with the overlay color
    for (int i = 0; i <= m_grid_rows; ++i) {
        int y = m_grid_origin.y + i * (m_cell_height);
        line(m_grid, Point(m_grid_origin.x, y), Point(m_grid_origin.x + m_arena_width, y), m_grid_line_color, m_grid_thickness);
        cv::imshow("Arena", m_arena);
    }

    for (int j = 0; j <= m_grid_cols; ++j) {
        int x = m_grid_origin.x + j * (m_cell_width);
        line(m_grid, Point(x, m_grid_origin.y), Point(x, m_grid_origin.y + m_arena_height), m_grid_line_color, m_grid_thickness);
        cv::imshow("Arena", m_arena);
    }
}

RDraw::~RDraw()
{
    cv::destroyAllWindows();
}

bool RDraw::drawArena()
{
    cvui::context("Arena");
    cv::Point mouse = cvui::mouse();
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

    for (int i = 0; i < m_grid_rows; ++i) {
        for (int j = 0; j < m_grid_cols; ++j) {
            int x = m_grid_origin.x + j * m_cell_width;
            int y = m_grid_origin.y + i * m_cell_height;
            if (m_obstacles[i][j]) {
                rectangle(m_grid, Rect(x + m_grid_thickness, y + m_grid_thickness,
                    m_cell_width - m_grid_thickness, m_cell_height - m_grid_thickness), m_obstacles_color, m_highlight_thickness);
            }
            else {
                rectangle(m_grid, Rect(x + m_grid_thickness, y + m_grid_thickness,
                    m_cell_width - m_grid_thickness, m_cell_height - m_grid_thickness), m_overlay_color, m_highlight_thickness);
            }
        }
    }

    m_arena =  Scalar(0, 0, 0); // Clear the arena image
    m_arena = imread("test_arena.jpg"); // Reload the frame
    addWeighted(m_arena, 0.5, m_grid, 0.5, 0, m_arena); // Overlay the grid on the arena image

    cvui::update();
    cv::imshow("Arena", m_arena);
    cv::waitKey(1);

    return true;
}