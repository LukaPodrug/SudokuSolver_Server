#include <iostream>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include <tesseract/baseapi.h>

using namespace std;
using namespace cv;
using namespace tesseract;

Mat imagePreproccessing(Mat image, int thresholdMin);
tuple<bool, Mat> findGrid(Mat image);
Mat fourPointPerspective(Mat image, vector<Point> points);
vector<Point2f> orderPointsOfQuadrilateral(vector<Point> points);
vector<tuple<Mat, tuple<int, int>>> findCells(Mat image);
vector<tuple<int, tuple<int, int>>> findCellValues(vector<tuple<Mat, tuple<int, int>>> cells);
vector<tuple<int, tuple<int, int>>> findCellPositions(vector<tuple<int, tuple<int, int>>> cells);

int main(int argc, char** argv) {
    //load image from file
    string imageName, imagePath;
    Mat image;

    imageName = argv[1];

    imagePath = "./images/" + imageName;

    image = imread(imagePath);

    //check if image exists
    if (image.empty()) { 
        cout << "Image not found" << endl;
        return -1; 
    }

    //vector of found grids
    vector<tuple<String, int>> gridValues;

    for(int thresholdMin = 80; thresholdMin <= 170; thresholdMin++) {
        //preproccessing image using threshold variable
        Mat proccessedImage;
        bool valid;

        proccessedImage = imagePreproccessing(image, thresholdMin);

        //finding sudoku grid in image
        tie(valid, proccessedImage) = findGrid(proccessedImage);

        if(valid == true) {
            //get cells from grid
            vector<tuple<Mat, tuple<int, int>>> cells;

            cells = findCells(proccessedImage);

            //get cell values and positions
            vector<tuple<int, tuple<int, int>>> cellValuesPositions;

            cellValuesPositions = findCellValues(cells);
            cellValuesPositions = findCellPositions(cellValuesPositions);

            //print sudoku grid for server to read
            string gridString = "";

            for(int index = 0; index < 81; index++) {
                gridString = gridString + to_string(get<0>(cellValuesPositions[index]));
            }

            //make grid tuple to push in grid vector
            tuple<String, int> gridTuple;
            int gridOccurance = 1;

            for(int index = 0; index < gridValues.size(); index++) {
                if(get<0>(gridValues[index]) == gridString) {
                    gridOccurance = get<1>(gridValues[index]);
                    gridValues.pop_back();
                    break;
                }
            }

            gridTuple = make_tuple(gridString, gridOccurance);

            gridValues.push_back(gridTuple);
        }
    }

    if(gridValues.size() == 0) {
        cout << "Grid not found" << endl;
        return -1;
    }

    //occurance record grid index
    int recordIndex = gridValues.size() - 1;

    for(int index = gridValues.size() - 2; index >= 0; index--) {
        if(get<1>(gridValues[index]) > get<1>(gridValues[recordIndex])) {
            recordIndex = index;
        }
    }

    cout << get<0>(gridValues[recordIndex]) << endl;

    return 0;
}

vector<tuple<int, tuple<int, int>>> findCellPositions(vector<tuple<int, tuple<int, int>>> cells) {
    //sorting by rows
    for(int index1 = 0; index1 < 81 - 1; index1++) {
        for(int index2 = index1 + 1; index2 < 81; index2++) {
            if(get<1>(get<1>(cells[index1])) > get<1>(get<1>(cells[index2]))) {
                swap(cells[index1], cells[index2]);
            }
        }
    }

    //sorting by columns
    for(int index1 = 0; index1 < 9; index1++) {
        for(int index2 = index1 * 9; index2 < (index1 + 1) * 9 - 1; index2++) {
            for(int index3 = index2 + 1; index3 < (index1 + 1) * 9; index3++) {
                if(get<0>(get<1>(cells[index2])) > get<0>(get<1>(cells[index3]))) {
                    swap(cells[index2], cells[index3]);
                }
            }
        }
    }

    return cells;
}

vector<tuple<int, tuple<int, int>>> findCellValues(vector<tuple<Mat, tuple<int, int>>> cells) {
    //ocr initialization and configuration
    TessBaseAPI *ocr;
    char *cellText;

    ocr = new TessBaseAPI();

    ocr->Init(NULL, "eng", OEM_LSTM_ONLY);
    ocr->SetPageSegMode(PSM_SINGLE_CHAR);
    ocr->SetVariable("tessedit_char_whitelist","123456789");

    //vector to return
    vector<tuple<int, tuple<int, int>>> cellValues;

    //recognize character in each cell and push it to vector
    for(tuple<Mat, tuple<int, int>> cell : cells) {
        ocr->SetImage(get<0>(cell).data, get<0>(cell).cols, get<0>(cell).rows, 1, get<0>(cell).cols);

        cellText = ocr->GetUTF8Text();

        cellValues.push_back(make_tuple(atoi(cellText), get<1>(cell)));
    }

    //destroy ocr to free memory
    ocr->End();

    return cellValues;
}

vector<tuple<Mat, tuple<int, int>>> findCells(Mat image) {
    //calculating image area
    int imageArea;

    imageArea = image.size[0] * image.size[1];

    //find cells contours
    vector<vector<Point>> contours;

    findContours(image, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);

    //empty cells vector
    vector<tuple<Mat, tuple<int, int>>> cells;

    for(vector<Point> contour : contours) {
        //calculating countur area
        double area;

        area = contourArea(contour);

        //approximate contour to check if it is quadrilateral
        double perimeter;
        vector<Point> approximate;
        
        perimeter = arcLength(contour, true);
        approxPolyDP(contour, approximate, 0.017 * perimeter, true);

        //rejecting too small and too big contours and contours that are not quadrilaterals
        if(area / imageArea > 0.0001 && area / imageArea < 0.02 && approximate.size() == 4) {
            //determening cell coordinates
            int minX = image.size[0], maxX = 0, minY = image.size[1], maxY = 0;

            for(int index = 0; index < contour.size(); index++) {
                if(contour[index].x < minX) {
                    minX = contour[index].x;
                }

                if(contour[index].x > maxX) {
                    maxX = contour[index].x;
                }

                if(contour[index].y < minY) {
                    minY = contour[index].y;
                }

                if(contour[index].y > maxY) {
                    maxY = contour[index].y;
                }
            }

            //crop cell from image 
            Mat cell;
            
            cell = image(Rect(minX, minY, maxX - minX, maxY - minY));

            //resize cell image
            resize(cell, cell, Size(28, 28));

            //calculate centroid of cell
            Moments M;
            int centroidX, centroidY;
            tuple<int, int> centroid;

            M = moments(contour);
            centroidX = int(M.m10 / M.m00);
            centroidY = int(M.m01 / M.m00);

            centroid = make_tuple(centroidX, centroidY);

            //make cell tuple to push in cells vector
            tuple<Mat, tuple<int, int>> cellTuple;

            cellTuple = make_tuple(cell, centroid);

            cells.push_back(cellTuple);
        }
    }

    return cells;
}

vector<Point2f> orderPointsOfQuadrilateral(vector<Point> points) {
    //calculating sum and difference between x and y coordinate
    vector<Point2f> orderedPoints;
    int sum[4], difference[4];

    for(int index = 0; index < 4; index++) {
        sum[index] = points[index].x + points[index].y;
        difference[index] = points[index].x - points[index].y;
    }

    //sorting sum and difference arrays ascending
    sort(sum, sum + 4);
    sort(difference, difference + 4);

    //assing points in order: top-left, top-right, bottom-right, bottom-left
    for(int index = 0; index < 4; index++) {
        switch(index) {
            case 0:
                //top-left point has lowest sum of coordinates
                for(int index2 = 0; index2 < 4; index2++) {
                    if(points[index2].x + points[index2].y == sum[0]) {
                        orderedPoints.push_back(Point2f(points[index2].x, points[index2].y));
                    }
                }

                break;

            case 1:
                //top-right point has greatest difference of coordinates
                for(int index2 = 0; index2 < 4; index2++) {
                    if(points[index2].x - points[index2].y == difference[3]) {
                        orderedPoints.push_back(Point2f(points[index2].x, points[index2].y));
                    }
                }

                break;

            case 2:
                //bottom-right point has greatest sum of coordinates
                for(int index2 = 0; index2 < 4; index2++) {
                    if(points[index2].x + points[index2].y == sum[3]) {
                        orderedPoints.push_back(Point2f(points[index2].x, points[index2].y));
                    }
                }

                break;

            case 3: 
                //bottom-left point has lowest difference of coordinates
                for(int index2 = 0; index2 < 4; index2++) {
                    if(points[index2].x - points[index2].y == difference[0]) {
                        orderedPoints.push_back(Point2f(points[index2].x, points[index2].y));
                    }
                }

                break;

            default: 
                break;
        }
    }

    return orderedPoints;
}


Mat fourPointPerspective(Mat image, vector<Point> points) {
    //order points of quadrilateral
    vector<Point2f> rectangle;

    rectangle = orderPointsOfQuadrilateral(points);

    //return not valid if rectangle is too small
    if(rectangle.size() != 4) {
        return image;
    }

    //computing new image width
    double widthTop, widthBottom;
    double widthMax;

    widthTop = sqrt(pow(rectangle[0].x - rectangle[1].x, 2) + pow(rectangle[0].y - rectangle[1].y, 2));
    widthBottom = sqrt(pow(rectangle[3].x - rectangle[2].x, 2) + pow(rectangle[3].y - rectangle[2].y, 2));
    widthMax = max(widthTop, widthBottom);

    //computing new image height
    double heightLeft, heightRight;
    double heightMax;

    heightLeft = sqrt(pow(rectangle[0].x - rectangle[3].x, 2) + pow(rectangle[0].y - rectangle[3].y, 2));
    heightRight = sqrt(pow(rectangle[1].x - rectangle[2].x, 2) + pow(rectangle[1].y - rectangle[2].y, 2));
    heightMax = max(heightLeft, heightRight);

    //obtaining bird-eye view of grid
    vector<Point2f> perspectiveTransformDestination;

    perspectiveTransformDestination.push_back(Point2f(10, 10));
    perspectiveTransformDestination.push_back(Point2f(widthMax - 10 , 10));
    perspectiveTransformDestination.push_back(Point2f(widthMax - 10, heightMax - 10));
    perspectiveTransformDestination.push_back(Point2f(10, heightMax - 10));

    Mat M, warped;

    M = getPerspectiveTransform(rectangle, perspectiveTransformDestination);
    warpPerspective(image, warped, M, Size(widthMax + 10, heightMax + 10));

    return warped;
}

tuple<bool, Mat> findGrid(Mat image) {
    //finding grid contours in image
    vector<vector<Point>> contours;

    findContours(image, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);

    for(vector<Point> contour : contours) {
        //approximate contour to check if it is quadrilateral
        double perimeter;
        vector<Point> approximate;
        
        perimeter = arcLength(contour, true);
        approxPolyDP(contour, approximate, 0.01 * perimeter, true);

        //check if contour is qadrilateral
        if(approximate.size() == 4) {
            //four point transform
            Mat warped;

            warped = fourPointPerspective(image, approximate);

            //find cells in grid
            vector<tuple<Mat, tuple<int, int>>> cells;

            cells = findCells(warped);
            if(cells.size() == 81) {
                return make_tuple(true, warped);
            }
        }
    }

    return make_tuple(false, image);
}

Mat imagePreproccessing(Mat image, int thresholdMin) {
    //calculating image ratio
    double ratio = (double)image.size[0] / (double)image.size[1];

    //resizing image
    resize(image, image, Size(1100, 1100 * ratio));

    //blurring image
    GaussianBlur(image, image, Size(3, 3), 0);

    //grayscaling image
    cvtColor(image, image, COLOR_BGR2GRAY);

    //converting image to black-white
    threshold(image, image, thresholdMin, 255, THRESH_BINARY);

    //adaptive threshold
    adaptiveThreshold(image, image, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 11, 2);

    //add padding to image
    copyMakeBorder(image, image, 50, 50, 50, 50, BORDER_CONSTANT, 255);

    return image;
}