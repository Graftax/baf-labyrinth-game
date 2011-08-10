#include "CGolem_Lava.h"
#include "../../../Wrappers/CSGD_TextureManager.h"
#include "../../../Messaging/MEventSystem.h"
#include "../../../Messaging/MMessageSystem.h"
#include "../CBaseObject.h"

void CGolem_Lava::LavaGolemSetup()
{
	SetGolemType(LAVA_GOLEM);
	SetImageID(CSGD_TextureManager::GetInstance()->LoadTexture( "resource/Sprites/Golems/LavaGolem.png" ));
	//basic golem events
	MEventSystem::GetInstance()->RegisterClient("ATTRACTORPLACED", this);
	MEventSystem::GetInstance()->RegisterClient("ATTRACTORREMOVED", this);
}
CGolem_Lava::CGolem_Lava(void)
{
	CBaseGolem::CBaseGolem();
	//basic Lava golem setup
	LavaGolemSetup();	
}
CGolem_Lava::CGolem_Lava(CBaseGolem* pGolem)
{
	CBaseGolem::CBaseGolem();
	//basic Lava golem setup
	LavaGolemSetup();
	//copy its positions
	this->SetIndexPosX(pGolem->GetIndexPosX());
	this->SetIndexPosY(pGolem->GetIndexPosY());
	this->SetPosX(pGolem->GetPosX());
	this->SetPosY(pGolem->GetPosY());
	this->SetLastPosX(pGolem->GetLastPosX());
	this->SetLastPosY(pGolem->GetLastPosY());
	//copy its states
	this->SetFlag_DirectionToMove(pGolem->GetFlag_DirectionToMove());
	this->SetFlag_MovementState(pGolem->GetFlag_MovementState());
}
CGolem_Lava::~CGolem_Lava(void)
{
	CBaseGolem::~CBaseGolem();
	//basic golem events
	MEventSystem::GetInstance()->UnregisterClient("ATTRACTORPLACED", this);
	MEventSystem::GetInstance()->UnregisterClient("ATTRACTORREMOVED", this);
}

void CGolem_Lava::Update(float fDT)
{
	CBaseGolem::Update(fDT);
	UpdateAI();
}
void CGolem_Lava::Render( int CameraPosX, int CameraPosY )
{
	CBaseGolem::Render(CameraPosX, CameraPosY);
}
bool CGolem_Lava::CheckCollision(IUnitInterface* pBase, bool nCanHandleCollision)
{
	if(!pBase)
		return false;

	//If the base collides with an object or entity leave
	bool Collided = CBaseGolem::CheckCollision(pBase, nCanHandleCollision);
	if(Collided)
		return Collided;

	//Do Lava Golem specific Collisions
	switch(pBase->m_nUnitType)
	{
	case OBJECT_OBJECT:
		{
			CBaseObject* temp = (CBaseObject*)pBase;
			
		}
		break;

	case OBJECT_ENTITY:
		{
			//Entities cannot walk-thro other entities
			if(!nCanHandleCollision)
				return true;

			CBaseEntity* temp = (CBaseEntity*)pBase;
			if(temp->GetType() == ENT_GOLEM)
			{
				CBaseGolem* temp = (CBaseGolem*)pBase;
				switch(temp->GetGolemType())
				{
				case WATER_GOLEM:
					{
						if(nCanHandleCollision)
						{
							//turn me into an Iron Golem
							MMessageSystem::GetInstance()->SendMsg(new msgChangeGolemType(this, IRON_GOLEM));
							//Get rid of the Water golem
							MMessageSystem::GetInstance()->SendMsg(new msgRemoveUnit(temp->m_nIdentificationNumber));
						}						
					}
					break;

				case ICE_GOLEM:
					{
						if(nCanHandleCollision)
						{
							//turn me into an Iron Golem
							MMessageSystem::GetInstance()->SendMsg(new msgChangeGolemType(this, IRON_GOLEM));
							//Get rid of the Ice golem
							MMessageSystem::GetInstance()->SendMsg(new msgRemoveUnit(temp->m_nIdentificationNumber));
						}						
					}
					break;
				};
			}
			return true;
		}
		break;
	};
	return false;
}
bool CGolem_Lava::CheckTileCollision(int TileID)
{
	//If the base collides with a tile leave
	bool Collided = CBaseGolem::CheckTileCollision(TileID);
	if(Collided)
		return Collided;

	//Do Lava Golem specific Collisions
	return false;
}
void CGolem_Lava::UpdateAI()
{
	CBaseGolem::UpdateAI();
}
void CGolem_Lava::HandleEvent( Event* _toHandle )
{
	CBaseGolem::HandleEvent(_toHandle);
	//Events only the Lava Golem responds to
}
bool CGolem_Lava::CanInteract(IUnitInterface* pBase)
{
	if(!pBase)
		return false;

	switch(pBase->m_nUnitType)
	{
	case OBJECT_OBJECT:
		{
			CBaseObject* temp = (CBaseObject*)pBase;
			return false;
		}
		break;

	case OBJECT_ENTITY:
		{
			CBaseEntity* temp = (CBaseEntity*)pBase;
			if(temp->GetType() == ENT_GOLEM)
			{
				CBaseGolem* temp = (CBaseGolem*)pBase;
				switch(temp->GetGolemType())
				{
				case WATER_GOLEM:
					{
						return true;
					}
					break;
				};
			}
		}
		break;
	};
	return false;
}
