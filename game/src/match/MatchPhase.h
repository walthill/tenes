#ifndef MATCH_PHASE_H
#define MATCH_PHASE_H

class MatchPhase
{
	public:
		MatchPhase();

        virtual bool Initialize();
        virtual void Start();
        virtual void Update();
        virtual bool Uninitialize();

	private:
};

#endif // !MATCH_PHASE_H
