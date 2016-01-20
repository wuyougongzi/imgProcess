1 图像处理相关
2 代码结构说明：
	a 3rdparty 第三方库支持，暂时包含opencv 部分
	b include 头文件引用部分
	c resouce 资源文件存放位置
	d shell 整体界面相关。
	e cmakeList 采用cmake构建工程,代码与build相隔离
	f imgprocess.pro qt工程文件，用qtcreator编辑器时直接打开即可，暂时不维护更新，但保留。
	g opencv 已经添加进代码库中，是精简过的lib 和dll暂时只支持32 vs10 
	h 环境配置可能需要说明，cmake中没有打包qt和opencv的dll支持（opencv是否一定需要不确定）
	  这边都配置qt的bin路径和opencv的bin路径加入到系统环境变量中，后期考虑cmake 打包。	

3 代码整体结构调整