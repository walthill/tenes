#ifndef PLAYER_TURN_PHASE_H
#define PLAYER_TURN_PHASE_H

#include "MatchPhase.h"

class Piece;

class PlayerTurnPhase : public MatchPhase
{
	public:
        PlayerTurnPhase();

        virtual bool Initialize() override;
        virtual void Start() override;
        virtual void Update() override;
        virtual void Render() override;
        virtual bool Uninitialize() override;

        virtual std::string GetName() override { return "PlayerTurnPhase"; }

    private:
        float m_waitAfterRollTime;
        float m_timer;
        bool m_rollComplete;
        int m_rollAmount;
};

#endif // !PLAYER_TURN_PHASE_H
