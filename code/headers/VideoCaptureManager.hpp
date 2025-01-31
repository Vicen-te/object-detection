
// Copyright (c) 2025+ Vicen-te
// This code is released under the MIT License.

#pragma once

// C++
#include <string>
#include <iostream>

// OpenCV
#include <opencv2/opencv.hpp>

class VideoCaptureManager
{
private:
    cv::VideoCapture capture;  // Video capture object
    cv::Mat frame;            // Current frame from the capture
    std::string window_name;   // Name of the window for displaying the frame

public:
    /**
     * Constructor for VideoCaptureManager.
     * Initializes the capture device and window name.
     * @param device_id The ID of the capture device (usually 0 for default webcam).
     * @param window_name The name of the window to display the captured frames.
     */
    VideoCaptureManager(int device_id, const std::string& window_name)
        : window_name(window_name)
    {
        // Open the camera
        capture.open(device_id, cv::CAP_DSHOW);

        if (!capture.isOpened()) 
        {
            std::cerr << "Error: Could not open video capture device." << std::endl;
            throw std::runtime_error("Failed to open capture device");
        }

        // Set the window name for imshow
        cv::namedWindow(window_name, cv::WINDOW_NORMAL);
    }

    /**
     * Capture a frame from the camera.
     * @return true if a frame is successfully captured, false otherwise.
     */
    inline bool CaptureFrame()
    {
        capture.read(frame);

        // Check if frame is empty
        return !frame.empty();
    }

    /**
     * Display the captured frame in the window.
     */
    inline void ShowFrame() const
    {
        cv::imshow(window_name, frame);
    }

    /**
     * Wait for a key press for a specified amount of time.
     * @param delay The time to wait in milliseconds.
     * @return The key pressed (if any).
     */
    inline int WaitKey(int delay = 1)
    {
        return cv::waitKey(delay);
    }

    /**
     * Release the capture device.
     */
    inline void ReleaseCapture()
    {
        capture.release();
    }

    /**
     * Destroy the window displaying the captured frames.
     */
    inline void DestroyWindow() const
    {
        cv::destroyWindow(window_name);
    }

    /**
     * Get the captured frame.
     * @return The current frame captured from the video feed.
     */
    inline cv::Mat GetFrame() const
    {
        return frame;
    }
};
