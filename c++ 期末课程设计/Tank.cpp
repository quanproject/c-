#include "Tank.h"
#include"main_game.h"
using namespace std;

//list<Shell*> EnemyTankShell;          //储存敌方坦克的子弹

Tank::Tank()
{
	/*
	Speed = SpeedLevel_1;           //初始速度
	Hp = 1;                         //初始生命
	Direction = UP;                 //初始方向
	ReadyForFire = 1;               //开局装弹
	FireInterval = IntervalLevel_1; //初始攻击间隔
	RectSphere = 60;                //坦克大小60x60像素
	*/
}


Tank::~Tank()
{
}


void Tank:: ChangeHp(int flag)
{
	if (flag == 1) //根据情况加减生命值
		Hp++;
	if (flag == 0)
		Hp--;
}


void Tank::FireIntevalFigure()
{
	static int nowInterval = FireInterval;  //初始化冷却时间
	if(!ReadyForFire)   //如果并没有冷却好，才开始减冷却
	nowInterval--;                   //冷却ing
	if (nowInterval == 0)           //冷却好了
	{
		nowInterval = FireInterval;  //重置冷却时间
		ReadyForFire=1;      //装弹（可以射击下一发
	}
}

//////////////////////////////////////玩家tank////////////////////////////////
PlayTank::PlayTank()
{
	Speed = SpeedLevel_1;           //初始速度
	Hp = 1;                         //初始生命
	Direction = UP;                 //初始方向
	ReadyForFire = 1;               //开局装弹
	FireInterval = IntervalLevel_1; //初始攻击间隔
	RectSphere = 60;                //坦克大小60x60像素
}

void PlayTank::Fire()
{
	ReadyForFire=0;     //进入开火冷却
}

void PlayTank::MoveTank(Dir NewDir)
{
			switch (NewDir) {    //按照移动速度移动
			case UP:
				XY.Y -= Speed;  //修改坐标
				break;
			case DOWN:
				XY.Y += Speed;
				break;
			case LEFT:
				XY.X -= Speed;
				break;
			case RIGHT:
				XY.X+= Speed;
				break;
			}
}

void PlayTank::Print()
{
	IMAGE img1,img2;
	loadimage(&img1, _T("PlayerTank.jpg")); //读取照片 （像素为60x60）

     //根据方向和位置打印坦克
	if (Direction == UP)
	{
		putimage(XY.X, XY.Y, &img1);       //在固定位置打印坦克
	}
	else if (Direction == DOWN)
	{
		// 旋转图像 180 度 (PI / 6)
		rotateimage(&img2, &img1, PI);

		putimage(XY.X, XY.Y, &img2);

	}
	else if (Direction == LEFT)
	{
		// 旋转图像 270 度 (PI / 6)
		rotateimage(&img2, &img1, PI / 2);

		putimage(XY.X, XY.Y, &img2);

	}
	else
	{
		// 旋转图像 30 度 (PI / 6)
		rotateimage(&img2, &img1, (3*PI) / 2);

		putimage(XY.X, XY.Y, &img2);

	}
}

/////////////////////////////////////普通敌方坦克//////////////////////////
NormalAITank::NormalAITank()
{
	Speed = SpeedLevel_1;           //初始速度
	Hp = 1;                         //初始生命
	Direction = UP;                 //初始方向
	ReadyForFire = 1;               //开局装弹
	FireInterval = IntervalLevel_1; //初始攻击间隔
	RectSphere = 60;                //坦克大小60x60像素
}

void NormalAITank::Print()
{
	IMAGE img1, img2;
	loadimage(&img1, _T("NormalTank.jpg")); //读取照片 （像素为60x60）

	 //根据方向和位置打印坦克
	if (Direction == UP)
	{
		putimage(XY.X, XY.Y, &img1);       //在固定位置打印坦克
	}
	else if (Direction == DOWN)
	{
		// 旋转图像 180 度 (PI / 6)
		rotateimage(&img2, &img1, PI);

		putimage(XY.X, XY.Y, &img2);

	}
	else if (Direction == LEFT)
	{
		// 旋转图像 270 度 (PI / 6)
		rotateimage(&img2, &img1, PI / 2);

		putimage(XY.X, XY.Y, &img2);

	}
	else
	{
		// 旋转图像 30 度 (PI / 6)
		rotateimage(&img2, &img1, (3 * PI) / 2);

		putimage(XY.X, XY.Y, &img2);

	}
}

Dir NormalAITank::NormalMoveAI()
{

	srand((unsigned int)time(NULL));

	int n = rand() % 5;
	switch (n)
	{
	case 0:return Direction; break;   //继续走
	case 1:return DOWN;  break;       //四个方向移动
	case 2:return RIGHT; break;
	case 3:return LEFT;  break;
	case 4:return RIGHT; break;
	}
}

void NormalAITank::MoveTank(Dir NewDir)
{
		switch (NewDir) {    //按照移动速度移动
		case UP:
			XY.Y -= Speed;  //修改坐标
			break;
		case DOWN:
			XY.Y += Speed;
			break;
		case LEFT:
			XY.X -= Speed;
			break;
		case RIGHT:
			XY.X += Speed;
			break;
		}
}

/*
void NormalAITank::Fire()
{
	ReadyForFire = 0;
	Shell *p = new Shell(Direction,XY);   //申请新内存
	p->Print();
	EnemyTankShell.push_back(p);                       //压入炮弹容器
}
*/

////////////////////////////////////精英敌方坦克//////////////////////////
BossAITank::BossAITank()
{
	Speed = SpeedLevel_3;           //初始速度
	Hp = 3;                         //初始生命
	Direction = UP;                 //初始方向
	ReadyForFire = 1;               //开局装弹
	FireInterval = IntervalLevel_3; //初始攻击间隔
	RectSphere = 60;                //坦克大小60x60像素
}

void BossAITank::Print()
{
	IMAGE img1, img2;
	loadimage(&img1, _T("BossTank.jpg")); //读取照片 （像素为60x60）

	 //根据方向和位置打印坦克
	if (Direction == UP)
	{
		putimage(XY.X, XY.Y, &img1);       //在固定位置打印坦克
	}
	else if (Direction == DOWN)
	{
		// 旋转图像 180 度 (PI / 6)
		rotateimage(&img2, &img1, PI);

		putimage(XY.X, XY.Y, &img2);

	}
	else if (Direction == LEFT)
	{
		// 旋转图像 270 度 (PI / 6)
		rotateimage(&img2, &img1, PI / 2);

		putimage(XY.X, XY.Y, &img2);

	}
	else
	{
		// 旋转图像 30 度 (PI / 6)
		rotateimage(&img2, &img1, (3 * PI) / 2);

		putimage(XY.X, XY.Y, &img2);

	}
}