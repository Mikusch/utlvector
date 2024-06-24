#include <sourcescramble>
#include <utlvector>

public void OnPluginStart()
{
	CreateVector();
	WorkWithAddress();
}

void CreateVector()
{
	CUtlVector vec = new CUtlVector(4); // sizeof(int) == 4
	
	for (int i = 0; i <= 3; ++i)
	{
		vec.AddToTail(i);
	}
	
	for (int i = 0; i < vec.Count(); ++i)
	{
		PrintToServer("Found int: %d", vec.Get(i));
	}
	
	delete vec;
}

void WorkWithAddress()
{
	Address adr = view_as<Address>(GetEntData(1, FindSendPropInfo("CTFPlayer", "m_hDisguiseWeaponList")));
	CUtlVector vec = CUtlVector.FromAddress(adr, 4); // sizeof(CTFWeaponBase) == 4
	
	for (int i = 0; i < vec.Count(); ++i)
	{
		Address handle = vec.Get(i);
		int weapon = LoadEntityFromHandleAddress(handle);
		
		PrintToServer("Found weapon entity: %d", weapon);
	}
	
	delete vec;
}
