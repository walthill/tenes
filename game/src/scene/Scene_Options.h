#ifndef SCENE_OPTIONS_H
#define SCENE_OPTIONS_H

#include "Scene.h"

class Scene_Options : public Scene
{
	public:
		void Init()			override;
		void Update()		override;
		void Draw()			override;
		void Unload()		override;
		void TryFinish()	override;

		virtual std::string GetName() override { return "Options"; }

	private:

};

#endif // !SCENE_LOGO_H
