#include <opencv2/opencv.hpp>
#include <iostream>
#include "frontalface.h" //Header file for the Haar Cascade XML data

/**
 * @brief Loads a Haar Cascade classifier from memory.
 *
 * @param classifier The cv::CascadeClassifier object to be initialized.
 * @param buffer Pointer to the buffer containing the XML data of the Haar Cascade.
 * @param bufferSize Size of the buffer.
 * @return true if the classifier was successfully loaded, false otherwise.
 */
bool loadCascadeFromMemory(cv::CascadeClassifier &classifier, const unsigned char *buffer, size_t bufferSize)
{
    // Create a cv::FileStorage object from the buffer
    cv::FileStorage fs(std::string(reinterpret_cast<const char *>(buffer), bufferSize), cv::FileStorage::READ | cv::FileStorage::MEMORY);

    // Check if the FileStorage was opened successfully and attempt to read the classifier data
    return fs.isOpened() && classifier.read(fs.getFirstTopLevelNode());
}

int main()
{
    // Load the pre-trained Haar Cascade classifier for face detection from memory
    cv::CascadeClassifier faceCascade;
    if (!loadCascadeFromMemory(faceCascade, frontalface_xml, frontalface_xml_len))
    {
        std::cerr << "Error loading Haar Cascade from embedded data" << std::endl;
        return -1;
    }

    // Open a connection to the default webcam (camera index 0)
    cv::VideoCapture cap(0);
    if (!cap.isOpened())
    {
        std::cerr << "Error opening webcam" << std::endl;
        return -1;
    }

    cv::Mat frame;
    while (true)
    {
        // Capture a frame from the webcam
        cap >> frame;
        if (frame.empty())
        {
            std::cerr << "Error capturing frame" << std::endl;
            break;
        }

        // Convert the captured frame to grayscale for face detection
        cv::Mat gray;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        // Detect faces in the grayscale image
        std::vector<cv::Rect> faces;
        faceCascade.detectMultiScale(gray, faces);

        // Draw rectangles around detected faces
        for (const auto &face : faces)
        {
            cv::rectangle(frame, face, cv::Scalar(255, 0, 0), 2); // Red rectangle
        }

        // Display the frame with detected faces
        cv::imshow("Live Face Detection", frame);

        // Exit the loop if 'q' or 'ESC' key is pressed
        char key = (char)cv::waitKey(30);
        if (key == 'q' || key == 27) // 'ESC' key code is 27
        {
            break;
        }
    }

    // Release resources and close all OpenCV windows
    cap.release();
    cv::destroyAllWindows();

    return 0;
}
