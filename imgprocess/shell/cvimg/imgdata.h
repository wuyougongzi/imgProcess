
//三层数据结构
#include <hash_map>

using namespace std;

/*
typedef struct {

}CvImgInfo;
*/

//每张图片由七个区域信息组成
//文字区，六个图片区
//


struct ZoneFeature
{
	int pixel;			//像素点总和，感觉这个值意义不大
	int veinOne;		//一阶纹理
	int veiwTwo;		//二阶纹理
	int viewThree;		//三阶纹理
	int featureId;		//可以通过像素点矩阵生成一个hash值,要保证相同的矩阵生成的值必须相同,暂时先不用,试一下效果
	void *otherInfo;	//留着备用
};

//int为小于8的数值
//按位取值，对应的位为1，则表示是该图片需要的信息，否则不是。
hash_map<__int64, int> ImgRecognitionMap;
