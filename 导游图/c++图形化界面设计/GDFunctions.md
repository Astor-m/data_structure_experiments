GraphicsDesign



### 1.绘图窗口

​	1.1加载头文件

​		#include<graphics.h>

​	1.2创建窗口

​		initgarph(int width,int height)

​	1.3关闭窗口

​		closegraph()

​	1.4窗口坐标

​	1.5颜色

​		基本颜色：RED  BLUE  YELLOW

​		RGB配置颜色

​			RGB( color1 , color2 ,color3 )//三基色配置调颜色

​			setlinecolor(RGB())

​		

### 2.基本绘图

#### 	2.1画点(参数为点的坐标)

​		putpixel( int  x, int  y, COLOR  color)

#### 	2.2画线

​		line( int  x1, int  y1, int  x2, int  y2)//从点（x1,y1）到点（x2,y2）的直线

#### 	2.3画矩形						setfillcolor(RED)//设置填充颜色

​		2.3.1空心

​			rectangle(int  x1,int  y1,int  x2,int  y2)//点（x1,y1）到点（x2,y2）的矩形

​		2.3.2填充

​			有边界线

​				fillrectangle(int  x1,int  y1,int  x2,int  y2)

​			无边界线

​				soildrectangle(int  x1,int  y1,int  x2,int  y2)

#### 	2.4画圆

​		2.4.1空心

​			circle(int  x,int  y,int  R) 

​		2.4.2填充

​			fillcircle(int  x,int  y,int  R) 

​			soildcircle(int  x,int  y,int  R) 

#### 	2.5文字输出

​			settextcolor(RED)

​		2.5.1去掉文字背景

​			setbkmode(TRANSPARENT)

​		2.5.2输出字符串

​			outtextxy(int  x,int  y,char*  str)

​		2.5.3文字格式

​			settextstyle(int  x,int  y,char*  s)//s为字体种类如“宋体”

### 3.基本贴图

​	3.1声明图片变量

​			IMAGE  img;

​	3.2将图片文件赋给img

​		loadimage(&img,char  *imgurl,int  width,int  weight)//imgurl为图片路径,设置图片显示大小

​	3.3显示图片

​		putimage(int  x,int  y,&img)//x，y图片显示起点

​	3.4图片坐标

​		3.4.1定点去图片

​			putimage(int  x,int  y,int  1x,int  1y,&  img,int  x3,int  y3)

### 4.鼠标操作

​	4.1声明鼠标变量

​		MOUSEMSG m;

​		m=GetMouseMsg();//获得鼠标信息

​		4.2获取鼠标

​			鼠标信息：m.uMsg

```
			swith(m.uMsg){
				case WM_MOUSEMOVE:
					break;
				case WM_LBTUUONDOWM://左键
					break;
				case WM_RBTUUONDOWM://右键
				break;
}
```

​	
