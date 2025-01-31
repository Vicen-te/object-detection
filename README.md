# Object Detection Project with YOLO11 and OpenCV

This project demonstrates object detection using the **YOLO11** model, with the **OpenCV** library for processing and handling images and videos in real-time.

## Requirements

- **YOLO11 Model**: This project utilizes the **YOLO11x** model for enhanced accuracy.
- **OpenCV Library**: The **OpenCV** library is required for image processing.

## Converting YOLO11x.pt to ONNX

To use the **YOLO11x** model in this project, you need to convert it to **ONNX format**. This requires **Python 3.9.13** and the \`ultralytics\` library.  Use the following script to perform the conversion:

```python
from ultralytics import YOLO
model = YOLO("yolo11x.pt")
model.export(format="onnx")
```

## Licenses

This project uses the following software under the licenses mentioned:

### YOLO11
The **YOLO11** model is used under the **AGPL-3.0 License**. The code and pretrained models are provided by [Ultralytics](https://github.com/ultralytics/ultralytics). You can find the full license details [here](https://www.gnu.org/licenses/agpl-3.0.html).

### OpenCV
**OpenCV** is used under the **Apache License 2.0**. You can find the full license details [here](https://opencv.org/license/). The official OpenCV repository can be found [here](https://github.com/opencv/opencv).
