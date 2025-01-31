
// Copyright (c) 2025+ Vicen-te
// This code is released under the MIT License.

// Header
#include "ObjectDetector.hpp"

// OpenCV
#include <opencv2/imgproc.hpp>

void ObjectDetector::processDetections(float* data, int rows, int dimensions, std::vector<int>& class_ids, std::vector<float>& confidences, std::vector<cv::Rect>& boxes, const cv::Mat& image) const
{
    // Iterate over each detected object and extract the information
    for (int i = 0; i < rows; ++i)
    {
        // The first 4 values are: x, y, width, height, which define the bounding box position and size
        float* classes_scores = data + 4;  //< Skip the first four values (x, y, width, height)
        cv::Mat scores(1, 80, CV_32FC1, classes_scores);  //< Scores for each class

        // Find the class with the maximum score
        cv::Point class_id;
        double maxClassScore;
        minMaxLoc(scores, nullptr, &maxClassScore, nullptr, &class_id);

        // If the score is above the threshold, save the detection
        if (maxClassScore > score_threshold)
        {
            confidences.push_back(static_cast<float>(maxClassScore)); //< Confidence score
            class_ids.push_back(class_id.x);  //< Detected class ID
            boxes.emplace_back(
                static_cast<int>(data[0] * image.cols - data[2] * image.cols / 2),  //< Left = x*cols - w*cols
                static_cast<int>(data[1] * image.rows - data[3] * image.rows / 2),  //< Top  = y*rows - y*rows 
                static_cast<int>(data[2] * image.cols),  //< Width  = w*cols
                static_cast<int>(data[3] * image.rows)   //< Height = h*rows
            );
        }
        data += dimensions;  //< Move to the next detection
    }
}

void ObjectDetector::drawResults(const cv::Mat& image, const std::vector<int>& class_ids, const std::vector<float>& confidences, const std::vector<cv::Rect>& boxes, const std::vector<int>& nms_result) const
{
    // Draw bounding boxes and labels on the image
    for (int idx : nms_result)
    {
        // Draw the bounding box
        cv::rectangle(image, boxes[idx], cv::Scalar(0, 255, 255), 2);

        // Draw the label with confidence score
        cv::putText(image, std::to_string(int(confidences[idx] * 100)) + "% " + (*class_list)[class_ids[idx]],
            cv::Point(boxes[idx].x, boxes[idx].y - 5), cv::FONT_HERSHEY_SIMPLEX, 0.5f,
            cv::Scalar(0, 255, 255), 2);
    }
}

void ObjectDetector::Detect(const cv::Mat& image) const
{
    // Convert the image into a blob suitable for input to the neural network
    cv::Mat blob;
    cv::dnn::blobFromImage(image, blob, 1.0 / 255.0, image_shape, cv::Scalar(), true, false);
    net->setInput(blob);

    // Perform a forward pass through the network to get the output
    std::vector<cv::Mat> outputs;
    net->forward(outputs, net->getUnconnectedOutLayersNames());

    int rows = outputs[0].size[2];  //< Number of rows in the output
    int dimensions = outputs[0].size[1];  //< Number of dimensions for each detection

    // Reshape the output tensor for further processing
    outputs[0] = outputs[0].reshape(1, dimensions);
    cv::transpose(outputs[0], outputs[0]);  //< Transpose for correct formatting

    float* data = reinterpret_cast<float*>(outputs[0].data);

    // Vectors to store detection information
    std::vector<int> class_ids;
    std::vector<float> confidences;
    std::vector<cv::Rect> boxes;

    // Preallocate vectors for efficiency
    class_ids.reserve(rows);
    confidences.reserve(rows);
    boxes.reserve(rows);

    // Process the detections
    processDetections(data, rows, dimensions, class_ids, confidences, boxes, image);

    // Apply Non-Maximum Suppression to remove redundant boxes
    std::vector<int> nms_result;
    cv::dnn::NMSBoxes(boxes, confidences, score_threshold, nms_threshold, nms_result);

    // Draw the results on the image
    drawResults(image, class_ids, confidences, boxes, nms_result);
}