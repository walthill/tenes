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

	private:

};

#endif // !SCENE_LOGO_H
