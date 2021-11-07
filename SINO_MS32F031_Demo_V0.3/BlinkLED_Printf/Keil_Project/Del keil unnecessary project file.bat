@ECHO OFF

REM hide all bat files
ATTRIB +H *.bat /S
REM hide all A51 files
ATTRIB +H *.a51 /S
REM hide all s files
ATTRIB +H *.s /S
REM hide all c files
ATTRIB +H *.c /S
REM hide all h files
ATTRIB +H *.h /S
REM hide all ini files
ATTRIB +H *.ini /S
REM hide all bin/hex/lib files
ATTRIB +H *.bin /S 
ATTRIB +H *.hex /S 
ATTRIB +H *.lib /S 
REM hide all keil project files
ATTRIB +H *.uvopt /S 
ATTRIB +H *.uvproj /S 
ATTRIB +H *.uvoptx /S 
ATTRIB +H *.uvprojx /S 
REM hide all svd files
ATTRIB +H *.SFR /S 
ATTRIB +H *.svd /S 

REM delete all unhided files
DEL /S /Q /A-H *.* 

REM unhide all bat files
ATTRIB -H *.bat /S
REM unhide all A51 files
ATTRIB -H *.a51 /S 
REM unhide all s files
ATTRIB -H *.s /S
REM unhide all c files
ATTRIB -H *.c /S
REM unhide all h files
ATTRIB -H *.h /S
REM hide all ini files
ATTRIB -H *.ini /S
REM unhide all bin/hex files
ATTRIB -H *.bin /S 
ATTRIB -H *.hex /S 
ATTRIB -H *.lib /S 
REM unhide all keil project files
ATTRIB -H *.uvopt /S 
ATTRIB -H *.uvproj /S 
ATTRIB -H *.uvoptx /S 
ATTRIB -H *.uvprojx /S
REM unhide all svd files
ATTRIB -H *.SFR /S 
ATTRIB -H *.svd /S 

REM PAUSE