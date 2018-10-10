#include "Input.hpp"
#include "InputKey.hpp"
#include "Camera.hpp"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	ChangeWindowMode(TRUE);
	SetBackgroundColor(100, 100, 100);
	SetGraphMode(1920, 1080, 32);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);

	SetDragFileValidFlag(TRUE);

	SetMouseDispFlag(TRUE);

	int windowX, windowY, colorBit;
	GetDefaultState(&windowX, &windowY, &colorBit);
	SetWindowSize(windowX, windowY);


	int model1 = MV1LoadModel("透過無双\\透過無双\\tkms_Blender.mv1");
	int model2 = MV1LoadModel("透過無双\\透過無双\\tkms_Blender.mv1");


	Camera* camera = new Camera();


	int mouseX, mouseY;
	int preMouseX, preMouseY;


	VECTOR model1VecUp = VGet(0.0f, 160.0f, 0.0f);
	VECTOR model1VecDown = VGet(0.0f, 0.0f, 0.0f);

	VECTOR model2VecUp = VGet(100.0f, 160.0f, 100.0f);
	VECTOR model2VecDown = VGet(100.0f, 0.0f, 100.0f);

	Vector2 model1Up(ConvWorldPosToScreenPos(model1VecUp).x, ConvWorldPosToScreenPos(model1VecUp).y);
	Vector2 model1Down(ConvWorldPosToScreenPos(model1VecDown).x, ConvWorldPosToScreenPos(model1VecDown).y);

	Vector2 model2Up(ConvWorldPosToScreenPos(model2VecUp).x, ConvWorldPosToScreenPos(model2VecUp).y);
	Vector2 model2Down(ConvWorldPosToScreenPos(model2VecDown).x, ConvWorldPosToScreenPos(model2VecDown).y);

	bool model1Flag = false;
	bool model2Flag = false;

	bool model1XMoveTouch = false;
	bool model1ZMoveTouch = false;
	bool model2XMoveTouch = false;
	bool model2ZMoveTouch = false;


	int i;
	VECTOR Pos1;
	VECTOR Pos2;

	float LINE_AREA_SIZE = 10000.0f;
	int LINE_NUM = 500;

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && !MouseData::GetClick(2))
	{
		SetUseZBufferFlag(TRUE);

		Pos1 = VGet(-LINE_AREA_SIZE / 2.0f, 0.0f, -LINE_AREA_SIZE / 2.0f);
		Pos2 = VGet(-LINE_AREA_SIZE / 2.0f, 0.0f, LINE_AREA_SIZE / 2.0f);
		for (i = 0; i <= LINE_NUM; i++)
		{
			DrawLine3D(Pos1, Pos2, GetColor(255, 255, 255));
			Pos1.x += LINE_AREA_SIZE / LINE_NUM;
			Pos2.x += LINE_AREA_SIZE / LINE_NUM;
		}

		Pos1 = VGet(-LINE_AREA_SIZE / 2.0f, 0.0f, -LINE_AREA_SIZE / 2.0f);
		Pos2 = VGet(LINE_AREA_SIZE / 2.0f, 0.0f, -LINE_AREA_SIZE / 2.0f);
		for (i = 0; i < LINE_NUM; i++)
		{
			DrawLine3D(Pos1, Pos2, GetColor(255, 255, 255));
			Pos1.z += LINE_AREA_SIZE / LINE_NUM;
			Pos2.z += LINE_AREA_SIZE / LINE_NUM;
		}

		SetUseZBufferFlag(FALSE);


		Vector2 model1Up(ConvWorldPosToScreenPos(model1VecUp).x - 5.0f, ConvWorldPosToScreenPos(model1VecUp).y);
		Vector2 model1Down(ConvWorldPosToScreenPos(model1VecDown).x + 5.0f, ConvWorldPosToScreenPos(model1VecDown).y);

		Vector2 model2Up(ConvWorldPosToScreenPos(model2VecUp).x - 5.0f, ConvWorldPosToScreenPos(model2VecUp).y);
		Vector2 model2Down(ConvWorldPosToScreenPos(model2VecDown).x + 5.0f, ConvWorldPosToScreenPos(model2VecDown).y);

		KeyData::UpDate();
		MouseData::Mouse_UpDate();
		MouseWheelData::MouseWheel_Update();
		GetMousePoint(&mouseX, &mouseY);

		camera->Process(mouseX, mouseY);

		MV1DrawModel(model1);
		MV1SetPosition(model1, model1VecDown);
		MV1DrawModel(model2);
		MV1SetPosition(model2, model2VecDown);

		if (model1Flag)
		{
			// X軸方向に関して
			for (int i = 0; i != 10; ++i)
			{
				DrawLine(ConvWorldPosToScreenPos(VGet(model1VecUp.x, (model1VecUp.y+i - (model1VecDown.y-i)) / 2.0f, model1VecUp.z)).x
					, ConvWorldPosToScreenPos(VGet(model1VecUp.x, (model1VecUp.y+i - (model1VecDown.y-i)) / 2.0f, model1VecUp.z)).y
					, ConvWorldPosToScreenPos(VGet(model1VecUp.x + 100.0f, (model1VecUp.y+i - (model1VecDown.y-i)) / 2.0f, model1VecUp.z)).x
					, ConvWorldPosToScreenPos(VGet(model1VecUp.x + 100.0f, (model1VecUp.y+i - (model1VecDown.y-i)) / 2.0f, model1VecUp.z)).y
					, GetColor(255, 0, 255));
			}
			if (!model1ZMoveTouch)
			{
				if ((ConvWorldPosToScreenPos(VGet(model1VecUp.x, (model1VecUp.y + i - (model1VecDown.y - i)) / 2.0f, model1VecUp.z)).x <= mouseX
					&& ConvWorldPosToScreenPos(VGet(model1VecUp.x + 100.0f, (model1VecUp.y + i - (model1VecDown.y - i)) / 2.0f, model1VecUp.z)).x >= mouseX)
					|| (ConvWorldPosToScreenPos(VGet(model1VecUp.x, (model1VecUp.y + i - (model1VecDown.y - i)) / 2.0f, model1VecUp.z)).x >= mouseX
						&& ConvWorldPosToScreenPos(VGet(model1VecUp.x + 100.0f, (model1VecUp.y + i - (model1VecDown.y - i)) / 2.0f, model1VecUp.z)).x <= mouseX))
				{
					if (MouseData::GetClick(0) >= 1)
					{
						model1XMoveTouch = true;
					}
				}
				if (model1XMoveTouch)
				{
					if (preMouseX > mouseX)
					{
						model1VecUp.x -= preMouseX - mouseX;
						model1VecDown.x -= preMouseX - mouseX;
					}
					if (preMouseX < mouseX)
					{
						model1VecUp.x += mouseX - preMouseX;
						model1VecDown.x += mouseX - preMouseX;
					}
				}
				if (MouseData::GetClick(0) == 0)
				{
					model1XMoveTouch = false;
				}
			}

			// Z軸方向に関して
			for (int i = 0; i != 10; ++i)
			{
				DrawLine(ConvWorldPosToScreenPos(VGet(model1VecUp.x, (model1VecUp.y + i - (model1VecDown.y - i)) / 2.0f, model1VecUp.z)).x
					, ConvWorldPosToScreenPos(VGet(model1VecUp.x, (model1VecUp.y + i - (model1VecDown.y - i)) / 2.0f, model1VecUp.z)).y
					, ConvWorldPosToScreenPos(VGet(model1VecUp.x, (model1VecUp.y + i - (model1VecDown.y - i)) / 2.0f, model1VecUp.z + 100.0f)).x
					, ConvWorldPosToScreenPos(VGet(model1VecUp.x, (model1VecUp.y + i - (model1VecDown.y - i)) / 2.0f, model1VecUp.z + 100.0f)).y
					, GetColor(0, 255, 255));	
			}
			if (!model1XMoveTouch)
			{
				if ((ConvWorldPosToScreenPos(VGet(model1VecUp.x, (model1VecUp.y + i - (model1VecDown.y - i)) / 2.0f, model1VecUp.z)).x <= mouseX
					&& ConvWorldPosToScreenPos(VGet(model1VecUp.x, (model1VecUp.y + i - (model1VecDown.y - i)) / 2.0f, model1VecUp.z + 100.0f)).x >= mouseX)
					|| (ConvWorldPosToScreenPos(VGet(model1VecUp.x, (model1VecUp.y + i - (model1VecDown.y - i)) / 2.0f, model1VecUp.z)).x >= mouseX
						&& ConvWorldPosToScreenPos(VGet(model1VecUp.x, (model1VecUp.y + i - (model1VecDown.y - i)) / 2.0f, model1VecUp.z + 100.0f)).x <= mouseX))
				{
					if (MouseData::GetClick(0) >= 1)
					{
						model1ZMoveTouch = true;
					}
				}
				if (model1ZMoveTouch)
				{
					if (preMouseX > mouseX)
					{
						model1VecUp.z += preMouseX - mouseX;
						model1VecDown.z += preMouseX - mouseX;
					}
					if (preMouseX < mouseX)
					{
						model1VecUp.z -= mouseX - preMouseX;
						model1VecDown.z -= mouseX - preMouseX;
					}
				}
				if (MouseData::GetClick(0) == 0)
				{
					model1ZMoveTouch = false;
				}
			}
			

			DrawCapsule3D(model1VecUp, model1VecDown, 50.0f, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), false);		// 当たり判定を確認用の表示テスト
		}
		
		if (model2Flag)
		{
			// X軸方向に関して
			for (int i = 0; i != 10; ++i)
			{
				DrawLine(ConvWorldPosToScreenPos(VGet(model2VecUp.x, (model2VecUp.y + i - (model1VecDown.y - i)) / 2.0f, model2VecUp.z)).x
					, ConvWorldPosToScreenPos(VGet(model2VecUp.x, (model2VecUp.y + i - (model1VecDown.y - i)) / 2.0f, model2VecUp.z)).y
					, ConvWorldPosToScreenPos(VGet(model2VecUp.x + 100.0f, (model2VecUp.y + i - (model1VecDown.y - i)) / 2.0f, model2VecUp.z)).x
					, ConvWorldPosToScreenPos(VGet(model2VecUp.x + 100.0f, (model2VecUp.y + i - (model1VecDown.y - i)) / 2.0f, model2VecUp.z)).y
					, GetColor(255, 0, 255));
			}
			if (!model1ZMoveTouch)
			{
				if ((ConvWorldPosToScreenPos(VGet(model2VecUp.x, (model2VecUp.y + i - (model1VecDown.y - i)) / 2.0f, model2VecUp.z)).x <= mouseX
					&& ConvWorldPosToScreenPos(VGet(model2VecUp.x + 100.0f, (model2VecUp.y + i - (model1VecDown.y - i)) / 2.0f, model2VecUp.z)).x >= mouseX)
					|| (ConvWorldPosToScreenPos(VGet(model2VecUp.x, (model2VecUp.y + i - (model1VecDown.y - i)) / 2.0f, model2VecUp.z)).x >= mouseX
						&& ConvWorldPosToScreenPos(VGet(model2VecUp.x + 100.0f, (model2VecUp.y + i - (model1VecDown.y - i)) / 2.0f, model2VecUp.z)).x <= mouseX))
				{
					if (MouseData::GetClick(0) >= 1)
					{
						model2XMoveTouch = true;
					}
				}
				if (model2XMoveTouch)
				{
					if (preMouseX > mouseX)
					{
						model2VecUp.x -= preMouseX - mouseX;
						model2VecDown.x -= preMouseX - mouseX;
					}
					if (preMouseX < mouseX)
					{
						model2VecUp.x += mouseX - preMouseX;
						model2VecDown.x += mouseX - preMouseX;
					}
				}
				if (MouseData::GetClick(0) == 0)
				{
					model2XMoveTouch = false;
				}
			}

			// Z軸方向に関して
			for (int i = 0; i != 10; ++i)
			{
				DrawLine(ConvWorldPosToScreenPos(VGet(model2VecUp.x, (model2VecUp.y + i - (model1VecDown.y - i)) / 2.0f, model2VecUp.z)).x
					, ConvWorldPosToScreenPos(VGet(model2VecUp.x, (model2VecUp.y + i - (model1VecDown.y - i)) / 2.0f, model2VecUp.z)).y
					, ConvWorldPosToScreenPos(VGet(model2VecUp.x, (model2VecUp.y + i - (model1VecDown.y - i)) / 2.0f, model2VecUp.z + 100.0f)).x
					, ConvWorldPosToScreenPos(VGet(model2VecUp.x, (model2VecUp.y + i - (model1VecDown.y - i)) / 2.0f, model2VecUp.z + 100.0f)).y
					, GetColor(0, 255, 255));
			}
			if (!model2XMoveTouch)
			{
				if ((ConvWorldPosToScreenPos(VGet(model2VecUp.x, (model2VecUp.y + i - (model1VecDown.y - i)) / 2.0f, model2VecUp.z)).x <= mouseX
					&& ConvWorldPosToScreenPos(VGet(model2VecUp.x, (model2VecUp.y + i - (model1VecDown.y - i)) / 2.0f, model2VecUp.z + 100.0f)).x >= mouseX)
					|| (ConvWorldPosToScreenPos(VGet(model2VecUp.x, (model2VecUp.y + i - (model1VecDown.y - i)) / 2.0f, model2VecUp.z)).x >= mouseX
						&& ConvWorldPosToScreenPos(VGet(model2VecUp.x, (model2VecUp.y + i - (model1VecDown.y - i)) / 2.0f, model2VecUp.z + 100.0f)).x <= mouseX))
				{
					if (MouseData::GetClick(0) >= 1)
					{
						model2ZMoveTouch = true;
					}
				}
				if (model2ZMoveTouch)
				{
					if (preMouseX > mouseX)
					{
						model2VecUp.z += preMouseX - mouseX;
						model2VecDown.z += preMouseX - mouseX;
					}
					if (preMouseX < mouseX)
					{
						model2VecUp.z -= mouseX - preMouseX;
						model2VecDown.z -= mouseX - preMouseX;
					}
				}
				if (MouseData::GetClick(0) == 0)
				{
					model2ZMoveTouch = false;
				}
			}

			DrawCapsule3D(model2VecUp, model2VecDown, 50.0f, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), false);		// 当たり判定を確認用の表示テスト
		}


		DrawBox(model1Up.x, model1Up.y, model1Down.x, model1Down.y, 255, false);
		DrawBox(model2Up.x, model2Up.y, model2Down.x, model2Down.y, 255, false);

		DrawLine(model2Up.x, model2Up.y, mouseX, mouseY, 255);
		DrawLine(model2Down.x, model2Down.y, mouseX, mouseY, 255);


		if (MouseData::GetClick(0) == 1)
		{
			if (!model1Flag)
			{
				if ((model1Up.x <= mouseX && model1Down.x >= mouseX)
					|| (model1Up.x >= mouseX && model1Down.x <= mouseX))
				{
					model1Flag = true;
					model2Flag = false;
				}
			}

			if (!model2Flag)
			{
				if ((model2Up.x <= mouseX && model2Down.x >= mouseX)
					|| (model2Up.x >= mouseX && model2Down.x <= mouseX))
				{
					model2Flag = true;
					model1Flag = false;
				}
			}
		}

		preMouseX = mouseX;
		preMouseY = mouseY;
	}


	MV1DeleteModel(model2);
	MV1DeleteModel(model1);


	delete camera;


	DxLib_End();
	return 0;
}