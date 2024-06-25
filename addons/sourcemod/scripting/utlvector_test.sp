#include <sourcescramble>
#include <utlvector>

public void OnPluginStart()
{
	CreateVector();
}

void CreateVector()
{
	CUtlVector vec = new CUtlVector(); // sizeof(int) == 4

	for (int i = 0; i <= 3; ++i)
	{
		PrintToServer("Adding: %i", i);
		
		MemoryBlock block = new MemoryBlock(4);
		block.StoreToOffset(0, i, NumberType_Int32);
		vec.AddToTail(block.Address);
	}
	
	PrintToServer("Count() %d", vec.Count());
	
	for (int i = 0; i < vec.Count(); ++i)
	{
		int num = LoadFromAddress(vec.Get(i), NumberType_Int32);
		PrintToServer("Found: %d", num);
	}
	
	PrintToServer("%x", vec.GetAddress());
	
	any adr64[2];
	vec.GetAddress64(adr64);
	PrintToServer("%x %x", adr64[0], adr64[1]);
	
	delete vec;
}
