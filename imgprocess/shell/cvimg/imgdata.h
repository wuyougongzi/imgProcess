
//�������ݽṹ
#include <hash_map>

using namespace std;

/*
typedef struct {

}CvImgInfo;
*/

//ÿ��ͼƬ���߸�������Ϣ���
//������������ͼƬ��
//


struct ZoneFeature
{
	int pixel;			//���ص��ܺͣ��о����ֵ���岻��
	int veinOne;		//һ������
	int veiwTwo;		//��������
	int viewThree;		//��������
	int featureId;		//����ͨ�����ص��������һ��hashֵ,Ҫ��֤��ͬ�ľ������ɵ�ֵ������ͬ,��ʱ�Ȳ���,��һ��Ч��
	void *otherInfo;	//���ű���
};

//intΪС��8����ֵ
//��λȡֵ����Ӧ��λΪ1�����ʾ�Ǹ�ͼƬ��Ҫ����Ϣ�������ǡ�
hash_map<__int64, int> ImgRecognitionMap;
