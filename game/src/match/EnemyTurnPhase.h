#ifndef ENEMY_TURN_PHASE_H
#define ENEMY_TURN_PHASE_H

#include "MatchPhase.h"

class EnemyTurnPhase : public MatchPhase
{
    public:
        EnemyTurnPhase();

        virtual bool Initialize() override;
        virtual void Start() override;
        virtual void Update() override;
        virtual void Render() override;
        virtual bool Uninitialize() override;

        const inline virtual std::string GetName() override { return "EnemyTurnPhase"; }

    private:
        float m_timeUntilRoll;
        float m_waitAfterRollTime;
        float m_timer;
        bool m_rollComplete;
        int m_rollAmount;
        bool m_turnEnd;
        float m_timeToEndTurn;
        bool m_movingFirstPiece = true;

        void CheckForBonusTile();
        void ApplyBonusMove();
        void ApplyBonusPiece();
        void ApplyBonusPoints();
};

#endif // !ENEMY_TURN_PHASE_H
