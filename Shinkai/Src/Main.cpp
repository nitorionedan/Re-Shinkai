//------------------------------------------------------------------------------
/// @file
/// @brief    Main
/// @author   nitorionedan
///
/// @copyright  Copyright 2016 KITIC

//------------------------------------------------------------------------------

#include "Keyboard.hpp"
#include "SceneMng.hpp"

#include <memory>
#include <random>
#include <Dxlib.h>
#include <fstream>


static int FrameStartTime;
static int FPS_60 = 1000 / 60;
static bool isFullSc = true;
static bool isPlay = true;

// @brief	�E�B���h�E�����ݒ�
static void Initialize();

// @brief	���ł��󂯕t����ݒ�
static void DynamicConfig();


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Initialize();
	std::unique_ptr<SceneMng>	sceneMng(new SceneMng);

	// �Q�[��--------------------------------------------------------------------------------------
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && isPlay)
	{
		// 60fps��ۂ����鏈��
		while (GetNowCount() - FrameStartTime < FPS_60) {} //< wait for about 1/60sec
		FrameStartTime = GetNowCount(); //< ���ݎ�����ۑ�
		
		Keyboard::Instance()->Update();
		DynamicConfig();
		sceneMng->Update();
		sceneMng->Draw();
	}

	DxLib_End();
	return 0;
}


void Initialize()
{
	SetGraphMode(320, 240, 32), ChangeWindowMode(isFullSc), DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);
	SetMainWindowText("ShinKai");
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
	SetWaitVSyncFlag(FALSE);        //< ���������M����҂��Ȃ�
	FrameStartTime = GetNowCount(); //< �J�n���Ԃ�ݒ�
	SetMouseDispFlag(TRUE);

	// �����V�[�h������
	std::random_device rnd;
	SRand(rnd());
	std::ofstream ofs("rndseed.dat");
	ofs << rnd();
	ofs.close();
}


void DynamicConfig()
{
	// Exit main loop
	if (Keyboard::Instance()->GetDown(KEY_INPUT_ESCAPE) == 1)
		isPlay = false;

	// Change window mode
	if (Keyboard::Instance()->GetDown(KEY_INPUT_F5) == 1)
	{
		isFullSc = !isFullSc;
		ChangeWindowMode(isFullSc);
	}
}
// EOF