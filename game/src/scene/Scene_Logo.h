#ifndef SCENE_LOGO_H
#define SCENE_LOGO_H

#include "Scene.h"

class Scene_Logo : public Scene
{
	public:
		void Init()			override;
		void Update()		override;
		void Draw()			override;
		void Unload()		override;
		void TryFinish()	override;

		virtual std::string GetName() { return "Logo"; }

	private:
		int m_lettersCount;
		int m_logoPositionX;
		int m_logoPositionY;
		int m_topSideRecWidth;
		int m_leftSideRecHeight;
		int m_bottomSideRecWidth;
		int m_rightSideRecHeight;
		int m_state;
		float m_alpha;

};

#endif // !SCENE_LOGO_H
