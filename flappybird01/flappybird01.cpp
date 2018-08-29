// flappybird01.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "bird.h"
#include "scence.h"
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include "pipes.h"
#include "playstatus.h"
#include "titlestatus.h"
#include "status.h"


#pragma comment(lib,"Winmm.lib")



#define DELTA_TIME 1
#define LEN 5



IMAGE background, ground;




int BACKGROUND_SCROLL_SPEED = 8;
int GROUND_SCROLL_SPEED = 10;
int BACKGROUND_LOOPING_POINT = 413;
int backgroundScroll;
int groundScroll;



void startup()
{
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
	loadimage(&background, _T("background.jpg"));
	loadimage(&ground, _T("ground.jpg"));
	
	mciSendString(_T("open marios_way.mp3 alias bkmusic"), NULL, 0, NULL);//打开背景音乐
	//mciSendString(_T("open C:\\Users\\clouduser\\source\\repos\\flappy_bird\\flappy_bird\\Material\\background.mp3 alias bkmusic"), NULL, 0, NULL);//打开背景音乐
	mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);  // 循环播放

	play_init();
	setStatus(TitleScreenState);


	BeginBatchDraw();
}

void updateWithoutInput(int dt)
{
	backgroundScroll = (backgroundScroll + BACKGROUND_SCROLL_SPEED * dt)
		% BACKGROUND_LOOPING_POINT;
	groundScroll = (groundScroll + GROUND_SCROLL_SPEED * dt)
		% WINDOW_WIDTH;
	switch (getStatus()) {
	case 0:
		title_update(dt);
		
		break;
	case 1:
		play_update(dt);
		break;
	}
		

}
void updateWithInput()
{

}

void show()
{
	putimage(-backgroundScroll, 0, &background);
	putimage(-groundScroll, WINDOW_HEIGHT - 16, &ground);
	
	switch (getStatus()) {
	case 0:
		title_render();
		break;
	case 1:
		play_render();
		
		break;
	}

	FlushBatchDraw();

	Sleep(50);

}

void gameover()
{
	EndBatchDraw();
}


int main()
{	
	startup();
	while (1)
	{
		show();  // 显示画面
		updateWithoutInput(DELTA_TIME);  // 与用户输入无关的更新
		updateWithInput();     // 与用户输入有关的更新
	}
	gameover();     // 游戏结束、后续处理
	return 0;
}


