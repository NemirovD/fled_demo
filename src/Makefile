#GENERAL INFORMATION
EXECNAME = fled.exe
OBJECTFILES = driver.obj functions.obj classes.obj lightdata.obj

#COMPILER INFORMATION
OWNINCLUDES = C:\Android Project\opencv\build\include
STANDALONEOPTIONS = /EHsc /nologo /c /O2
INCLUDE = $(INCLUDE)$(OWNINCLUDES)

#LINKER OPTIONS
OPENCV_LIB = C:\Android Project\opencv\build\x86\vc10\staticlib

LINK =  "$(OPENCV_LIB)\IlmImf.lib" \
		"$(OPENCV_LIB)\libjasper.lib" \
		"$(OPENCV_LIB)\libjpeg.lib" \
		"$(OPENCV_LIB)\libpng.lib" \
		"$(OPENCV_LIB)\libtiff.lib" \
		"$(OPENCV_LIB)\zlib.lib" \
		"$(OPENCV_LIB)\opencv_calib3d240.lib" \
		"$(OPENCV_LIB)\opencv_contrib240.lib" \
		"$(OPENCV_LIB)\opencv_core240.lib" \
		"$(OPENCV_LIB)\opencv_features2d240.lib" \
		"$(OPENCV_LIB)\opencv_flann240.lib" \
		"$(OPENCV_LIB)\opencv_gpu240.lib" \
		"$(OPENCV_LIB)\opencv_haartraining_engine.lib" \
		"$(OPENCV_LIB)\opencv_highgui240.lib" \
		"$(OPENCV_LIB)\opencv_imgproc240.lib" \
		"$(OPENCV_LIB)\opencv_legacy240.lib" \
		"$(OPENCV_LIB)\opencv_ml240.lib" \
		"$(OPENCV_LIB)\opencv_nonfree240.lib" \
		"$(OPENCV_LIB)\opencv_objdetect240.lib" \
		"$(OPENCV_LIB)\opencv_photo240.lib" \
		"$(OPENCV_LIB)\opencv_stitching240.lib" \
		"$(OPENCV_LIB)\opencv_ts240.lib" \
		"$(OPENCV_LIB)\opencv_video240.lib" \
		"$(OPENCV_LIB)\opencv_videostab240.lib" \
		"vfw32.lib" \
		"comctl32.lib" \
		"kernel32.lib" \
		"user32.lib" \
		"gdi32.lib" \
		"winspool.lib" \
		"comdlg32.lib" \
		"advapi32.lib" \
		"shell32.lib" \
		"ole32.lib" \
		"oleaut32.lib" \
		"uuid.lib" \
		"odbc32.lib" \
		"odbccp32.lib"

prog: $(OBJECTFILES)
	link /OUT:$(EXECNAME) /nologo $(OBJECTFILES) $(LINK)
	del *.obj
	
driver.obj: functions.obj lightdata.obj classes.obj
	cl $(STANDALONEOPTIONS) driver.cc
	
functions.obj: classes.obj lightdata.obj
	cl $(STANDALONEOPTIONS) functions.cc
	
lightdata.obj: classes.obj
	cl $(STANDALONEOPTIONS) lightdata.cc
	
classes.obj:
	cl $(STANDALONEOPTIONS) classes.cc
	
run:
	fled 5 -1 -1 10 10 GREY
	
clean:
	del fled.exe
	del *.obj