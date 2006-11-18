
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Sat Sep 28 13:23:34 2002
 */
/* Compiler settings for Audtest.odl:
    Os, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __audtest_h_h__
#define __audtest_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IAudtes_FWD_DEFINED__
#define __IAudtes_FWD_DEFINED__
typedef interface IAudtes IAudtes;
#endif 	/* __IAudtes_FWD_DEFINED__ */


#ifndef __CAudtestDoc_FWD_DEFINED__
#define __CAudtestDoc_FWD_DEFINED__

#ifdef __cplusplus
typedef class CAudtestDoc CAudtestDoc;
#else
typedef struct CAudtestDoc CAudtestDoc;
#endif /* __cplusplus */

#endif 	/* __CAudtestDoc_FWD_DEFINED__ */


#ifndef __IDlgSweep_FWD_DEFINED__
#define __IDlgSweep_FWD_DEFINED__
typedef interface IDlgSweep IDlgSweep;
#endif 	/* __IDlgSweep_FWD_DEFINED__ */


#ifndef __CDlgSweep_FWD_DEFINED__
#define __CDlgSweep_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgSweep CDlgSweep;
#else
typedef struct CDlgSweep CDlgSweep;
#endif /* __cplusplus */

#endif 	/* __CDlgSweep_FWD_DEFINED__ */


#ifndef __IDlgSine_FWD_DEFINED__
#define __IDlgSine_FWD_DEFINED__
typedef interface IDlgSine IDlgSine;
#endif 	/* __IDlgSine_FWD_DEFINED__ */


#ifndef __CDlgSine_FWD_DEFINED__
#define __CDlgSine_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgSine CDlgSine;
#else
typedef struct CDlgSine CDlgSine;
#endif /* __cplusplus */

#endif 	/* __CDlgSine_FWD_DEFINED__ */


#ifndef __IDlgGenerator_FWD_DEFINED__
#define __IDlgGenerator_FWD_DEFINED__
typedef interface IDlgGenerator IDlgGenerator;
#endif 	/* __IDlgGenerator_FWD_DEFINED__ */


#ifndef __CDlgGenerator_FWD_DEFINED__
#define __CDlgGenerator_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgGenerator CDlgGenerator;
#else
typedef struct CDlgGenerator CDlgGenerator;
#endif /* __cplusplus */

#endif 	/* __CDlgGenerator_FWD_DEFINED__ */


#ifndef __IDlgPulse_FWD_DEFINED__
#define __IDlgPulse_FWD_DEFINED__
typedef interface IDlgPulse IDlgPulse;
#endif 	/* __IDlgPulse_FWD_DEFINED__ */


#ifndef __CDlgPulse_FWD_DEFINED__
#define __CDlgPulse_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgPulse CDlgPulse;
#else
typedef struct CDlgPulse CDlgPulse;
#endif /* __cplusplus */

#endif 	/* __CDlgPulse_FWD_DEFINED__ */


#ifndef __IDlgMls_FWD_DEFINED__
#define __IDlgMls_FWD_DEFINED__
typedef interface IDlgMls IDlgMls;
#endif 	/* __IDlgMls_FWD_DEFINED__ */


#ifndef __CDlgMls_FWD_DEFINED__
#define __CDlgMls_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgMls CDlgMls;
#else
typedef struct CDlgMls CDlgMls;
#endif /* __cplusplus */

#endif 	/* __CDlgMls_FWD_DEFINED__ */


#ifndef __IDlgDsGeneral_FWD_DEFINED__
#define __IDlgDsGeneral_FWD_DEFINED__
typedef interface IDlgDsGeneral IDlgDsGeneral;
#endif 	/* __IDlgDsGeneral_FWD_DEFINED__ */


#ifndef __CDlgDsGeneral_FWD_DEFINED__
#define __CDlgDsGeneral_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgDsGeneral CDlgDsGeneral;
#else
typedef struct CDlgDsGeneral CDlgDsGeneral;
#endif /* __cplusplus */

#endif 	/* __CDlgDsGeneral_FWD_DEFINED__ */


#ifndef __IDlgDataset_FWD_DEFINED__
#define __IDlgDataset_FWD_DEFINED__
typedef interface IDlgDataset IDlgDataset;
#endif 	/* __IDlgDataset_FWD_DEFINED__ */


#ifndef __CDlgDataset_FWD_DEFINED__
#define __CDlgDataset_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgDataset CDlgDataset;
#else
typedef struct CDlgDataset CDlgDataset;
#endif /* __cplusplus */

#endif 	/* __CDlgDataset_FWD_DEFINED__ */


#ifndef __IDlgChart_FWD_DEFINED__
#define __IDlgChart_FWD_DEFINED__
typedef interface IDlgChart IDlgChart;
#endif 	/* __IDlgChart_FWD_DEFINED__ */


#ifndef __CDlgChart_FWD_DEFINED__
#define __CDlgChart_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgChart CDlgChart;
#else
typedef struct CDlgChart CDlgChart;
#endif /* __cplusplus */

#endif 	/* __CDlgChart_FWD_DEFINED__ */


#ifndef __IDlgDataLines_FWD_DEFINED__
#define __IDlgDataLines_FWD_DEFINED__
typedef interface IDlgDataLines IDlgDataLines;
#endif 	/* __IDlgDataLines_FWD_DEFINED__ */


#ifndef __CDlgDataLines_FWD_DEFINED__
#define __CDlgDataLines_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgDataLines CDlgDataLines;
#else
typedef struct CDlgDataLines CDlgDataLines;
#endif /* __cplusplus */

#endif 	/* __CDlgDataLines_FWD_DEFINED__ */


#ifndef __IDlgGrid_FWD_DEFINED__
#define __IDlgGrid_FWD_DEFINED__
typedef interface IDlgGrid IDlgGrid;
#endif 	/* __IDlgGrid_FWD_DEFINED__ */


#ifndef __CDlgGrid_FWD_DEFINED__
#define __CDlgGrid_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgGrid CDlgGrid;
#else
typedef struct CDlgGrid CDlgGrid;
#endif /* __cplusplus */

#endif 	/* __CDlgGrid_FWD_DEFINED__ */


#ifndef __IDlgChGen_FWD_DEFINED__
#define __IDlgChGen_FWD_DEFINED__
typedef interface IDlgChGen IDlgChGen;
#endif 	/* __IDlgChGen_FWD_DEFINED__ */


#ifndef __CDlgChGen_FWD_DEFINED__
#define __CDlgChGen_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgChGen CDlgChGen;
#else
typedef struct CDlgChGen CDlgChGen;
#endif /* __cplusplus */

#endif 	/* __CDlgChGen_FWD_DEFINED__ */


#ifndef __IDlgChData_FWD_DEFINED__
#define __IDlgChData_FWD_DEFINED__
typedef interface IDlgChData IDlgChData;
#endif 	/* __IDlgChData_FWD_DEFINED__ */


#ifndef __CDlgChData_FWD_DEFINED__
#define __CDlgChData_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgChData CDlgChData;
#else
typedef struct CDlgChData CDlgChData;
#endif /* __cplusplus */

#endif 	/* __CDlgChData_FWD_DEFINED__ */


#ifndef __IAddChartData_FWD_DEFINED__
#define __IAddChartData_FWD_DEFINED__
typedef interface IAddChartData IAddChartData;
#endif 	/* __IAddChartData_FWD_DEFINED__ */


#ifndef __CAddChartData_FWD_DEFINED__
#define __CAddChartData_FWD_DEFINED__

#ifdef __cplusplus
typedef class CAddChartData CAddChartData;
#else
typedef struct CAddChartData CAddChartData;
#endif /* __cplusplus */

#endif 	/* __CAddChartData_FWD_DEFINED__ */


#ifndef __IDlgXfLimit_FWD_DEFINED__
#define __IDlgXfLimit_FWD_DEFINED__
typedef interface IDlgXfLimit IDlgXfLimit;
#endif 	/* __IDlgXfLimit_FWD_DEFINED__ */


#ifndef __CDlgXfLimit_FWD_DEFINED__
#define __CDlgXfLimit_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgXfLimit CDlgXfLimit;
#else
typedef struct CDlgXfLimit CDlgXfLimit;
#endif /* __cplusplus */

#endif 	/* __CDlgXfLimit_FWD_DEFINED__ */


#ifndef __IDlgXfScale_FWD_DEFINED__
#define __IDlgXfScale_FWD_DEFINED__
typedef interface IDlgXfScale IDlgXfScale;
#endif 	/* __IDlgXfScale_FWD_DEFINED__ */


#ifndef __CDlgXfScale_FWD_DEFINED__
#define __CDlgXfScale_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgXfScale CDlgXfScale;
#else
typedef struct CDlgXfScale CDlgXfScale;
#endif /* __cplusplus */

#endif 	/* __CDlgXfScale_FWD_DEFINED__ */


#ifndef __IDlgXfTruncate_FWD_DEFINED__
#define __IDlgXfTruncate_FWD_DEFINED__
typedef interface IDlgXfTruncate IDlgXfTruncate;
#endif 	/* __IDlgXfTruncate_FWD_DEFINED__ */


#ifndef __CDlgXfTruncate_FWD_DEFINED__
#define __CDlgXfTruncate_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgXfTruncate CDlgXfTruncate;
#else
typedef struct CDlgXfTruncate CDlgXfTruncate;
#endif /* __cplusplus */

#endif 	/* __CDlgXfTruncate_FWD_DEFINED__ */


#ifndef __IDlgXfDelay_FWD_DEFINED__
#define __IDlgXfDelay_FWD_DEFINED__
typedef interface IDlgXfDelay IDlgXfDelay;
#endif 	/* __IDlgXfDelay_FWD_DEFINED__ */


#ifndef __CDlgXfDelay_FWD_DEFINED__
#define __CDlgXfDelay_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgXfDelay CDlgXfDelay;
#else
typedef struct CDlgXfDelay CDlgXfDelay;
#endif /* __cplusplus */

#endif 	/* __CDlgXfDelay_FWD_DEFINED__ */


#ifndef __IDlgXfSmooth_FWD_DEFINED__
#define __IDlgXfSmooth_FWD_DEFINED__
typedef interface IDlgXfSmooth IDlgXfSmooth;
#endif 	/* __IDlgXfSmooth_FWD_DEFINED__ */


#ifndef __CDlgXfSmooth_FWD_DEFINED__
#define __CDlgXfSmooth_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgXfSmooth CDlgXfSmooth;
#else
typedef struct CDlgXfSmooth CDlgXfSmooth;
#endif /* __cplusplus */

#endif 	/* __CDlgXfSmooth_FWD_DEFINED__ */


#ifndef __IDlgDsDataset_FWD_DEFINED__
#define __IDlgDsDataset_FWD_DEFINED__
typedef interface IDlgDsDataset IDlgDsDataset;
#endif 	/* __IDlgDsDataset_FWD_DEFINED__ */


#ifndef __CDlgDsDataset_FWD_DEFINED__
#define __CDlgDsDataset_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgDsDataset CDlgDsDataset;
#else
typedef struct CDlgDsDataset CDlgDsDataset;
#endif /* __cplusplus */

#endif 	/* __CDlgDsDataset_FWD_DEFINED__ */


#ifndef __IDlgNetList_FWD_DEFINED__
#define __IDlgNetList_FWD_DEFINED__
typedef interface IDlgNetList IDlgNetList;
#endif 	/* __IDlgNetList_FWD_DEFINED__ */


#ifndef __CDlgNetList_FWD_DEFINED__
#define __CDlgNetList_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgNetList CDlgNetList;
#else
typedef struct CDlgNetList CDlgNetList;
#endif /* __cplusplus */

#endif 	/* __CDlgNetList_FWD_DEFINED__ */


#ifndef __IDlgNetGeneral_FWD_DEFINED__
#define __IDlgNetGeneral_FWD_DEFINED__
typedef interface IDlgNetGeneral IDlgNetGeneral;
#endif 	/* __IDlgNetGeneral_FWD_DEFINED__ */


#ifndef __CDlgNetGeneral_FWD_DEFINED__
#define __CDlgNetGeneral_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgNetGeneral CDlgNetGeneral;
#else
typedef struct CDlgNetGeneral CDlgNetGeneral;
#endif /* __cplusplus */

#endif 	/* __CDlgNetGeneral_FWD_DEFINED__ */


#ifndef __IDlgNetDriver_FWD_DEFINED__
#define __IDlgNetDriver_FWD_DEFINED__
typedef interface IDlgNetDriver IDlgNetDriver;
#endif 	/* __IDlgNetDriver_FWD_DEFINED__ */


#ifndef __CDlgNetDriver_FWD_DEFINED__
#define __CDlgNetDriver_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgNetDriver CDlgNetDriver;
#else
typedef struct CDlgNetDriver CDlgNetDriver;
#endif /* __cplusplus */

#endif 	/* __CDlgNetDriver_FWD_DEFINED__ */


#ifndef __IDlgNetwork_FWD_DEFINED__
#define __IDlgNetwork_FWD_DEFINED__
typedef interface IDlgNetwork IDlgNetwork;
#endif 	/* __IDlgNetwork_FWD_DEFINED__ */


#ifndef __CDlgNetwork_FWD_DEFINED__
#define __CDlgNetwork_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgNetwork CDlgNetwork;
#else
typedef struct CDlgNetwork CDlgNetwork;
#endif /* __cplusplus */

#endif 	/* __CDlgNetwork_FWD_DEFINED__ */


#ifndef __IDlgRoomGeneral_FWD_DEFINED__
#define __IDlgRoomGeneral_FWD_DEFINED__
typedef interface IDlgRoomGeneral IDlgRoomGeneral;
#endif 	/* __IDlgRoomGeneral_FWD_DEFINED__ */


#ifndef __CDlgRoomGeneral_FWD_DEFINED__
#define __CDlgRoomGeneral_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgRoomGeneral CDlgRoomGeneral;
#else
typedef struct CDlgRoomGeneral CDlgRoomGeneral;
#endif /* __cplusplus */

#endif 	/* __CDlgRoomGeneral_FWD_DEFINED__ */


#ifndef __IDlgRoomBoxes_FWD_DEFINED__
#define __IDlgRoomBoxes_FWD_DEFINED__
typedef interface IDlgRoomBoxes IDlgRoomBoxes;
#endif 	/* __IDlgRoomBoxes_FWD_DEFINED__ */


#ifndef __CDlgRoomBoxes_FWD_DEFINED__
#define __CDlgRoomBoxes_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgRoomBoxes CDlgRoomBoxes;
#else
typedef struct CDlgRoomBoxes CDlgRoomBoxes;
#endif /* __cplusplus */

#endif 	/* __CDlgRoomBoxes_FWD_DEFINED__ */


#ifndef __IDlgRoomWall_FWD_DEFINED__
#define __IDlgRoomWall_FWD_DEFINED__
typedef interface IDlgRoomWall IDlgRoomWall;
#endif 	/* __IDlgRoomWall_FWD_DEFINED__ */


#ifndef __CDlgRoomWall_FWD_DEFINED__
#define __CDlgRoomWall_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgRoomWall CDlgRoomWall;
#else
typedef struct CDlgRoomWall CDlgRoomWall;
#endif /* __cplusplus */

#endif 	/* __CDlgRoomWall_FWD_DEFINED__ */


#ifndef __IDlgRoom_FWD_DEFINED__
#define __IDlgRoom_FWD_DEFINED__
typedef interface IDlgRoom IDlgRoom;
#endif 	/* __IDlgRoom_FWD_DEFINED__ */


#ifndef __CDlgRoom_FWD_DEFINED__
#define __CDlgRoom_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgRoom CDlgRoom;
#else
typedef struct CDlgRoom CDlgRoom;
#endif /* __cplusplus */

#endif 	/* __CDlgRoom_FWD_DEFINED__ */


#ifndef __IDlgLocations_FWD_DEFINED__
#define __IDlgLocations_FWD_DEFINED__
typedef interface IDlgLocations IDlgLocations;
#endif 	/* __IDlgLocations_FWD_DEFINED__ */


#ifndef __CDlgLocations_FWD_DEFINED__
#define __CDlgLocations_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgLocations CDlgLocations;
#else
typedef struct CDlgLocations CDlgLocations;
#endif /* __cplusplus */

#endif 	/* __CDlgLocations_FWD_DEFINED__ */


#ifndef __IDlgGenGeneral_FWD_DEFINED__
#define __IDlgGenGeneral_FWD_DEFINED__
typedef interface IDlgGenGeneral IDlgGenGeneral;
#endif 	/* __IDlgGenGeneral_FWD_DEFINED__ */


#ifndef __CDlgGenGeneral_FWD_DEFINED__
#define __CDlgGenGeneral_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgGenGeneral CDlgGenGeneral;
#else
typedef struct CDlgGenGeneral CDlgGenGeneral;
#endif /* __cplusplus */

#endif 	/* __CDlgGenGeneral_FWD_DEFINED__ */


#ifndef __IDlgXfIfft_FWD_DEFINED__
#define __IDlgXfIfft_FWD_DEFINED__
typedef interface IDlgXfIfft IDlgXfIfft;
#endif 	/* __IDlgXfIfft_FWD_DEFINED__ */


#ifndef __CDlgXfIfft_FWD_DEFINED__
#define __CDlgXfIfft_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgXfIfft CDlgXfIfft;
#else
typedef struct CDlgXfIfft CDlgXfIfft;
#endif /* __cplusplus */

#endif 	/* __CDlgXfIfft_FWD_DEFINED__ */


#ifndef __IDlgXfFft_FWD_DEFINED__
#define __IDlgXfFft_FWD_DEFINED__
typedef interface IDlgXfFft IDlgXfFft;
#endif 	/* __IDlgXfFft_FWD_DEFINED__ */


#ifndef __CDlgXfFft_FWD_DEFINED__
#define __CDlgXfFft_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgXfFft CDlgXfFft;
#else
typedef struct CDlgXfFft CDlgXfFft;
#endif /* __cplusplus */

#endif 	/* __CDlgXfFft_FWD_DEFINED__ */


#ifndef __IDlgRecord_FWD_DEFINED__
#define __IDlgRecord_FWD_DEFINED__
typedef interface IDlgRecord IDlgRecord;
#endif 	/* __IDlgRecord_FWD_DEFINED__ */


#ifndef __CDlgRecord_FWD_DEFINED__
#define __CDlgRecord_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgRecord CDlgRecord;
#else
typedef struct CDlgRecord CDlgRecord;
#endif /* __cplusplus */

#endif 	/* __CDlgRecord_FWD_DEFINED__ */


#ifndef __IDlgXcImpedance_FWD_DEFINED__
#define __IDlgXcImpedance_FWD_DEFINED__
typedef interface IDlgXcImpedance IDlgXcImpedance;
#endif 	/* __IDlgXcImpedance_FWD_DEFINED__ */


#ifndef __CDlgXcImpedance_FWD_DEFINED__
#define __CDlgXcImpedance_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgXcImpedance CDlgXcImpedance;
#else
typedef struct CDlgXcImpedance CDlgXcImpedance;
#endif /* __cplusplus */

#endif 	/* __CDlgXcImpedance_FWD_DEFINED__ */


#ifndef __IDlgPrefTransform_FWD_DEFINED__
#define __IDlgPrefTransform_FWD_DEFINED__
typedef interface IDlgPrefTransform IDlgPrefTransform;
#endif 	/* __IDlgPrefTransform_FWD_DEFINED__ */


#ifndef __CDlgPrefTransform_FWD_DEFINED__
#define __CDlgPrefTransform_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgPrefTransform CDlgPrefTransform;
#else
typedef struct CDlgPrefTransform CDlgPrefTransform;
#endif /* __cplusplus */

#endif 	/* __CDlgPrefTransform_FWD_DEFINED__ */


#ifndef __IDlgPlaySound_FWD_DEFINED__
#define __IDlgPlaySound_FWD_DEFINED__
typedef interface IDlgPlaySound IDlgPlaySound;
#endif 	/* __IDlgPlaySound_FWD_DEFINED__ */


#ifndef __CDlgPlaySound_FWD_DEFINED__
#define __CDlgPlaySound_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgPlaySound CDlgPlaySound;
#else
typedef struct CDlgPlaySound CDlgPlaySound;
#endif /* __cplusplus */

#endif 	/* __CDlgPlaySound_FWD_DEFINED__ */


#ifndef __IDlgPrefNetwork_FWD_DEFINED__
#define __IDlgPrefNetwork_FWD_DEFINED__
typedef interface IDlgPrefNetwork IDlgPrefNetwork;
#endif 	/* __IDlgPrefNetwork_FWD_DEFINED__ */


#ifndef __CDlgPrefNetwork_FWD_DEFINED__
#define __CDlgPrefNetwork_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgPrefNetwork CDlgPrefNetwork;
#else
typedef struct CDlgPrefNetwork CDlgPrefNetwork;
#endif /* __cplusplus */

#endif 	/* __CDlgPrefNetwork_FWD_DEFINED__ */


#ifndef __IDlgPassiveProp_FWD_DEFINED__
#define __IDlgPassiveProp_FWD_DEFINED__
typedef interface IDlgPassiveProp IDlgPassiveProp;
#endif 	/* __IDlgPassiveProp_FWD_DEFINED__ */


#ifndef __CDlgPassiveProp_FWD_DEFINED__
#define __CDlgPassiveProp_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgPassiveProp CDlgPassiveProp;
#else
typedef struct CDlgPassiveProp CDlgPassiveProp;
#endif /* __cplusplus */

#endif 	/* __CDlgPassiveProp_FWD_DEFINED__ */


#ifndef __IDlgPerturb_FWD_DEFINED__
#define __IDlgPerturb_FWD_DEFINED__
typedef interface IDlgPerturb IDlgPerturb;
#endif 	/* __IDlgPerturb_FWD_DEFINED__ */


#ifndef __CDlgPerturb_FWD_DEFINED__
#define __CDlgPerturb_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgPerturb CDlgPerturb;
#else
typedef struct CDlgPerturb CDlgPerturb;
#endif /* __cplusplus */

#endif 	/* __CDlgPerturb_FWD_DEFINED__ */


#ifndef __IDlgXfCorrelate_FWD_DEFINED__
#define __IDlgXfCorrelate_FWD_DEFINED__
typedef interface IDlgXfCorrelate IDlgXfCorrelate;
#endif 	/* __IDlgXfCorrelate_FWD_DEFINED__ */


#ifndef __CDlgXfCorrelate_FWD_DEFINED__
#define __CDlgXfCorrelate_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgXfCorrelate CDlgXfCorrelate;
#else
typedef struct CDlgXfCorrelate CDlgXfCorrelate;
#endif /* __cplusplus */

#endif 	/* __CDlgXfCorrelate_FWD_DEFINED__ */


#ifndef __IDlgDriver_FWD_DEFINED__
#define __IDlgDriver_FWD_DEFINED__
typedef interface IDlgDriver IDlgDriver;
#endif 	/* __IDlgDriver_FWD_DEFINED__ */


#ifndef __CDlgDriver_FWD_DEFINED__
#define __CDlgDriver_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgDriver CDlgDriver;
#else
typedef struct CDlgDriver CDlgDriver;
#endif /* __cplusplus */

#endif 	/* __CDlgDriver_FWD_DEFINED__ */


#ifndef __IDlgDrData_FWD_DEFINED__
#define __IDlgDrData_FWD_DEFINED__
typedef interface IDlgDrData IDlgDrData;
#endif 	/* __IDlgDrData_FWD_DEFINED__ */


#ifndef __CDlgDrData_FWD_DEFINED__
#define __CDlgDrData_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgDrData CDlgDrData;
#else
typedef struct CDlgDrData CDlgDrData;
#endif /* __cplusplus */

#endif 	/* __CDlgDrData_FWD_DEFINED__ */


#ifndef __IDlgDrGeneral_FWD_DEFINED__
#define __IDlgDrGeneral_FWD_DEFINED__
typedef interface IDlgDrGeneral IDlgDrGeneral;
#endif 	/* __IDlgDrGeneral_FWD_DEFINED__ */


#ifndef __CDlgDrGeneral_FWD_DEFINED__
#define __CDlgDrGeneral_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgDrGeneral CDlgDrGeneral;
#else
typedef struct CDlgDrGeneral CDlgDrGeneral;
#endif /* __cplusplus */

#endif 	/* __CDlgDrGeneral_FWD_DEFINED__ */


#ifndef __IDlgDrParms_FWD_DEFINED__
#define __IDlgDrParms_FWD_DEFINED__
typedef interface IDlgDrParms IDlgDrParms;
#endif 	/* __IDlgDrParms_FWD_DEFINED__ */


#ifndef __CDlgDrParms_FWD_DEFINED__
#define __CDlgDrParms_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgDrParms CDlgDrParms;
#else
typedef struct CDlgDrParms CDlgDrParms;
#endif /* __cplusplus */

#endif 	/* __CDlgDrParms_FWD_DEFINED__ */


#ifndef __IDlgSelectObject_FWD_DEFINED__
#define __IDlgSelectObject_FWD_DEFINED__
typedef interface IDlgSelectObject IDlgSelectObject;
#endif 	/* __IDlgSelectObject_FWD_DEFINED__ */


#ifndef __CDlgSelectObject_FWD_DEFINED__
#define __CDlgSelectObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgSelectObject CDlgSelectObject;
#else
typedef struct CDlgSelectObject CDlgSelectObject;
#endif /* __cplusplus */

#endif 	/* __CDlgSelectObject_FWD_DEFINED__ */


#ifndef __IDlgSimpleBox_FWD_DEFINED__
#define __IDlgSimpleBox_FWD_DEFINED__
typedef interface IDlgSimpleBox IDlgSimpleBox;
#endif 	/* __IDlgSimpleBox_FWD_DEFINED__ */


#ifndef __CDlgSimpleBox_FWD_DEFINED__
#define __CDlgSimpleBox_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgSimpleBox CDlgSimpleBox;
#else
typedef struct CDlgSimpleBox CDlgSimpleBox;
#endif /* __cplusplus */

#endif 	/* __CDlgSimpleBox_FWD_DEFINED__ */


#ifndef __IDlgEnGeneral_FWD_DEFINED__
#define __IDlgEnGeneral_FWD_DEFINED__
typedef interface IDlgEnGeneral IDlgEnGeneral;
#endif 	/* __IDlgEnGeneral_FWD_DEFINED__ */


#ifndef __CDlgEnGeneral_FWD_DEFINED__
#define __CDlgEnGeneral_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgEnGeneral CDlgEnGeneral;
#else
typedef struct CDlgEnGeneral CDlgEnGeneral;
#endif /* __cplusplus */

#endif 	/* __CDlgEnGeneral_FWD_DEFINED__ */


#ifndef __IDlgEnParms_FWD_DEFINED__
#define __IDlgEnParms_FWD_DEFINED__
typedef interface IDlgEnParms IDlgEnParms;
#endif 	/* __IDlgEnParms_FWD_DEFINED__ */


#ifndef __CDlgEnParms_FWD_DEFINED__
#define __CDlgEnParms_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgEnParms CDlgEnParms;
#else
typedef struct CDlgEnParms CDlgEnParms;
#endif /* __cplusplus */

#endif 	/* __CDlgEnParms_FWD_DEFINED__ */


#ifndef __IDlgEnclosure_FWD_DEFINED__
#define __IDlgEnclosure_FWD_DEFINED__
typedef interface IDlgEnclosure IDlgEnclosure;
#endif 	/* __IDlgEnclosure_FWD_DEFINED__ */


#ifndef __CDlgEnclosure_FWD_DEFINED__
#define __CDlgEnclosure_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgEnclosure CDlgEnclosure;
#else
typedef struct CDlgEnclosure CDlgEnclosure;
#endif /* __cplusplus */

#endif 	/* __CDlgEnclosure_FWD_DEFINED__ */


#ifndef __IDlgPrefChart_FWD_DEFINED__
#define __IDlgPrefChart_FWD_DEFINED__
typedef interface IDlgPrefChart IDlgPrefChart;
#endif 	/* __IDlgPrefChart_FWD_DEFINED__ */


#ifndef __CDlgPrefChart_FWD_DEFINED__
#define __CDlgPrefChart_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgPrefChart CDlgPrefChart;
#else
typedef struct CDlgPrefChart CDlgPrefChart;
#endif /* __cplusplus */

#endif 	/* __CDlgPrefChart_FWD_DEFINED__ */


#ifndef __IDlgGenUserDef_FWD_DEFINED__
#define __IDlgGenUserDef_FWD_DEFINED__
typedef interface IDlgGenUserDef IDlgGenUserDef;
#endif 	/* __IDlgGenUserDef_FWD_DEFINED__ */


#ifndef __CDlgGenUserDef_FWD_DEFINED__
#define __CDlgGenUserDef_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgGenUserDef CDlgGenUserDef;
#else
typedef struct CDlgGenUserDef CDlgGenUserDef;
#endif /* __cplusplus */

#endif 	/* __CDlgGenUserDef_FWD_DEFINED__ */


#ifndef __IDlgGenWarble_FWD_DEFINED__
#define __IDlgGenWarble_FWD_DEFINED__
typedef interface IDlgGenWarble IDlgGenWarble;
#endif 	/* __IDlgGenWarble_FWD_DEFINED__ */


#ifndef __CDlgGenWarble_FWD_DEFINED__
#define __CDlgGenWarble_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgGenWarble CDlgGenWarble;
#else
typedef struct CDlgGenWarble CDlgGenWarble;
#endif /* __cplusplus */

#endif 	/* __CDlgGenWarble_FWD_DEFINED__ */


#ifndef __IDlgXfInvert_FWD_DEFINED__
#define __IDlgXfInvert_FWD_DEFINED__
typedef interface IDlgXfInvert IDlgXfInvert;
#endif 	/* __IDlgXfInvert_FWD_DEFINED__ */


#ifndef __CDlgXfInvert_FWD_DEFINED__
#define __CDlgXfInvert_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgXfInvert CDlgXfInvert;
#else
typedef struct CDlgXfInvert CDlgXfInvert;
#endif /* __cplusplus */

#endif 	/* __CDlgXfInvert_FWD_DEFINED__ */


#ifndef __IDlgMsrPassive_FWD_DEFINED__
#define __IDlgMsrPassive_FWD_DEFINED__
typedef interface IDlgMsrPassive IDlgMsrPassive;
#endif 	/* __IDlgMsrPassive_FWD_DEFINED__ */


#ifndef __CDlgMsrPassive_FWD_DEFINED__
#define __CDlgMsrPassive_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgMsrPassive CDlgMsrPassive;
#else
typedef struct CDlgMsrPassive CDlgMsrPassive;
#endif /* __cplusplus */

#endif 	/* __CDlgMsrPassive_FWD_DEFINED__ */


#ifndef __IDlgCalcSealed_FWD_DEFINED__
#define __IDlgCalcSealed_FWD_DEFINED__
typedef interface IDlgCalcSealed IDlgCalcSealed;
#endif 	/* __IDlgCalcSealed_FWD_DEFINED__ */


#ifndef __CDlgCalcSealed_FWD_DEFINED__
#define __CDlgCalcSealed_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgCalcSealed CDlgCalcSealed;
#else
typedef struct CDlgCalcSealed CDlgCalcSealed;
#endif /* __cplusplus */

#endif 	/* __CDlgCalcSealed_FWD_DEFINED__ */


#ifndef __IDlgCalcBandAir_FWD_DEFINED__
#define __IDlgCalcBandAir_FWD_DEFINED__
typedef interface IDlgCalcBandAir IDlgCalcBandAir;
#endif 	/* __IDlgCalcBandAir_FWD_DEFINED__ */


#ifndef __CDlgCalcBandAir_FWD_DEFINED__
#define __CDlgCalcBandAir_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgCalcBandAir CDlgCalcBandAir;
#else
typedef struct CDlgCalcBandAir CDlgCalcBandAir;
#endif /* __cplusplus */

#endif 	/* __CDlgCalcBandAir_FWD_DEFINED__ */


#ifndef __IDlgCalcBandChamber_FWD_DEFINED__
#define __IDlgCalcBandChamber_FWD_DEFINED__
typedef interface IDlgCalcBandChamber IDlgCalcBandChamber;
#endif 	/* __IDlgCalcBandChamber_FWD_DEFINED__ */


#ifndef __CDlgCalcBandChamber_FWD_DEFINED__
#define __CDlgCalcBandChamber_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgCalcBandChamber CDlgCalcBandChamber;
#else
typedef struct CDlgCalcBandChamber CDlgCalcBandChamber;
#endif /* __cplusplus */

#endif 	/* __CDlgCalcBandChamber_FWD_DEFINED__ */


#ifndef __IDlgCalcVented_FWD_DEFINED__
#define __IDlgCalcVented_FWD_DEFINED__
typedef interface IDlgCalcVented IDlgCalcVented;
#endif 	/* __IDlgCalcVented_FWD_DEFINED__ */


#ifndef __CDlgCalcVented_FWD_DEFINED__
#define __CDlgCalcVented_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgCalcVented CDlgCalcVented;
#else
typedef struct CDlgCalcVented CDlgCalcVented;
#endif /* __cplusplus */

#endif 	/* __CDlgCalcVented_FWD_DEFINED__ */


#ifndef __IDlgFilter_FWD_DEFINED__
#define __IDlgFilter_FWD_DEFINED__
typedef interface IDlgFilter IDlgFilter;
#endif 	/* __IDlgFilter_FWD_DEFINED__ */


#ifndef __CDlgFilter_FWD_DEFINED__
#define __CDlgFilter_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgFilter CDlgFilter;
#else
typedef struct CDlgFilter CDlgFilter;
#endif /* __cplusplus */

#endif 	/* __CDlgFilter_FWD_DEFINED__ */


#ifndef __IDlgPrefMeasure_FWD_DEFINED__
#define __IDlgPrefMeasure_FWD_DEFINED__
typedef interface IDlgPrefMeasure IDlgPrefMeasure;
#endif 	/* __IDlgPrefMeasure_FWD_DEFINED__ */


#ifndef __CDlgPrefMeasure_FWD_DEFINED__
#define __CDlgPrefMeasure_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgPrefMeasure CDlgPrefMeasure;
#else
typedef struct CDlgPrefMeasure CDlgPrefMeasure;
#endif /* __cplusplus */

#endif 	/* __CDlgPrefMeasure_FWD_DEFINED__ */


#ifndef __IDlgTree_FWD_DEFINED__
#define __IDlgTree_FWD_DEFINED__
typedef interface IDlgTree IDlgTree;
#endif 	/* __IDlgTree_FWD_DEFINED__ */


#ifndef __CDlgTree_FWD_DEFINED__
#define __CDlgTree_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgTree CDlgTree;
#else
typedef struct CDlgTree CDlgTree;
#endif /* __cplusplus */

#endif 	/* __CDlgTree_FWD_DEFINED__ */


#ifndef __IDlgXfFilter_FWD_DEFINED__
#define __IDlgXfFilter_FWD_DEFINED__
typedef interface IDlgXfFilter IDlgXfFilter;
#endif 	/* __IDlgXfFilter_FWD_DEFINED__ */


#ifndef __CDlgXfFilter_FWD_DEFINED__
#define __CDlgXfFilter_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgXfFilter CDlgXfFilter;
#else
typedef struct CDlgXfFilter CDlgXfFilter;
#endif /* __cplusplus */

#endif 	/* __CDlgXfFilter_FWD_DEFINED__ */


#ifndef __IDlgFilterLow_FWD_DEFINED__
#define __IDlgFilterLow_FWD_DEFINED__
typedef interface IDlgFilterLow IDlgFilterLow;
#endif 	/* __IDlgFilterLow_FWD_DEFINED__ */


#ifndef __CDlgFilterLow_FWD_DEFINED__
#define __CDlgFilterLow_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgFilterLow CDlgFilterLow;
#else
typedef struct CDlgFilterLow CDlgFilterLow;
#endif /* __cplusplus */

#endif 	/* __CDlgFilterLow_FWD_DEFINED__ */


#ifndef __IdlgFilterHigh_FWD_DEFINED__
#define __IdlgFilterHigh_FWD_DEFINED__
typedef interface IdlgFilterHigh IdlgFilterHigh;
#endif 	/* __IdlgFilterHigh_FWD_DEFINED__ */


#ifndef __CdlgFilterHigh_FWD_DEFINED__
#define __CdlgFilterHigh_FWD_DEFINED__

#ifdef __cplusplus
typedef class CdlgFilterHigh CdlgFilterHigh;
#else
typedef struct CdlgFilterHigh CdlgFilterHigh;
#endif /* __cplusplus */

#endif 	/* __CdlgFilterHigh_FWD_DEFINED__ */


#ifndef __IdlgFilterStop_FWD_DEFINED__
#define __IdlgFilterStop_FWD_DEFINED__
typedef interface IdlgFilterStop IdlgFilterStop;
#endif 	/* __IdlgFilterStop_FWD_DEFINED__ */


#ifndef __CdlgFilterStop_FWD_DEFINED__
#define __CdlgFilterStop_FWD_DEFINED__

#ifdef __cplusplus
typedef class CdlgFilterStop CdlgFilterStop;
#else
typedef struct CdlgFilterStop CdlgFilterStop;
#endif /* __cplusplus */

#endif 	/* __CdlgFilterStop_FWD_DEFINED__ */


#ifndef __IDlgFilterPass_FWD_DEFINED__
#define __IDlgFilterPass_FWD_DEFINED__
typedef interface IDlgFilterPass IDlgFilterPass;
#endif 	/* __IDlgFilterPass_FWD_DEFINED__ */


#ifndef __CDlgFilterPass_FWD_DEFINED__
#define __CDlgFilterPass_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgFilterPass CDlgFilterPass;
#else
typedef struct CDlgFilterPass CDlgFilterPass;
#endif /* __cplusplus */

#endif 	/* __CDlgFilterPass_FWD_DEFINED__ */


#ifndef __IDlgMsrDistort_FWD_DEFINED__
#define __IDlgMsrDistort_FWD_DEFINED__
typedef interface IDlgMsrDistort IDlgMsrDistort;
#endif 	/* __IDlgMsrDistort_FWD_DEFINED__ */


#ifndef __CDlgMsrDistort_FWD_DEFINED__
#define __CDlgMsrDistort_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgMsrDistort CDlgMsrDistort;
#else
typedef struct CDlgMsrDistort CDlgMsrDistort;
#endif /* __cplusplus */

#endif 	/* __CDlgMsrDistort_FWD_DEFINED__ */


#ifndef __IDlgPrefReference_FWD_DEFINED__
#define __IDlgPrefReference_FWD_DEFINED__
typedef interface IDlgPrefReference IDlgPrefReference;
#endif 	/* __IDlgPrefReference_FWD_DEFINED__ */


#ifndef __CDlgPrefReference_FWD_DEFINED__
#define __CDlgPrefReference_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgPrefReference CDlgPrefReference;
#else
typedef struct CDlgPrefReference CDlgPrefReference;
#endif /* __cplusplus */

#endif 	/* __CDlgPrefReference_FWD_DEFINED__ */


#ifndef __IDlgCalibrate_FWD_DEFINED__
#define __IDlgCalibrate_FWD_DEFINED__
typedef interface IDlgCalibrate IDlgCalibrate;
#endif 	/* __IDlgCalibrate_FWD_DEFINED__ */


#ifndef __CDlgCalibrate_FWD_DEFINED__
#define __CDlgCalibrate_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgCalibrate CDlgCalibrate;
#else
typedef struct CDlgCalibrate CDlgCalibrate;
#endif /* __cplusplus */

#endif 	/* __CDlgCalibrate_FWD_DEFINED__ */


#ifndef __IDlgCalcTuned_FWD_DEFINED__
#define __IDlgCalcTuned_FWD_DEFINED__
typedef interface IDlgCalcTuned IDlgCalcTuned;
#endif 	/* __IDlgCalcTuned_FWD_DEFINED__ */


#ifndef __CDlgCalcTuned_FWD_DEFINED__
#define __CDlgCalcTuned_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgCalcTuned CDlgCalcTuned;
#else
typedef struct CDlgCalcTuned CDlgCalcTuned;
#endif /* __cplusplus */

#endif 	/* __CDlgCalcTuned_FWD_DEFINED__ */


#ifndef __IDlgCalcPassive_FWD_DEFINED__
#define __IDlgCalcPassive_FWD_DEFINED__
typedef interface IDlgCalcPassive IDlgCalcPassive;
#endif 	/* __IDlgCalcPassive_FWD_DEFINED__ */


#ifndef __CDlgCalcPassive_FWD_DEFINED__
#define __CDlgCalcPassive_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgCalcPassive CDlgCalcPassive;
#else
typedef struct CDlgCalcPassive CDlgCalcPassive;
#endif /* __cplusplus */

#endif 	/* __CDlgCalcPassive_FWD_DEFINED__ */


#ifndef __IDlgPrefMarker_FWD_DEFINED__
#define __IDlgPrefMarker_FWD_DEFINED__
typedef interface IDlgPrefMarker IDlgPrefMarker;
#endif 	/* __IDlgPrefMarker_FWD_DEFINED__ */


#ifndef __CDlgPrefMarker_FWD_DEFINED__
#define __CDlgPrefMarker_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDlgPrefMarker CDlgPrefMarker;
#else
typedef struct CDlgPrefMarker CDlgPrefMarker;
#endif /* __cplusplus */

#endif 	/* __CDlgPrefMarker_FWD_DEFINED__ */


#ifndef __IDlgOptXover_FWD_DEFINED__
#define __IDlgOptXover_FWD_DEFINED__
typedef interface IDlgOptXover IDlgOptXover;
#endif 	/* __IDlgOptXover_FWD_DEFINED__ */


#ifndef __DLGOPTXOVER_FWD_DEFINED__
#define __DLGOPTXOVER_FWD_DEFINED__

#ifdef __cplusplus
typedef class DLGOPTXOVER DLGOPTXOVER;
#else
typedef struct DLGOPTXOVER DLGOPTXOVER;
#endif /* __cplusplus */

#endif 	/* __DLGOPTXOVER_FWD_DEFINED__ */


#ifndef __IDlgCrossover_FWD_DEFINED__
#define __IDlgCrossover_FWD_DEFINED__
typedef interface IDlgCrossover IDlgCrossover;
#endif 	/* __IDlgCrossover_FWD_DEFINED__ */


#ifndef __DLGCROSSOVER_FWD_DEFINED__
#define __DLGCROSSOVER_FWD_DEFINED__

#ifdef __cplusplus
typedef class DLGCROSSOVER DLGCROSSOVER;
#else
typedef struct DLGCROSSOVER DLGCROSSOVER;
#endif /* __cplusplus */

#endif 	/* __DLGCROSSOVER_FWD_DEFINED__ */


#ifndef __IDlgAddPassive_FWD_DEFINED__
#define __IDlgAddPassive_FWD_DEFINED__
typedef interface IDlgAddPassive IDlgAddPassive;
#endif 	/* __IDlgAddPassive_FWD_DEFINED__ */


#ifndef __DLGADDPASSIVE_FWD_DEFINED__
#define __DLGADDPASSIVE_FWD_DEFINED__

#ifdef __cplusplus
typedef class DLGADDPASSIVE DLGADDPASSIVE;
#else
typedef struct DLGADDPASSIVE DLGADDPASSIVE;
#endif /* __cplusplus */

#endif 	/* __DLGADDPASSIVE_FWD_DEFINED__ */


#ifndef __IDlgZobel_FWD_DEFINED__
#define __IDlgZobel_FWD_DEFINED__
typedef interface IDlgZobel IDlgZobel;
#endif 	/* __IDlgZobel_FWD_DEFINED__ */


#ifndef __DLGZOBEL_FWD_DEFINED__
#define __DLGZOBEL_FWD_DEFINED__

#ifdef __cplusplus
typedef class DLGZOBEL DLGZOBEL;
#else
typedef struct DLGZOBEL DLGZOBEL;
#endif /* __cplusplus */

#endif 	/* __DLGZOBEL_FWD_DEFINED__ */


#ifndef __IDlgNotch_FWD_DEFINED__
#define __IDlgNotch_FWD_DEFINED__
typedef interface IDlgNotch IDlgNotch;
#endif 	/* __IDlgNotch_FWD_DEFINED__ */


#ifndef __DLGNOTCH_FWD_DEFINED__
#define __DLGNOTCH_FWD_DEFINED__

#ifdef __cplusplus
typedef class DLGNOTCH DLGNOTCH;
#else
typedef struct DLGNOTCH DLGNOTCH;
#endif /* __cplusplus */

#endif 	/* __DLGNOTCH_FWD_DEFINED__ */


#ifndef __IDlgNetLayout_FWD_DEFINED__
#define __IDlgNetLayout_FWD_DEFINED__
typedef interface IDlgNetLayout IDlgNetLayout;
#endif 	/* __IDlgNetLayout_FWD_DEFINED__ */


#ifndef __DLGNETLAYOUT_FWD_DEFINED__
#define __DLGNETLAYOUT_FWD_DEFINED__

#ifdef __cplusplus
typedef class DLGNETLAYOUT DLGNETLAYOUT;
#else
typedef struct DLGNETLAYOUT DLGNETLAYOUT;
#endif /* __cplusplus */

#endif 	/* __DLGNETLAYOUT_FWD_DEFINED__ */


#ifndef __IDlgDriverEstimate_FWD_DEFINED__
#define __IDlgDriverEstimate_FWD_DEFINED__
typedef interface IDlgDriverEstimate IDlgDriverEstimate;
#endif 	/* __IDlgDriverEstimate_FWD_DEFINED__ */


#ifndef __DLGDRIVERESTIMATE_FWD_DEFINED__
#define __DLGDRIVERESTIMATE_FWD_DEFINED__

#ifdef __cplusplus
typedef class DLGDRIVERESTIMATE DLGDRIVERESTIMATE;
#else
typedef struct DLGDRIVERESTIMATE DLGDRIVERESTIMATE;
#endif /* __cplusplus */

#endif 	/* __DLGDRIVERESTIMATE_FWD_DEFINED__ */


#ifndef __IDlgXfSplice_FWD_DEFINED__
#define __IDlgXfSplice_FWD_DEFINED__
typedef interface IDlgXfSplice IDlgXfSplice;
#endif 	/* __IDlgXfSplice_FWD_DEFINED__ */


#ifndef __DLGXFSPLICE_FWD_DEFINED__
#define __DLGXFSPLICE_FWD_DEFINED__

#ifdef __cplusplus
typedef class DLGXFSPLICE DLGXFSPLICE;
#else
typedef struct DLGXFSPLICE DLGXFSPLICE;
#endif /* __cplusplus */

#endif 	/* __DLGXFSPLICE_FWD_DEFINED__ */


#ifndef __IDlgPrefImpedance_FWD_DEFINED__
#define __IDlgPrefImpedance_FWD_DEFINED__
typedef interface IDlgPrefImpedance IDlgPrefImpedance;
#endif 	/* __IDlgPrefImpedance_FWD_DEFINED__ */


#ifndef __DLGPREFIMPEDANCE_FWD_DEFINED__
#define __DLGPREFIMPEDANCE_FWD_DEFINED__

#ifdef __cplusplus
typedef class DLGPREFIMPEDANCE DLGPREFIMPEDANCE;
#else
typedef struct DLGPREFIMPEDANCE DLGPREFIMPEDANCE;
#endif /* __cplusplus */

#endif 	/* __DLGPREFIMPEDANCE_FWD_DEFINED__ */


#ifndef __IDlgPrefGeneral_FWD_DEFINED__
#define __IDlgPrefGeneral_FWD_DEFINED__
typedef interface IDlgPrefGeneral IDlgPrefGeneral;
#endif 	/* __IDlgPrefGeneral_FWD_DEFINED__ */


#ifndef __DLGPREFGENERAL_FWD_DEFINED__
#define __DLGPREFGENERAL_FWD_DEFINED__

#ifdef __cplusplus
typedef class DLGPREFGENERAL DLGPREFGENERAL;
#else
typedef struct DLGPREFGENERAL DLGPREFGENERAL;
#endif /* __cplusplus */

#endif 	/* __DLGPREFGENERAL_FWD_DEFINED__ */


#ifndef __IDlgCalJig3_FWD_DEFINED__
#define __IDlgCalJig3_FWD_DEFINED__
typedef interface IDlgCalJig3 IDlgCalJig3;
#endif 	/* __IDlgCalJig3_FWD_DEFINED__ */


#ifndef __DLGCALJIG3_FWD_DEFINED__
#define __DLGCALJIG3_FWD_DEFINED__

#ifdef __cplusplus
typedef class DLGCALJIG3 DLGCALJIG3;
#else
typedef struct DLGCALJIG3 DLGCALJIG3;
#endif /* __cplusplus */

#endif 	/* __DLGCALJIG3_FWD_DEFINED__ */


#ifndef __IDlgWizLoop_FWD_DEFINED__
#define __IDlgWizLoop_FWD_DEFINED__
typedef interface IDlgWizLoop IDlgWizLoop;
#endif 	/* __IDlgWizLoop_FWD_DEFINED__ */


#ifndef __DLGWIZLOOP_FWD_DEFINED__
#define __DLGWIZLOOP_FWD_DEFINED__

#ifdef __cplusplus
typedef class DLGWIZLOOP DLGWIZLOOP;
#else
typedef struct DLGWIZLOOP DLGWIZLOOP;
#endif /* __cplusplus */

#endif 	/* __DLGWIZLOOP_FWD_DEFINED__ */


#ifndef __IDlgWizLoopBegin_FWD_DEFINED__
#define __IDlgWizLoopBegin_FWD_DEFINED__
typedef interface IDlgWizLoopBegin IDlgWizLoopBegin;
#endif 	/* __IDlgWizLoopBegin_FWD_DEFINED__ */


#ifndef __DLGWIZLPBEGIN_FWD_DEFINED__
#define __DLGWIZLPBEGIN_FWD_DEFINED__

#ifdef __cplusplus
typedef class DLGWIZLPBEGIN DLGWIZLPBEGIN;
#else
typedef struct DLGWIZLPBEGIN DLGWIZLPBEGIN;
#endif /* __cplusplus */

#endif 	/* __DLGWIZLPBEGIN_FWD_DEFINED__ */


#ifndef __IDlgCalWizLoopEnd_FWD_DEFINED__
#define __IDlgCalWizLoopEnd_FWD_DEFINED__
typedef interface IDlgCalWizLoopEnd IDlgCalWizLoopEnd;
#endif 	/* __IDlgCalWizLoopEnd_FWD_DEFINED__ */


#ifndef __DLGCALWIZLOOPEND_FWD_DEFINED__
#define __DLGCALWIZLOOPEND_FWD_DEFINED__

#ifdef __cplusplus
typedef class DLGCALWIZLOOPEND DLGCALWIZLOOPEND;
#else
typedef struct DLGCALWIZLOOPEND DLGCALWIZLOOPEND;
#endif /* __cplusplus */

#endif 	/* __DLGCALWIZLOOPEND_FWD_DEFINED__ */


#ifndef __IDlgCalLoopJig_FWD_DEFINED__
#define __IDlgCalLoopJig_FWD_DEFINED__
typedef interface IDlgCalLoopJig IDlgCalLoopJig;
#endif 	/* __IDlgCalLoopJig_FWD_DEFINED__ */


#ifndef __DLGCALLOOPJIG_FWD_DEFINED__
#define __DLGCALLOOPJIG_FWD_DEFINED__

#ifdef __cplusplus
typedef class DLGCALLOOPJIG DLGCALLOOPJIG;
#else
typedef struct DLGCALLOOPJIG DLGCALLOOPJIG;
#endif /* __cplusplus */

#endif 	/* __DLGCALLOOPJIG_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 


#ifndef __audtest_LIBRARY_DEFINED__
#define __audtest_LIBRARY_DEFINED__

/* library audtest */
/* [version][uuid] */ 


DEFINE_GUID(LIBID_audtest,0x018FC421,0x7EE6,0x11CE,0xBC,0x27,0x44,0x45,0x53,0x54,0x00,0x00);

#ifndef __IAudtes_DISPINTERFACE_DEFINED__
#define __IAudtes_DISPINTERFACE_DEFINED__

/* dispinterface IAudtes */
/* [uuid] */ 


DEFINE_GUID(DIID_IAudtes,0x018FC422,0x7EE6,0x11CE,0xBC,0x27,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("018FC422-7EE6-11CE-BC27-444553540000")
    IAudtes : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IAudtesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAudtes * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAudtes * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAudtes * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IAudtes * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IAudtes * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IAudtes * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IAudtes * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IAudtesVtbl;

    interface IAudtes
    {
        CONST_VTBL struct IAudtesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAudtes_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAudtes_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAudtes_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAudtes_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAudtes_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAudtes_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAudtes_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IAudtes_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CAudtestDoc,0x018FC420,0x7EE6,0x11CE,0xBC,0x27,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("018FC420-7EE6-11CE-BC27-444553540000")
CAudtestDoc;
#endif

#ifndef __IDlgSweep_DISPINTERFACE_DEFINED__
#define __IDlgSweep_DISPINTERFACE_DEFINED__

/* dispinterface IDlgSweep */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgSweep,0xA21C48A2,0x7EEB,0x11CE,0xBC,0x27,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("A21C48A2-7EEB-11CE-BC27-444553540000")
    IDlgSweep : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgSweepVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgSweep * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgSweep * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgSweep * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgSweep * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgSweep * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgSweep * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgSweep * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgSweepVtbl;

    interface IDlgSweep
    {
        CONST_VTBL struct IDlgSweepVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgSweep_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgSweep_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgSweep_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgSweep_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgSweep_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgSweep_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgSweep_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgSweep_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgSweep,0xA21C48A3,0x7EEB,0x11CE,0xBC,0x27,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("A21C48A3-7EEB-11CE-BC27-444553540000")
CDlgSweep;
#endif

#ifndef __IDlgSine_DISPINTERFACE_DEFINED__
#define __IDlgSine_DISPINTERFACE_DEFINED__

/* dispinterface IDlgSine */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgSine,0xF83EBB20,0x7EEE,0x11CE,0xBC,0x27,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("F83EBB20-7EEE-11CE-BC27-444553540000")
    IDlgSine : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgSineVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgSine * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgSine * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgSine * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgSine * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgSine * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgSine * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgSine * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgSineVtbl;

    interface IDlgSine
    {
        CONST_VTBL struct IDlgSineVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgSine_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgSine_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgSine_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgSine_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgSine_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgSine_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgSine_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgSine_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgSine,0xF83EBB21,0x7EEE,0x11CE,0xBC,0x27,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("F83EBB21-7EEE-11CE-BC27-444553540000")
CDlgSine;
#endif

#ifndef __IDlgGenerator_DISPINTERFACE_DEFINED__
#define __IDlgGenerator_DISPINTERFACE_DEFINED__

/* dispinterface IDlgGenerator */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgGenerator,0xF83EBB22,0x7EEE,0x11CE,0xBC,0x27,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("F83EBB22-7EEE-11CE-BC27-444553540000")
    IDlgGenerator : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgGeneratorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgGenerator * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgGenerator * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgGenerator * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgGenerator * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgGenerator * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgGenerator * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgGenerator * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgGeneratorVtbl;

    interface IDlgGenerator
    {
        CONST_VTBL struct IDlgGeneratorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgGenerator_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgGenerator_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgGenerator_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgGenerator_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgGenerator_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgGenerator_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgGenerator_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgGenerator_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgGenerator,0xF83EBB23,0x7EEE,0x11CE,0xBC,0x27,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("F83EBB23-7EEE-11CE-BC27-444553540000")
CDlgGenerator;
#endif

#ifndef __IDlgPulse_DISPINTERFACE_DEFINED__
#define __IDlgPulse_DISPINTERFACE_DEFINED__

/* dispinterface IDlgPulse */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgPulse,0x26CA4F80,0x8486,0x11CE,0xBC,0x27,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("26CA4F80-8486-11CE-BC27-444553540000")
    IDlgPulse : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgPulseVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgPulse * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgPulse * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgPulse * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgPulse * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgPulse * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgPulse * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgPulse * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgPulseVtbl;

    interface IDlgPulse
    {
        CONST_VTBL struct IDlgPulseVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgPulse_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgPulse_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgPulse_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgPulse_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgPulse_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgPulse_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgPulse_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgPulse_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgPulse,0x26CA4F81,0x8486,0x11CE,0xBC,0x27,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("26CA4F81-8486-11CE-BC27-444553540000")
CDlgPulse;
#endif

#ifndef __IDlgMls_DISPINTERFACE_DEFINED__
#define __IDlgMls_DISPINTERFACE_DEFINED__

/* dispinterface IDlgMls */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgMls,0x26CA4F82,0x8486,0x11CE,0xBC,0x27,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("26CA4F82-8486-11CE-BC27-444553540000")
    IDlgMls : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgMlsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgMls * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgMls * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgMls * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgMls * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgMls * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgMls * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgMls * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgMlsVtbl;

    interface IDlgMls
    {
        CONST_VTBL struct IDlgMlsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgMls_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgMls_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgMls_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgMls_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgMls_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgMls_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgMls_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgMls_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgMls,0x26CA4F83,0x8486,0x11CE,0xBC,0x27,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("26CA4F83-8486-11CE-BC27-444553540000")
CDlgMls;
#endif

#ifndef __IDlgDsGeneral_DISPINTERFACE_DEFINED__
#define __IDlgDsGeneral_DISPINTERFACE_DEFINED__

/* dispinterface IDlgDsGeneral */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgDsGeneral,0x1711C9C0,0x8615,0x11CE,0xBC,0x27,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("1711C9C0-8615-11CE-BC27-444553540000")
    IDlgDsGeneral : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgDsGeneralVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgDsGeneral * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgDsGeneral * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgDsGeneral * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgDsGeneral * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgDsGeneral * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgDsGeneral * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgDsGeneral * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgDsGeneralVtbl;

    interface IDlgDsGeneral
    {
        CONST_VTBL struct IDlgDsGeneralVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgDsGeneral_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgDsGeneral_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgDsGeneral_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgDsGeneral_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgDsGeneral_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgDsGeneral_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgDsGeneral_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgDsGeneral_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgDsGeneral,0x1711C9C1,0x8615,0x11CE,0xBC,0x27,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("1711C9C1-8615-11CE-BC27-444553540000")
CDlgDsGeneral;
#endif

#ifndef __IDlgDataset_DISPINTERFACE_DEFINED__
#define __IDlgDataset_DISPINTERFACE_DEFINED__

/* dispinterface IDlgDataset */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgDataset,0x1711C9C2,0x8615,0x11CE,0xBC,0x27,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("1711C9C2-8615-11CE-BC27-444553540000")
    IDlgDataset : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgDatasetVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgDataset * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgDataset * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgDataset * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgDataset * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgDataset * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgDataset * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgDataset * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgDatasetVtbl;

    interface IDlgDataset
    {
        CONST_VTBL struct IDlgDatasetVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgDataset_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgDataset_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgDataset_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgDataset_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgDataset_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgDataset_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgDataset_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgDataset_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgDataset,0x1711C9C3,0x8615,0x11CE,0xBC,0x27,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("1711C9C3-8615-11CE-BC27-444553540000")
CDlgDataset;
#endif

#ifndef __IDlgChart_DISPINTERFACE_DEFINED__
#define __IDlgChart_DISPINTERFACE_DEFINED__

/* dispinterface IDlgChart */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgChart,0x74689AE0,0x8F93,0x11CE,0xBC,0x27,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("74689AE0-8F93-11CE-BC27-444553540000")
    IDlgChart : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgChartVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgChart * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgChart * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgChart * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgChart * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgChart * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgChart * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgChart * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgChartVtbl;

    interface IDlgChart
    {
        CONST_VTBL struct IDlgChartVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgChart_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgChart_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgChart_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgChart_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgChart_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgChart_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgChart_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgChart_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgChart,0x74689AE1,0x8F93,0x11CE,0xBC,0x27,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("74689AE1-8F93-11CE-BC27-444553540000")
CDlgChart;
#endif

#ifndef __IDlgDataLines_DISPINTERFACE_DEFINED__
#define __IDlgDataLines_DISPINTERFACE_DEFINED__

/* dispinterface IDlgDataLines */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgDataLines,0x74689AE2,0x8F93,0x11CE,0xBC,0x27,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("74689AE2-8F93-11CE-BC27-444553540000")
    IDlgDataLines : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgDataLinesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgDataLines * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgDataLines * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgDataLines * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgDataLines * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgDataLines * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgDataLines * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgDataLines * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgDataLinesVtbl;

    interface IDlgDataLines
    {
        CONST_VTBL struct IDlgDataLinesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgDataLines_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgDataLines_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgDataLines_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgDataLines_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgDataLines_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgDataLines_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgDataLines_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgDataLines_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgDataLines,0x74689AE3,0x8F93,0x11CE,0xBC,0x27,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("74689AE3-8F93-11CE-BC27-444553540000")
CDlgDataLines;
#endif

#ifndef __IDlgGrid_DISPINTERFACE_DEFINED__
#define __IDlgGrid_DISPINTERFACE_DEFINED__

/* dispinterface IDlgGrid */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgGrid,0xBD25DFE0,0x8F98,0x11CE,0xBC,0x27,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("BD25DFE0-8F98-11CE-BC27-444553540000")
    IDlgGrid : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgGridVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgGrid * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgGrid * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgGrid * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgGrid * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgGrid * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgGrid * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgGrid * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgGridVtbl;

    interface IDlgGrid
    {
        CONST_VTBL struct IDlgGridVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgGrid_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgGrid_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgGrid_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgGrid_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgGrid_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgGrid_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgGrid_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgGrid_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgGrid,0xBD25DFE1,0x8F98,0x11CE,0xBC,0x27,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("BD25DFE1-8F98-11CE-BC27-444553540000")
CDlgGrid;
#endif

#ifndef __IDlgChGen_DISPINTERFACE_DEFINED__
#define __IDlgChGen_DISPINTERFACE_DEFINED__

/* dispinterface IDlgChGen */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgChGen,0xBD25DFE2,0x8F98,0x11CE,0xBC,0x27,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("BD25DFE2-8F98-11CE-BC27-444553540000")
    IDlgChGen : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgChGenVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgChGen * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgChGen * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgChGen * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgChGen * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgChGen * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgChGen * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgChGen * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgChGenVtbl;

    interface IDlgChGen
    {
        CONST_VTBL struct IDlgChGenVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgChGen_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgChGen_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgChGen_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgChGen_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgChGen_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgChGen_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgChGen_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgChGen_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgChGen,0xBD25DFE3,0x8F98,0x11CE,0xBC,0x27,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("BD25DFE3-8F98-11CE-BC27-444553540000")
CDlgChGen;
#endif

#ifndef __IDlgChData_DISPINTERFACE_DEFINED__
#define __IDlgChData_DISPINTERFACE_DEFINED__

/* dispinterface IDlgChData */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgChData,0xBD25DFE4,0x8F98,0x11CE,0xBC,0x27,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("BD25DFE4-8F98-11CE-BC27-444553540000")
    IDlgChData : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgChDataVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgChData * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgChData * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgChData * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgChData * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgChData * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgChData * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgChData * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgChDataVtbl;

    interface IDlgChData
    {
        CONST_VTBL struct IDlgChDataVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgChData_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgChData_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgChData_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgChData_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgChData_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgChData_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgChData_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgChData_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgChData,0xBD25DFE5,0x8F98,0x11CE,0xBC,0x27,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("BD25DFE5-8F98-11CE-BC27-444553540000")
CDlgChData;
#endif

#ifndef __IAddChartData_DISPINTERFACE_DEFINED__
#define __IAddChartData_DISPINTERFACE_DEFINED__

/* dispinterface IAddChartData */
/* [uuid] */ 


DEFINE_GUID(DIID_IAddChartData,0x1EAA3880,0x9D11,0x11CE,0xBC,0x2D,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("1EAA3880-9D11-11CE-BC2D-444553540000")
    IAddChartData : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IAddChartDataVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAddChartData * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAddChartData * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAddChartData * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IAddChartData * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IAddChartData * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IAddChartData * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IAddChartData * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IAddChartDataVtbl;

    interface IAddChartData
    {
        CONST_VTBL struct IAddChartDataVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAddChartData_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAddChartData_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAddChartData_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAddChartData_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAddChartData_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAddChartData_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAddChartData_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IAddChartData_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CAddChartData,0x1EAA3881,0x9D11,0x11CE,0xBC,0x2D,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("1EAA3881-9D11-11CE-BC2D-444553540000")
CAddChartData;
#endif

#ifndef __IDlgXfLimit_DISPINTERFACE_DEFINED__
#define __IDlgXfLimit_DISPINTERFACE_DEFINED__

/* dispinterface IDlgXfLimit */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgXfLimit,0x33F08180,0xA27B,0x11CE,0xBC,0x2F,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("33F08180-A27B-11CE-BC2F-444553540000")
    IDlgXfLimit : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgXfLimitVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgXfLimit * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgXfLimit * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgXfLimit * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgXfLimit * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgXfLimit * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgXfLimit * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgXfLimit * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgXfLimitVtbl;

    interface IDlgXfLimit
    {
        CONST_VTBL struct IDlgXfLimitVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgXfLimit_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgXfLimit_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgXfLimit_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgXfLimit_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgXfLimit_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgXfLimit_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgXfLimit_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgXfLimit_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgXfLimit,0x33F08181,0xA27B,0x11CE,0xBC,0x2F,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("33F08181-A27B-11CE-BC2F-444553540000")
CDlgXfLimit;
#endif

#ifndef __IDlgXfScale_DISPINTERFACE_DEFINED__
#define __IDlgXfScale_DISPINTERFACE_DEFINED__

/* dispinterface IDlgXfScale */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgXfScale,0x43E4E880,0xA341,0x11CE,0xBC,0x2F,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("43E4E880-A341-11CE-BC2F-444553540000")
    IDlgXfScale : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgXfScaleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgXfScale * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgXfScale * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgXfScale * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgXfScale * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgXfScale * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgXfScale * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgXfScale * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgXfScaleVtbl;

    interface IDlgXfScale
    {
        CONST_VTBL struct IDlgXfScaleVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgXfScale_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgXfScale_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgXfScale_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgXfScale_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgXfScale_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgXfScale_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgXfScale_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgXfScale_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgXfScale,0x43E4E881,0xA341,0x11CE,0xBC,0x2F,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("43E4E881-A341-11CE-BC2F-444553540000")
CDlgXfScale;
#endif

#ifndef __IDlgXfTruncate_DISPINTERFACE_DEFINED__
#define __IDlgXfTruncate_DISPINTERFACE_DEFINED__

/* dispinterface IDlgXfTruncate */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgXfTruncate,0x72906560,0xA350,0x11CE,0xBC,0x2F,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("72906560-A350-11CE-BC2F-444553540000")
    IDlgXfTruncate : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgXfTruncateVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgXfTruncate * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgXfTruncate * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgXfTruncate * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgXfTruncate * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgXfTruncate * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgXfTruncate * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgXfTruncate * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgXfTruncateVtbl;

    interface IDlgXfTruncate
    {
        CONST_VTBL struct IDlgXfTruncateVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgXfTruncate_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgXfTruncate_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgXfTruncate_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgXfTruncate_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgXfTruncate_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgXfTruncate_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgXfTruncate_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgXfTruncate_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgXfTruncate,0x72906561,0xA350,0x11CE,0xBC,0x2F,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("72906561-A350-11CE-BC2F-444553540000")
CDlgXfTruncate;
#endif

#ifndef __IDlgXfDelay_DISPINTERFACE_DEFINED__
#define __IDlgXfDelay_DISPINTERFACE_DEFINED__

/* dispinterface IDlgXfDelay */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgXfDelay,0x5E601C00,0xA393,0x11CE,0xBC,0x2F,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("5E601C00-A393-11CE-BC2F-444553540000")
    IDlgXfDelay : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgXfDelayVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgXfDelay * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgXfDelay * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgXfDelay * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgXfDelay * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgXfDelay * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgXfDelay * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgXfDelay * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgXfDelayVtbl;

    interface IDlgXfDelay
    {
        CONST_VTBL struct IDlgXfDelayVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgXfDelay_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgXfDelay_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgXfDelay_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgXfDelay_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgXfDelay_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgXfDelay_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgXfDelay_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgXfDelay_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgXfDelay,0x5E601C01,0xA393,0x11CE,0xBC,0x2F,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("5E601C01-A393-11CE-BC2F-444553540000")
CDlgXfDelay;
#endif

#ifndef __IDlgXfSmooth_DISPINTERFACE_DEFINED__
#define __IDlgXfSmooth_DISPINTERFACE_DEFINED__

/* dispinterface IDlgXfSmooth */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgXfSmooth,0x5E601C02,0xA393,0x11CE,0xBC,0x2F,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("5E601C02-A393-11CE-BC2F-444553540000")
    IDlgXfSmooth : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgXfSmoothVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgXfSmooth * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgXfSmooth * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgXfSmooth * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgXfSmooth * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgXfSmooth * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgXfSmooth * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgXfSmooth * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgXfSmoothVtbl;

    interface IDlgXfSmooth
    {
        CONST_VTBL struct IDlgXfSmoothVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgXfSmooth_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgXfSmooth_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgXfSmooth_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgXfSmooth_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgXfSmooth_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgXfSmooth_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgXfSmooth_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgXfSmooth_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgXfSmooth,0x5E601C03,0xA393,0x11CE,0xBC,0x2F,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("5E601C03-A393-11CE-BC2F-444553540000")
CDlgXfSmooth;
#endif

#ifndef __IDlgDsDataset_DISPINTERFACE_DEFINED__
#define __IDlgDsDataset_DISPINTERFACE_DEFINED__

/* dispinterface IDlgDsDataset */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgDsDataset,0xA018E4C0,0xBAC6,0x11CE,0xB1,0xC7,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("A018E4C0-BAC6-11CE-B1C7-444553540000")
    IDlgDsDataset : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgDsDatasetVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgDsDataset * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgDsDataset * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgDsDataset * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgDsDataset * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgDsDataset * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgDsDataset * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgDsDataset * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgDsDatasetVtbl;

    interface IDlgDsDataset
    {
        CONST_VTBL struct IDlgDsDatasetVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgDsDataset_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgDsDataset_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgDsDataset_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgDsDataset_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgDsDataset_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgDsDataset_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgDsDataset_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgDsDataset_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgDsDataset,0xA018E4C1,0xBAC6,0x11CE,0xB1,0xC7,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("A018E4C1-BAC6-11CE-B1C7-444553540000")
CDlgDsDataset;
#endif

#ifndef __IDlgNetList_DISPINTERFACE_DEFINED__
#define __IDlgNetList_DISPINTERFACE_DEFINED__

/* dispinterface IDlgNetList */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgNetList,0xEF83D5C0,0xBCFF,0x11CE,0xB1,0xC8,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("EF83D5C0-BCFF-11CE-B1C8-444553540000")
    IDlgNetList : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgNetListVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgNetList * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgNetList * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgNetList * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgNetList * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgNetList * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgNetList * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgNetList * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgNetListVtbl;

    interface IDlgNetList
    {
        CONST_VTBL struct IDlgNetListVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgNetList_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgNetList_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgNetList_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgNetList_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgNetList_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgNetList_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgNetList_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgNetList_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgNetList,0xEF83D5C1,0xBCFF,0x11CE,0xB1,0xC8,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("EF83D5C1-BCFF-11CE-B1C8-444553540000")
CDlgNetList;
#endif

#ifndef __IDlgNetGeneral_DISPINTERFACE_DEFINED__
#define __IDlgNetGeneral_DISPINTERFACE_DEFINED__

/* dispinterface IDlgNetGeneral */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgNetGeneral,0xEF83D5C2,0xBCFF,0x11CE,0xB1,0xC8,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("EF83D5C2-BCFF-11CE-B1C8-444553540000")
    IDlgNetGeneral : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgNetGeneralVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgNetGeneral * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgNetGeneral * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgNetGeneral * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgNetGeneral * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgNetGeneral * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgNetGeneral * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgNetGeneral * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgNetGeneralVtbl;

    interface IDlgNetGeneral
    {
        CONST_VTBL struct IDlgNetGeneralVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgNetGeneral_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgNetGeneral_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgNetGeneral_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgNetGeneral_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgNetGeneral_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgNetGeneral_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgNetGeneral_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgNetGeneral_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgNetGeneral,0xEF83D5C3,0xBCFF,0x11CE,0xB1,0xC8,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("EF83D5C3-BCFF-11CE-B1C8-444553540000")
CDlgNetGeneral;
#endif

#ifndef __IDlgNetDriver_DISPINTERFACE_DEFINED__
#define __IDlgNetDriver_DISPINTERFACE_DEFINED__

/* dispinterface IDlgNetDriver */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgNetDriver,0xEF83D5C4,0xBCFF,0x11CE,0xB1,0xC8,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("EF83D5C4-BCFF-11CE-B1C8-444553540000")
    IDlgNetDriver : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgNetDriverVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgNetDriver * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgNetDriver * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgNetDriver * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgNetDriver * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgNetDriver * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgNetDriver * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgNetDriver * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgNetDriverVtbl;

    interface IDlgNetDriver
    {
        CONST_VTBL struct IDlgNetDriverVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgNetDriver_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgNetDriver_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgNetDriver_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgNetDriver_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgNetDriver_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgNetDriver_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgNetDriver_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgNetDriver_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgNetDriver,0xEF83D5C5,0xBCFF,0x11CE,0xB1,0xC8,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("EF83D5C5-BCFF-11CE-B1C8-444553540000")
CDlgNetDriver;
#endif

#ifndef __IDlgNetwork_DISPINTERFACE_DEFINED__
#define __IDlgNetwork_DISPINTERFACE_DEFINED__

/* dispinterface IDlgNetwork */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgNetwork,0x0B496760,0xBD01,0x11CE,0xB1,0xC8,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("0B496760-BD01-11CE-B1C8-444553540000")
    IDlgNetwork : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgNetworkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgNetwork * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgNetwork * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgNetwork * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgNetwork * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgNetwork * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgNetwork * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgNetwork * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgNetworkVtbl;

    interface IDlgNetwork
    {
        CONST_VTBL struct IDlgNetworkVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgNetwork_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgNetwork_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgNetwork_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgNetwork_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgNetwork_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgNetwork_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgNetwork_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgNetwork_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgNetwork,0x0B496761,0xBD01,0x11CE,0xB1,0xC8,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("0B496761-BD01-11CE-B1C8-444553540000")
CDlgNetwork;
#endif

#ifndef __IDlgRoomGeneral_DISPINTERFACE_DEFINED__
#define __IDlgRoomGeneral_DISPINTERFACE_DEFINED__

/* dispinterface IDlgRoomGeneral */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgRoomGeneral,0xD46A8480,0xBD10,0x11CE,0xB1,0xC8,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("D46A8480-BD10-11CE-B1C8-444553540000")
    IDlgRoomGeneral : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgRoomGeneralVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgRoomGeneral * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgRoomGeneral * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgRoomGeneral * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgRoomGeneral * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgRoomGeneral * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgRoomGeneral * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgRoomGeneral * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgRoomGeneralVtbl;

    interface IDlgRoomGeneral
    {
        CONST_VTBL struct IDlgRoomGeneralVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgRoomGeneral_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgRoomGeneral_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgRoomGeneral_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgRoomGeneral_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgRoomGeneral_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgRoomGeneral_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgRoomGeneral_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgRoomGeneral_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgRoomGeneral,0xD46A8481,0xBD10,0x11CE,0xB1,0xC8,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("D46A8481-BD10-11CE-B1C8-444553540000")
CDlgRoomGeneral;
#endif

#ifndef __IDlgRoomBoxes_DISPINTERFACE_DEFINED__
#define __IDlgRoomBoxes_DISPINTERFACE_DEFINED__

/* dispinterface IDlgRoomBoxes */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgRoomBoxes,0xD46A8482,0xBD10,0x11CE,0xB1,0xC8,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("D46A8482-BD10-11CE-B1C8-444553540000")
    IDlgRoomBoxes : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgRoomBoxesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgRoomBoxes * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgRoomBoxes * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgRoomBoxes * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgRoomBoxes * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgRoomBoxes * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgRoomBoxes * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgRoomBoxes * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgRoomBoxesVtbl;

    interface IDlgRoomBoxes
    {
        CONST_VTBL struct IDlgRoomBoxesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgRoomBoxes_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgRoomBoxes_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgRoomBoxes_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgRoomBoxes_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgRoomBoxes_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgRoomBoxes_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgRoomBoxes_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgRoomBoxes_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgRoomBoxes,0xD46A8483,0xBD10,0x11CE,0xB1,0xC8,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("D46A8483-BD10-11CE-B1C8-444553540000")
CDlgRoomBoxes;
#endif

#ifndef __IDlgRoomWall_DISPINTERFACE_DEFINED__
#define __IDlgRoomWall_DISPINTERFACE_DEFINED__

/* dispinterface IDlgRoomWall */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgRoomWall,0xD46A8484,0xBD10,0x11CE,0xB1,0xC8,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("D46A8484-BD10-11CE-B1C8-444553540000")
    IDlgRoomWall : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgRoomWallVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgRoomWall * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgRoomWall * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgRoomWall * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgRoomWall * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgRoomWall * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgRoomWall * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgRoomWall * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgRoomWallVtbl;

    interface IDlgRoomWall
    {
        CONST_VTBL struct IDlgRoomWallVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgRoomWall_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgRoomWall_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgRoomWall_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgRoomWall_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgRoomWall_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgRoomWall_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgRoomWall_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgRoomWall_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgRoomWall,0xD46A8485,0xBD10,0x11CE,0xB1,0xC8,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("D46A8485-BD10-11CE-B1C8-444553540000")
CDlgRoomWall;
#endif

#ifndef __IDlgRoom_DISPINTERFACE_DEFINED__
#define __IDlgRoom_DISPINTERFACE_DEFINED__

/* dispinterface IDlgRoom */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgRoom,0xD46A8486,0xBD10,0x11CE,0xB1,0xC8,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("D46A8486-BD10-11CE-B1C8-444553540000")
    IDlgRoom : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgRoomVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgRoom * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgRoom * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgRoom * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgRoom * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgRoom * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgRoom * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgRoom * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgRoomVtbl;

    interface IDlgRoom
    {
        CONST_VTBL struct IDlgRoomVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgRoom_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgRoom_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgRoom_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgRoom_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgRoom_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgRoom_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgRoom_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgRoom_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgRoom,0xD46A8487,0xBD10,0x11CE,0xB1,0xC8,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("D46A8487-BD10-11CE-B1C8-444553540000")
CDlgRoom;
#endif

#ifndef __IDlgLocations_DISPINTERFACE_DEFINED__
#define __IDlgLocations_DISPINTERFACE_DEFINED__

/* dispinterface IDlgLocations */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgLocations,0x09D96940,0xC10A,0x11CE,0xB1,0xC8,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("09D96940-C10A-11CE-B1C8-444553540000")
    IDlgLocations : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgLocationsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgLocations * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgLocations * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgLocations * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgLocations * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgLocations * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgLocations * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgLocations * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgLocationsVtbl;

    interface IDlgLocations
    {
        CONST_VTBL struct IDlgLocationsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgLocations_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgLocations_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgLocations_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgLocations_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgLocations_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgLocations_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgLocations_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgLocations_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgLocations,0x09D96941,0xC10A,0x11CE,0xB1,0xC8,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("09D96941-C10A-11CE-B1C8-444553540000")
CDlgLocations;
#endif

#ifndef __IDlgGenGeneral_DISPINTERFACE_DEFINED__
#define __IDlgGenGeneral_DISPINTERFACE_DEFINED__

/* dispinterface IDlgGenGeneral */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgGenGeneral,0x4AF654E0,0xC1FC,0x11CE,0xB1,0xC8,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("4AF654E0-C1FC-11CE-B1C8-444553540000")
    IDlgGenGeneral : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgGenGeneralVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgGenGeneral * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgGenGeneral * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgGenGeneral * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgGenGeneral * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgGenGeneral * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgGenGeneral * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgGenGeneral * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgGenGeneralVtbl;

    interface IDlgGenGeneral
    {
        CONST_VTBL struct IDlgGenGeneralVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgGenGeneral_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgGenGeneral_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgGenGeneral_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgGenGeneral_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgGenGeneral_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgGenGeneral_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgGenGeneral_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgGenGeneral_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgGenGeneral,0x4AF654E1,0xC1FC,0x11CE,0xB1,0xC8,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("4AF654E1-C1FC-11CE-B1C8-444553540000")
CDlgGenGeneral;
#endif

#ifndef __IDlgXfIfft_DISPINTERFACE_DEFINED__
#define __IDlgXfIfft_DISPINTERFACE_DEFINED__

/* dispinterface IDlgXfIfft */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgXfIfft,0x8510D420,0xC283,0x11CE,0xB1,0xC8,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("8510D420-C283-11CE-B1C8-444553540000")
    IDlgXfIfft : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgXfIfftVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgXfIfft * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgXfIfft * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgXfIfft * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgXfIfft * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgXfIfft * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgXfIfft * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgXfIfft * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgXfIfftVtbl;

    interface IDlgXfIfft
    {
        CONST_VTBL struct IDlgXfIfftVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgXfIfft_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgXfIfft_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgXfIfft_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgXfIfft_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgXfIfft_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgXfIfft_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgXfIfft_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgXfIfft_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgXfIfft,0x8510D421,0xC283,0x11CE,0xB1,0xC8,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("8510D421-C283-11CE-B1C8-444553540000")
CDlgXfIfft;
#endif

#ifndef __IDlgXfFft_DISPINTERFACE_DEFINED__
#define __IDlgXfFft_DISPINTERFACE_DEFINED__

/* dispinterface IDlgXfFft */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgXfFft,0xB5EBC940,0xC294,0x11CE,0xB1,0xC8,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("B5EBC940-C294-11CE-B1C8-444553540000")
    IDlgXfFft : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgXfFftVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgXfFft * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgXfFft * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgXfFft * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgXfFft * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgXfFft * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgXfFft * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgXfFft * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgXfFftVtbl;

    interface IDlgXfFft
    {
        CONST_VTBL struct IDlgXfFftVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgXfFft_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgXfFft_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgXfFft_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgXfFft_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgXfFft_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgXfFft_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgXfFft_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgXfFft_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgXfFft,0xB5EBC941,0xC294,0x11CE,0xB1,0xC8,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("B5EBC941-C294-11CE-B1C8-444553540000")
CDlgXfFft;
#endif

#ifndef __IDlgRecord_DISPINTERFACE_DEFINED__
#define __IDlgRecord_DISPINTERFACE_DEFINED__

/* dispinterface IDlgRecord */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgRecord,0xAB427A00,0xC39F,0x11CE,0xB1,0xC8,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("AB427A00-C39F-11CE-B1C8-444553540000")
    IDlgRecord : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgRecordVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgRecord * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgRecord * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgRecord * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgRecord * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgRecord * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgRecord * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgRecord * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgRecordVtbl;

    interface IDlgRecord
    {
        CONST_VTBL struct IDlgRecordVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgRecord_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgRecord_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgRecord_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgRecord_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgRecord_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgRecord_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgRecord_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgRecord_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgRecord,0xAB427A01,0xC39F,0x11CE,0xB1,0xC8,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("AB427A01-C39F-11CE-B1C8-444553540000")
CDlgRecord;
#endif

#ifndef __IDlgXcImpedance_DISPINTERFACE_DEFINED__
#define __IDlgXcImpedance_DISPINTERFACE_DEFINED__

/* dispinterface IDlgXcImpedance */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgXcImpedance,0xA6726FE0,0xC556,0x11CE,0xB1,0xC8,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("A6726FE0-C556-11CE-B1C8-444553540000")
    IDlgXcImpedance : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgXcImpedanceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgXcImpedance * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgXcImpedance * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgXcImpedance * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgXcImpedance * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgXcImpedance * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgXcImpedance * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgXcImpedance * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgXcImpedanceVtbl;

    interface IDlgXcImpedance
    {
        CONST_VTBL struct IDlgXcImpedanceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgXcImpedance_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgXcImpedance_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgXcImpedance_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgXcImpedance_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgXcImpedance_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgXcImpedance_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgXcImpedance_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgXcImpedance_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgXcImpedance,0xA6726FE1,0xC556,0x11CE,0xB1,0xC8,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("A6726FE1-C556-11CE-B1C8-444553540000")
CDlgXcImpedance;
#endif

#ifndef __IDlgPrefTransform_DISPINTERFACE_DEFINED__
#define __IDlgPrefTransform_DISPINTERFACE_DEFINED__

/* dispinterface IDlgPrefTransform */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgPrefTransform,0x37A70D20,0xC757,0x11CE,0xB1,0xC9,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("37A70D20-C757-11CE-B1C9-444553540000")
    IDlgPrefTransform : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgPrefTransformVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgPrefTransform * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgPrefTransform * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgPrefTransform * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgPrefTransform * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgPrefTransform * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgPrefTransform * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgPrefTransform * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgPrefTransformVtbl;

    interface IDlgPrefTransform
    {
        CONST_VTBL struct IDlgPrefTransformVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgPrefTransform_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgPrefTransform_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgPrefTransform_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgPrefTransform_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgPrefTransform_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgPrefTransform_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgPrefTransform_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgPrefTransform_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgPrefTransform,0x37A70D21,0xC757,0x11CE,0xB1,0xC9,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("37A70D21-C757-11CE-B1C9-444553540000")
CDlgPrefTransform;
#endif

#ifndef __IDlgPlaySound_DISPINTERFACE_DEFINED__
#define __IDlgPlaySound_DISPINTERFACE_DEFINED__

/* dispinterface IDlgPlaySound */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgPlaySound,0x80FF7480,0xE9E9,0x11CE,0xB1,0xCB,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("80FF7480-E9E9-11CE-B1CB-444553540000")
    IDlgPlaySound : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgPlaySoundVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgPlaySound * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgPlaySound * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgPlaySound * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgPlaySound * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgPlaySound * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgPlaySound * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgPlaySound * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgPlaySoundVtbl;

    interface IDlgPlaySound
    {
        CONST_VTBL struct IDlgPlaySoundVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgPlaySound_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgPlaySound_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgPlaySound_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgPlaySound_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgPlaySound_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgPlaySound_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgPlaySound_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgPlaySound_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgPlaySound,0x80FF7481,0xE9E9,0x11CE,0xB1,0xCB,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("80FF7481-E9E9-11CE-B1CB-444553540000")
CDlgPlaySound;
#endif

#ifndef __IDlgPrefNetwork_DISPINTERFACE_DEFINED__
#define __IDlgPrefNetwork_DISPINTERFACE_DEFINED__

/* dispinterface IDlgPrefNetwork */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgPrefNetwork,0xDC271960,0xEDB0,0x11CE,0xB1,0xCB,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("DC271960-EDB0-11CE-B1CB-444553540000")
    IDlgPrefNetwork : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgPrefNetworkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgPrefNetwork * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgPrefNetwork * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgPrefNetwork * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgPrefNetwork * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgPrefNetwork * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgPrefNetwork * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgPrefNetwork * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgPrefNetworkVtbl;

    interface IDlgPrefNetwork
    {
        CONST_VTBL struct IDlgPrefNetworkVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgPrefNetwork_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgPrefNetwork_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgPrefNetwork_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgPrefNetwork_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgPrefNetwork_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgPrefNetwork_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgPrefNetwork_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgPrefNetwork_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgPrefNetwork,0xDC271961,0xEDB0,0x11CE,0xB1,0xCB,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("DC271961-EDB0-11CE-B1CB-444553540000")
CDlgPrefNetwork;
#endif

#ifndef __IDlgPassiveProp_DISPINTERFACE_DEFINED__
#define __IDlgPassiveProp_DISPINTERFACE_DEFINED__

/* dispinterface IDlgPassiveProp */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgPassiveProp,0xF5FCE180,0xEE78,0x11CE,0xB1,0xCB,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("F5FCE180-EE78-11CE-B1CB-444553540000")
    IDlgPassiveProp : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgPassivePropVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgPassiveProp * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgPassiveProp * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgPassiveProp * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgPassiveProp * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgPassiveProp * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgPassiveProp * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgPassiveProp * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgPassivePropVtbl;

    interface IDlgPassiveProp
    {
        CONST_VTBL struct IDlgPassivePropVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgPassiveProp_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgPassiveProp_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgPassiveProp_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgPassiveProp_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgPassiveProp_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgPassiveProp_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgPassiveProp_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgPassiveProp_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgPassiveProp,0xF5FCE181,0xEE78,0x11CE,0xB1,0xCB,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("F5FCE181-EE78-11CE-B1CB-444553540000")
CDlgPassiveProp;
#endif

#ifndef __IDlgPerturb_DISPINTERFACE_DEFINED__
#define __IDlgPerturb_DISPINTERFACE_DEFINED__

/* dispinterface IDlgPerturb */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgPerturb,0x25A108A0,0xF1DD,0x11CE,0xB1,0xCB,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("25A108A0-F1DD-11CE-B1CB-444553540000")
    IDlgPerturb : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgPerturbVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgPerturb * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgPerturb * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgPerturb * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgPerturb * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgPerturb * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgPerturb * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgPerturb * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgPerturbVtbl;

    interface IDlgPerturb
    {
        CONST_VTBL struct IDlgPerturbVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgPerturb_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgPerturb_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgPerturb_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgPerturb_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgPerturb_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgPerturb_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgPerturb_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgPerturb_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgPerturb,0x25A108A1,0xF1DD,0x11CE,0xB1,0xCB,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("25A108A1-F1DD-11CE-B1CB-444553540000")
CDlgPerturb;
#endif

#ifndef __IDlgXfCorrelate_DISPINTERFACE_DEFINED__
#define __IDlgXfCorrelate_DISPINTERFACE_DEFINED__

/* dispinterface IDlgXfCorrelate */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgXfCorrelate,0x62C3A720,0xF47A,0x11CE,0xB1,0xCB,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("62C3A720-F47A-11CE-B1CB-444553540000")
    IDlgXfCorrelate : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgXfCorrelateVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgXfCorrelate * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgXfCorrelate * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgXfCorrelate * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgXfCorrelate * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgXfCorrelate * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgXfCorrelate * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgXfCorrelate * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgXfCorrelateVtbl;

    interface IDlgXfCorrelate
    {
        CONST_VTBL struct IDlgXfCorrelateVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgXfCorrelate_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgXfCorrelate_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgXfCorrelate_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgXfCorrelate_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgXfCorrelate_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgXfCorrelate_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgXfCorrelate_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgXfCorrelate_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgXfCorrelate,0x62C3A721,0xF47A,0x11CE,0xB1,0xCB,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("62C3A721-F47A-11CE-B1CB-444553540000")
CDlgXfCorrelate;
#endif

#ifndef __IDlgDriver_DISPINTERFACE_DEFINED__
#define __IDlgDriver_DISPINTERFACE_DEFINED__

/* dispinterface IDlgDriver */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgDriver,0xC7800800,0xF5B7,0x11CE,0xB1,0xCB,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("C7800800-F5B7-11CE-B1CB-444553540000")
    IDlgDriver : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgDriverVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgDriver * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgDriver * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgDriver * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgDriver * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgDriver * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgDriver * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgDriver * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgDriverVtbl;

    interface IDlgDriver
    {
        CONST_VTBL struct IDlgDriverVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgDriver_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgDriver_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgDriver_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgDriver_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgDriver_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgDriver_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgDriver_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgDriver_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgDriver,0xC7800801,0xF5B7,0x11CE,0xB1,0xCB,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("C7800801-F5B7-11CE-B1CB-444553540000")
CDlgDriver;
#endif

#ifndef __IDlgDrData_DISPINTERFACE_DEFINED__
#define __IDlgDrData_DISPINTERFACE_DEFINED__

/* dispinterface IDlgDrData */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgDrData,0xC7800802,0xF5B7,0x11CE,0xB1,0xCB,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("C7800802-F5B7-11CE-B1CB-444553540000")
    IDlgDrData : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgDrDataVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgDrData * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgDrData * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgDrData * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgDrData * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgDrData * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgDrData * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgDrData * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgDrDataVtbl;

    interface IDlgDrData
    {
        CONST_VTBL struct IDlgDrDataVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgDrData_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgDrData_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgDrData_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgDrData_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgDrData_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgDrData_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgDrData_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgDrData_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgDrData,0xC7800803,0xF5B7,0x11CE,0xB1,0xCB,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("C7800803-F5B7-11CE-B1CB-444553540000")
CDlgDrData;
#endif

#ifndef __IDlgDrGeneral_DISPINTERFACE_DEFINED__
#define __IDlgDrGeneral_DISPINTERFACE_DEFINED__

/* dispinterface IDlgDrGeneral */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgDrGeneral,0xC7800804,0xF5B7,0x11CE,0xB1,0xCB,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("C7800804-F5B7-11CE-B1CB-444553540000")
    IDlgDrGeneral : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgDrGeneralVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgDrGeneral * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgDrGeneral * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgDrGeneral * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgDrGeneral * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgDrGeneral * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgDrGeneral * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgDrGeneral * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgDrGeneralVtbl;

    interface IDlgDrGeneral
    {
        CONST_VTBL struct IDlgDrGeneralVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgDrGeneral_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgDrGeneral_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgDrGeneral_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgDrGeneral_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgDrGeneral_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgDrGeneral_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgDrGeneral_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgDrGeneral_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgDrGeneral,0xC7800805,0xF5B7,0x11CE,0xB1,0xCB,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("C7800805-F5B7-11CE-B1CB-444553540000")
CDlgDrGeneral;
#endif

#ifndef __IDlgDrParms_DISPINTERFACE_DEFINED__
#define __IDlgDrParms_DISPINTERFACE_DEFINED__

/* dispinterface IDlgDrParms */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgDrParms,0xC7800806,0xF5B7,0x11CE,0xB1,0xCB,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("C7800806-F5B7-11CE-B1CB-444553540000")
    IDlgDrParms : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgDrParmsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgDrParms * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgDrParms * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgDrParms * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgDrParms * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgDrParms * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgDrParms * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgDrParms * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgDrParmsVtbl;

    interface IDlgDrParms
    {
        CONST_VTBL struct IDlgDrParmsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgDrParms_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgDrParms_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgDrParms_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgDrParms_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgDrParms_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgDrParms_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgDrParms_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgDrParms_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgDrParms,0xC7800807,0xF5B7,0x11CE,0xB1,0xCB,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("C7800807-F5B7-11CE-B1CB-444553540000")
CDlgDrParms;
#endif

#ifndef __IDlgSelectObject_DISPINTERFACE_DEFINED__
#define __IDlgSelectObject_DISPINTERFACE_DEFINED__

/* dispinterface IDlgSelectObject */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgSelectObject,0xDDE21BA0,0xF6CB,0x11CE,0xB1,0xCB,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("DDE21BA0-F6CB-11CE-B1CB-444553540000")
    IDlgSelectObject : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgSelectObjectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgSelectObject * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgSelectObject * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgSelectObject * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgSelectObject * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgSelectObject * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgSelectObject * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgSelectObject * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgSelectObjectVtbl;

    interface IDlgSelectObject
    {
        CONST_VTBL struct IDlgSelectObjectVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgSelectObject_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgSelectObject_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgSelectObject_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgSelectObject_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgSelectObject_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgSelectObject_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgSelectObject_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgSelectObject_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgSelectObject,0xDDE21BA1,0xF6CB,0x11CE,0xB1,0xCB,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("DDE21BA1-F6CB-11CE-B1CB-444553540000")
CDlgSelectObject;
#endif

#ifndef __IDlgSimpleBox_DISPINTERFACE_DEFINED__
#define __IDlgSimpleBox_DISPINTERFACE_DEFINED__

/* dispinterface IDlgSimpleBox */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgSimpleBox,0xCA31E040,0xF996,0x11CE,0xB1,0xCB,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("CA31E040-F996-11CE-B1CB-444553540000")
    IDlgSimpleBox : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgSimpleBoxVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgSimpleBox * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgSimpleBox * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgSimpleBox * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgSimpleBox * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgSimpleBox * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgSimpleBox * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgSimpleBox * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgSimpleBoxVtbl;

    interface IDlgSimpleBox
    {
        CONST_VTBL struct IDlgSimpleBoxVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgSimpleBox_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgSimpleBox_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgSimpleBox_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgSimpleBox_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgSimpleBox_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgSimpleBox_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgSimpleBox_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgSimpleBox_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgSimpleBox,0xCA31E041,0xF996,0x11CE,0xB1,0xCB,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("CA31E041-F996-11CE-B1CB-444553540000")
CDlgSimpleBox;
#endif

#ifndef __IDlgEnGeneral_DISPINTERFACE_DEFINED__
#define __IDlgEnGeneral_DISPINTERFACE_DEFINED__

/* dispinterface IDlgEnGeneral */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgEnGeneral,0x97906F80,0xDB7E,0x11CD,0xB1,0xCC,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("97906F80-DB7E-11CD-B1CC-444553540000")
    IDlgEnGeneral : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgEnGeneralVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgEnGeneral * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgEnGeneral * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgEnGeneral * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgEnGeneral * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgEnGeneral * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgEnGeneral * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgEnGeneral * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgEnGeneralVtbl;

    interface IDlgEnGeneral
    {
        CONST_VTBL struct IDlgEnGeneralVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgEnGeneral_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgEnGeneral_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgEnGeneral_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgEnGeneral_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgEnGeneral_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgEnGeneral_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgEnGeneral_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgEnGeneral_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgEnGeneral,0x97906F81,0xDB7E,0x11CD,0xB1,0xCC,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("97906F81-DB7E-11CD-B1CC-444553540000")
CDlgEnGeneral;
#endif

#ifndef __IDlgEnParms_DISPINTERFACE_DEFINED__
#define __IDlgEnParms_DISPINTERFACE_DEFINED__

/* dispinterface IDlgEnParms */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgEnParms,0x97906F82,0xDB7E,0x11CD,0xB1,0xCC,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("97906F82-DB7E-11CD-B1CC-444553540000")
    IDlgEnParms : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgEnParmsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgEnParms * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgEnParms * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgEnParms * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgEnParms * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgEnParms * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgEnParms * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgEnParms * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgEnParmsVtbl;

    interface IDlgEnParms
    {
        CONST_VTBL struct IDlgEnParmsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgEnParms_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgEnParms_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgEnParms_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgEnParms_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgEnParms_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgEnParms_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgEnParms_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgEnParms_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgEnParms,0x97906F83,0xDB7E,0x11CD,0xB1,0xCC,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("97906F83-DB7E-11CD-B1CC-444553540000")
CDlgEnParms;
#endif

#ifndef __IDlgEnclosure_DISPINTERFACE_DEFINED__
#define __IDlgEnclosure_DISPINTERFACE_DEFINED__

/* dispinterface IDlgEnclosure */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgEnclosure,0x1C2F3DC0,0xDB7F,0x11CD,0xB1,0xCC,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("1C2F3DC0-DB7F-11CD-B1CC-444553540000")
    IDlgEnclosure : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgEnclosureVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgEnclosure * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgEnclosure * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgEnclosure * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgEnclosure * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgEnclosure * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgEnclosure * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgEnclosure * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgEnclosureVtbl;

    interface IDlgEnclosure
    {
        CONST_VTBL struct IDlgEnclosureVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgEnclosure_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgEnclosure_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgEnclosure_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgEnclosure_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgEnclosure_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgEnclosure_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgEnclosure_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgEnclosure_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgEnclosure,0x1C2F3DC1,0xDB7F,0x11CD,0xB1,0xCC,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("1C2F3DC1-DB7F-11CD-B1CC-444553540000")
CDlgEnclosure;
#endif

#ifndef __IDlgPrefChart_DISPINTERFACE_DEFINED__
#define __IDlgPrefChart_DISPINTERFACE_DEFINED__

/* dispinterface IDlgPrefChart */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgPrefChart,0xA418ED40,0x00A3,0x11CF,0xB1,0xCD,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("A418ED40-00A3-11CF-B1CD-444553540000")
    IDlgPrefChart : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgPrefChartVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgPrefChart * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgPrefChart * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgPrefChart * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgPrefChart * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgPrefChart * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgPrefChart * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgPrefChart * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgPrefChartVtbl;

    interface IDlgPrefChart
    {
        CONST_VTBL struct IDlgPrefChartVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgPrefChart_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgPrefChart_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgPrefChart_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgPrefChart_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgPrefChart_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgPrefChart_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgPrefChart_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgPrefChart_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgPrefChart,0xA418ED41,0x00A3,0x11CF,0xB1,0xCD,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("A418ED41-00A3-11CF-B1CD-444553540000")
CDlgPrefChart;
#endif

#ifndef __IDlgGenUserDef_DISPINTERFACE_DEFINED__
#define __IDlgGenUserDef_DISPINTERFACE_DEFINED__

/* dispinterface IDlgGenUserDef */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgGenUserDef,0x96916B20,0x029C,0x11CF,0xB1,0xCD,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("96916B20-029C-11CF-B1CD-444553540000")
    IDlgGenUserDef : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgGenUserDefVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgGenUserDef * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgGenUserDef * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgGenUserDef * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgGenUserDef * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgGenUserDef * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgGenUserDef * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgGenUserDef * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgGenUserDefVtbl;

    interface IDlgGenUserDef
    {
        CONST_VTBL struct IDlgGenUserDefVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgGenUserDef_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgGenUserDef_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgGenUserDef_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgGenUserDef_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgGenUserDef_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgGenUserDef_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgGenUserDef_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgGenUserDef_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgGenUserDef,0x96916B21,0x029C,0x11CF,0xB1,0xCD,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("96916B21-029C-11CF-B1CD-444553540000")
CDlgGenUserDef;
#endif

#ifndef __IDlgGenWarble_DISPINTERFACE_DEFINED__
#define __IDlgGenWarble_DISPINTERFACE_DEFINED__

/* dispinterface IDlgGenWarble */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgGenWarble,0x96916B22,0x029C,0x11CF,0xB1,0xCD,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("96916B22-029C-11CF-B1CD-444553540000")
    IDlgGenWarble : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgGenWarbleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgGenWarble * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgGenWarble * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgGenWarble * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgGenWarble * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgGenWarble * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgGenWarble * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgGenWarble * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgGenWarbleVtbl;

    interface IDlgGenWarble
    {
        CONST_VTBL struct IDlgGenWarbleVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgGenWarble_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgGenWarble_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgGenWarble_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgGenWarble_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgGenWarble_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgGenWarble_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgGenWarble_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgGenWarble_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgGenWarble,0x96916B23,0x029C,0x11CF,0xB1,0xCD,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("96916B23-029C-11CF-B1CD-444553540000")
CDlgGenWarble;
#endif

#ifndef __IDlgXfInvert_DISPINTERFACE_DEFINED__
#define __IDlgXfInvert_DISPINTERFACE_DEFINED__

/* dispinterface IDlgXfInvert */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgXfInvert,0xF34C3880,0x0676,0x11CF,0xB1,0xCD,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("F34C3880-0676-11CF-B1CD-444553540000")
    IDlgXfInvert : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgXfInvertVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgXfInvert * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgXfInvert * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgXfInvert * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgXfInvert * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgXfInvert * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgXfInvert * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgXfInvert * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgXfInvertVtbl;

    interface IDlgXfInvert
    {
        CONST_VTBL struct IDlgXfInvertVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgXfInvert_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgXfInvert_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgXfInvert_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgXfInvert_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgXfInvert_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgXfInvert_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgXfInvert_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgXfInvert_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgXfInvert,0xF34C3881,0x0676,0x11CF,0xB1,0xCD,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("F34C3881-0676-11CF-B1CD-444553540000")
CDlgXfInvert;
#endif

#ifndef __IDlgMsrPassive_DISPINTERFACE_DEFINED__
#define __IDlgMsrPassive_DISPINTERFACE_DEFINED__

/* dispinterface IDlgMsrPassive */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgMsrPassive,0x544800A0,0x09B1,0x11CF,0xB1,0xCD,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("544800A0-09B1-11CF-B1CD-444553540000")
    IDlgMsrPassive : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgMsrPassiveVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgMsrPassive * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgMsrPassive * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgMsrPassive * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgMsrPassive * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgMsrPassive * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgMsrPassive * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgMsrPassive * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgMsrPassiveVtbl;

    interface IDlgMsrPassive
    {
        CONST_VTBL struct IDlgMsrPassiveVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgMsrPassive_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgMsrPassive_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgMsrPassive_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgMsrPassive_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgMsrPassive_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgMsrPassive_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgMsrPassive_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgMsrPassive_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgMsrPassive,0x544800A1,0x09B1,0x11CF,0xB1,0xCD,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("544800A1-09B1-11CF-B1CD-444553540000")
CDlgMsrPassive;
#endif

#ifndef __IDlgCalcSealed_DISPINTERFACE_DEFINED__
#define __IDlgCalcSealed_DISPINTERFACE_DEFINED__

/* dispinterface IDlgCalcSealed */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgCalcSealed,0x785A3500,0x0AE5,0x11CF,0xB1,0xCD,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("785A3500-0AE5-11CF-B1CD-444553540000")
    IDlgCalcSealed : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgCalcSealedVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgCalcSealed * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgCalcSealed * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgCalcSealed * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgCalcSealed * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgCalcSealed * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgCalcSealed * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgCalcSealed * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgCalcSealedVtbl;

    interface IDlgCalcSealed
    {
        CONST_VTBL struct IDlgCalcSealedVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgCalcSealed_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgCalcSealed_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgCalcSealed_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgCalcSealed_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgCalcSealed_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgCalcSealed_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgCalcSealed_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgCalcSealed_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgCalcSealed,0x785A3501,0x0AE5,0x11CF,0xB1,0xCD,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("785A3501-0AE5-11CF-B1CD-444553540000")
CDlgCalcSealed;
#endif

#ifndef __IDlgCalcBandAir_DISPINTERFACE_DEFINED__
#define __IDlgCalcBandAir_DISPINTERFACE_DEFINED__

/* dispinterface IDlgCalcBandAir */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgCalcBandAir,0x785A3502,0x0AE5,0x11CF,0xB1,0xCD,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("785A3502-0AE5-11CF-B1CD-444553540000")
    IDlgCalcBandAir : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgCalcBandAirVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgCalcBandAir * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgCalcBandAir * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgCalcBandAir * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgCalcBandAir * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgCalcBandAir * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgCalcBandAir * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgCalcBandAir * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgCalcBandAirVtbl;

    interface IDlgCalcBandAir
    {
        CONST_VTBL struct IDlgCalcBandAirVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgCalcBandAir_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgCalcBandAir_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgCalcBandAir_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgCalcBandAir_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgCalcBandAir_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgCalcBandAir_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgCalcBandAir_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgCalcBandAir_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgCalcBandAir,0x785A3503,0x0AE5,0x11CF,0xB1,0xCD,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("785A3503-0AE5-11CF-B1CD-444553540000")
CDlgCalcBandAir;
#endif

#ifndef __IDlgCalcBandChamber_DISPINTERFACE_DEFINED__
#define __IDlgCalcBandChamber_DISPINTERFACE_DEFINED__

/* dispinterface IDlgCalcBandChamber */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgCalcBandChamber,0x785A3504,0x0AE5,0x11CF,0xB1,0xCD,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("785A3504-0AE5-11CF-B1CD-444553540000")
    IDlgCalcBandChamber : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgCalcBandChamberVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgCalcBandChamber * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgCalcBandChamber * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgCalcBandChamber * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgCalcBandChamber * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgCalcBandChamber * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgCalcBandChamber * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgCalcBandChamber * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgCalcBandChamberVtbl;

    interface IDlgCalcBandChamber
    {
        CONST_VTBL struct IDlgCalcBandChamberVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgCalcBandChamber_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgCalcBandChamber_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgCalcBandChamber_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgCalcBandChamber_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgCalcBandChamber_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgCalcBandChamber_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgCalcBandChamber_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgCalcBandChamber_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgCalcBandChamber,0x785A3505,0x0AE5,0x11CF,0xB1,0xCD,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("785A3505-0AE5-11CF-B1CD-444553540000")
CDlgCalcBandChamber;
#endif

#ifndef __IDlgCalcVented_DISPINTERFACE_DEFINED__
#define __IDlgCalcVented_DISPINTERFACE_DEFINED__

/* dispinterface IDlgCalcVented */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgCalcVented,0x785A3506,0x0AE5,0x11CF,0xB1,0xCD,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("785A3506-0AE5-11CF-B1CD-444553540000")
    IDlgCalcVented : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgCalcVentedVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgCalcVented * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgCalcVented * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgCalcVented * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgCalcVented * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgCalcVented * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgCalcVented * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgCalcVented * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgCalcVentedVtbl;

    interface IDlgCalcVented
    {
        CONST_VTBL struct IDlgCalcVentedVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgCalcVented_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgCalcVented_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgCalcVented_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgCalcVented_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgCalcVented_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgCalcVented_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgCalcVented_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgCalcVented_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgCalcVented,0x785A3507,0x0AE5,0x11CF,0xB1,0xCD,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("785A3507-0AE5-11CF-B1CD-444553540000")
CDlgCalcVented;
#endif

#ifndef __IDlgFilter_DISPINTERFACE_DEFINED__
#define __IDlgFilter_DISPINTERFACE_DEFINED__

/* dispinterface IDlgFilter */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgFilter,0xE4A434A0,0x0EE5,0x11CF,0xB1,0xCD,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("E4A434A0-0EE5-11CF-B1CD-444553540000")
    IDlgFilter : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgFilterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgFilter * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgFilter * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgFilter * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgFilter * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgFilter * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgFilter * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgFilter * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgFilterVtbl;

    interface IDlgFilter
    {
        CONST_VTBL struct IDlgFilterVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgFilter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgFilter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgFilter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgFilter_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgFilter_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgFilter_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgFilter_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgFilter_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgFilter,0xE4A434A1,0x0EE5,0x11CF,0xB1,0xCD,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("E4A434A1-0EE5-11CF-B1CD-444553540000")
CDlgFilter;
#endif

#ifndef __IDlgPrefMeasure_DISPINTERFACE_DEFINED__
#define __IDlgPrefMeasure_DISPINTERFACE_DEFINED__

/* dispinterface IDlgPrefMeasure */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgPrefMeasure,0x51FCD7A0,0x1242,0x11CF,0xB1,0xCD,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("51FCD7A0-1242-11CF-B1CD-444553540000")
    IDlgPrefMeasure : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgPrefMeasureVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgPrefMeasure * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgPrefMeasure * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgPrefMeasure * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgPrefMeasure * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgPrefMeasure * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgPrefMeasure * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgPrefMeasure * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgPrefMeasureVtbl;

    interface IDlgPrefMeasure
    {
        CONST_VTBL struct IDlgPrefMeasureVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgPrefMeasure_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgPrefMeasure_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgPrefMeasure_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgPrefMeasure_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgPrefMeasure_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgPrefMeasure_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgPrefMeasure_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgPrefMeasure_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgPrefMeasure,0x51FCD7A1,0x1242,0x11CF,0xB1,0xCD,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("51FCD7A1-1242-11CF-B1CD-444553540000")
CDlgPrefMeasure;
#endif

#ifndef __IDlgTree_DISPINTERFACE_DEFINED__
#define __IDlgTree_DISPINTERFACE_DEFINED__

/* dispinterface IDlgTree */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgTree,0x48089AA1,0x2B82,0x11CF,0xAA,0x03,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("48089AA1-2B82-11CF-AA03-444553540000")
    IDlgTree : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgTreeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgTree * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgTree * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgTree * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgTree * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgTree * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgTree * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgTree * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgTreeVtbl;

    interface IDlgTree
    {
        CONST_VTBL struct IDlgTreeVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgTree_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgTree_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgTree_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgTree_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgTree_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgTree_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgTree_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgTree_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgTree,0x48089AA2,0x2B82,0x11CF,0xAA,0x03,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("48089AA2-2B82-11CF-AA03-444553540000")
CDlgTree;
#endif

#ifndef __IDlgXfFilter_DISPINTERFACE_DEFINED__
#define __IDlgXfFilter_DISPINTERFACE_DEFINED__

/* dispinterface IDlgXfFilter */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgXfFilter,0x930EAE20,0x5B5E,0x11CF,0xAA,0x04,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("930EAE20-5B5E-11CF-AA04-444553540000")
    IDlgXfFilter : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgXfFilterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgXfFilter * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgXfFilter * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgXfFilter * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgXfFilter * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgXfFilter * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgXfFilter * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgXfFilter * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgXfFilterVtbl;

    interface IDlgXfFilter
    {
        CONST_VTBL struct IDlgXfFilterVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgXfFilter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgXfFilter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgXfFilter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgXfFilter_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgXfFilter_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgXfFilter_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgXfFilter_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgXfFilter_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgXfFilter,0x930EAE21,0x5B5E,0x11CF,0xAA,0x04,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("930EAE21-5B5E-11CF-AA04-444553540000")
CDlgXfFilter;
#endif

#ifndef __IDlgFilterLow_DISPINTERFACE_DEFINED__
#define __IDlgFilterLow_DISPINTERFACE_DEFINED__

/* dispinterface IDlgFilterLow */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgFilterLow,0xB2CCFBC0,0x5B60,0x11CF,0xAA,0x04,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("B2CCFBC0-5B60-11CF-AA04-444553540000")
    IDlgFilterLow : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgFilterLowVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgFilterLow * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgFilterLow * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgFilterLow * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgFilterLow * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgFilterLow * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgFilterLow * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgFilterLow * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgFilterLowVtbl;

    interface IDlgFilterLow
    {
        CONST_VTBL struct IDlgFilterLowVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgFilterLow_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgFilterLow_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgFilterLow_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgFilterLow_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgFilterLow_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgFilterLow_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgFilterLow_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgFilterLow_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgFilterLow,0xB2CCFBC1,0x5B60,0x11CF,0xAA,0x04,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("B2CCFBC1-5B60-11CF-AA04-444553540000")
CDlgFilterLow;
#endif

#ifndef __IdlgFilterHigh_DISPINTERFACE_DEFINED__
#define __IdlgFilterHigh_DISPINTERFACE_DEFINED__

/* dispinterface IdlgFilterHigh */
/* [uuid] */ 


DEFINE_GUID(DIID_IdlgFilterHigh,0xB2CCFBC2,0x5B60,0x11CF,0xAA,0x04,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("B2CCFBC2-5B60-11CF-AA04-444553540000")
    IdlgFilterHigh : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IdlgFilterHighVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IdlgFilterHigh * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IdlgFilterHigh * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IdlgFilterHigh * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IdlgFilterHigh * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IdlgFilterHigh * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IdlgFilterHigh * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IdlgFilterHigh * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IdlgFilterHighVtbl;

    interface IdlgFilterHigh
    {
        CONST_VTBL struct IdlgFilterHighVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IdlgFilterHigh_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IdlgFilterHigh_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IdlgFilterHigh_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IdlgFilterHigh_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IdlgFilterHigh_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IdlgFilterHigh_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IdlgFilterHigh_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IdlgFilterHigh_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CdlgFilterHigh,0xB2CCFBC3,0x5B60,0x11CF,0xAA,0x04,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("B2CCFBC3-5B60-11CF-AA04-444553540000")
CdlgFilterHigh;
#endif

#ifndef __IdlgFilterStop_DISPINTERFACE_DEFINED__
#define __IdlgFilterStop_DISPINTERFACE_DEFINED__

/* dispinterface IdlgFilterStop */
/* [uuid] */ 


DEFINE_GUID(DIID_IdlgFilterStop,0xB2CCFBC4,0x5B60,0x11CF,0xAA,0x04,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("B2CCFBC4-5B60-11CF-AA04-444553540000")
    IdlgFilterStop : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IdlgFilterStopVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IdlgFilterStop * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IdlgFilterStop * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IdlgFilterStop * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IdlgFilterStop * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IdlgFilterStop * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IdlgFilterStop * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IdlgFilterStop * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IdlgFilterStopVtbl;

    interface IdlgFilterStop
    {
        CONST_VTBL struct IdlgFilterStopVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IdlgFilterStop_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IdlgFilterStop_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IdlgFilterStop_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IdlgFilterStop_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IdlgFilterStop_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IdlgFilterStop_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IdlgFilterStop_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IdlgFilterStop_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CdlgFilterStop,0xB2CCFBC5,0x5B60,0x11CF,0xAA,0x04,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("B2CCFBC5-5B60-11CF-AA04-444553540000")
CdlgFilterStop;
#endif

#ifndef __IDlgFilterPass_DISPINTERFACE_DEFINED__
#define __IDlgFilterPass_DISPINTERFACE_DEFINED__

/* dispinterface IDlgFilterPass */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgFilterPass,0xB2CCFBC6,0x5B60,0x11CF,0xAA,0x04,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("B2CCFBC6-5B60-11CF-AA04-444553540000")
    IDlgFilterPass : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgFilterPassVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgFilterPass * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgFilterPass * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgFilterPass * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgFilterPass * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgFilterPass * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgFilterPass * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgFilterPass * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgFilterPassVtbl;

    interface IDlgFilterPass
    {
        CONST_VTBL struct IDlgFilterPassVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgFilterPass_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgFilterPass_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgFilterPass_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgFilterPass_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgFilterPass_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgFilterPass_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgFilterPass_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgFilterPass_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgFilterPass,0xB2CCFBC7,0x5B60,0x11CF,0xAA,0x04,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("B2CCFBC7-5B60-11CF-AA04-444553540000")
CDlgFilterPass;
#endif

#ifndef __IDlgMsrDistort_DISPINTERFACE_DEFINED__
#define __IDlgMsrDistort_DISPINTERFACE_DEFINED__

/* dispinterface IDlgMsrDistort */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgMsrDistort,0x11B046E0,0x666C,0x11CF,0xAA,0x04,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("11B046E0-666C-11CF-AA04-444553540000")
    IDlgMsrDistort : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgMsrDistortVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgMsrDistort * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgMsrDistort * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgMsrDistort * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgMsrDistort * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgMsrDistort * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgMsrDistort * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgMsrDistort * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgMsrDistortVtbl;

    interface IDlgMsrDistort
    {
        CONST_VTBL struct IDlgMsrDistortVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgMsrDistort_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgMsrDistort_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgMsrDistort_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgMsrDistort_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgMsrDistort_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgMsrDistort_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgMsrDistort_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgMsrDistort_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgMsrDistort,0x11B046E1,0x666C,0x11CF,0xAA,0x04,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("11B046E1-666C-11CF-AA04-444553540000")
CDlgMsrDistort;
#endif

#ifndef __IDlgPrefReference_DISPINTERFACE_DEFINED__
#define __IDlgPrefReference_DISPINTERFACE_DEFINED__

/* dispinterface IDlgPrefReference */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgPrefReference,0xA308C900,0x6D10,0x11CF,0xAA,0x04,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("A308C900-6D10-11CF-AA04-444553540000")
    IDlgPrefReference : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgPrefReferenceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgPrefReference * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgPrefReference * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgPrefReference * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgPrefReference * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgPrefReference * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgPrefReference * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgPrefReference * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgPrefReferenceVtbl;

    interface IDlgPrefReference
    {
        CONST_VTBL struct IDlgPrefReferenceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgPrefReference_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgPrefReference_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgPrefReference_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgPrefReference_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgPrefReference_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgPrefReference_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgPrefReference_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgPrefReference_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgPrefReference,0xA308C901,0x6D10,0x11CF,0xAA,0x04,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("A308C901-6D10-11CF-AA04-444553540000")
CDlgPrefReference;
#endif

#ifndef __IDlgCalibrate_DISPINTERFACE_DEFINED__
#define __IDlgCalibrate_DISPINTERFACE_DEFINED__

/* dispinterface IDlgCalibrate */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgCalibrate,0x235663A0,0x7627,0x11CF,0xAA,0x04,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("235663A0-7627-11CF-AA04-444553540000")
    IDlgCalibrate : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgCalibrateVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgCalibrate * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgCalibrate * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgCalibrate * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgCalibrate * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgCalibrate * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgCalibrate * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgCalibrate * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgCalibrateVtbl;

    interface IDlgCalibrate
    {
        CONST_VTBL struct IDlgCalibrateVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgCalibrate_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgCalibrate_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgCalibrate_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgCalibrate_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgCalibrate_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgCalibrate_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgCalibrate_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgCalibrate_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgCalibrate,0x235663A1,0x7627,0x11CF,0xAA,0x04,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("235663A1-7627-11CF-AA04-444553540000")
CDlgCalibrate;
#endif

#ifndef __IDlgCalcTuned_DISPINTERFACE_DEFINED__
#define __IDlgCalcTuned_DISPINTERFACE_DEFINED__

/* dispinterface IDlgCalcTuned */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgCalcTuned,0xB4D31A40,0x78D3,0x11CF,0xAA,0x04,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("B4D31A40-78D3-11CF-AA04-444553540000")
    IDlgCalcTuned : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgCalcTunedVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgCalcTuned * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgCalcTuned * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgCalcTuned * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgCalcTuned * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgCalcTuned * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgCalcTuned * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgCalcTuned * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgCalcTunedVtbl;

    interface IDlgCalcTuned
    {
        CONST_VTBL struct IDlgCalcTunedVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgCalcTuned_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgCalcTuned_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgCalcTuned_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgCalcTuned_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgCalcTuned_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgCalcTuned_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgCalcTuned_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgCalcTuned_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgCalcTuned,0xB4D31A41,0x78D3,0x11CF,0xAA,0x04,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("B4D31A41-78D3-11CF-AA04-444553540000")
CDlgCalcTuned;
#endif

#ifndef __IDlgCalcPassive_DISPINTERFACE_DEFINED__
#define __IDlgCalcPassive_DISPINTERFACE_DEFINED__

/* dispinterface IDlgCalcPassive */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgCalcPassive,0xB4D31A42,0x78D3,0x11CF,0xAA,0x04,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("B4D31A42-78D3-11CF-AA04-444553540000")
    IDlgCalcPassive : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgCalcPassiveVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgCalcPassive * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgCalcPassive * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgCalcPassive * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgCalcPassive * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgCalcPassive * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgCalcPassive * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgCalcPassive * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgCalcPassiveVtbl;

    interface IDlgCalcPassive
    {
        CONST_VTBL struct IDlgCalcPassiveVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgCalcPassive_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgCalcPassive_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgCalcPassive_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgCalcPassive_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgCalcPassive_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgCalcPassive_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgCalcPassive_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgCalcPassive_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgCalcPassive,0xB4D31A43,0x78D3,0x11CF,0xAA,0x04,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("B4D31A43-78D3-11CF-AA04-444553540000")
CDlgCalcPassive;
#endif

#ifndef __IDlgPrefMarker_DISPINTERFACE_DEFINED__
#define __IDlgPrefMarker_DISPINTERFACE_DEFINED__

/* dispinterface IDlgPrefMarker */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgPrefMarker,0xF0549AC0,0x7EC4,0x11CF,0xAA,0x04,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("F0549AC0-7EC4-11CF-AA04-444553540000")
    IDlgPrefMarker : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgPrefMarkerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgPrefMarker * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgPrefMarker * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgPrefMarker * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgPrefMarker * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgPrefMarker * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgPrefMarker * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgPrefMarker * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgPrefMarkerVtbl;

    interface IDlgPrefMarker
    {
        CONST_VTBL struct IDlgPrefMarkerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgPrefMarker_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgPrefMarker_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgPrefMarker_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgPrefMarker_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgPrefMarker_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgPrefMarker_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgPrefMarker_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgPrefMarker_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_CDlgPrefMarker,0xF0549AC1,0x7EC4,0x11CF,0xAA,0x04,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("F0549AC1-7EC4-11CF-AA04-444553540000")
CDlgPrefMarker;
#endif

#ifndef __IDlgOptXover_DISPINTERFACE_DEFINED__
#define __IDlgOptXover_DISPINTERFACE_DEFINED__

/* dispinterface IDlgOptXover */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgOptXover,0x1B6B9BA0,0x895B,0x11CF,0xAA,0x04,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("1B6B9BA0-895B-11CF-AA04-444553540000")
    IDlgOptXover : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgOptXoverVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgOptXover * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgOptXover * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgOptXover * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgOptXover * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgOptXover * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgOptXover * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgOptXover * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgOptXoverVtbl;

    interface IDlgOptXover
    {
        CONST_VTBL struct IDlgOptXoverVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgOptXover_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgOptXover_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgOptXover_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgOptXover_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgOptXover_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgOptXover_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgOptXover_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgOptXover_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_DLGOPTXOVER,0x1B6B9BA1,0x895B,0x11CF,0xAA,0x04,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("1B6B9BA1-895B-11CF-AA04-444553540000")
DLGOPTXOVER;
#endif

#ifndef __IDlgCrossover_DISPINTERFACE_DEFINED__
#define __IDlgCrossover_DISPINTERFACE_DEFINED__

/* dispinterface IDlgCrossover */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgCrossover,0x1B6B9BA2,0x895B,0x11CF,0xAA,0x04,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("1B6B9BA2-895B-11CF-AA04-444553540000")
    IDlgCrossover : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgCrossoverVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgCrossover * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgCrossover * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgCrossover * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgCrossover * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgCrossover * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgCrossover * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgCrossover * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgCrossoverVtbl;

    interface IDlgCrossover
    {
        CONST_VTBL struct IDlgCrossoverVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgCrossover_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgCrossover_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgCrossover_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgCrossover_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgCrossover_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgCrossover_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgCrossover_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgCrossover_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_DLGCROSSOVER,0x1B6B9BA3,0x895B,0x11CF,0xAA,0x04,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("1B6B9BA3-895B-11CF-AA04-444553540000")
DLGCROSSOVER;
#endif

#ifndef __IDlgAddPassive_DISPINTERFACE_DEFINED__
#define __IDlgAddPassive_DISPINTERFACE_DEFINED__

/* dispinterface IDlgAddPassive */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgAddPassive,0x615486C0,0x8967,0x11CF,0xAA,0x04,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("615486C0-8967-11CF-AA04-444553540000")
    IDlgAddPassive : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgAddPassiveVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgAddPassive * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgAddPassive * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgAddPassive * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgAddPassive * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgAddPassive * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgAddPassive * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgAddPassive * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgAddPassiveVtbl;

    interface IDlgAddPassive
    {
        CONST_VTBL struct IDlgAddPassiveVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgAddPassive_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgAddPassive_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgAddPassive_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgAddPassive_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgAddPassive_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgAddPassive_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgAddPassive_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgAddPassive_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_DLGADDPASSIVE,0x615486C1,0x8967,0x11CF,0xAA,0x04,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("615486C1-8967-11CF-AA04-444553540000")
DLGADDPASSIVE;
#endif

#ifndef __IDlgZobel_DISPINTERFACE_DEFINED__
#define __IDlgZobel_DISPINTERFACE_DEFINED__

/* dispinterface IDlgZobel */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgZobel,0x5401F4E0,0x897F,0x11CF,0xAA,0x04,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("5401F4E0-897F-11CF-AA04-444553540000")
    IDlgZobel : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgZobelVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgZobel * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgZobel * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgZobel * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgZobel * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgZobel * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgZobel * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgZobel * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgZobelVtbl;

    interface IDlgZobel
    {
        CONST_VTBL struct IDlgZobelVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgZobel_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgZobel_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgZobel_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgZobel_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgZobel_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgZobel_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgZobel_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgZobel_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_DLGZOBEL,0x5401F4E1,0x897F,0x11CF,0xAA,0x04,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("5401F4E1-897F-11CF-AA04-444553540000")
DLGZOBEL;
#endif

#ifndef __IDlgNotch_DISPINTERFACE_DEFINED__
#define __IDlgNotch_DISPINTERFACE_DEFINED__

/* dispinterface IDlgNotch */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgNotch,0x5401F4E2,0x897F,0x11CF,0xAA,0x04,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("5401F4E2-897F-11CF-AA04-444553540000")
    IDlgNotch : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgNotchVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgNotch * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgNotch * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgNotch * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgNotch * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgNotch * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgNotch * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgNotch * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgNotchVtbl;

    interface IDlgNotch
    {
        CONST_VTBL struct IDlgNotchVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgNotch_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgNotch_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgNotch_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgNotch_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgNotch_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgNotch_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgNotch_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgNotch_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_DLGNOTCH,0x5401F4E3,0x897F,0x11CF,0xAA,0x04,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("5401F4E3-897F-11CF-AA04-444553540000")
DLGNOTCH;
#endif

#ifndef __IDlgNetLayout_DISPINTERFACE_DEFINED__
#define __IDlgNetLayout_DISPINTERFACE_DEFINED__

/* dispinterface IDlgNetLayout */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgNetLayout,0xA9092EE0,0x8AEC,0x11CF,0xAA,0x04,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("A9092EE0-8AEC-11CF-AA04-444553540000")
    IDlgNetLayout : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgNetLayoutVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgNetLayout * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgNetLayout * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgNetLayout * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgNetLayout * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgNetLayout * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgNetLayout * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgNetLayout * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgNetLayoutVtbl;

    interface IDlgNetLayout
    {
        CONST_VTBL struct IDlgNetLayoutVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgNetLayout_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgNetLayout_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgNetLayout_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgNetLayout_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgNetLayout_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgNetLayout_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgNetLayout_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgNetLayout_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_DLGNETLAYOUT,0xA9092EE1,0x8AEC,0x11CF,0xAA,0x04,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("A9092EE1-8AEC-11CF-AA04-444553540000")
DLGNETLAYOUT;
#endif

#ifndef __IDlgDriverEstimate_DISPINTERFACE_DEFINED__
#define __IDlgDriverEstimate_DISPINTERFACE_DEFINED__

/* dispinterface IDlgDriverEstimate */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgDriverEstimate,0x2D835140,0xA4CF,0x11CF,0xAA,0x03,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("2D835140-A4CF-11CF-AA03-444553540000")
    IDlgDriverEstimate : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgDriverEstimateVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgDriverEstimate * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgDriverEstimate * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgDriverEstimate * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgDriverEstimate * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgDriverEstimate * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgDriverEstimate * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgDriverEstimate * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgDriverEstimateVtbl;

    interface IDlgDriverEstimate
    {
        CONST_VTBL struct IDlgDriverEstimateVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgDriverEstimate_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgDriverEstimate_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgDriverEstimate_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgDriverEstimate_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgDriverEstimate_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgDriverEstimate_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgDriverEstimate_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgDriverEstimate_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_DLGDRIVERESTIMATE,0x2D835141,0xA4CF,0x11CF,0xAA,0x03,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("2D835141-A4CF-11CF-AA03-444553540000")
DLGDRIVERESTIMATE;
#endif

#ifndef __IDlgXfSplice_DISPINTERFACE_DEFINED__
#define __IDlgXfSplice_DISPINTERFACE_DEFINED__

/* dispinterface IDlgXfSplice */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgXfSplice,0x86088380,0xA862,0x11CF,0xAA,0x03,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("86088380-A862-11CF-AA03-444553540000")
    IDlgXfSplice : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgXfSpliceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgXfSplice * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgXfSplice * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgXfSplice * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgXfSplice * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgXfSplice * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgXfSplice * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgXfSplice * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgXfSpliceVtbl;

    interface IDlgXfSplice
    {
        CONST_VTBL struct IDlgXfSpliceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgXfSplice_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgXfSplice_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgXfSplice_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgXfSplice_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgXfSplice_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgXfSplice_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgXfSplice_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgXfSplice_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_DLGXFSPLICE,0x86088381,0xA862,0x11CF,0xAA,0x03,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("86088381-A862-11CF-AA03-444553540000")
DLGXFSPLICE;
#endif

#ifndef __IDlgPrefImpedance_DISPINTERFACE_DEFINED__
#define __IDlgPrefImpedance_DISPINTERFACE_DEFINED__

/* dispinterface IDlgPrefImpedance */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgPrefImpedance,0x57BA63E0,0xAFDD,0x11CF,0xAA,0x03,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("57BA63E0-AFDD-11CF-AA03-444553540000")
    IDlgPrefImpedance : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgPrefImpedanceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgPrefImpedance * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgPrefImpedance * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgPrefImpedance * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgPrefImpedance * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgPrefImpedance * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgPrefImpedance * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgPrefImpedance * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgPrefImpedanceVtbl;

    interface IDlgPrefImpedance
    {
        CONST_VTBL struct IDlgPrefImpedanceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgPrefImpedance_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgPrefImpedance_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgPrefImpedance_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgPrefImpedance_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgPrefImpedance_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgPrefImpedance_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgPrefImpedance_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgPrefImpedance_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_DLGPREFIMPEDANCE,0x57BA63E1,0xAFDD,0x11CF,0xAA,0x03,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("57BA63E1-AFDD-11CF-AA03-444553540000")
DLGPREFIMPEDANCE;
#endif

#ifndef __IDlgPrefGeneral_DISPINTERFACE_DEFINED__
#define __IDlgPrefGeneral_DISPINTERFACE_DEFINED__

/* dispinterface IDlgPrefGeneral */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgPrefGeneral,0x013D3B80,0x3171,0x11D0,0xAA,0x04,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("013D3B80-3171-11D0-AA04-444553540000")
    IDlgPrefGeneral : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgPrefGeneralVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgPrefGeneral * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgPrefGeneral * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgPrefGeneral * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgPrefGeneral * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgPrefGeneral * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgPrefGeneral * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgPrefGeneral * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgPrefGeneralVtbl;

    interface IDlgPrefGeneral
    {
        CONST_VTBL struct IDlgPrefGeneralVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgPrefGeneral_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgPrefGeneral_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgPrefGeneral_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgPrefGeneral_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgPrefGeneral_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgPrefGeneral_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgPrefGeneral_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgPrefGeneral_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_DLGPREFGENERAL,0x013D3B81,0x3171,0x11D0,0xAA,0x04,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("013D3B81-3171-11D0-AA04-444553540000")
DLGPREFGENERAL;
#endif

#ifndef __IDlgCalJig3_DISPINTERFACE_DEFINED__
#define __IDlgCalJig3_DISPINTERFACE_DEFINED__

/* dispinterface IDlgCalJig3 */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgCalJig3,0xDA743AC0,0x338D,0x11D0,0xAA,0x04,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("DA743AC0-338D-11D0-AA04-444553540000")
    IDlgCalJig3 : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgCalJig3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgCalJig3 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgCalJig3 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgCalJig3 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgCalJig3 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgCalJig3 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgCalJig3 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgCalJig3 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgCalJig3Vtbl;

    interface IDlgCalJig3
    {
        CONST_VTBL struct IDlgCalJig3Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgCalJig3_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgCalJig3_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgCalJig3_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgCalJig3_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgCalJig3_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgCalJig3_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgCalJig3_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgCalJig3_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_DLGCALJIG3,0xDA743AC1,0x338D,0x11D0,0xAA,0x04,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("DA743AC1-338D-11D0-AA04-444553540000")
DLGCALJIG3;
#endif

#ifndef __IDlgWizLoop_DISPINTERFACE_DEFINED__
#define __IDlgWizLoop_DISPINTERFACE_DEFINED__

/* dispinterface IDlgWizLoop */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgWizLoop,0x1E22DC40,0x3519,0x11D0,0xAA,0x04,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("1E22DC40-3519-11D0-AA04-444553540000")
    IDlgWizLoop : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgWizLoopVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgWizLoop * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgWizLoop * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgWizLoop * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgWizLoop * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgWizLoop * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgWizLoop * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgWizLoop * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgWizLoopVtbl;

    interface IDlgWizLoop
    {
        CONST_VTBL struct IDlgWizLoopVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgWizLoop_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgWizLoop_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgWizLoop_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgWizLoop_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgWizLoop_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgWizLoop_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgWizLoop_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgWizLoop_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_DLGWIZLOOP,0x1E22DC41,0x3519,0x11D0,0xAA,0x04,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("1E22DC41-3519-11D0-AA04-444553540000")
DLGWIZLOOP;
#endif

#ifndef __IDlgWizLoopBegin_DISPINTERFACE_DEFINED__
#define __IDlgWizLoopBegin_DISPINTERFACE_DEFINED__

/* dispinterface IDlgWizLoopBegin */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgWizLoopBegin,0x1E22DC42,0x3519,0x11D0,0xAA,0x04,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("1E22DC42-3519-11D0-AA04-444553540000")
    IDlgWizLoopBegin : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgWizLoopBeginVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgWizLoopBegin * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgWizLoopBegin * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgWizLoopBegin * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgWizLoopBegin * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgWizLoopBegin * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgWizLoopBegin * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgWizLoopBegin * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgWizLoopBeginVtbl;

    interface IDlgWizLoopBegin
    {
        CONST_VTBL struct IDlgWizLoopBeginVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgWizLoopBegin_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgWizLoopBegin_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgWizLoopBegin_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgWizLoopBegin_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgWizLoopBegin_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgWizLoopBegin_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgWizLoopBegin_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgWizLoopBegin_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_DLGWIZLPBEGIN,0x1E22DC43,0x3519,0x11D0,0xAA,0x04,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("1E22DC43-3519-11D0-AA04-444553540000")
DLGWIZLPBEGIN;
#endif

#ifndef __IDlgCalWizLoopEnd_DISPINTERFACE_DEFINED__
#define __IDlgCalWizLoopEnd_DISPINTERFACE_DEFINED__

/* dispinterface IDlgCalWizLoopEnd */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgCalWizLoopEnd,0x1E22DC44,0x3519,0x11D0,0xAA,0x04,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("1E22DC44-3519-11D0-AA04-444553540000")
    IDlgCalWizLoopEnd : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgCalWizLoopEndVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgCalWizLoopEnd * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgCalWizLoopEnd * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgCalWizLoopEnd * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgCalWizLoopEnd * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgCalWizLoopEnd * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgCalWizLoopEnd * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgCalWizLoopEnd * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgCalWizLoopEndVtbl;

    interface IDlgCalWizLoopEnd
    {
        CONST_VTBL struct IDlgCalWizLoopEndVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgCalWizLoopEnd_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgCalWizLoopEnd_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgCalWizLoopEnd_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgCalWizLoopEnd_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgCalWizLoopEnd_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgCalWizLoopEnd_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgCalWizLoopEnd_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgCalWizLoopEnd_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_DLGCALWIZLOOPEND,0x1E22DC45,0x3519,0x11D0,0xAA,0x04,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("1E22DC45-3519-11D0-AA04-444553540000")
DLGCALWIZLOOPEND;
#endif

#ifndef __IDlgCalLoopJig_DISPINTERFACE_DEFINED__
#define __IDlgCalLoopJig_DISPINTERFACE_DEFINED__

/* dispinterface IDlgCalLoopJig */
/* [uuid] */ 


DEFINE_GUID(DIID_IDlgCalLoopJig,0x1E22DC46,0x3519,0x11D0,0xAA,0x04,0x44,0x45,0x53,0x54,0x00,0x00);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("1E22DC46-3519-11D0-AA04-444553540000")
    IDlgCalLoopJig : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDlgCalLoopJigVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDlgCalLoopJig * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDlgCalLoopJig * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDlgCalLoopJig * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDlgCalLoopJig * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDlgCalLoopJig * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDlgCalLoopJig * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDlgCalLoopJig * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IDlgCalLoopJigVtbl;

    interface IDlgCalLoopJig
    {
        CONST_VTBL struct IDlgCalLoopJigVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDlgCalLoopJig_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDlgCalLoopJig_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDlgCalLoopJig_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDlgCalLoopJig_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDlgCalLoopJig_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDlgCalLoopJig_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDlgCalLoopJig_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDlgCalLoopJig_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_DLGCALLOOPJIG,0x1E22DC47,0x3519,0x11D0,0xAA,0x04,0x44,0x45,0x53,0x54,0x00,0x00);

#ifdef __cplusplus

class DECLSPEC_UUID("1E22DC47-3519-11D0-AA04-444553540000")
DLGCALLOOPJIG;
#endif
#endif /* __audtest_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


