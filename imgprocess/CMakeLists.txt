PROJECT(ImgProcess)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(PLATFORM_NAME "${PlatformName}")
SET(CONFIGURATION_NAME "${ConfigurationName}")

#添加QT4库
FIND_PACKAGE(QT4 REQUIRED)
INCLUDE(${QT_USE_FILE})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
ADD_DEFINITIONS(${QT_DEFINITIONS})

#将.h文件进行moc操作， ui文件进行uic操作，资源文件进行rcc操作
#设置头文件
SET(IMGPRROCESS_HEADERS mainwindow.h showpicture.h )
SET(IMGPRROCESS_HEADERS startanimal.h)

#设置ui文件
SET(IMGPROCESS_UIS mainwindow.ui showPicure.ui)
#设置qrc文件
SET(IMGPROCESS_QRCS img.qrc)

#cmake 不区分大小写
set(IMGPROCESS_SRCS main.cpp mainwindow.cpp startanimal.cpp showPicure.cpp)

SET(CMAKE_AUTOMOC ON)

QT4_WRAP_CPP (IMGPRROCESS_HEADERS_MOC ${IMGPRROCESS_HEADERS})
QT4_WRAP_UI (IMGPROCESS_UIS_UIC ${IMGPROCESS_UIS})
QT4_ADD_RESOURCES	(IMGPROCESS_QRCS_RCC ${IMGPROCESS_QRCS})

#添加工程 并链接qt库
add_executable(ImgProcess	${IMGPROCESS_SRCS}
							${IMGPRROCESS_HEADERS_MOC}
							${IMGPROCESS_UIS_UIC}
							${IMGPROCESS_QRCS_RCC})

target_link_libraries(ImgProcess ${QT_LIBRARIES})							




