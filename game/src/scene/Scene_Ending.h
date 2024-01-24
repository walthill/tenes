#ifndef SCENE_END_H
#define SCENE_END_H

#include "Scene.h"

class Scene_Ending : public Scene
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
