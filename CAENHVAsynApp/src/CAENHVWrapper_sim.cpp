#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <map>

#define CAENHVLIB /* so we get dllexport rather than dllimport on windows in CAENHVWrapper.h */
#include "CAENHVWrapper.h"

#define NUM_SLOTS 2
#define NUM_CH 2
#define BOARDNAME "s1535s"

static unsigned g_call_out = 0;
static unsigned g_error_on_call = 1000;

// note: must use malloc() not new[] to allocate memory as client will use free()

struct chan_t
{
    std::string name;
};

typedef std::map<int,chan_t> slot_t;
typedef std::map<int,slot_t> crate_t;
static std::map<std::string, crate_t> crate_info;

CAENHVLIB_API char *CAENHVGetError(const char *SystemName)
{
    return const_cast<char*>("CAENHVWrapper_sim error");
}

CAENHVLIB_API char *CAENHV_GetError(int handle)
{
    return CAENHVGetError("");
}

CAENHVLIB_API CAENHVRESULT  CAENHVInitSystem(const char *SystemName, int LinkType, void *Arg, const char *UserName, const char *Passwd)
{
     return CAENHV_OK;
}

CAENHVLIB_API CAENHVRESULT CAENHV_InitSystem(CAENHV_SYSTEM_TYPE_t system, int LinkType, void *Arg, const char *UserName, const char *Passwd,  int *handle)
{
     *handle = 0;
     return CAENHVInitSystem("", LinkType, Arg, UserName, Passwd);
}


CAENHVLIB_API CAENHVRESULT  CAENHVDeinitSystem(const char *SystemName)
{
    return CAENHV_OK;
}

CAENHVLIB_API CAENHVRESULT  CAENHV_DeinitSystem(int handle)
{
    return CAENHVDeinitSystem("");
}

CAENHVLIB_API CAENHVRESULT  CAENHVGetChName(const char *SystemName, ushort slot, 
 ushort ChNum, const ushort *ChList, char (*ChNameList)[MAX_CH_NAME])
{
    if (++g_call_out % g_error_on_call == 0) {
	    return CAENHV_TIMEERR;
	}	
	
    // ChNum should be 1 in our case
	for(int i=0; i<ChNum; ++i)
	{
		std::string& name = crate_info[SystemName][slot][ChList[i]].name;
		if (name.size() == 0)
		{
			sprintf(ChNameList[i], "s1535");			
		}
		else
		{
			strncpy(ChNameList[i], name.c_str(), MAX_CH_NAME); 
		}
    }		
    return CAENHV_OK;
}

CAENHVLIB_API CAENHVRESULT  CAENHV_GetChName(int handle, ushort slot, 
 ushort ChNum, const ushort *ChList, char (*ChNameList)[MAX_CH_NAME])
 {
     return CAENHVGetChName("", slot, ChNum, ChList, ChNameList);
 }


CAENHVLIB_API CAENHVRESULT  CAENHVSetChName(const char *SystemName, ushort slot, 
 ushort ChNum, const ushort *ChList, const char *ChName)
{
    if (++g_call_out % g_error_on_call == 0) {
	    return CAENHV_TIMEERR;
	}	

	for(int i=0; i< ChNum; ++i)
	{
		crate_info[SystemName][slot][ChList[i]].name = ChName;
	}		
    return CAENHV_OK;
}

CAENHVLIB_API CAENHVRESULT  CAENHV_SetChName(int handle, ushort slot, 
 ushort ChNum, const ushort *ChList, const char *ChName)
 {
     return CAENHVSetChName("", slot, ChNum, ChList, ChName);     
 }
 
#define MAX_PARAM 100
CAENHVLIB_API CAENHVRESULT  CAENHVGetChParamInfo(const char *SystemName, 
 ushort slot, ushort Ch, char **ParNameList)
{
	int j=0;
    if (++g_call_out % g_error_on_call == 0) {
	    return CAENHV_TIMEERR;
	}	
    *ParNameList = static_cast<char*>(malloc(MAX_PARAM * MAX_PARAM_NAME));
	char (*par)[MAX_PARAM_NAME] = reinterpret_cast<char (*)[MAX_PARAM_NAME]>(*ParNameList);
	strcpy(par[j++], "ChName");
	strcpy(par[j++], "V0Set");
	strcpy(par[j++], "V1Set");
	strcpy(par[j++], "I0Set");
	strcpy(par[j++], "I1Set");
	strcpy(par[j++], "RUp");
	strcpy(par[j++], "RDWn");
	strcpy(par[j++], "Trip");
	strcpy(par[j++], "SVMax");
	strcpy(par[j++], "Pw");
	strcpy(par[j++], "POn");
	strcpy(par[j++], "PDwn");
	strcpy(par[j++], "TripInt");
	strcpy(par[j++], "TripExt");
	strcpy(par[j++], "VMon");
	strcpy(par[j++], "IMon");
	strcpy(par[j++], "Status");
	strcpy(par[j++], ""); // must end list with this
    return CAENHV_OK;
}

CAENHVLIB_API CAENHVRESULT  CAENHV_GetChParamInfo(int handle, 
 ushort slot, ushort Ch, char **ParNameList, int *ParNumber)
 {
     *ParNumber = 17; // see above
     return CAENHVGetChParamInfo("", slot, Ch, ParNameList);
 }

CAENHVLIB_API CAENHVRESULT  CAENHVGetChParamProp(const char *SystemName, 
 ushort slot, ushort Ch, const char *ParName, const char *PropName, void *retval)
{
    if (++g_call_out % g_error_on_call == 0) {
	    return CAENHV_TIMEERR;
	}	
    if (!strcmp(ParName, "Mode"))
	{
	    *(static_cast<unsigned long*>(retval)) = PARAM_MODE_RDWR;
	}
    else if (!strcmp(ParName, "Type"))
	{
	    *(static_cast<unsigned long*>(retval)) = PARAM_TYPE_NUMERIC;
	    return PARAM_TYPE_NUMERIC;
	}
	else
	{
	    *(static_cast<unsigned long*>(retval)) = 0;
	}
    return CAENHV_OK;
}

CAENHVLIB_API CAENHVRESULT  CAENHV_GetChParamProp(int handle, 
 ushort slot, ushort Ch, const char *ParName, const char *PropName, void *retval)
 {
     return CAENHVGetChParamProp("", slot, Ch, ParName, PropName, retval);
 }

CAENHVLIB_API CAENHVRESULT  CAENHVGetChParam(const char *SystemName, ushort slot, 
 const char *ParName, ushort ChNum, const ushort *ChList, void *ParValList)
{
    if (++g_call_out % g_error_on_call == 0) {
	    return CAENHV_TIMEERR;
	}	
	 *(static_cast<unsigned long*>(ParValList)) = 0;
     return CAENHV_OK;
}

CAENHVLIB_API CAENHVRESULT  CAENHV_GetChParam(int handle, ushort slot, 
 const char *ParName, ushort ChNum, const ushort *ChList, void *ParValList)
 {
     return CAENHVGetChParam("", slot, ParName, ChNum, ChList, ParValList);
 }

CAENHVLIB_API CAENHVRESULT  CAENHVSetChParam(const char *SystemName, ushort slot, 
 const char *ParName, ushort ChNum, const ushort *ChList, void *ParValue)
{
    if (++g_call_out % g_error_on_call == 0) {
	    return CAENHV_TIMEERR;
	}	
    return CAENHV_OK;
}

CAENHVLIB_API CAENHVRESULT  CAENHV_SetChParam(int handle, ushort slot, 
 const char *ParName, ushort ChNum, const ushort *ChList, void *ParValue)
 {
     return CAENHVSetChParam("", slot, ParName, ChNum, ChList, ParValue);
 }

CAENHVLIB_API CAENHVRESULT  CAENHVGetSysProp(const char *SystemName, 
 const char *PropName, void *Result)
{
    if (++g_call_out % g_error_on_call == 0) {
	    return CAENHV_TIMEERR;
	}	
	if ( !strcmp(PropName, "HvPwSM") )
	{
		strcpy(static_cast<char*>(Result), "HvPwSM value");
	}
	else
	{
		*(static_cast<unsigned long*>(Result)) = 0;
	}
    return CAENHV_OK;
}
 
CAENHVLIB_API CAENHVRESULT  CAENHV_GetSysProp(int handle, 
 const char *PropName, void *Result)
 {
     return CAENHVGetSysProp("", PropName, Result);
 }

CAENHVLIB_API CAENHVRESULT  CAENHVSetSysProp(const char *SystemName, 
 const char	*PropName, void *Set)
 {
     // need to check map 
    return CAENHV_OK;
 }     

CAENHVLIB_API CAENHVRESULT  CAENHV_SetSysProp(int handle, 
 const char	*PropName, void *Set)
 {
     return CAENHVSetSysProp("", PropName, Set);
 }


CAENHVLIB_API CAENHVRESULT  CAENHVGetCrateMap(const char *SystemName,	
 ushort *NrOfSlot, ushort **NrofChList, char **ModelList, char **DescriptionList,
 ushort **SerNumList, uchar **FmwRelMinList, uchar **FmwRelMaxList)
{
    if (++g_call_out % g_error_on_call == 0) {
	    return CAENHV_TIMEERR;
	}	
    *NrOfSlot = NUM_SLOTS;
	*NrofChList = static_cast<ushort*>(malloc(NUM_SLOTS * sizeof(ushort)));
	*SerNumList = static_cast<ushort*>(malloc(NUM_SLOTS * sizeof(ushort)));
	*FmwRelMinList = static_cast<uchar*>(malloc(NUM_SLOTS * sizeof(uchar)));
	*FmwRelMaxList = static_cast<uchar*>(malloc(NUM_SLOTS * sizeof(uchar)));
	*DescriptionList = static_cast<char*>(malloc(NUM_SLOTS*(1+strlen("description"))));
	*ModelList = static_cast<char*>(malloc(NUM_SLOTS*(1+strlen(BOARDNAME))));
	for(int i=0; i<NUM_SLOTS; ++i)
	{
		(*NrofChList)[i] = NUM_CH;
		(*SerNumList)[i] = 1;
		(*FmwRelMinList)[i] = 0;
		(*FmwRelMaxList)[i] = 0;
		strcpy(*DescriptionList + i * (1 + strlen("description")), "description");
		strcpy(*ModelList  + i * (1 + strlen(BOARDNAME)), BOARDNAME);
	}
    return CAENHV_OK;
}

CAENHVLIB_API CAENHVRESULT CAENHV_GetCrateMap(int handle,	
 ushort *NrOfSlot, ushort **NrofChList, char **ModelList, char **DescriptionList,
 ushort **SerNumList, uchar **FmwRelMinList, uchar **FmwRelMaxList)
 {
     return CAENHVGetCrateMap("", NrOfSlot, NrofChList, ModelList, DescriptionList, SerNumList, FmwRelMinList, FmwRelMaxList);
 }

CAENHVLIB_API CAENHVRESULT  CAENHVGetBdParam(const char *SystemName, 
 ushort slotNum, const ushort *slotList, const char *ParName, void *ParValList)
{
    if (++g_call_out % g_error_on_call == 0) {
	    return CAENHV_TIMEERR;
	}	
    if ( !strcmp(ParName, "HVMax") )
    {
        *(float*)ParValList = 10.0f * slotNum;
    }
    return CAENHV_OK;
}

CAENHVLIB_API CAENHVRESULT  CAENHV_GetBdParam(int handle, 
 ushort slotNum, const ushort *slotList, const char *ParName, void *ParValList)
{
    return CAENHVGetBdParam("", slotNum, slotList, ParName, ParValList);
}

CAENHVLIB_API CAENHVRESULT  CAENHVGetSysPropList(const char *SystemName, 
 ushort *NumProp, char **PropNameList)
{
    return CAENHV_OK;
}

CAENHVLIB_API CAENHVRESULT  CAENHV_GetSysPropList(int handle, 
 ushort *NumProp, char **PropNameList)
{
    return CAENHVGetSysPropList("", NumProp, PropNameList);
}
 
CAENHVLIB_API CAENHVRESULT  CAENHVGetSysPropInfo(const char *SystemName, 
 const char *PropName, unsigned *PropMode, unsigned *PropType)
{
    return CAENHV_OK;
}
 
CAENHVLIB_API CAENHVRESULT  CAENHV_GetSysPropInfo(int handle, 
 const char *PropName, unsigned *PropMode, unsigned *PropType)
{
    return CAENHVGetSysPropInfo("", PropName, PropMode, PropType);
}

 
CAENHVLIB_API CAENHVRESULT  CAENHVSetBdParam(const char *SystemName, 
 ushort slotNum, const ushort *slotList, const char *ParName, void *ParValue)
{
    return CAENHV_OK;
}
 
CAENHVLIB_API CAENHVRESULT  CAENHV_SetBdParam(int handle, 
 ushort slotNum, const ushort *slotList, const char *ParName, void *ParValue)
{
    return CAENHVSetBdParam("", slotNum, slotList, ParName, ParValue);
}
 
CAENHVLIB_API CAENHVRESULT  CAENHVGetBdParamProp(const char *SystemName, 
 ushort slot, const char *ParName, const char *PropName, void *retval)
{
    return CAENHV_OK;
}
 
CAENHVLIB_API CAENHVRESULT  CAENHV_GetBdParamProp(int handle, 
 ushort slot, const char *ParName, const char *PropName, void *retval)
{
    return CAENHVGetBdParamProp("", slot, ParName, PropName, retval);
}

CAENHVLIB_API CAENHVRESULT  CAENHVGetBdParamInfo(const char *SystemName, 
 ushort slot, char **ParNameList)
{
    return CAENHV_OK;
}
 
CAENHVLIB_API CAENHVRESULT  CAENHV_GetBdParamInfo(int handle, 
 ushort slot, char **ParNameList)
{
    return CAENHVGetBdParamInfo("", slot, ParNameList);
}
