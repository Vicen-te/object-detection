
// Copyright (c) 2025+ Vicen-te
// This code is released under the MIT License.

#pragma once

// C++
#include <string>
#include <memory>

// OpenCV
#include <opencv2/dnn.hpp>

class YoloModel
{
private:
    // The pre-trained YOLO model as an OpenCV DNN network
    std::shared_ptr<cv::dnn::Net> net;

    // Flag indicating whether to use CUDA for model execution
    bool use_cuda;

    /**
     * Reconfigures the backend and target for CUDA or CPU usage.
     * This is called both in the constructor and in SetUseCuda.
     */
    void ConfigureBackendAndTarget();

public:
    /**
     * Constructor for YoloModel.
     * Loads the YOLO model from an ONNX file and configures its execution backend.
     * @param model_path The path to the ONNX model file.
     * @param use_cuda Flag to enable CUDA acceleration (true for CUDA, false for CPU).
     * @throws std::runtime_error If the model cannot be loaded or set up.
     */
    YoloModel(const std::string& model_path, bool use_cuda);

    /**
     * Gets the pre-trained YOLO model network.
     * @return A shared pointer to the OpenCV DNN network.
     */
    inline std::shared_ptr<cv::dnn::Net> GetNet() const { return net; }

    /**
     * Sets whether the model should use CUDA for execution.
     * @param use_cuda Flag to enable CUDA acceleration (true for CUDA, false for CPU).
     */
    void SetUseCuda(bool use_cuda);

    /**
     * Gets the current status of CUDA usage.
     * @return True if CUDA is enabled, false if using CPU.
     */
    bool IsCudaEnabled() const;

    /**
     * Checks if the model was successfully loaded.
     * @return True if the model was loaded successfully, false otherwise.
     */
    bool IsModelLoaded() const;
};
