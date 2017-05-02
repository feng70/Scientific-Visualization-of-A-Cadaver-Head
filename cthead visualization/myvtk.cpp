//读入一序列tif格式的图像，利用mc算法进行三维重建，得到头颅的立体展示，设置皮肤的透明度为0.5，
//外面一层为皮肤，里面为骨骼。
//dataset来源于The Stanford volume data archive（http://graphics.stanford.edu/data/voldata/）

#include"stdafx.h"
#include <vtkSmartPointer.h>
#include <vtkMarchingCubes.h>
#include <vtkImageData.h>
#include<vtkProperty.h>
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include<vtkTIFFReader.h>
#include<vtkImageReader.h>
#include<vtkOutlineFilter.h>

int main(int argc, char *argv[])
{
	vtkSmartPointer<vtkImageData> volumedata =vtkSmartPointer<vtkImageData>::New();   //定义volume数据对象
	vtkSmartPointer<vtkRenderer> vtkrenderer = vtkSmartPointer<vtkRenderer>::New();      //声明绘制者
	vtkSmartPointer<vtkRenderWindow> vtkrenderWindow = vtkSmartPointer<vtkRenderWindow>::New();   //声明绘制窗口
	vtkrenderWindow->AddRenderer(vtkrenderer);   //绘制者加入绘制窗口
	vtkSmartPointer<vtkRenderWindowInteractor> windowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();//交互窗口
	windowInteractor->SetRenderWindow(vtkrenderWindow);

	vtkTIFFReader *tifReader = vtkTIFFReader::New();//用tiff进行读取一系列tif格式的图片 
	tifReader->SetFilePrefix("cthead-16/cthead-16bit");  //设置tif图像文件读取的前缀
	tifReader->SetFilePattern("%s%03d.tif");  //设置图片名称的格式
	//vtkImageReader2 *reader = vtkImageReader2::New();  //用vtkImageReader2读取
	tifReader->SetDataExtent(0, 255, 0, 255, 1, 99);   //256*256，99张
	//reader->SetDataExtent(0, 149, 0, 149, 0, 275);  //尺寸150*150，276张
	tifReader->SetDataSpacing(1, 1, 2);
    //reader->SetFileName("mouse0.raw"); //文件名
	tifReader->SetDataScalarTypeToUnsignedShort(); //转化为ushort
	tifReader->SetDataByteOrderToBigEndian();  //转化为大端格式
	tifReader->SetFileDimensionality(3);  //一个文件内存储的数据维数
	tifReader->Update();
	volumedata->DeepCopy(tifReader->GetOutput());  //复制读入的数据

	vtkSmartPointer<vtkMarchingCubes> skinsurface =vtkSmartPointer<vtkMarchingCubes>::New(); //声明等值面对象
    skinsurface->SetInputData(volumedata);  //将volume数据对象作为输入，这个方法不建立可视化管线链接 
    skinsurface->ComputeNormalsOn();  //为了使等值面有明暗效果，开启法向量计算
	skinsurface->SetValue(0, 800);  //设置等值面的值

	vtkSmartPointer<vtkPolyDataMapper> skinmapper = vtkSmartPointer<vtkPolyDataMapper>::New(); //体数据映射为可显示的图像数据
	skinmapper->SetInputConnection(skinsurface->GetOutputPort());
	skinmapper->ScalarVisibilityOff();  //不带颜色

	vtkSmartPointer<vtkActor> skinActor =vtkSmartPointer<vtkActor>::New();  //skin角色
	skinActor->SetMapper(skinmapper);
	skinActor->GetProperty()->SetDiffuseColor(1, .45, .29);  //设置皮肤表面的颜色，皮肤颜色在这个设置左右
	skinActor->GetProperty()->SetOpacity(0.5);  //设置等值面的透明度，1表示不透明，0表示完全透明,0.5表示半透明

	vtkSmartPointer<vtkMarchingCubes> bonesurface = vtkSmartPointer<vtkMarchingCubes>::New(); //声明骨骼等值面对象
	bonesurface->SetInputData(volumedata);
	bonesurface->ComputeNormalsOn();  //为了使等值面有明暗效果，开启法向量计算
	bonesurface->SetValue(1, 1150);  //设置等值面的值

	vtkSmartPointer<vtkPolyDataMapper> bonemapper = vtkSmartPointer<vtkPolyDataMapper>::New(); //体数据映射为可显示的图像数据
	bonemapper->SetInputConnection(bonesurface->GetOutputPort());
	bonemapper->ScalarVisibilityOff(); //不带颜色

	vtkSmartPointer<vtkActor> boneActor = vtkSmartPointer<vtkActor>::New();  //bone角色
	boneActor->SetMapper(bonemapper);
	boneActor->GetProperty()->SetDiffuseColor(1, 1, .9241);  //设置骨骼表面的颜色，骨骼颜色在这个设置左右

	vtkrenderWindow->SetSize(640, 500);  //设置显示窗口的大小
	vtkrenderer->SetBackground(.1, .2, .3);  //设置显示的背景颜色
	vtkrenderer->AddActor(skinActor);   //加入皮肤
	vtkrenderer->AddActor(boneActor);  //加入骨骼
	vtkrenderWindow->Render();  //让每个窗口内的成员开始绘制它们的图像并综合起来
	windowInteractor->Start();  //开始演示

//释放空间
	tifReader->Delete();
	skinsurface->Delete();
	skinmapper->Delete();
	skinActor->Delete();
	bonesurface->Delete();
	bonemapper->Delete();
	boneActor->Delete();
	vtkrenderer->Delete();
	vtkrenderWindow->Delete();
	windowInteractor->Delete();

	return EXIT_SUCCESS;
}
