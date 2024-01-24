#ifndef SCENE_TITLE_H
#define SCENE_TITLE_H

#include "Scene.h"

class Scene_Title : public Scene
{
	public:
		void Init()		override;
		void Update()	override;
		void Draw()		override;
		void Unload()	override;
		void TryFinish()	override;

	private:


};

#endif // !SCENE_LOGO_H
