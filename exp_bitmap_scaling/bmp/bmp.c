#include<stdio.h>
#include<malloc.h>
#include<string.h>
#pragma pack(1)	// �ýṹ���и���Ա��1�ֽڶ���,��������ļ���д���� 

//BMP�Ĵ��: 1.�ļ�ͷ 2.��Ϣͷ 3.��ɫ�� 4.λͼ���� 

//�ļ�ͷ
typedef struct tagBITMAPFILEHEADER {
	//unsigned short bfType;	  // ����ͼƬ���ͣ���ȡʱ��Ҫ��ע�͵����ı���ʶ��ֻ�ܵ������ж�д
    unsigned int   bfSize;        // �ļ���С
    unsigned short bfReserved1;   // ����������Ϊ0
    unsigned short bfReserved2;   // ����������Ϊ0
    unsigned int   bfOffBits;     // ���ļ�ͷ��ʵ�ʵ�ͼ������֮����ֽڵ�ƫ����
}BITMAPFILEHEADER;
//��Ϣͷ
typedef struct tagBITMAPINFOHEADER {
    unsigned int    biSize;          // �˽ṹ��Ĵ�С
    unsigned int    biWidth;         // ͼ��Ŀ�
    unsigned int    biHeight;        // ͼ��ĸ�
    unsigned short  biPlanes;        // ��ɫƽ���� ��Ϊ1
    unsigned short  biBitCount;      // һ������ռ��λ�� һ��Ϊ24
    unsigned int    biCompression;   // ˵��ͼ������ѹ�������ͣ�0Ϊ��ѹ��
    unsigned int    biSizeImage;     // ͼ���С, ֵ���������ļ�ͷ�ṹ��bfSize-bfOffBits
    int             biXPelsPerMeter; // ˵��ˮƽ�ֱ��ʣ�������/�ױ�ʾ һ��Ϊ0 
    int             biYPelsPerMeter; // ˵����ֱ�ֱ��ʣ�������/�ױ�ʾ һ��Ϊ0 
    unsigned int    biClrUsed;       // ˵��λͼʵ��ʹ�õĲ�ɫ���е���ɫ����������Ϊ0�Ļ�����˵��ʹ�����е�ɫ���
    unsigned int    biClrImportant;  // ˵����ͼ����ʾ����ҪӰ�����ɫ��������Ŀ �����0��ʾ����Ҫ
}BITMAPINFOHEADER;
//��ɫ��[��256(==2^8)��������ɫ��8λ���ϵĿ���û�е�ɫ��]
struct PixelInfo {
    unsigned char rgbBlue;     //����ɫ����ɫ����  (ֵ��ΧΪ0-255)
    unsigned char rgbGreen;    //����ɫ����ɫ����  (ֵ��ΧΪ0-255)
    unsigned char rgbRed;      //����ɫ�ĺ�ɫ����  (ֵ��ΧΪ0-255)
    unsigned char rgbReserved; // ����������Ϊ0
};
BITMAPFILEHEADER fileHeader;
BITMAPINFOHEADER infoHeader;

//��ʾbmpͼƬ�ļ�ͷ���� 
void showBmpHead(BITMAPFILEHEADER pBmpHead)
{  
	//printf("�ļ���ʶ����%x\n", fileHeader.bfType);
	printf("BMP�ļ���С��%dkb\n", fileHeader.bfSize);
	printf("�����ֱ���Ϊ0��%d\n", fileHeader.bfReserved1);
	printf("�����ֱ���Ϊ0��%d\n", fileHeader.bfReserved2);
	printf("ʵ��λͼ���ݵ�ƫ���ֽ���: %d\n", fileHeader.bfOffBits);
}
//��ʾbmpͼƬλͼ��Ϣͷ���� 
void showBmpInfoHead(BITMAPINFOHEADER pBmpinfoHead)
{
	printf("λͼ��Ϣͷ:\n");
	printf("��Ϣͷ�Ĵ�С:%d\n", infoHeader.biSize);
	printf("λͼ���:%d\n", infoHeader.biWidth);
	printf("λͼ�߶�:%d\n", infoHeader.biHeight);
	printf("ͼ���λ����(λ�����ǵ�ɫ�������,Ĭ��Ϊ1����ɫ��):%d\n", infoHeader.biPlanes);
	printf("ÿ�����ص�λ��:%d\n", infoHeader.biBitCount);
	printf("ѹ����ʽ:%d\n", infoHeader.biCompression);
	printf("ͼ��Ĵ�С:%d\n", infoHeader.biSizeImage);
	printf("ˮƽ����ֱ���:%d\n", infoHeader.biXPelsPerMeter);
	printf("��ֱ����ֱ���:%d\n", infoHeader.biYPelsPerMeter);
	printf("ʹ�õ���ɫ��:%d\n", infoHeader.biClrUsed);
	printf("��Ҫ��ɫ��:%d\n", infoHeader.biClrImportant);
}
int main(int agrc, char *argv[]) {
	FILE* fp;
	unsigned short fileType;
	fp = fopen("zh.bmp", "rb");
	if (fp == NULL) {
		printf("��ͼƬ'img.bmp'ʧ��!\n");
		return -1;
	}
	fread(&fileType, sizeof(unsigned short), 1, fp);
	//42 4d : 4d42 : 19778
	//e6 1e 04 00 : 00041ee6 : 270054�ֽ� 
	if (fileType == 0x4d42)//bfType,ͼƬ������,������BMP, 0x4d42(��ʮ���Ƶ�19778) 
	{
		printf("�ļ����ͱ�ʶ��ȷ!");
		printf("\n�ļ���ʶ����%x\n", fileType);
		fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, fp);
		showBmpHead(fileHeader);
		fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, fp);
		showBmpInfoHead(infoHeader);
		fclose(fp); 
	}
	return 0;
}
