#include "../headers/ArUcoTest.hpp"
#include "KalmanFilter3D.hpp"

ArUcoTest::ArUcoTest()
{
    
}

// === CONFIG ===
    const Point2i canvasCenter(300, 240);
    const float CAMERA_TO_WORLD_ROT = static_cast<float>(CV_PI); // or your actual offset
    const float SCALE = 100.0f; // adjust until it looks right on screen
    const float MAX_DELTA_PER_FRAME = 30.0f; // clamp noisy movement
    const float MAX_REASONABLE_JUMP = 0.1f;

    // === GLOBALS ===
    KalmanFilter kalman(6, 3, 0); // 3D position + velocity
    Mat state(6, 1, CV_32F);      // [x, y, z, dx, dy, dz]
    Mat meas(3, 1, CV_32F);       // [x, y, z]
    Vec3f lastFilteredTrans(0, 0, 0);

void ArUcoTest::start()
{
    RPiCamera camera(0, CAP_DSHOW);
    bool calib = camera.importCalibration("calibration.yaml");
    if(calib) cout << "Calibration successful!" << endl;

    const Point2i coords(300, 240);
    const float angle = -3.14159265358979;

    KalmanFilter3D filter;

    while (true)
    {
        // === Get tag translation vector ===
        Vec3d rawTrans;
        // Replace this with your tag detection method
        bool tagFound = camera.getTranslationClosestTag(rawTrans);

        // === Filter and scale ===
        Vec3f trans = filter.update(rawTrans);

        // === Rotate to top-down view ===
        float prop_angle = CV_PI - CAMERA_TO_WORLD_ROT;
        double x0 = canvasCenter.x + trans[0] * cos(prop_angle) + trans[2] * sin(prop_angle);
        double y0 = canvasCenter.y + trans[0] * sin(prop_angle) - trans[2] * cos(prop_angle);

        // === Draw ===
        Mat frame(480, 600, CV_8UC3, Scalar(255, 255, 255));
        circle(frame, canvasCenter, 10, Scalar(0, 0, 0), -1); // camera
        circle(frame, Point2d(x0, y0), 20, Scalar(0, 0, 255), -1); // tag

        if(tagFound){
            putText(frame, format("Distance: %.0001f", norm(trans)), Point(10, 30),
                FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0, 0, 0), 1);
            cout << trans << "\t" << rawTrans << endl;
        }

        imshow("Bird's Eye View", frame);

        Mat cam_frame;
        camera >> cam_frame;
        imshow("Camera", cam_frame);

        if(waitKey(1) == 'q') return;
    }
}

