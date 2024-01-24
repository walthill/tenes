#ifndef SCREEN_H
#define SCREEN_H

typedef enum GameScreen { UNKNOWN = -1, LOGO = 0, TITLE, OPTIONS, GAMEPLAY, ENDING, CREDITS } GameScreen;

class Scene
{
	public:
		virtual void Init();
		virtual void Update()		=0;
		virtual void Draw()			=0;
		virtual void Unload()		=0;
		virtual void TryFinish()	=0;

		static int s_framesCounter;
		static int s_finishScreen;

	private:

};

#endif // !SCREEN_H
