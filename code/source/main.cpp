
// Copyright (c) 2025+ Vicen-te
// This code is released under the MIT License.

// Custom Headers
#include <YoloModel.hpp>
#include <LabelLoader.hpp>
#include <ObjectDetector.hpp>
#include <VideoCaptureManager.hpp>

int main()
{
    // Create LabelLoader instance
    LabelLoader label_loader;

    // Load the class names from file
    if (!label_loader.Load("./../../models/coco.txt"))
    {
        std::cerr << "Failed to load class names from file." << std::endl;
        return -1;
    }

    // Create VideoCaptureManager instance (device_id = 1, window_name = "YOLO11-OpenCV4.11.0")
    VideoCaptureManager capture_manager(1, "YOLO11-OpenCV4.11.0");

    // Load YOLO model
    YoloModel model("./../../models/yolo11x.onnx", true);

    // Create ObjectDetector using the YOLO model's network and class list
    ObjectDetector detector(model.GetNet(), label_loader.GetClassList());

    while (true)
    {
        if (!capture_manager.CaptureFrame())
        {
            std::cerr << "Failed to capture frame." << std::endl;
            break;
        }

        // Perform object detection
        detector.Detect(capture_manager.GetFrame());

        // Show the frame in the window
        capture_manager.ShowFrame();

        // Check if a key was pressed and exit if it's not -1 (ESC key or any key)
        if (capture_manager.WaitKey(1) != -1)
        {
            break;
        }
    }

    // Release the capture device
    capture_manager.ReleaseCapture();

    // Destroy the window
    capture_manager.DestroyWindow();

    return 0;
}