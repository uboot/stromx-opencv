# -*- coding: utf-8 -*-
"""
Created on Mon Apr  1 18:19:38 2013

@author: matz
"""

import sys

import cvtype
import datatype
import document
import generator
import package
import test

# default test data
DT = test.Default()

# generatePattern
dcl = document.Document()
dclIncludes = ["<opencv2/core/core.hpp>"]
dcl.text(
"""
void generatePattern(const cv::Size & size, const float squareSize, cv::Mat & output);
""")
dtnIncludes = []
dtn = document.Document()              
dtn.text(
"""
void generatePattern(const cv::Size & size, const float squareSize, cv::Mat & output)
{
    output = cv::Mat(size.width * size.height, 1, CV_32FC3);
    
    for (int j = 0; j < size.height; ++j)
    {
        for (int i = 0; i < size.width; ++i)
        {
            output.at<cv::Point3f>(i + j * size.width) = 
                cv::Point3f((size.width - i) * squareSize,
                            j * squareSize, 0);
        }
    }
}
""")
generatePatternWrapper = package.Function(dcl, dclIncludes, dtn, dtnIncludes)

# calibrateCamera
objectPoints = package.Argument(
    "objectPoints", "Object points", cvtype.VectorOfMat(),
    datatype.List(datatype.Float32Matrix()),
    visualization = datatype.Visualization.POINT
)
imagePoints = package.Argument(
    "imagePoints", "Image points", cvtype.VectorOfMat(),
    datatype.List(datatype.Float32Matrix()),
    visualization = datatype.Visualization.POINT
)
imageSizeX = package.NumericParameter(
    "imageSizeX", "Sensor size X", cvtype.Int(), datatype.UInt32(), default = 640,
    minValue = 1
)
imageSizeY = package.NumericParameter(
    "imageSizeY", "Sensor size Y", cvtype.Int(), datatype.UInt32(), default = 480,
    minValue = 1
)
imageSize = package.Size(imageSizeX, imageSizeY)
cameraMatrix = package.MatrixArgument(
    "cameraMatrix", "Camera matrix", cvtype.Mat(), datatype.Float64Matrix(),
    rows = 3, cols = 3
)
distCoeffs = package.MatrixArgument(
    "distCoeffs", "Distortion coefficients", cvtype.Mat(), 
    datatype.Float64Matrix(), rows = 1, cols = 5
)
allocateRVecs = document.Document(
"""
std::vector<cv::Mat> rvecs(objectPointsCastedData->content().size());
std::fill(rvecs.begin(), rvecs.end(), cv::Mat());
"""
)
allocateTVecs = document.Document(
"""
std::vector<cv::Mat> tvecs(objectPointsCastedData->content().size());
std::fill(tvecs.begin(), tvecs.end(), cv::Mat());
"""
)
rvecs = package.Constant("rvecs", initIn = allocateRVecs);
tvecs = package.Constant("tvecs", initIn = allocateTVecs);
listSizeCheck = document.Document(
"""
if (objectPointsCastedData->content().size() != imagePointsCastedData->content().size())
{
    throw runtime::InputError(INPUT_OBJECT_POINTS, *this, "Object and image point lists must have the same size.");
}
""")

chess_corners_files = (
  test.MatrixFile("chess_corners_1.npy"), # 32-bit float 35x2
  test.MatrixFile("chess_corners_2.npy"),
  test.MatrixFile("chess_corners_3.npy"),
  test.MatrixFile("chess_corners_4.npy"),
  test.MatrixFile("chess_corners_5.npy"),
  test.MatrixFile("chess_corners_6.npy"),
  test.MatrixFile("chess_corners_7.npy")
)
chess_corners_3d_files = (
  test.MatrixFile("chess_corners_3d.npy"), # 32-bit float 35x3
) * 7
chess_corners = test.List(*chess_corners_files)
chess_corners_3d = test.List(*chess_corners_3d_files)

allocate = package.Option(
    "allocate", "Allocate",
    [package.Input(objectPoints), package.Input(imagePoints), imageSize,
     package.Allocation(cameraMatrix), package.Allocation(distCoeffs), rvecs,
     tvecs],
    inputCheck = listSizeCheck,
    tests = [
        [chess_corners_3d, chess_corners, (320, 240), DT, DT, DT, DT]
    ]
)
calibrateCamera = package.Method(
    "calibrateCamera", options = [allocate]
)

# stereoCalibrate
imagePoints1 = package.Argument(
    "imagePoints1", "Image points camera 1", cvtype.VectorOfMat(),
    datatype.List(datatype.Float32Matrix()),
    visualization = datatype.Visualization.POINT
)
imagePoints2 = package.Argument(
    "imagePoints2", "Image points 2", cvtype.VectorOfMat(),
    datatype.List(datatype.Float32Matrix()),
    visualization = datatype.Visualization.POINT
)
cameraMatrix1 = package.MatrixParameter(
    "cameraMatrix1", "Camera matrix 1", datatype.FloatMatrix(),
    default = "cvsupport::Matrix::zeros(3, 3, runtime::Matrix::FLOAT_32)",
    rows = 3, cols = 3
)
distCoeffs1 = package.MatrixParameter(
    "distCoeffs1", "Distortion coefficients 1", datatype.FloatMatrix(),
    default = "cvsupport::Matrix::zeros(1, 5, runtime::Matrix::FLOAT_32)",
    rows = 1, cols = 5,
)
cameraMatrix2 = package.MatrixParameter(
    "cameraMatrix2", "Camera matrix 2", datatype.FloatMatrix(),
    default = "cvsupport::Matrix::zeros(3, 3, runtime::Matrix::FLOAT_32)",
    rows = 3, cols = 3
)
distCoeffs2 = package.MatrixParameter(
    "distCoeffs2", "Distortion coefficients 2", datatype.FloatMatrix(),
    default = "cvsupport::Matrix::zeros(1, 5, runtime::Matrix::FLOAT_32)",
    rows = 1, cols = 5,
)
cameraMatrix1Arg = package.MatrixArgument(
    "cameraMatrix1Arg", "Camera matrix 1", cvtype.Mat(), datatype.Float64Matrix(),
    rows = 3, cols = 3
)
distCoeffs1Arg = package.MatrixArgument(
    "distCoeffs1Arg", "Distortion coefficients 1", cvtype.Mat(), 
    datatype.Float64Matrix(), rows = 1, cols = 5
)
cameraMatrix2Arg = package.MatrixArgument(
    "cameraMatrix2Arg", "Camera matrix 2", cvtype.Mat(), datatype.Float64Matrix(),
    rows = 3, cols = 3
)
distCoeffs2Arg = package.MatrixArgument(
    "distCoeffs2Arg", "Distortion coefficients 2", cvtype.Mat(), 
    datatype.Float64Matrix(), rows = 1, cols = 5
)
rvec = package.MatrixArgument(
    "rvec", "Rotation", cvtype.Mat(channels = 2), datatype.Float64Matrix(),
    rows = 3, cols = 1
)
tvec = package.MatrixArgument(
    "tvec", "Translation", cvtype.Mat(channels = 2), datatype.Float64Matrix(),
    rows = 3, cols = 1
)
listSizeCheck = document.Document(
"""
if (objectPointsCastedData->content().size() != imagePoints1CastedData->content().size())
{
    throw runtime::InputError(INPUT_OBJECT_POINTS, *this, "Object and image point (1) lists must have the same size.");
}
if (objectPointsCastedData->content().size() != imagePoints2CastedData->content().size())
{
    throw runtime::InputError(INPUT_OBJECT_POINTS, *this, "Object and image point (2) lists must have the same size.");
}
""")

chess_corners_files = (
  test.MatrixFile("chess_corners_1.npy"), # 32-bit float 35x2
  test.MatrixFile("chess_corners_2.npy"),
  test.MatrixFile("chess_corners_3.npy"),
  test.MatrixFile("chess_corners_4.npy"),
  test.MatrixFile("chess_corners_5.npy"),
  test.MatrixFile("chess_corners_6.npy"),
  test.MatrixFile("chess_corners_7.npy")
)
chess_corners_3d_files = (
  test.MatrixFile("chess_corners_3d.npy"), # 32-bit float 35x3
) * 7
chess_corners = test.List(*chess_corners_files)
chess_corners_3d = test.List(*chess_corners_3d_files)
camera_matrix = test.MatrixFile("camera_matrix_32f.npy")
dist_coeffs = test.MatrixFile("dist_coeffs_32f.npy")

intrinsics = package.Option(
    "intrinsics", "Extrinsics and intrinsics",
    [package.Input(objectPoints), package.Input(imagePoints1), 
     package.Input(imagePoints2), package.Allocation(cameraMatrix1Arg), 
     package.Allocation(distCoeffs1Arg), package.Allocation(cameraMatrix2Arg),
     package.Allocation(distCoeffs2Arg), imageSize, package.Allocation(rvec),
     package.Allocation(tvec),  package.Constant('cv::Mat(3, 3, CV_64F)'),
     package.Constant("cv::Mat(3, 3, CV_64F)")],
    inputCheck = listSizeCheck,
    tests = [
        [chess_corners_3d, chess_corners, chess_corners, DT, DT, DT, DT, 
         (320, 240), DT, DT, DT, DT]
    ]
)
extrinsics = package.Option(
    "extrinsics", "Only extrinsics",
    [package.Input(objectPoints), package.Input(imagePoints1), 
     package.Input(imagePoints2), cameraMatrix1, distCoeffs1, 
     cameraMatrix2, distCoeffs2, imageSize, package.Allocation(rvec),
     package.Allocation(tvec),  package.Constant('cv::Mat(3, 3, CV_64F)'),
     package.Constant("cv::Mat(3, 3, CV_64F)")],
    inputCheck = listSizeCheck,
    tests = [
        [chess_corners_3d, chess_corners, chess_corners, camera_matrix,
         dist_coeffs, camera_matrix, dist_coeffs, (320, 240), DT, DT,
         DT, DT]
    ]
)
stereoCalibrate = package.Method(
    "stereoCalibrate", options = [extrinsics, intrinsics]
)

# findChessboardCorners
image = package.Argument(
    "image", "Image", cvtype.Mat(), datatype.Image()
)
sizex = package.NumericParameter(
    "patternSizeX", "Pattern size X", cvtype.Int(), datatype.UInt32(), default = 7,
    minValue = 1
)
sizey = package.NumericParameter(
    "patternSizeY", "Pattern size Y", cvtype.Int(), datatype.UInt32(), default = 5,
    minValue = 1
)
size = package.Size(sizex, sizey)
corners = package.MatrixArgument(
    "corners", "Corners", cvtype.Mat(channels = 2), datatype.Float32Matrix(),
    cols = 2, visualization = datatype.Visualization.POLYLINE
)
chessboard_bw = test.ImageFile("chess.png", grayscale = True)
chessboard_color = test.ImageFile("chess.png")
allocate = package.Option(
    "allocate", "Allocate",
    [package.Input(image), size, package.Allocation(corners)],
    tests = [
        [chessboard_bw, DT, DT, DT],
        [chessboard_color, DT, DT, DT]
    ]
)
findChessboardCorners = package.Method(
    "findChessboardCorners", options = [allocate]
)

# generatePattern
sizex = package.NumericParameter(
    "patternSizeX", "Pattern size X", cvtype.Int(), datatype.UInt32(), default = 7,
    minValue = 1
)
sizey = package.NumericParameter(
    "patternSizeY", "Pattern size Y", cvtype.Int(), datatype.UInt32(), default = 5,
    minValue = 1
)
size = package.Size(sizex, sizey)
squareSize = package.NumericParameter(
    "squareSize", "Square size", cvtype.Float32(), datatype.Float32(), default = 10,
    minValue = 0
)
corners = package.MatrixArgument(
    "corners", "Corners", cvtype.Mat(channels = 3), datatype.Float32Matrix(),
    cols = 3, visualization = datatype.Visualization.POLYLINE
)
allocate = package.Option(
    "allocate", "Allocate",
    [size, squareSize, package.Allocation(corners)],
    tests = [
        [DT, DT, DT, DT]
    ]
)
generatePattern = package.Method(
    "generatePattern", namespace = "", options = [allocate]
)

# solvePnP
objectPoints = package.MatrixArgument(
    "objectPoints", "Object points", cvtype.Mat(channels = 3),
    datatype.Float32Matrix(), cols = 3, 
    visualization = datatype.Visualization.POINT
)
imagePoints = package.MatrixArgument(
    "imagePoints", "Image points", cvtype.Mat(channels = 2),
    datatype.Float32Matrix(), cols = 2, 
    visualization = datatype.Visualization.POINT
)
pointSizeCheck = document.Document(
"""
if (objectPointsCastedData->rows() != imagePointsCastedData->rows())
{
    throw runtime::InputError(INPUT_OBJECT_POINTS, *this, "Object and image points must have the same number of rows.");
}
""")
cameraMatrix = package.MatrixParameter(
    "cameraMatrix", "Camera matrix", datatype.FloatMatrix(),
    default = "cvsupport::Matrix::zeros(3, 3, runtime::Matrix::FLOAT_32)",
    rows = 3, cols = 3
)
distCoeffs = package.MatrixParameter(
    "distCoeffs", "Distortion coefficients", datatype.FloatMatrix(),
    default = "cvsupport::Matrix::zeros(1, 5, runtime::Matrix::FLOAT_32)",
    rows = 1, cols = 5,
)
chess_corners = test.MatrixFile("chess_corners_1.npy")
chess_corners_3d = test.MatrixFile("chess_corners_3d.npy")
camera_matrix_64f = test.MatrixFile("camera_matrix_64f.npy")
dist_coeffs_64f = test.MatrixFile("dist_coeffs_64f.npy")
camera_matrix_32f = test.MatrixFile("camera_matrix_32f.npy")
dist_coeffs_32f = test.MatrixFile("dist_coeffs_32f.npy")

allocate = package.Option(
    "allocate", "Allocate",
    [package.Input(objectPoints), package.Input(imagePoints), cameraMatrix,
     distCoeffs, package.Allocation(rvec), package.Allocation(tvec)],
    inputCheck = pointSizeCheck,
    tests = [
        [chess_corners_3d, chess_corners, camera_matrix_64f, dist_coeffs_32f, DT, DT],
        [chess_corners_3d, chess_corners, camera_matrix_32f, dist_coeffs_64f, DT, DT]
    ]
)
solvePnP = package.Method(
    "solvePnP", options = [allocate]
)

calib3d = package.Package(
    "cvcalib3d", 0, 1, 0,
    methods = [
        calibrateCamera,
        stereoCalibrate,
        findChessboardCorners,
        generatePattern,
        solvePnP
    ],
    functions = [
        generatePatternWrapper,
    ],
    testFiles = [
        "chess.png", # 24-bit color
        "chess_corners_1.npy", # 32-bit float
        "chess_corners_2.npy",
        "chess_corners_3.npy",
        "chess_corners_4.npy",
        "chess_corners_5.npy",
        "chess_corners_6.npy",
        "chess_corners_7.npy",
        "chess_corners_3d.npy",
        "camera_matrix_64f.npy",
        "dist_coeffs_64f.npy",
        "camera_matrix_32f.npy",
        "dist_coeffs_32f.npy"
    ]
)

package = calib3d

if __name__ == '__main__':
    if len(sys.argv) > 1:
        for arg in sys.argv[1:]:
            generator.generateMethodFiles(package, globals()[arg])
    else:
        generator.generatePackageFiles(package) 
