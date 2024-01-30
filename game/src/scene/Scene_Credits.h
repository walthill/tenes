#ifndef SCENE_CREDITS_H
#define SCENE_CREDITS_H

#include "Scene.h"

class Scene_Credits : public Scene
{
	public:
		void Init()			override;
		void Update()		override;
		void Draw()			override;
		void Unload()		override;
		void TryFinish()	override;

		const inline virtual std::string GetName() override { return "Credits"; }

	private:

};

#endif // !SCENE_LOGO_H
