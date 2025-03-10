#include "raylib.h"
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

void Game::UnloadGame() {
	delete gameInstance;
}

Game::~Game()
{
	if (mp_currentPhase != nullptr)
	{
		delete mp_currentPhase;
	}
	if (mp_nextPhase != nullptr)
	{
		delete mp_nextPhase;
	}
}

void Game::Update()
{
    UpdateMatchPhase();
	gameGrid.Update();
}

void Game::Render()
{
    RenderMatchPhase();
    gameGrid.Render();
	RenderUI();
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
	if (mp_currentPhase != nullptr)
	{
		delete mp_currentPhase;
	}

	mp_currentPhase = a_phase;
	m_currentSubPhase = PhaseSubSection::InitializePhase;
}

void Game::LoadScene(GameScreen a_screen)
{
    SceneManager::SetScene(a_screen);
}

void Game::AddPiece(bool a_isPlayer)
{
    if (a_isPlayer) {
		m_playerScore += c_addPieceScoreBonus;
    }
    else
    {
		m_enemyScore += c_addPieceScoreBonus;
    }
    matchUI.RefreshPieceUI(a_isPlayer);
    matchUI.UpdateScores(m_playerScore, m_enemyScore);
}

int Game::DoDiceRoll(bool a_isPlayer)
{
    auto val = GetRandomValue(0, 100);
    auto rollAmount = 0;
    if (val < 14) {
        rollAmount = 0;
    }
    else if (val > 14 && val < 14 + 43) {
        rollAmount = 1;
    }
    else
    {
        rollAmount = 2;
    }

    if (a_isPlayer)
    {
        if (m_playerNextRollBonus) 
        {
            rollAmount += c_bonusRollAmount;
        }
    }
    else
    {
		if (m_enemyNextRollBonus)
		{
            rollAmount += c_bonusRollAmount;
        }
    }

    auto amountStr = std::string();
    if (a_isPlayer) {
        amountStr = "Player Move -- Roll Amount: " + std::to_string(rollAmount);
    }
    else
    {
        amountStr = "Enemy Move -- Roll Amount: " + std::to_string(rollAmount);
    }
    TraceLog(LOG_TRACE, amountStr.c_str());

    if (a_isPlayer && m_playerNextRollBonus)
    {
        m_playerNextRollBonus = false;
    }
    if (!a_isPlayer && m_enemyNextRollBonus)
    {
        m_enemyNextRollBonus = false;
    }

	return rollAmount;
}

//TODO: add turn speed bonus (track the turn a piece is made visible?)
void Game::ApplyPieceScored(bool a_isPlayer)
{
    if (a_isPlayer) {
        m_playerScore += m_firstPlayerPieceScored ? c_firstPieceScoreAmount : c_secondPieceScoreAmount;
        if (!m_firstPlayerPieceScored)
        {
            m_firstPlayerPieceScored = true;
        }
    }
    else
    {
        m_enemyScore += m_firstEnemyPieceScored ? c_firstPieceScoreAmount : c_secondPieceScoreAmount;
		if (!m_firstEnemyPieceScored)
		{
			m_firstEnemyPieceScored = true;
		}
    }
    matchUI.UpdateScores(m_playerScore, m_enemyScore);
}

void Game::ApplyBonusMove(bool a_isPlayer)
{
    if (a_isPlayer) {
		m_playerNextRollBonus = true;
	}
    else
    {
        m_enemyNextRollBonus = true;
    }
}

void Game::ApplyBonusPoints(bool a_isPlayer)
{
    if (a_isPlayer) {
		m_playerScore += c_bonusPointsAmount;
	}
    else
    {
        m_enemyScore += c_bonusPointsAmount;
    }
    gameGrid.BonusPointsAwarded(a_isPlayer);
    matchUI.UpdateScores(m_playerScore, m_enemyScore);
}

bool Game::HasEnemyFinished()
{
    auto enemyPieces = gameGrid.GetEnemyPieces();
    if (!gameGrid.EnemyHasSecondPiece())
        return enemyPieces[0].HasScored();

    for (size_t i = 0; i < c_numPieces; i++)
    {
        if (!enemyPieces[i].HasScored())
            return false;
    }
    return true;
}

bool Game::HasPlayerFinished()
{
    auto playerPieces = gameGrid.GetPlayerPieces();
    if (!gameGrid.EnemyHasSecondPiece())
        return playerPieces[0].HasScored();

    for (size_t i = 0; i < c_numPieces; i++)
    {
        if (!playerPieces[i].HasScored())
            return false;
    }
    return true;
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

void Game::RenderMatchPhase()
{
    switch (m_currentSubPhase)
    {
        case PhaseSubSection::InitializePhase:
        case PhaseSubSection::Start:
        case PhaseSubSection::Update:
            mp_currentPhase->Render();
            break;
        default:
            break;
    }
}

void Game::RenderUI() {
    if(SceneManager::GetCurrentSceneType() != GAMEPLAY)
		return;
    	
    matchUI.Render();
}
