#ifndef COIL_H
#define COIL_H

#include "../CBaseObject.h"

class COil : public CBaseObject
{
private:
	int m_nAnimID ;
	int m_nAnimImageID ;
	int m_nFireSoundID ;
	float m_fLifeDuration ;
	float m_fFireTimer ;
	bool m_bOnFire ;
	bool m_bIsOil ;
public:
	COil( bool bIsOil = true ) ;
	~COil() ;

	void Update(float fDT) ;

	void Render( int CameraPosX , int CameraPosY ) ;

	void SetLifeDuration( float life ) { m_fLifeDuration = life ; } ;
	void SetFireTimer( float timer ) { m_fFireTimer = timer ; } ;
	void SetOnFire( bool onFire ) ;

	float GetLifeDuration( void ) { return m_fLifeDuration ; } ;
	float GetFireTimer( void ) { return m_fFireTimer ; } ;
	bool GetOnFire( void ) { return m_bOnFire ; } ;

	bool GetIsOil( void ) { return m_bIsOil; }
	
	bool CheckCollision(IUnitInterface* pBase, bool nCanHandleCollision);
} ;

#endif