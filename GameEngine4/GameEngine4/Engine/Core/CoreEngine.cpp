#include "CoreEngine.h"

std::unique_ptr<CoreEngine> CoreEngine::engineInstance = nullptr;

CoreEngine::CoreEngine() : window(nullptr), IsRunning(false), fps(120),
gameInterface(nullptr),currentSceneNum(0), camera(nullptr){
}


CoreEngine::~CoreEngine(){
	OnDestroy();
}

bool CoreEngine::OnCreate(std::string name_, int width_, int height_){
	Debug::DebugInit();
	Debug::SetSeverity(MessageType::TYPE_INFO);

	window = new Window();
	if (!window->OnCreate(name_, width_, height_)) {
		return IsRunning = false;
	}

	ShaderHandler::GetInstance()->CreateProgram("colourShader",
		"Engine/Shaders/ColourVertexShader.glsl",
		"Engine/Shaders/ColourFragmentShader.glsl");

	if (gameInterface) {
		if (!gameInterface->OnCreate()) {

		}
	}

	timer.Start();

	Debug::Info(" Engine Started ", " CoreEngine.cpp   ", __LINE__);
	return IsRunning = true;
}

void CoreEngine::Run(){
	while (IsRunning){
		timer.UpdateFrameTicks();
		Update(timer.GetDeltaTime());
		Render();
		SDL_Delay(timer.GetSleepTime(fps));
	}
	if (!IsRunning) OnDestroy();
}

CoreEngine* CoreEngine::GetInstance() {
	if (engineInstance.get() == nullptr) {
		engineInstance.reset(new CoreEngine);

	}
	return engineInstance.get();
}

bool CoreEngine::GetIsRunning() const{
	return IsRunning;
}

void CoreEngine::Update(float deltaTime_){
	if (gameInterface) {
		gameInterface->Update(deltaTime_);	
	}
}

void CoreEngine::Render(){
	glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	if (gameInterface) {
		gameInterface->Render();


	}
	SDL_GL_SwapWindow(window->GetWindow());
}

void CoreEngine::OnDestroy(){
	delete camera;
	camera = nullptr;

	delete window;
	window = nullptr;

	SDL_Quit();
	exit(0);
}

void CoreEngine::SetGameInterface(GameInterface* gameInterface_) {
	gameInterface = gameInterface_;
}

int CoreEngine::GetCurrentScene(){
	return currentSceneNum;
}

void CoreEngine::SetCurrentScene(int sceneNum_){
	currentSceneNum = sceneNum_;
}

void CoreEngine::Exit(){
	IsRunning = false;

}

Camera * CoreEngine::GetCamera() const{
	return camera;
}

void CoreEngine::SetCamera(Camera * camera_){
	camera = camera_;
}

glm::vec2 CoreEngine::GetWindowSize() const {
	return glm::vec2(window->GetWidth(), window->GetHeight());
}