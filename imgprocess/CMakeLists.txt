project(ImgProcess)
cmake_minimum_required(VERSION 2.8)

#添加QT4库
find_package(QT4 REQUIRED)
include(${QT_USE_FILE})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_definitions(${QT_DEFINITIONS})
					
set(OPENCVSHARE)
				
#将.h文件进行moc操作， ui文件进行uic操作，资源文件进行rcc操作
#设置头文件
set(IMGPRROCESS_HEADERS 
	shell/ui/startanimal.h 
	shell/ui/showpicture.h 
	shell/ui/imgprocesscenterwidget.h 
	shell/ui/mainwindow.h
	shell/ui/imgprocessarea.h
	shell/ui/hotkeytabledialog.h
	shell/ui/hotkeylineedit.h
	shell/ui/onlineexplorer.h
	shell/screenshot/screenimg.h
	shell/screenshot/screentoolbar.h
	shell/screenshot/screenarearect.h
	)
	
#设置ui文件
set(IMGPROCESS_UIS 
	shell/ui/mainwindow.ui 
	shell/ui/showpicture.ui 
	shell/ui/imgprocesscenterwidget.ui
	shell/ui/imgprocessarea.ui
	shell/ui/hotkeytabledialog.ui
	shell/ui/onlineexplorer.ui
	shell/screenshot/screentoolbar.ui
	)

#设置qrc文件
set(IMGPROCESS_QRCS 
	shell/resource/img.qrc)

#cmake 不区分大小写
set(IMGPROCESS_SRCS	
	shell/main.cpp 
	shell/stdafx.h
	shell/stdafx.cpp
	shell/ui/mainwindow.cpp 
	shell/ui/startanimal.cpp 
	shell/ui/showpicture.cpp 
	shell/ui/imgprocesscenterwidget.cpp
	shell/ui/imgprocessarea.cpp
	shell/ui/hotkeytabledialog.cpp
	shell/ui/hotkeylineedit.cpp
	shell/ui/onlineexplorer.cpp
	shell/screenshot/screenimg.cpp
	shell/screenshot/screentoolbar.cpp
	shell/screenshot/screenarearect.cpp
	shell/utility/cvtools.cpp
	shell/utility/cvtools.h
	shell/utility/winsort.h
	shell/utility/hash.h
	shell/cvimg/imgdata.h
	shell/resource/imgprocess.rc
	)

QT4_WRAP_CPP (IMGPRROCESS_HEADERS_MOCS ${IMGPRROCESS_HEADERS})
QT4_WRAP_UI (IMGPROCESS_UIS_UIC ${IMGPROCESS_UIS})
QT4_ADD_RESOURCES	(IMGPROCESS_QRCS_RCC ${IMGPROCESS_QRCS})


#添加引用头文件上层文件
include_directories(shell/)

#添加opencv库头文件
include_directories(include
					include/opencv
					include/opencv2
					)
					
#添加opencvlib库
set (OPENCVLIBPATH ${PROJECT_SOURCE_DIR}/3rdparty/opencv/x86/vc10)
set (OPENCVLIB
	${OPENCVLIBPATH}/lib/opencv_calib3d231d.lib
	${OPENCVLIBPATH}/lib/opencv_contrib231d.lib
	${OPENCVLIBPATH}/lib/opencv_core231d.lib
	${OPENCVLIBPATH}/lib/opencv_features2d231d.lib
	${OPENCVLIBPATH}/lib/opencv_flann231d.lib
	${OPENCVLIBPATH}/lib/opencv_gpu231d.lib
	${OPENCVLIBPATH}/lib/opencv_highgui231d.lib
	${OPENCVLIBPATH}/lib/opencv_imgproc231d.lib
	${OPENCVLIBPATH}/lib/opencv_legacy231d.lib
	${OPENCVLIBPATH}/lib/opencv_ml231d.lib
	${OPENCVLIBPATH}/lib/opencv_objdetect231d.lib
	${OPENCVLIBPATH}/lib/opencv_ts231d.lib
	${OPENCVLIBPATH}/lib/opencv_video231d.lib
	)

#添加opencvdll库	
set (OPENCVSHAREDLL
	${OPENCVLIBPATH}/bin/opencv_core231d.dll
	${OPENCVLIBPATH}/bin/opencv_highgui231d.dll
	)
	
#添加工程 并链接qt库
add_executable(ImgProcess	${IMGPRROCESS_HEADERS_MOCS}
							${IMGPROCESS_SRCS}
							${IMGPROCESS_UIS_UIC}
							${IMGPROCESS_QRCS_RCC})
						
					
target_link_libraries(ImgProcess 
					${OPENCVLIB}
					${QT_LIBRARIES}
					Qt4::QtWebKit)
					
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

###############################################
# todo:添加opencv支持



