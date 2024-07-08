#pragma once
#include "GamePresenter.h"

namespace NightFarm {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Threading;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de GameNightFarm
	/// </summary>
	public ref class GameNightFarm : public System::Windows::Forms::Form
	{
	public:
		GameNightFarm(void)
		{
			this->Icon = gcnew System::Drawing::Icon("./assets/sprites/logo/icon.ico");
			this->ClientSize = System::Drawing::Size(1024, 793);
			InitializeComponent();
			//
			//TODO: agregar código de constructor aquí
			//
			skipThread = finishThread = false;

			srand(time(nullptr));
			g = this->CreateGraphics();
			gamePresenter = new GamePresenter();

			context = BufferedGraphicsManager::Current;
			buffer = context->Allocate(g, this->ClientRectangle);

			sequenceThread = gcnew Thread(gcnew ThreadStart(this, &GameNightFarm::handleThredPresenter));

			timerInitializer = gcnew Forms::Timer();
			timerInitializer->Interval = 200;

			timerMainGame = gcnew Forms::Timer();
			timerMainGame->Interval = 200;

			timerInitializer->Tick += gcnew EventHandler(this, &GameNightFarm::handleTickInitializer);
			timerInitializer->Enabled = false;

			timerMainGame->Tick += gcnew EventHandler(this, &GameNightFarm::handleTickMainGame);
			timerMainGame->Enabled = false;

			this->MouseClick += gcnew MouseEventHandler(this, &GameNightFarm::handleClickButtons);
			this->MouseClick += gcnew MouseEventHandler(this, &GameNightFarm::handleClickInitialGame);
			this->MouseClick += gcnew MouseEventHandler(this, &GameNightFarm::handleClickMainGame);
			this->MouseMove += gcnew MouseEventHandler(this, &GameNightFarm::handleHoverButtons);
			this->MouseMove += gcnew MouseEventHandler(this, &GameNightFarm::handleHoverInitialGame);
			this->KeyPress += gcnew KeyPressEventHandler(this, &GameNightFarm::handleKeyPress);
			this->KeyDown += gcnew KeyEventHandler(this, &GameNightFarm::handleKeyDown);
			this->KeyUp += gcnew KeyEventHandler(this, &GameNightFarm::handleKeyUpMainGame);
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~GameNightFarm()
		{
			if (components)
			{
				delete components;
			}
			delete context;
			// delete gamePresenter;
		}

	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>
		System::ComponentModel::Container^ components;

		GamePresenter* gamePresenter;

		BufferedGraphicsContext^ context;
		BufferedGraphics^ buffer;

		Forms::Timer^ timerInitializer;
		Forms::Timer^ timerMainGame;

		Graphics^ g;
		Thread^ sequenceThread;
		bool skipThread, finishThread;


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// GameNightFarm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Cursor = System::Windows::Forms::Cursors::Default;
			this->Margin = System::Windows::Forms::Padding(0);
			this->Name = L"GameNightFarm";
			this->Text = L"NightFarm";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &GameNightFarm::handleCloseForm);
			this->Load += gcnew System::EventHandler(this, &GameNightFarm::handleLoad);
			this->ResizeEnd += gcnew System::EventHandler(this, &GameNightFarm::handleResize);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &GameNightFarm::handlePaintInitial);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &GameNightFarm::handleKeyUp);
			this->ResumeLayout(false);			

		}
#pragma endregion

#pragma region Handlers Listener Events
		// Handles Listener
	private:
		System::Void handlePaintInitial(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
			if (!sequenceThread->IsAlive && !finishThread) sequenceThread->Start();
			else if (finishThread && gamePresenter->getIsShowedMenu()) {

				gamePresenter->showMenu(buffer->Graphics);

				buffer->Render(g);

			}
			else if (finishThread && gamePresenter->getIsShowedInitialGame()) {
				gamePresenter->showGameInitializer(buffer->Graphics);

				buffer->Render(g);
			}
		}

		System::Void handleLoad(System::Object^ sender, System::EventArgs^ e) {
			gamePresenter->initializeButtons(g);
		}

		System::Void handleClickButtons(System::Object^ sender, MouseEventArgs^ e) {

			bool buttonClicked = gamePresenter->chooseButton(buffer->Graphics, e->Location);
			bool buttonBackClicked = gamePresenter->clickButtonBack(buffer->Graphics, e->Location);

			if (buttonClicked || buttonBackClicked) {
				if (gamePresenter->getIsShowedMenu()) {
					timerInitializer->Enabled = false;
					gamePresenter->showMenu(buffer->Graphics);
				}
				if (gamePresenter->getIsShowedInstruccions()) {
					timerInitializer->Enabled = true;
					gamePresenter->showInstruccions(buffer->Graphics);
				}
				if (gamePresenter->getIsShowedExit()) {
					timerInitializer->Enabled = true;
					gamePresenter->showExit(buffer->Graphics);
				}
				if (gamePresenter->getIsShowedCredits()) {
					timerInitializer->Enabled = true;
				}

				buffer->Render(g);
			}

		}

		System::Void handleHoverButtons(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
			if (!gamePresenter->getIsShowedInitialGame()) {
				bool buttonHovered = gamePresenter->hoverButton(g, e->Location);
				if (buttonHovered) this->Cursor = Cursors::Hand;
				else if (this->Cursor == Cursors::Hand) this->Cursor = Cursors::Default;
			}
		}

		System::Void handleClickInitialGame(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
			if (gamePresenter->getIsShowedInitialGame()) {
				bool inputFocus = gamePresenter->getGameInitializer()->focusInput(e->Location);
				bool clickedCombo = gamePresenter->getGameInitializer()->clickCombo(e->Location);
				bool isClicked = gamePresenter->getGameInitializer()->clickButtonStart(g, e->Location);

				if (isClicked) {
					timerMainGame->Enabled = true;
					gamePresenter->setIsShowedInitialGame(false);
				}

				if (inputFocus || clickedCombo) {
					BufferedGraphicsContext^ context = BufferedGraphicsManager::Current;
					BufferedGraphics^ buffer = context->Allocate(g, this->ClientRectangle);
					buffer->Graphics->Clear(Color::White);

					gamePresenter->showGameInitializer(buffer->Graphics);
					gamePresenter->getGameInitializer()->clickButtonStart(buffer->Graphics, e->Location);

					buffer->Render(g);

					delete context;
					delete buffer;
				}
			}
		}
		System::Void handleHoverInitialGame(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
			if (gamePresenter->getIsShowedInitialGame()) {
				bool comboHovered = gamePresenter->getGameInitializer()->hoverCombo(e->Location);
				bool inputFocus = gamePresenter->getGameInitializer()->hoverInput(e->Location);
				bool buttonHovered = gamePresenter->getGameInitializer()->hoverButtonStart(g, e->Location);
				bool buttonGamePresenterHovered = gamePresenter->hoverButtonBack(g, e->Location);

				if (inputFocus) this->Cursor = Cursors::IBeam;
				else if (comboHovered || buttonHovered || buttonGamePresenterHovered) this->Cursor = Cursors::Hand;
				else if (this->Cursor == Cursors::IBeam || this->Cursor == Cursors::Hand) this->Cursor = Cursors::Default;
			}
		}

		System::Void handleClickMainGame(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
			if (gamePresenter->getGameInitializer()->getGameController()->getRunned()) {
				gamePresenter->getGameInitializer()->getGameController()->handleClick(buffer->Graphics, 
					e->Location);
			}
		}
		System::Void handleThredPresenter() {
			// Show Logo

			clock_t startTime = clock();
			int seconds = 0;

			gamePresenter->showLogo(g);

			do {
				seconds = (clock() - startTime) / CLOCKS_PER_SEC;
			} while (seconds < 3 && !skipThread);

			if (skipThread) skipThread = false;

			// Show Credits

			startTime = clock();
			seconds = 0;

			this->Invoke(gcnew MethodInvoker(this, &GameNightFarm::showCredits));

			do {
				seconds = (clock() - startTime) / CLOCKS_PER_SEC;
			} while (seconds < 3 && !skipThread);

			if (skipThread) skipThread = false;

			// Show Menu

			this->Invoke(gcnew MethodInvoker(this, &GameNightFarm::showMenu));

			finishThread = true;
		}

		System::Void handleKeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
			if (sequenceThread->IsAlive && e->KeyCode == Keys::Enter) skipThread = true;
		}

		System::Void handleKeyUpMainGame(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {

			if (gamePresenter->getGameInitializer()->getGameController()->getRunned()) {
				gamePresenter->getGameInitializer()->getGameController()->handleKeyUp(
					e->KeyCode == Keys::Space ? ActionFarmer::PlayFlashLight : ActionFarmer::Nothing);
			}
		}

		System::Void handleCloseForm(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
			if (sequenceThread->IsAlive) sequenceThread->Abort();
			if (timerMainGame->Enabled) timerMainGame->Enabled = false;
		}

		System::Void handleTickInitializer(System::Object^ sender, System::EventArgs^ e) {

			buffer->Graphics->Clear(Color::White);

			if (gamePresenter->getIsShowedInstruccions()) gamePresenter->showInstruccions(buffer->Graphics);
			if (gamePresenter->getIsShowedExit()) {
				gamePresenter->showExit(buffer->Graphics);
			};
			if (gamePresenter->getIsShowedCredits()) {
				gamePresenter->showCredits(buffer->Graphics);
			}

			gamePresenter->paintSequences(buffer->Graphics);

			if (gamePresenter->getSequenceExit()->getIsFinished()) {
				timerInitializer->Enabled = false;
				gamePresenter->showMessageExit(buffer->Graphics);
				Application::Exit();
			}

			buffer->Render(g);
		}


		System::Void handleTickMainGame(System::Object^ sender, System::EventArgs^ e) {

			buffer->Graphics->Clear(Color::White);

			gamePresenter->getGameInitializer()->getGameController()->showGame(buffer->Graphics);

			buffer->Render(g);

		}

		System::Void handleKeyPress(System::Object^ sender, KeyPressEventArgs^ e) {
			if (gamePresenter->getIsShowedInitialGame()) {
				BufferedGraphicsContext^ context = BufferedGraphicsManager::Current;
				BufferedGraphics^ buffer = context->Allocate(g, this->ClientRectangle);
				buffer->Graphics->Clear(Color::White);

				gamePresenter->getGameInitializer()->handleInput(e->KeyChar);
				gamePresenter->showGameInitializer(buffer->Graphics);

				buffer->Render(g);

				delete context;
				delete buffer;
			}
		}

		System::Void handleKeyDown(System::Object^ sender, KeyEventArgs^ e) {
			if (gamePresenter->getGameInitializer()->getGameController()->getRunned()) {
				Direction* direction = new Direction;

				if (e->KeyCode == Keys::W) *direction = Direction::Up;
				else if (e->KeyCode == Keys::A) *direction = Direction::Left;
				else if (e->KeyCode == Keys::D) *direction = Direction::Right;
				else if (e->KeyCode == Keys::S) *direction = Direction::Down;

				if (e->KeyCode == Keys::E) gamePresenter->getGameInitializer()->getGameController()->handleActionFarmer(ActionFarmer::KeyForSale);

				if (e->KeyCode == Keys::Q) gamePresenter->getGameInitializer()->getGameController()->handleActionFarmer(ActionFarmer::KeyForBuy);

				gamePresenter->getGameInitializer()->getGameController()->handleDirection(g, *direction);

				delete direction;
			}
		}
#pragma endregion
#pragma region Functions UI
	private:
		System::Void showMenu() {
			timerInitializer->Enabled = false;
			gamePresenter->showMenu(buffer->Graphics);

			buffer->Render(g);
		}
		System::Void showCredits() {
			timerInitializer->Enabled = true;

			gamePresenter->showCredits(buffer->Graphics);
			buffer->Render(g);
		}
#pragma endregion
	private: System::Void handleResize(System::Object^ sender, System::EventArgs^ e) {
		
		buffer = context->Allocate(g, this->ClientRectangle);
	}
};
}
