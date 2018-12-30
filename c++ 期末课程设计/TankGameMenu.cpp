#include "TankGameMenu.h"
using namespace std;

void const drawdre(COORD x);              //画方块函数
bool const cor_cmp(COORD pt1, COORD pt2);  //坐标比较函数
bool const JudgmentKill(COORD shellxy, COORD tankxy); //命中函数


TankGameMenu::TankGameMenu()
{
}


TankGameMenu::~TankGameMenu()
{
}
//主菜单
void TankGameMenu::printTankGameMenu()
{
	initgraph(1200, 900);              //初始化图形界面
	setbkcolor(BLACK);              //设置字体背景颜色
	setfillcolor(BLACK);            //设置初始背景颜色
	solidrectangle(0,0,1200,900);      //画出背景色
	settextstyle(40, 0, _T("黑体"));   //设置文字格式各个参数

	int const ox = 500;          //标注位置的常量

	settextcolor(RED);          //被选择的字体颜色
	outtextxy(ox, ox-100, _T("游 戏 开 始"));//菜单界面文字输出
	settextcolor(GREEN);        //未选择的字体颜色
	outtextxy(ox, ox+50, _T("游 戏 说 明"));
	outtextxy(ox, ox+200, _T("退 出 游 戏"));

	int dir;                        //菜单选择方向，上和下
	int flag = 1;                   //确定选择
	while (1)
	{
		if (_kbhit())
		{//根据flag值进行移动

			dir = _getch();    //获取方向键值
			if (dir == UP && flag != 1)  //根据键值变换选项
				flag--;
			if (dir == DOWN && flag != 3)
				flag++;
			if (dir == DETER)
				break;
			settextcolor(GREEN);
			outtextxy(ox, ox-100, _T("游 戏 开 始"));//菜单界面文字颜色覆盖
			outtextxy(ox, ox+50, _T("游 戏 说 明"));
			outtextxy(ox, ox+200, _T("退 出 游 戏"));

			switch (flag)                //根据选项变换颜色
			{
			case 1: settextcolor(RED);
				outtextxy(ox, ox - 100, _T("游 戏 开 始"));
				break;
			case 2: settextcolor(RED);
				outtextxy(ox, ox + 50, _T("游 戏 说 明"));
				break;
			case 3:settextcolor(RED);
				outtextxy(ox, ox + 200, _T("退 出 游 戏"));
				break;
			default: break;
			}
		}
	}
	if (flag == 1)//游戏开始
	{
		GameStart(1);
	}
	if (flag == 2)//游戏说明
	{
		Commeting();
	}
	if (flag == 3)//退出游戏
	{
		Inaugurated();  //结束动画
		exit(-1);
	}

}
//刷屏
void TankGameMenu::Inaugurated()
{
	setfillcolor(GREEN);            //设置颜色
	COORD point = { 0,0 };          //设置笔尖位置（画方块的初始位置
	while (point.Y<=2)
	{
		while (point.X <= 60)
		{
			drawdre(point);
			drawdre({ point.X-7,point.Y + 1 });
			drawdre({ point.X-15,point.Y + 2 });
			drawdre({ point.X-2,point.Y + 4 });
			drawdre({ point.X-1,point.Y + 5 });
			drawdre({ point.X-4,point.Y + 6 });
			drawdre({ point.X - 15,point.Y + 8 });
			drawdre({ point.X-1,point.Y + 9 });
			drawdre({ point.X-2,point.Y + 11 });
			drawdre({ point.X - 3,point.Y + 13 });
			drawdre({ point.X - 15,point.Y + 15 });
			drawdre({ point.X - 6,point.Y + 16 });
			drawdre({ point.X - 7,point.Y + 18 });
			drawdre({ point.X - 18,point.Y + 20 });
			drawdre({ point.X - 1,point.Y + 21 });
			drawdre({ point.X - 18,point.Y + 23 });
			drawdre({ point.X - 15,point.Y + 24 });
			drawdre({ point.X - 1,point.Y + 26 });
			drawdre({ point.X - 4,point.Y + 28 });
			drawdre({ point.X - 1,point.Y + 30 });
			drawdre({ point.X - 20,point.Y + 32 });
			drawdre({ point.X - 15,point.Y + 33 });
			drawdre({ point.X - 4,point.Y + 35 });
			drawdre({ point.X - 1,point.Y + 37 });
			drawdre({ point.X - 20,point.Y + 39 });
			drawdre({ point.X - 4,point.Y + 40 });
			point.X += 1;
			Sleep(8);
		}
		point.X = 0;
		point.Y += 1;
	}
	printf("%d,%d\n", point.X, point.Y);
}
//游戏开始
void TankGameMenu::GameStart(int card)
{
	setfillcolor(BLACK);            //设置初始背景颜色
	solidrectangle(0, 0, 1200, 900);      //画出背景色

	srand((unsigned int)time(NULL));


	////////////////////////////////////////////////////测试范围//////////////////////////////////////////////////
	//定义多个对象


	//容器
	list<Shell*> PlayerTankShell;         //存储玩家坦克的子弹 
	list<Shell*> EnemyTankShell;          //储存敌方坦克的子弹
	list<NormalAITank*> NormalTank;       //储存敌方坦克


	//迭代器
	list<Shell*>::iterator PTS;           //玩家坦克的子弹
	list<Shell*>::iterator ETS;           //敌方坦克的子弹
	list<NormalAITank*>::iterator NT;     //敌方坦克




	PlayTank player;                    //定义玩家坦克
	COORD Judgmentxy;                   //用来判断是否遇到地形阻挡的 坐标记录
	Map gamemap;                        //定义地图

	player.Setxy({ 14*GAMESIZE,24*GAMESIZE });              //定位玩家初始坐标



	int operation;                    //记录操作键
	int random;                       //一个随机数
	
	BeginBatchDraw();          //开始批量绘图

	gamemap.ReadyforMap_one();            //地图生成通用地形



	//循环游戏过程
	while (1)
	{
		//玩家按键操作响应
		if (_kbhit())       //如果玩家有输入
		{
			operation= _getch();    //获取当前操作

			if (operation == DETER && player.GetReadyForFire())          //确认攻击操作而且已经冷却好了
			{
				player.Fire();             //使玩家进入开炮冷却
				Shell *p = new Shell(player.GetDir(),player.Getxy());   //申请新内存
				p->Print();                                          //打印炮弹
				PlayerTankShell.push_back(p);                       //压入炮弹容器
			}

			else if (operation == UP || operation == DOWN || operation == RIGHT || operation == LEFT)    //移动操作
			{
				Judgmentxy = player.Getxy();   //记录当前坦克坐标
				player.ChangeDir((Dir)operation);           //修改坦克朝向
				switch (operation) { 
				case UP:
					Judgmentxy.Y-=player.GetSpeed();  
					break;
				case DOWN:
					Judgmentxy.Y += player.GetSpeed();
					break;
				case LEFT:
					Judgmentxy.X -= player.GetSpeed();
					break;
				case RIGHT:
					Judgmentxy.X += player.GetSpeed();
					break;
				}
				if (gamemap.GetTankAdmit(Judgmentxy)                                  //判断四角是否与地形碰撞
					&& gamemap.GetTankAdmit({ Judgmentxy.X + 59,Judgmentxy.Y + 59 })
					&& gamemap.GetTankAdmit({ Judgmentxy.X ,Judgmentxy.Y + 59 })
					&& gamemap.GetTankAdmit({ Judgmentxy.X + 59,Judgmentxy.Y })
					&& !gamemap.JudgmentBorder(Judgmentxy)                             //判断两角是否超界
					&&!gamemap.JudgmentBorder({ Judgmentxy.X + 59,Judgmentxy.Y + 59 }))
				player.MoveTank((Dir)operation);      //移动坦克        这里将int型强制转换为Dir（方向）类型
			}
			//玩家操作
		}


		//生成敌方坦克	
		if (gamemap.GetNumNormalTank() > 0 && NormalTank.size()< 3)   //场上少于4个敌方坦克且坦克还有剩余
		{
			NormalAITank *p=new NormalAITank();        //分配tank内存
			gamemap.KillNormalTank();                  //减少剩余敌方坦克数量
			random = rand();     //随机数
			p->Setxy(gamemap.CreatObjectXY(random));         //随机分配位置
			NormalTank.push_back(p);          //压入
		}
		
		///////////////////////////////////打印环节//////////////////////////////////////
		loadimage(NULL, _T("Floor.jpg"));          //背景地图
		gamemap.PrintMap_2();   //画地图Map类（根据card确定map  坦克下方
		player.Print();  //打印玩家坦克

		 //对所有普通敌方坦克操作（开火，移动，打印
		for (NT = NormalTank.begin(); NT != NormalTank.end();)  
		{
			if ((*NT)->GetHP() == 0)        //判断是否死亡
			{
				NT = NormalTank.erase(NT);       //释放敌方坦克内存
			}
			else
			{
				random = rand();  //随机数
				Dir movedir = (*NT)->NormalMoveAI(random);    //调用普通坦克移动ai
				Judgmentxy = (*NT)->Getxy();        //记录当前坦克坐标


				//开火判断（好了就打
				if ((*NT)->GetReadyForFire())        
				{
					(*NT)->ChangeReadyForFire(0);     //冷却
					Shell *p = new Shell(movedir, Judgmentxy);   //申请新内存
					p->Print();
					EnemyTankShell.push_back(p);                       //压入炮弹容器
				}



				//修改坦克朝向
				(*NT)->ChangeDir(movedir);          
				switch (movedir) {
				case UP:
					Judgmentxy.Y -= SpeedLevel_1;
					break;
				case DOWN:
					Judgmentxy.Y += SpeedLevel_1;
					break;
				case LEFT:
					Judgmentxy.X -= SpeedLevel_1;
					break;
				case RIGHT:
					Judgmentxy.X += SpeedLevel_1;
					break;
				}

				if (gamemap.GetTankAdmit(Judgmentxy)                                  //判断四角是否与地形碰撞
					&& gamemap.GetTankAdmit({ Judgmentxy.X + 59,Judgmentxy.Y + 59 })
					&& gamemap.GetTankAdmit({ Judgmentxy.X ,Judgmentxy.Y + 59 })
					&& gamemap.GetTankAdmit({ Judgmentxy.X + 59,Judgmentxy.Y })
					&& !gamemap.JudgmentBorder(Judgmentxy)                             //判断两角是否超界
					&& !gamemap.JudgmentBorder({ Judgmentxy.X + 59,Judgmentxy.Y + 59 }))
					(*NT)->MoveTank(movedir);      //移动敌方普通坦克        

				(*NT)->Print();         //打印坦克


				++NT;           //对下一个坦克操作
			}
		}
		gamemap.PrintMap_1();  //画地图Map类（根据card确定map   坦克上方


		//迭代器遍历对玩家炮弹操作
		for (PTS = PlayerTankShell.begin(); PTS != PlayerTankShell.end();)   
		{

			(*PTS)->Print();       //打印炮弹
			(*PTS)->Fly();         //炮弹移动
			COORD Shellxy = (*PTS)->GetXY();  //记录炮弹坐标
			bool flag = 0;        //是否命中敌方坦克的标志

			for (NT = NormalTank.begin(); NT != NormalTank.end(); NT++)      //遍历坦克来确认有没有命中
			{
				if (JudgmentKill(Shellxy, (*NT)->Getxy()))  //命中
				{
					(*NT)->ChangeHp(0);              //减少HP
					flag = 1;
					break;
				}
			}

			if (!gamemap.GetShellAdmit((*PTS)->GetXY()))			          //判断是否打到地形
			{
				gamemap.ChangeMap((*PTS)->GetXY()); //修改地图（减少墙体耐久
				PTS = PlayerTankShell.erase(PTS);	//命中删除并释放内存
			}
			else if (gamemap.JudgmentBorder((*PTS)->GetXY())||flag)          //炮弹超界或击杀
			{
				PTS = PlayerTankShell.erase(PTS);	//删除并释放内存
			}
			else             //处理下一棵炮弹
			{
				++PTS;
			}
		}

		//迭代器遍历对敌方炮弹操作
		for (ETS = EnemyTankShell.begin(); ETS != EnemyTankShell.end();)  
		{

			(*ETS)->Print();       //打印炮弹
			(*ETS)->Fly();         //炮弹移动

			if (!gamemap.GetShellAdmit((*ETS)->GetXY()))			          //判断是否打到地形
			{
				gamemap.ChangeMap((*ETS)->GetXY()); //修改地图（减少墙体耐久
				ETS = EnemyTankShell.erase(ETS);	//命中删除并释放内存
			}

			//	else if()              //判断命中坦克

			else if (gamemap.JudgmentBorder((*ETS)->GetXY()))          //炮弹超界
			{
				ETS = EnemyTankShell.erase(ETS);	//删除并释放内存
			}
			else             //处理下一棵炮弹
				++ETS;
		}

		player.FireIntevalFigure();          //计算玩家开火冷却缩减
		for (NT = NormalTank.begin(); NT != NormalTank.end(); NT++)
			(*NT)->FireIntevalFigure();      //计算敌方炮弹冷却

		//结算
		//玩家生存状况（跳出
		//通关判定（跳出并调用下一关
		FlushBatchDraw();  //批量绘图
		Sleep(GameSpeed); //游戏延迟
		cleardevice();    //清除屏幕
	}
	EndBatchDraw();         //结束批量绘图
	gamemap.CloseMap();     //释放地图内存
	//死亡界面
	//再来一局or返回界面


	//////////////////////////////////////////////////////////////////测试范围/////////////////////////////////////////////////////////
}

//游戏说明
void TankGameMenu::Commeting()
{
	//打印一张图片
	loadimage(NULL, _T("说明图片"));
	//按k返回
	int flag;     //判断输入
	if (_kbhit())
		flag=_getch();
	if (flag == ACT)
		printTankGameMenu(); //返回选择菜单
}