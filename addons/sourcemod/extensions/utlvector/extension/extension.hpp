#ifndef _INCLUDE_SOURCEMOD_EXTENSION_H_
#define _INCLUDE_SOURCEMOD_EXTENSION_H_

#include "smsdk_ext.h"
#include <unordered_map>
#include <tier1/utlvector.h>

class CUtlVectorExt : public SDKExtension
{
public:
	/**
	 * @brief This is called after the initial loading sequence has been processed.
	 *
	 * @param error		Error message buffer.
	 * @param maxlen	Size of error message buffer.
	 * @param late		Whether or not the module was loaded after map load.
	 * @return			True to succeed loading, false to fail.
	 */
	 //virtual bool SDK_OnLoad(char* error, size_t maxlen, bool late);

	 /**
	  * @brief This is called right before the extension is unloaded.
	  */
	  //virtual void SDK_OnUnload();

	  /**
	   * @brief This is called once all known extensions have been loaded.
	   * Note: It is is a good idea to add natives here, if any are provided.
	   */
	virtual void SDK_OnAllLoaded();

	/**
	 * @brief Called when the pause state is changed.
	 */
	 //virtual void SDK_OnPauseChange(bool paused);

	 /**
	  * @brief this is called when Core wants to know if your extension is working.
	  *
	  * @param error		Error message buffer.
	  * @param maxlen	Size of error message buffer.
	  * @return			True if working, false otherwise.
	  */
	  //virtual bool QueryRunning(char *error, size_t maxlen);
public:
#if defined SMEXT_CONF_METAMOD
	/**
	 * @brief Called when Metamod is attached, before the extension version is called.
	 *
	 * @param error			Error buffer.
	 * @param maxlen		Maximum size of error buffer.
	 * @param late			Whether or not Metamod considers this a late load.
	 * @return				True to succeed, false to fail.
	 */
	//virtual bool SDK_OnMetamodLoad(ISmmAPI* ismm, char* error, size_t maxlen, bool late);

	/**
	 * @brief Called when Metamod is detaching, after the extension version is called.
	 * NOTE: By default this is blocked unless sent from SourceMod.
	 *
	 * @param error			Error buffer.
	 * @param maxlen		Maximum size of error buffer.
	 * @return				True to succeed, false to fail.
	 */
	 //virtual bool SDK_OnMetamodUnload(char *error, size_t maxlen);

	 /**
	  * @brief Called when Metamod's pause state is changing.
	  * NOTE: By default this is blocked unless sent from SourceMod.
	  *
	  * @param paused		Pause state being set.
	  * @param error			Error buffer.
	  * @param maxlen		Maximum size of error buffer.
	  * @return				True to succeed, false to fail.
	  */
	  //virtual bool SDK_OnMetamodPauseChange(bool paused, char *error, size_t maxlen);
#endif
};

#endif

namespace CUtlVectorNative
{
	static cell_t CUtlVector_Create(IPluginContext* pContext, const cell_t* params);
	static cell_t CUtlVector_Count(IPluginContext* pContext, const cell_t* params);
	static cell_t CUtlVector_Get(IPluginContext* pContext, const cell_t* params);
	static cell_t CUtlVector_AddToTail(IPluginContext* pContext, const cell_t* params);
	static cell_t CUtlVector_GetAddress64(IPluginContext* pContext, const cell_t* params);
	static cell_t CUtlVector_FromAddress64(IPluginContext* pContext, const cell_t* params);

	const sp_nativeinfo_t g_ExtensionNatives[] =
	{
			{"CUtlVector.CUtlVector", CUtlVector_Create},
			{"CUtlVector.Count", CUtlVector_Count},
			{"CUtlVector.Get", CUtlVector_Get},
			{"CUtlVector.AddToTail", CUtlVector_AddToTail},
			{"CUtlVector.GetAddress64", CUtlVector_GetAddress64},
			{"CUtlVector.FromAddress64", CUtlVector_FromAddress64},

			{nullptr, nullptr},
	};
}