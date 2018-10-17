#include "../../../lib/ci_ext/object.hpp"
#include "../../../lib/ci_ext/Console.hpp"
#include <iostream>
#include <Windows.h>

#include "../../../lib/ci_ext/xinput.hpp" 
#include "../../../lib/gplib.h" 
#include "../../../lib/lib_windowDx.hpp"

#include "../Game/Scene.hpp"

#include <string>
#include <thread>

namespace gplib {
	namespace system {
		const char USERNAME[256] = "  ";
#ifdef _DEBUG
		const int	WINW = 1280;
		const int	WINH = 720;
		bool	WindowMode = true;
#else
		const int	WINW = GetSystemMetrics(SM_CXVIRTUALSCREEN);
		const int	WINH = GetSystemMetrics(SM_CYVIRTUALSCREEN);
		bool	WindowMode = false;
#endif
		int		KeyboardMode = 0;									//pad disable:1 pad enable:0
	}
}
int ci_ext::Object::uid_ = 0;
int ci_ext::Window::uid_ = 0;

//ルートオブジェクト
class Root : public ci_ext::Object
{
	int frame_;
public:
	Root()
		:
		Object("root"),
		frame_(0)
	{
	}

	void init(std::shared_ptr<ci_ext::Object> thisObjectPtr)
	{
		setWeakPtr(thisObjectPtr);

		insertAsChild(new Scene("Scene"));
	}

	void update() override
	{
		++frame_;

	}
	void render() override
	{


	}
	int frame() const { return frame_; }
};

//ゲームクラス
//ルートになるクラスで、mainで宣言する。
class App : public ci_ext::WindowDx
{
	int frame_;
	//ルートオブジェクト
	std::shared_ptr<Root> root;

public:
	App(HINSTANCE inst, const std::string& title, int w, int h,
		const char* classname = "default_class_name")
		:
		ci_ext::WindowDx(title, w, h, classname)
	{
		root = std::make_shared<Root>();
		root->init(root);
		gplib::camera::InitCamera(static_cast<float>(gplib::system::WINW) / 2.f, static_cast<float>(gplib::system::WINH) / 2.f, 0.f, 0.f);
		doMsgLoop();
	}

	void update() override
	{
		//gplib::graph::Draw_Clear();
		//ルートオブジェクトから処理を行
		root->updateWithChildren();
		root->renderWithChildren();

		//gplib::graph::Draw_Refresh();
	}

	//アクセサ
	int frame() const { return frame_; }

};

//エントリポイント
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInst, LPSTR lpszCmdLine, int nCmdShow)
{
	//アプリケーション終了時にメモリ情報をデバッグウインドウへ出力
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	ShowConsole();
	App a(GetModuleHandle(nullptr), "Astar", gplib::system::WINW, gplib::system::WINH);

	//  delete w0;
	std::cout << "=======================" << std::endl;
	return 0;
}
