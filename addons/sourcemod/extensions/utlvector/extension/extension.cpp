
#include "extension.hpp"

constexpr auto cutl_vector_handle_name = "CUtlVector";

HandleType_t g_utl_vector_handle_type;

class CUtlVectorHandler : public IHandleTypeDispatch
{
public:
	void OnHandleDestroy(HandleType_t type, void* object)
	{
		if (type == g_utl_vector_handle_type)
		{
			delete reinterpret_cast<CUtlVector<void*>*>(object);
		}
	}
};

CUtlVectorHandler g_utl_vector_handler;

CUtlVectorExt g_ext;
SMEXT_LINK(&g_ext);

template<typename T>
inline T* GetObjFromHandle(HandleType_t type, cell_t cellhandle, IPluginContext* pContext)
{
	Handle_t handle = (Handle_t)cellhandle;
	HandleError hndlError;
	HandleSecurity hndlSecurity;

	hndlSecurity.pOwner = pContext->GetIdentity();
	hndlSecurity.pIdentity = myself->GetIdentity();

	T* obj = nullptr;
	if ((hndlError = g_pHandleSys->ReadHandle(handle, type, &hndlSecurity, (void**)&obj)) != HandleError_None)
	{
		if (!pContext)
		{
			smutils->LogError(myself, "Invalid handle %x (error %d)", handle, hndlError);
		}
		else
		{
			pContext->ThrowNativeError("Invalid handle %x (error %d)", handle, hndlError);
		}

		return nullptr;
	}

	return obj;
}

void CUtlVectorExt::SDK_OnAllLoaded()
{
	if (!handlesys->FindHandleType(cutl_vector_handle_name, &g_utl_vector_handle_type))
	{
		g_utl_vector_handle_type = handlesys->CreateType(cutl_vector_handle_name, &g_utl_vector_handler, 0, nullptr, nullptr, myself->GetIdentity(), nullptr);
	}

	sharesys->AddNatives(myself, CUtlVectorNative::g_ExtensionNatives);
	sharesys->RegisterLibrary(myself, "utlvector");
}

namespace CUtlVectorNative
{
	static cell_t CUtlVector_Create(IPluginContext* pContext, const cell_t* params)
	{
		uintptr_t address = static_cast<uintptr_t>(params[1]) | (static_cast<uintptr_t>(params[2]) << 32);
		CUtlVector<void*>* vec = reinterpret_cast<CUtlVector<void*>*>(address);
		return handlesys->CreateHandle(g_utl_vector_handle_type, vec, pContext->GetIdentity(), myself->GetIdentity(), NULL);
	}

	static cell_t CUtlVector_Get(IPluginContext* pContext, const cell_t* params)
	{
		CUtlVector<void*>* vec = GetObjFromHandle<CUtlVector<void*>>(g_utl_vector_handle_type, params[1], pContext);
		if (vec)
		{
			int index = params[2];

			if (vec->Count() <= index)
			{
				return pContext->ThrowNativeError("Index %d out of bounds.", index);
			}

			void* elementPtr = (*vec)[index];
			return reinterpret_cast<uintptr_t>(elementPtr);
		}

		return 0;
	}

	static cell_t CUtlVector_Count(IPluginContext* pContext, const cell_t* params)
	{
		CUtlVector<void*>* vec = GetObjFromHandle<CUtlVector<void*>>(g_utl_vector_handle_type, params[1], pContext);
		if (vec)
		{
			return vec->Count();
		}
		
		return 0;
	}

	static cell_t CUtlVector_AddToTail(IPluginContext* pContext, const cell_t* params)
	{
		CUtlVector<void*>* vec = GetObjFromHandle<CUtlVector<void*>>(g_utl_vector_handle_type, params[1], pContext);
		if (vec)
		{
			void* value = reinterpret_cast<void*>(params[2]);
			vec->AddToTail(value);
			return 1;
		}

		return 0;
	}

	static cell_t CUtlVector_GetAddress64(IPluginContext* pContext, const cell_t* params)
	{
		CUtlVector<void*>* vec = GetObjFromHandle<CUtlVector<void*>>(g_utl_vector_handle_type, params[1], pContext);
		if (vec)
		{
			uintptr_t* address;
			pContext->LocalToPhysAddr(params[2], reinterpret_cast<cell_t**>(&address));
			*address = reinterpret_cast<uintptr_t>(vec);
		}

		return 0;
	}

	static cell_t CUtlVector_FromAddress64(IPluginContext* pContext, const cell_t* params)
	{
		uintptr_t* address;
		pContext->LocalToPhysAddr(params[1], reinterpret_cast<cell_t**>(&address));

		CUtlVector<void*>* vec = reinterpret_cast<CUtlVector<void*>*>(address);
		return handlesys->CreateHandle(g_utl_vector_handle_type, vec, pContext->GetIdentity(), myself->GetIdentity(), NULL);
	}
}
