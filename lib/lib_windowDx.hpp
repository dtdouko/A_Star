#pragma once

#include "lib_window.hpp"
#include "../lib/gplib.h"

namespace ci_ext
{

class WindowDx : public Window
{
public:
  WindowDx(const std::string& title, int w, int h,
    const char* classname = "default_class_name)")
    :
    Window(title, w, h, classname)
  {
    using namespace gplib;
    using namespace gplib::system;
    using namespace gplib::input;

    hWnd = windowhandle();
    InitDx();
    //resource table init
    //void Draw_InitImgTable();
    //void Draw_InitFont();
    //Draw_InitImgTable();
    //Draw_InitFont();
    //player input init

    void InitPlayerInput();
    InitPlayerInput(); 
    
    //for (int i = 0; i < system::PLAYER_NUM; i++)
      //input::InitKeyInfo(i);
    //stage flag init
    //void InitFlagStage();
    //InitFlagStage();
    //math::RandomInit();
    //sound com init
//#ifdef USE_DIRECTSOUND
//    se::DSound_Init();
//#endif
//#ifdef USE_DIRECTSHOW
//    bgm::DShow_Init();
//#endif
    //srand((unsigned)::time(NULL));
    //time::Time_CheckTimer();
    camera::InitCamera(WINW / 2.0f, WINH / 2.0f, 0, 0);
  }

  ~WindowDx() override
  {
    using namespace gplib;
    using namespace gplib::system;
    using namespace gplib::input;
    //void Draw_DelImgTable();
    //void Draw_DeleteFont();
    void DeletePlayerInput();

    //Draw_DelImgTable();
    //Draw_DeleteFont();
    //sound com release
//#ifdef CI_EXT
//    ci_ext::dsRelease();
//#endif
//#ifdef USE_DIRECTSOUND
//    se::DSound_Del();
//
//#endif
//#ifdef USE_DIRECTSHOW
//    bgm::DShow_Del();
//#endif
    //directx release
    DelDx();
    //pad delete
    DeletePlayerInput();
  }
  void update_before() override
  {
	gplib::XInput::CheckKey();
    gplib::input::CheckKey();

	//gplib::graph::Draw_2DClear();
	gplib::graph::Draw_Clear();
  }
  void update_after()  override
  {
    gplib::camera::StepCamera();
    //サウンド終了チェック
//#ifdef USE_DIRECTSHOW
//    gplib::bgm::DShow_EndCheck();
//#endif
//#ifdef USE_DIRECTSOUND
//    gplib::se::DSound_EndCheck();
//#endif
    //ホイールdeltaクリア
    void ClearWheelDelta();
    ClearWheelDelta();
	gplib::graph::Draw_3DUpdate();
    
	gplib::graph::Draw_2DRefresh();
	//gplib::graph::Draw_Refresh();

    //TIMER更新
    //gplib::system::FrameTime = gplib::time::Time_Update();
  }

};


}
