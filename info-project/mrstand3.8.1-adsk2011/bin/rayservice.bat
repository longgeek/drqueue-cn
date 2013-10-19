@echo off
@setlocal

rem *+
rem ***********************************************************************
rem **
rem **  Module:
rem **	mental ray 3.8
rem **
rem **  Copyright (C) 1997-2010 Autodesk Inc.
rem **
rem **
rem ** The information  in  this  file is  provided for the  exclusive use of the
rem ** licensees of Autodesk Inc. Such users have the right to use, modify,
rem ** and  incorporate this code  into  other  products  for purposes authorized
rem ** by the Autodesk Inc. license agreement, without fee.
rem **
rem ** Autodesk Inc. disclaims all warranties with regard to this software,
rem ** including all implied warranties  of  merchantability and  fitness.  In no
rem ** event  shall  Autodesk Inc. be liable for any  special,  indirect or
rem ** consequential  damages  or  any  damages whatsoever resulting from loss of
rem ** use, data  or profits, whether in  an  action of  contract,  negligence or
rem ** other tortious  action,  arising out of or  in connection  with the use or
rem ** performance of this software.
rem **
rem **  This file is required for network rendering and is called by the mi-ray
rem **  service.  Please refer to the online networking rendering documentation
rem **  for more information.
rem **
rem *************************************************************************

set MRSTANDALONE=C:\Program Files\Autodesk\mrstand3.8.1-adsk2011\

set MI_RAY_SERVICE=adskmr381

"%MRSTANDALONE%\bin\rayserver.exe"

