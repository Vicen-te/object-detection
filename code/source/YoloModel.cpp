
// Copyright (c) 2025+ Vicen-te
// This code is released under public domain

// Header
#include "YoloModel.hpp"

// C++
#include <stdexcept> 

YoloModel::YoloModel(const std::string& model_path, bool use_cuda) : 
    use_cuda(use_cuda) //< Initialize use_cuda with the constructor parameter
{
    // Try loading the model from the specified ONNX file
    net = std::make_shared<cv::dnn::Net>(cv::dnn::readNetFromONNX(model_path));

    if (net->empty()) 
    {
        throw std::runtime_error("Failed to load YOLO model from: " + model_path);
    }

    // Configure backend and target for execution
    ConfigureBackendAndTarget();
}

void YoloModel::ConfigureBackendAndTarget()
{
    // Reconfigure the backend and target based on the current use_cuda flag
    cv::dnn::Backend backend = use_cuda ? cv::dnn::DNN_BACKEND_CUDA : cv::dnn::DNN_BACKEND_OPENCV;
    cv::dnn::Target target = use_cuda ? cv::dnn::DNN_TARGET_CUDA : cv::dnn::DNN_TARGET_CPU;

    net->setPreferableBackend(backend);
    net->setPreferableTarget(target);
}

void YoloModel::SetUseCuda(bool use_cuda)
{
    this->use_cuda = use_cuda;

    // Reconfigure the backend and target based on the new setting
    ConfigureBackendAndTarget();
}

bool YoloModel::IsCudaEnabled() const
{
    return use_cuda;
}

bool YoloModel::IsModelLoaded() const
{
    return !net->empty();
}
