#include <deque>
#include <vector>
#include <algorithm>
#include <opencv2/opencv.hpp> // for cv::Vec3f

class MedianFilter3D {
public:
    MedianFilter3D(int window_size) : window_size(window_size) {}

    cv::Vec3f update(const cv::Vec3f& new_sample) {
        if (buffer.size() == window_size) {
            buffer.pop_front();
        }
        buffer.push_back(new_sample);

        std::vector<float> xs, ys, zs;
        for (auto& v : buffer) {
            xs.push_back(v[0]);
            ys.push_back(v[1]);
            zs.push_back(v[2]);
        }

        return cv::Vec3f(
            median(xs),
            median(ys),
            median(zs)
        );
    }

private:
    int window_size;
    std::deque<cv::Vec3f> buffer;

    float median(std::vector<float>& values) {
        std::sort(values.begin(), values.end());
        size_t n = values.size();
        if (n % 2 == 1)
            return values[n / 2];
        else
            return (values[n / 2 - 1] + values[n / 2]) / 2.0f;
    }
};