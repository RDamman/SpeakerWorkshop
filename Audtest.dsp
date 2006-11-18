# Microsoft Developer Studio Project File - Name="Audtest" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Audtest - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Audtest.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Audtest.mak" CFG="Audtest - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Audtest - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "Audtest - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Audtest - Win32 Local" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/", aaaaaaaa"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Audtest - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\WinDebug"
# PROP BASE Intermediate_Dir ".\WinDebug"
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\WinDebug"
# PROP Intermediate_Dir ".\WinDebug"
# PROP Ignore_Export_Lib 0
# ADD BASE CPP /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W4 /Gm /Gi /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 winmm.lib /nologo /subsystem:windows /debug /machine:I386 /out:".\WinDebug\SpkrWork.exe"
# SUBTRACT LINK32 /pdb:none /map /nodefaultlib

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\WinRel"
# PROP BASE Intermediate_Dir ".\WinRel"
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\WinRel"
# PROP Intermediate_Dir ".\WinRel"
# PROP Ignore_Export_Lib 0
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W4 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 winmm.lib /nologo /subsystem:windows /machine:I386 /out:".\WinRel\SpkrWork.exe"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Audtest___Win32_Local"
# PROP BASE Intermediate_Dir "Audtest___Win32_Local"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WinLocal"
# PROP Intermediate_Dir "WinLocal"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Zp1 /MT /W4 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MT /W4 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "DONATIONAL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 winmm.lib /nologo /subsystem:windows /machine:I386 /out:".\WinRel\SpkrWork.exe"
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 winmm.lib /nologo /subsystem:windows /machine:I386 /out:".\WinLocal\SpkrWork.exe"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "Audtest - Win32 Debug"
# Name "Audtest - Win32 Release"
# Name "Audtest - Win32 Local"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\audtedoc.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\audtest.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Audtest.odl
# End Source File
# Begin Source File

SOURCE=.\Audtest.RC

!IF  "$(CFG)" == "Audtest - Win32 Debug"

# ADD BASE RSC /l 0x409 /i ".\WinDebug"
# ADD RSC /l 0x409 /i ".\WinDebug"
# SUBTRACT RSC /d "_AFXDLL"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\audtevw.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\BarNetwork.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Chart.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Clipbd.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ColorButton.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Complex.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Ctrls.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DataSet.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DataTag.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Debug.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dibapi.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgAddDriver.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgAddPassive.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgAudioCheck.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgBurst.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgCalcMerge.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgCalcPassive.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgCalcTuned.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgCalibrate.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgCalWizAmp.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgCalWizBrd.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgCalWizImp.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgCalWizLp.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgCalWizVol.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgcbox.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgChart.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgChartProp.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgchdat.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgchgen.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgCreateGoal.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgCrossover.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgDataS.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgDefWr.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgDisable48K.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgDoc.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgDocGe.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgdrdat.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgdrgen.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgDrive.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgdrpar.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgDrvEquiv.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgDsDat.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgDsGen.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgDvEst.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgEnclo.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgengen.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgenpar.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgfilte.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgFldGe.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgFolder.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgGener.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlggenge.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlggenus.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlggrid.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlglocat.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgLPad.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgmls.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgMsrDistort.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgMsrIn.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgMsrPa.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgnetdr.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgNetGe.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgNetLayout.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgnetli.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgNetOptimize.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgNetwo.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgnoise.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgNotch.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgNote.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgOptXover.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgpertu.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgPlayS.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgprcha.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgPrefAcoustic.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgPrefDebug.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgPrefer.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgPrefGe.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgprefm.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgPrefMarker.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgprefn.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgPrefReference.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgPrfIm.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgprtra.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgpulse.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgrecor.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgRenam.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgrmbox.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgRmGen.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgRmWal.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgRoom.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgRoot.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgsawto.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgSelec.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgSine.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgSplice.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgsquar.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgSweep.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgTimeDist.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgTones.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgVolumeCalc.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgVuMeter.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgxcadd.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgxcimp.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgxfcor.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgxfdel.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgxffft.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgXfFrq.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgxfgrp.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgxfiff.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgxfinv.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgxflim.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgxfsca.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgxfsmo.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dlgxftru.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgXfWaterfall.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DlgZobel.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DrawObj.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Driver.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Enclosur.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Filter.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Folder.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\FxFont.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Generat.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Grid.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ipFrame.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mainFrm.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mmWave.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\mmwOps.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Named.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\NetClip.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\NetOps.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\NetOptimize.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Network.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\OpCode.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\opItem.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\opRecord.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Passive.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Room.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SetLocale.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Splash.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SplitBar.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\srvrItem.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\stdAfx.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\treectrl.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TrueDialogBar.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Utils.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ViewRecd.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\vwchart.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\vwdata.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\vwdrive.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\vwencl.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\vwgen.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\vwNet.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\vwroom.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\vwtree.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\xForm.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\xFormBig.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\XformGoal.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ZcSplitCtrl.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\zFormEdt.cpp

!IF  "$(CFG)" == "Audtest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\audtedoc.h
# End Source File
# Begin Source File

SOURCE=.\audtest.h
# End Source File
# Begin Source File

SOURCE=.\audtevw.h
# End Source File
# Begin Source File

SOURCE=.\BarNetwork.h
# End Source File
# Begin Source File

SOURCE=.\Chart.h
# End Source File
# Begin Source File

SOURCE=.\childfrm.h
# End Source File
# Begin Source File

SOURCE=.\ClipBd.h
# End Source File
# Begin Source File

SOURCE=.\ColorButton.h
# End Source File
# Begin Source File

SOURCE=.\Complex.h
# End Source File
# Begin Source File

SOURCE=.\Ctrls.h
# End Source File
# Begin Source File

SOURCE=.\dataset.h
# End Source File
# Begin Source File

SOURCE=.\DataTag.h
# End Source File
# Begin Source File

SOURCE=.\Debug.h
# End Source File
# Begin Source File

SOURCE=.\dibapi.h
# End Source File
# Begin Source File

SOURCE=.\DlgAddDriver.h
# End Source File
# Begin Source File

SOURCE=.\DlgAddPassive.h
# End Source File
# Begin Source File

SOURCE=.\DlgAudioCheck.h
# End Source File
# Begin Source File

SOURCE=.\DlgBurst.h
# End Source File
# Begin Source File

SOURCE=.\DlgCalcMerge.h
# End Source File
# Begin Source File

SOURCE=.\dlgCalcPassive.h
# End Source File
# Begin Source File

SOURCE=.\dlgCalcTuned.h
# End Source File
# Begin Source File

SOURCE=.\dlgCalibrate.h
# End Source File
# Begin Source File

SOURCE=.\DlgCalWizAmp.h
# End Source File
# Begin Source File

SOURCE=.\DlgCalWizBrd.h
# End Source File
# Begin Source File

SOURCE=.\DlgCalWizImp.h
# End Source File
# Begin Source File

SOURCE=.\DlgCalWizLp.h
# End Source File
# Begin Source File

SOURCE=.\DlgCalWizVol.h
# End Source File
# Begin Source File

SOURCE=.\dlgcbox.h
# End Source File
# Begin Source File

SOURCE=.\Dlgchart.h
# End Source File
# Begin Source File

SOURCE=.\DlgChartProp.h
# End Source File
# Begin Source File

SOURCE=.\dlgchdat.h
# End Source File
# Begin Source File

SOURCE=.\dlgchgen.h
# End Source File
# Begin Source File

SOURCE=.\DlgCreateGoal.h
# End Source File
# Begin Source File

SOURCE=.\DlgCrossover.h
# End Source File
# Begin Source File

SOURCE=.\dlgdatas.h
# End Source File
# Begin Source File

SOURCE=.\DlgDefWr.h
# End Source File
# Begin Source File

SOURCE=.\DlgDisable48K.h
# End Source File
# Begin Source File

SOURCE=.\DlgDoc.h
# End Source File
# Begin Source File

SOURCE=.\DlgDocGe.h
# End Source File
# Begin Source File

SOURCE=.\dlgdrdat.h
# End Source File
# Begin Source File

SOURCE=.\dlgdrgen.h
# End Source File
# Begin Source File

SOURCE=.\dlgdrive.h
# End Source File
# Begin Source File

SOURCE=.\dlgdrPar.h
# End Source File
# Begin Source File

SOURCE=.\DlgDrvEquiv.h
# End Source File
# Begin Source File

SOURCE=.\dlgdsdat.h
# End Source File
# Begin Source File

SOURCE=.\dlgdsgen.h
# End Source File
# Begin Source File

SOURCE=.\DlgDvEst.h
# End Source File
# Begin Source File

SOURCE=.\dlgenclo.h
# End Source File
# Begin Source File

SOURCE=.\dlgenGen.h
# End Source File
# Begin Source File

SOURCE=.\dlgEnPar.h
# End Source File
# Begin Source File

SOURCE=.\dlgfilte.h
# End Source File
# Begin Source File

SOURCE=.\DlgFldGe.h
# End Source File
# Begin Source File

SOURCE=.\DlgFolder.h
# End Source File
# Begin Source File

SOURCE=.\dlggener.h
# End Source File
# Begin Source File

SOURCE=.\dlgGenGe.h
# End Source File
# Begin Source File

SOURCE=.\dlgGenUs.h
# End Source File
# Begin Source File

SOURCE=.\dlggrid.h
# End Source File
# Begin Source File

SOURCE=.\dlglocat.h
# End Source File
# Begin Source File

SOURCE=.\DlgLPad.h
# End Source File
# Begin Source File

SOURCE=.\dlgMls.h
# End Source File
# Begin Source File

SOURCE=.\DlgMsrDistort.h
# End Source File
# Begin Source File

SOURCE=.\DlgMsrIn.h
# End Source File
# Begin Source File

SOURCE=.\dlgmsrpa.h
# End Source File
# Begin Source File

SOURCE=.\dlgnetdr.h
# End Source File
# Begin Source File

SOURCE=.\dlgnetge.h
# End Source File
# Begin Source File

SOURCE=.\DlgNetLayout.h
# End Source File
# Begin Source File

SOURCE=.\dlgnetli.h
# End Source File
# Begin Source File

SOURCE=.\DlgNetOptimize.h
# End Source File
# Begin Source File

SOURCE=.\dlgnetwo.h
# End Source File
# Begin Source File

SOURCE=.\dlgNoise.h
# End Source File
# Begin Source File

SOURCE=.\DlgNotch.h
# End Source File
# Begin Source File

SOURCE=.\DlgNote.h
# End Source File
# Begin Source File

SOURCE=.\DlgOptXover.h
# End Source File
# Begin Source File

SOURCE=.\dlgpertu.h
# End Source File
# Begin Source File

SOURCE=.\dlgplays.h
# End Source File
# Begin Source File

SOURCE=.\dlgprcha.h
# End Source File
# Begin Source File

SOURCE=.\DlgPrefAcoustic.h
# End Source File
# Begin Source File

SOURCE=.\DlgPrefDebug.h
# End Source File
# Begin Source File

SOURCE=.\dlgPrefer.h
# End Source File
# Begin Source File

SOURCE=.\DlgPrefGe.h
# End Source File
# Begin Source File

SOURCE=.\dlgprefm.h
# End Source File
# Begin Source File

SOURCE=.\DlgPrefMarker.h
# End Source File
# Begin Source File

SOURCE=.\dlgprefn.h
# End Source File
# Begin Source File

SOURCE=.\DlgPrefReference.h
# End Source File
# Begin Source File

SOURCE=.\DlgPrfIm.h
# End Source File
# Begin Source File

SOURCE=.\dlgprtra.h
# End Source File
# Begin Source File

SOURCE=.\dlgPulse.h
# End Source File
# Begin Source File

SOURCE=.\dlgrecor.h
# End Source File
# Begin Source File

SOURCE=.\dlgrenam.h
# End Source File
# Begin Source File

SOURCE=.\dlgrmbox.h
# End Source File
# Begin Source File

SOURCE=.\dlgrmgen.h
# End Source File
# Begin Source File

SOURCE=.\dlgrmwal.h
# End Source File
# Begin Source File

SOURCE=.\dlgroom.h
# End Source File
# Begin Source File

SOURCE=.\DlgRoot.h
# End Source File
# Begin Source File

SOURCE=.\dlgSawto.h
# End Source File
# Begin Source File

SOURCE=.\dlgSelec.h
# End Source File
# Begin Source File

SOURCE=.\dlgSine.h
# End Source File
# Begin Source File

SOURCE=.\DlgSplice.h
# End Source File
# Begin Source File

SOURCE=.\dlgSquar.h
# End Source File
# Begin Source File

SOURCE=.\dlgSweep.h
# End Source File
# Begin Source File

SOURCE=.\DlgTimeDist.h
# End Source File
# Begin Source File

SOURCE=.\dlgTones.h
# End Source File
# Begin Source File

SOURCE=.\DlgVolumeCalc.h
# End Source File
# Begin Source File

SOURCE=.\DlgVuMeter.h
# End Source File
# Begin Source File

SOURCE=.\dlgxcadd.h
# End Source File
# Begin Source File

SOURCE=.\dlgxcimp.h
# End Source File
# Begin Source File

SOURCE=.\dlgxfcor.h
# End Source File
# Begin Source File

SOURCE=.\dlgxfdel.h
# End Source File
# Begin Source File

SOURCE=.\dlgxffft.h
# End Source File
# Begin Source File

SOURCE=.\dlgXfFrq.h
# End Source File
# Begin Source File

SOURCE=.\dlgXfGrp.h
# End Source File
# Begin Source File

SOURCE=.\dlgxfiff.h
# End Source File
# Begin Source File

SOURCE=.\dlgxfinv.h
# End Source File
# Begin Source File

SOURCE=.\dlgxflim.h
# End Source File
# Begin Source File

SOURCE=.\dlgxfsca.h
# End Source File
# Begin Source File

SOURCE=.\dlgxfsmo.h
# End Source File
# Begin Source File

SOURCE=.\dlgxftru.h
# End Source File
# Begin Source File

SOURCE=.\DlgXfWaterfall.h
# End Source File
# Begin Source File

SOURCE=.\DlgZobel.h
# End Source File
# Begin Source File

SOURCE=.\DrawObj.h
# End Source File
# Begin Source File

SOURCE=.\Driver.h
# End Source File
# Begin Source File

SOURCE=.\Enclosur.h
# End Source File
# Begin Source File

SOURCE=.\filter.h
# End Source File
# Begin Source File

SOURCE=.\Folder.h
# End Source File
# Begin Source File

SOURCE=.\fxfont.h
# End Source File
# Begin Source File

SOURCE=.\generat.h
# End Source File
# Begin Source File

SOURCE=.\Grid.h
# End Source File
# Begin Source File

SOURCE=.\Ipframe.h
# End Source File
# Begin Source File

SOURCE=.\mainfrm.h
# End Source File
# Begin Source File

SOURCE=.\mmwave.h
# End Source File
# Begin Source File

SOURCE=.\Named.h
# End Source File
# Begin Source File

SOURCE=.\NetClip.h
# End Source File
# Begin Source File

SOURCE=.\NetOptimize.h
# End Source File
# Begin Source File

SOURCE=.\network.h
# End Source File
# Begin Source File

SOURCE=.\opcode.h
# End Source File
# Begin Source File

SOURCE=.\opitem.h
# End Source File
# Begin Source File

SOURCE=.\opRecord.h
# End Source File
# Begin Source File

SOURCE=.\Passive.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\Room.h
# End Source File
# Begin Source File

SOURCE=.\SetLocale.h
# End Source File
# Begin Source File

SOURCE=.\Splash.h
# End Source File
# Begin Source File

SOURCE=.\SplitBar.h
# End Source File
# Begin Source File

SOURCE=.\srvritem.h
# End Source File
# Begin Source File

SOURCE=.\stdafx.h
# End Source File
# Begin Source File

SOURCE=.\treectrl.h
# End Source File
# Begin Source File

SOURCE=.\TrueDialogBar.h
# End Source File
# Begin Source File

SOURCE=.\Utils.h
# End Source File
# Begin Source File

SOURCE=.\vwchart.h
# End Source File
# Begin Source File

SOURCE=.\vwdata.h
# End Source File
# Begin Source File

SOURCE=.\vwdrive.h
# End Source File
# Begin Source File

SOURCE=.\vwencl.h
# End Source File
# Begin Source File

SOURCE=.\vwgen.h
# End Source File
# Begin Source File

SOURCE=.\vwNet.h
# End Source File
# Begin Source File

SOURCE=.\vwroom.h
# End Source File
# Begin Source File

SOURCE=.\vwtree.h
# End Source File
# Begin Source File

SOURCE=.\xform.h
# End Source File
# Begin Source File

SOURCE=.\XformAll.h
# End Source File
# Begin Source File

SOURCE=.\XformGoal.h
# End Source File
# Begin Source File

SOURCE=.\ZcSplitCtrl.h
# End Source File
# Begin Source File

SOURCE=.\zFormEdt.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Res\arrow.cur
# End Source File
# Begin Source File

SOURCE=.\Res\arrowcop.cur
# End Source File
# Begin Source File

SOURCE=.\Res\audtedoc.ico
# End Source File
# Begin Source File

SOURCE=.\Res\audtest.ico
# End Source File
# Begin Source File

SOURCE=.\Res\Audtest.rc2
# End Source File
# Begin Source File

SOURCE=.\res\bandpass.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bandstop.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00004.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00005.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\bmp00006.bmp
# End Source File
# Begin Source File

SOURCE=.\res\chkduplex.ico
# End Source File
# Begin Source File

SOURCE=.\res\chkin.ico
# End Source File
# Begin Source File

SOURCE=.\res\chkout.ico
# End Source File
# Begin Source File

SOURCE=.\Res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\res\highpass.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\Res\ico00002.ico
# End Source File
# Begin Source File

SOURCE=.\Res\ico00003.ico
# End Source File
# Begin Source File

SOURCE=.\Res\ico00004.ico
# End Source File
# Begin Source File

SOURCE=.\Res\ico00005.ico
# End Source File
# Begin Source File

SOURCE=.\Res\idr_chart.ico
# End Source File
# Begin Source File

SOURCE=.\Res\idr_comp.ico
# End Source File
# Begin Source File

SOURCE=.\Res\idr_data.ico
# End Source File
# Begin Source File

SOURCE=.\Res\idr_drive.ico
# End Source File
# Begin Source File

SOURCE=.\Res\idr_encl.ico
# End Source File
# Begin Source File

SOURCE=.\Res\idr_gen.ico
# End Source File
# Begin Source File

SOURCE=.\Res\idr_main.ico
# End Source File
# Begin Source File

SOURCE=.\Res\idr_net.ico
# End Source File
# Begin Source File

SOURCE=.\Res\idr_room.ico
# End Source File
# Begin Source File

SOURCE=.\Res\idr_tree.ico
# End Source File
# Begin Source File

SOURCE=.\Res\Itoolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\lowpass1.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\lowpass2.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\lowpass3.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\mover.cur
# End Source File
# Begin Source File

SOURCE=.\Res\mover1.cur
# End Source File
# Begin Source File

SOURCE=.\Res\nodrop.cur
# End Source File
# Begin Source File

SOURCE=.\res\resistor.bmp
# End Source File
# Begin Source File

SOURCE=.\res\smallcro.cur
# End Source File
# Begin Source File

SOURCE=.\Res\splsh256.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolchar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tooldriv.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolencl.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolnetw.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolsign.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\treelist.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\uniter.cur
# End Source File
# Begin Source File

SOURCE=.\res\wiz_amp_.bmp
# End Source File
# Begin Source File

SOURCE=.\res\wiz_brd_.bmp
# End Source File
# Begin Source File

SOURCE=.\res\wiz_cal4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\wiz_lp_b.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\Wz_impbe.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\Wz_impj1.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\Wz_impj2.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\Wz_lp1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\xvhigh3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\xvhigh4.bmp
# End Source File
# End Group
# Begin Group "Help Files"

# PROP Default_Filter ".hpj"
# Begin Source File

SOURCE=".\hlp\Speaker Workshop.hpj"

!IF  "$(CFG)" == "Audtest - Win32 Debug"

USERDEP__SPEAK="..\..\My Documents\Speaker Workshop.rtf"	"SpkrWork.cnt"	
# Begin Custom Build
ProjDir=.
InputPath=".\hlp\Speaker Workshop.hpj"

"$(ProjDir)/SpkrWork.hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo on 
	hcw /C /E $(InputPath) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Audtest - Win32 Release"

USERDEP__SPEAK="\My Documents\Speaker Workshop.rtf"	
# Begin Custom Build
ProjDir=.
InputPath=".\hlp\Speaker Workshop.hpj"

"$(ProjDir)/SpkrWork.hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	hcw /C /E $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "Audtest - Win32 Local"

USERDEP__SPEAK="\My Documents\Speaker Workshop.rtf"	
# Begin Custom Build
ProjDir=.
InputPath=".\hlp\Speaker Workshop.hpj"

"$(ProjDir)/SpkrWork.hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	hcw /C /E $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
# Section Audtest : {3FF43293-2929-11CF-AA03-444553540000}
# 	1:17:CG_IDS_DISK_SPACE:106
# 	1:19:CG_IDS_PHYSICAL_MEM:105
# 	1:25:CG_IDS_DISK_SPACE_UNAVAIL:107
# 	2:10:SysInfoKey:1234
# End Section
