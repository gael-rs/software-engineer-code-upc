#include "GameNightFarm.h"

using namespace NightFarm;

int main() {
	
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	GameNightFarm^ gameNightFarm = gcnew GameNightFarm();

	Application::Run(gameNightFarm);
	
	return 0;
}