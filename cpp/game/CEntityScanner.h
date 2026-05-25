#pragma once

struct CEntityScanner {
protected:
	void* vtable;

public:
	int field_4;
	unsigned int m_nCount;
	struct CEntity* m_apEntities[16];
	struct CEntity *field_4C;
};