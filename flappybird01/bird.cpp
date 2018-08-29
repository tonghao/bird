
#include "stdafx.h"
#include "bird.h"
#include "scence.h"
#include <graphics.h>
#include <conio.h>

IMAGE bird, bird_mask;
int bird_x, bird_y;

int dy;

int GRAVITY = 1;

void bird_init()
{
	loadimage(&bird, _T("bird.jpg"));
	loadimage(&bird_mask, _T("bird_mask.jpg"));

	bird_x = WINDOW_WIDTH / 2 - bird.getwidth() / 2;
	bird_y = WINDOW_HEIGHT / 2 - bird.getheight() / 2;
}

void bird_update(int dt)
{
	int c;

	dy = dy + GRAVITY * dt;
	bird_y = bird_y + dy;

	if (_kbhit())
		if ((c = _getch()) == ' ')
		{
			dy = -5;
			mciSendString(_T("close jpmusic"), NULL, 0, NULL); // �Ȱ�ǰ��һ�ε����ֹر�
			//mciSendString(_T("open C:\\Users\\clouduser\\source\\repos\\flappy_bird\\flappy_bird\\Material\\Jump.mp3 alias jpmusic"), NULL, 0, NULL); // ����������
			mciSendString(_T("open jump.mp3 alias jpmusic"), NULL, 0, NULL); 
			mciSendString(_T("play jpmusic"), NULL, 0, NULL); // ������һ��
		}

}



void bird_render()
{
	putimage(bird_x, bird_y, &bird_mask, NOTSRCERASE);
	putimage(bird_x, bird_y, &bird, SRCINVERT);

}