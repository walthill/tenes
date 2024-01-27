#include "Game.h"

Game* Game::gameInstance = new Game;

void Game::LoadGame(int a_windowX, int a_windowY, int a_tileSize,
			Grid a_grid)
{
	auto inst = GM;

	//stats
	inst->windowX = a_windowX;
	inst->windowY = a_windowY;
	inst->tileSize = a_tileSize;
	
	//objects
	inst->gameGrid = a_grid;
    inst->mp_nextPhase = nullptr;
    inst->SetCurrentPhase(new PlayerTurnPhase());
}

void Game::Update()
{
    UpdateMatchPhase();
	gameGrid.Update();
}

void Game::Render()
{
	gameGrid.Render();
}

void Game::SetNextPhase(MatchPhase* a_phase)
{
	if ((int)m_currentSubPhase > (int)PhaseSubSection::Update)
		return;

    m_changePhase = true;
	mp_nextPhase = a_phase;
}

void Game::SetCurrentPhase(MatchPhase* a_phase)
{
	mp_currentPhase = a_phase;
	m_currentSubPhase = PhaseSubSection::InitializePhase;
}

void Game::UpdateMatchPhase()
{
    bool complete = false;
    switch (m_currentSubPhase)
    {
        case PhaseSubSection::InitializePhase:
            complete = mp_currentPhase->Initialize();
            if (complete)
            {
                m_currentSubPhase = PhaseSubSection::Start;
            }
            break;
        case PhaseSubSection::Start:
            mp_currentPhase->Start();
            m_currentSubPhase = PhaseSubSection::Update;
            break;
        case PhaseSubSection::Update:
            mp_currentPhase->Update();
            if (mp_nextPhase != nullptr)
            {
                m_currentSubPhase = PhaseSubSection::UninitializePhase;
            }
            break;
        case PhaseSubSection::UninitializePhase:
            complete = mp_currentPhase->Uninitialize();
            if (complete)
            {
                SetCurrentPhase(mp_nextPhase); 
                mp_nextPhase = nullptr;
            }
            break;
        default:
            break;
    }
}
