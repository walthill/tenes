#ifndef SCENE_GAME_H
#define SCENE_GAME_H

#include "Scene.h"

class Scene_Game : public Scene
{
	public:
		void Init()			override;
		void Update()		override;
		void Draw()			override;
		void Unload()		override;
		void TryFinish()	override;

		virtual std::string GetName() override { return "Game"; }

	private:
};

#endif // !SCENE_LOGO_H
