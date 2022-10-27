cmake_minimum_required(VERSION 3.5)

project(qBatchCutROI VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)








#set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
if(MSVC)
    set(CMAKE_DEBUG_POSTFIX "d")
endif()
#link_directories(${CMAKE_BINARY_DIR} )

message( "CMAKE_C_COMPILER = ${CMAKE_C_COMPILER}"  )
message( "CMAKE_C_COMPILER_VERSION = ${CMAKE_C_COMPILER_VERSION}"  )
message( "CMAKE_CXX_PLATFORM_ID = ${CMAKE_CXX_PLATFORM_ID}"  )
message( "CMAKE_CXX_COMPILER_TARGET = ${CMAKE_CXX_COMPILER_TARGET}"  )
message( "CMAKE_CXX_COMPILER_AR = ${CMAKE_CXX_COMPILER_AR}"  )
message( "CMAKE_C_COMPILER_ABI = ${CMAKE_C_COMPILER_ABI}"  )
message( "CMAKE_C_COMPILER_TARGET = ${CMAKE_C_COMPILER_TARGET}"  )
message( "CMAKE_HOST_SYSTEM = ${CMAKE_HOST_SYSTEM}"  )
message( "CMAKE_HOST_SYSTEM_NAME = ${CMAKE_HOST_SYSTEM_NAME}"  )
message( "CMAKE_VS_PLATFORM_NAME = ${CMAKE_VS_PLATFORM_NAME}"  )
message( "CMAKE_VS_PLATFORM_TOOLSET = ${CMAKE_VS_PLATFORM_TOOLSET}"  )
message( "CMAKE_CXX_COMPILER_VERSION = ${CMAKE_CXX_COMPILER_VERSION}"  )
#message(  "CMAKE_CXX_COMPILER_TARGET= ${CMAKE_CXX_COMPILER_TARGET}"   )
message(  "CMAKE_CXX_COMPILER_ABI= ${CMAKE_CXX_COMPILER_ABI}"   )
message(  "CMAKE_CXX_COMPILER_EXTERNAL_TOOLCHAIN= ${CMAKE_CXX_COMPILER_EXTERNAL_TOOLCHAIN}"   )
message(  "CMAKE_CXX_COMPILER_ID= ${CMAKE_CXX_COMPILER_ID}"   )
message(  "CMAKE_CXX_COMPILER_ARCHITECTURE_ID= ${CMAKE_CXX_COMPILER_ARCHITECTURE_ID}"   )
#message(  "CMAKE_HOST_SYSTEM_NAME= ${CMAKE_HOST_SYSTEM_NAME}"   )
message(  "CMAKE_Fortran_FORMAT= ${CMAKE_Fortran_FORMAT}"   )
message(  "CMAKE_Fortran_COMPILER= ${CMAKE_Fortran_COMPILER}"   )
message(  "CMAKE_Fortran_COMPILER_VERSION= ${CMAKE_Fortran_COMPILER_VERSION}"   )
message(  "CMAKE_Fortran_COMPILER_ID= ${CMAKE_Fortran_COMPILER_ID}"   )



# 改变安装路径可以使用下面的语句，Unix: "/usr/local", Windows: "c:/Program Files/${PROJECT_NAME}" 为默认值，所有的DESTINATION均以此目录为根目录
# set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/mymath)
#set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/../${PROJECT_NAME}_${PROJECT_VERSION}_${CMAKE_HOST_SYSTEM}_${CMAKE_CXX_COMPILER_ID}_${CMAKE_CXX_COMPILER_VERSION}_install)
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/../${PROJECT_NAME}_${PROJECT_VERSION}_${CMAKE_CXX_COMPILER_ID}_${CMAKE_CXX_COMPILER_VERSION}_${CMAKE_Fortran_COMPILER_ID}_${CMAKE_Fortran_COMPILER_VERSION}_install)










find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)



MESSAGE(STATUS "platform: ${CMAKE_SYSTEM_NAME}")
if (UNIX AND NOT APPLE)
    MESSAGE(STATUS "unix")
elseif   (APPLE )
    MESSAGE(STATUS "APPLE")
elseif   (WIN32 )
    MESSAGE(STATUS "WIN32")
else()
    MESSAGE(STATUS " other sys  ...  ")
endif()

message( "UNIX  =  ${UNIX}  " )
message( "Android  =  ${Android}  " )

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
#
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
#
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "FreeBSD")
#
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Android")
#
ELSE ()
MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")



if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    # using Clang
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    # using GCC
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
    # using Intel C++
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    # using Visual Studio C++
    ELSE ()
    MESSAGE(STATUS "other compiler : ${CMAKE_CXX_COMPILER_ID}")
endif()


message( "CMAKE_SYSTEM_NAME  =  ${CMAKE_SYSTEM_NAME}  " )
message( "CMAKE_CXX_COMPILER_ID  =  ${CMAKE_CXX_COMPILER_ID}  " )

#set(CMAKE_OSX_ARCHITECTURES  ArmV7a )
message( "TARget:     ${CMAKE_OSX_ARCHITECTURES}  " )
message( "WIN32 =    ${WIN32}  " )
message( "CMAKE_HOST_WIN32 =    ${CMAKE_HOST_WIN32}  " )
message( "CMAKE_HOST_UNIX =    ${CMAKE_HOST_UNIX}  " )
message( "CMAKE_HOST_LINUX =    ${CMAKE_HOST_LINUX}  " )


if(WIN32 )
    message( "compile on win32 sys."  )
    #    D:\win10\cv460Offical\opencv\build\x64\vc14\lib
    #    find_package(OpenCV REQUIRED EXACT 4.5.1 PATHS "D:/win10/Cv451GLVs2015install")
#    set(OpenCV_DIR  "D:/win10/cv460Offical/opencv/build/x64/vc14/lib")
#    find_package(OpenCV REQUIRED EXACT 4.6.0 PATHS "D:/win10/cv460Offical/opencv/build")
    set(OpenCV_DIR   "D:\\win10\\Cv451GLVs2015install\\x64\\vc14\\lib"  )
    find_package(OpenCV REQUIRED EXACT 4.5.1 PATHS "D:\\win10\\Cv451GLVs2015install")
    #    message("--------Proj Src Dir: " ${CMAKE_CURRENT_SOURCE_DIR})
    file(TO_CMAKE_PATH "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v8.0/include" cudaINcPath)
    #    message("-----cudaINcPath:${cudaINcPath}")
    include_directories(   "${cudaINcPath}" )
    file(TO_CMAKE_PATH "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v8.0\\lib\\x64" cudaLibPath)
    #    message("-----cudaLibPath:${cudaLibPath}")
    link_directories(   "${cudaLibPath}" )
    set(OpenCL_LIBRARY  OpenCL)
elseif( CMAKE_HOST_WIN32 )
    message( "compile on windows10 sys."  )
    if( CMAKE_SYSTEM_NAME MATCHES "Windows"  )
        message( "\t target platform is windows." )
        # message( "TARget:  a   ${CMAKE_OSX_ARCHITECTURES}  " )
        set(OpenCV_DIR  "D:/win10/Cv451GLVs2015install/x64/vc14/lib")
        find_package(OpenCV REQUIRED EXACT 4.5.1 PATHS "D:/win10/Cv451GLVs2015install")
    elseif( CMAKE_SYSTEM_NAME MATCHES "Linux"  )
        message( "\t target platform is  Linux ." )
        set(OpenCV_DIR  "/home/kent/bin160407/InstallCv451U160407Simple/lib/cmake/opencv4")
        find_package(OpenCV REQUIRED EXACT 4.5.1 PATHS "/home/kent/bin160407/InstallCv451U160407Simple")
    elseif (CMAKE_SYSTEM_NAME MATCHES "Android")
        message( "\t target platform is  Android ." )
        set(OPencv_root_dir_LK    "D:\\win10\\installCv455Arm64v8aNdk21.3.6528147Release5950x/install")
        set(OpenCV_DIR "${OPencv_root_dir_LK}\\sdk\\native\\jni/${ANDROID_ABI}" )
        set(  OpenCV_INCLUDE_DIRS  "${OPencv_root_dir_LK}\\sdk\\native\\jni/include"  )
        set(  OpenCV_LIBRARY_DIRS  "${OPencv_root_dir_LK}\\sdk\\native\\libs/${ANDROID_ABI}"  )
        set(  OpenCV_LIBS   opencv_calib3d   opencv_core   opencv_dnn
            opencv_features2d
            opencv_flann
            opencv_gapi
            opencv_highgui
            opencv_imgcodecs
            opencv_imgproc
            #            opencv_ml
            #            opencv_objdetect
            #            opencv_photo
            opencv_stitching
            opencv_video
            opencv_videoio
            )
        include_directories(  "${OPencv_root_dir_LK}\\sdk\\native\\jni/include" )
        link_directories(  "${OPencv_root_dir_LK}\\sdk\\native\\libs/${ANDROID_ABI}" )
    endif()
elseif( CMAKE_HOST_UNIX )
    message(STATUS  "compile on UNIX sys."  )
    if( CMAKE_SYSTEM_NAME MATCHES "Linux"  )
        message( "\t target platform is  Linux ." )
        find_package( OpenCV EXACT 4.5.5 REQUIRED PATHS "/home/kent/binUbun18045/installUbun1804Gcc750NonfreeGLCLLIte2")
        find_package(OpenCL 1.2 QUIET)  # -- OpenCL_LIBRARY = /usr/lib/x86_64-linux-gnu/libOpenCL.so
        if(NOT OpenCL_FOUND)
            message(STATUS "OpenCL samples are skipped: OpenCL SDK is required")
            return()
        endif()
    elseif (CMAKE_SYSTEM_NAME MATCHES "Android")
        message( "\t target platform is  Android ." )
        set(OPencv_root_dir_LK  "/home/kent/binUbun18045/installCv455Ubun1804Arm64V8ReleaseShared/install")
        set(OpenCV_DIR "${OPencv_root_dir_LK}\\sdk\\native\\jni/${ANDROID_ABI}" )
        set(  OpenCV_INCLUDE_DIRS  "${OPencv_root_dir_LK}\\sdk\\native\\jni/include"  )
        set(  OpenCV_LIBRARY_DIRS  "${OPencv_root_dir_LK}\\sdk\\native\\libs/${ANDROID_ABI}"  )
        set(  OpenCV_LIBS   opencv_calib3d   opencv_core   opencv_dnn
            opencv_features2d
            opencv_flann
            opencv_gapi
            opencv_highgui
            opencv_imgcodecs
            opencv_imgproc
            #  opencv_ml
            # opencv_objdetect
            # opencv_photo
            opencv_stitching
            opencv_video
            opencv_videoio
            )
        set(  OpenCV_LIBRARIES    ${OpenCV_LIBS} )
        include_directories(  "${OPencv_root_dir_LK}\\sdk\\native\\jni/include" )
        link_directories(  "${OPencv_root_dir_LK}\\sdk\\native\\libs/${ANDROID_ABI}" )
        set(OpenCL_ROOT_DIR  /home/kent/Android/Development/fastcv-android-1-7-1  )
    endif()
elseif( CMAKE_HOST_LINUX )
    message( "compile on LINUX sys."  )
elseif( CMAKE_HOST_APPLE)
    message( "compile on APPLE sys." )
elseif( CMAKE_CUDA_HOST_COMPILER)
    message( "compile on CUDA sys."  )
else()
    message( "compile on other sys." )
endif()
message(STATUS "OpenCL_LIBRARY = ${OpenCL_LIBRARY}")
include_directories(  ${OpenCV_INCLUDE_DIRS})
link_directories( ${OpenCV_LIBRARY_DIRS})
message( "OpenCV_LIBS" )
message( "${OpenCV_LIBS}" )
message( "OpenCV_LIBRARIES" )
message( "${OpenCV_LIBRARIES}" )


FIND_PACKAGE( OpenMP REQUIRED)
if(OPENMP_FOUND)
    #    OpenMP::OpenMP_CXX   -fopenmp  -lstdc++
    message("OPENMP FOUND")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
    include_directories(   ${OpenMP_INCLUDES}  )
endif()






set(PROJECT_SOURCES
        main.cpp
        widget.cpp
        widget.h
        widget.ui  qdicethread.cpp  qdicethread.h  resource.qrc  a.rc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(qBatchCutROI
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET qBatchCutROI APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(qBatchCutROI SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(qBatchCutROI
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(qBatchCutROI PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${OpenCV_LIBRARIES} )

set_target_properties(qBatchCutROI PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS qBatchCutROI
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(qBatchCutROI)
endif()
