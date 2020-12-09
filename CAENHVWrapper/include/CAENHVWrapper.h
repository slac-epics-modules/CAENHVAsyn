/***************************************************************************/
/*                                                                         */
/*        --- CAEN Engineering Srl - Computing Systems Division ---        */
/*                                                                         */
/*    CAENHVWRAPPER.H                                                      */
/*                                                                         */
/*                                                                         */
/*    Source code written in ANSI C                                        */
/*                                                                         */ 
/*    Created:  July 2011                                                 */
/*                                                                         */
/***************************************************************************/

#ifndef __CAENHVWRAPPER_H
#define __CAENHVWRAPPER_H

#ifdef __GNUC__
#define HV_DEPRECATED(func) func __attribute__ ((deprecated))
#elif defined(_MSC_VER)
#define HV_DEPRECATED(func) __declspec(deprecated) func
#else
#pragma message("WARNING: DEPRECATED marking not supported on this compiler")
#define HV_DEPRECATED(func) func
#endif

#include "caenhvoslib.h"

#ifndef uchar 
#define uchar unsigned char
#endif
#ifndef ushort 
#define ushort unsigned short
#endif
#ifndef ulong
#define ulong unsigned int
#endif

#define LIBSWREL				"5.52"

#define MAX_CH_NAME                12
 
#define MAX_PARAM_NAME             10

#define MAX_CRATES                             8
#define MAX_SLOTS                             32
#define MAX_BOARDS    ( MAX_SLOTS * MAX_CRATES )

#define MAX_BOARD_NAME             12
#define MAX_BOARD_DESC             28 
#define SET                         1
#define MON                         0
#define SIGNED                      1
#define UNSIGNED                    0

#define PARAM_TYPE_NUMERIC          0
#define PARAM_TYPE_ONOFF            1
#define PARAM_TYPE_CHSTATUS         2
#define PARAM_TYPE_BDSTATUS         3
#define PARAM_TYPE_BINARY			4			// Rel. 2.16
#define PARAM_TYPE_STRING			5
#define PARAM_TYPE_ENUM				6			// Rel 5.30

#define PARAM_MODE_RDONLY           0
#define PARAM_MODE_WRONLY           1
#define PARAM_MODE_RDWR             2

#define PARAM_UN_NONE               0
#define PARAM_UN_AMPERE             1
#define PARAM_UN_VOLT               2
#define PARAM_UN_WATT               3
#define PARAM_UN_CELSIUS            4
#define PARAM_UN_HERTZ              5
#define PARAM_UN_BAR                6
#define PARAM_UN_VPS                7
#define PARAM_UN_SECOND             8
#define PARAM_UN_RPM                9             // Rel. 1.4
#define PARAM_UN_COUNT             10             // Rel. 2.6
#define PARAM_UN_BIT               11			

#define SYSPROP_TYPE_STR            0
#define SYSPROP_TYPE_REAL           1
#define SYSPROP_TYPE_UINT2          2
#define SYSPROP_TYPE_UINT4          3
#define SYSPROP_TYPE_INT2           4
#define SYSPROP_TYPE_INT4           5
#define SYSPROP_TYPE_BOOLEAN        6

#define SYSPROP_MODE_RDONLY         0
#define SYSPROP_MODE_WRONLY         1
#define SYSPROP_MODE_RDWR           2

#define EVENTTYPE_PARAMETER			0
#define EVENTTYPE_ALARM				1
#define EVENTTYPE_KEEPALIVE			2

#define MAXLINE						0x1000

/*-----------------------------------------------------------------------------
                                                                             
                             ERROR    CODES                                 
                                                                             
  Their meaning is the next:                                                 
   CODES                                                                     
     0    Command wrapper correctly executed                                 
     1    Error of operatived system                                         
     2    Write error in communication channel                               
     3    Read error in communication channel                                
     4    Time out in server communication                                   
     5    Command Front End application is down                              
     6    Comunication with system not yet connected by a Login command      
     7    Execute Command not yet implemented                              
     8    Get Property not yet implemented                                 
     9    Set Property not yet implemented                                 
     10   Communication with RS232 not yet implemented                     
     11   User memory not sufficient                                          
	 12   Value out of range
     13   Property not yet implementated
     14   Property not found
     15   Execute command not found
     16   No System property
     17   No get property
     18   No set property
     19   No execute command
     20   configuration change
     21   Property of param not found
     22   Param not found
	 23	  No data present
	 24   Device already open
	 25   To Many devices opened
	 26   Function Parameter not valid
	 27	  Function not available for the connected device
 -----------------------------------------------------------------------------*/
#define CAENHV_OK                   0
#define CAENHV_SYSERR               1
#define CAENHV_WRITEERR             2
#define CAENHV_READERR              3
#define CAENHV_TIMEERR              4
#define CAENHV_DOWN                 5
#define CAENHV_NOTPRES              6
#define CAENHV_SLOTNOTPRES          7
#define CAENHV_NOSERIAL             8
#define CAENHV_MEMORYFAULT          9
#define CAENHV_OUTOFRANGE           10
#define CAENHV_EXECCOMNOTIMPL       11
#define CAENHV_GETPROPNOTIMPL       12
#define CAENHV_SETPROPNOTIMPL       13
#define CAENHV_PROPNOTFOUND         14
#define CAENHV_EXECNOTFOUND         15
#define CAENHV_NOTSYSPROP		    16
#define CAENHV_NOTGETPROP		    17
#define CAENHV_NOTSETPROP           18
#define CAENHV_NOTEXECOMM           19
#define CAENHV_SYSCONFCHANGE	    20
#define CAENHV_PARAMPROPNOTFOUND    21
#define CAENHV_PARAMNOTFOUND        22
#define CAENHV_NODATA				23
#define CAENHV_DEVALREADYOPEN		24
#define CAENHV_TOOMANYDEVICEOPEN	25
#define CAENHV_INVALIDPARAMETER		26
#define CAENHV_FUNCTIONNOTAVAILABLE	27
#define CAENHV_SOCKETERROR			28
#define CAENHV_COMMUNICATIONERROR	29
#define CAENHV_NOTYETIMPLEMENTED	30
#define CAENHV_CONNECTED			(0x1000 + 1)
#define CAENHV_NOTCONNECTED			(0x1000 + 2)
#define CAENHV_OS					(0x1000 + 3)
#define CAENHV_LOGINFAILED			(0x1000 + 4)
#define CAENHV_LOGOUTFAILED			(0x1000 + 5)
#define CAENHV_LINKNOTSUPPORTED		(0x1000 + 6)  // Rel. 1.2
#define CAENHV_USERPASSFAILED		(0x1000 + 7)  // Rel. 5.0

// Link Types for InitSystem
#define LINKTYPE_TCPIP				0
#define LINKTYPE_RS232				1
#define LINKTYPE_CAENET				2
#define LINKTYPE_USB				3
#define LINKTYPE_OPTLINK			4
#define LINKTYPE_USB_VCP			5

#ifndef __CAENHVRESULT__                         // Rel. 2.0 - Linux
// The Error Code type
typedef int CAENHVRESULT;
#define __CAENHVRESULT__
#endif

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef union {
	char			StringValue[1024];
	float			FloatValue;
	int				IntValue;
} IDValue_t;

typedef enum {
	PARAMETER		= 0,
	ALARM			= 1,
	KEEPALIVE		= 2,
}CAENHV_ID_TYPE_t;

// Rel. 3.00
typedef struct {    
	char	Type;
	char	ItemID[64];
	char	Lvalue[4];
	char	Tvalue[256];
} CAENHVEVENT_TYPE;

typedef struct {
	CAENHV_ID_TYPE_t	Type;
	int					SystemHandle;
	int					BoardIndex;
	int					ChannelIndex;
	char				ItemID[20];
	IDValue_t			Value;
} CAENHVEVENT_TYPE_t;

typedef enum {
	SY1527		= 0,
	SY2527		= 1,
	SY4527		= 2,
	SY5527		= 3,
	N568		= 4,
	V65XX		= 5,
	N1470		= 6,
	V8100		= 7,
	N568E		= 8,
	DT55XX		= 9
} CAENHV_SYSTEM_TYPE_t;
typedef enum {
	SYNC		= 0,
	ASYNC		= 1,
	UNSYNC		= 2,
	NOTAVAIL	= 3,
} CAENHV_EVT_STATUS_t;

typedef struct {
	CAENHV_EVT_STATUS_t	System;
	CAENHV_EVT_STATUS_t	Board[16];
} CAENHV_SYSTEMSTATUS_t;

HV_DEPRECATED(CAENHVLIB_API char *CAENHVGetError(const char *SystemName));

CAENHVLIB_API char         *CAENHVLibSwRel(void);

/* Rel. 1.1 */
CAENHVLIB_API CAENHVRESULT CAENHVCaenetComm(const char *SystemName, 
 ushort Crate, ushort Code, ushort NrWCode, ushort *WCode, short *Result,
 ushort *NrOfData, ushort **Data);

CAENHVLIB_API CAENHVRESULT CAENHV_CaenetComm(int handle, 
 ushort Crate, ushort Code, ushort NrWCode, ushort *WCode, short *Result,
 ushort *NrOfData, ushort **Data);

HV_DEPRECATED(CAENHVLIB_API CAENHVRESULT  CAENHVInitSystem(const char *SystemName, 
 int LinkType, void *Arg, const char *UserName, const char *Passwd));
 
CAENHVLIB_API CAENHVRESULT CAENHV_InitSystem(CAENHV_SYSTEM_TYPE_t system, int LinkType, void *Arg, const char *UserName, const char *Passwd,  int *handle);

HV_DEPRECATED(CAENHVLIB_API CAENHVRESULT  CAENHVDeinitSystem(const char *SystemName));

CAENHVLIB_API CAENHVRESULT  CAENHV_DeinitSystem(int handle);

HV_DEPRECATED(CAENHVLIB_API CAENHVRESULT  CAENHVGetCrateMap(const char *SystemName,	
 ushort *NrOfSlot, ushort **NrofChList, char **ModelList, char **DescriptionList,
 ushort **SerNumList, uchar **FmwRelMinList, uchar **FmwRelMaxList));

CAENHVLIB_API CAENHVRESULT CAENHV_GetCrateMap(int handle,	
 ushort *NrOfSlot, ushort **NrofChList, char **ModelList, char **DescriptionList,
 ushort **SerNumList, uchar **FmwRelMinList, uchar **FmwRelMaxList);
 
HV_DEPRECATED(CAENHVLIB_API CAENHVRESULT  CAENHVGetSysPropList(const char *SystemName, 
 ushort *NumProp, char **PropNameList));

CAENHVLIB_API CAENHVRESULT  CAENHV_GetSysPropList(int handle, 
 ushort *NumProp, char **PropNameList);
 
HV_DEPRECATED(CAENHVLIB_API CAENHVRESULT  CAENHVGetSysPropInfo(const char *SystemName, 
 const char *PropName, unsigned *PropMode, unsigned *PropType));
 
CAENHVLIB_API CAENHVRESULT  CAENHV_GetSysPropInfo(int handle, 
 const char *PropName, unsigned *PropMode, unsigned *PropType);

HV_DEPRECATED(CAENHVLIB_API CAENHVRESULT  CAENHVGetSysProp(const char *SystemName, 
 const char *PropName, void *Result));
 
CAENHVLIB_API CAENHVRESULT  CAENHV_GetSysProp(int handle, 
 const char *PropName, void *Result);

HV_DEPRECATED(CAENHVLIB_API CAENHVRESULT  CAENHVSetSysProp(const char *SystemName, 
 const char	*PropName, void *Set)); 

CAENHVLIB_API CAENHVRESULT  CAENHV_SetSysProp(int handle, 
 const char	*PropName, void *Set); 

HV_DEPRECATED(CAENHVLIB_API CAENHVRESULT  CAENHVGetBdParam(const char *SystemName, 
 ushort slotNum, const ushort *slotList, const char *ParName, void *ParValList));
 
CAENHVLIB_API CAENHVRESULT  CAENHV_GetBdParam(int handle, 
 ushort slotNum, const ushort *slotList, const char *ParName, void *ParValList);
 
HV_DEPRECATED(CAENHVLIB_API CAENHVRESULT  CAENHVSetBdParam(const char *SystemName, 
 ushort slotNum, const ushort *slotList, const char *ParName, void *ParValue));

CAENHVLIB_API CAENHVRESULT  CAENHV_SetBdParam(int handle, 
 ushort slotNum, const ushort *slotList, const char *ParName, void *ParValue);
 
HV_DEPRECATED(CAENHVLIB_API CAENHVRESULT  CAENHVGetBdParamProp(const char *SystemName, 
 ushort slot, const char *ParName, const char *PropName, void *retval));

CAENHVLIB_API CAENHVRESULT  CAENHV_GetBdParamProp(int handle, 
 ushort slot, const char *ParName, const char *PropName, void *retval);

HV_DEPRECATED(CAENHVLIB_API CAENHVRESULT  CAENHVGetBdParamInfo(const char *SystemName, 
 ushort slot, char **ParNameList));
 
CAENHVLIB_API CAENHVRESULT  CAENHV_GetBdParamInfo(int handle, 
 ushort slot, char **ParNameList);

HV_DEPRECATED(CAENHVLIB_API CAENHVRESULT  CAENHVTestBdPresence(const char *SystemName, 
 ushort slot, ushort *NrofCh, char *Model, char *Description, ushort *SerNum, 
 uchar *FmwRelMin, uchar *FmwRelMax));
 
CAENHVLIB_API CAENHVRESULT  CAENHV_TestBdPresence(int handle, 
 ushort slot, ushort *NrofCh, char **Model, char **Description, ushort *SerNum, 
 uchar *FmwRelMin, uchar *FmwRelMax);
 
HV_DEPRECATED(CAENHVLIB_API CAENHVRESULT  CAENHVGetChParamProp(const char *SystemName, 
 ushort slot, ushort Ch, const char *ParName, const char *PropName, void *retval));

CAENHVLIB_API CAENHVRESULT  CAENHV_GetChParamProp(int handle, 
 ushort slot, ushort Ch, const char *ParName, const char *PropName, void *retval);
 
HV_DEPRECATED(CAENHVLIB_API CAENHVRESULT  CAENHVGetChParamInfo(const char *SystemName, 
 ushort slot, ushort Ch, char **ParNameList));
 
CAENHVLIB_API CAENHVRESULT CAENHV_GetChParamInfo(int handle, ushort slot, ushort Ch, char **ParNameList, int *ParNumber);

HV_DEPRECATED(CAENHVLIB_API CAENHVRESULT  CAENHVGetChName(const char *SystemName, ushort slot, 
 ushort ChNum, const ushort *ChList, char (*ChNameList)[MAX_CH_NAME]));
 
CAENHVLIB_API CAENHVRESULT  CAENHV_GetChName(int handle, ushort slot, 
 ushort ChNum, const ushort *ChList, char (*ChNameList)[MAX_CH_NAME]);

HV_DEPRECATED(CAENHVLIB_API CAENHVRESULT  CAENHVSetChName(const char *SystemName, ushort slot, 
 ushort ChNum, const ushort *ChList, const char *ChName));

CAENHVLIB_API CAENHVRESULT  CAENHV_SetChName(int handle, ushort slot, 
 ushort ChNum, const ushort *ChList, const char *ChName);

HV_DEPRECATED(CAENHVLIB_API CAENHVRESULT  CAENHVGetChParam(const char *SystemName, ushort slot, 
 const char *ParName, ushort ChNum, const ushort *ChList, void *ParValList));

CAENHVLIB_API CAENHVRESULT  CAENHV_GetChParam(int handle, ushort slot, 
 const char *ParName, ushort ChNum, const ushort *ChList, void *ParValList);
 
HV_DEPRECATED(CAENHVLIB_API CAENHVRESULT  CAENHVSetChParam(const char *SystemName, ushort slot, 
 const char *ParName, ushort ChNum, const ushort *ChList, void *ParValue));

CAENHVLIB_API CAENHVRESULT  CAENHV_SetChParam(int handle, ushort slot, 
 const char *ParName, ushort ChNum, const ushort *ChList, void *ParValue);

HV_DEPRECATED(CAENHVLIB_API CAENHVRESULT  CAENHVGetExecCommList(const char *SystemName,
 ushort *NumComm, char **CommNameList));
 
CAENHVLIB_API CAENHVRESULT  CAENHV_GetExecCommList(int handle,
 ushort *NumComm, char **CommNameList);

HV_DEPRECATED(CAENHVLIB_API CAENHVRESULT  CAENHVExecComm(const char *SystemName, 
 const char *CommName));
 
CAENHVLIB_API CAENHVRESULT  CAENHV_ExecComm(int handle, const char *CommName);

HV_DEPRECATED(CAENHVLIB_API CAENHVRESULT CAENHVSubscribe(const char *SystemName, 
 short Port, ushort NrOfItems, const char *ListOfItems, char *ListofResultCodes));

CAENHVLIB_API CAENHVRESULT CAENHV_SubscribeSystemParams(int handle, short Port, const char *paramNameList, unsigned int paramNum ,char *listOfResultCodes);

CAENHVLIB_API CAENHVRESULT CAENHV_SubscribeBoardParams(int handle, short Port, const unsigned short slotIndex, const char *paramNameList, unsigned int paramNum ,char *listOfResultCodes);

CAENHVLIB_API CAENHVRESULT CAENHV_SubscribeChannelParams(int handle, short Port, const unsigned short slotIndex,const unsigned short chanIndex, const char *paramNameList, unsigned int paramNum ,char *listOfResultCodes);

CAENHVLIB_API CAENHVRESULT CAENHV_UnSubscribeSystemParams(int handle, short Port, const char *paramNameList, unsigned int paramNum ,char *listOfResultCodes);

CAENHVLIB_API CAENHVRESULT CAENHV_UnSubscribeBoardParams(int handle, short Port, const unsigned short slotIndex, const char *paramNameList, unsigned int paramNum ,char *listOfResultCodes);

CAENHVLIB_API CAENHVRESULT CAENHV_UnSubscribeChannelParams(int handle, short Port, const unsigned short slotIndex,const unsigned short chanIndex, const char *paramNameList, unsigned int paramNum ,char *listOfResultCodes);

HV_DEPRECATED (CAENHVLIB_API CAENHVRESULT CAENHV_Subscribe(int handle, 
 short Port, ushort NrOfItems, const char *ListOfItems, char *ListofResultCodes));

CAENHVLIB_API char *CAENHV_GetError(int handle);

HV_DEPRECATED(CAENHVLIB_API CAENHVRESULT CAENHVUnSubscribe(const char *SystemName, short Port,
 ushort NrOfItems, const char *ListOfItems, char *ListofResultCodes));
 
HV_DEPRECATED (CAENHVLIB_API CAENHVRESULT CAENHV_UnSubscribe(int handle, short Port, ushort NrOfItems, const char *ListOfItems, char *ListOfResultCodes));

#ifdef WIN32
HV_DEPRECATED(CAENHVLIB_API CAENHVRESULT CAENHVGetEventData(SOCKET sck, CAENHVEVENT_TYPE **ListOfItems, unsigned int *NumberOfItems));

CAENHVLIB_API CAENHVRESULT CAENHV_GetEventData(SOCKET sck, CAENHV_SYSTEMSTATUS_t *SysStatus, CAENHVEVENT_TYPE_t **EventData, unsigned int *DataNumber);
#else

HV_DEPRECATED(CAENHVLIB_API CAENHVRESULT CAENHVGetEventData(int sck, CAENHVEVENT_TYPE **ListOfItems, unsigned int *NumberOfItems));

CAENHVLIB_API CAENHVRESULT CAENHV_GetEventData(int sck, CAENHV_SYSTEMSTATUS_t *SysStatus, CAENHVEVENT_TYPE_t **EventData, unsigned int *DataNumber);
#endif


HV_DEPRECATED(CAENHVLIB_API CAENHVRESULT CAENHVFreeEventData(CAENHVEVENT_TYPE **EventData));

CAENHVLIB_API CAENHVRESULT CAENHV_FreeEventData(CAENHVEVENT_TYPE_t **ListOfItemsData);

CAENHVLIB_API CAENHVRESULT CAENHV_Free(void *arg);


/********************************************/

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // __CAENHVWRAPPER_H
