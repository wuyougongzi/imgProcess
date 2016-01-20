project(ImgProcess)
cmake_minimum_required(VERSION 2.8)

#添加QT4库
find_package(QT4 REQUIRED)
include(${QT_USE_FILE})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_definitions(${QT_DEFINITIONS})

#将.h文件进行moc操作， ui文件进行uic操作，资源文件进行rcc操作
#设置头文件
set(IMGPRROCESS_HEADERS 
	shell/ui/startanimal.h 
	shell/ui/showpicture.h 
	shell/ui/imgprocesscenterwidget.h 
	shell/ui/mainwindow.h)

#设置ui文件
set(IMGPROCESS_UIS 
	shell/ui/mainwindow.ui 
	shell/ui/showpicture.ui 
	shell/ui/imgprocesscenterwidget.ui)

#设置qrc文件
set(IMGPROCESS_QRCS 
	shell/resource/img.qrc)

#cmake 不区分大小写
set(IMGPROCESS_SRCS	
	shell/main.cpp 
	shell/ui/mainwindow.cpp 
	shell/ui/startanimal.cpp 
	shell/ui/showpicture.cpp 
	shell/ui/imgprocesscenterwidget.cpp
	shell/resource/imgprocess.rc)

QT4_WRAP_CPP (IMGPRROCESS_HEADERS_MOCS ${IMGPRROCESS_HEADERS})
QT4_WRAP_UI (IMGPROCESS_UIS_UIC ${IMGPROCESS_UIS})
QT4_ADD_RESOURCES	(IMGPROCESS_QRCS_RCC ${IMGPROCESS_QRCS})


#添加工程 并链接qt库
add_executable(ImgProcess	${IMGPRROCESS_HEADERS_MOCS}
							${IMGPROCESS_SRCS}
							${IMGPROCESS_UIS_UIC}
							${IMGPROCESS_QRCS_RCC})


target_link_libraries(ImgProcess ${QT_LIBRARIES})							

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

###############################################
# todo:添加opencv支持



