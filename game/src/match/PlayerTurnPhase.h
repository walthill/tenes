#ifndef PLAYER_TURN_PHASE_H
#define PLAYER_TURN_PHASE_H

#include "MatchPhase.h"

class PlayerTurnPhase : public MatchPhase
{
	public:
        PlayerTurnPhase();

        virtual bool Initialize() override;
        virtual void Start() override;
        virtual void Update() override;
        virtual bool Uninitialize() override;

};

#endif // !PLAYER_TURN_PHASE_H
