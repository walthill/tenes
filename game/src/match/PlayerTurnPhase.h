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
        virtual void Render() override;
        virtual bool Uninitialize() override;

        const inline virtual std::string GetName() override { return "PlayerTurnPhase"; }

    private:
        const int c_defaultMinRollAmount = 0;
        const int c_defaultMaxRollAmount = 2;
        
        float m_waitAfterRollTime;
        float m_timer;
        bool m_rollComplete;
        int m_rollAmount;
        bool m_turnEnd;
        float m_timeToEndTurn;
        bool m_movingFirstPiece = true;
        bool m_pieceMoving = false;
        bool m_moveForward = false;

        void CheckForBonusTile();
        void ApplyBonusMove();
        void ApplyBonusPiece();
        void ApplyBonusPoints();
};

#endif // !PLAYER_TURN_PHASE_H
