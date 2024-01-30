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

		const inline virtual std::string GetName() override { return "Ending"; }

	private:

};

#endif // !SCENE_LOGO_H
