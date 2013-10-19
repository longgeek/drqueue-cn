********************************************
** mental images
********************************************


Description:
------------
Test scenes using MetaSL shaders for mental ray 3.7+


Setup:
------
Note: We are assuming a clean installation of mental ray standalone and mental mill.

{ray3rc}  
  - Change the registry 'mrpath' to point to the mental ray binary directory.
  - Change the registry 'mmpath' to point to the mental mill installation directory.
  - Change the registry '_MI_REG_INCLUDE' to include the directory 
    to all MetaSL shaders.
{msl_run.bat} 
  - Change the environment 'MR' to point to the mental ray binary directory.


Rendering the scenes:
---------------------
To render the scenes, open a command window in this directory. Then 
execute the following command:
  
  msl_run.bat [name of scene]
