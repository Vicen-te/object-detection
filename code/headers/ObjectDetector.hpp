
// Copyright (c) 2025+ Vicen-te
// This code is released under the MIT License.

#pragma once

// C++
#include <string>
#include <memory>
#include <vector>

// OpenCV
#include <opencv2/dnn/dnn.hpp>
#include <opencv2/core/types.hpp>


class ObjectDetector
{
private:
    // The pre-trained object detection model (YOLO, SSD, etc.)
    std::shared_ptr<cv::dnn::Net> net;

    // List of class names for the detected objects (e.g., ["person", "car", "dog", ...])
    std::shared_ptr<std::vector<std::string>> class_list;

    // Detection thresholds for object confidence and non-max suppression (NMS)
    float score_threshold;
    float nms_threshold;

    // Shape of the input image (e.g., 640x640 for YOLO)
    cv::Size image_shape;

    /**
      * Processes the raw detection data and extracts the class IDs, confidence scores,
      * and bounding boxes for each detected object.
      *
      * @param data Pointer to the detection data, where each detection consists of the
      *             following format: [x, y, width, height, class_1_score, class_2_score, ..., class_n_score].
      * @param rows The number of detections (objects) to process.
      * @param dimensions The number of values per detection (e.g., 4 for bounding box + n for class scores).
      * @param class_ids A reference to a vector that will store the class IDs of detected objects.
      * @param confidences A reference to a vector that will store the confidence scores for each detection.
      * @param boxes A reference to a vector that will store the bounding boxes for each detection.
      * @param image The input image used for the detection (used to scale the bounding boxes appropriately).
      */
    void processDetections
    (
        float* data, 
        int rows, 
        int dimensions,
        std::vector<int>& class_ids,
        std::vector<float>& confidences,
        std::vector<cv::Rect>& boxes, 
        const cv::Mat& image
    ) const;


    /**
      * Draws the detection results (bounding boxes and class labels) on the input image.
      *
      * @param image The image on which the detection results will be drawn. The image will be modified in place.
      * @param class_ids A vector containing the class IDs for each detection.
      * @param confidences A vector containing the confidence scores for each detection.
      * @param boxes A vector containing the bounding boxes for each detection.
      * @param nms_result A vector containing the indices of the detections to keep after applying Non-Maximum Suppression.
      *                   This is used to filter out redundant or overlapping boxes.
      */
    void drawResults
    (
        const cv::Mat& image,
        const std::vector<int>& class_ids,
        const std::vector<float>& confidences,
        const std::vector<cv::Rect>& boxes,
        const std::vector<int>& nms_result
    ) const;

public:
    /**
     * Constructor for ObjectDetector class.
     * @param net The pre-trained network for object detection (e.g., YOLO).
     * @param class_list List of class names for detected objects.
     * @param image_shape Input image size for detection (default 640x640).
     * @param nms_threshold Threshold for Non-Maximum Suppression (default 0.5).
     * @param score_threshold Threshold for object detection confidence (default 0.5).
     */
    ObjectDetector(
        std::shared_ptr<cv::dnn::Net> net,
        std::shared_ptr<std::vector<std::string>> class_list,
        cv::Size image_shape = cv::Size(640, 640),
        float nms_threshold = 0.5f,
        float score_threshold = 0.5f
    )
        : net(net),
        class_list(class_list),
        score_threshold(score_threshold),
        nms_threshold(nms_threshold),
        image_shape(image_shape)
    {
    }

    /**
     * Perform object detection on the input image.
     * @param image The input image for object detection.
     */
    void Detect(const cv::Mat& image) const;

    /**
     * Set the detection thresholds.
     * @param score_threshold Confidence threshold for detection (default 0.5).
     * @param nms_threshold Threshold for Non-Maximum Suppression (default 0.5).
     */
    void SetThresholds(float score_threshold, float nms_threshold)
    {
        this->score_threshold = score_threshold;
        this->nms_threshold = nms_threshold;
    }

    /**
     * Get the list of class names for the detected objects.
     * @return A reference to the class list.
     */
    std::shared_ptr<std::vector<std::string>> GetClassList() const
    {
        return class_list;
    }

    /**
     * Get the current image shape for detection.
     * @return The current image shape (width, height).
     */
    cv::Size GetImageShape() const
    {
        return image_shape;
    }
};
