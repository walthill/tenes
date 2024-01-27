#ifndef MATCH_PHASE_H
#define MATCH_PHASE_H

#include <string>

class MatchPhase
{
	public:
		MatchPhase();

        virtual bool Initialize();
        virtual void Start();
        virtual void Update();
        virtual void Render();
        virtual bool Uninitialize();

        inline virtual std::string GetName() { return "MatchPhase"; }

	private:
};

#endif // !MATCH_PHASE_H
